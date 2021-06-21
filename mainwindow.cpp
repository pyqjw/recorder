#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPalette>
void MainWindow::init() {
    ui->FRATE->setText(QString("50"));
    ui->LeftTopX->setText(QString("0"));
    ui->LeftTopY->setText(QString("0"));
    ui->RightBottomX->setText(QString("1920"));
    ui->RightBottomY->setText(QString("1080"));

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
//	Sleep(250);
    char tmpfnbuf[MAX_PATH*4];
    //GetDlgItemText(hwnd, IDC_IPATH, tmpfnbuf, MAX_PATH*4);
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
    char ww[10];
    sprintf(ww, "%d", w);

    char hh[10];
    sprintf(hh, "%d", h);

    char xx[10];
    sprintf(xx, "%d", 0);

    char yy[10];
    sprintf(yy, "%d", 0);

    char frate[10];
    sprintf(yy, "%d", 50);

//	GetDlgItemText(hwnd, IDC_FRATE, frate, 10);
//	GetDlgItemText(hwnd, IDC_LUX, xx, 10);
//	GetDlgItemText(hwnd, IDC_LUY, yy, 10);
//	GetDlgItemText(hwnd, IDC_RDX, ww, 10);
//	GetDlgItemText(hwnd, IDC_RDY, hh, 10);

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
    sprintf(aboutbuf, "tyzq录屏软件（软工大作业），一个录屏软件，由C++编写。\n版本：1.0.0.0 语言：汉语（中国）\n"
"作者（排名不分先后，均为第一作者）：齐敬文、张泽坤、闫秀泽、汤云灿。如有任何意见或建议，请联系作者邮箱: tyc18265475128@163.com。"
"\n\n约束条件: 路径中不可带有空格，尽量不要有中文，否则可能无法录制。输入框是为您填入保存位置用的，若留空，则默认保存至Records文件夹，"
"以开始拍摄的时间命名。您也可以通过“选择保存路径”来选择位置。具体保存位置由开始拍摄前指定的为准。拍摄一开始，就会转最小化，您可以从任务栏"
"唤醒本软件来结束录制。由于制作者能力有限，仅支持mpg与avi两种格式。您可以通过EFChange来转换为您想要的格式。若您是通过强制方式关闭的本进"
"程，请务必运行本文件夹下的clean.bat批处理文件来清理进程，否则可能导致内存大量消耗！\n 更多功能敬请期待tyzq录屏软件（软工大作业）版本2"
".0.0.0！！！！");

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
    start_rec();
}

