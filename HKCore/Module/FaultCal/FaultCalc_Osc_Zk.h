#pragma once
#include "FaultDef_Calc.h"

//������: ��ǰ���������, ������װ�� K ��Ĳ����迹
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

	//�ṹ���ʼ��
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

	//�ṹ�帴��
	void CopyStructTo(FaultCalc_Osc_Zk *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_Osc_Zk *pSrc, FaultCalc_Osc_Zk *pDst)
	{
		pDst=pSrc;
	}


};
