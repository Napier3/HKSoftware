#pragma once

#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

//2021-5-30  lijunqing
#include "tmt_test_paras_head.h"


#define   TMT_MANU_FUNC_TYPE_Common                                0 //�ֶ����鹦�����  0����һ����ֶ�����
#define   TMT_MANU_FUNC_TYPE_MUAccuracy                            1 //�ֶ����鹦�����  1����ϲ���Ԫ���Ȳ���
//#define   TMT_MANU_FUNC_TYPE_MUZeroDrift                           2 //�ֶ����鹦�����  2����ϲ���Ԫ��Ư����
#define	  TMT_MANU_FUNC_TYPE_MUFirstCycleWave					   2 //�ֶ����鹦�����  2����ϲ���Ԫ���ܲ�����
#define   TMT_MANU_FUNC_TYPE_MUTimingAccur                         3 //�ֶ����鹦�����  3����ϲ���Ԫ��ʱ���Ȳ���
#define   TMT_MANU_FUNC_TYPE_MUPunctAccur                          4 //�ֶ����鹦�����  4����ϲ���Ԫ��ʱ���Ȳ���



// �ֶ�������ز���
typedef struct tmt_manu_gradient
{
    int		nMode;	// 0:ʼֵ-��ֵ  1:ʼֵ-��ֵ-ʼֵ
    float	fStart;
    float	fEnd;
    float	fStep;
    float	fStepTime;
    float	fTrigDelay;
    int		nHarmIndex;	//�仯г������ 1Ϊ����

    void init()
    {
        nMode = 0;
        fStart = 1;
        fEnd = 10;
        fTrigDelay = 0;
        fStep = 0.5;
        fStepTime = 1;
        nHarmIndex = 1;
    }

    tmt_manu_gradient()
    {
        init();
    }
} tmt_ManuGradient;

typedef struct tmt_mu_paras
{
    int		nAlgorithmType;	// 0:��ֵ��  1:ͬ����
    int		nPPS_SetType;	// 0:��������Ч  1:�½�����Ч 2:��PPS
    float	fUn;//���ѹ-������Ư����
    float	fIn;//�����-������Ư����
    long   nSynTime;//��ʱ���Ȳ���ʱ,��ʼ���Ժ�,��ͬ����ʱ���,�Զ��ж�ͬ���ź�
	//zhouhj 2023.10.13 ɾ��
 //   float   fDelayCompens_NoPPS;//��PPSģʽ�µ���ʱ����ֵ
	int   m_nUseSetRpt;//�Ƿ�ʹ���Զ��屨�淽ʽ,��ָ�����������ÿ�ε�ʱ��
	int   m_nMaxTestCount;//�����Դ���
	float  m_fTimeOneCount;//ÿ�ε�ʱ��


    void init()
    {
        nAlgorithmType = 0;
        nPPS_SetType = 0;
        fUn = 57.74f;
        fIn = 1.0;
        nSynTime = 2;
//        fDelayCompens_NoPPS = 0.0f;
		m_nUseSetRpt = 0;
		m_nMaxTestCount = 10;//
		m_fTimeOneCount = 0.5f;
    }

    tmt_mu_paras()
    {
        init();
    }
} tmt_MuParas;

typedef struct tmt_manual_paras
{
public:
    BOOL    m_bBinStop;//����ֹͣ,����UpdateParameterʱ�ײ���±���
    BOOL	m_bAging;		//�Ƿ��ϻ�����
    BOOL	m_bAuto;
    BOOL	m_bDC;
    BOOL       m_bLockChanged;//lock mark
	BOOL	m_bResultAddBin;
    float       m_fOutPutTime;	// ����ʱ��
    float	    m_fVolAux;		// ����ֱ����ѹ����ģ�⣩
    float	    m_fCurAux;		// ����ֱ����������ģ�⣩
//	float       m_fOverloadDelaytime;	//������ʱ  ��λ�� ���ܣ��������ڿ�ʼ������趨ʱ��֮����⵽���ز��ж����
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    //������
    int		m_nBinLogic;			//0-�� 1-��
    tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];
    tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������
    tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������
    int		 m_nGradientTpSelect;	// �ݱ�����ѡ��
    int		 m_nGradientChSelect;	// �ݱ�ͨ��ѡ��
	int	     m_nVarIndexType;//0=���� 1=��ѹ 2=Ƶ��
    tmt_ManuGradient m_manuGradient;

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
    //Ft3Pub
    tmt_Ft3Pub m_oFt3Pub[MAX_MODULES_FT3PUB_COUNT];
    //2M
    tmt_2MOnePortPub m_o2MOnePortPub[MAX_2M_BLOCKS_COUNT];
    int            m_nFuncType;//�������  0-�����ֶ�����  1-MU���Ȳ���  2-MU��Ư����   3-��ʱ���Ȳ���      4-��ʱ���Ȳ���
    int            m_nSelHarm;//ѡ�����г��
    int            m_nHarmIndex;// ѡ�����г����Index  2-2��г��    3-3��г��
//	int            m_nUploadRpt_Started;//��ʼ����ʱ,�Ƿ����ͱ���
    tmt_MuParas    m_oMuParas;//�ϲ���Ԫ������ز���

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
        float fAngle[3] = {0, -120.0, 120.0};
        m_bAging = false;
        m_bAuto = false;
        m_bDC = false;
        m_bLockChanged = false;
		m_bResultAddBin = FALSE;
        m_fOutPutTime = 0.000001f;
//		m_nUploadRpt_Started = 0;
        m_fVolAux = 0;
        m_fCurAux = 0;
//		m_fOverloadDelaytime = 0;
        m_nBinLogic = 0;
        m_nGradientChSelect = 0;
        m_nGradientTpSelect = 0;
		m_nVarIndexType = 0;
        m_nFuncType = TMT_MANU_FUNC_TYPE_Common;
        m_nSelHarm = 0;
        m_nHarmIndex = 2;
        m_oMuParas.init();
        m_manuGradient.init();

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

    void InitManuGradient(bool bType_U)
    {
        m_manuGradient.fStart = 0;
        m_manuGradient.fStep = 0.5;
        m_manuGradient.fStepTime = 0.5;

        if(bType_U)
        {
            m_manuGradient.fEnd = 10;
        }
        else
        {
            m_manuGradient.fEnd = 5;
        }
    }

    void setDC(bool bDC, bool bUpdateAngleFre = false)
    {
        m_bDC = bDC;
        float fAngle[3] = {0, -120.0, 120.0};

        for(int j = 0; j < MAX_VOLTAGE_COUNT; j++)
        {
            m_uiVOL[j].Harm[1].bDC = bDC;

            if(bUpdateAngleFre)
            {
                if(bDC)
                {
                    m_uiVOL[j].Harm[1].fAngle = 0;
                    m_uiVOL[j].Harm[1].fFreq = 0;
                }
                else
                {
                    m_uiVOL[j].Harm[1].fFreq = 50;
                    m_uiVOL[j].Harm[1].fAngle = fAngle[j % 3];
                }
            }
        }

        for(int j = 0; j < MAX_CURRENT_COUNT; j++)
        {
            m_uiCUR[j].Harm[1].bDC = bDC;

            if(bUpdateAngleFre)
            {
                if(bDC)
                {
                    m_uiCUR[j].Harm[1].fAngle = 0;
                    m_uiCUR[j].Harm[1].fFreq = 0;
                }
                else
                {
                    m_uiCUR[j].Harm[1].fFreq = 50;
                    m_uiCUR[j].Harm[1].fAngle = fAngle[j % 3];
                }
            }
        }
    }
	void CopyOwn(tmt_manual_paras *pDest)
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

		pDest->m_nVarIndexType = m_nVarIndexType;

	}


    void SetFundFreq(float fFreqValue)
    {
        for(int j = 0; j < MAX_VOLTAGE_COUNT; j++)
        {
            m_uiVOL[j].Harm[1].fFreq = fFreqValue;
            m_uiCUR[j].Harm[1].fFreq = fFreqValue;
        }
    }

    tmt_manual_paras()
    {
        init();
    }

} tmt_ManualParas;

typedef struct tmt_mu_time_result//20220806 zhouhj �������ںϲ���Ԫ��ʱ����ʱ���Ȳ��Է��ر���
{
public:
    float m_fHasUsingTime;//��ʹ��ʵ��ʱ�䳤��,ͬ��ʱ��/��ʱʱ��(��λ:s)
    float m_fCurrErrTime;//��ǰ���ʱ��(��λ:��s)
    float m_fMaxErrTime;//������ʱ��(��λ:��s)
    float m_fMinErrTime;//��С���ʱ��(��λ:��s)
    float m_fAverageErrTime;//ƽ�����ʱ��(��λ:��s)
    long  m_nTimeTestResult;//MUʱ�侫�Ȳ��Խ��,�ж��Ƿ�ϸ�

    void init()
    {
        m_fHasUsingTime = 0.00f;
        m_fCurrErrTime = 0.00f;
        m_fMaxErrTime = 0.00f;
        m_fMinErrTime = 0.00f;
        m_fAverageErrTime = 0.00f;
        m_nTimeTestResult = 0;
    }

    void CopyOwn(tmt_mu_time_result *pDest)
    {
        pDest->m_fHasUsingTime = m_fHasUsingTime;
        pDest->m_fCurrErrTime = m_fCurrErrTime;
        pDest->m_fMaxErrTime = m_fMaxErrTime;
        pDest->m_fMinErrTime = m_fMinErrTime;
        pDest->m_fAverageErrTime = m_fAverageErrTime;
        pDest->m_nTimeTestResult = m_nTimeTestResult;
    }

    tmt_mu_time_result()
    {
        init();
    }
} tmt_MuTimeResult;

typedef struct tmt_manual_result
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

    tmt_MuTimeResult m_oMuTimeRlt;//20220806 zhouhj �������ںϲ���Ԫ��ʱ����ʱ���Ȳ��Է��ر���

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
        m_oMuTimeRlt.init();

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

    void CopyOwn(tmt_manual_result *pDest)
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
        pDest->m_oMuTimeRlt.CopyOwn(&pDest->m_oMuTimeRlt);

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

    tmt_manual_result()
    {
        init();
    }
} tmt_ManualResult;

typedef struct tmt_manual_test : public TMT_PARAS_HEAD
{
public:
    tmt_ManualParas   m_oManuParas;
    tmt_ManualResult m_oManuResult;

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_ManualTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oManuResult.init();
        m_oManuParas.init();
    }

    tmt_manual_test()
    {
        init();
    }
} tmt_ManualTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_ManuTest();
void stt_init_paras(tmt_ManualParas *pParas);
void stt_init_results(tmt_ManualResult *pResults);
void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);
void stt_xml_serialize(tmt_ManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize, BOOL bBinStatus = FALSE);
void stt_xml_serialize_dc(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//void stt_xml_serialize_Aging(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//void stt_xml_serialize_Lock(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//void stt_xml_serialize_Auto(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);  zhouhj 20210830 ���л���֧��BOOL,������ô˺���

void stt_xml_serialize_12u12i_pnv(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase *stt_xml_serialize(tmt_ManualTest *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);

