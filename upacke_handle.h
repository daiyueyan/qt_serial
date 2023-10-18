#ifndef UPACKE_HANDLE_H
#define UPACKE_HANDLE_H

#include "upacker.h"
#include <QMainWindow>
#include <QObject>

typedef enum
{
    PC_SCREEN_NAME = 0,
    PC_SCREEN_IP,
    PC_SCREEN_OLD,
    PC_SCREEN_KV,
    PC_SCREEN_MS,
    PC_SCREEN_MAS,
}pc_screen_cmd;

class Upacke_handle:public QObject
{
public:
    Upacke_handle(Upacker* upacker);
    static void upacke_gethandle(uint8_t *, uint16_t);
    static void upacke_send(uint8_t *, uint16_t);

signals:
    static void upacke_handle_signal(uint8_t *, uint16_t);

private:
    PACKER_CB send_handle;
    PACKER_CB get_handle;
    Upacker* upacker;
};

#endif // UPACKE_HANDLE_H
