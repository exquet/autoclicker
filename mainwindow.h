#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QSpinBox>
#include <QTimer>
#include <QMouseEvent>
#include <QCursor>
#include <Windows.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int hours;
    int mins;
    int secs;
    int msecs;
    long time;
    long timeScale();
    bool click;

private slots:
    void on_startButton_clicked();
};
#endif // MAINWINDOW_H
