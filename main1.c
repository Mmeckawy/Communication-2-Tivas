#include <stdint.h>
#include "stdbool.h"
#include <driverlib/systick.h>
#include <driverlib/gpio.h>
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "tm4c123gh6pm.h"


void main()
{
  SYSCTL_RCGCUART_R |= 0X02;
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  while(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)==0){}
  UART1_CTL_R &=~ 0x01;
  UART1_IBRD_R = 104
  UART1_FBRD_R = 11;
  UART1_LCRH_R |= 0x70;
  UART1_CTL_R |= 0x301;
  GPIO_PORTB_AFSEL_R |= 0x02;
  GPIO_PORTB_DEN_R |= 0x02; 
  GPIO_PORTB_PCTL_R = 0x10;
  GPIO_PORTB_AMSEL_R = 0x0; 
  
  SYSCTL_RCGCUART_R |= 0X20;
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  while(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)==0){}
  UART5_CTL_R &=~ 0x01;
  UART5_IBRD_R = 520;
  UART5_FBRD_R = 53;
  UART5_LCRH_R |= 0x70;
  UART5_CTL_R |= 0x301;
  GPIO_PORTE_AFSEL_R |= 0x10;
  GPIO_PORTE_DEN_R |= 0x10; 
  GPIO_PORTE_PCTL_R = 0x10000; //Configure PE4 for UART
  GPIO_PORTE_AMSEL_R = 0x0;
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)==0){}
  GPIO_PORTF_CR_R |= 0X16;
  GPIO_PORTF_DIR_R = 0x06;
  GPIO_PORTF_PUR_R = 0x10;
  GPIO_PORTF_DEN_R = 0x16;
   while(1)
   {
     unsigned long SW1, data;
     SW1 = GPIO_PORTF_DATA_R & 0x10;
     if (SW1 == 0x10)
     {
       data = 0x0;
       GPIO_PORTF_DATA_R &= ~0x02;
     }
     if (SW1 == 0x00)
     {
       data = 0x1;
     }
     while((UART1_FR_R & 0x20) != 0);
     UART1_DR_R = data;
     
     while ((UART5_FR_R & 0x10) != 0);
    if ((UART5_DR_R & 0XFF)==0X1)
      GPIO_PORTF_DATA_R = 0X04;
    else if ((UART5_DR_R & 0XFF) == 0X0)
      GPIO_PORTF_DATA_R &=~ 0X04;
   }
   
}