﻿#pragma once
#include "FaultDef_Calc.h"

//零序过流保护定值校验计算: 固定定电流模型, 
//计算结果: 三个状态 (故障前, 故障, 故障转换=故障)
class CFaultCalc_ZeroSeqCurr :
	public FaultCalc_ZeroSeqCurr
{
public:

	CFaultCalc_ZeroSeqCurr(void)
	{
		InitStruct();
	}
	~CFaultCalc_ZeroSeqCurr(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_ZeroSeqCurr *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			Izd=5.0f;				//零序电流 3I0 定值
			If_Ratio=1.05f;			//短路电流: 倍数
			Zf_Mag=1.0f;			//短路阻抗: 幅值, 灵敏角 (计算模型: 定电流)
			Zf_Ang=90.0f;
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
			//计算结果
			for(i=0;i<3;i++)
			{
				Result.Up_PreFault[i].Mag=0.0f;
				Result.Up_PreFault[i].Ang=0.0f;
				Result.Ip_PreFault[i].Mag=0.0f;
				Result.Ip_PreFault[i].Ang=0.0f;
				//
				Result.Up_Fault[i].Mag=0.0f;
				Result.Up_Fault[i].Ang=0.0f;
				Result.Ip_Fault[i].Mag=0.0f;
				Result.Ip_Fault[i].Ang=0.0f;
				//
				Result.Up_TransFault[i].Mag=0.0f;
				Result.Up_TransFault[i].Ang=0.0f;
				Result.Ip_TransFault[i].Mag=0.0f;
				Result.Ip_TransFault[i].Ang=0.0f;
			}
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//结构体复制
	void CopyStructTo(FaultCalc_ZeroSeqCurr *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_ZeroSeqCurr *pSrc, FaultCalc_ZeroSeqCurr *pDst)
	{
		pDst=pSrc;
	}


};
