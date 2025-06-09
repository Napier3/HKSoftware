#pragma once
#include "FaultDef_Calc.h"

//故障计算: 工频变化量计算模型: 固定定电流模型(专用)
class CFaultCalc_GPFault :
	public FaultCalc_GPFault
{
public:

	CFaultCalc_GPFault(void)
	{
		InitStruct();
	}
	~CFaultCalc_GPFault(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_GPFault *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			Zzd_Mag=1.0f;			//整定阻抗
			Zzd_Ang=90.0f;
			m=0.9f;					//校验点: m=0.9, 1.1, ...
			FaultIf=5.0f;			//短路电流
			FaultType=FAULT_A;		//故障类型: 见 FaultEnum_FaultType
			FaultDirection=0;		//故障方向: 0--正方向, 1--反方向
			//
			Us=57.735f;				//额定电压
			ILoad_Mag=0.0f;			//负荷电流
			ILoad_Ang=0.0f;			//负荷电流角度(相对于对应相的电压, +为超前)
			//
			KL_Mode=KL;				//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
			KL_Mag=0.67f;			//线路阻抗的零序补偿系数(KL 方式有效)
			KL_Ang=0.0f;
			KL_KR=0.67f;			//线路阻抗的零序补偿系数(KR,KX 方式有效)
			KL_KX=0.67f;
			//
			//计算结果: 3相电压, 3相电流
			for(i=0;i<3;i++)
			{
				Result.Up[i].Mag=0.0f;
				Result.Up[i].Ang=0.0f;
				Result.Ip[i].Mag=0.0f;
				Result.Ip[i].Ang=0.0f;
			}
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//结构体复制
	void CopyStructTo(FaultCalc_GPFault *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_GPFault *pSrc, FaultCalc_GPFault *pDst)
	{
		pDst=pSrc;
	}


};
