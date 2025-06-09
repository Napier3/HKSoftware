#pragma once
#include "FaultDef_Calc.h"

//整组试验计算: 常规计算模型(定电流, 定电压, 定Zs), 
//计算结果: 三个状态 (故障前, 故障, 故障转换)
class CFaultCalc_Shot_Ex :
	public FaultCalc_Shot_Ex
{
public:

	CFaultCalc_Shot_Ex(void)
	{
		InitStruct();
	}
	~CFaultCalc_Shot_Ex(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_Shot_Ex *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			//故障前
			Us=57.735f;				//额定电压
			ILoad_Mag=0.0f;			//负荷电流
			ILoad_Ang=0.0f;			//负荷电流角度(相对于对应相的电压, +为超前)
			//故障
			FaultType=FAULT_A;		//故障类型: 见 FaultEnum_FaultType
			FaultDirection=0;		//故障方向: 0--正方向, 1--反方向
			FaultUf=0.0f;			//短路电压(计算模型为定电压时有效)
			FaultIf=5.0f;			//短路电流(计算模型为定电流时有效)
			FaultZf_Mag=1.0f;		//短路阻抗
			FaultZf_Ang=90.0f;
			//故障转换
			bFaultTrans=0;
			TransFaultType=FAULT_AB;
			TransFaultDirection=0;
			TransFaultUf=0.0f;
			TransFaultIf=5.0f;
			TransFaultZf_Mag=1.0f;
			TransFaultZf_Ang=90.0f;
			//
			CalcuMode=CALCUMODE_IF;		//短路计算模型: 详见 FaultEnum_CalcuMode
			Zs_Mag=0.0f;				//电源侧阻抗(定Zs模型有效)
			Zs_Ang=0.0f;
			Ks_Mode=0;					//电源阻抗的零序补偿系数设置方式: 0--Ks 输入, 1--Ks=KL;
			Ks_Mag=0.0f;				//电源侧阻抗的零序补偿系数(幅值,角度)
			Ks_Ang=0.0f;
			//
			KL_Mode=KL;					//线路阻抗的零序补偿系数设置方式: 0--Kl, 1--KR,KX
			KL_Mag=0.67f;				//线路阻抗的零序补偿系数(KL 方式有效)
			KL_Ang=0.0f;
			KL_KR=0.67f;				//线路阻抗的零序补偿系数(KR,KX 方式有效)
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
	void CopyStructTo(FaultCalc_Shot_Ex *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_Shot_Ex *pSrc, FaultCalc_Shot_Ex *pDst)
	{
		pDst=pSrc;
	}


};
