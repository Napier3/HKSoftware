#pragma once
#include "FaultDef_Calc.h"

//差动计算: 根据 I1[3], I2[3] 计算三相差流和制流
class CFaultCalc_Diff_IrId :
	public FaultCalc_Diff_IrId
{
public:

	CFaultCalc_Diff_IrId(void)
	{
		InitStruct();
	}
	~CFaultCalc_Diff_IrId(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_Diff_IrId *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			for(i=0;i<3;i++)
			{
				I1[i].Mag=0.0f;		//I1: ABC
				I1[i].Ang=0.0f;
				I2[i].Mag=0.0f;		//I2: abc
				I2[i].Ang=0.0f;
			}
			//
			IdEquation=ID1;			//Id 动作方程索引号: 0,12,34; 见 FaultEnum_Diff_IdEquation
			IrEquation=IR1_ID1;		//Ir 制动方程索引号: ..., 见 FaultEnum_Diff_IrEquation
			K=2.0f;
			KP1=1.0f;				//I1, I2侧的CT变比补偿系数(按三相对称状态计算)	
			KP2=1.0f;
			//
			//变压器接线(保护设置), 用于确定变压器钟点 m_nClock
			ProtSort=PROT_TRANS;			//保护分类: 见 FaultEnum_Diff_ProtSort
			TransWindType=TWO_WINDINGS;		//变压器绕组数: 见 FaultEnum_Diff_TransWindType
			TransGroupMode=YD_11;			//变压器接线组别: 见 FaultEnum_Diff_TransGroupMode_...
			AdoptWind=H_L;					//参与试验的绕组: 见 FaultEnum_Diff_AdoptWind 
			PhaseCompMode=PHASECOMP_Y;		//保护内部相位校正方式: 见 FaultEnum_Diff_PhaseCompMode
			Y0CompMode=0;					//保护内部零序修正方式: 0--无校正; 1-- Y 侧做 I0 校正
			//
			//计算结果
			for(i=0;i<3;i++)
			{
				Result.Id[i]=0.0f;
				Result.Ir[i]=0.0f;
			}
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//结构体复制
	void CopyStructTo(FaultCalc_Diff_IrId *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_Diff_IrId *pSrc, FaultCalc_Diff_IrId *pDst)
	{
		pDst=pSrc;
	}


};
