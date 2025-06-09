#pragma once
#include "FaultDef_Calc.h"

//功率振荡: 当前发电机角下, 保护安装处 K 点的电压电流有效值
class CFaultCalc_Osc :
	public FaultCalc_Osc
{
public:

	CFaultCalc_Osc(void)
	{
		InitStruct();
	}
	~CFaultCalc_Osc(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_Osc *pSrc=NULL)
	{
		if(pSrc==NULL)
		{

		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//结构体复制
	void CopyStructTo(FaultCalc_Osc *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_Osc *pSrc, FaultCalc_Osc *pDst)
	{
		pDst=pSrc;
	}


};
