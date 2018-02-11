

#include "uart_init.h"
#include "init.h"
#include "config.h"
#include "modbus.h"


__EEPROM_DATA (1,37,128,255,255,255,255,255); 

#define _XTAL_FREQ 20000000

#define CONST_TICK_ADC  0x0A                


UART_DATA MODBUS;                           
unsigned char TickAdc;                      
BOOL Flag_Adc=0,Flag_Ch_Adc=0;
unsigned int adc_ch0,adc_ch1,adc_ch2,adc_ch3;                   



void interrupt isr (void) {
    
    if (INTCONbits.T0IF && INTCONbits.T0IE){
        if (TickAdc<=CONST_TICK_ADC){                  
            TickAdc++;
        }
        else{
            TickAdc=0;                                 
            Flag_Adc=1;
        }

        if((MODBUS.rxtimer++>MODBUS.delay)&(MODBUS.rxcnt>1))
           MODBUS.rxgap=1;
        else
           MODBUS.rxgap=0;
        
        INTCONbits.T0IF=0;                              
    }

    
    if (PIR1bits.RCIF){
        if (RCSTAbits.FERR || RCSTAbits.OERR) {         
            RCSTAbits.CREN=0;                           
            RCSTAbits.CREN=1;                           
        }
        while (PIR1bits.RCIF){

            MODBUS.rxtimer=0;                           
            if(MODBUS.rxcnt>(BUF_SZ-2)) MODBUS.rxcnt=0;
            MODBUS.buffer[MODBUS.rxcnt++]=RCREG;        
        }

        PIR1bits.RCIF=0;                                
    }
    PIR1=0;
}

unsigned int ADC_Read(unsigned char adc_ch)
{  
  ADCON0bits.CHS = adc_ch;
   
  __delay_us(50);   // Wait for mux
    
  ADCON0bits.GO_DONE = 1;      // Start conversion  
  
  while(ADCON0bits.GO_DONE) ;  // Wait until conversion success

  // Get ADC value
  return ((ADRESH << 8) + ADRESL);
}


void main(){
    pic_init();
    uart_init(9600);
    INTCONbits.T0IE=1;                                  
    INTCONbits.GIE=1;                                   
    INTCONbits.PEIE=1;                                  
    PIE1bits.RCIE=1;                                   
    PIE1bits.TXIE=0;                                    
    MODBUS.delay=3;                                  
    addr=eeprom_read(0);                                
    res_table[0].byte.LB=addr;                          
    res_table[1].byte.HB=eeprom_read(1);                
    res_table[1].byte.LB=eeprom_read(2);                

    while(1){
        CLRWDT();
        
        adc_ch0 = ADC_Read(0); 
        adc_ch1 = ADC_Read(1);
        adc_ch2 = ADC_Read(2);
        adc_ch3 = ADC_Read(3);
        
        res_table[0].Val = adc_ch0;
        res_table[1].Val = adc_ch1;
        res_table[2].Val = adc_ch2;
        res_table[3].Val = adc_ch3;
        
//        if (Flag_Adc){                                  
//            if (Flag_Ch_Adc){
//                ADCON0bits.GO_DONE=1;                   
//                while (ADCON0bits.GO_DONE) continue;
//                adc_ch1.byte.HB=ADRESH;
//                adc_ch1.byte.LB=ADRESL;                 
//                AN1_ON=0;                               
//                res_table[3].Val=adc_ch1.Val;           
//                Flag_Ch_Adc=0;
//            }
//            else{
//                ADCON0bits.GO_DONE=1;
//                while (ADCON0bits.GO_DONE) continue;
//                adc_ch0.byte.HB=ADRESH;
//                adc_ch0.byte.LB=ADRESL;                 
//                AN1_ON=1;                               
//                res_table[2].Val=adc_ch0.Val;           
//                Flag_Ch_Adc=1;
//            }
//            Flag_Adc=0;
//        }
        

        if (MODBUS.rxgap){
            MODBUS_SLAVE(&MODBUS);
            MODBUS.rxgap=0;
        }

        if (MODBUS.write){
            
            if(res_table[4].bits.b0){
                PORTBbits.RB0 = 1 ;
            }else{
                PORTBbits.RB0 = 0 ;
            }
            
//            PORTB=res_table[4].byte.LB ;          
        }
    }
}


