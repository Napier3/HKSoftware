#pragma once
#include "FaultDef_Calc.h"

//������: ��ǰ���������, ������װ�� K ��ĵ�ѹ������Чֵ
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

	//�ṹ���ʼ��
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

	//�ṹ�帴��
	void CopyStructTo(FaultCalc_Osc *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_Osc *pSrc, FaultCalc_Osc *pDst)
	{
		pDst=pSrc;
	}


};
