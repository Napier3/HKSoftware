#pragma once

//2021-5-30  lijunqing
#include "../tmt_manu_test.h"
#include "../tmt_system_config.h"

#define  STT_LINEVOLT_Gradient_Ch_Uab1              0
#define  STT_LINEVOLT_Gradient_Ch_3U0_1             1
#define  STT_LINEVOLT_Gradient_Ch_Uab2              2
#define  STT_LINEVOLT_Gradient_Ch_3U0_2             3
#define  STT_LINEVOLT_Gradient_Ch_Ia1               4
#define  STT_LINEVOLT_Gradient_Ch_Ib1               5
#define  STT_LINEVOLT_Gradient_Ch_Ic1               6
#define  STT_LINEVOLT_Gradient_Ch_Ia2               7
#define  STT_LINEVOLT_Gradient_Ch_Ib2               8
#define  STT_LINEVOLT_Gradient_Ch_Ic2               9

// �ֶ�������ز���
typedef struct tmt_Linevolt_gradient
{
	int		nMode;	// 0:ʼֵ-��ֵ  1:ʼֵ-��ֵ-ʼֵ
	float	fStart;
	float	fEnd;
	float	fStep;
	float	fStepTime;
	float	fTrigDelay;

	void init()
	{
		nMode = 0;
		fStart=1;
		fEnd=10;
		fTrigDelay=0;
		fStep=0.5;
		fStepTime=1;
	}

	tmt_Linevolt_gradient()
	{
		init();
	}
}tmt_LinevoltGradient;

typedef struct tmt_linevolt_manu_paras
{
public:
	BOOL    m_bBinStop;//����ֹͣ,����UpdateParameterʱ�ײ���±���
	BOOL	m_bAging;		//�Ƿ��ϻ�����
	BOOL	m_bAuto;
	BOOL       m_bLockChanged;//lock mark
	//float       m_fOutPutTime;	// ����ʱ��
	float	    m_fVolAux;		// ����ֱ����ѹ����ģ�⣩
	float	    m_fCurAux;		// ����ֱ����������ģ�⣩
//	float       m_fOverloadDelaytime;	//������ʱ  ��λ�� ���ܣ��������ڿ�ʼ������趨ʱ��֮����⵽���ز��ж����
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
	float       m_fFreq;
	//������
	int		m_nBinLogic;			//0-�� 1-��
	tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];
	tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������
	tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������
	int		 m_nGradientTpSelect;	// �ݱ�����ѡ�� 0-��ֵ  1-��λ
	int		 m_nGradientChSelect;	// �ݱ�ͨ��ѡ��
	tmt_LinevoltGradient m_oLinevoltGradient;
	int	  m_nVarIndexType;//0=���� 1=��ѹ 2=Ƶ��

	//GoosePub
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
    //2M
    tmt_2MOnePortPub m_o2MOnePortPub[MAX_2M_BLOCKS_COUNT];

	//����ֵ
	float m_fTimeSet;   //��������ʱ��
	float m_fUSet;		//��ѹ��������ֵ
	float m_fISet;		//������������ֵ
	float m_fAngleSet;	//��λ��������ֵ
	float m_fHzSet;		//Ƶ����������ֵ
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
	float m_fHzActVal_AbsErr; 		//Ƶ�ʶ���ֵ������� 		
	float m_fHzActVal_RelErr; 		//Ƶ�ʶ���ֵ������ 		
	long m_nHzActVal_ErrorLogic; 	//Ƶ�ʶ���ֵ����ж��߼� 	
	float m_fRetCoef_AbsErr; 		//����ϵ��������� 		
	float m_fRetCoef_RelErr;		//����ϵ�������� 		
	long m_nRetCoef_ErrorLogic; 	//����ϵ������ж��߼� 	

public:
	void init()
	{
		m_bBinStop=FALSE;
		float fAngle[3] = {0, -120.0, 120.0};
		m_bAging = false;
		m_bAuto = false;
		m_bLockChanged = false;
		//m_fOutPutTime = 0.000001f;
		m_fVolAux = 0;
		m_fCurAux = 0;
		m_nBinLogic = 0;
		m_nGradientChSelect = STT_LINEVOLT_Gradient_Ch_Uab1;
		m_nGradientTpSelect = 0;
		m_fFreq = 50.0f;

		m_fTimeSet =0; 
		m_fUSet=0;		
		m_fISet=0;		
		m_fAngleSet=0;	
		//m_fHzSet=0;		
		m_fRetCoefSet=0;

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
		m_fRetCoef_AbsErr = 0.001f; 			
		m_fRetCoef_RelErr = 0.1f;				
		m_nRetCoef_ErrorLogic = 0; 
		m_nVarIndexType = 0;


		m_oLinevoltGradient.init();

		for(int i=0; i<MAX_VOLTAGE_COUNT; i++)
		{
			m_uiVOL[i].Harm[0].fAmp = 0;
			m_uiCUR[i].Harm[0].fAmp = 0;
			m_uiVOL[i].Harm[1].fAmp = 0;
			m_uiCUR[i].Harm[1].fAmp = 0;
			m_uiVOL[i].Harm[1].fAngle = m_uiCUR[i].Harm[1].fAngle = fAngle[i%3];
			m_uiVOL[i].Harm[1].fFreq=m_uiCUR[i].Harm[1].fFreq=50;

            for(int harm = 0; harm< MAX_HARM_COUNT;harm++)
            {
                m_uiVOL[i].Harm[harm].init();
                m_uiCUR[i].Harm[harm].init();
            }
		}

		for (int j=0;j<MAX_BINARYIN_COUNT;j++)
		{
			m_binIn[j].nSelect = 0;
			m_binIn[j].nTrigMode = 0;

#ifndef _PSX_QT_LINUX_
			if(j<g_nBinCount)
			{
				m_binIn[j].nSelect = 1;
			}
#endif
		}

		for (int j=0;j<MAX_BINARYOUT_COUNT;j++)
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

		for(int nIndex=0;nIndex<MAX_MODULES_GOOSEPUB_COUNT;nIndex++)
			m_oGoosePub[nIndex].init();

        for(int nIndex = 0;nIndex < MAX_2M_BLOCKS_COUNT;nIndex++)
            m_o2MOnePortPub[nIndex].init();
	}

	void InitLinevoltGradient(bool bType_U)
	{
		m_oLinevoltGradient.fStart = 0;
		m_oLinevoltGradient.fStep = 0.5;
		m_oLinevoltGradient.fStepTime = 0.5;

		if (bType_U)
		{
			m_oLinevoltGradient.fEnd = 10;
		}
		else
		{
			m_oLinevoltGradient.fEnd = 5;
		}
	}

	void SetFundFreq(float fFreqValue)
	{
		for (int j=0;j<MAX_VOLTAGE_COUNT;j++)
		{
			m_uiVOL[j].Harm[1].fFreq = fFreqValue;
			m_uiCUR[j].Harm[1].fFreq = fFreqValue;
		}
	}
	void CopyOwn(tmt_linevolt_manu_paras *pDest)
	{

		pDest->m_fTimeSet =m_fTimeSet; 
		pDest->m_fUSet=m_fUSet;		
		pDest->m_fISet=m_fISet;		
		pDest->m_fAngleSet=m_fAngleSet;	
		pDest->m_fHzSet=m_fHzSet;		
		pDest->m_fRetCoefSet=m_fRetCoefSet;

		pDest->m_fTimeValue_AbsErr = m_fTimeValue_AbsErr;
		pDest->m_fTimeValue_RelErr = m_fTimeValue_RelErr;
		pDest->m_nTimeValue_ErrorLogic = m_nTimeValue_ErrorLogic;
		pDest->m_fUActVal_AbsErr = m_fUActVal_AbsErr;
		pDest->m_fUActVal_RelErr = m_fUActVal_RelErr;
		pDest->m_nUActVal_ErrorLogic = m_nUActVal_ErrorLogic;
		pDest->m_fIActVal_AbsErr = m_fIActVal_AbsErr;
		pDest->m_fIActVal_RelErr = m_fIActVal_RelErr;
		pDest->m_nIActVal_ErrorLogic = m_nIActVal_ErrorLogic;
		pDest->m_fAngleActVal_AbsErr = m_fAngleActVal_AbsErr;
		pDest->m_fAngleActVal_RelErr = m_fAngleActVal_RelErr;
		pDest->m_nAngleActVal_ErrorLogic = m_nAngleActVal_ErrorLogic; 
		pDest->m_fRetCoef_AbsErr = m_fRetCoef_AbsErr; 	
		pDest->m_fRetCoef_RelErr = m_fRetCoef_RelErr;	
		pDest->m_nRetCoef_ErrorLogic = m_nRetCoef_ErrorLogic;

		pDest->m_nVarIndexType = m_nVarIndexType;

	}

	tmt_linevolt_manu_paras()
	{
		init();
	}

}tmt_LinevoltManuParas;


typedef struct tmt_linevolt_manu_result  : public tmt_ManualResult
{
public:


public:
	virtual void init()
	{
		tmt_ManualResult::init();
	}

	tmt_linevolt_manu_result()
	{
		init();
	}
}tmt_LinevoltManuResult;


typedef struct tmt_linevolt_manu_test : public TMT_PARAS_HEAD
{
public:
	tmt_LinevoltManuParas   m_oLinevoltManuParas;
	tmt_LinevoltManuResult m_oLinevoltManuResult;

	void init()
	{
		strcpy(m_pszMacroID, STT_MACRO_ID_LineVolManuTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
		m_oLinevoltManuResult.init();
		m_oLinevoltManuParas.init();
	}

	tmt_linevolt_manu_test()
	{
		init();
	}
}tmt_LinevoltManuTest;

void stt_xml_serialize_write_LinevoltManuTest();

void stt_init_paras(tmt_LinevoltManuParas *pParas);
void stt_init_results(tmt_LinevoltManuResult *pResults);
void stt_xml_serialize(tmt_LinevoltManuParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_LinevoltManuParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nVolGroupNum,long nCurGroupNum);
//void stt_xml_serialize(tmt_LinevoltManuResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_LinevoltManuTest *pParas, CSttXmlSerializeBase *pXmlSierialize,tmt_channel *puiVOL, tmt_channel *puiCUR);
void stt_xml_serialize_linevolt(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, tmt_channel *puiVOL, tmt_channel *puiCUR);
