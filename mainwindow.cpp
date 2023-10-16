#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QDateTime>
#include <QDebug>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mtimer = new QTimer(this);
    mtimer->start(1000);

    //获取系统上有哪些串口
    QList<QSerialPortInfo> serialport = QSerialPortInfo::availablePorts();
    //把系统上存在的串口给port供选择
    for (int i=0; i<serialport.count(); i++)
    {
        ui->cboxport->addItem(serialport.at(i).portName());
    }
    ui->btn_send->setEnabled(false);
    //串口接收到数据都会发出readyRead()的信号连接这个信号即可读取串口数据
    connect(&mSerialPort, SIGNAL(readyRead()), this, SLOT(getrev()));

    connect(mtimer, SIGNAL(timeout()), this, SLOT(timerupdata()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getrev()
{
    if("关闭" == ui->btn_open->text())
    {
        QByteArray arr = mSerialPort.readAll();
        if (ui->checkBox_16bin->isChecked())
        {
            QString hex_data = arr.toHex().data(); // 将读取出来的buf里的数据转换为16进制
            hex_data = hex_data.toUpper(); // 转换为大写
            QString hex_str;
            // 将16进制转换为大写
            for (int i=0; i< hex_data.length(); i+=2)
            {
                QString st = hex_data.mid(i,2);
                hex_str+=st;
                hex_str+=' ';
            }
            ui->text_rev->append(hex_str);
        }
        else
        {
            //需要转换成字符串而且中文不会乱码
            ui->text_rev->append(QString::fromLocal8Bit(arr));
        }
    }
}

void MainWindow::timerupdata()
{
    QDateTime realtime = QDateTime::currentDateTime();
    QString str = realtime.toString("yyyy/MM/dd hh:mm:ss dddd");
    ui->time_show->setText(str);
}

void MainWindow::on_btn_rev_clean_clicked()
{
    ui->text_rev->clear();
}

void MainWindow::on_btn_open_clicked()
{
    //当前处于打开的状态
    if("关闭" == ui->btn_open->text())
    {
        ui->btn_open->setText("打开");
        ui->btn_send->setEnabled(false);
        ui->cboxport->setEnabled(true);
        ui->cboxbaund->setEnabled(true);
        ui->cboxstop->setEnabled(true);
        ui->cboxdata->setEnabled(true);
        ui->cboxparity->setEnabled(true);
        mSerialPort.close();
        qDebug()<<"关闭串口"<<serialportname;

    }
    else//当前处于关闭的状态
    {
        if(true == serialconfig())//如果打开成功
        {
            ui->btn_open->setText("关闭");
            ui->btn_send->setEnabled(true);
            ui->cboxport->setEnabled(false);
            ui->cboxbaund->setEnabled(false);
            ui->cboxstop->setEnabled(false);
            ui->cboxdata->setEnabled(false);
            ui->cboxparity->setEnabled(false);
            qDebug()<<"成功打开串口"<<serialportname;
        }
    }
}

void MainWindow::on_btn_send_clicked()
{
    QString str = "\r\n"; //将\n替换为\r\n
    QString text = ui->text_send->toPlainText(); //当前输入框中的数据
    if(text.indexOf("\n") != -1) //如果有\n
    {
        text.replace("\n","\r\n"); //将每个\n都替换为\r\n
    }
    //需要转换成特定的字符串在转换为字符toLocal8Bit
    //发送中文不会乱码
    mSerialPort.write(text.toLocal8Bit());
}

void MainWindow::on_btn_clean_clicked()
{
    ui->text_send->clear();
}

bool MainWindow::serialconfig()
{
    serialportname = ui->cboxport->currentText();
    serialbaund = ui->cboxbaund->currentText();
    serialstopbit = ui->cboxstop->currentText();
    serialdatabit = ui->cboxdata->currentText();
    serialparity = ui->cboxparity->currentText();

    mSerialPort.setPortName(serialportname);
    //由于使用的是枚举，不能向上面一样长换入字符串
    if("9600" == serialbaund)
    {
        mSerialPort.setBaudRate(QSerialPort::Baud9600);
    }
    else if("19200" == serialbaund)
    {
        mSerialPort.setBaudRate(QSerialPort::Baud19200);
    }
    else
    {
        mSerialPort.setBaudRate(QSerialPort::Baud115200);
    }

    if("1.5" == serialstopbit)
    {
        mSerialPort.setStopBits(QSerialPort::OneAndHalfStop);
    }
    else if("2" == serialstopbit)
    {
        mSerialPort.setStopBits(QSerialPort::TwoStop);
    }
    else
    {
        mSerialPort.setStopBits(QSerialPort::OneStop);
    }

    if("偶校验" == serialparity)
    {
        mSerialPort.setParity(QSerialPort::EvenParity);
    }
    else if("奇校验" == serialparity)
    {
        mSerialPort.setParity(QSerialPort::OddParity);
    }
    else
    {
        mSerialPort.setParity(QSerialPort::NoParity);
    }

    if("5" == serialdatabit)
    {
        mSerialPort.setDataBits(QSerialPort::Data5);
    }
    else if("6" == serialdatabit)
    {
        mSerialPort.setDataBits(QSerialPort::Data6);
    }
    else if("7" == serialdatabit)
    {
        mSerialPort.setDataBits(QSerialPort::Data7);
    }
    else
    {
        mSerialPort.setDataBits(QSerialPort::Data8);
    }
    //以读写的方式打开串口并且返回结果是否打开成功
    return mSerialPort.open(QIODevice::ReadWrite);
}
