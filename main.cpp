#include "mainwindow.h"
#include "main.h"

int main(int argc, char *argv[])
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QString dsn = QString::fromLocal8Bit("test");      //数据源名称
    db.setHostName("localhost");                        //选择本地主机，127.0.1.1
    db.setDatabaseName(dsn);                            //设置数据源名称
    db.setUserName("pyqjw");                               //登录用户
    db.setPassword("123456");                              //密码
    if(!db.open())                                      //打开数据库
    {
        //qDebug()<<db.lastError().text();
        //QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
        return false;                                   //打开失败
    }
    QSqlQuery sq(db);
    sq.exec("use teaching");
    sq.exec("select * from student");
    sq.next();
    QString ss = sq.value(0).toString();
    ss = sq.value(1).toString();
   QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
