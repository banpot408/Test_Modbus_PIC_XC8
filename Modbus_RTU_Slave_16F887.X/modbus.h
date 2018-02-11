/*
 * Заголовочный файл протокола ModBus RTU
 */


#ifndef MODBUS_H
#define	MODBUS_H

#include "type_def.h"

/*Формируем буфер для УАРТа*/

#define BUF_SZ 50                       /*Количество байт данных фрейма Modbus*/
#define MODBUS_WRD_SZ (BUF_SZ-5)/2      /*Количество регистров в посылке*/
#define MODBUS_ADDR 1                   /*Сетевой адрес modbus устройства*/
#define OBJ_SZ 20                       /*Общее количество регистров*/

WORD_VAL res_table[OBJ_SZ];             /*Таблица регистров модбас, с которых происходит чтение значений пареметров*/
                                        /*установленных пользователем*/
                                        /*[0] - модбас адрес устройства, можно применить для конфигурирования по сети*/
                                        /*[1] - скорость передачи УАРТ, можно конфигурировать по сети*/
                                        /*[2] - значение кода АЦП канала 0*/
                                        /*[3] - значение кода АЦП канала 1*/
                                        /*[4] - команда от мастера для управления уровенями на порту Б, используется младший байт*/
                                        /*Так составляется карта регистров модбас устройства*/

/*УАРТ структура Modbus*/

typedef struct {
unsigned char buffer[BUF_SZ];
unsigned char rxtimer;
unsigned char rxcnt;
unsigned char txcnt;
unsigned char txlen;
unsigned char rxgap;
unsigned char delay;
unsigned char write;
} UART_DATA;

unsigned char addr;


void MODBUS_SLAVE(UART_DATA *MODBUS);
unsigned int CRC16(unsigned char *ptrByte, int byte_cnt);
void TX_03(UART_DATA *MODBUS);
void TX_16(UART_DATA *MODBUS);
void TX_ERROR(UART_DATA *MODBUS,unsigned char error_type);
void TX_FRAME(UART_DATA *MODBUS);

#endif	/* MODBUS_H */



