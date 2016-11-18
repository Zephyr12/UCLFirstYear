/*
 * Author: Amartya Vadlamani
 * Notes: The program reads data from most of the arduino sensors and 
 *        outputs it into a plain text format that is easy to parse.
 *        
 *        The grammar is
 *        
 *        > program := <message> '\n' <program> | ;
 *        > message := <key-value-pair> ',' <message> | ; 
 *        > key-value-pair := <key> '=' <value> | ;
 *        > key = [a-zA-Z.0-9]+; // a identifer with a . in it
 *        > value  = [0-9]+(.[0-9]+)? // a float
 *        
 *        in BNF
 */

#include <EngduinoThermistor.h>
#include <EngduinoLight.h>
#include <EngduinoAccelerometer.h>
#include <EngduinoLEDs.h>
#include <EngduinoButton.h>
#include <EngduinoMagnetometer.h>
#include <Wire.h>

/* Defining a value for gravity as the accelerometer only outputs values
 * between 0 and 1 and it should take values of 1 to G
 */
#define G 9.81f

/*
 * A simple typedef to define a named key-value pair
 */
typedef struct value{
  char* name;
  float value;
} value_t;

void setup()
{
  /*initalise a fast serial connection and all the relevant modules*/
  Serial.begin(115200);
  EngduinoAccelerometer.begin();
  EngduinoLEDs.begin();
  EngduinoThermistor.begin();
  EngduinoLight.begin();
  EngduinoMagnetometer.begin();
  EngduinoButton.begin();
  
  /* 
   *  Debug is it working?
   *  cyan and red alternating to test the LEDs
   */
  for (int i = 0; i < 16; i++){
    EngduinoLEDs.setLED(i, 15*i % 30, (15+15*i)%30, (15+15*i)%30);
    delay(50);
    EngduinoLEDs.setLED(i, 2*i % 4, (2+2*i)%4, (2+2*i)%4);
  }
  /*
   * Zero it out to avoid light sensor interference
   */
  for (int i = 0; i < 16; i++){
    EngduinoLEDs.setLED(i, 15*i % 30, (15+15*i)%30, (15+15*i)%30);
    delay(50);
    EngduinoLEDs.setLED(i, 0, 0, 0);
  }
  /*
   * but set an "on" light
   */
  EngduinoLEDs.setLED(0, 1, 1, 1);
}

/*
 * Print a key-value pair with given `value`
 */
void printValue(value_t value){
  Serial.write(value.name);
  Serial.write("=");
  Serial.print(value.value);
}

/*
 * Print output for a given array of `values` of length `num_values`
 */
void printFormattedOutput(value_t values[], int num_values){
  for(int i = 0; i < num_values; i++){
    value_t value = values[i];
    printValue(value);
    if (i != num_values - 1){
      Serial.write(',');
    }else{
      Serial.write('\n');
      Serial.flush();
    }
  }
}


void loop()
{   
  /*
   * Begin reading values
   */
  float temp = EngduinoThermistor.temperature(CELSIUS);
  float light = EngduinoLight.lightLevel();

  
  float mag_buf[3] = {0,0,0};
  EngduinoMagnetometer.xyz(mag_buf);

  float accel_buf[3] = {0,0,0};
  EngduinoAccelerometer.xyz(accel_buf);
  
  /*
   * Multiply accelerometer by G = 9.81 to map acceleration values to ms^-2
   */
  accel_buf[0] *= G;
  accel_buf[1] *= G;
  accel_buf[2] *= G;

  /*
   * Calculate magnitudes with pythagoreas theorem.
   */
  float accel_mag = sqrt(accel_buf[0]*accel_buf[0] + accel_buf[1]*accel_buf[1] + accel_buf[2]*accel_buf[2]);
  float mag_mag = sqrt(mag_buf[0]*mag_buf[0] + mag_buf[1]*mag_buf[1] + mag_buf[2]*mag_buf[2]);

  /*
   * Build the values array using named structured syntax
   */
  value_t values[] = {
    
    {.name="temp (C)", temp},
    {.name="light (1-1000)", light},
    
    {.name="mag.x", mag_buf[0]},
    {.name="mag.y", mag_buf[1]},
    {.name="mag.z", mag_buf[2]},
    {.name="mag.mag", mag_mag},

    {.name="accel.x (ms^-2)", accel_buf[0]},
    {.name="accel.y (ms^-2)", accel_buf[1]},
    {.name="accel.z (ms^-2)", accel_buf[2]},
    {.name="accel.mag (ms^-2)", accel_mag}
  
  };
  /*
   * Print out the values
   */
  printFormattedOutput(values, 10);
  
  /*
   * Small delay to stop strange issues with high update rate
   */
  delay(100);
}



