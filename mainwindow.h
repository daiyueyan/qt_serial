#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>
#include "upacke_handle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Upacke_handle *upacke_handle;
    Upacker *upacker;

private slots:
    void on_btn_rev_clean_clicked();

    void on_btn_open_clicked();

    void on_btn_send_clicked();

    void on_btn_clean_clicked();

    //配置串口
    bool serialconfig();
    //自定义接收函数
    void getrev();

    void timerupdata();

    void pc_send_serial(uint8_t *buf, uint16_t len);

private:
    Ui::MainWindow *ui;
    QSerialPort mSerialPort;
    QString serialportname;
    QString serialbaund;
    QString serialstopbit;
    QString serialparity;
    QString serialdatabit;

    QTimer* mtimer;

};
#endif // MAINWINDOW_H
