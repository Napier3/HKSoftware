#pragma once
#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_manu_test.h"
#include "tmt_gradient_test.h"

//2021-6-3  mym
#include "tmt_test_paras_head.h"

//zhouhj 2023.7.11 谐波模块串行化数据量较大,在开始测试命令时,谐波通道只发送非0数据
//更新命令时,只更新修改的谐波数据
#define STT_TMT_harm_write_serialize_Mode_ALL                     0
#define STT_TMT_harm_write_serialize_Mode_NotZero                 1
#define STT_TMT_harm_write_serialize_Mode_Changed                 2

extern long g_nHarmWriteSerialMode;


typedef tmt_ManuGradient tmt_HarmGradient;
typedef struct tmt_harm_paras
{
public:
    BOOL    m_bBinStop;//开入停止,接收UpdateParameter时底层更新变量
    BOOL    m_bLock;
    BOOL	m_bAuto;
	int     m_nFuncType;//功能类别  0-常规谐波试验  1-MU谐波测试
    int     m_nHarmMode;		//harm mode
    int		m_nGradientTpSelect;//递变类型选择
    int		m_nGradientChSelect;//递变通道选择
    float   m_fOutPutTime;		//最长输出时间
    float	m_fVolAux;			//辅助直流电压（仅模拟）
    float	m_fCurAux;			//辅助直流电流（仅模拟）
	float   m_fBaseFre;

	int		m_nVolChSelect;//电压通道选择 （只作为界面显示）  //20240326 suyang
	int		m_nCurChSelect;//电流通道选择

    int	  m_nVarIndexType;//0=电流 1=电压 2=频率

    tmt_BinaryConfig m_oBinaryConfig;
    tmt_HarmGradient m_oHarmGradient;
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];

    //整定值
    float m_fTimeSet;   //动作整定时间
    float m_fUSet;		//电压整定动作值
    float m_fISet;		//电流整定动作值

    //评估
    float m_fTimeValue_AbsErr;      //动作时间值绝对误差
	float m_fTimeValue_AbsErrNeg;      //动作时间值负绝对误差
    float m_fTimeValue_RelErr;      //动作时间值相对误差
	long m_nTimeValue_ErrorLogic; 	//动作时间误差判断逻辑 
    float m_fUActVal_AbsErr; 		//电压动作值绝对误差
	float m_fUActVal_RelErr; 		//电压动作值相对误差 		
	long m_nUActVal_ErrorLogic; 	//电压动作值误差判断逻辑 	
	float m_fIActVal_AbsErr; 		//电流动作值绝对误差 		
	float m_fIActVal_RelErr; 		//电流动作值相对误差 		
    long m_nIActVal_ErrorLogic; 	//电流动作值误差判断逻辑

public:
    void init()
    {
        m_bBinStop = FALSE; //试验开始改成FALSE，安扭锁过以后，就改成TRUE；20201-7-1 周磊让改的；
        float fAngle[3] = {0, -120.0, 120.0};
		m_nFuncType = 0;
        m_nHarmMode = 0;
        m_bLock = false;
        m_bAuto = false;
        m_fBaseFre = 50;
        m_fOutPutTime = 0.000001f;
        m_fVolAux = 0;
        m_fCurAux = 0;
        m_nGradientChSelect = 0;
        m_nGradientTpSelect = 0;
		m_nVolChSelect = 0;
		m_nCurChSelect = 0;

		m_fTimeSet =0; 
		m_fUSet=0;		
		m_fISet=0;		
        m_fTimeValue_AbsErr = 0.001f;
		m_fTimeValue_AbsErrNeg = 0.001f;
        m_fTimeValue_RelErr = 0.1f;
        m_nTimeValue_ErrorLogic = 0;
        m_fUActVal_AbsErr = 0.001f;
		m_fUActVal_RelErr = 0.1f;	
        m_nUActVal_ErrorLogic = 0;
		m_fIActVal_AbsErr = 0.001f; 				
		m_fIActVal_RelErr = 0.1f; 		
		m_nIActVal_ErrorLogic = 0; 	
        m_nVarIndexType = 0;


        m_oHarmGradient.init();
        m_oBinaryConfig.init();

        for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
        {
            m_uiVOL[i].Harm[1].fAmp = 0;
            m_uiVOL[i].Harm[1].m_bSelect = TRUE;
            m_uiCUR[i].Harm[1].fAmp = 0;
            m_uiCUR[i].Harm[1].m_bSelect = TRUE;
            m_uiVOL[i].Harm[1].fAngle = m_uiCUR[i].Harm[1].fAngle = fAngle[i % 3];
            m_uiVOL[i].Harm[0].fAmp = m_uiCUR[i].Harm[0].fAmp = 0;
            m_uiVOL[i].Harm[0].m_bSelect = TRUE;
            m_uiCUR[i].Harm[0].m_bSelect = TRUE;

            for(int j = 2; j < MAX_HARM_COUNT; j++)
            {
                m_uiVOL[i].Harm[j].fAngle = m_uiCUR[i].Harm[j].fAngle = fAngle[i % 3];
                m_uiVOL[i].Harm[j].fAmp = m_uiCUR[i].Harm[j].fAmp = 0;
                m_uiVOL[i].Harm[j].m_bSelect = TRUE;
                m_uiCUR[i].Harm[j].m_bSelect = TRUE;
            }

            m_uiVOL[i].InterHarm.fAmp = m_uiCUR[i].InterHarm.fAmp = 0;
            m_uiVOL[i].InterHarm.fAngle = m_uiCUR[i].InterHarm.fAngle = 0;
            m_uiVOL[i].InterHarm.fFreq = m_uiCUR[i].InterHarm.fFreq = 0;
            m_uiVOL[i].InterHarm.m_bSelect = TRUE;
            m_uiCUR[i].InterHarm.m_bSelect = TRUE;
        }

        for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
        {
            m_oGoosePub[nIndex].init();
        }
    }

    void setBaseAmp(float fAmp)
    {
        for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
        {
            m_uiVOL[i].Harm[1].fAmp = fAmp;
        }
    }

    void CopyOwn(tmt_harm_paras *pDest)
    {

		pDest->m_fTimeSet =m_fTimeSet; 
		pDest->m_fUSet=m_fUSet;		
		pDest->m_fISet=m_fISet;		
		

        pDest->m_fTimeValue_AbsErr = m_fTimeValue_AbsErr;
		pDest->m_fTimeValue_AbsErrNeg = m_fTimeValue_AbsErrNeg;
        pDest->m_fTimeValue_RelErr = m_fTimeValue_RelErr;
        pDest->m_nTimeValue_ErrorLogic = m_nTimeValue_ErrorLogic;
        pDest->m_fUActVal_AbsErr = m_fUActVal_AbsErr;
        pDest->m_fUActVal_RelErr = m_fUActVal_RelErr;
        pDest->m_nUActVal_ErrorLogic = m_nUActVal_ErrorLogic;
        pDest->m_fIActVal_AbsErr = m_fIActVal_AbsErr;
        pDest->m_fIActVal_RelErr = m_fIActVal_RelErr;
		pDest->m_nIActVal_ErrorLogic = m_nIActVal_ErrorLogic;	

        pDest->m_nVarIndexType = m_nVarIndexType;

    }

    void setBaseFree(float fFre)
    {
        int i = 0;
        int j = 1;
        m_fBaseFre = fFre;

        for(i = 0; i < MAX_VOLTAGE_COUNT; i++)
        {
            for(j = 1; j < MAX_HARM_COUNT; j++)
            {
                m_uiVOL[i].Harm[j].fFreq = fFre * j;
            }
        }

        for(i = 0; i < MAX_CURRENT_COUNT; i++)
        {
            for(j = 1; j < MAX_HARM_COUNT; j++)
            {
                m_uiCUR[i].Harm[j].fFreq = fFre * j;
            }
        }
    }
    void InitHarmGradient(bool bType_U)
    {
        m_oHarmGradient.fStart = 0;
        m_oHarmGradient.fStep = 0.5;
        m_oHarmGradient.fStepTime = 0.5;

        if(bType_U)
        {
            m_oHarmGradient.fEnd = 10;
        }
        else
        {
            m_oHarmGradient.fEnd = 5;
        }
    }

    void ClearHarmChs_SelectIndex();//把所有谐波通道(2次及以上谐波)的选择置为-1
    void SetHarmChsSelectIndex_BeforeClearZero();//点击清零按钮时,标记所有修改的通道

    tmt_harm_paras()
    {
        init();
    }
    virtual ~tmt_harm_paras() {}
} tmt_HarmParas;

typedef struct tmt_harm_result
{
public:
    int		m_nTripFlag;
    float	m_fTripTime;
    float	m_fActValue;
    float	m_frTestTime;							//实际试验时间

    float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间
    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT]; //变位次数
    float	m_frTimeBinExAct[MAX_ExBINARY_COUNT][64];		//每一个开入记录64次变位时间
    int		m_nrBinExSwitchCount[MAX_ExBINARY_COUNT]; //变位次数

    float	m_fReturnValue;
    float   m_fReturnCoef;
    float   m_fReturnTime;

public:
    void init()
    {
        m_nTripFlag = 0;
        m_fTripTime = 0;
        m_fActValue = 0;
        m_frTestTime = 0;
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

    tmt_harm_result()
    {
        init();
    }
    virtual ~tmt_harm_result() {}
} tmt_HarmResult;

typedef struct tmt_harm_test:    public TMT_PARAS_HEAD
{
public:
    tmt_HarmResult  m_oHarmResult;
    tmt_HarmParas    m_oHarmParas;

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_HarmTest);
        m_nVersion = 0x00010001;
        m_nTestState = 0;
        m_oHarmResult.init();
        m_oHarmParas.init();
    }

    tmt_harm_test()
    {
        init();
    }
    virtual ~tmt_harm_test() {}
} tmt_HarmTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_HarmTest();
void stt_init_paras(tmt_HarmParas *pParas);
void stt_init_results(tmt_HarmResult *pResults);
void stt_xml_serialize(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nHarmCount = MAX_HARM_COUNT);
void stt_xml_serialize(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum, long nHarmCount);
void stt_xml_serialize(tmt_HarmResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

//void stt_xml_serialize_ex(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, bool bSel);
CSttXmlSerializeBase *stt_xml_serialize(tmt_harm_test *pHarmTest, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum, long nHarmCount);


