#pragma once
#include "FaultDef_Calc.h"

//ABC��-�߷���ת��
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

	//�ṹ���ʼ��
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

			//������
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

	//�ṹ�帴��
	void CopyStructTo(FaultCalc_ABCPP *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_ABCPP *pSrc, FaultCalc_ABCPP *pDst)
	{
		pDst=pSrc;
	}


};
