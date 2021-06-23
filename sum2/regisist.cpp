#include "regisist.h"
#include "ui_regisist.h"
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
regisist::regisist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::regisist)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    QPalette palette;
    QPixmap pixmap("D:/qt/sum2/background.jpg");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
}

regisist::~regisist()
{
    delete ui;
}

void regisist::on_pushButton_clicked()
{
    QString name=ui->lineEdit->text();
    QString pwd=ui->lineEdit_2->text();
    QString sex=ui->radioButton->isChecked() ? "Man" : "Woman";
    QString birthday=ui->dateEdit->text();
    QString tel=ui->lineEdit_3->text();
    if((!name.isEmpty())&&(!pwd.isEmpty()))
    {
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
    else
    {
        QMessageBox::information(this, "提示", "注册失败", QMessageBox::Ok);
    }
}


void regisist::on_pushButton_2_clicked()
{
    farm_login *reg = new farm_login();
    reg->show();
    this->close();
}

