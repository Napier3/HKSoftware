#pragma once

#include "../tmt_manu_test.h"

#define  STT_Power_Gradient_Ch_Sa                                     0
#define  STT_Power_Gradient_Ch_Sb                                     1
#define  STT_Power_Gradient_Ch_Sc                                     2
#define  STT_Power_Gradient_Ch_S				      3
#define  STT_Power_Gradient_Ch_Pa                                     4
#define  STT_Power_Gradient_Ch_Pb                                     5
#define  STT_Power_Gradient_Ch_Pc                                     6
#define  STT_Power_Gradient_Ch_Pabc                                   7
#define  STT_Power_Gradient_Ch_Qa                                     8
#define  STT_Power_Gradient_Ch_Qb                                     9
#define  STT_Power_Gradient_Ch_Qc                                     10
#define  STT_Power_Gradient_Ch_Qabc                                   11


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
//// 手动测试相关参数
//typedef struct tmt_power_gradient
//{
//    int		nMode;	// 0:始值-终值  1:始值-终值-始值 通用参数-变化参数
//    float	fStart; //变化始值
//    float	fEnd;   //变化终值
//    float	fStep;  //变化步长
//    float	fStepTime; //变化时间
//
//    void init()
//    {
//        nMode = 0;
//        fStart = 1;
//        fEnd = 10;
//        fStep = 0.5;
//        fStepTime = 1;
//    }
//
//    tmt_power_gradient()
//    {
//        init();
//    }
//} tmt_PowerGradient;

// 手动测试相关参数

typedef struct tmt_power_manu_paras
{
public:
    BOOL    m_bBinStop;//开入停止,接收UpdateParameter时底层更新变量
    BOOL	m_bAuto;
    BOOL       m_bLockChanged;//lock mark
    float       m_fOutPutTime;	// 最长输出时间
    tmt_channel m_uiVOL[4];
    tmt_ChannelPower m_uiPOW[3];//功率数组:有功无功等参数，下同

	float	    m_fTrigDelay; //触发后延时
    float       m_fFreq;    //频率,唯一的
    //开关量
    int		m_nBinLogic;			//0-或 1-与 触发逻辑
    tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT]; //开入
    tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];//开出
    tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//系统扩展开关量
    tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//系统扩展开关量

    int		 m_nGradientChSelect;	// 递变通道选择
    tmt_ManuGradient m_oPowerGradient;
    int	  m_nVarIndexType;//0=视在功率 1=有功功率 2=无功功率 

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];  //goose数据发送，需要

    //整定值
    float m_fTimeSet;   //动作整定时间 
	float m_fSpowerSet;       //视在功率整定值
	float m_fPpowerSet;       //有功功率整定值
	float m_fQpowerSet;		//无功功率整定值

    //评估
	float m_fTimeValue_AbsErrPos;      //动作时间值正绝对误差
	float m_fTimeValue_AbsErrNeg;      //动作时间值负绝对误差
    float m_fTimeValue_RelErr;      //动作时间值相对误差
    long m_nTimeValue_ErrorLogic; 	//动作时间误差判断逻辑

	float m_fSpowerValue_AbsErr;      //视在功率绝对误差
	float m_fSpowerValue_RelErr;      //视在功率相对误差
	long m_nSpowerValue_ErrorLogic; 	//视在功率误差判断逻辑

	float m_fPpowerValue_AbsErr;      //有功功率绝对误差
	float m_fPpowerValue_RelErr;      //有功功率相对误差
	long m_nPpowerValue_ErrorLogic; 	//有功功率误差判断逻辑

	float m_fQpowerValue_AbsErr;      //无功功率绝对误差
	float m_fQpowerValue_RelErr;      //无功功率相对误差
	long m_nQpowerValue_ErrorLogic; 	//无功功率误差判断逻辑

public:
    void init()
    {
        m_bBinStop = FALSE;
        float fAngle[3] = {0, -120.0, 120.0};
        m_bAuto = false;
        m_bLockChanged = false;
        m_fOutPutTime = 0.0f;
		m_fTrigDelay = 0;
        m_nBinLogic = 0;
        m_nGradientChSelect = STT_Power_Gradient_Ch_Sa;
        m_fFreq = 50.0f;
        m_fTimeSet = 0;
		m_fSpowerSet = 0;
		m_fPpowerSet = 0;
		m_fQpowerSet = 0;
		m_fTimeValue_AbsErrPos = 0.001f;
		m_fTimeValue_AbsErrNeg = 0.001f;
        m_fTimeValue_RelErr = 0.1f;
        m_nTimeValue_ErrorLogic = 0;
		m_fSpowerValue_AbsErr = 0.001f;   
		m_fSpowerValue_RelErr = 0.1f;      
		m_nSpowerValue_ErrorLogic = 0;; 	
		m_fPpowerValue_AbsErr = 0.001f;
		m_fPpowerValue_RelErr = 0.1f;
		m_nPpowerValue_ErrorLogic = 0;
		m_fQpowerValue_AbsErr = 0.001f; 		
		m_fQpowerValue_RelErr = 0.1f;		
		m_nQpowerValue_ErrorLogic = 0; 	
        m_nVarIndexType = 0;
        m_oPowerGradient.init();

		for(int i = 0; i < 4; i++)
        {
            m_uiVOL[i].Harm[0].fAmp = 0;
            m_uiVOL[i].Harm[1].fAmp = 0;
            m_uiVOL[i].Harm[1].fAngle = fAngle[i % 3];
            m_uiVOL[i].Harm[1].fFreq = 50;

            for(int harm = 0; harm < MAX_HARM_COUNT; harm++)
            {
                m_uiVOL[i].Harm[harm].init();
            }
        }

		for(int i = 0; i < 3; i++)
		{
			m_uiPOW[i].init();
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
        pDest->m_fTrigDelay = m_fTrigDelay;
		pDest->m_fSpowerSet = m_fSpowerSet;
		pDest->m_fPpowerSet = m_fPpowerSet;
		pDest->m_fQpowerSet = m_fQpowerSet;
		pDest->m_fTimeValue_AbsErrPos = m_fTimeValue_AbsErrPos;
		pDest->m_fTimeValue_AbsErrNeg = m_fTimeValue_AbsErrNeg;
        pDest->m_fTimeValue_RelErr = m_fTimeValue_RelErr;
        pDest->m_nTimeValue_ErrorLogic = m_nTimeValue_ErrorLogic;
		pDest->m_fSpowerValue_AbsErr = m_fSpowerValue_AbsErr;
		pDest->m_fSpowerValue_RelErr = m_fSpowerValue_RelErr;
		pDest->m_nSpowerValue_ErrorLogic = m_nSpowerValue_ErrorLogic;
		pDest->m_fPpowerValue_AbsErr = m_fPpowerValue_AbsErr;    
		pDest->m_fPpowerValue_RelErr = m_fPpowerValue_RelErr;      
		pDest->m_nPpowerValue_ErrorLogic = m_nPpowerValue_ErrorLogic; 	
		pDest->m_fQpowerValue_AbsErr = m_fQpowerValue_AbsErr; 		
		pDest->m_fQpowerValue_RelErr = m_fQpowerValue_RelErr;		
		pDest->m_nQpowerValue_ErrorLogic = m_nQpowerValue_ErrorLogic; 	
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

	//整定值
	float m_fTimeErrVal;		 //动作时间误差 
	float m_fSpowerErrVal;       //视在功率误差
	float m_fPpowerErrVal;       //有功功率误差
	float m_fQpowerErrVal;		//无功功率误差

public:
    virtual void init()
    {
        tmt_ManualResult::init();
		m_fTimeErrVal = 0;
		m_fSpowerErrVal = 0;
		m_fPpowerErrVal = 0;
		m_fQpowerErrVal = 0;
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
void stt_xml_serialize(tmt_PowerManuResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_PowerManuTest *pParas, CSttXmlSerializeBase *pXmlSierialize,long nVolGroupNum,long nCurGroupNum);

