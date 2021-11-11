/**
******************************************************************************
@brief main function of the pingpong program
@file pingpong.c
@author Ludvig Larsson
@version 1.0
@date 08-November-2021
@brief Main function of the pingpong program, calling functions defined in pingpong_functions.c
******************************************************************************
*/

#include "Pingpong.h"

/* Define states for state machine*/
typedef enum {
  WaitingForGame,
  StartRound,
  MoveRight,
  MoveLeft
} states;

static states State;

void Pingpong(void) {
  bool ButtonPressed = false; 				// To remember that button is pressed
  uint32_t CountdownValue, Speed; 			// Ball speed, Program timer
  uint8_t CurrentLed; 					// LED number
  uint8_t L_Points = 0;
  uint8_t R_Points = 0;
  uint8_t Bounces = 0;
  int8_t Turn;						// Which player that serves
  State = WaitingForGame; 				// Initiate State to Start
  Speed = 500000; 					// Number of loops

  /* Infinite loop */
  while (1) {

      switch (State) { 					// State machine

	case WaitingForGame: {
	  Speed = 500000;
	  uint32_t LedTimerValue = 400000;

	  while (1) {
	      if (LedTimerValue == 0) {
		LedTimerValue = 400000;
	      } else if (LedTimerValue < 200000) {
		led_off(1);
		led_off(8);
	      } else {
		led_on(1);
		led_on(8);
	      }
	      LedTimerValue--;

	      if(l_hit()) {
		led_off(1);
		led_off(8);
		State = StartRound;
		Turn = 1;
		break;
	      } else if (r_hit()) {
		  led_off(1);
		  led_off(8);
		  State = StartRound;
		  Turn = -1;
		  break;
	      }
	  }
	  break;
	}

	/* ############################################################################################# */

	case StartRound: {
	  Speed = 500000;
	  CountdownValue = Speed;
	  Bounces = 0;

	  if (!(L_Points == 0 && R_Points == 0))
	      show_points(L_Points, R_Points);
	  if (L_Points == 4 || R_Points == 4) {
	      show_points(L_Points, R_Points);
	      show_points(L_Points, R_Points);
	      show_points(L_Points, R_Points);
	      State = WaitingForGame;
	      L_Points = 0;
	      R_Points = 0;
	      break;
	  }

	  while(1) {
	      if (Turn == 1) {
		  CurrentLed = 1;
		  led_on(CurrentLed);
	      } else {
		  CurrentLed = 8;
		  led_on(CurrentLed);
	      }

	      if (l_hit() && Turn == 1) {					// Left serve
		  State = MoveRight;
		  while (l_hit());						// Wait for released button
		  break;
	      }

	      if (r_hit() && Turn == -1) {					// Right serve
		  State = MoveLeft;
		  while (r_hit());						// Wait for released button
		  break;
	      }
	  }

	  break;
	}

	/* ############################################################################################# */

	case MoveRight: {

	  led_off(CurrentLed - 1);
	  led_on(CurrentLed);				// Proceed one LED
	  CountdownValue = Speed;

	  while(CountdownValue != 0) {			// Delay between LED switching, note button press
	    if (r_hit())
	      ButtonPressed = true;
	    CountdownValue--;
	  }

	  if (ButtonPressed) {				// R pressed
	      if (CurrentLed == 8) {			// and LED8 active
		State = MoveLeft; 			// return ball
		CurrentLed = 7;
		Bounces++;
		if (Bounces != 0 && Bounces%2 == 0)
		  Speed = Speed * 0.75;
	      } else {
		  Turn = Turn * -1;
		  State = StartRound; 			// hit too early
		  L_Points++;
		  led_off(CurrentLed);
	      }
	  } else {
	      if (CurrentLed == 9) {			// no hit or too late
		  Turn = Turn * -1;
		  State = StartRound;
		  L_Points++;
	      }
	  }

	  if (!ButtonPressed)
	    CurrentLed++; 				// prepare to turn next LED on
	  ButtonPressed = false;
	  break;
	}

	/* ############################################################################################# */

	case MoveLeft: {
	  led_off(CurrentLed + 1);
	  led_on(CurrentLed);
	  CountdownValue = Speed;

	  while(CountdownValue != 0) {
	    if (l_hit())				// L hit
	      ButtonPressed = true;
	    CountdownValue--;
	  }

	  if (ButtonPressed) { 				// L pressed
	    if (CurrentLed == 1) { 			// and LED1 active
	      State = MoveRight; 			// return ball
	      CurrentLed = 2;
	      Bounces++;
	      if (Bounces != 0 && Bounces%2 == 0)
		Speed = Speed * 0.75;
	    } else {					// hit too early
		Turn = Turn * -1;
		State = StartRound;
		R_Points++;
		led_off(CurrentLed);
	    }
	  } else {
	      if (CurrentLed == 0) { 			// no hit or to late
		  Turn = Turn * -1;
		  State = StartRound;
		  R_Points++;
	      }
	    }
	  if (!ButtonPressed)
	    CurrentLed--; 				// prepare to turn next LED on
	  ButtonPressed = false;
	  break;
	}

	/* ############################################################################################# */

	default: {
	  break;
	}
    }
  }
}




