#include <MD_MAX72xx.h>
#include <SPI.h>
#include "RobotEye.h"
#include "Joystick.h"


// MD_MAX72xx hardware definitions and object
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW   // Check your deisplay type
#define MAX_DEVICES 4                       // no. of segment in display
#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);                      // SPI hardware interface


/* TO Switch Between Jostick and EYE Control mode, remove comment to enable the mode, both can also work together. */
#define JOYSTICK
//#define EYE_CONTROLLED


#define EYES_DELAY 2500
uint32_t prevTimeAnim = 0;    // Used for remembering the millis() value in animations
uint8_t state=0;
uint8_t prev_state=0;
boolean t_wait=false;


void setup()
{
  mx.begin();
  prevTimeAnim = millis();
  Serial.begin(115200);
  button.setDebounceTime(50); // set debounce time to 50 milliseconds for Joystick
  resetMatrix();
}

void loop()
{
  
  state= get_state();
  //Serial.print(state);  /* Enable to debug */
  runMatrixAnimation(state);
}

uint8_t get_state()
{
  #ifdef JOYSTICK   // To get data from Joystick
    state = joystick_input();    
  #endif

  #ifdef EYE_CONTROLLED  // To controll using Eyes
    if(Serial.available())
    {
      state = Serial.read()-48; // Subtract 48 to convert ASCII to integer
    }
  #endif

/* Below logic will hold robotic eyes to a fix state, like left, right, etc. */
  if(state == prev_state)
  {
    t_wait = true; //wait until state changes
  }
  else
  {
    prev_state = state;
    t_wait = false;
  }
  return state;
}

/* This function will Draw robotic eyes on display based on current state. */

bool Draw_Robotic_Eyes(bool bInit, uint8_t data[8], uint8_t pause, bool wait)
{
  #define NUM_EYES  2

  const uint8_t offset = 6;
  const uint8_t dataSize = 8;

  // are we initializing?
  if (bInit)
  {
    resetMatrix();
    bInit = false;
  }

 /* "wait" will be true for the eye pose which need to put on hold untill state changes. */
  if(wait)
  {
     while(t_wait)
     {
       get_state();
     }
  }
  /* otherwise pose will pause for given duration specified using "pause" */
  else
  {
     // waiting for time to animate?
     while (millis()-prevTimeAnim < pause);
  }
 
  prevTimeAnim = millis();    // starting point for next animate


  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t e=1; e<=NUM_EYES; e++)
  {
    for (uint8_t i=0; i<dataSize; i++)
    {
      mx.setColumn((e * offset) + ((e-1) * 6 )+i, data[i]) ;
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}


// ========== Control routines ===========
//
void resetMatrix(void)
{
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY/1); // MAX_INTENSITY = 15 >> 1 
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
  prevTimeAnim = 0;
}

void runMatrixAnimation(uint8_t state)
// Schedule the animations, switching to the next one when the
// the mode switch is pressed.
{
  static  boolean bRestart = true;
  uint8_t * data;
  uint8_t pause;



  // now do whatever we do in the current state
  switch(state)
  {
    case  rest: 
    {
      data = RE_rest;
      bRestart = Draw_Robotic_Eyes(bRestart,data,1000,false);         
      break;
    }
    case  blink: 
    {
      data = RE_blink[0];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);        
      data = RE_blink[1];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);   
      data = RE_blink[2];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);   
      data = RE_blink[3];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);   
      data = RE_blink[4];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);
      data = RE_blink[0];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,true);     
      break;
    }
    case  right: 
    {
      data = RE_right[0];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);       
      data = RE_right[1];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,true);     
      break;
    }
    case  left: 
    {
      data = RE_left[0];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);       
      data = RE_left[1];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,true);     
      break;
    }
    case  up: 
    {
      data = RE_up[0];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);       
      data = RE_up[1];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);    
      data = RE_up[2];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,true);    
      break;
    }
    case  down: 
    {
      data = RE_down[0];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);       
      data = RE_down[1];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,false);   
      data = RE_down[2];
      bRestart = Draw_Robotic_Eyes(bRestart,data,100,true);   
      break;
    }
    default: state = 0;
  }
}


uint8_t joystick_input(void)
{
  uint8_t pos =0;
  button.loop(); // MUST call the loop() function first
  // read analog X and Y analog values
  value_X = map (analogRead(VRX_PIN), 0, 1023, -255, 255);
  value_Y = map (analogRead(VRY_PIN), 0, 1023, -255, 255);
  //Serial.print("Value of X is: ");
  //Serial.println(value_X);
  //Serial.print("Value of Y is: ");
  //Serial.println(value_Y);
  // Read the button value
  bValue = button.getState();

  if (button.isPressed()) {
    // TODO do something here
    pos = J_blink;
    return pos;
  }

  if (button.isReleased()) {
    // TODO do something here    
  }

  if (abs(value_X) > abs(value_Y))
  { 
    //value of x : 0:125:255  up:middle:down -255:-4:255
    //value of y : 0:129:255  right:middle:left -255:4:255

    //Serial.print(" : button = ");
    //Serial.println(bValue);
    
    if(value_X > MIN_THRESHOLD)
    {
      pos = J_down;
    }
    else if(value_X < -MIN_THRESHOLD)
    {
      pos = J_up;
    }
    else
    {
      pos = J_center;
    }
  }
  else
  {
    if(value_Y > MIN_THRESHOLD)
    {
      pos = J_left;
    }
    else if(value_Y < -MIN_THRESHOLD)
    {
      pos = J_right;
    }
    else
    {
      pos = J_center;
    }
  }
    return pos;
}


