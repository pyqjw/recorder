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
    //"border-image: url(:/images/3.png);"
    /*QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);*/
    QPalette palette;
    QPixmap pixmap("border-image: url(:/imglogin/background2.jpg);");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
    int flag1=0;
    QFile file("user.txt");
        //如果文件不存在会自动创建文件
        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"打开失败";
        }else{
            qDebug()<<"打开成功";
        }

        //读取文件

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
    int flag1=0,flag2=0,checkk=0;
    QString name = ui->lineEdit->text();
    QString pwd = ui->lineEdit_2->text();
    if(ui->checkBox->isChecked()==true)
    {
        checkk=1;
    }
    //把name、pwd、checkk传过去
    //把flag1、flag2值接受过来

    if((!name.isEmpty())&&(!pwd.isEmpty()))
    {
        if(flag1==1)
        {
            if (flag2==1)
            {
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

