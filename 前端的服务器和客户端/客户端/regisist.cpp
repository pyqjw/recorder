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

    //把name、pwd传过去

    if((!name.isEmpty())&&(!pwd.isEmpty()))
    {
       //把name、pwd传过去
        while(1)
        {
            break;
        }
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

