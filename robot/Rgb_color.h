#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#define PIN_L      9
#define PIN_R      A3
#define NUMPIXEL_L 9
#define NUMPIXEL_R 9
#define touch1 6
#define touch2 7
#define touch3 8
#define touchHead A2
Adafruit_NeoPixel led_L(NUMPIXEL_L,PIN_L,NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_R(NUMPIXEL_R,PIN_R,NEO_GRB + NEO_KHZ800);
void touch_rgb_init()
{
  pinMode(touch1,INPUT);
  pinMode(touch2,INPUT);
  pinMode(touch3,INPUT);
  pinMode(touchHead,INPUT);
  Serial.begin(9600);
  led_L.begin();
  led_R.begin();
  led_L.setBrightness(200);
  led_R.setBrightness(200);
  led_L.clear();
  led_R.clear();
  led_L.show();
  led_R.show();
}
void touch_rgb_control()
{
  Serial.print(digitalRead(touch1));
  Serial.print("  ");
  Serial.print(digitalRead(touch2));
  Serial.print("  ");
  Serial.print(digitalRead(touch3));
  Serial.println("");
  delay(200);
  led_L.clear();
  led_L.show();
  led_R.clear();
  led_R.show();
  if (!digitalRead(touch1))
  {
    while (digitalRead(touch2) !=0  )
    {
      for (int i = 0;i <= 8;i++)
      {
        led_L.setPixelColor(i,led_L.Color(255,0,0));
        led_R.setPixelColor(8-i,led_R.Color(255,0,0));
        led_L.show();
        led_R.show();
        delay(50);
      }
      led_L.clear();
      led_R.clear();
      led_L.show();
      led_R.show();
    }

  }
  else if (!digitalRead(touch3))
  {
    while (digitalRead(touch2) !=0 )
    {
      for (int i = 8;i >= 0;i--)
      {
        led_L.setPixelColor(i,led_L.Color(255,0,0));
        led_R.setPixelColor(8-i,led_R.Color(255,0,0));
        led_L.show();
        led_R.show();
        delay(50);
      }
    led_L.clear();
    led_L.show();
    led_R.clear();
    led_R.show();
    }
  }
}
void touch_head()
{
  Serial.println(digitalRead(touchHead));
  delay(100);
  if (!touchHead)
  {
    for (int brightness = 0; brightness <= 255; brightness ++)
    {
      led_L.setBrightness(brightness);
      led_R.setBrightness(brightness);
      delay(10);
    }
    for (int i = 0;i <= 8;i++)
    {
      led_L.setPixelColor(i,led_L.Color(255,0,0));
      led_R.setPixelColor(8-i,led_R.Color(255,0,0));
    }
    led_L.show();
    led_R.show();
  }

}
