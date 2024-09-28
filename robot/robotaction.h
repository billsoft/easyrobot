/*
1.前进后退等动作分解，可对应动作图例文件夹内图片分析
2.步态动作参考b站up主石桥北老师，地址：
https://www.bilibili.com/video/BV1yH4y1U7Zo/?spm_id_from=333.337.search-card.all.click&vd_source=0b2798e3dbadd3bb799cc7f946455f03
3.使用舵机为270度舵机，某宝不算贵，14元一个（地址可看文件夹内的物料清单）
4.需要舵机方向两正两反，目的是保持转动方向一致
5.程序稍微长，可以使用优化版robotactions.h（暂未验证，此程序舵机安装为同侧正反相同，即正正反反，安装方式见安装示例图）
6.此程序为舵机安装为异向，即正反反正，安装方式见安装示例图
*/
#include <Servo.h>
Servo myservo_L1;
Servo myservo_R1;
Servo myservo_L2;
Servo myservo_R2;
int L1_init_pt = 40;
int R1_init_pt = 48;
int L2_init_pt = 45;
int R2_init_pt = 55;
int L1_init_nt = 220;
int R1_init_nt = 228;
int L2_init_nt = 225;
int R2_init_nt = 235;
int angle = 20;
int servo_270(int x) //将180度舵机转为270度
{
  int angle = map(x,0,270,0,180);
  return angle;
}
void set_pin(int L1_Pin,int R1_Pin,int L2_pin,int R2_Pin)
{
  myservo_L1.attach(L1_Pin);
  myservo_R1.attach(R1_Pin);
  myservo_L2.attach(L2_pin);
  myservo_R2.attach(R2_Pin);
}  
//初使站立状态
//具体数值需要根据安装调整，270度的舵机因为上下翻转
//所以最开始状态设置在45度左右

void positive_stand_set()//正向站立初始化角度
{ 

  myservo_L1.write(servo_270(L1_init_pt));
  myservo_R1.write(servo_270(R1_init_pt));
  myservo_L2.write(servo_270(L2_init_pt));
  myservo_R2.write(servo_270(R2_init_pt));

}
void negative_stand_set()//反向站立初始化角度
{
  myservo_L1.write(servo_270(L1_init_nt));
  myservo_R1.write(servo_270(R1_init_nt));
  myservo_L2.write(servo_270(L2_init_nt));
  myservo_R2.write(servo_270(R2_init_nt));
}

void positive_go()//正向站立向前行走
{
  //L1 40,R1 48,L2 45,R2 55
  //可以减少延时增加速度
  // 动作 1-2
  myservo_R1.write(servo_270(R1_init_pt + angle));
  delay(150);
  myservo_L2.write(servo_270(L2_init_pt - angle));
  delay(150);
  myservo_L1.write(servo_270(L1_init_pt - angle));
  delay(150);
  myservo_R2.write(servo_270(R2_init_pt + angle));
  delay(150);
 
  // 动作 3-4
  myservo_R1.write(servo_270(R1_init_pt));
  delay(150);
  myservo_L2.write(servo_270(L2_init_pt));
  delay(150); 
  myservo_L1.write(servo_270(L1_init_pt));
  delay(150);
  myservo_R2.write(servo_270(R2_init_pt));
  delay(150);
  // 动作 5-6
  myservo_L1.write(servo_270(L1_init_pt + angle));
  delay(150);
  myservo_R2.write(servo_270(R2_init_pt - angle));
  delay(150);
  myservo_R1.write(servo_270(R1_init_pt - angle));
  delay(50);
  myservo_L2.write(servo_270(L2_init_pt + angle));
  // 动作 7-8
  myservo_L1.write(servo_270(L1_init_pt));
  delay(150);
  myservo_R2.write(servo_270(R2_init_pt));
  delay(150);
  myservo_R1.write(servo_270(R1_init_pt));
  delay(150);
  myservo_L2.write(servo_270(L2_init_pt));
  delay(150);

}
void positive_back()//正向倒走
{
  //初始L1 40,R1 48,L2 45,R2 55
  //动作 1-2
  myservo_L2.write(servo_270(L2_init_pt + angle));
  delay(150);
  myservo_R1.write(servo_270(R1_init_pt - angle));
  delay(150);
  myservo_R2.write(servo_270(R2_init_pt - angle));
  delay(150);
  myservo_L1.write(servo_270(L1_init_pt + angle));
  delay(150);
  //动作 3-4
  myservo_L2.write(servo_270(L2_init_pt));
  delay(150);
  myservo_R1.write(servo_270(R1_init_pt));
  delay(150);
  myservo_R2.write(servo_270(R2_init_pt));
  delay(150);
  myservo_L1.write(servo_270(L1_init_pt));
  delay(150);
  //动作 5-6
  myservo_R2.write(servo_270(R2_init_pt + angle));
  delay(150);
  myservo_L1.write(servo_270(L1_init_pt - angle));
  delay(150);
  myservo_L2.write(servo_270(L2_init_pt - angle));
  delay(150);
  myservo_R1.write(servo_270(R1_init_pt - angle));
  delay(150);
  //动作 7-8
  myservo_R2.write(servo_270(R2_init_pt));
  delay(150);
  myservo_L1.write(servo_270(L1_init_pt));
  delay(150);
  myservo_L2.write(servo_270(L2_init_pt));
  delay(150);
  myservo_R1.write(servo_270(R1_init_pt));
  delay(150);
}
void negative_go()//反向站立向前行走
{
  //初始L1 220，R1 228，L2 225,R2 235
  //动作 1-2
  myservo_R1.write(servo_270(R1_init_nt - angle));
  delay(150);
  myservo_L2.write(servo_270(L2_init_nt + angle));
  delay(150);
  myservo_L1.write(servo_270(L1_init_nt + angle));
  delay(150);
  myservo_R2.write(servo_270(R2_init_nt - angle));
  delay(150);

  //动作 3-4
  myservo_R1.write(servo_270(R1_init_nt));
  delay(150);
  myservo_L2.write(servo_270(L2_init_nt));
  delay(150);
  myservo_L1.write(servo_270(L1_init_nt));
  delay(150);
  myservo_R2.write(servo_270(R2_init_nt));
  delay(150);

  //动作 5-6
  myservo_L1.write(servo_270(L1_init_nt - angle));
  delay(150);
  myservo_R2.write(servo_270(R2_init_nt + angle));
  delay(150);
  myservo_R1.write(servo_270(R1_init_nt + angle));
  delay(150);
  myservo_L2.write(servo_270(L2_init_nt - angle));
  delay(150);

  //动作 7-8
  myservo_L1.write(servo_270(R1_init_nt));
  delay(150);
  myservo_R2.write(servo_270(R2_init_nt));
  delay(150);
  myservo_R1.write(servo_270(R1_init_nt));
  delay(150);
  myservo_L2.write(servo_270(L2_init_nt));
  delay(150);
}
void negative_back()//反向倒走
{
  //初始L1 220，R1 228，L2 225,R2 235
  //动作 1-2
  myservo_L2.write(servo_270(L2_init_nt - angle));
  delay(150);
  myservo_R1.write(servo_270(R1_init_nt + angle));
  delay(150);
  myservo_R2.write(servo_270(R2_init_nt + angle));
  delay(150);
  myservo_L1.write(servo_270(L1_init_nt - angle));
  delay(150);
  //动作 3-4
  myservo_L2.write(servo_270(L2_init_nt));
  delay(150);
  myservo_R1.write(servo_270(R1_init_nt));
  delay(150);
  myservo_R2.write(servo_270(R2_init_nt));
  delay(150);
  myservo_L1.write(servo_270(L1_init_nt));
  delay(150);
  //动作 5-6
  myservo_R2.write(servo_270(R2_init_nt - angle));
  delay(150);
  myservo_L1.write(servo_270(L1_init_nt + angle));
  delay(150);
  myservo_L2.write(servo_270(L2_init_nt + angle));
  delay(150);
  myservo_R1.write(servo_270(R1_init_nt - angle));
  delay(150);
  //动作 7-8
  myservo_R2.write(servo_270(R2_init_nt));
  delay(150);
  myservo_L1.write(servo_270(L1_init_nt));
  delay(150);
  myservo_L2.write(servo_270(L2_init_nt));
  delay(150);
  myservo_R1.write(servo_270(R1_init_nt));
}
void positive_get_down() //正向站立时趴下
{
  myservo_L1.write(servo_270(90));
  myservo_R1.write(servo_270(98));
  delay(150);
  myservo_L2.write(servo_270(95));
  myservo_R2.write(servo_270(105));
}
void negative_get_down() //反向站立时趴下
{
  myservo_L1.write(servo_270(180));
  myservo_R1.write(servo_270(188));
  delay(150);
  myservo_L2.write(servo_270(185));
  myservo_R2.write(servo_270(195)); 
}
void do_flip_positive()//正向站立时翻跟头
{
  positive_stand_set();
  delay(100);
  myservo_L1.write(servo_270(0));
  myservo_R1.write(servo_270(8));
  delay(100);
  myservo_L2.write(servo_270(0));
  myservo_R2.write(servo_270(10));
  delay(2000);
  myservo_L2.write(servo_270(260));
  myservo_R2.write(servo_270(270));
  delay(1000);
  myservo_L1.write(servo_270(260));
  myservo_R1.write(servo_270(268));
  delay(1000);
  negative_get_down();
  

}

void do_flip_negative()//反向站立时翻跟头
{
  //初始L1 220，R1 228，L2 225,R2 235
  negative_stand_set();
  delay(100);
  myservo_L1.write(servo_270(260));
  myservo_R1.write(servo_270(268));
  delay(100);
  myservo_L2.write(servo_270(260));
  myservo_R2.write(servo_270(270));
  delay(2000);
  myservo_L2.write(servo_270(0));
  myservo_R2.write(servo_270(10));
  delay(1000);
  myservo_L1.write(servo_270(0));
  myservo_R1.write(servo_270(8));
  delay(1000);
  positive_get_down();

}

void positive_left() //正向站立时左转
{
  //初始L1 40,R1 48,L2 45,R2 55
  myservo_R2.write(servo_270(35));
  delay(150);
  myservo_L1.write(servo_270(20));
  delay(150);
  myservo_R1.write(servo_270(28));
  delay(150);
  myservo_L2.write(servo_270(25));
  delay(150);

  myservo_R2.write(servo_270(55));
  delay(150);
  myservo_L1.write(servo_270(40));
  delay(150);
  myservo_R1.write(servo_270(48));
  delay(150);
  myservo_L2.write(servo_270(45));
  delay(150);
}
void negative_left() //反向站立时左转
{
  //初始L1 220，R1 228，L2 225,R2 235
  myservo_L2.write(servo_270(245));
  delay(150);
  myservo_R1.write(servo_270(248));
  delay(150);
  myservo_R2.write(servo_270(255));
  delay(150);
  myservo_L1.write(servo_270(240));
  delay(150);

  myservo_L2.write(servo_270(225));
  delay(150);
  myservo_R1.write(servo_270(228));
  delay(150);
  myservo_R2.write(servo_270(235));
  delay(150);
  myservo_L1.write(servo_270(220));
}
void positive_right() //正向站立时右转
{
  //初始L1 40,R1 48,L2 45,R2 55
  myservo_L2.write(servo_270(25));
  delay(150);
  myservo_R1.write(servo_270(28));
  delay(150);
  myservo_L1.write(servo_270(20));
  delay(150);
  myservo_R2.write(servo_270(35));
  delay(150);

  myservo_L2.write(servo_270(45));
  delay(150);
  myservo_R1.write(servo_270(48));
  delay(150);
  myservo_L1.write(servo_270(40));
  delay(150);
  myservo_R2.write(servo_270(55));
  delay(150);
}
void negative_right() //反向站立时右转
{
  //初始L1 220，R1 228，L2 225,R2 235
  myservo_R2.write(servo_270(255));
  delay(150);
  myservo_L1.write(servo_270(240));
  delay(150);
  myservo_L2.write(servo_270(245));
  delay(150);
  myservo_R1.write(servo_270(248));
  delay(150);

  myservo_R2.write(servo_270(235));
  delay(150);
  myservo_L1.write(servo_270(220));
  delay(150);
  myservo_L2.write(servo_270(225));
  delay(150);
  myservo_R1.write(servo_270(228));
  delay(150);
}
void dog_shake()
{
  for (int i=0;i<=20;i=i+2)
  {
    myservo_L1.write(servo_270(40-i));
    delay(10);
    myservo_R1.write(servo_270(48-i));
    delay(10);
    myservo_L2.write(servo_270(45+i));
    delay(10);
    myservo_R2.write(servo_270(55+i));
    delay(10);
  }
  for (int i=20;i>=0;i=i-2)
  {
    myservo_L1.write(servo_270(40+i));
    delay(10);
    myservo_R1.write(servo_270(48+i));
    delay(10);
    myservo_L2.write(servo_270(45-i));
    delay(10);
    myservo_R2.write(servo_270(55-i));
    delay(10);
  }
}
void dog_down()
{
  myservo_L2.write(servo_270(5));
  myservo_R2.write(servo_270(10));
  for (int i=0;i<=40;i++)
  {
    myservo_L1.write(servo_270(90-i));
    myservo_R1.write(servo_270(98-i));
    delay(10);
  }
  for (int i=90;i>=0;i--)
  {
    myservo_L1.write(servo_270(90+i));
    myservo_R1.write(servo_270(98+i));
    delay(10);
  }
}