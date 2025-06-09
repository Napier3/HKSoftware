#pragma once

#include "tmt_action_time_test.h"

typedef struct tmt_current_inverse_time_paras :public tmt_action_time_paras
{
	long m_nRefValueType;//基准值类型(0-In;1-Iset1;2-Iset2;3-Iset3;4-In*Ip)
	float m_fIset1;
	float m_fIset2;
	float m_fIset3;
	float m_fTset1;
	float m_fTset2;
	float m_fTset3;
	
public:
	virtual void init()
	{
		tmt_action_time_paras::init();
		m_nRefValueType = 0;
		m_fIset1 = 5.0f;
		m_fIset2 = 3.0f;
		m_fIset3 = 2.0f;
		m_fTset1 = 0.5f;
		m_fTset2 = 1.0f;
		m_fTset3 = 2.0f;
	} 

}tmt_ActionTimeParas;

typedef struct tmt_action_time_results
{
	float m_fTripTime;
	long m_nAct;

public:
	virtual void init()
	{
		m_fTripTime = 0.0f;
		m_nAct = 0;
	} 

}tmt_ActionTimeResults;


typedef struct tmt_action_time_test : public TMT_PARAS_HEAD
{
public:
	tmt_ActionTimeParas      m_oActionTimeParas ;
	tmt_ActionTimeResults   m_oActionTimeResults;


	void init()
	{
		strcpy(m_pszMacroID, STT_MACRO_ID_ActionTime);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oActionTimeParas.init();
		m_oActionTimeResults.init();
	}

	tmt_action_time_test()	{init();}
	virtual ~tmt_action_time_test(){}
}tmt_ActionTimeTest;

void stt_init_paras(tmt_ActionTimeParas *pParas);
void stt_init_results(tmt_ActionTimeResults *pResults);

void stt_xml_serialize(tmt_ActionTimeParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum);
void stt_xml_serialize(tmt_ActionTimeResults *pResults, CSttXmlSerializeBase *pXmlSierialize,long nBinExNum,long nBoutExNum);

CSttXmlSerializeBase* stt_xml_serialize(tmt_ActionTimeTest *pTests, CSttXmlSerializeBase *pXmlSerialize,long nBinExNum,long nBoutExNum);