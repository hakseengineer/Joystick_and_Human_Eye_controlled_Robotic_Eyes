#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <ezButton.h>
#include <stdint.h>
#include <Arduino.h>

#define VRX_PIN  A0 // Arduino Nano pin connected to VRX pin
#define VRY_PIN  A1 // Arduino Nano pin connected to VRY pin
#define SW_PIN   12  // Arduino Nano pin connected to SW pin

#define MIN_THRESHOLD 10

ezButton button(SW_PIN);
uint8_t joystick_input(void);

typedef enum {
  J_center,
  J_blink,
  J_right,
  J_left,
  J_up,
  J_down
}jostick_pos;

int value_X = 0; // The variable to store value of the X axis
int value_Y = 0; // The variable to store value of the Y axis
int bValue = 0; // The variable to store value of the button

#endif
