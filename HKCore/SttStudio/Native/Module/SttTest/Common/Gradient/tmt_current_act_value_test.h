#pragma once

#include "../tmt_gradient_test.h"
#include "../tmt_test_paras_head.h"


typedef struct tmt_current_act_value_paras :public tmt_GradientParas
{
public:
	float m_fSettingActTime;//整定动作时间
	float m_fSettingValue;//整定动作值
	float m_fMarginTime;//故障时间裕度
	int		m_nFaultType;	//故障类型
	int   m_nFaultDir;//故障方向  0:反方向;1:正方向

	float m_fImpAngle;
	float m_fFaultVol;//短路电压
	BOOL	m_bImitatePT;		//是否模拟PT断线
	int		m_nImitPTPhase;		//PT断线模拟相  A B C AB BC CA ABC

	
public:
	virtual void init()
	{
		tmt_GradientParas::init();
		m_nSttTestMode = GradientTest_Base;
		m_fSettingActTime = 0.1f;
		m_fMarginTime = 0.1f;
		m_fSettingValue = 1.0f;
		m_fStart = 4.9f;
		m_fStop = 5.1f;
		m_fStep = 0.1f;
		m_fStepTime = 0.1f;
		m_nFaultType = 0;
		m_nTestMode = Gradient_TestMode_ActValue;
		m_fImpAngle = 78.0f;
		m_fFaultVol = 50.0;
		m_bImitatePT = 0;
		m_nImitPTPhase = 0;
		m_nFaultDir = 1;
	} 

}tmt_CurrentActValueParas;

typedef struct tmt_cur_act_value_pnv_paras :public tmt_GradientParas
{
public:
    int		m_nFaultType;	//测试相别

public:
    virtual void init()
    {
        tmt_GradientParas::init();
        m_nSttTestMode = GradientTest_Base;
        m_fStart = 4.9f;
        m_fStop = 5.1f;
        m_fStep = 0.1f;
        m_fStepTime = 0.1f;
        m_nTestMode = Gradient_TestMode_ActValue;
        m_nFaultType = 0;
        m_nVarIndexType = 0;
    }

}tmt_CurActValuePnvParas;

typedef struct tmt_current_act_value_results :public tmt_GradientResult
{

public:
	virtual void init()
	{
		tmt_GradientResult::init();
	} 

}tmt_CurrentActValueResults;

typedef struct tmt_current_act_value_test : public TMT_PARAS_HEAD
{
public:
	tmt_CurrentActValueParas       m_oTmtParas;
	tmt_CurrentActValueResults   m_oTmtResults;

	void init()
	{
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_CurrentActValue);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oTmtParas.init();
		m_oTmtResults.init();
	}

	tmt_current_act_value_test()	{init();}
	virtual void clear_result(){	m_oTmtResults.init();	}
	virtual ~tmt_current_act_value_test(){}
}tmt_CurrentActValueTest;

typedef struct tmt_cur_act_value_pnv_test : public TMT_PARAS_HEAD
{
public:
    tmt_CurActValuePnvParas       m_oTmtParas;
    tmt_GradientResult            m_oTmtResults;

    void init()
    {
        init_head();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvVoltageActValue);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oTmtParas.init();
        m_oTmtResults.init();
    }

    tmt_cur_act_value_pnv_test()	{init();}
    virtual void clear_result(){	m_oTmtResults.init();	}
    virtual ~tmt_cur_act_value_pnv_test(){}
}tmt_CurActValuePnvTest;

void stt_init_paras(tmt_CurrentActValueParas *pParas);
void stt_init_results(tmt_CurrentActValueResults *pResults);
void stt_init_paras(tmt_CurActValuePnvParas *pParas);

void stt_xml_serialize(tmt_CurrentActValueParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_current_actvalue(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_CurActValuePnvParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_cur_actvalue_pnv(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);



CSttXmlSerializeBase* stt_xml_serialize(tmt_CurrentActValueTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_CurActValuePnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
