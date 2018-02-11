/*
 * Функция инициализации УАРТа МК
 */

#ifndef UART_INIT_H
#define	UART_INIT_H

#include <xc.h>
#include "type_def.h"

/*Определяем констаты*/

#define FOSC_UART        20000000L
//#define BAUDRATE    9600L
//#define SPBRG_CONST    ((FOSC + BAUDRATE*2) / (BAUDRATE*4) - 1) /*Вычисление скорости УАРТ по умолчанию*/
#define BAUD_CALC(x)    ((FOSC_UART + x*2) / (x*4) - 1)              /*Вычисление скорости по входным переменным*/

void uart_init(unsigned int bRate);

#endif	/* UART_INIT_H */

