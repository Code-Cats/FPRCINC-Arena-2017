#include "date_deal.h"
#include "base_deal.h"
#include "pid.h"
//转换数列
//A组
volatile u16  CONVERT_2Y0A02[2][47]=\
{{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,55,60,65,70,75,80,85,90,95,100,105,110,200}\
,{1369,2208,2351,2347,2487,2600,2755,3075,3372,3516,3565,3584,3545,3480,3435,3370,3305,3242,3165,3021,2855,2705,2582,2426,2280,2177,2075,1970,1867,1800,1715,1635,1555,1519,1433,1379,1306,1140,1115,997,931,900,817,803,790,730,500}};
//B组	//前两组设置为999，0的原因是防止前面一段误差检测				//最后面加200的目的是过远距离检测
volatile u16 CONVERT_2Y0A21[2][47]=\
{{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,55,60,65,70,75,80,85,90,95,100,105,110,200}\
,{0,3564,3747,3847,3862,3735,3475,3070,2822,2620,2425,2275,2135,1972,1875,1822,1750,1685,1640,1555,1445,1297,1200,1155,1110,1067,1010,975,935,905,875,832,815,787,722,670,650,610,575,560,503,485,480,460,455,435,290}};

AttitudeTypeDef Attitude={0};


void Infrare_Convert()
{
	int ergodic;
	for(Sensor.Infrare.number=0;Sensor.Infrare.number<10;Sensor.Infrare.number++)
	{
		if(Sensor.Infrare.number==5||Sensor.Infrare.number==9)	//B短的2Y0A21
		{
			
			for(ergodic=0;ergodic<46;ergodic++)
			{
				if(Sensor.Infrare.rawdate[Sensor.Infrare.number]>CONVERT_2Y0A21[1][ergodic] && Sensor.Infrare.rawdate[Sensor.Infrare.number]<CONVERT_2Y0A21[1][ergodic+1])
				{
					Sensor.Infrare.distance[Sensor.Infrare.number][0][0]=CONVERT_2Y0A21[0][ergodic];
					Sensor.Infrare.distance[Sensor.Infrare.number][0][1]=CONVERT_2Y0A21[0][ergodic+1];
				}
				else if(Sensor.Infrare.rawdate[Sensor.Infrare.number]<CONVERT_2Y0A21[1][ergodic] && Sensor.Infrare.rawdate[Sensor.Infrare.number]>CONVERT_2Y0A21[1][ergodic+1])
				{
					Sensor.Infrare.distance[Sensor.Infrare.number][1][0]=CONVERT_2Y0A21[0][ergodic];
					Sensor.Infrare.distance[Sensor.Infrare.number][1][1]=CONVERT_2Y0A21[0][ergodic+1];////////////////////////////
				}
			}
			
		}
		else	//A长的2Y0A02
		{
			
			for(ergodic=0;ergodic<46;ergodic++)
			{
			if(Sensor.Infrare.rawdate[Sensor.Infrare.number]>CONVERT_2Y0A02[1][ergodic] && Sensor.Infrare.rawdate[Sensor.Infrare.number]<CONVERT_2Y0A02[1][ergodic+1])
				{
					Sensor.Infrare.distance[Sensor.Infrare.number][0][0]=CONVERT_2Y0A02[0][ergodic];
					Sensor.Infrare.distance[Sensor.Infrare.number][0][1]=CONVERT_2Y0A02[0][ergodic+1];
				}
  				else if(Sensor.Infrare.rawdate[Sensor.Infrare.number]<CONVERT_2Y0A02[1][ergodic] && Sensor.Infrare.rawdate[Sensor.Infrare.number]>CONVERT_2Y0A02[1][ergodic+1])
				{
					Sensor.Infrare.distance[Sensor.Infrare.number][1][0]=CONVERT_2Y0A02[0][ergodic];
					Sensor.Infrare.distance[Sensor.Infrare.number][1][1]=CONVERT_2Y0A02[0][ergodic+1];
				}
			}
			
		}
	}
}



void Get_Enemy(void)	//	在岛上时检测敌人位置与距离	//返回值为距离+在自己什么方位
{

	
	Attitude.Sign_Bit=0;	//清零标志位
	for(Sensor.Infrare.number=0;Sensor.Infrare.number<10;Sensor.Infrare.number++)
	{
		Attitude.position[Sensor.Infrare.number]=0;
		Attitude.distance[Sensor.Infrare.number]=0;
	}
	
	
			if(Sensor.Infrare.distance[0][0][0]>2 && Sensor.Infrare.distance[0][1][0]<=32)		//A长：小的小值大于2，大的小值小于32  为近
			{	//对0号传感器的单独照顾
				Attitude.position[Attitude.Sign_Bit]=10;
				Attitude.distance[Attitude.Sign_Bit]=NEAR;
				Attitude.Sign_Bit++;
			}
			else if(Sensor.Infrare.distance[0][1][0]>32 && Sensor.Infrare.distance[0][1][1]<70)
			{
				Attitude.position[Attitude.Sign_Bit]=10;
				Attitude.distance[Attitude.Sign_Bit]=FAR;
				Attitude.Sign_Bit++;
			}
	
	for(Sensor.Infrare.number=1;Sensor.Infrare.number<9;Sensor.Infrare.number++)	//9的原因是删掉9号短
	{
		if(Sensor.Infrare.number==5)
		{
//			if(Sensor.Infrare.distance[Sensor.Infrare.number][1][0]<=32)		//B长：大的小值小于32  为近
//			{
//				Attitude.position[Attitude.Sign_Bit]=Sensor.Infrare.number;
//				Attitude.distance[Attitude.Sign_Bit]=NEAR;
//				Attitude.Sign_Bit++;
//			}
//			else if(Sensor.Infrare.distance[Sensor.Infrare.number][1][0]>32 && Sensor.Infrare.distance[Sensor.Infrare.number][1][1]<70)
//			{
//				Attitude.position[Attitude.Sign_Bit]=Sensor.Infrare.number;
//				Attitude.distance[Attitude.Sign_Bit]=FAR;
//				Attitude.Sign_Bit++;
//			}
		}
		else
		{
			if(Sensor.Infrare.distance[Sensor.Infrare.number][0][0]>2 && Sensor.Infrare.distance[Sensor.Infrare.number][1][0]<=32)		//A长：小的小值大于2，大的小值小于32  为近
			{
				Attitude.position[Attitude.Sign_Bit]=Sensor.Infrare.number;
				Attitude.distance[Attitude.Sign_Bit]=NEAR;
				Attitude.Sign_Bit++;
			}
			else if(Sensor.Infrare.distance[Sensor.Infrare.number][1][0]>32 && Sensor.Infrare.distance[Sensor.Infrare.number][1][1]<60)
			{
				Attitude.position[Attitude.Sign_Bit]=Sensor.Infrare.number;
				Attitude.distance[Attitude.Sign_Bit]=FAR;
				Attitude.Sign_Bit++;
			}
		}
	}
	
	Attitude.Front_distance=Sensor.Infrare.distance[0][1][0];
		
//	if(Sensor.Infrare.distance[0][1][0]<75)
//		{
//			if(Sensor.Infrare.distance[0][1][0]>32)
//			{
//				Attitude.position[Attitude.Sign_Bit]=10;
//				Attitude.distance[Attitude.Sign_Bit]=FAR;
//				Attitude.Sign_Bit++;
//			}
//			else
//			{
//				Attitude.position[Attitude.Sign_Bit]=10;
//				Attitude.distance[Attitude.Sign_Bit]=NEAR;
//				Attitude.Sign_Bit++;
//			}
//			
//			//Attitude.Front_distance=Sensor.Infrare.distance[0][1][0];
//		}
	
	
//		if(Sensor.Infrare.distance[0][1][0]<75 && Sensor.Infrare.distance[9][1][0]<75)
//		{
//			qian_dif=MyAbs(Sensor.Infrare.distance[0][0][0]-Sensor.Infrare.distance[9][1][0]);
//			hou_dif=MyAbs(Sensor.Infrare.distance[0][1][0]-Sensor.Infrare.distance[9][1][0]);
//			
//			if(qian_dif>hou_dif)
//			{
//				Attitude.Front_distance=(Sensor.Infrare.distance[9][1][0]+Sensor.Infrare.distance[0][1][0])/2;
//				if(Attitude.Front_distance<32)
//				{
//				Attitude.position[Attitude.Sign_Bit]=10;
//				Attitude.distance[Attitude.Sign_Bit]=NEAR;
//				Attitude.Sign_Bit++;
//				}
//				else
//				{
//				Attitude.position[Attitude.Sign_Bit]=10;
//				Attitude.distance[Attitude.Sign_Bit]=FAR;
//				Attitude.Sign_Bit++;
//				}
//			}
//			else
//			{
//				Attitude.Front_distance=(Sensor.Infrare.distance[9][1][0]+Sensor.Infrare.distance[0][0][0])/2;
//				if(Attitude.Front_distance<32)
//				{
//				Attitude.position[Attitude.Sign_Bit]=10;
//				Attitude.distance[Attitude.Sign_Bit]=NEAR;
//				Attitude.Sign_Bit++;
//				}
//				else
//				{
//				Attitude.position[Attitude.Sign_Bit]=10;
//				Attitude.distance[Attitude.Sign_Bit]=FAR;
//				Attitude.Sign_Bit++;
//				}
//			}
//		}
		
		
		
	
}





