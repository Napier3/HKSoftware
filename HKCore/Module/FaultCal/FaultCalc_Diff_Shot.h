#pragma once
#include "FaultDef_Calc.h"

//�����: �����
class CFaultCalc_Diff_Shot :
	public FaultCalc_Diff_Shot
{
public:

	CFaultCalc_Diff_Shot(void)
	{
		InitStruct();
	}
	~CFaultCalc_Diff_Shot(void)
	{
	}
public:

	//�ṹ���ʼ��
	void InitStruct(FaultCalc_Diff_Shot *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			//��ѹ������(��������), ����ȷ����ѹ���ӵ� m_nClock
			ProtSort=PROT_TRANS;			//��������: �� FaultEnum_Diff_ProtSort
			TransWindType=TWO_WINDINGS;		//��ѹ��������: �� FaultEnum_Diff_TransWindType
			TransGroupMode=YD_11;			//��ѹ���������: �� FaultEnum_Diff_TransGroupMode_...
			AdoptWind=H_L;					//�������������: �� FaultEnum_Diff_AdoptWind 
			//
			I1_bY0=1;				//1--Y0; 0--Y �� d
			I2_bY0=0;
			PowerPos=0;				//��Դλ��: 0--I1��, 1--I2��;
			FaultPos=1;				//���ϵ�λ��: 0--I1��,     1--I2��
			FaultArea=0;			//            0--���ڹ���; 1--�������
			FaultType=DIFF_AB;		//��������: �� FaultEnum_Diff_FaultType, 012--ABC,  345--AB,BC,CA;  6--ABC
			FaultIp=1.0f;			//���ϵ���: CT ���β�ֵ
			DirectionMode=0;		//��������������: 0--Ԫ���ڲ�����Ϊ��;  1--Ԫ���ⲿ����Ϊ��
			//
			//������, ֻ��Ҫ���е� 6 ·��������
			for(i=0;i<6;i++)
			{
				Result.Ip[i].Mag=0.0f;			//��������
				Result.Ip[i].Ang=0.0f;
				//
				Result.Ip_Harm[i].Mag=0.0f;		//г���ƶ�: ����г������
				Result.Ip_Harm[i].Ang=0.0f;
				//
				Result.GapAng[i]=0.0f;			//��Ͻ��ƶ�: ��Ͻ�
			}
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//�ṹ�帴��
	void CopyStructTo(FaultCalc_Diff_Shot *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_Diff_Shot *pSrc, FaultCalc_Diff_Shot *pDst)
	{
		pDst=pSrc;
	}


};
