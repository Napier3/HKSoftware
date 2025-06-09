#pragma once
#include "FaultDef_Calc.h"

//正常运行负荷状态计算
class CFaultCalc_LoadState :
	public FaultCalc_LoadState
{
public:

	CFaultCalc_LoadState(void)
	{
		InitStruct(NULL);
	}
	~CFaultCalc_LoadState(void)
	{
	}
public:

	//结构体初始化
	void InitStruct(FaultCalc_LoadState *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			Us=57.735f;			//额定电压
			ILoad_Mag=0.0f;		//负荷电流
			ILoad_Ang=0.0f;		//负荷电流角度(相对于对应相的电压, +为超前)
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
	void CopyStructTo(FaultCalc_LoadState *pDst)
	{
		CopyStruct(this,pDst);
	}

	//结构体复制
	void CopyStruct(FaultCalc_LoadState *pSrc, FaultCalc_LoadState *pDst)
	{
		pDst=pSrc;
	}


};
