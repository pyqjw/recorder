#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCompleter>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QStringLiteral>
#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::login()
{
    //服务器端处理函数
    //客户端接受的是nameee和pwddd和int checkkk
    char *nameee;
    char * pwddd;
    int checkkk;








    QString name = nameee;
    QString pwd = pwddd;
    int check=checkkk;




    //服务器端处理
    QString namee = "";
    QString pwdd = "";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");//数据库驱动类型位sqlserver
    QString dsn = QString::fromLocal8Bit("qtsql");
    db.setHostName("localhost");        //选择本地主机，或则127.0.0.1
    db.setDatabaseName(dsn);
       // db.setDatabaseName("qtsql");       //设置数据库名称
    db.setUserName("tyc2");       //登录用户
    db.setPassword("123456");     //密码
    if (!db.open())
    {
       QMessageBox::critical(0, qApp->tr("Cannot open database"),
                                  db.lastError().databaseText(), QMessageBox::Cancel);

    }
    else
        qDebug()<<"database open success!";
    QSqlQuery query(db);
    query.exec("use [user] select * from dbo.login");
    int flag1=0;
    int flag2=0;
    while(query.next())
    {
       namee=query.value(0).toString();
       pwdd=query.value(1).toString();
       if(namee==name)
       {
          flag1=1;
          if(pwd==pwdd)
          {
              flag2=1;
          }
          break;
       }
     }
     db.close();



     //往客户端传flag1和flag2的两个值；
}
void MainWindow::regisist()
{
    //接受传过来的name、pwd

    char *namee;
    char *pwdd;


    QString name=namee;
    QString pwd=pwdd;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");//数据库驱动类型位sqlserver
    QString dsn = QString::fromLocal8Bit("qtsql");
    db.setHostName("localhost");        //选择本地主机，或则127.0.0.1
    db.setDatabaseName(dsn);
   // db.setDatabaseName("qtsql");       //设置数据库名称
    db.setUserName("tyc2");       //登录用户
    db.setPassword("123456");     //密码
    if (!db.open())
    {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              db.lastError().databaseText(), QMessageBox::Cancel);

    }
    else
            qDebug()<<"database open success!";
    QSqlQuery query(db);
    query.exec("use [user] select * from dbo.login where username = '"+name+"'");
    if(query.next())
    {
        QMessageBox::information(this, "提示", "you zhuce guole", QMessageBox::Ok);
    }
    else
    {
        query.exec("use [user] insert into dbo.login values('"+name+"','"+pwd+"')");
        QMessageBox::information(this, "提示", "注册成功", QMessageBox::Ok);
    }
    db.close();
}
