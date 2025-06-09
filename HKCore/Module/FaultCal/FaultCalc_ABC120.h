#pragma once
#include "FaultDef_Calc.h"

//ABC��-�����ת��
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

	//�ṹ���ʼ��
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
	void CopyStructTo(FaultCalc_ABC120 *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_ABC120 *pSrc, FaultCalc_ABC120 *pDst)
	{
		pDst=pSrc;
	}


};
