#include <Servo.h>
Servo myservo[4]; //初始四个舵机，myservo[0]-L1,myservo[1]-R1,myservo[2]-L2,myservo[3]-R2
int servoPin[] = {2,3,4,5}; //初始引脚设置
int pt_angle[] = {40,40,40,40}; //正向站立初始角度，零点位置
//int nt_angle[] = {220,220,220,220}; //反向站立初始角度，零点位置
/*
正向前进
*/
int anglePt[8][4] = {
  {0,20,20,0},          //步态1
  {-20,20,20,-20},      //步态2
  {-20,0,0,-20},        //步态3
  {0,0,0,0},            //步态4
  {20,0,0,20},          //步态5
  {20,-20,-20,20},      //步态6
  {0,-20,-20,0},        //步态7
  {0,0,0,0},            //步态8
  };
/*
反向前进
*/
int angleNt[8][4] = {
  {20,0,0,20},          //步态1
  {20,-20,-20,20},      //步态2
  {0,-20,-20,0},        //步态3
  {0,0,0,0},            //步态4
  {0,20,20,0},          //步态5
  {-20,20,20,-20},      //步态6
  {-20,0,0,-20},        //步态7
  {0,0,0,0},            //步态8
};
/*
初始舵机引脚配置和角度归零
*/
void servoSetinit(int dt) // dicrection 为0或1，0正向站立，1反向站立
{
  for (int i = 0; i <= 3; i++)
  {
    myservo[i].attach(servoPin[i]);
  }
  for (int i =0;i <= 3; i++)
  {
    myservo[i].write(map(pt_angle[i]+180*dt,0,270,0,180));
    delay(100);
  }
}
/*
步态设置
waittime延时时间，步态改变角度数组angle[8][4]，第几个动作row，d为pt正向，nt为反向
*/
void servoSet(int waittime,int angle[8][4],int row,String d) 
{
  if (d == "pt")
  {
    for (int i = 0; i <= 3; i++)
    {
      myservo[i].write(map(pt_angle[i]+angle[row-1][i],0,270,0,180));
      delay(waittime);   
    }
  }
  else if (d == "nt")
  {
    for (int i = 0; i <= 3; i++)
    {
      myservo[i].write(map(pt_angle[i]+180+(-1*angle[row-1][i]),0,270,0,180));
      delay(waittime);   
    }
  }
}
/*
1.前进动作
2.dicrection 为pt时正向前进
3.dicrection 为nt时反向前进(倒过来)
*/
void go(int delaytime,String dicrection) 
{
  if (dicrection == "pt")
  {
   for (int pos = 1;pos <= 8;pos ++)
    {
      servoSet(delaytime,anglePt,pos,dicrection);
    }
  }
  else if (dicrection == "nt")
  {
    for (int pos = 1;pos <= 8;pos ++)
    {
      servoSet(delaytime,angleNt,pos,dicrection);
    }
  }
}
/*
1.后退动作
2.dicrection 为pt时正向后退
3.dicrection 为nt时反向后退(倒过来)
*/
void back(int delaytime,String dicrection) 
{
  if (dicrection == "pt")
  {
   for (int pos = 8;pos <= 1;pos --)
    {
      servoSet(delaytime,anglePt,pos,dicrection);
    }
  }
  else if (dicrection == "nt")
  {
    for (int pos = 8;pos <= 8;pos --)
    {
      servoSet(delaytime,angleNt,pos,dicrection);
    }
  }
}