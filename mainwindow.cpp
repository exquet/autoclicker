#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , click(false)
    , hours(0)
    , mins(0)
    , secs(1)
    , msecs(0)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    timer->setInterval(timeScale());
    connect(timer, &QTimer::timeout, this, &MainWindow::on_timeout);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    click = true;
}

long MainWindow::timeScale(){
    time = (hours*3600000 + mins*60000 + secs*1000 + msecs);
    return time;
}


void MainWindow::on_stopButton_clicked()
{
    click = false;
}

void MainWindow::on_timeout(){
    INPUT inputEvents[2] = {0}; // подготавливаем массив из двух структур INPUT для эмуляции клика

    if(click){
        if(ui->leftRadioButton->isChecked()){
            inputEvents[0].type = INPUT_MOUSE; // type - mouse
            inputEvents[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // click
            inputEvents[1].type = INPUT_MOUSE; // type - mouse
            inputEvents[1].mi.dwFlags = MOUSEEVENTF_LEFTUP; // up click
            SendInput(2, inputEvents, sizeof(INPUT)); // send windows event
        }

        else if (ui->rightRadioButton->isChecked()){
            inputEvents[0].type = INPUT_MOUSE;
            inputEvents[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            inputEvents[1].type = INPUT_MOUSE;
            inputEvents[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            SendInput(2, inputEvents, sizeof(INPUT));
        }
    }
}

