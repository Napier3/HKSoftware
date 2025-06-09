#pragma once
#include "FaultDef_Calc.h"
#include <math.h>

//差动计算: 补偿系数 KP123 辅助计算
class CFaultCalc_Diff_KP :
	public FaultCalc_Diff_KP
{
public:

	CFaultCalc_Diff_KP(void)
	{
		InitStruct();
	}
	~CFaultCalc_Diff_KP(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_Diff_KP *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			//保护设置
			ProtSort=PROT_TRANS;	//保护分类: 见 FaultEnum_Diff_ProtSort
			//计算模式
			CalcuMode=0;			//电流补偿系数计算方式: 0--根据额定电压和CT变比归算至高压侧
			//                      1--根据额定电流In'归算至高压侧
			//                      2--标么值计算(RCS-978, 额定电流In'的倒数)
			Sn=180.0f;				//变压器额定容量, MVA
			for(i=0;i<3;i++)
			{
				switch(i)
				{
				case 0:
					Un[i]=220.0f;	//KV
					CT[i]=240.0f;	//1200:5
					break;
				case 1:
					Un[i]=115.0f;	//KV
					CT[i]=250.0f;	//1250:5
					break;
				case 2:
					Un[i]=10.5f;	//KV
					CT[i]=600.0f;	//3000:5
					break;
				}
				In[i]=(float)(1000.0f*Sn/(sqrt(3.0)*Un[i])/CT[i]);
			}
			//
			//计算结果
			Result.KPH=1.0000f;
			Result.KPM=0.5445f;
			Result.KPL=0.1193f;
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//结构体复制
	void CopyStructTo(FaultCalc_Diff_KP *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_Diff_KP *pSrc, FaultCalc_Diff_KP *pDst)
	{
		pDst=pSrc;
	}


};
