#pragma once
#include "FaultDef_Calc.h"

//电铁差动: 根据 Id,Ir 计算两侧所加电流 Iabc,Ixy
class CFaultCalc_Diff5 :
	public FaultCalc_Diff5
{
public:

	CFaultCalc_Diff5(void)
	{
		InitStruct();
	}
	~CFaultCalc_Diff5(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_Diff5 *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			//TestItem=BIASED_DIFFERENTIAL;	//测试项目：见 FaultEnum_Diff_TestItem
			FaultType=DIFF_A;				//测试相别: 见 FaultEnum_Diff_FaultType, 012--ABC,  345--AB,BC,CA;  6--ABC
			Ir=0.5f;				//计算用的 (Ir, Id), (Id, Harm), (Id, GapAng)
			Id=1.0f;
			Harm=0.1f;				//谐波含量: 百分比, 如 0.2(即 20%)
			Harm_Num=2;				//谐波次数
			Harm_Pos=0;				//谐波施加侧: 0--I1侧, 1--I2侧;
			GapAng=60.0f;	
			GapAng_Pos=0;			//间断角施加侧: 0--I1侧, 1--I2侧;
			//
			IdEquation=ID1;			//Id 动作方程索引号: 0,12,34; 见 FaultEnum_Diff_IdEquation
			IrEquation=IR1_ID1;		//Ir 制动方程索引号: ..., 见 FaultEnum_Diff_IrEquation
			K=2.0f;
			KP1=1.0f;				//I1, I2侧的CT变比补偿系数(按三相对称状态计算)	
			KP2=1.0f;
			//
			I1_Ang=0.0f;
			I2_Ang=180.0f;			//测试仪第12组电流基准相位;
			//
			//根据以下参数, 结合 FaultType 计算实际使用的 K1, K2 修正系数, 及 I1,I2 角度
			//
			ProtSort=PROT_TRANS;			//保护分类: 见 FaultEnum_Diff_ProtSort
			TransWindType=TWO_WINDINGS;		//变压器绕组数: 见 FaultEnum_Diff_TransWindType
			//
			//变压器组别(类别): 见 FaultEnum_Diff5_TransGroupMode
			TransGroupMode=DIFF5_BALANCE_Z;
			//
			AdoptWind=H_L;					//参与试验的绕组: 见 FaultEnum_Diff_AdoptWind 
			PhaseCompMode=PHASECOMP_Y;		//保护内部相位校正方式: 见 FaultEnum_Diff_PhaseCompMode
			Y0CompMode=0;					//保护内部零序修正方式: 0--无校正; 1-- Y 侧做 I0 校正
			//
			//计算结果
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
	void CopyStructTo(FaultCalc_Diff5 *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_Diff5 *pSrc, FaultCalc_Diff5 *pDst)
	{
		pDst=pSrc;
	}


};
