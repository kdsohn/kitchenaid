/*
 * File:   kaffee.c
 * Author: Sohn2
 *
 * Created on 27. Oktober 2019, 11:48
 */

#define F_CPU 9600000 / 8

#include <xc.h>
#include <util\delay.h>

void IO_INIT(void) {
#ifdef later    
  __watchdog_reset();
  /* Write logical one to WDCE and WDE */
  /* Keep old prescaler setting to prevent unintentional time-out */

  WDTCR |= (1<<WDCE) | (1<<WDE);
  /* Turn off WDT */
  WDTCR = 0x0F;    // 2 Sekunden
#endif
  DDRB = 1;
  PORTB |= 4;  // Pullup Pin 2
  TCCR0A = 0x80 + 1; // phase correct PWM, clear on match upcounting, set on match downcounting
  TCCR0B = 3; // ./. 64
  
}

#define PWM_OFF  7 // 2/1000*(9600000/8/64/2) war 9
#define PWM_ON  19 // 2/1000*(9600000/8/64/2)

int main(void) {
  IO_INIT();
 
  OCR0A = PWM_OFF;
  _delay_ms(5000);
  for (;;) {
    if (OCR0A < PWM_ON) {
      OCR0A++;
    }
    _delay_ms(50);
  }  
}
