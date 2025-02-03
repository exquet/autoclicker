#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QSpinBox>
#include <QTimer>
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

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
    // получаем уведомления о срабатывании глобальной горячей клавиши

private:
    Ui::MainWindow *ui;
    int hours;
    int mins;
    int secs;
    int msecs;
    long time;
    long timeScale();
    bool click;
    QTimer *timer;

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_timeout();
    void toggleClicker();
};
#endif // MAINWINDOW_H
