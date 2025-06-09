#pragma once
#include "FaultDef_Calc.h"

//功率振荡: 当前发电机角下, 保护安装处 K 点的测量阻抗
class CFaultCalc_Osc_Zk :
	public FaultCalc_Osc_Zk
{
public:

	CFaultCalc_Osc_Zk(void)
	{
		InitStruct();
	}
	~CFaultCalc_Osc_Zk(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_Osc_Zk *pSrc=NULL)
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
	void CopyStructTo(FaultCalc_Osc_Zk *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_Osc_Zk *pSrc, FaultCalc_Osc_Zk *pDst)
	{
		pDst=pSrc;
	}


};
