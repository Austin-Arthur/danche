#ifndef _GPIO_H
#define _GPIO_H

#include "common.h"




#define LED_ERR_PIN         P20_6
#define LED_RUN_PIN         P20_7

#define EN_PIN              P11_6

void led_init(void);
void led_output(void);

#endif
