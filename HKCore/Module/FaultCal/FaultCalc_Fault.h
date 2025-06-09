#pragma once
#include "FaultDef_Calc.h"

//���ϼ���: �������ģ��(������, ����ѹ, ��Zs)
class CFaultCalc_Fault :
	public FaultCalc_Fault
{
public:

	CFaultCalc_Fault(void)
	{
		InitStruct();
	}
	~CFaultCalc_Fault(void)
	{
	}
public:

	//�ṹ���ʼ��
	void InitStruct(FaultCalc_Fault *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			Us=57.735f;				//���ѹ
			ILoad_Mag=0.0f;			//���ɵ���
			ILoad_Ang=0.0f;			//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
			//
			FaultType=FAULT_A;		//��������: �� FaultEnum_FaultType
			FaultDirection=0;		//���Ϸ���: 0--������, 1--������
			FaultUf=0.0f;			//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
			FaultIf=5.0f;			//��·����(����ģ��Ϊ������ʱ��Ч)
			FaultZf_Mag=1.0f;		//��·�迹
			FaultZf_Ang=90.0f;
			//
			CalcuMode=CALCUMODE_IF;		//��·����ģ��: ��� FaultEnum_CalcuMode
			Zs_Mag=0.0f;				//��Դ���迹(��Zsģ����Ч)
			Zs_Ang=0.0f;
			Ks_Mag=0.0f;				//��Դ���迹�����򲹳�ϵ��(��ֵ,�Ƕ�)
			Ks_Ang=0.0f;
			//
			KL_Mode=KL;					//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
			KL_Mag=0.67f;				//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
			KL_Ang=0.0f;
			KL_KR=0.67f;				//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
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
	void CopyStructTo(FaultCalc_Fault *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_Fault *pSrc, FaultCalc_Fault *pDst)
	{
		pDst=pSrc;
	}


};
