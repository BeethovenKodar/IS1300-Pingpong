/**
******************************************************************************
@brief Functions for the Pingpong-program
@file pingpong_functions.c
@author Ludvig Larsson
@version 1.0
@date 08-November-2021
******************************************************************************
*/

#include "Pingpong.h"

/* Define ports and pins in lists */
GPIO_TypeDef* ports[] = {LED1_GPIO_Port, LED2_GPIO_Port, LED3_GPIO_Port, LED4_GPIO_Port,
    LED5_GPIO_Port, LED6_GPIO_Port, LED7_GPIO_Port, LED8_GPIO_Port};
uint16_t pins[] = {LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin, LED5_Pin, LED6_Pin,
    LED7_Pin, LED8_Pin};

/**
@brief show_points, shows points for 1 second after missed ball
@param1 uint8_t l_points points for left player
@param2 uint8_t r_points points for right player
*/
void show_points(uint8_t l_points, uint8_t r_points) {
  uint8_t i;
  for (i = 1; i <= l_points; i++) {
      led_on(i);
  }
  for (i = 1; i <= r_points; i++) {
      led_on(9-i);
  }
  HAL_Delay(1000);
  for (i = 1; i < 9; i++) {
      led_off(i);
  }
}

/**
@brief led_on2, enables one LED
@param1 uint8_t led_nr the LED to enable, can be 1..8
*/
void led_on(uint8_t led_nr) {
  if (valid_lednr(led_nr))
    HAL_GPIO_WritePin(ports[led_nr - 1], pins[led_nr - 1], GPIO_PIN_SET);
}

/**
@brief led_off, enables one led light
@param1 uint8_t led_nr the LED to enable, can be 1..8
*/
void led_off(uint8_t led_nr) {
  if (valid_lednr(led_nr))
    HAL_GPIO_WritePin(ports[led_nr - 1], pins[led_nr - 1],  GPIO_PIN_RESET);
}

/**
@breif reads the left button on the board
@return true if the button is pressed, else false
*/
bool l_hit(void) {
  if (HAL_GPIO_ReadPin(L_Button_GPIO_Port, L_Button_Pin) == 0)
    return true;
  else
    return false;
}

/**
@breif reads the right button on the board
@return true if the button is pressed, else false
*/
bool r_hit(void) {
  if (HAL_GPIO_ReadPin(R_Button_GPIO_Port, R_Button_Pin) == 0)
    return true;
  else
    return false;
}

/**
@brief valid_lednr
@param1 uint8_t led_nr the LED to enable, can be 1-8
@return boolean value if it is a valid pin or not
*/
bool valid_lednr(uint8_t led_nr) {
  if (led_nr < 1 || led_nr > 8)
      return false;
  else
    return true;
}


