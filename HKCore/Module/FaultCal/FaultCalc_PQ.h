#pragma once
#include "FaultDef_Calc.h"

//���������ѹ/�����������๦�� P,Q,COS
class CFaultCalc_PQ :
	public FaultCalc_PQ
{
public:

	CFaultCalc_PQ(void)
	{
		InitStruct();
	}
	~CFaultCalc_PQ(void)
	{
	}
public:

	//�ṹ���ʼ��
	void InitStruct(FaultCalc_PQ *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			CalcuMode=0;			//0--����Ʒ�, 1--����Ʒ�
			for(i=0;i<3;i++)
			{
				Up[i].Mag=0.0f;		//�����ѹ: ��ֵ, �Ƕ�
				Up[i].Ang=0.0f;
				//
				Ip[i].Mag=0.0f;		//�������: ��ֵ, �Ƕ�
				Ip[i].Ang=0.0f;
			}
			//
			//������: 3�๦��, P,Q,COS
			Result.P=0.0f;
			Result.Q=0.0f;
			Result.COS=0.0f;
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//�ṹ�帴��
	void CopyStructTo(FaultCalc_PQ *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_PQ *pSrc, FaultCalc_PQ *pDst)
	{
		pDst=pSrc;
	}


};
