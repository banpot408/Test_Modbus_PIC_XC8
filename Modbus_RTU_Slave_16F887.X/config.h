/*
 *Заголовочный файл для конфигурации МК
 */


#ifndef CONFIG_H
#define	CONFIG_H

/*Конфигурируем фьюзы МК*/

#pragma config FOSC  = HS       //Используем кварцевой резонатор
#pragma config MCLRE = ON       //Активируем ножку сброса МК
#pragma config WDTE = ON        //Включаем сторожевой таймер

#endif	/* CONFIG_H */

