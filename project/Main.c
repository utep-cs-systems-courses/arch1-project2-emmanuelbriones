#include <msp430.h>
//#include "libTimer.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

void main() {
  configureClocks();
  switch_init();
  buzzer_init();
  led_init();

  or_sr(0x18);
}
