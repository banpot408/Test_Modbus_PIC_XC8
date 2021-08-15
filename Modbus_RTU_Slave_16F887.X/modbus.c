

#include <xc.h>
#include "modbus.h"



void MODBUS_SLAVE(UART_DATA *MODBUS){
    unsigned int tmp;

    /*если обращаются к нам или широковещательныйм адресом, и в буфере больше 5 байт*/

    if(((MODBUS->buffer[0]==addr)|(MODBUS->buffer[0]==255)) & (MODBUS->rxcnt>5)){
        tmp=CRC16(MODBUS->buffer,MODBUS->rxcnt-2);              /*проверяем контрольную сумму*/
    /*если контрольная сумма совпала, обрабатываем сообщение*/

    if((MODBUS->buffer[MODBUS->rxcnt-2]==(tmp&0x00FF)) & (MODBUS->buffer[MODBUS->rxcnt-1]==(tmp>>8))) {
        switch(MODBUS->buffer[1]){
            case 3:                                             /*Обработка команды чтения*/
                TX_03(MODBUS);
                break;
            case 16:                                            /*Обработка команды запись*/
                TX_16(MODBUS);
                break;
            default :                                           /*Если пришла команда не поддерживаемая, отвечаем ошибкой*/
                TX_ERROR(MODBUS,0x01);
                break;
        }
        /*добавляем контрольную сумму*/

         tmp=CRC16(MODBUS->buffer,MODBUS->txlen-2);
         MODBUS->buffer[MODBUS->txlen-2]=tmp;
         MODBUS->buffer[MODBUS->txlen-1]=tmp>>8;
         MODBUS->txcnt=0;

	}
     }
    /*отправляем ответ*/

        TX_FRAME(MODBUS);
	MODBUS->rxgap=0;
	MODBUS->rxcnt=0;
	MODBUS->rxtimer=0x00;
}


void TX_03(UART_DATA *MODBUS)
{
unsigned int tmp,tmp1;
unsigned int m=0,n=0;

   tmp=((MODBUS->buffer[2]<<8)+MODBUS->buffer[3]);

   tmp1=((MODBUS->buffer[4]<<8)+MODBUS->buffer[5]);

   n=3;
/*если не в наше адресное пространство, отвечаем ошибкой*/

  if((((tmp+tmp1)<OBJ_SZ)&(tmp1<MODBUS_WRD_SZ+1)))
   {

    for(m=0;m<tmp1;m++)
    {
     MODBUS->buffer[n]=res_table[m+tmp].byte.HB;
     MODBUS->buffer[n+1]=res_table[m+tmp].byte.LB;
     n+=2;
    }

     MODBUS->buffer[2]=m*2;                                         /*byte count*/
     MODBUS->txlen=m*2+5;                                           /*responce length*/

   }
  else
  {
   /*область памяти не поддерживается*/

   TX_ERROR(MODBUS,0x02);
  }
}

void TX_16(UART_DATA *MODBUS)
{
    unsigned int tmp;
    unsigned char count,j;

   tmp=((MODBUS->buffer[2]<<8)+MODBUS->buffer[3]);                          /*adress*/
   count=MODBUS->buffer[6];
   /*если в нашем адресном пространстве*/

   if((tmp+count)<OBJ_SZ) {
       j=7;
       for (unsigned int i=tmp; i<tmp+(count>1);i++){
            res_table[i].Val=(MODBUS->buffer[j]<<8)+MODBUS->buffer[j+1];
            j+=2;
        }
       MODBUS->txlen=8;
       MODBUS->write=1;
    }
   else
   {
    /*область памяти не поддерживается*/
    TX_ERROR(MODBUS,0x02) ;
   }
}

void TX_FRAME(UART_DATA *MODBUS)
{
      RCSTAbits.CREN=0;
      TXSTAbits.TXEN=1;
      INTCONbits.GIE=0;                                             /* время передачи отключим прерывания*/
      while(MODBUS->txcnt<MODBUS->txlen){
         TXREG=MODBUS->buffer[MODBUS->txcnt++];
         while(!PIR1bits.TXIF) NOP();
      }
      INTCONbits.GIE=1;
      MODBUS->txlen=0;
      RCSTAbits.CREN=1;
}


void TX_ERROR(UART_DATA *MODBUS,unsigned char error_type)
{
 /*Отправляем ошибку*/

    MODBUS->buffer[1]|=0b10000000;
    MODBUS->buffer[2]=error_type;                                       /*код ошибки*/
    MODBUS->txlen=5;                                                    /*длина сообщения*/
}


unsigned int CRC16(unsigned char *ptrByte, int byte_cnt){
unsigned int w=0;
char shift_cnt;

 if(ptrByte)
 {
   w=0xffffU;
   for(; byte_cnt>0; byte_cnt--)
   {
    w=(unsigned int)((w/256U)*256U+((w%256U)^(*ptrByte++)));
    for(shift_cnt=0; shift_cnt<8; shift_cnt++)
    {
     if((w&0x1)==1)
     w=(unsigned int)((w>>1)^0xa001U);
     else
     w>>=1;
    }
   }
 }
return w;
}

