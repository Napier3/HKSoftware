#pragma once

#include "../tmt_manu_test.h"

#define  STT_Power_Gradient_Ch_U1_1                                     0
#define  STT_Power_Gradient_Ch_U1_2                                     1
#define  STT_Power_Gradient_Ch_U1_0                                     2
#define  STT_Power_Gradient_Ch_U2_1                                     3
#define  STT_Power_Gradient_Ch_U2_2                                     4
#define  STT_Power_Gradient_Ch_U2_0                                     5
#define  STT_Power_Gradient_Ch_P1_1                                     6
#define  STT_Power_Gradient_Ch_P1_2                                     7
#define  STT_Power_Gradient_Ch_P1_0                                     8
#define  STT_Power_Gradient_Ch_P2_1                                     9
#define  STT_Power_Gradient_Ch_P2_2                                    10
#define  STT_Power_Gradient_Ch_P2_0                                    11

typedef struct tmt_channel_power
{
public:

	float	m_fFpower; //功率因数
	float	m_fPpower; //有功功率
	float	m_fQpower; //无功功率

public:
	void init()
	{
		m_fFpower = 1.0f;
		m_fPpower = 0;
		m_fQpower = 0;
	}

	tmt_channel_power()
	{
		init();
	}
} tmt_ChannelPower;
// 手动测试相关参数
typedef struct tmt_power_gradient
{
    int		nMode;	// 0:始值-终值  1:始值-终值-始值 通用参数-变化参数
    float	fStart; //变化始值
    float	fEnd;   //变化终值
    float	fStep;  //变化步长
    float	fStepTime; //变化时间

    void init()
    {
        nMode = 0;
        fStart = 1;
        fEnd = 10;
        fStep = 0.5;
        fStepTime = 1;
    }

    tmt_power_gradient()
    {
        init();
    }
} tmt_PowerGradient;

typedef struct tmt_power_manu_paras
{
public:
    BOOL    m_bBinStop;//开入停止,接收UpdateParameter时底层更新变量
    BOOL	m_bAging;		//是否老化试验
    BOOL	m_bAuto;
    BOOL       m_bLockChanged;//lock mark
    float       m_fOutPutTime;	// 最长输出时间
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_ChannelPower m_uiPOW[MAX_VOLTAGE_COUNT];//add wangtao 20240605 功率数组:有功无功等参数，下同

	float	    m_fTrigDelay; //触发后延时
    float       m_fFreq;    //频率,唯一的
    //开关量
    int		m_nBinLogic;			//0-或 1-与 触发逻辑
    tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT]; //开入
    tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];//开出
    tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//系统扩展开关量
    tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//系统扩展开关量

    int		 m_nGradientChSelect;	// 递变通道选择
    tmt_PowerGradient m_oPowerGradient;
    int	  m_nVarIndexType;//0=电流 1=电压 2=频率->改为和功率相关的

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];  //goose数据发送，需要

    //整定值
    float m_fTimeSet;   //动作整定时间 
    float m_fActSet;       //动作整定值
    //float m_fTimeUSet;	//电压整定时间 
    float m_fUSet;		//电压整定动作值
    //float m_fPTimeSet;  //功率整定时间
	float m_fPSet;      //功率整定动作值
    float m_fHzSet;		//频率整定动作值
    float m_fRetCoefSet; //返回系数整定值


    //评估
    float m_fTimeValue_AbsErr;      //动作时间值绝对误差
    float m_fTimeValue_RelErr;      //动作时间值相对误差
    long m_nTimeValue_ErrorLogic; 	//动作时间误差判断逻辑

	float m_fActValue_AbsErr;      //动作值绝对误差
	float m_fActValue_RelErr;      //动作值相对误差
	long m_nActValue_ErrorLogic; 	//动作值误差判断逻辑

    float m_fUActVal_AbsErr; 		//电压动作值绝对误差
    float m_fUActVal_RelErr; 		//电压动作值相对误差
    long m_nUActVal_ErrorLogic; 	//电压动作值误差判断逻辑
                                
	float m_fPActVal_AbsErr; 		//功率动作值绝对误差
	float m_fPActVal_RelErr; 		//功率动作值相对误差
	long m_nPActVal_ErrorLogic; 	//功率动作值误差判断逻辑

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
		m_fTrigDelay = 0;
        m_nBinLogic = 0;
        m_nGradientChSelect = STT_Power_Gradient_Ch_U1_1;
        m_fFreq = 50.0f;
        m_fTimeSet = 0;
		m_fActSet = 0;
        m_fUSet = 0;
        m_fPSet = 0;
        m_fHzSet=0;
        m_fRetCoefSet = 0;
        m_fTimeValue_AbsErr = 0.001f;
        m_fTimeValue_RelErr = 0.1f;
        m_nTimeValue_ErrorLogic = 0;
		m_fActValue_AbsErr = 0.001f;     //动作值绝对误差
		m_fActValue_RelErr = 0.1f;      //动作值相对误差
		m_nActValue_ErrorLogic = 0;; 	//动作值误差判断逻辑
        m_fUActVal_AbsErr = 0.001f;
        m_fUActVal_RelErr = 0.1f;
        m_nUActVal_ErrorLogic = 0;
	    m_fPActVal_AbsErr = 0.001f; 		//功率动作值绝对误差
		m_fPActVal_RelErr = 0.1f;		//功率动作值相对误差
		m_nPActVal_ErrorLogic = 0; 	//功率动作值误差判断逻辑
        m_fRetCoef_AbsErr = 0.001f;
        m_fRetCoef_RelErr = 0.1f;
        m_nRetCoef_ErrorLogic = 0;
        m_nVarIndexType = 0;
        m_oPowerGradient.init();

        for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
        {
            m_uiVOL[i].Harm[0].fAmp = 0;
            m_uiVOL[i].Harm[1].fAmp = 0;
            m_uiVOL[i].Harm[1].fAngle = fAngle[i % 3];
            m_uiVOL[i].Harm[1].fFreq = 50;
            m_uiPOW[i].init();
            for(int harm = 0; harm < MAX_HARM_COUNT; harm++)
            {
                m_uiVOL[i].Harm[harm].init();
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

    void InitPowerGradient(bool bType_U)
    {
        m_oPowerGradient.fStart = 0;
        m_oPowerGradient.fStep = 0.5;
        m_oPowerGradient.fStepTime = 0.5;

        if(bType_U)
        {
            m_oPowerGradient.fEnd = 10;
        }
        else
        {
            m_oPowerGradient.fEnd = 5;
        }
    }

    void SetFundFreq(float fFreqValue)
    {
        for(int j = 0; j < MAX_VOLTAGE_COUNT; j++)
        {
            m_uiVOL[j].Harm[1].fFreq = fFreqValue;
        }
        m_fFreq = fFreqValue;
    }
    void CopyOwn(tmt_power_manu_paras *pDest)
    {
        pDest->m_fTimeSet = m_fTimeSet;
        pDest->m_fUSet = m_fUSet;
        pDest->m_fTrigDelay = m_fTrigDelay;
        pDest->m_fHzSet = m_fHzSet;
		pDest->m_fPSet = m_fPSet;
        pDest->m_fRetCoefSet = m_fRetCoefSet;
        pDest->m_fTimeValue_AbsErr = m_fTimeValue_AbsErr;
        pDest->m_fTimeValue_RelErr = m_fTimeValue_RelErr;
        pDest->m_nTimeValue_ErrorLogic = m_nTimeValue_ErrorLogic;
        pDest->m_fUActVal_AbsErr = m_fUActVal_AbsErr;
        pDest->m_fUActVal_RelErr = m_fUActVal_RelErr;
        pDest->m_nUActVal_ErrorLogic = m_nUActVal_ErrorLogic;  

		pDest->m_fActValue_AbsErr = m_fActValue_AbsErr;     //动作值绝对误差
		pDest->m_fActValue_RelErr = m_fActValue_RelErr;      //动作值相对误差
		pDest->m_nActValue_ErrorLogic = m_nActValue_ErrorLogic; 	//动作值误差判断逻辑
		pDest->m_fPActVal_AbsErr = m_fPActVal_AbsErr; 		//功率动作值绝对误差
		pDest->m_fPActVal_RelErr = m_fPActVal_RelErr;		//功率动作值相对误差
		pDest->m_nPActVal_ErrorLogic = m_nPActVal_ErrorLogic; 	//功率动作值误差判断逻辑

        pDest->m_fRetCoef_AbsErr = m_fRetCoef_AbsErr;
        pDest->m_fRetCoef_RelErr = m_fRetCoef_RelErr;
        pDest->m_nRetCoef_ErrorLogic = m_nRetCoef_ErrorLogic;
        pDest->m_nVarIndexType = m_nVarIndexType;
    }

    tmt_power_manu_paras()
    {
        init();
    }

} tmt_PowerManuParas;


typedef struct tmt_power_manu_result  : public tmt_ManualResult
{
public:


public:
    virtual void init()
    {
        tmt_ManualResult::init();
    }

    tmt_power_manu_result()
    {
        init();
    }
} tmt_PowerManuResult;


typedef struct tmt_power_manu_test : public TMT_PARAS_HEAD
{
public:
    tmt_PowerManuParas   m_oPowerManuParas;
    tmt_PowerManuResult m_oPowerManuResult;

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_PowerManuTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oPowerManuResult.init();
        m_oPowerManuParas.init();
    }

    tmt_power_manu_test()
    {
        init();
    }
} tmt_PowerManuTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_PowerManuTest();
void stt_init_paras(tmt_PowerManuParas *pParas);
void stt_init_results(tmt_PowerManuResult *pResults);
void stt_xml_serialize(tmt_PowerManuParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_PowerManuParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nVolGroupNum,long nCurGroupNum);
void stt_xml_serialize_Power(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, tmt_channel *puiVOL, tmt_channel *puiCUR,tmt_ChannelPower *puiPOW);
void stt_xml_serialize(tmt_PowerManuResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_PowerManuTest *pParas, CSttXmlSerializeBase *pXmlSierialize,long nVolGroupNum,long nCurGroupNum);

