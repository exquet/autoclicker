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

    RegisterHotKey(reinterpret_cast<HWND>(winId()), 1, 0, VK_F10); // регистрация глобальной горячей клавиши с id = 1
}

MainWindow::~MainWindow()
{
    UnregisterHotKey(reinterpret_cast<HWND>(winId()), 1); // отмена регистрации глобальной горячей клавиши с id = 1
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer->setInterval(timeScale());
    click = true;
}

long MainWindow::timeScale(){
    hours = ui->hoursSpinBox->value();
    mins = ui->minsSpinBox->value();
    secs = ui->secsSpinBox->value();
    msecs = ui->msecsSpinBox->value();

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

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result) // WinAPI
{
    // проверяем, что полученное событие – Windows-сообщение
    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG*>(message);
        // если сообщение WM_HOTKEY
        if (msg->message == WM_HOTKEY) {
            // если идентификатор горячей клавиши равен 1
            if (msg->wParam == 1) {
                toggleClicker();
                return true;
            }
        }
    }

    return QMainWindow::nativeEvent(eventType, message, result);
}

void MainWindow::toggleClicker(){
    timer->setInterval(timeScale());
    click = !click;
}

