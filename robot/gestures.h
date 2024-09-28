//paj7620_9gestures 示例改
#include <Wire.h>
#include "paj7620.h"
#define GES_REACTION_TIME   500 
#define GES_ENTRY_TIME			600
#define GES_QUIT_TIME			800
void gestures_init()
{
  uint8_t error = 0;
  Serial.begin(9600);
  Serial.println("初始化手势模块");
  error = paj7620Init();//初始化手势模块
  if (error)
  {
    Serial.print("初始化错误，错误代码是：");
    Serial.println(error);
  }
  else
  {
    Serial.println("初始化成功");
  }
  Serial.println("输入手势");
}
String result_gesture()
{
  String result;
  uint8_t data = 0,data1 = 0,error;
  error = paj7620ReadReg(0x43, 1, &data); //读取手势数据
  if (!error)
  {
    switch(data)
    {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data==GES_FORWARD_FLAG)
        {
          result = "forward";
          //Serial.println("获取到向前状态");
				  delay(GES_QUIT_TIME);
        }
        else if(data==GES_BACKWARD_FLAG)
        {
          result = "backward";
          //Serial.println("获取到向后状态");
          delay(GES_QUIT_TIME);
        }
        else
        {
          result = "right";
          //Serial.println("获取到向右状态");
        }
        break;
      case GES_LEFT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data==GES_FORWARD_FLAG)
        {
          result = "forward";
          //Serial.println("获取到向前状态");
          delay(GES_QUIT_TIME);
        }
        else if(data==GES_BACKWARD_FLAG)
        {
          result = "backward";
          //Serial.println("获取到向后状态");
          delay(GES_QUIT_TIME);
        }
        else
        {
          result = "left";
          //Serial.println("获取到向左状态");
        }
        break;
      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data==GES_FORWARD_FLAG)
        {
          result = "forward";
          //Serial.println("获取到向前状态");
          delay(GES_QUIT_TIME);
        }
        else if(data==GES_BACKWARD_FLAG)
        {
          result = "backward";
          //Serial.println("获取到向后状态");
          delay(GES_QUIT_TIME);
        }
        else
        {
          result = "up";
          //Serial.println("获取到向上状态");
        }
        break;
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
				paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
				{
          result = "forward";
					//Serial.println("获取到向前状态");
					delay(GES_QUIT_TIME);
				}
				else if(data == GES_BACKWARD_FLAG) 
				{
          result = "backward";
					//Serial.println("获取到向后状态");
					delay(GES_QUIT_TIME);
				}
				else
				{
          result = "down";
					//Serial.println("获取到向下状态");
				}          
				break;
      case GES_FORWARD_FLAG:
        result = "forward";
				//Serial.println("获取到向前状态");
				delay(GES_QUIT_TIME);
				break;
			case GES_BACKWARD_FLAG:
        result = "backward";		  
				//Serial.println("获取到向后状态");
				delay(GES_QUIT_TIME);
				break;
			default:
				paj7620ReadReg(0x44, 1, &data1);
				if (data1 == GES_WAVE_FLAG) 
				{
          result = "wave";
					//Serial.println("获取到挥手状态");
				}
				break;
    }
  }
  return result;
}