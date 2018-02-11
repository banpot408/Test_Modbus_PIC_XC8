/*
 * Заголовочный файл для определения констат
 * и определения финкции инициализации МК
 */


#ifndef INIT_H
#define	INIT_H

#define     TX_TRIS     TRISCbits.TRISC6        /*Определим констаты для инициализации МК*/
#define     RX_TRIS     TRISCbits.TRISC7        /*Настройка пинов УАРТа*/
#define     TX_TRANS    TRISCbits.TRISC5        /*Переключение драйвера RS-485 на передачу*/
#define     TX_ENABLE   PORTCbits.RC5           /*Вкл/Откл передачи*/

#define     AN0_TRIS    TRISAbits.TRISA0        /*Настройка пинов аналоговых входов*/
#define     AN1_TRIS    TRISAbits.TRISA1
#define     AN2_TRIS    TRISAbits.TRISA2
#define     AN3_TRIS    TRISAbits.TRISA3
#define     AN1_ON      ADCON0bits.CHS0         /*Определим выбор канала подключенного к АЦП*/
                                                /*AN1_ON=1 - выбран канал AN1, AN1_ON=0 - выбран канал AN0*/

void pic_init(void);

#endif	/* INIT_H */

