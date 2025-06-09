#pragma once
#include "FaultDef_Calc.h"

//距离保护定值校验计算: 固定定电流模型, 
//计算结果: 三个状态 (故障前, 故障, 故障转换=故障)
class CFaultCalc_Distance :
	public FaultCalc_Distance
{
public:

	CFaultCalc_Distance(void)
	{
		InitStruct();
	}
	~CFaultCalc_Distance(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_Distance *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			Zzd_Mag=1.0f;			//阻抗定值
			Zzd_Ang=90.0f;
			Zf_Ratio=0.95f;			//短路阻抗: 倍数
			FaultIf=5.0f;			//短路电流(计算模型: 定电流)
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
			//计算结果: 故障前, 故障, 故障转换=故障
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
	void CopyStructTo(FaultCalc_Distance *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_Distance *pSrc, FaultCalc_Distance *pDst)
	{
		pDst=pSrc;
	}


};
