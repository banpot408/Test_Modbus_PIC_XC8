/*
 * Подпрограмма настройки УАРТа МК
 * На вход получаем скорость в БОДах
 */

#include "uart_init.h"

void uart_init(unsigned int baud){

    TRISCbits.TRISC7=1;
    TRISCbits.TRISC6=0;
    PORTCbits.RC6=1;

    WORD_VAL bRate;
    bRate.Val=(unsigned int) BAUD_CALC(baud);           /*Производим расчет регистров*/
    
    TXSTA=0b00100100;                                   /*Асинхронный режим, высокоскоростной*/
    RCSTA=0b10010000;                                   /*Включить УАРТ*/
    BAUDCTL=0b00001000;                                 /*16-битный генератор скорости*/

    SPBRGH=bRate.byte.HB;                               /*Устанавливаем скорость*/
    SPBRG=bRate.byte.LB;


}
