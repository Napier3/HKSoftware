#pragma once
#include "FaultDef_Calc.h"
#include <math.h>

//�����: ����ϵ�� KP123 ��������
class CFaultCalc_Diff_KP :
	public FaultCalc_Diff_KP
{
public:

	CFaultCalc_Diff_KP(void)
	{
		InitStruct();
	}
	~CFaultCalc_Diff_KP(void)
	{
	}
public:

	//�ṹ���ʼ��
	void InitStruct(FaultCalc_Diff_KP *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			//��������
			ProtSort=PROT_TRANS;	//��������: �� FaultEnum_Diff_ProtSort
			//����ģʽ
			CalcuMode=0;			//��������ϵ�����㷽ʽ: 0--���ݶ��ѹ��CT��ȹ�������ѹ��
			//                      1--���ݶ����In'��������ѹ��
			//                      2--��ôֵ����(RCS-978, �����In'�ĵ���)
			Sn=180.0f;				//��ѹ�������, MVA
			for(i=0;i<3;i++)
			{
				switch(i)
				{
				case 0:
					Un[i]=220.0f;	//KV
					CT[i]=240.0f;	//1200:5
					break;
				case 1:
					Un[i]=115.0f;	//KV
					CT[i]=250.0f;	//1250:5
					break;
				case 2:
					Un[i]=10.5f;	//KV
					CT[i]=600.0f;	//3000:5
					break;
				}
				In[i]=(float)(1000.0f*Sn/(sqrt(3.0)*Un[i])/CT[i]);
			}
			//
			//������
			Result.KPH=1.0000f;
			Result.KPM=0.5445f;
			Result.KPL=0.1193f;
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//�ṹ�帴��
	void CopyStructTo(FaultCalc_Diff_KP *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_Diff_KP *pSrc, FaultCalc_Diff_KP *pDst)
	{
		pDst=pSrc;
	}


};
