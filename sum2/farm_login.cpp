#include "farm_login.h"
#include "ui_farm_login.h"
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
QString namee="username";
QString pwdd="password";
farm_login::farm_login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::farm_login)
{
    ui->setupUi(this);
   // setWindowState(Qt::WindowMaximized);
    QPalette palette;
    QPixmap pixmap("D:/qt/sum2/background2.jpg");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
    int flag1=0;
    QFile file("D:/qt/sum2/user.txt");
        //如果文件不存在会自动创建文件
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"打开失败";
        }else{
            qDebug()<<"打开成功";
        }

        //读取文件
        int line = 1;
        //判断文件是否已经读到末尾了
        int flag=0;
        while(!file.atEnd()){
            char buffer[1024];
            //读取一行数据
            qint64 length = file.readLine(buffer,1024);
            if(length != -1&&flag==0){
                namee=buffer;
                namee = namee.simplified();
                if(namee!="")
                {
                    flag1=1;
                }
                flag++;
            }
            else if(length != -1&&flag==1){
                pwdd=buffer;
                pwdd = pwdd.simplified();
            }
        }
        qint64 length = -1;
        QString kkkk="      ";
        length = file.write(kkkk.toLatin1(),kkkk.length());
        //关闭文件
        file.close();
        if(flag1==1)
        {
            ui->lineEdit->setAlignment(Qt::AlignHCenter);
            ui->lineEdit->setText(namee);
            ui->lineEdit_2->setEchoMode(QLineEdit::Password);
            ui->lineEdit_2->setAlignment(Qt::AlignHCenter);
            ui->lineEdit_2->setText(pwdd);
            ui->checkBox->setCheckState(Qt::Checked);
        }
        else
        {
            ui->lineEdit->setAlignment(Qt::AlignHCenter);
            ui->lineEdit->setPlaceholderText("username");
            ui->lineEdit_2->setEchoMode(QLineEdit::Password);
            ui->lineEdit_2->setAlignment(Qt::AlignHCenter);
            ui->lineEdit_2->setPlaceholderText("password");
        }
}

farm_login::~farm_login()
{
    delete ui;
}


void farm_login::on_pushButton_2_clicked()
{
    QString name = ui->lineEdit->text();
    QString pwd = ui->lineEdit_2->text();
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
        if(flag1==1)
        {
            if (flag2==1)
            {
                if(ui->checkBox->isChecked()==true)
                {
                    QFile file("D:/qt/sum2/user.txt");
                    if(!file.open(QIODevice::ReadWrite))
                    {
                            qDebug()<<"打开失败";
                    }
                    else
                    {
                            qDebug()<<"打开成功";
                    }
                    qint64 length = -1;
                    QString kkk="\n";
                    length = file.write(name.toLatin1(),name.length());
                    length = file.write(kkk.toLatin1(),kkk.length());
                    length = file.write(pwd.toLatin1(),pwd.length());
                    if(length == -1){
                           qDebug()<<"写入文件失败";
                       }else{
                           qDebug()<<"写入文件成功";
                       }
                    file.close();
                    /*int line = 1;
                    while(!file.atEnd())
                    {
                        char buffer[1024];
                        qint64 length = file.readLine(buffer,1024);
                        if(length != -1){
                             pwdd=buffer;
                    }*/
                }
                MainWindow *reg = new MainWindow();
                reg->show();
                this->close();
            }
            else
            {
                QMessageBox::information(this, "提示","登入失败!密码错误", QMessageBox::Ok);
            }
        }
        else
        {
            QMessageBox::information(this, "提示","你还未注册!请先去注册吧", QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::information(this, "提示", "登入失败!未注册,请先注册", QMessageBox::Ok);
    }
}


void farm_login::on_pushButton_clicked()
{
    regisist *reg = new regisist();
    reg->show();
    this->close();
}

