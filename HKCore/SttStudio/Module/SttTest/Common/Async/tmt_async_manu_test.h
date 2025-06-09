#pragma once

#include "../tmt_common_def.h"
// #include "../../../SttTestBase/SttXmlSerialize.h"
#include "../tmt_test_paras_head.h"


//�ݱ������ز���
typedef struct tmt_async_manu_gradient
{
	int		nMode;	// 0:ʼֵ-��ֵ  1:ʼֵ-��ֵ-ʼֵ
	float	fStart;
	float	fEnd;
	float	fStep;
	float	fStepTime;
	float	fTrigDelay;//��������ʱ
// 	int		nHarmIndex;	//�仯г������ 1Ϊ����
	int		 m_nGradientTpSelect;		// �ݱ�����ѡ��  ��ֵ��λƵ��
	int		 m_nGradientChSelect;		// �ݱ�ͨ��ѡ��
	int		 m_nGradientModuleSelect;	// �ݱ�ģ��ѡ��

	void init()
	{
		nMode = 0;
		fStart = 1;
		fEnd = 10;
		fTrigDelay = 0;
		fStep = 0.5;
		fStepTime = 1;
		m_nGradientTpSelect = 0;	
		m_nGradientChSelect = 0;	
		m_nGradientModuleSelect = 0;

// 		nHarmIndex = 1;
	}

	tmt_async_manu_gradient()
	{
		init();
	}
} tmt_AsyncManuGradient;

typedef struct tmt_async_manual_paras
{
public:
	BOOL    m_bBinStop;//����ֹͣ,����UpdateParameterʱ�ײ���±���
	BOOL	m_bAging;		//�Ƿ��ϻ�����
	BOOL       m_bLockChanged;//lock mark
	float       m_fOutPutTime;	// ����ʱ��
	float	    m_fVolAux;		// ����ֱ����ѹ����ģ�⣩
	float	    m_fCurAux;		// ����ֱ����������ģ�⣩
	//	float       m_fOverloadDelaytime;	//������ʱ  ��λ�� ���ܣ��������ڿ�ʼ������趨ʱ��֮����⵽���ز��ж����

	//ģ�� 
	tmt_AsyncModules	 m_oAsyncModuels;

	//������
	int		m_nBinLogic;			//0-�� 1-��
	tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];
	tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������
	tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������

	//�ݱ�
	BOOL	m_bAuto;
	int		 m_nGradientModuleTypeSel;	// �ݱ�ģ������ѡ��
	tmt_AsyncManuGradient m_manuGradient[ASYNC_MODULE_TYPE_COUNT];

	//GoosePub
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
	//Ft3Pub
	tmt_Ft3Pub m_oFt3Pub[MAX_MODULES_FT3PUB_COUNT];
	//2M
	tmt_2MOnePortPub m_o2MOnePortPub[MAX_2M_BLOCKS_COUNT];
// 	int            m_nFuncType;//�������  0-�����ֶ�����  1-MU���Ȳ���  2-MU��Ư����   3-��ʱ���Ȳ���      4-��ʱ���Ȳ���
// 	int            m_nSelHarm;//ѡ�����г��
// 	int            m_nHarmIndex;// ѡ�����г����Index  2-2��г��    3-3��г��
	//	int            m_nUploadRpt_Started;//��ʼ����ʱ,�Ƿ����ͱ���

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
		m_bBinStop = FALSE;
		m_bAging = false;
		m_bAuto = false;
		m_bLockChanged = false;
		m_fOutPutTime = 0.000001f;
		//		m_nUploadRpt_Started = 0;
		m_fVolAux = 0;
		m_fCurAux = 0;
		//		m_fOverloadDelaytime = 0;
		m_nBinLogic = 0;
		m_nGradientModuleTypeSel = 0;
// 		m_nGradientChSelect = 0;
// 		m_nGradientTpSelect = 0;
// 		m_nVarIndexType = 0;
// 		m_nFuncType = TMT_MANU_FUNC_TYPE_Common;
// 		m_nSelHarm = 0;
// 		m_nHarmIndex = 2;
// 		m_oMuParas.init();
		for(int nIndex = 0;nIndex < ASYNC_MODULE_TYPE_COUNT;nIndex++)
		{
			m_manuGradient[nIndex].init();
		}

		m_oAsyncModuels.init();

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

		for(int nIndex = 0; nIndex < MAX_MODULES_FT3PUB_COUNT; nIndex++)
		{
			m_oFt3Pub[nIndex].init();
		}

		for(int nIndex = 0; nIndex < MAX_2M_BLOCKS_COUNT; nIndex++)
		{
			m_o2MOnePortPub[nIndex].init();
		}

		m_fTimeSet =0; 
		m_fUSet=0;		
		m_fISet=0;		
		m_fAngleSet=0;	
		m_fHzSet=0;		
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
		m_fHzActVal_AbsErr = 0.001f; 		
		m_fHzActVal_RelErr = 0.1f; 		 		
		m_nHzActVal_ErrorLogic = 0; 	
		m_fRetCoef_AbsErr = 0.001f; 			
		m_fRetCoef_RelErr = 0.1f;				
		m_nRetCoef_ErrorLogic = 0; 
	}

// 	void InitManuGradient(bool bType_U)
// 	{
// 		m_manuGradient.fStart = 0;
// 		m_manuGradient.fStep = 0.5;
// 		m_manuGradient.fStepTime = 0.5;
// 
// 		if(bType_U)
// 		{
// 			m_manuGradient.fEnd = 10;
// 		}
// 		else
// 		{
// 			m_manuGradient.fEnd = 5;
// 		}
// 	}

	void InitModuleCh(tmt_AsyncModule *pAnsyncModule, int nCurChCount, int nVolChCount)
	{
		pAnsyncModule->initChannel(nCurChCount, nVolChCount);

		float fAng[3] = {0,-120,120};
		for(int nIndex=0;nIndex<nCurChCount;nIndex++)
		{
			pAnsyncModule->m_pCurrChannel[nIndex].m_oHarm.m_bSelect = TRUE;
			pAnsyncModule->m_pCurrChannel[nIndex].m_oHarm.fAmp = 0;
			pAnsyncModule->m_pCurrChannel[nIndex].m_oHarm.fAngle = fAng[nIndex%3];
			pAnsyncModule->m_pCurrChannel[nIndex].m_oHarm.fFreq = 50;
		}
		for(int nIndex=0;nIndex<nVolChCount;nIndex++)
		{
			pAnsyncModule->m_pVolChannel[nIndex].m_oHarm.m_bSelect = TRUE;
			pAnsyncModule->m_pVolChannel[nIndex].m_oHarm.fAmp = 0;
			pAnsyncModule->m_pVolChannel[nIndex].m_oHarm.fAngle = fAng[nIndex%3];
			pAnsyncModule->m_pVolChannel[nIndex].m_oHarm.fFreq = 50;
		}

	}

	void setDC(bool bDC, int nModuleType, bool bUpdateAngleFre = false)
	{
		m_oAsyncModuels.m_nDc[nModuleType] = bDC;

		tmt_AsyncModule *pAnsyncModule = NULL;
		int nNum = 0;
		float fAngle[3] = {0, -120.0, 120.0};

		switch (nModuleType)
		{
		case ASYNC_MODULE_TYPE_ANALOG:
			pAnsyncModule = m_oAsyncModuels.m_oAnalogModules;
			nNum = m_oAsyncModuels.m_nAnalogCount;
			break;
		case ASYNC_MODULE_TYPE_DIGITAL:
			pAnsyncModule = &m_oAsyncModuels.m_oDigitalModules;
			nNum = 1; // ֻ��һ������ģ��
			break;
		case ASYNC_MODULE_TYPE_WEEK:
			pAnsyncModule = m_oAsyncModuels.m_oWeekModules;
			nNum = m_oAsyncModuels.m_nWeekCount;
			break;
		default:
			return;
		}

		if (!pAnsyncModule->m_pCurrChannel || !pAnsyncModule->m_pVolChannel)
		{
			return;
		}

		for (int nIndex = 0; nIndex < nNum; nIndex++)
		{
			for (int nChannelIndex = 0; nChannelIndex < pAnsyncModule[nIndex].m_nCurrChCount; nChannelIndex++)
			{
				if (bDC)
				{
					pAnsyncModule[nIndex].m_pCurrChannel[nChannelIndex].m_oHarm.fAngle = 0;
					pAnsyncModule[nIndex].m_pCurrChannel[nChannelIndex].m_oHarm.fFreq = 0;
				}
				if (bUpdateAngleFre && !bDC)
				{
					pAnsyncModule[nIndex].m_pCurrChannel[nChannelIndex].m_oHarm.fFreq = 50;
					pAnsyncModule[nIndex].m_pCurrChannel[nChannelIndex].m_oHarm.fAngle = fAngle[nChannelIndex % 3];
				}
			}

			for (int nChannelIndex = 0; nChannelIndex < pAnsyncModule[nIndex].m_nVolChCount; nChannelIndex++)
			{
				if (bDC)
				{
					pAnsyncModule[nIndex].m_pVolChannel[nChannelIndex].m_oHarm.fAngle = 0;
					pAnsyncModule[nIndex].m_pVolChannel[nChannelIndex].m_oHarm.fFreq = 0;
				}
				if (bUpdateAngleFre && !bDC)
				{
					pAnsyncModule[nIndex].m_pVolChannel[nChannelIndex].m_oHarm.fFreq = 50;
					pAnsyncModule[nIndex].m_pVolChannel[nChannelIndex].m_oHarm.fAngle = fAngle[nChannelIndex % 3];
				}
			}
		}
	}

	void CopyOwn(tmt_async_manual_paras *pDest)
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
		pDest->m_fHzActVal_AbsErr = m_fHzActVal_AbsErr;	
		pDest->m_fHzActVal_RelErr = m_fHzActVal_RelErr;	
		pDest->m_nHzActVal_ErrorLogic = m_nHzActVal_ErrorLogic;
		pDest->m_fAngleActVal_AbsErr = m_fAngleActVal_AbsErr;
		pDest->m_fAngleActVal_RelErr = m_fAngleActVal_RelErr;
		pDest->m_nAngleActVal_ErrorLogic = m_nAngleActVal_ErrorLogic; 
		pDest->m_fRetCoef_AbsErr = m_fRetCoef_AbsErr; 	
		pDest->m_fRetCoef_RelErr = m_fRetCoef_RelErr;	
		pDest->m_nRetCoef_ErrorLogic = m_nRetCoef_ErrorLogic;

// 		pDest->m_nVarIndexType = m_nVarIndexType;

	}


// 	void SetFundFreq(float fFreqValue)
// 	{
// 		for(int j = 0; j < MAX_VOLTAGE_COUNT; j++)
// 		{
// 			m_uiVOL[j].Harm[1].fFreq = fFreqValue;
// 			m_uiCUR[j].Harm[1].fFreq = fFreqValue;
// 		}
// 	}

	tmt_async_manual_paras()
	{
		init();
	}

} tmt_AsyncManualParas;

typedef struct tmt_async_manual_result
{
public:
	unsigned  int m_nindex;		//���
	unsigned   int m_nsecondtime;		// ʱ����� ��
	unsigned   int m_nnsecondtime;	// ʱ����� ����
	unsigned   int m_noactivetype;	// ����
	unsigned   int m_nBinstate;		// ������
	unsigned   int m_nBinAllState;   // ����������״ֵ̬
	unsigned   int m_nOverLoad;		// ���غ�ֹͣ
	float        m_fuavalue;		// ��ѹʵ�����ֵ�����ڼ�����ѹУ��ϵ��
	float        m_fubvalue;
	float        m_fucvalue;
	float        m_fuzvalue;

	//�������
	float	m_frTestTime;							//ʵ������ʱ��
	float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//ÿһ�������¼64�α�λʱ��
	int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT]; //��λ����
	float	m_frTimeBinExAct[MAX_ExBINARY_COUNT][64];		//ÿһ�������¼64�α�λʱ��
	int		m_nrBinExSwitchCount[MAX_ExBINARY_COUNT]; //��λ����
	int		m_nTripFlag; //0,1
	float	m_fTripTime;		//ʵ������ʱ��
	float	m_fActValue;
	float	m_fReturnValue;
	float   m_fReturnCoef;
	float   m_fReturnTime;


public:
	virtual void init()
	{
		m_nindex = 0;
		m_nsecondtime = 0;
		m_nnsecondtime = 0;
		m_noactivetype = 0;
		m_nBinstate = 0;
		m_nBinAllState = 0;
		m_nOverLoad = 0;
		m_fuavalue = 0;
		m_fubvalue = 0;
		m_fucvalue = 0;
		m_fuzvalue = 0;
		m_frTestTime = 0;
		m_nTripFlag = 0;
		m_fTripTime = 0;
		m_fActValue = 0;
		m_fReturnValue = 0;
		m_fReturnCoef = 0;
		m_fReturnTime = 0;

		for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			for(int j = 0; j < 64; j++)
			{
				m_frTimeBinAct[i][j] = 0;
			}

			m_nrBinSwitchCount[i] = 0;
		}

		for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for(int j = 0; j < 64; j++)
			{
				m_frTimeBinExAct[i][j] = 0;
			}

			m_nrBinExSwitchCount[i] = 0;
		}
	}

	void CopyOwn(tmt_async_manual_result *pDest)
	{
		pDest->m_nindex = m_nindex;
		pDest->m_nsecondtime = m_nsecondtime;
		pDest->m_nnsecondtime = m_nnsecondtime;
		pDest->m_noactivetype = m_noactivetype;
		pDest->m_nBinstate = m_nBinstate;
		pDest->m_nBinAllState = m_nBinAllState;
		pDest->m_nOverLoad = m_nOverLoad;
		pDest->m_fuavalue = m_fuavalue;
		pDest->m_fubvalue = m_fubvalue;
		pDest->m_fucvalue = m_fucvalue;
		pDest->m_fuzvalue = m_fuzvalue;
		pDest->m_frTestTime = m_frTestTime;
		pDest->m_nTripFlag = m_nTripFlag;
		pDest->m_fTripTime = m_fTripTime;
		pDest->m_fActValue = m_fActValue;
		pDest->m_fReturnValue = m_fReturnValue;
		pDest->m_fReturnTime = m_fReturnTime;
		pDest->m_fReturnCoef = m_fReturnCoef;

		for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			for(int j = 0; j < 64; j++)
			{
				pDest->m_frTimeBinAct[i][j] = m_frTimeBinAct[i][j];
			}

			pDest->m_nrBinSwitchCount[i] = m_nrBinSwitchCount[i];
		}

		for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for(int j = 0; j < 64; j++)
			{
				pDest->m_frTimeBinExAct[i][j] = m_frTimeBinExAct[i][j];
			}

			pDest->m_nrBinExSwitchCount[i] = m_nrBinExSwitchCount[i];
		}
	}

	tmt_async_manual_result()
	{
		init();
	}
} tmt_AsyncManualResult;

typedef struct tmt_async_manual_test : public TMT_PARAS_HEAD
{
public:
	tmt_AsyncManualParas   m_oParas;
	tmt_AsyncManualResult m_oResult;

	void init()
	{
		strcpy(m_pszMacroID, STT_MACRO_ID_AnsyncManualTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
		m_oResult.init();
		m_oParas.init();
	}

	tmt_async_manual_test()
	{
		init();
	}
} tmt_AsyncManualTest;



void stt_xml_serialize_Channel(tmt_async_channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_Analog(tmt_async_module *pModule, int nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_Week(tmt_async_module *pModule, int nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_Digital(tmt_async_module *pModule, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_Modules(tmt_AsyncManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_act_rcd(tmt_AsyncManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_AsyncManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_AsyncManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_write_AsyncManualTest();
void stt_xml_serialize_Gradient(tmt_async_manu_gradient *pGradientPara, CSttXmlSerializeBase *pXmlSierialize, int nModuleType);

CSttXmlSerializeBase *stt_xml_serialize(tmt_async_manual_test *pParas, CSttXmlSerializeBase *pXmlSierialize);