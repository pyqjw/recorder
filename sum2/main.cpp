#include "farm_login.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    farm_login w;
    w.show();
    return a.exec();
}
