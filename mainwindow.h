#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <main.h>
#include <QMainWindow>
#define MAX_PATH 4096




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

private:
    void init();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
