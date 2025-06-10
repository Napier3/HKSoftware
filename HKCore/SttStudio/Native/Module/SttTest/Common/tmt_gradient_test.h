#pragma once

#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_test_paras_head.h"
//////////////////////////////////////////////////////////////////////////
// �ݱ������ز���
enum GradientChan
{
	U1a = 0,
	U1b,
	U1c,
	Null,
	U1ab=4,
	U1bc,
	U1ca,
	U1abc,
	U2a,
	U2b,
	U2c,
	U2abc,
	I1a,
	I1b,
	I1c,
	I1ab,
	I1bc,
	I1ca,
	I1abc,
	I2a,
	I2b,
	I2c,
	I2abc,
	U_All,
	I_All,
	Udc,
	Uz,
	U2ab,
	U2bc,
	U2ca,
	I2ab,
	I2bc,
	I2ca,
	I1abcAdd=33,
	I2abcAdd,  //a2+b2+c2
	U1abcAdd,
	U2abcAdd,  //va2+vb2+vc2
	FreAll,
	Ia1Ia2Add,//ia+ia2
	Ib1Ib2Add,//ib+ib2
	Ic1Ic2Add,//ic+ic2
	Ia1Ia2Add_Ib1Ib2Add_Ic1Ic2Add,//ia+ia2,ib+ib2,ic+ic2
	Ia1Ia2_Ib1Ib2_Ic1Ic2_Add//ia+ia2+ib+ib2+ic+ic2
};

enum AtsGradientChan
{
	a1=0,
	b1,
	c1,
	a2,
	b2,
	c2,
	ab1,
	bc1,
	ca1,
	ab2,
	bc2,
	ca2,
	abc1,
	abc2,
	abc12
};

enum AtsURampCh //��ѹ�ݱ�ͨ������
{
	URampCh_Ua=0,
	URampCh_Ub,
	URampCh_Uc,
    URampCh_Ua2,
    URampCh_Ub2,
    URampCh_Uc2,
	URampCh_Uab,
	URampCh_Ubc,
	URampCh_Uca,
    URampCh_Uab2,
    URampCh_Ubc2,
    URampCh_Uca2,
    URampCh_Uabc,
    URampCh_Uabc2,
    URampCh_Uabc12
};

enum AtsIRampCh //�����ݱ�ͨ������
{
	IRampCh_Ia=0,
	IRampCh_Ib,
	IRampCh_Ic,
	IRampCh_Ia2,
	IRampCh_Ib2,
	IRampCh_Ic2,
	IRampCh_Iab,
	IRampCh_Ibc,
	IRampCh_Ica,
	IRampCh_Iab2,
	IRampCh_Ibc2,
    IRampCh_Ica2,
    IRampCh_Iabc,
    IRampCh_Iabc2,
    IRampCh_Iabc12
};

enum SequenceGradientVarPhase
{
    VarPhaseV1 = 0,
    VarPhaseV2,
    VarPhaseV0,
    VarPhaseI1,
    VarPhaseI2,
    VarPhaseI0
};

enum ArcRampIndex
{
    Pha_a = 0,
    Phb_b,
    Phc_c,
    Phab_c = 6,
    Phbc_a,
    Phca_b
};

/*********SttGradientTest**********/
#define TMT_GRADIENT_CHANNEL_A    0
#define TMT_GRADIENT_CHANNEL_B    1
#define TMT_GRADIENT_CHANNEL_C    2
#define TMT_GRADIENT_CHANNEL_A2   3
#define TMT_GRADIENT_CHANNEL_B2   4
#define TMT_GRADIENT_CHANNEL_C2   5


#define GradientTest_Base   0   //0-����ģʽ
#define GradientTest_URamp  1	//1-�Զ����Ե�ѹ�ݱ�
#define GradientTest_IRamp  2	//2-�Զ����Ե����ݱ�
#define GradientTest_Base_1 3	//3-�ݱ�,��������<�仯ǰ������ǰ������>

#define TESTSTATE_NONE		0
#define TESTSTATE_SUCCESS	1
#define TESTSTATE_FAIL		2

#define MAX_GRADIENT_COUNT  20


#define Gradient_TestMode_ActValue                              0
#define Gradient_TestMode_ReturnCoef                            1
#define Gradient_TestMode_MaxAngle                              2


typedef struct tmt_gradient_paras
{
public:
	int   m_nChannel;
	int   m_nType;//��ֵ����λ��Ƶ��
	int   m_nChannel2; //add wangtao 20240619 �ڶ�������ͨ�� ����ͬ
	int   m_nType2;//�ڶ���������
	int   m_nStepCnt;//������SttDevice����
	int   m_nStepDirection;//������SttDevice
	int   m_nStepHarm;//������SttDevice
	BOOL  m_bManuDc;//�����ֶ�ʵ��ѡ��ֱ��ģʽ
	int	  m_nVarIndexType;//0=���� 1=��ѹ 2=Ƶ��

	int   m_nSttTestMode;	//0-����ģʽ 1-�Զ����Ե�ѹ�ݱ� 2-�Զ����Ե����ݱ�  3-�ݱ�,��������
	float m_fG1Current;     //���ϵ���ֵ1
	float m_fG2Current;     //���ϵ���ֵ2
	float m_fG1Volt;        //���ϵ�ѹֵ1
	float m_fG2Volt;        //���ϵ�ѹֵ2
	float m_fDiffIAngle;	//����ǰ����ǶȲ�
	float m_fHz;			//����ǰƵ��

	float m_fStart;
	float m_fStop;
	float m_fStep;
	float m_fStart2;//�ڶ�����ʼֵ
	float m_fStop2;//�ڶ�������ֵ
	float m_fStep2;//�ڶ���������
	float m_fStepTime;
	float m_fPrepareTime;
	float m_fPreFaultTime;
    float m_fMarginTime;
	int	  m_nTestMode;	//�������ͣ�0-����ֵ 1-����ϵ�� 2-���������
	float m_fVolAux;		// ����ֱ����ѹ����ģ�⣩
	float m_fCurAux;		// ����ֱ����������ģ�⣩
	int	  m_nBinLogic;			//0-�� 1-��
	float m_fEDU;//�
	float m_fEDI;//�
	float m_fEDUaIaAngle;//�
	float m_fEDFreq;//�
	int   m_nPhaseGradDir;//��λ�ݱ�ķ���(0:��ʱ�뷽��  1:˳ʱ�뷽��)

	//�Զ�������
	tmt_channel m_uiVOL[3][MAX_VOLTAGE_COUNT];	//(����ǰ+����ǰ+����)*����ѹ��
	tmt_channel m_uiCUR[3][MAX_CURRENT_COUNT];

	//������
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-�ǹ���̬���� 1-����̬����
	tmt_BinaryOut m_binOutEx[2][MAX_ExBINARY_COUNT];//0-�ǹ���̬���� 1-����̬����

	//GoosePub
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];

	int		m_nPhaseSet[2];	// �������� ��ѹ����,���ڸ߼�����,�縴ѹ����

	//��ֵ
	float m_fUSet;		//��ѹ��������ֵ
	float m_fISet;		//������������ֵ
	float m_fAngleSet;	//��λ��������ֵ
	float m_fHzSet;		//Ƶ����������ֵ
	float m_fRetCoefSet; //����ϵ������ֵ
	float m_fAngleFSet; //�߽��1����ֵ
	float m_fAngleSSet; //�߽��2����ֵ
	float m_fMaxAngleSet; //�������������ֵ

	//����
	float m_fUActVal_AbsErr; 		//��ѹ����ֵ�������
	float m_fUActVal_RelErr; 		//��ѹ����ֵ������ 		
	long m_nUActVal_ErrorLogic; 			//��ѹ����ֵ����ж��߼� 	
	float m_fIActVal_AbsErr; 		//��������ֵ������� 		
	float m_fIActVal_RelErr; 		//��������ֵ������ 		
	long m_nIActVal_ErrorLogic; 			//��������ֵ����ж��߼� 	
	float m_fAngleActVal_AbsErr; 	//��λ����ֵ������� 		
	float m_fAngleActVal_RelErr; 	//��λ����ֵ������ 		
	long m_nAngleActVal_ErrorLogic; 		//��λ����ֵ����ж��߼� 	
	float m_fHzActVal_AbsErr; 		//Ƶ�ʶ���ֵ������� 		
	float m_fHzActVal_RelErr; 		//Ƶ�ʶ���ֵ������ 		
	long m_nHzActVal_ErrorLogic; 		//Ƶ�ʶ���ֵ����ж��߼� 	
	float m_fRetCoef_AbsErr; 		//����ϵ��������� 		
	float m_fRetCoef_RelErr;			//����ϵ�������� 		
	long m_nRetCoef_ErrorLogic; 		//����ϵ������ж��߼� 	
	float m_fMaxAngle_AbsErr; 		//��������Ǿ������		
	float m_fMaxAngle_RelErr; 		//��������������� 		
	long m_nMaxAngle_ErrorLogic; 	//�������������ж��߼�	
	float m_fAngleF_AbsErr; 			//�߽��1�������			
	float m_fAngleF_RelErr; 			//�߽��1������			
	long m_nAngleF_ErrorLogic; 		//�߽��1����ж��߼� 		
	float m_fAngleS_AbsErr; 			//�߽��2������� 			
	float m_fAngleS_RelErr; 			//�߽��2������ 			
	long m_nAngleS_ErrorLogic; 		//�߽��2����ж��߼�		


public:
	void init()
	{
        m_nSttTestMode = GradientTest_Base;
		m_nChannel = 0;
		m_nType = GRADIENT_AMP;
		m_nChannel2 = 0;
		m_nType2 = GRADIENT_AMP;
		m_fStart = 0;
		m_fStop = 0;
		m_fStep = 0;
		m_fStart2 = 0;
		m_fStop2 = 0;
		m_fStep2 = 0;
		m_fStepTime = 0;
		m_fPrepareTime = 0;
		m_fPreFaultTime = 0;
        m_fMarginTime = 0;
		m_nTestMode = Gradient_TestMode_ActValue;
		m_fVolAux = 0;
		m_fCurAux = 0;
		m_nBinLogic = 0;
		//�仯ǰ�
		m_fEDU = 57.74f;
		m_fEDI = 0;
		m_fEDUaIaAngle = 0;
		m_fEDFreq = 50;
		m_nVarIndexType = 0;

		//����ǰ
		m_fG1Current=0;
		m_fG2Current=0;
		m_fDiffIAngle = 0;
		m_fG1Volt=57.74f;
		m_fG2Volt=57.74f;
		m_fHz=50;
		m_nPhaseGradDir = 0;

		float fAngle[3]={0,-120,120};
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<MAX_VOLTAGE_COUNT; j++)
			{
				m_uiVOL[i][j].Harm[1].fAmp = 0;
				m_uiVOL[i][j].Harm[1].fAngle = fAngle[j%3];
				m_uiVOL[i][j].Harm[1].fFreq = 50;
			}
			for(int j=0; j<MAX_CURRENT_COUNT; j++)
			{
				m_uiCUR[i][j].Harm[1].fAmp = 0;
				m_uiCUR[i][j].Harm[1].fAngle = fAngle[j%3];
				m_uiCUR[i][j].Harm[1].fFreq = 50;
			}
		}

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			for(int j=0;j<2;j++)
			{
				m_binOut[j][i].init();
			}
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binInEx[i].init();
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for(int j=0;j<2;j++)
			{
				m_binOutEx[j][i].init();
			}
		}

		m_nPhaseSet[0] = m_nPhaseSet[1] = 0;

		m_fUSet = 0;		
		m_fISet = 0;		
		m_fAngleSet = 30;	
		m_fHzSet = 50;
		m_fRetCoefSet = 0;	
		m_fAngleFSet = 0;	
		m_fAngleSSet = 0;	
		m_fMaxAngleSet = 0;	

		m_fUActVal_AbsErr = 0;
		m_fUActVal_RelErr = 0;
		m_nUActVal_ErrorLogic = 0;
		m_fIActVal_AbsErr = 0;
		m_fIActVal_RelErr = 0;
		m_nIActVal_ErrorLogic = 0;
		m_fAngleActVal_AbsErr = 0;
		m_fAngleActVal_RelErr = 0;
		m_nAngleActVal_ErrorLogic = 0;
		m_fHzActVal_AbsErr = 0;		
		m_fHzActVal_RelErr = 0;		
		m_nHzActVal_ErrorLogic = 0;		
		m_fRetCoef_AbsErr = 0; 		
		m_fRetCoef_RelErr = 0;		
		m_nRetCoef_ErrorLogic = 0;	
		m_fMaxAngle_AbsErr = 0;		
		m_fMaxAngle_RelErr = 0;		
		m_nMaxAngle_ErrorLogic = 0; 	
		m_fAngleF_AbsErr = 0;		
		m_fAngleF_RelErr = 0;		
		m_nAngleF_ErrorLogic = 0;	
		m_fAngleS_AbsErr = 0; 		
		m_fAngleS_RelErr = 0; 		
		m_nAngleS_ErrorLogic = 0; 	
	}

	void CopyOwn(tmt_gradient_paras* pDest,long nVolChNum,long nCurrChNum)
	{
		pDest->m_nSttTestMode = m_nSttTestMode;
		pDest->m_nChannel = m_nChannel;
		pDest->m_nType = m_nType;
		pDest->m_fStart = m_fStart;
		pDest->m_fStop = m_fStop;
		pDest->m_fStep = m_fStep;
		pDest->m_nChannel2 = m_nChannel2;
		pDest->m_nType2 = m_nType2;
		pDest->m_fStart2 = m_fStart2;
		pDest->m_fStop2 = m_fStop2;
		pDest->m_fStep2 = m_fStep2;
		pDest->m_fStepTime = m_fStepTime;
		pDest->m_fPrepareTime = m_fPrepareTime;
		pDest->m_fPreFaultTime = m_fPreFaultTime;
		pDest->m_fMarginTime = m_fMarginTime;
		pDest->m_nTestMode = m_nTestMode;
		pDest->m_nVarIndexType = m_nVarIndexType;
		pDest->m_fVolAux = m_fVolAux;
		pDest->m_fCurAux = m_fCurAux;
		pDest->m_nBinLogic = m_nBinLogic;
		//�仯ǰ�
		pDest->m_fEDU = m_fEDU;
		pDest->m_fEDI = m_fEDI;
		pDest->m_fEDUaIaAngle = m_fEDUaIaAngle;
		pDest->m_fEDFreq = m_fEDFreq;

		//����ǰ
		pDest->m_fG1Current=m_fG1Current;
		pDest->m_fG2Current=m_fG2Current;
		pDest->m_fDiffIAngle = m_fDiffIAngle;
		pDest->m_fG1Volt=m_fG1Volt;
		pDest->m_fG2Volt=m_fG2Volt;
		pDest->m_fHz=m_fHz;

		for(int i=0; i<3; i++)
		{
			for(int j=0; j<nVolChNum; j++)
			{
				pDest->m_uiVOL[i][j].Harm[1].fAmp = m_uiVOL[i][j].Harm[1].fAmp;
				pDest->m_uiVOL[i][j].Harm[1].fAngle = m_uiVOL[i][j].Harm[1].fAngle;
			}
			for(int j=0; j<nCurrChNum; j++)
			{
				pDest->m_uiCUR[i][j].Harm[1].fAmp = m_uiCUR[i][j].Harm[1].fAmp;
				pDest->m_uiCUR[i][j].Harm[1].fAngle = m_uiCUR[i][j].Harm[1].fAngle;
			}
		}

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			pDest->m_binIn[i] = m_binIn[i];

			for(int j=0;j<2;j++)
			{
				pDest->m_binOut[j][i] = m_binOut[j][i];
			}
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			pDest->m_binInEx[i] = m_binInEx[i];
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for(int j=0;j<2;j++)
			{
				pDest->m_binOutEx[j][i] = m_binOutEx[j][i];
			}
		}

		pDest->m_nPhaseSet[0] = m_nPhaseSet[0];
		pDest->m_nPhaseSet[1] = m_nPhaseSet[1];

		pDest->m_fUSet = m_fUSet;		
		pDest->m_fISet = m_fISet;		
		pDest->m_fAngleSet = m_fAngleSet;	
		pDest->m_fHzSet = m_fHzSet;
		pDest->m_fRetCoefSet = m_fRetCoefSet;	
		pDest->m_fAngleFSet = m_fAngleFSet;	
		pDest->m_fAngleSSet = m_fAngleSSet;	
		pDest->m_fMaxAngleSet = m_fMaxAngleSet;	

		pDest->m_fUActVal_AbsErr = m_fUActVal_AbsErr;
		pDest->m_fUActVal_RelErr = m_fUActVal_RelErr;
		pDest->m_nUActVal_ErrorLogic = m_nUActVal_ErrorLogic;
		pDest->m_fIActVal_AbsErr = m_fIActVal_AbsErr;
		pDest->m_fIActVal_RelErr = m_fIActVal_RelErr;
		pDest->m_nIActVal_ErrorLogic = m_nIActVal_ErrorLogic;
		pDest->m_fAngleActVal_AbsErr = m_fAngleActVal_AbsErr;
		pDest->m_fAngleActVal_RelErr = m_fAngleActVal_RelErr;
		pDest->m_nAngleActVal_ErrorLogic = m_nAngleActVal_ErrorLogic; 
		pDest->m_fHzActVal_AbsErr = m_fHzActVal_AbsErr;	
		pDest->m_fHzActVal_RelErr = m_fHzActVal_RelErr;	
		pDest->m_nHzActVal_ErrorLogic = m_nHzActVal_ErrorLogic;
		pDest->m_fRetCoef_AbsErr = m_fRetCoef_AbsErr; 	
		pDest->m_fRetCoef_RelErr = m_fRetCoef_RelErr;	
		pDest->m_nRetCoef_ErrorLogic = m_nRetCoef_ErrorLogic;
		pDest->m_fMaxAngle_AbsErr = m_fMaxAngle_AbsErr;	
		pDest->m_fMaxAngle_RelErr = m_fMaxAngle_RelErr;	
		pDest->m_nMaxAngle_ErrorLogic = m_nMaxAngle_ErrorLogic;
		pDest->m_fAngleF_AbsErr = m_fAngleF_AbsErr;	
		pDest->m_fAngleF_RelErr = m_fAngleF_RelErr;	
		pDest->m_nAngleF_ErrorLogic = m_nAngleF_ErrorLogic;
		pDest->m_fAngleS_AbsErr = m_fAngleS_AbsErr; 	
		pDest->m_fAngleS_RelErr = m_fAngleS_RelErr; 	
		pDest->m_nAngleS_ErrorLogic = m_nAngleS_ErrorLogic; 
	}

	void SetAllFreq(float fFreqValue)//���ñ仯ǰ������ǰ������̬Ƶ��
	{
		m_fEDFreq = fFreqValue;
		m_fHz = fFreqValue;//����ǰƵ��
	}

	tmt_gradient_paras()	{}
}tmt_GradientParas;

typedef struct tmt_gradient_max_angle_result
{
public:
	float m_fAngleF;	//�߽��1
	float m_fAngleS;	//�߽��2
	float m_fMaxAngle; //���������
	int  m_nAngleF_StepIndex;//�׶˱߽�ǵĵݱ䲽��,��0��ʼ����,0Ϊʼֵ
	long m_nAngleS_StepIndex;//ĩ�˱߽�ǵĵݱ䲽��,��0��ʼ����,0Ϊʼֵ
	int   m_nActF;		//1-���� 0-û����
	int   m_nActS;		//1-���� 0-û����

	void init()
	{
		m_fAngleF = 0;
		m_fAngleS = 0;
		m_fMaxAngle = 0;
		m_nAngleF_StepIndex = 0;
		m_nAngleS_StepIndex = 0;
		m_nActF = 0;
		m_nActS = 0;
	}

	tmt_gradient_max_angle_result(){}
}tmt_GradientMaxAngleResult;

typedef struct tmt_gradient_result
{
public:
	float m_fTripValue;	//����ֵ
	float m_fTripTime;//����ʱ�� zhouhj 20211125 ���ڼ�¼����ʱ��
	float m_fTripValueChl[MAX_BINARYIN_COUNT];//����ֵ��Ĭ����0
	float m_fTripValueExChl[MAX_ExBINARY_COUNT];//0-�ǹ���̬���� 1-����̬����
	float m_fReturnValue;
	float m_fReturnCoef;//����ֵ/����ֵ
	int   m_nAct;		//1-���� 0-û����
	float m_fPhiAngleValue;
	tmt_GradientMaxAngleResult m_oMaxAngle;

	//����
	float m_fTripUErrVal;		 //��ѹ����ֵ���
	float m_fTripIErrVal;		 //��������ֵ���
	float m_fTripHzErrVal;		 //Ƶ�ʶ���ֵ���
	float m_fTripAngleErrVal;	 //��λ����ֵ���
	float m_fRetCoefErrVal;      //����ϵ�����
	float m_fMaxAngleErrVal;     //������������
	float m_fAngleFErrVal;		 //�߽��1���
	float m_fAngleSErrVal;		 //�߽��2���

	void init()
	{
		m_fTripValue = 0;
		m_fTripTime = 0;
		m_fReturnValue = 0;
		m_fReturnCoef = 0;
		m_nAct = 0;
		m_fPhiAngleValue = 0;
		m_oMaxAngle.init();

		m_fTripUErrVal = 0;
		m_fTripIErrVal = 0;
		m_fTripHzErrVal = 0;
		m_fTripAngleErrVal = 0;
		m_fRetCoefErrVal = 0;
		m_fMaxAngleErrVal = 0;
		m_fAngleFErrVal = 0;
		m_fAngleSErrVal = 0;
		
		for(int i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			m_fTripValueChl[i] = 0;
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_fTripValueExChl[i] = 0;
		}
	}

	tmt_gradient_result()	{}
	tmt_StepUI uiResult;
}tmt_GradientResult;

typedef struct tmt_gradient_test
{
public:
	tmt_GradientParas m_oGradientParas;
	tmt_GradientResult m_oResultParas;

	void init()
	{
		m_oGradientParas.init();
		m_oResultParas.init();
	}

	tmt_gradient_test()	{}
}tmt_GradientTest;

struct TestDataCondition
{
	bool bXD;
	float fXD;		//���
	bool bJD;
	float fJD;		//����
	bool bCoeff;	//ϵ��
	float fCoeff;  
	bool bLogicOr;	//�߼���:1 or,0 and,������������ʱʹ��

	TestDataCondition()
	{
		bXD = false;
		fXD = 5;
		bJD = false;
		fJD = -1;
		bCoeff = false;
		fCoeff = -1;
		bLogicOr = true;
	}

	TestDataCondition &operator = (const TestDataCondition &right)
	{
		bXD = right.bXD;
		fXD = right.fXD;
		bJD = right.bJD;
		fJD = right.fJD;
		bCoeff = right.bCoeff;
		fCoeff = right.fCoeff;
		bLogicOr = right.bLogicOr;

		return *this;
	}
};

typedef struct tmt_gradient_paras_ex : public tmt_gradient_paras
{
public:
	TestDataCondition sCondition; //����о�

public:
	void init()
	{
        m_nSttTestMode = GradientTest_Base;

		tmt_gradient_paras::init();
	}

	tmt_gradient_paras_ex()	{}
}tmt_GradientParasEx;

typedef struct tmt_gradient_test_ex : public TMT_PARAS_HEAD
{
public:
	tmt_GradientParasEx m_oGradientParasEx;
	tmt_GradientResult m_oResultParas;

	void init()
	{
		init_head(); 
		strcpy(m_pszMacroID,STT_MACRO_ID_GradientTest);
		m_nSelected = 1;
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oGradientParasEx.init();
		m_oResultParas.init();
	}

	tmt_gradient_test_ex(){	init();}
}tmt_GradientTestEx;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_GradientTest();
void stt_init_paras(tmt_GradientParas *pParas);
void stt_init_results(tmt_GradientParas *pResults);
void stt_xml_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AtsRamp(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_binary_out(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_base(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_GradientParas *pPara, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_GradientTestEx *pParas, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_common(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
