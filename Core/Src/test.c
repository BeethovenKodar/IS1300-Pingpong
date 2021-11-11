/**
******************************************************************************
@brief Test functions for the Pingpong-program
@file test.c
@author Ludvig Larsson
@version 1.0
@date 09-November-2021
@brief Test functions for the pingpong program.
******************************************************************************
*/

#include "Test.h"

/**
@brief main function for calling the various tests
*/
void Test_program(void) {
  test_led();
  test_score();
  test_buttons();
}

/**
@brief test the LED's one at a time
and make sure that only valid leds can be targeted (valid_led)
*/
void test_led(void) {
  int8_t lednr;
  /* Loop checking that all leds can be turned on,  */
  for (lednr = 0; lednr <= 9; lednr++) {
      led_on(lednr);
      HAL_Delay(500);
      led_off(lednr);
  }
  HAL_Delay(1000);
}

/**
@breif test that each score can be displayed
with show_points
*/
void test_score(void) {
  /* iterate through all possible combinations of left and right score */
  uint8_t left_score, right_score;
  for (left_score = 0; left_score < 5; left_score++) {
      for (right_score = 0; right_score < 5; right_score++) {
	  if (left_score + right_score < 8 && left_score + right_score != 0) {
	    show_points(left_score, right_score);
	    HAL_Delay(500);
	  }
      }
  }
}

/**
@breif test that the buttons used can direct the ball
correctly
*/
void test_buttons(void)
{
  uint8_t j = 4;
  led_on(j);				// An arbitrary LED initially lit

  while (j < 9 && j > 0) {
    if (l_hit() == true) { 		// Wait for left button hit
	led_off(j++); 			// next led to the right
	led_on(j);
	HAL_Delay(100);
	while (l_hit() == true); 	// Wait for button release
	HAL_Delay(100);
    }

    if (r_hit() == true) { 		// Wait for right button hit
	led_off(j--); 			// next led to the left
	led_on(j); // Light on
	HAL_Delay(100);
	while (r_hit() == true); 	// Wait for button release
	HAL_Delay(100);
    }
  }
}




