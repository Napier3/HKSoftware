#pragma once
#include "FaultDef_Calc.h"

//����������ֵУ�����: �̶�������ģ��, 
//������: ����״̬ (����ǰ, ����, ����ת��=����)
class CFaultCalc_OverCurr :
	public FaultCalc_OverCurr
{
public:

	CFaultCalc_OverCurr(void)
	{
		InitStruct();
	}
	~CFaultCalc_OverCurr(void)
	{
	}
public:

	//�ṹ���ʼ��
	void InitStruct(FaultCalc_OverCurr *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			Izd=5.0f;				//������ֵ
			If_Ratio=1.05f;			//��·����: ����
			Zf_Mag=1.0f;			//��·�迹: ��ֵ, ������ (����ģ��: ������)
			Zf_Ang=90.0f;
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
			//������
			for(i=0;i<3;i++)
			{
				Result.Up_PreFault[i].Mag=0.0f;
				Result.Up_PreFault[i].Ang=0.0f;
				Result.Ip_PreFault[i].Mag=0.0f;
				Result.Ip_PreFault[i].Ang=0.0f;
				//
				Result.Up_Fault[i].Mag=0.0f;
				Result.Up_Fault[i].Ang=0.0f;
				Result.Ip_Fault[i].Mag=0.0f;
				Result.Ip_Fault[i].Ang=0.0f;
				//
				Result.Up_TransFault[i].Mag=0.0f;
				Result.Up_TransFault[i].Ang=0.0f;
				Result.Ip_TransFault[i].Mag=0.0f;
				Result.Ip_TransFault[i].Ang=0.0f;
			}
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//�ṹ�帴��
	void CopyStructTo(FaultCalc_OverCurr *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_OverCurr *pSrc, FaultCalc_OverCurr *pDst)
	{
		pDst=pSrc;
	}


};
