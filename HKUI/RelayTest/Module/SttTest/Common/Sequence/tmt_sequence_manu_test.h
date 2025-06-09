#pragma once

#include "../tmt_manu_test.h"

#define  STT_Sequence_Gradient_Ch_U1_1                                     0
#define  STT_Sequence_Gradient_Ch_U1_2                                     1
#define  STT_Sequence_Gradient_Ch_U1_0                                     2
#define  STT_Sequence_Gradient_Ch_U2_1                                     3
#define  STT_Sequence_Gradient_Ch_U2_2                                     4
#define  STT_Sequence_Gradient_Ch_U2_0                                     5
#define  STT_Sequence_Gradient_Ch_I1_1                                     6
#define  STT_Sequence_Gradient_Ch_I1_2                                     7
#define  STT_Sequence_Gradient_Ch_I1_0                                     8
#define  STT_Sequence_Gradient_Ch_I2_1                                     9
#define  STT_Sequence_Gradient_Ch_I2_2                                    10
#define  STT_Sequence_Gradient_Ch_I2_0                                    11

// 手动测试相关参数
typedef struct tmt_sequence_gradient
{
    int		nMode;	// 0:始值-终值  1:始值-终值-始值
    float	fStart;
    float	fEnd;
    float	fStep;
    float	fStepTime;
	float	fMarginTime;
    float	fTrigDelay;

    void init()
    {
        nMode = 0;
        fStart = 1;
        fEnd = 10;
        fTrigDelay = 0;
        fStep = 0.5;
        fStepTime = 1;
		fMarginTime = 0;
    }

    tmt_sequence_gradient()
    {
        init();
    }
} tmt_SequenceGradient;

typedef struct tmt_sequence_manu_paras
{
public:
    BOOL    m_bBinStop;//开入停止,接收UpdateParameter时底层更新变量
    BOOL	m_bAging;		//是否老化试验
    BOOL	m_bAuto;
    BOOL       m_bLockChanged;//lock mark
    float       m_fOutPutTime;	// 最长输出时间
//	float       m_fOverloadDelaytime;	//过载延时  单位秒 功能：测试仪在开始输出的设定时间之，检测到过载不切断输出
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    float       m_fFreq;
    //开关量
    int		m_nBinLogic;			//0-或 1-与
    tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];
    tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//系统扩展开关量
    tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//系统扩展开关量
    int		 m_nGradientTpSelect;	// 递变类型选择 0-幅值  1-相位
    int		 m_nGradientChSelect;	// 递变通道选择
    tmt_SequenceGradient m_oSequenceGradient;
    int	  m_nVarIndexType;//0=电流 1=电压 2=频率

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];

    //整定值
    float m_fTimeSet;   //动作整定时间
    float m_fUSet;		//电压整定动作值
    float m_fISet;		//电流整定动作值
    float m_fAngleSet;	//相位整定动作值
    float m_fHzSet;		//频率整定动作值
    float m_fRetCoefSet; //返回系数整定值


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
    float m_fAngleActVal_AbsErr; 	//相位动作值绝对误差
    float m_fAngleActVal_RelErr; 	//相位动作值相对误差
    long m_nAngleActVal_ErrorLogic; //相位动作值误差判断逻辑
    float m_fHzActVal_AbsErr; 		//频率动作值绝对误差
    float m_fHzActVal_RelErr; 		//频率动作值相对误差
    long m_nHzActVal_ErrorLogic; 	//频率动作值误差判断逻辑
    float m_fRetCoef_AbsErr; 		//返回系数绝对误差
    float m_fRetCoef_RelErr;		//返回系数相对误差
    long m_nRetCoef_ErrorLogic; 	//返回系数误差判断逻辑

public:
    void init()
    {
        m_bBinStop = FALSE;
        float fAngle[3] = {0, -120.0, 120.0};
        m_bAging = false;
        m_bAuto = false;
        m_bLockChanged = false;
        m_fOutPutTime = 0.000001f;
        m_nBinLogic = 0;
        m_nGradientChSelect = STT_Sequence_Gradient_Ch_U1_1;
        m_nGradientTpSelect = 0;
        m_fFreq = 50.0f;
        m_fTimeSet = 0;
        m_fUSet = 0;
        m_fISet = 0;
        m_fAngleSet = 0;
        //m_fHzSet=0;
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
        m_fRetCoef_AbsErr = 0.001f;
        m_fRetCoef_RelErr = 0.1f;
        m_nRetCoef_ErrorLogic = 0;
        m_nVarIndexType = 0;
		m_fTimeValue_AbsErrNeg = 0.001f;
        m_oSequenceGradient.init();

        for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
        {
            m_uiVOL[i].Harm[0].fAmp = 0;
            m_uiCUR[i].Harm[0].fAmp = 0;
            m_uiVOL[i].Harm[1].fAmp = 0;
            m_uiCUR[i].Harm[1].fAmp = 0;
            m_uiVOL[i].Harm[1].fAngle = m_uiCUR[i].Harm[1].fAngle = fAngle[i % 3];
            m_uiVOL[i].Harm[1].fFreq = m_uiCUR[i].Harm[1].fFreq = 50;

            for(int harm = 0; harm < MAX_HARM_COUNT; harm++)
            {
                m_uiVOL[i].Harm[harm].init();
                m_uiCUR[i].Harm[harm].init();
            }
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
            m_binInEx[j].nSelect = 0;//默认扩增开入不选中
            m_binInEx[j].nTrigMode = 0;
        }

        for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
        {
            m_binOutEx[j].nState = 0;//默认扩增开出全断开
            m_binOutEx[j].nMode = 0;
            m_binOutEx[j].fTimeTrig = 0;
            m_binOutEx[j].fHoldTime = 0;
        }

        for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
        {
            m_oGoosePub[nIndex].init();
        }
    }

    void InitSequenceGradient(bool bType_U)
    {
        m_oSequenceGradient.fStart = 0;
        m_oSequenceGradient.fStep = 0.5;
        m_oSequenceGradient.fStepTime = 0.5;

        if(bType_U)
        {
            m_oSequenceGradient.fEnd = 10;
        }
        else
        {
            m_oSequenceGradient.fEnd = 5;
        }
    }

    void SetFundFreq(float fFreqValue)
    {
        for(int j = 0; j < MAX_VOLTAGE_COUNT; j++)
        {
            m_uiVOL[j].Harm[1].fFreq = fFreqValue;
            m_uiCUR[j].Harm[1].fFreq = fFreqValue;
        }
    }
    void CopyOwn(tmt_sequence_manu_paras *pDest)
    {
        pDest->m_fTimeSet = m_fTimeSet;
        pDest->m_fUSet = m_fUSet;
        pDest->m_fISet = m_fISet;
        pDest->m_fAngleSet = m_fAngleSet;
        pDest->m_fHzSet = m_fHzSet;
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
        pDest->m_fRetCoef_AbsErr = m_fRetCoef_AbsErr;
        pDest->m_fRetCoef_RelErr = m_fRetCoef_RelErr;
        pDest->m_nRetCoef_ErrorLogic = m_nRetCoef_ErrorLogic;
        pDest->m_nVarIndexType = m_nVarIndexType;
	pDest->m_fTimeValue_AbsErrNeg = m_fTimeValue_AbsErrNeg;
    }

    tmt_sequence_manu_paras()
    {
        init();
    }

} tmt_SequenceManuParas;


typedef struct tmt_sequence_manu_result  : public tmt_ManualResult
{
public:


public:
    virtual void init()
    {
        tmt_ManualResult::init();
    }

    tmt_sequence_manu_result()
    {
        init();
    }
} tmt_SequenceManuResult;


typedef struct tmt_sequence_manu_test : public TMT_PARAS_HEAD
{
public:
    tmt_SequenceManuParas   m_oSequenceManuParas;
    tmt_SequenceManuResult m_oSequenceManuResult;

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_SequenceManuTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oSequenceManuResult.init();
        m_oSequenceManuParas.init();
    }

    tmt_sequence_manu_test()
    {
        init();
    }
} tmt_SequenceManuTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_SequenceManuTest();
void stt_init_paras(tmt_SequenceManuParas *pParas);
void stt_init_results(tmt_SequenceManuResult *pResults);
void stt_xml_serialize(tmt_SequenceManuParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_SequenceManuParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nVolGroupNum,long nCurGroupNum);
void stt_xml_serialize_Sequence(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, tmt_channel *puiVOL, tmt_channel *puiCUR);
void stt_xml_serialize(tmt_SequenceManuResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_SequenceManuTest *pParas, CSttXmlSerializeBase *pXmlSierialize,long nVolGroupNum,long nCurGroupNum);

