#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPalette>
void MainWindow::init() {
    ui->frate->setText(QString("50"));
    ui->LeftTopX->setText(QString("0"));
    ui->LeftTopY->setText(QString("0"));
    ui->width->setText(QString("1920"));
    ui->height->setText(QString("1080"));
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    init();
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::start_rec() {
    this->showMinimized();   //窗口最小化
    Sleep(250);
    char tmpfnbuf[MAX_PATH*4];
    QString qs = ui->path->text();
    sprintf(tmpfnbuf, "%s", qs.toStdString().c_str());
    if (strcmp(tmpfnbuf, "") == 0) {
        time(&rawtime);
        strftime(outputname, 500, "Records/Record_%Y-%m-%d_%H-%M-%S.mpg", localtime(&rawtime));
        ui->path->setText(outputname);
    } else {
        sprintf(outputname, "%s", tmpfnbuf);
    }
    /*
    string ifoutput;
    ifoutput="Records/tmp.mpg";

    fstream _file;
    _file.open(ifoutput.c_str(), ios::in);//判断文件是否存在
    if (!_file)
    {
        _file.close();
    }
    else
    {
        _file.close();
        MessageBox (0, "故障：录制时的临时文件已存在，这可能是由于您同时进行了两个录屏进程。若您确定不是如此（即本台电脑只打开了本一个Ericord窗口进程），则可能是由于上此运行Ericord时异常终止导致的，请删除Records/tmp.avi，并重启本软件。", "错误", MB_OK|MB_ICONERROR);
        return (1);
    }
    */
    QRect re = this->rect();
    int w = re.right(), h = re.bottom();
    string xx, yy, ww, hh, frate;
    xx = ui->LeftTopX->text().toStdString();
    yy = ui->LeftTopY->text().toStdString();
    ww = ui->width->text().toStdString();
    hh = ui->height->text().toStdString();
    frate = ui->frate->text().toStdString();
    string exe = "tools/ffmpeg.exe -f gdigrab -framerate ";
    exe += frate;
    exe += " -offset_x ";
    exe += xx;//获取的左上角x
    exe += " -offset_y ";
    exe += yy;//获取的左上角y
    exe += " -video_size ";
    exe += ww;
    exe += "x";
    exe += hh;
    exe += " -i desktop \"";
    exe += outputname;
    exe += "\"";

    //system(exe.c_str());//会出现控制台

    STARTUPINFO si2 = { sizeof(si2) };
    PROCESS_INFORMATION  pi2;
    si2.wShowWindow = FALSE;
    si2.dwFlags = STARTF_USESHOWWINDOW;
    char* execstr = (char*)exe.c_str();
    clockstartt = clock();
    BOOL ret2 = ::CreateProcess(NULL, (LPWSTR)execstr, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2);
    WaitForSingleObject(pi2.hProcess, INFINITE);
/*
//转换为mp4格式:
    TCHAR szCommandLine[] = ("Source/ffmpeg.exe -i Records/tmp.mpg output.mp4");

    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION  pi;
    si.wShowWindow = FALSE;
    si.dwFlags = STARTF_USESHOWWINDOW;
    BOOL ret = ::CreateProcess(NULL, szCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
*/
    return 0;
}
void MainWindow::on_action_about_triggered()
{
    char aboutbuf[1000];
    sprintf(aboutbuf, "tyzq录屏软件");

    QMessageBox message(QMessageBox::Information,"Information",

                                                     aboutbuf,QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::Yes)
       {
           qDebug()<<"clicked yes\n";
       }
       else
       {
           qDebug()<<"clicked no\n";
       }
}


void MainWindow::on_recordButton_clicked()
{
    if(isrecording == 0) {
        isrecording = 1;
        ui->recordButton->setText("结束录制");
        start_rec();
    }

}


void MainWindow::on_MainWindow_destroyed()
{
    char szCommandLine2[] = ("taskkill /im ffmpeg.exe");
    STARTUPINFO si2 = { sizeof(si2) };
    PROCESS_INFORMATION  pi2;
    si2.wShowWindow = FALSE;
    si2.dwFlags = STARTF_USESHOWWINDOW;
    BOOL ret2 = ::CreateProcess(NULL, (LPWSTR)szCommandLine2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2);
    Sleep(200);
}

