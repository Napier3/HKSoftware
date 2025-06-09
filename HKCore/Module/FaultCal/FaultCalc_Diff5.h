#pragma once
#include "FaultDef_Calc.h"

//�����: ���� Id,Ir �����������ӵ��� Iabc,Ixy
class CFaultCalc_Diff5 :
	public FaultCalc_Diff5
{
public:

	CFaultCalc_Diff5(void)
	{
		InitStruct();
	}
	~CFaultCalc_Diff5(void)
	{
	}
public:

	//�ṹ���ʼ��
	void InitStruct(FaultCalc_Diff5 *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			//TestItem=BIASED_DIFFERENTIAL;	//������Ŀ���� FaultEnum_Diff_TestItem
			FaultType=DIFF_A;				//�������: �� FaultEnum_Diff_FaultType, 012--ABC,  345--AB,BC,CA;  6--ABC
			Ir=0.5f;				//�����õ� (Ir, Id), (Id, Harm), (Id, GapAng)
			Id=1.0f;
			Harm=0.1f;				//г������: �ٷֱ�, �� 0.2(�� 20%)
			Harm_Num=2;				//г������
			Harm_Pos=0;				//г��ʩ�Ӳ�: 0--I1��, 1--I2��;
			GapAng=60.0f;	
			GapAng_Pos=0;			//��Ͻ�ʩ�Ӳ�: 0--I1��, 1--I2��;
			//
			IdEquation=ID1;			//Id ��������������: 0,12,34; �� FaultEnum_Diff_IdEquation
			IrEquation=IR1_ID1;		//Ir �ƶ�����������: ..., �� FaultEnum_Diff_IrEquation
			K=2.0f;
			KP1=1.0f;				//I1, I2���CT��Ȳ���ϵ��(������Գ�״̬����)	
			KP2=1.0f;
			//
			I1_Ang=0.0f;
			I2_Ang=180.0f;			//�����ǵ�12�������׼��λ;
			//
			//�������²���, ��� FaultType ����ʵ��ʹ�õ� K1, K2 ����ϵ��, �� I1,I2 �Ƕ�
			//
			ProtSort=PROT_TRANS;			//��������: �� FaultEnum_Diff_ProtSort
			TransWindType=TWO_WINDINGS;		//��ѹ��������: �� FaultEnum_Diff_TransWindType
			//
			//��ѹ�����(���): �� FaultEnum_Diff5_TransGroupMode
			TransGroupMode=DIFF5_BALANCE_Z;
			//
			AdoptWind=H_L;					//�������������: �� FaultEnum_Diff_AdoptWind 
			PhaseCompMode=PHASECOMP_Y;		//�����ڲ���λУ����ʽ: �� FaultEnum_Diff_PhaseCompMode
			Y0CompMode=0;					//�����ڲ�����������ʽ: 0--��У��; 1-- Y ���� I0 У��
			//
			//������
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
	void CopyStructTo(FaultCalc_Diff5 *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_Diff5 *pSrc, FaultCalc_Diff5 *pDst)
	{
		pDst=pSrc;
	}


};
