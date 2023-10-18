#include "upacke_handle.h"
#include "mainwindow.h"
#include <binders.h>
#include <QDebug>

Upacke_handle::Upacke_handle(Upacker* upacker)
{
    //需要设置upacke_gethandle和upacke_send为静态函数才可以
    upacker->upacker_init(upacke_gethandle, upacke_send);
}

void Upacke_handle::upacke_gethandle(uint8_t *buf, uint16_t len)
{
    uint8_t cmd = buf[0];
    uint16_t size = len;

    for(int i=0; i<size; i++)
    {
        qDebug() << buf[i];
    }
    qDebug() << endl;

    switch (cmd)
    {
    case PC_SCREEN_NAME:
        qDebug() << "NAME" << endl;
    break;

    case PC_SCREEN_IP:
        qDebug() << "IP" << endl;
    break;

    case PC_SCREEN_OLD:
        qDebug() << "old" << endl;
    break;

    case PC_SCREEN_KV:
        qDebug() << "kv" << endl;
    break;

    case PC_SCREEN_MS:
        qDebug() << "ms" << endl;
    break;

    case PC_SCREEN_MAS:
        qDebug() << "mas" << endl;
    break;

    default:
    break;

    };
}

void Upacke_handle::upacke_send(uint8_t *buf, uint16_t len)
{
    emit upacke_handle_signal(buf, len);
}

void Upacke_handle::upacke_handle_signal(uint8_t * buf, uint16_t len)
{

}



