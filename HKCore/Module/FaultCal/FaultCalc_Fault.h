#pragma once
#include "FaultDef_Calc.h"

//故障计算: 常规计算模型(定电流, 定电压, 定Zs)
class CFaultCalc_Fault :
	public FaultCalc_Fault
{
public:

	CFaultCalc_Fault(void)
	{
		InitStruct();
	}
	~CFaultCalc_Fault(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_Fault *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			Us=57.735f;				//额定电压
			ILoad_Mag=0.0f;			//负荷电流
			ILoad_Ang=0.0f;			//负荷电流角度(相对于对应相的电压, +为超前)
			//
			FaultType=FAULT_A;		//故障类型: 见 FaultEnum_FaultType
			FaultDirection=0;		//故障方向: 0--正方向, 1--反方向
			FaultUf=0.0f;			//短路电压(计算模型为定电压时有效)
			FaultIf=5.0f;			//短路电流(计算模型为定电流时有效)
			FaultZf_Mag=1.0f;		//短路阻抗
			FaultZf_Ang=90.0f;
			//
			CalcuMode=CALCUMODE_IF;		//短路计算模型: 详见 FaultEnum_CalcuMode
			Zs_Mag=0.0f;				//电源侧阻抗(定Zs模型有效)
			Zs_Ang=0.0f;
			Ks_Mag=0.0f;				//电源侧阻抗的零序补偿系数(幅值,角度)
			Ks_Ang=0.0f;
			//
			KL_Mode=KL;					//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
			KL_Mag=0.67f;				//线路阻抗的零序补偿系数(KL 方式有效)
			KL_Ang=0.0f;
			KL_KR=0.67f;				//线路阻抗的零序补偿系数(KR,KX 方式有效)
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
	void CopyStructTo(FaultCalc_Fault *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_Fault *pSrc, FaultCalc_Fault *pDst)
	{
		pDst=pSrc;
	}


};
