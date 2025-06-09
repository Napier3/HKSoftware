#pragma once
#include "FaultDef_Calc.h"

//差动计算: 差动整组
class CFaultCalc_Diff_Shot :
	public FaultCalc_Diff_Shot
{
public:

	CFaultCalc_Diff_Shot(void)
	{
		InitStruct();
	}
	~CFaultCalc_Diff_Shot(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_Diff_Shot *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			//变压器接线(保护设置), 用于确定变压器钟点 m_nClock
			ProtSort=PROT_TRANS;			//保护分类: 见 FaultEnum_Diff_ProtSort
			TransWindType=TWO_WINDINGS;		//变压器绕组数: 见 FaultEnum_Diff_TransWindType
			TransGroupMode=YD_11;			//变压器接线组别: 见 FaultEnum_Diff_TransGroupMode_...
			AdoptWind=H_L;					//参与试验的绕组: 见 FaultEnum_Diff_AdoptWind 
			//
			I1_bY0=1;				//1--Y0; 0--Y 或 d
			I2_bY0=0;
			PowerPos=0;				//电源位置: 0--I1侧, 1--I2侧;
			FaultPos=1;				//故障点位置: 0--I1侧,     1--I2侧
			FaultArea=0;			//            0--区内故障; 1--区外故障
			FaultType=DIFF_AB;		//故障类型: 见 FaultEnum_Diff_FaultType, 012--ABC,  345--AB,BC,CA;  6--ABC
			FaultIp=1.0f;			//故障电流: CT 二次侧值
			DirectionMode=0;		//电流正方向设置: 0--元件内部故障为正;  1--元件外部故障为正
			//
			//计算结果, 只需要其中的 6 路基波电流
			for(i=0;i<6;i++)
			{
				Result.Ip[i].Mag=0.0f;			//基波电流
				Result.Ip[i].Ang=0.0f;
				//
				Result.Ip_Harm[i].Mag=0.0f;		//谐波制动: 叠加谐波电流
				Result.Ip_Harm[i].Ang=0.0f;
				//
				Result.GapAng[i]=0.0f;			//间断角制动: 间断角
			}
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//结构体复制
	void CopyStructTo(FaultCalc_Diff_Shot *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_Diff_Shot *pSrc, FaultCalc_Diff_Shot *pDst)
	{
		pDst=pSrc;
	}


};
