#pragma once
#include "FaultDef_Calc.h"

//ABC相-序分量转换
class CFaultCalc_ABC120 :
	public FaultCalc_ABC120
{
public:

	CFaultCalc_ABC120(void)
	{
		InitStruct();
	}
	~CFaultCalc_ABC120(void)
	{
	}

public:

	//结构体初始化
	void InitStruct(FaultCalc_ABC120 *pSrc=NULL)
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
	void CopyStructTo(FaultCalc_ABC120 *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_ABC120 *pSrc, FaultCalc_ABC120 *pDst)
	{
		pDst=pSrc;
	}


};
