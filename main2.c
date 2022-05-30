#include <stdint.h>
#include "stdbool.h"
#include <driverlib/systick.h>
#include <driverlib/gpio.h>
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "tm4c123gh6pm.h"

void main()
{
  //Initializing UART1
  SYSCTL_RCGCUART_R |= 0X02;
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  while(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)==0){}
  UART1_CTL_R &=~ 0x01; //Disable control register
  UART1_IBRD_R = 104; //Baud rate
  UART1_FBRD_R = 11;  //Fractional portion of baud rate
  UART1_LCRH_R |= 0x70; //line control register
  UART1_CTL_R |= 0x301; //Enable UART pins
  GPIO_PORTB_AFSEL_R |= 0x01; //Aletranating function for analog mode
  GPIO_PORTB_DEN_R |= 0x01;  //Enable digital I/O
  GPIO_PORTB_PCTL_R = 0x01;  //Configure PB0 for UART
  GPIO_PORTB_AMSEL_R = 0x0; // disable analog functionality on Port B
  
  //Initializing UART5
  SYSCTL_RCGCUART_R |= 0X20;
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  while(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)==0){}
  UART5_CTL_R &=~ 0x01;
  UART5_IBRD_R = 520;
  UART5_FBRD_R = 53;  
  UART5_LCRH_R |= 0x70; 
  UART5_CTL_R |= 0x301; 
  GPIO_PORTE_AFSEL_R |= 0x20;
  GPIO_PORTE_DEN_R |= 0x20;  
  GPIO_PORTE_PCTL_R = 0x100000; //Configure PE5 for UART
  GPIO_PORTE_AMSEL_R = 0x0;
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)==0){}
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  GPIO_PORTF_CR_R |= 0X07; 
  GPIO_PORTF_DIR_R = 0x06;
  GPIO_PORTF_PUR_R = 0x01;
  GPIO_PORTF_DEN_R = 0x07;

  while (1)
  { 
    unsigned long SW2, data;
     SW2 = GPIO_PORTF_DATA_R & 0x01;
     if (SW2 == 0x01)
     {
       data = 0x0;
       GPIO_PORTF_DATA_R &= ~0x04;
     }
     if (SW2 == 0x00)
     {
       data = 0x1;
     }
     while((UART5_FR_R & 0x20) != 0);
     UART5_DR_R = data;
     
     while ((UART1_FR_R & 0x10) != 0);
    if ((UART1_DR_R & 0XFF)==0X1)
      GPIO_PORTF_DATA_R = 0X02;
    else if ((UART1_DR_R & 0XFF) == 0X0)
      GPIO_PORTF_DATA_R &=~ 0X02;
  }
}
