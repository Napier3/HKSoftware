#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_manu_test.h"
#include"../../../SttTestBase/SttXmlSerialize.h"

// �ֶ�������ز���
typedef struct tmt_manuImped_gradient
{
	int		nMode;			// 0:ʼֵ-��ֵ  1:ʼֵ-��ֵ-ʼֵ
	float		fStep;			//�仯����
	float		fTrigDelay;	//��������ʱ
	float		fStart;			//�仯ʼֵ;
	float		fEnd;				//�仯��ֵ
	float		fStepTime;	//�仯ʱ��

	void init()
	{
		nMode = 0;		
		fTrigDelay = 0;
		fStep = 0.5;
		fStart = 1;
		fEnd = 10;
		fStepTime = 1;
	}

public:
    tmt_manuImped_gradient()
    {
        init();
    }
} tmt_ManuImpedGradient;


typedef struct tmt_manualImped_paras
{
public:
	//��������
	int		 m_nCalMode;				// �迹���� Add����ģ�ͣ�0-������ 1-����ѹ 2-�̶�ϵͳ���迹
	double  m_fSCCurrent;				// ��·���� 
	double  m_fSCVoltage;				// ��·��ѹ 
	double	m_fSZSAmp;					// ZS -Amp
	double	m_fSZSAngle;				// ZS -Angle

	int		m_nOffsetsMode;			// ���򲹳�ϵ����ģʽ
	float		m_fAmplitudeOrKr;		// Ko��Z0,Z1�� ��ֵ��Kr,Kx 
	float		m_fPhaseOrKx;				// Ko��Z0,Z1�� ��λ��Kr,Kx 

	int		m_nFaultType;				// ��������(0:A��ӵ�;1:B��ӵ�;2:C��ӵ�;3:AB��·;4:BC��·;5:CA��·;6:AB�ӵض�·;7:BC�ӵض�·;8:CA�ӵض�·;9:�����·;) 	
	int		m_nImped;					// �迹����ѡ��
	float		m_fZAmp;						// ��·�迹��ֵ
	float		m_fZAngle;					// �迹��
	float		m_fR;
	float		m_fX;

	int		m_nFirstMode;				// ����ѡ��1- Z R X 
	int		m_nSecondMode;			// ����ѡ��2 - ��ֵ ��λ	
	BOOL		m_bAuto;						// �Զ��ݱ�//20240624 suyang �޸�ΪBOOL����
	int		m_bMutation;				// ͻ��������
	int		m_bLockChanged;		// lock mark
	float		m_fPrepareTime;			//��̬ʱ��(�ò���Ϊ����ǰ����ʱ��,Ҳ�����仯ǰʱ��,���ݱ��෢���ݱ�ǰ�ĸ���ʱ��,���������迹�߽�,�����Ƕȵ�,һ���غ�բ����١����벻�øò���)
	float		m_fPreFaultTime;			//����ǰʱ��(����ǰ����ʱ��,ÿ�ι���ǰ�Ĺ��ϸ���ʱ��)

	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

	//������
	int		m_nBinLogic;			//0-�� 1-��
	tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];
	tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������
	tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������

	tmt_ManuImpedGradient m_manuImpedGradient;
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];//GoosePub

	//����ֵ
	float m_fTimeSet;   //��������ʱ��
	float m_fUSet;		//��ѹ��������ֵ
	float m_fISet;		//������������ֵ
	float m_fAngleSet;	//��λ��������ֵ
	//float m_fHzSet;		//Ƶ����������ֵ
	float m_fImpSet;		//�迹��������ֵ
	float m_fRetCoefSet; //����ϵ������ֵ

	//����
	float m_fTimeValue_AbsErr;      //����ʱ��ֵ�������
	float m_fTimeValue_RelErr;      //����ʱ��ֵ������
	long m_nTimeValue_ErrorLogic; 	//����ʱ������ж��߼�
	float m_fUActVal_AbsErr; 		//��ѹ����ֵ�������
	float m_fUActVal_RelErr; 		//��ѹ����ֵ������
	long m_nUActVal_ErrorLogic; 	//��ѹ����ֵ����ж��߼�
	float m_fIActVal_AbsErr; 		//��������ֵ�������
	float m_fIActVal_RelErr; 		//��������ֵ������
	long m_nIActVal_ErrorLogic; 	//��������ֵ����ж��߼�
	float m_fAngleActVal_AbsErr; 	//��λ����ֵ�������
	float m_fAngleActVal_RelErr; 	//��λ����ֵ������
	long m_nAngleActVal_ErrorLogic; //��λ����ֵ����ж��߼�
	//float m_fHzActVal_AbsErr; 		//Ƶ�ʶ���ֵ�������
	//float m_fHzActVal_RelErr; 		//Ƶ�ʶ���ֵ������
	//long m_nHzActVal_ErrorLogic; 	//Ƶ�ʶ���ֵ����ж��߼�
	float m_fImpValue_AbsErr;//�迹����ֵ�������
	float m_fImpValue_RelErr;//�迹����ֵ������
	long m_nImpValue_ErrorLogic; 	//�迹����ֵ����ж��߼�
	float m_fRetCoef_AbsErr; 		//����ϵ���������
	float m_fRetCoef_RelErr;		//����ϵ��������
	long m_nRetCoef_ErrorLogic; 	//����ϵ������ж��߼�

	void init()
	{		
		//�迹����
		 m_nCalMode = 0;//  0:�迹�������� 1:�迹������ѹ 2:�迹���̶�ϵͳ���迹 ��Ĭ��Ϊ0����������
		 m_fSCCurrent = 5.000f;		//��·����
		 m_fSCVoltage = 10.000f;		//��·��ѹ
		 m_fSZSAmp = 1.000f;	
		 m_fSZSAngle = 90.000f;

		//���򲹳�ϵ��
		 m_nOffsetsMode = 0;//���򲹳�ϵ����ģʽ
		 m_fAmplitudeOrKr = 0.000f;
		 m_fPhaseOrKx	=  0.000f;
		
		 m_nFaultType = 0;//��������-A��ӵ�	 		 
		 m_nImped = 0;//�迹����ѡ��
		 m_fZAmp = 1.000f;			
		 m_fZAngle = 90.000f;	
		 m_fR = 0.000f;	
		 m_fX = 1.000f;	

		 m_nFirstMode = 0;//����ѡ��1- Z R X 
		 m_nSecondMode = 0;//����ѡ��2 - ��ֵ ��λ
		 m_bAuto = false;
		 m_bMutation = false;		 
		 m_bLockChanged = false;
		 m_fPrepareTime = 0.000f;		//��̬ʱ��
		 m_fPreFaultTime = 0.000f;		//����ǰʱ��
		 float fAngle[3] = {0, -120.0, 120.0};
		 m_manuImpedGradient.init();

		 for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
		 {
			 m_uiVOL[i].Harm[0].fAmp = 0;
			 m_uiCUR[i].Harm[0].fAmp = 0;
			 m_uiVOL[i].Harm[1].fAmp = 0;
			 m_uiCUR[i].Harm[1].fAmp = 0;

			 for(int harm = 0; harm < MAX_HARM_COUNT; harm++)
			 {
				 m_uiVOL[i].Harm[harm].init();
				 m_uiCUR[i].Harm[harm].init();
			 }

			 m_uiVOL[i].Harm[1].fAngle = m_uiCUR[i].Harm[1].fAngle = fAngle[i % 3];
			 m_uiVOL[i].Harm[1].fFreq = m_uiCUR[i].Harm[1].fFreq = 50;
		 }

		 for(int j = 0; j < MAX_BINARYIN_COUNT; j++)
		 {
			 m_binIn[j].nSelect = 0;
			 m_binIn[j].nTrigMode = 0;

#ifndef _PSX_QT_LINUX_
			 if(j < g_nBinCount)
			 {
				 m_binIn[j].nSelect = 1;
			 }
#endif
		 }

		 for(int j = 0; j < MAX_BINARYOUT_COUNT; j++)
		 {
			 m_binOut[j].nState = 0;
			 m_binOut[j].nMode = 0;
			 m_binOut[j].fTimeTrig = 0;
			 m_binOut[j].fHoldTime = 0;
		 }

		 for(int j = 0; j < g_nBinExCount && j < MAX_ExBINARY_COUNT; j++)
		 {
			 m_binInEx[j].nSelect = 0;//Ĭ���������벻ѡ��
			 m_binInEx[j].nTrigMode = 0;
		 }

		 for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
		 {
			 m_binOutEx[j].nState = 0;//Ĭ����������ȫ�Ͽ�
			 m_binOutEx[j].nMode = 0;
			 m_binOutEx[j].fTimeTrig = 0;
			 m_binOutEx[j].fHoldTime = 0;
		 }

		 for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
		 {
			 m_oGoosePub[nIndex].init();
		 }

		 m_fTimeSet = 0;
		 m_fUSet = 0;
		 m_fISet = 0;
		 m_fAngleSet = 0;
		 //m_fHzSet=0;
		 m_fImpSet = 0;
		 m_fRetCoefSet = 0;
		 m_fTimeValue_AbsErr = 0.001f;
		 m_fTimeValue_RelErr = 0.1f;
		 m_nTimeValue_ErrorLogic = 0;
		 m_fUActVal_AbsErr = 0.001f;
		 m_fUActVal_RelErr = 0.1f;
		 m_nUActVal_ErrorLogic = 0;
		 m_fIActVal_AbsErr = 0.001f;
		 m_fIActVal_RelErr = 0.1f;
		 m_nIActVal_ErrorLogic = 0;
		 m_fAngleActVal_AbsErr = 0.001f;
		 m_fAngleActVal_RelErr = 0.1f;
		 m_nAngleActVal_ErrorLogic = 0;
		 //m_fHzActVal_AbsErr = 0.001f;
		 //m_fHzActVal_RelErr = 0.1f;
		 //m_nHzActVal_ErrorLogic = 0;
		 m_fImpValue_AbsErr = 0.001f;
		 m_fImpValue_RelErr = 0.1f;
		 m_nImpValue_ErrorLogic = 0;
		 m_fRetCoef_AbsErr = 0.001f;
		 m_fRetCoef_RelErr = 0.1f;
		 m_nRetCoef_ErrorLogic = 0;		
	}

	void InitManuImpedGradient(int nType)
	{	
		m_manuImpedGradient.fStep = 0.5;
		m_manuImpedGradient.fStepTime = 1.2;

		if(nType = 0)
		{
			m_manuImpedGradient.fStart = 1;
			m_manuImpedGradient.fEnd = 10;
		}
		else if(nType = 1)
		{
			m_manuImpedGradient.fStart = 50;
			m_manuImpedGradient.fEnd = 20;
		}

	}

	void CopyOwn(tmt_manualImped_paras *pDest)
	{
		pDest->m_fTimeSet = m_fTimeSet;
		pDest->m_fUSet = m_fUSet;
		pDest->m_fISet = m_fISet;
		pDest->m_fAngleSet = m_fAngleSet;
		//pDest->m_fHzSet = m_fHzSet;
		pDest->m_fImpSet = m_fImpSet;
		pDest->m_fRetCoefSet = m_fRetCoefSet;
		pDest->m_fTimeValue_AbsErr = m_fTimeValue_AbsErr;
		pDest->m_fTimeValue_RelErr = m_fTimeValue_RelErr;
		pDest->m_nTimeValue_ErrorLogic = m_nTimeValue_ErrorLogic;
		pDest->m_fUActVal_AbsErr = m_fUActVal_AbsErr;
		pDest->m_fUActVal_RelErr = m_fUActVal_RelErr;
		pDest->m_nUActVal_ErrorLogic = m_nUActVal_ErrorLogic;
		pDest->m_fIActVal_AbsErr = m_fIActVal_AbsErr;
		pDest->m_fIActVal_RelErr = m_fIActVal_RelErr;
		pDest->m_nIActVal_ErrorLogic = m_nIActVal_ErrorLogic;
		//pDest->m_fHzActVal_AbsErr = m_fHzActVal_AbsErr;
		//pDest->m_fHzActVal_RelErr = m_fHzActVal_RelErr;
		//pDest->m_nHzActVal_ErrorLogic = m_nHzActVal_ErrorLogic;
		pDest->m_fAngleActVal_AbsErr = m_fAngleActVal_AbsErr;
		pDest->m_fAngleActVal_RelErr = m_fAngleActVal_RelErr;
		pDest->m_nAngleActVal_ErrorLogic = m_nAngleActVal_ErrorLogic;
		pDest->m_fImpValue_AbsErr = m_fImpValue_AbsErr;
		pDest->m_fImpValue_RelErr = m_fImpValue_RelErr;
		pDest->m_nImpValue_ErrorLogic = m_nImpValue_ErrorLogic;
		pDest->m_fRetCoef_AbsErr = m_fRetCoef_AbsErr;
		pDest->m_fRetCoef_RelErr = m_fRetCoef_RelErr;
		pDest->m_nRetCoef_ErrorLogic = m_nRetCoef_ErrorLogic; 
	}

	void SetFundFreq(float fFreqValue)
	{
		for(int j = 0; j < MAX_VOLTAGE_COUNT; j++)
		{
			m_uiVOL[j].Harm[1].fFreq = fFreqValue;
			m_uiCUR[j].Harm[1].fFreq = fFreqValue;
		}
	}

public:
    tmt_manualImped_paras()
    {
        init();
    }
} tmt_ManualImpedParas;

typedef struct tmt_manualImped_result:public tmt_ManualResult
{
public:
    tmt_manualImped_result()
    {
        init();
    }
} tmt_ManualImpedResult;

typedef struct tmt_manualImped_test : public TMT_PARAS_HEAD
{
public:
    tmt_ManualImpedParas   m_oManuImpedParas;
    tmt_ManualImpedResult  m_oManuImpedResult;

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_ImpedManualTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oManuImpedResult.init();
        m_oManuImpedParas.init();
    }

    tmt_manualImped_test()
    {
        init();
    }
} tmt_ManualImpedTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_write_ManuImpedTest();
void stt_init_paras(tmt_ManualImpedParas *pParas);
void stt_init_results(tmt_ManualImpedResult *pResults);
void stt_xml_serialize(tmt_ManualImpedParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ManualImpedResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase *stt_xml_serialize(tmt_ManualImpedTest *pParas, CSttXmlSerializeBase *pXmlSierialize);

