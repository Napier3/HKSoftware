#pragma once

#include "../tmt_common_def.h"
#include"../../../SttTestBase/SttXmlSerialize.h"
#include "../tmt_manu_test.h"

typedef struct tmt_prim_freq_manual_paras : public tmt_manual_paras
{
public:
	int 	m_nOutputType;	//输出模式 0-不输出 1-转速脉冲 2-直流信号
	//脉冲
	int  	m_nSpeedPulseType;     // 脉冲信号类型  0-
	int  	m_nPulseWidth;       // 脉冲宽度（单位: us）
	int  	m_nPeakToPeakTypeIndex;    // 峰峰值下拉框选择
	float 	m_fPulseFreqHz;       // 脉冲频率（单位: Hz）

	//直流  
	float	m_frCurrentDc[2];//直流信号源
	int   	m_nDcOutputMode;      // 直流信号源模式 (频率/转速)
	float 	m_fDcOutputValue;     // 直流信号输出值
	float 	m_fGridFrequencyMinHz;  // 电网频率最小值
	float 	m_fGridFrequencyMaxHz;  // 电网频率最大值
	float 	m_fGenSpeedMinRpm;     // 发电机转速最小值
	float 	m_fGenSpeedMaxRpm;     // 发电机转速最大值
	float	 m_fDcCurrentMeasured;  // 直流电流测量值

public:
    void init()
    {
		tmt_manual_paras::init();
		m_nOutputType = 0;
		m_nSpeedPulseType = 0;    
		m_nPulseWidth = 0;      
		m_nPeakToPeakTypeIndex = 0;    
		m_fPulseFreqHz = 0.0f;       
		m_frCurrentDc[0] = 0.0f;
		m_frCurrentDc[1] = 0.0f;
		m_nDcOutputMode = 0;      
		m_fDcOutputValue= 0.0f;     
		m_fGridFrequencyMinHz= 0.0f;
		m_fGridFrequencyMaxHz= 0.0f;
		m_fGenSpeedMinRpm= 0.0f;    
		m_fGenSpeedMaxRpm= 0.0f;    
		m_fDcCurrentMeasured= 0.0f;

    }

	void CopyOwn(tmt_prim_freq_manual_paras *pDest)
	{
		tmt_manual_paras::CopyOwn(pDest);
		pDest->m_nOutputType = m_nOutputType;
		pDest->m_nSpeedPulseType = m_nSpeedPulseType;    
		pDest->m_nPulseWidth = m_nPulseWidth;      
		pDest->m_nPeakToPeakTypeIndex = m_nPeakToPeakTypeIndex;    
		pDest->m_fPulseFreqHz = m_fPulseFreqHz;       
		memcpy(pDest->m_frCurrentDc, m_frCurrentDc, sizeof(m_frCurrentDc));
		pDest->m_nDcOutputMode = m_nDcOutputMode;      
		pDest->m_fDcOutputValue= m_fDcOutputValue;     
		pDest->m_fGridFrequencyMinHz= m_fGridFrequencyMinHz;
		pDest->m_fGridFrequencyMaxHz= m_fGridFrequencyMaxHz;
		pDest->m_fGenSpeedMinRpm= m_fGenSpeedMinRpm;    
		pDest->m_fGenSpeedMaxRpm= m_fGenSpeedMaxRpm;    
		pDest->m_fDcCurrentMeasured= m_fDcCurrentMeasured;
	}

    tmt_prim_freq_manual_paras()
    {
        init();
    }

	virtual ~tmt_prim_freq_manual_paras()
	{

	}

}tmt_PrimFreqManualParas;

typedef struct tmt_prim_freq_manual_result : public tmt_manual_result
{

public:
    virtual void init()
    {
		tmt_manual_result::init();
    }

    void CopyOwn(tmt_prim_freq_manual_result *pDest)
    {
		tmt_manual_result::CopyOwn(pDest);
    }

    tmt_prim_freq_manual_result()
    {
        init();
    }
} tmt_PrimFreqManualResult;

typedef struct tmt_prim_freq_manual_test : public TMT_PARAS_HEAD
{
public:
    tmt_PrimFreqManualParas   m_oManuParas;
    tmt_PrimFreqManualResult  m_oManuResult;

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_PrimFreqManualTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oManuResult.init();
        m_oManuParas.init();
    }

    tmt_prim_freq_manual_test()
    {
        init();
    }
} tmt_PrimFreqManualTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_write_PrimFreqManuTest();
void stt_init_paras(tmt_PrimFreqManualParas *pParas);
void stt_init_results(tmt_PrimFreqManualResult *pResults);
void stt_xml_serialize(tmt_PrimFreqManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_PrimFreqManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);
void stt_xml_serialize_act_rcd(tmt_PrimFreqManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase *stt_xml_serialize(tmt_PrimFreqManualTest *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);

