#pragma once

#include "tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_OVERCURRENT_SETTING_NUM                     5
#define TMT_OVERCURRENT_TESTNAME_LEN	64
#define TMT_OVERCURRENT_GROUPID_LEN		32

typedef struct tmt_over_current_paras :public tmt_ImpedanceParas
{
public:
	float	m_fTSetting;		//装置故障动作时间定值

	float   m_fSettingOverCur[TMT_OVERCURRENT_SETTING_NUM];//
	float   m_fSettingTime[TMT_OVERCURRENT_SETTING_NUM];//

	float  m_fVolAmp[8];//常态及故障态电压幅值Ua\Ub\Uc\Uz
	float  m_fVolAng[8];//常态及故障态电压相位Ua\Ub\Uc\Uz

	//2022.5.23 caoxc 增加项目名称
	char m_pszTestName[TMT_OVERCURRENT_TESTNAME_LEN];
	//2022.5.26 caoxc 增加分组id
	char m_pszGroupID[TMT_OVERCURRENT_GROUPID_LEN];

    //2024-3-26 Xuzhantao Pnv新增
    float m_fUNom;//额定电压

public:
	virtual void init()
	{
		tmt_ImpedanceParas::init();
		m_fTSetting = 5.0f;

		m_fSettingOverCur[0] = 8.0f;
		m_fSettingOverCur[1] = 7.0f;
		m_fSettingOverCur[2] = 6.0f;
		m_fSettingOverCur[3] = 5.0f;
		m_fSettingOverCur[4] = 3.0f;
		m_fSettingTime[0] = 0.0f;
		m_fSettingTime[1] = 0.5f;
		m_fSettingTime[2] = 1.0f;
		m_fSettingTime[3] = 1.5f;
		m_fSettingTime[4] = 2.0f;
		//2022.5.23 caoxc
		memset(m_pszTestName, 0, TMT_OVERCURRENT_TESTNAME_LEN);
		//2022.5.26 caoxc
		memset(m_pszGroupID, 0, TMT_OVERCURRENT_GROUPID_LEN);

		for (int nIndex = 0;nIndex<8;nIndex++)
		{
			m_fVolAmp[nIndex] = 57.74f;
			m_fVolAng[nIndex] = 0.0f;
		}

		m_fVolAng[1] = -120.0f;
		m_fVolAng[2] = 120.0f;

		m_fVolAng[5] = -120.0f;
		m_fVolAng[6] = 120.0f;
        m_fUNom = 0;
	}

}tmt_OverCurrentParas;

typedef struct tmt_over_current_paras_ex :public tmt_OverCurrentParas
{
public:
	char m_pszSetting[PARAS_RSLT_EXPR_LEN];
	char m_pszTSetting[PARAS_RSLT_EXPR_LEN];

	virtual void init()
	{
		tmt_OverCurrentParas::init();
		memset(m_pszSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszTSetting,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_OverCurrentParasEx;

typedef struct tmt_over_current_results :public tmt_ImpedanceResults
{
public:
	float    m_fZshort;    //短路阻抗
	float    m_fIShortAngle;   //短路电流相位角 

public:
	virtual void init()
	{
		m_fZshort = 0.0f;
		m_fIShortAngle = 90.0f;
		tmt_ImpedanceResults::init();
	} 

}tmt_OverCurrentResults;

typedef struct tmt_over_current_test : public TMT_PARAS_HEAD
{
public:
	tmt_OverCurrentParasEx m_oOverCurrentParas;
	tmt_OverCurrentResults m_oOverCurrentResults;
	char m_szName[MAX_NAME_LEN];

	virtual void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_OverCurrent);
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		memset(m_szName, 0, MAX_NAME_LEN);
		memset(&m_oRsltExprMngr, 0, sizeof(TMT_PARAS_RSLT_EXPR_MNGR));

		m_oOverCurrentParas.init();
		m_oOverCurrentResults.init();
	}

	tmt_over_current_test(){	init();}
	virtual void clear_result(){	m_oOverCurrentResults.init();	}
	virtual ~tmt_over_current_test(){}

}tmt_OverCurrentTest;

typedef struct tmt_state_over_current_test : public tmt_OverCurrentTest
{
public:

	virtual void init()
	{
		tmt_OverCurrentTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_StateOverCurrent);
	}

	tmt_state_over_current_test(){	init();}
	virtual ~tmt_state_over_current_test(){}
}tmt_StateOverCurrentTest;


void stt_init_paras(tmt_OverCurrentParas *pParas);
void stt_init_paras_ex(tmt_OverCurrentParasEx *pParas);
void stt_init_results(tmt_OverCurrentResults *pResults);

void stt_xml_serialize_StateOverCurrent(tmt_OverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_OverCurrent(tmt_OverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_StateOverCurrent_ex(tmt_OverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_OverCurrent_ex(tmt_OverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_OverCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_OverCurrentTest *pTests, CSttXmlSerializeBase *pXmlSerialize);


