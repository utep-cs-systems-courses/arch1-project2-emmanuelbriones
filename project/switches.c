#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

char switch_state_down, switch_state_changed; /* effectively boolean */

static char 
switch_update_interrupt_sense()
{
  char p1val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();
  if (p1val & SW1 && p1val & SW2 && p1val & SW3 && p1val & SW4) {
    buzzer_set_period(0);
    switch_state_down = 0;
  }
  else if (!(SW1 & p1val)) {
    star_wars();
    switch_state_down = 1;
   
  }

  else if (!(SW2 & p1val)) {
    buzzer_set_period(473);
    switch_state_down = 1;
  }

  else if (!(SW3 & p1val)) {
    buzzer_set_period(723);
    switch_state_down = 1;
  }

  else if (!(SW4 & p1val)) {
    mario();
    switch_state_down = 1;
  }
  
  //next_state();
  switch_state_changed = 1;
  led_update();
}
