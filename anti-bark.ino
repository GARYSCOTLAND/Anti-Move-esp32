// use first channel of 16 channels (started from zero)
#define LEDC_CHANNEL_0     0

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     5000

int brightness = 0;    // how bright the LED is
int fadeAmount = 10;    // how many points to fade the LED by
// Arduino like analogWrite
// value has to be between 0 and valueMax
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(channel, duty);
}


const float sound_analog = 36;
const int green_led = 22;
const int red_led = 23;
const int speaker = 25;
const int motors = 26;
int sensitivity = 1200; //700 really sensitive

#include <WiFi.h>



// Set these to your desired credentials.
const char* ssid = "BARK";
const char* password = "pleaseno";




void setup(){
  Serial.begin(115200);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(motors, OUTPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
 ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
 ledcAttachPin(green_led, LEDC_CHANNEL_0);
  


}

void loop(){

  
  if(WiFi.softAPgetStationNum()== 1){
    
    digitalWrite(red_led, LOW);
      // set the brightness on LEDC channel 0
  ledcAnalogWrite(LEDC_CHANNEL_0, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 300) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

 

  if(WiFi.softAPgetStationNum()== 0) {
    ledcAnalogWrite(LEDC_CHANNEL_0, 0);

  
  digitalWrite(red_led, HIGH); 
  int val_analog = (analogRead(sound_analog));

  //Serial.print(val_analog);
  Serial.print('\n'); 




  
 
  if (val_analog >= sensitivity){

    Serial.print("FOUND THRESHOLD");

    digitalWrite(green_led, HIGH);   // turn the LED on (HIGH is the voltage level)
 
   
   digitalWrite(red_led, HIGH);   // turn the LED on (HIGH is the voltage level)

  
  digitalWrite(speaker, HIGH);   // turn the LED on (HIGH is the voltage level)


   digitalWrite(motors, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);  

   digitalWrite(green_led, LOW);    // turn the LED off by making the voltage LOW
   digitalWrite(red_led, LOW);    // turn the LED off by making the voltage LOW
                        // wait for a second
  digitalWrite(speaker, LOW);    // turn the LED off by making the voltage LOW
digitalWrite(motors, LOW);    // turn the LED off by making the voltage LOW
delay(1000);
  }
    }
  


  

 
}
