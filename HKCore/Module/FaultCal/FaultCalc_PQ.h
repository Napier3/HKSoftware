#pragma once
#include "FaultDef_Calc.h"

//根据三相电压/电流计算三相功率 P,Q,COS
class CFaultCalc_PQ :
	public FaultCalc_PQ
{
public:

	CFaultCalc_PQ(void)
	{
		InitStruct();
	}
	~CFaultCalc_PQ(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_PQ *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			CalcuMode=0;			//0--三表计法, 1--两表计法
			for(i=0;i<3;i++)
			{
				Up[i].Mag=0.0f;		//三相电压: 幅值, 角度
				Up[i].Ang=0.0f;
				//
				Ip[i].Mag=0.0f;		//三相电流: 幅值, 角度
				Ip[i].Ang=0.0f;
			}
			//
			//计算结果: 3相功率, P,Q,COS
			Result.P=0.0f;
			Result.Q=0.0f;
			Result.COS=0.0f;
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//结构体复制
	void CopyStructTo(FaultCalc_PQ *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_PQ *pSrc, FaultCalc_PQ *pDst)
	{
		pDst=pSrc;
	}


};
