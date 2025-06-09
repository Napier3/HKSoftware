#pragma once
#include "FaultDef_Calc.h"

//�����: ���� I1[3], I2[3] �����������������
class CFaultCalc_Diff_IrId :
	public FaultCalc_Diff_IrId
{
public:

	CFaultCalc_Diff_IrId(void)
	{
		InitStruct();
	}
	~CFaultCalc_Diff_IrId(void)
	{
	}
public:

	//�ṹ���ʼ��
	void InitStruct(FaultCalc_Diff_IrId *pSrc=NULL)
	{
		int i;

		if(pSrc==NULL)
		{
			for(i=0;i<3;i++)
			{
				I1[i].Mag=0.0f;		//I1: ABC
				I1[i].Ang=0.0f;
				I2[i].Mag=0.0f;		//I2: abc
				I2[i].Ang=0.0f;
			}
			//
			IdEquation=ID1;			//Id ��������������: 0,12,34; �� FaultEnum_Diff_IdEquation
			IrEquation=IR1_ID1;		//Ir �ƶ�����������: ..., �� FaultEnum_Diff_IrEquation
			K=2.0f;
			KP1=1.0f;				//I1, I2���CT��Ȳ���ϵ��(������Գ�״̬����)	
			KP2=1.0f;
			//
			//��ѹ������(��������), ����ȷ����ѹ���ӵ� m_nClock
			ProtSort=PROT_TRANS;			//��������: �� FaultEnum_Diff_ProtSort
			TransWindType=TWO_WINDINGS;		//��ѹ��������: �� FaultEnum_Diff_TransWindType
			TransGroupMode=YD_11;			//��ѹ���������: �� FaultEnum_Diff_TransGroupMode_...
			AdoptWind=H_L;					//�������������: �� FaultEnum_Diff_AdoptWind 
			PhaseCompMode=PHASECOMP_Y;		//�����ڲ���λУ����ʽ: �� FaultEnum_Diff_PhaseCompMode
			Y0CompMode=0;					//�����ڲ�����������ʽ: 0--��У��; 1-- Y ���� I0 У��
			//
			//������
			for(i=0;i<3;i++)
			{
				Result.Id[i]=0.0f;
				Result.Ir[i]=0.0f;
			}
		}
		else
		{
			CopyStruct(pSrc,this);
		}
	}

	//�ṹ�帴��
	void CopyStructTo(FaultCalc_Diff_IrId *pDst)
	{
		CopyStruct(this,pDst);
	}

	//�ṹ�帴��
	void CopyStruct(FaultCalc_Diff_IrId *pSrc, FaultCalc_Diff_IrId *pDst)
	{
		pDst=pSrc;
	}


};
