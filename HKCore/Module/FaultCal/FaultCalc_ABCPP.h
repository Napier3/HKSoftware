#pragma once
#include "FaultDef_Calc.h"

//ABC相-线分量转换
class CFaultCalc_ABCPP :
	public FaultCalc_ABCPP
{
public:

	CFaultCalc_ABCPP(void)
	{
		InitStruct();
	}
	~CFaultCalc_ABCPP(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_ABCPP *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			for(i=0;i<3;i++)
			{
				Up[i].Mag=0.0f;
				Up[i].Ang=0.0f;
			}

			//计算结果
			for(i=0;i<3;i++)
			{
				Result.Up[i].Mag=0.0f;
				Result.Up[i].Ang=0.0f;
			}
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//结构体复制
	void CopyStructTo(FaultCalc_ABCPP *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_ABCPP *pSrc, FaultCalc_ABCPP *pDst)
	{
		pDst=pSrc;
	}


};
