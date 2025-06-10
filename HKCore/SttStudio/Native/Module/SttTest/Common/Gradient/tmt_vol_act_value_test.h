#pragma once

#include "../tmt_gradient_test.h"
#include "../tmt_test_paras_head.h"


typedef struct tmt_vol_act_value_paras :public tmt_GradientParas
{
public:
	int		m_nFaultType;	//故障类型
	float m_fImpAngle;
	float m_fFaultCurrent;//短路电流

	
public:
	virtual void init()
	{
		tmt_GradientParas::init();
		m_nSttTestMode = GradientTest_Base;
		m_fStart = 4.9f;
		m_fStop = 5.1f;
		m_fStep = 0.1f;
		m_fStepTime = 0.1f;
		m_nFaultType = 0;
		m_nTestMode = Gradient_TestMode_ActValue;
		m_fImpAngle = 78.0f;
		m_fFaultCurrent = 1.0;
	} 

}tmt_VolActValueParas;


typedef struct tmt_vol_act_value_results :public tmt_GradientResult
{

public:
	virtual void init()
	{
		tmt_GradientResult::init();
	} 

}tmt_VolActValueResults;

typedef struct tmt_vol_act_value_pnv_paras :public tmt_GradientParas
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
        m_nVarIndexType = 1;
    }

}tmt_VolActValuePnvParas;

typedef struct tmt_vol_act_value_test : public TMT_PARAS_HEAD
{
public:
	tmt_VolActValueParas       m_oTmtParas;
	tmt_VolActValueResults   m_oTmtResults;

	void init()
	{
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_VoltageActValue);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oTmtParas.init();
		m_oTmtResults.init();
	}

	tmt_vol_act_value_test()	{init();}
	virtual void clear_result(){	m_oTmtResults.init();	}
	virtual ~tmt_vol_act_value_test(){}
}tmt_VolActValueTest;

typedef struct tmt_vol_act_value_pnv_test : public TMT_PARAS_HEAD
{
public:
    tmt_VolActValuePnvParas       m_oTmtParas;
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

    tmt_vol_act_value_pnv_test()	{init();}
    virtual void clear_result(){	m_oTmtResults.init();	}
    virtual ~tmt_vol_act_value_pnv_test(){}
}tmt_VolActValuePnvTest;

void stt_init_paras(tmt_VolActValueParas *pParas);
void stt_init_results(tmt_VolActValueResults *pResults);
void stt_init_paras(tmt_VolActValuePnvParas *pParas);


void stt_xml_serialize(tmt_VolActValueParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_vol_actvalue(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_VolActValuePnvParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_vol_actvalue_pnv(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);



CSttXmlSerializeBase* stt_xml_serialize(tmt_VolActValueTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_VolActValuePnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize);

