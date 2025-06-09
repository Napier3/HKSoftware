#pragma once
#include "FaultDef_Calc.h"

//���ϼ���: ��Ƶ�仯������ģ��: �̶�������ģ��(ר��)
class CFaultCalc_GPFault :
	public FaultCalc_GPFault
{
public:

	CFaultCalc_GPFault(void)
	{
		InitStruct();
	}
	~CFaultCalc_GPFault(void)
	{
	}
public:

	//�ṹ���ʼ��
	void InitStruct(FaultCalc_GPFault *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			Zzd_Mag=1.0f;			//�����迹
			Zzd_Ang=90.0f;
			m=0.9f;					//У���: m=0.9, 1.1, ...
			FaultIf=5.0f;			//��·����
			FaultType=FAULT_A;		//��������: �� FaultEnum_FaultType
			FaultDirection=0;		//���Ϸ���: 0--������, 1--������
			//
			Us=57.735f;				//���ѹ
			ILoad_Mag=0.0f;			//���ɵ���
			ILoad_Ang=0.0f;			//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
			//
			KL_Mode=KL;				//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
			KL_Mag=0.67f;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
			KL_Ang=0.0f;
			KL_KR=0.67f;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
			KL_KX=0.67f;
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
	void CopyStructTo(FaultCalc_GPFault *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_GPFault *pSrc, FaultCalc_GPFault *pDst)
	{
		pDst=pSrc;
	}


};
