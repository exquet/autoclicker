#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , click(false)
{
    ui->setupUi(this);

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
    return time = (hours*3600000 + mins*60000 + secs*1000 + msecs);
}


void MainWindow::on_stopButton_clicked()
{
    click = false;
}

void MainWindow::on_timeout(){
    if(click){

    }
}

