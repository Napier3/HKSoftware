#pragma once

#include "tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_OVERDCVOLTAGE_TESTNAME_LEN	64
#define TMT_OVERDCVOLTAGE_GROUPID_LEN   32

typedef struct tmt_over_voltage_paras :public tmt_ImpedanceParas
{
public:
	float	m_fTSetting;		//装置故障动作时间定值（整定动作时间）
	double  m_fUSetting;         //整定动作电压

	float   m_fSettingOverVol; //过压整定值
	float   m_fSettingTime;    //过压整定动作时间

	//2022.5.23 caoxc 增加项目名称
	char m_pszTestName[TMT_OVERDCVOLTAGE_TESTNAME_LEN];
	//2022.5.26 caoxc 增加分组id
	char m_pszGroupID[TMT_OVERDCVOLTAGE_GROUPID_LEN];

public:
	virtual void init()
	{
		tmt_ImpedanceParas::init();
		m_fTSetting = 5.0f;
		m_fUSetting = 2.85f;

		m_fSettingOverVol = 8.0f;
		m_fSettingTime = 0.0f;
		//2022.5.23 caoxc
		memset(m_pszTestName, 0, TMT_OVERDCVOLTAGE_TESTNAME_LEN);
		//2022.5.26 caoxc
		memset(m_pszGroupID, 0, TMT_OVERDCVOLTAGE_GROUPID_LEN);
	}

}tmt_OverVoltageParas;

typedef struct tmt_over_voltage_paras_ex :public tmt_OverVoltageParas
{
public:
	char m_pszSetting[PARAS_RSLT_EXPR_LEN];   //整定动作电压表达式
	char m_pszTSetting[PARAS_RSLT_EXPR_LEN];  //整定动作时间表达式

	virtual void init()
	{
		tmt_OverVoltageParas::init();
		memset(m_pszSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszTSetting,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_OverVoltageParasEx;

typedef struct tmt_over_voltage_results :public tmt_ImpedanceResults
{
public:
	float    m_fZshort;    //短路阻抗
	float    m_fIShortAngle;   //短路电流相位角 
	float    m_fDcVoltage;

public:
	virtual void init()
	{
		m_fZshort = 0.0f;
		m_fIShortAngle = 90.0f;
		m_fDcVoltage = 0;
		tmt_ImpedanceResults::init();
	} 

}tmt_OverVoltageResults;

typedef struct tmt_over_voltage_test : public TMT_PARAS_HEAD
{
public:
	tmt_OverVoltageParasEx m_oOverVoltageParas;
	tmt_OverVoltageResults m_oOverVoltageResults;
	char m_szName[MAX_NAME_LEN];

	virtual void init()
	{
		init_head();
		strcpy(m_pszMacroID, STT_MACRO_ID_OverVoltageTest);
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		memset(m_szName, 0, MAX_NAME_LEN);
		memset(&m_oRsltExprMngr, 0, sizeof(TMT_PARAS_RSLT_EXPR_MNGR));

		m_oOverVoltageParas.init();
		m_oOverVoltageResults.init();
	}

	tmt_over_voltage_test(){	init();}
	virtual void clear_result(){	m_oOverVoltageResults.init();	}
	virtual ~tmt_over_voltage_test(){}

}tmt_OverVoltageTest;



void stt_init_paras(tmt_OverVoltageParas *pParas);
void stt_init_paras_ex(tmt_OverVoltageParasEx *pParas);
void stt_init_results(tmt_OverVoltageResults *pResults);

void stt_xml_serialize_OverVoltage(tmt_OverVoltageParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_OverVoltage_ex(tmt_OverVoltageParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_OverVoltageResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_OverVoltageTest *pTests, CSttXmlSerializeBase *pXmlSerialize);


