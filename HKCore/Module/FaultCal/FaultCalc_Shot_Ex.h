#pragma once
#include "FaultDef_Calc.h"

//�����������: �������ģ��(������, ����ѹ, ��Zs), 
//������: ����״̬ (����ǰ, ����, ����ת��)
class CFaultCalc_Shot_Ex :
	public FaultCalc_Shot_Ex
{
public:

	CFaultCalc_Shot_Ex(void)
	{
		InitStruct();
	}
	~CFaultCalc_Shot_Ex(void)
	{
	}
public:

	//�ṹ���ʼ��
	void InitStruct(FaultCalc_Shot_Ex *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			//����ǰ
			Us=57.735f;				//���ѹ
			ILoad_Mag=0.0f;			//���ɵ���
			ILoad_Ang=0.0f;			//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
			//����
			FaultType=FAULT_A;		//��������: �� FaultEnum_FaultType
			FaultDirection=0;		//���Ϸ���: 0--������, 1--������
			FaultUf=0.0f;			//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
			FaultIf=5.0f;			//��·����(����ģ��Ϊ������ʱ��Ч)
			FaultZf_Mag=1.0f;		//��·�迹
			FaultZf_Ang=90.0f;
			//����ת��
			bFaultTrans=0;
			TransFaultType=FAULT_AB;
			TransFaultDirection=0;
			TransFaultUf=0.0f;
			TransFaultIf=5.0f;
			TransFaultZf_Mag=1.0f;
			TransFaultZf_Ang=90.0f;
			//
			CalcuMode=CALCUMODE_IF;		//��·����ģ��: ��� FaultEnum_CalcuMode
			Zs_Mag=0.0f;				//��Դ���迹(��Zsģ����Ч)
			Zs_Ang=0.0f;
			Ks_Mode=0;					//��Դ�迹�����򲹳�ϵ�����÷�ʽ: 0--Ks ����, 1--Ks=KL;
			Ks_Mag=0.0f;				//��Դ���迹�����򲹳�ϵ��(��ֵ,�Ƕ�)
			Ks_Ang=0.0f;
			//
			KL_Mode=KL;					//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
			KL_Mag=0.67f;				//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
			KL_Ang=0.0f;
			KL_KR=0.67f;				//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
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
	void CopyStructTo(FaultCalc_Shot_Ex *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_Shot_Ex *pSrc, FaultCalc_Shot_Ex *pDst)
	{
		pDst=pSrc;
	}


};
