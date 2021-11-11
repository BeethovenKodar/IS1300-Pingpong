
#ifndef INC_PINGPONG_H_
  #define INC_PINGPONG_H_
#endif

#include "stdint.h"
#include "stdbool.h"
#include "gpio.h"

void Pingpong(void);

void led_on(uint8_t lednr);

void led_off(uint8_t led_nr);

void show_points(uint8_t l_points, uint8_t r_points);

bool valid_lednr(uint8_t led_nr);

bool l_hit(void);

bool r_hit(void);

//void wait_for_start(void);
