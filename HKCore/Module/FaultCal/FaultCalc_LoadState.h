#pragma once
#include "FaultDef_Calc.h"

//�������и���״̬����
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

	//�ṹ���ʼ��
	void InitStruct(FaultCalc_LoadState *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			Us=57.735f;			//���ѹ
			ILoad_Mag=0.0f;		//���ɵ���
			ILoad_Ang=0.0f;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
			//
			//������: 3���ѹ, 3�����
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

	//�ṹ�帴��
	void CopyStructTo(FaultCalc_LoadState *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_LoadState *pSrc, FaultCalc_LoadState *pDst)
	{
		pDst=pSrc;
	}


};
