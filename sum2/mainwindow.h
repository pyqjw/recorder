#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <string>
#include <windows.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
using namespace std;




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int xxxx;
    bool isrecording=0;
    time_t rawtime;
    char outputname[MAX_PATH*4];
    time_t clockstartt;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int start_rec();
private slots:
    void on_action_about_triggered();

    void on_recordButton_clicked();

    void on_MainWindow_destroyed();

private:
    void init();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
