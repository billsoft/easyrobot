/*
1.动作步态程序可看robotaction.h或者robotactions.h
2.手势识别动作基于paj7620_9gestures 示例修改，具体可看gestures.h
3.RGB和触摸集成到一块扩展，具体引脚参考可以看Rgb_color.h
4.摄像头视频采集和控制采用esp32cam,通过串口通讯接受指令，程序可看相关文件夹
5.mpu6050检测姿态暂时没有写，有想添加的可自行添加
6.纯菜鸟制作，勿喷，有问题可以一起交流，b站: 黄昏近残夜
*/
#include "robotaction.h"
#include "gestures.h"
#include "Rgb_color.h"
#include <SoftwareSerial.h>
#define L1 2
#define R1 3
#define L2 4
#define R2 5
#define camera_led 9
SoftwareSerial mySerial(12,13);
bool touch_turn = false;
bool positive = true,negative = false;
int turn_number = 0;
String esp32_read;
void setup()
{
  // put your setup code here, to run once:
  pinMode(camera_led,OUTPUT);
  set_pin(L1,R1,L2,R2);
  //gestures_init();
  positive_stand_set();
  touch_rgb_init();
  //pinMode(touch,INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop()
{
  if (mySerial.available())
  {
    esp32_read = mySerial.readString();
    Serial.println(esp32_read);
    if (esp32_read == "Camera ready")
    {
      for (int i = 0; i <= 10; i++)
      {
        digitalWrite(camera_led, HIGH);
        delay(200);
        digitalWrite(camera_led, LOW);
        delay(200);
      }
    }
    if (esp32_read == "turn")
    {
      turn_number ++;
      if (turn_number % 2 == 1)
      {
        positive = false;
        do_flip_positive();
      }
      else
      {
        positive = true;
        do_flip_negative();
      }
      negative = !positive;
      Serial.println(turn_number % 2);
      delay(500);
    }

    if (positive)
    { 
      //do_flip_positive();
      if (esp32_read == "go")
      {
        for (int i = 0; i <= 3; i++)
        {
          positive_go();
        }
      }
      else if (esp32_read == "back")
      {
        for (int i = 0; i <=3; i++)
        {
          positive_back();
        }
      }
      else if (esp32_read == "left")
      {
        for (int i = 0; i <=2; i++)
        {
          positive_left();
        }
      }
      else if (esp32_read == "right")
      {
        for (int i = 0; i <=2; i++)
        {
          positive_right();
        }
      }
    }
    if (negative)
    { 
      if (esp32_read == "go")
      {
        for (int i = 0; i <= 3; i++)
        {
          negative_go();
        }
      }
      else if (esp32_read == "back")
      {
        for (int i = 0; i <= 3; i++)
        {
          negative_back();
        }
      }
      else if (esp32_read == "left")
      {
        for (int i = 0; i <= 2; i++)
        {
          negative_left();
        }
      }
      else if (esp32_read == "right")
      {
        for (int i = 0; i <= 2; i++)
        {
          negative_right();
        }
      }
    }
  }
  else 
  {
    touch_rgb_control();
  }
  delay(200);

  /*以下程序是手势识别*/
  /*
  String result_rv = result_gesture();
  //Serial.println(result_rv);
  if (result_rv == "forward")
  {
    Serial.println("向前");
    do_flip_positive();

    for (int i=0;i<=5;i++)
    {
      negative_back();
    }
  }
  
  else if (result_rv == "backward")
  {
    Serial.println("向后");
    for(int i=0;i<=2;i++)
    {
      positive_back();
    }
  }
  /*
  else if (result_rv == "left")
  {
    Serial.println("向左");
    for (int i=0;i<=2;i++)
    {
      posivite_right();
    }
  }
  else if (result_rv == "right")
  {
    Serial.println("向右");
    for (int i=0;i<=2;i++)
    {
      posivite_left();
    }
  }
  else if (result_rv == "up")
  {
    Serial.println("向上");
    positive_stand_set();
  }
  else if (result_rv == "down")
  {
    Serial.println("向下");
    positive_get_down();
  }

  else if (result_rv == "wave")
  {
    Serial.println("挥手");
    for(int i=0;i<=2;i++)
    {
      positive_wave();
    }
    positive_stand_set();
  }
  */
}
