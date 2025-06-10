#pragma once

#include "tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_POWERFREQ_TESTNAME_LEN	64

typedef struct tmt_power_freq_paras :public tmt_ImpedanceParas
{
public:
	//故障参数
	float	m_fCalCoef;
	float	m_fTSetting;		//装置故障动作时间定值

	float m_fPostSensAngle;//该参数在实际计算时未用到,等待后期验证
	float m_fOffsetAngleLN;//该参数在实际计算时未用到,等待后期验证
	float m_fOffsetAngleLL;//该参数在实际计算时未用到,等待后期验证

	//2022.5.26 caoxc 增加项目名称
	char m_pszTestName[TMT_POWERFREQ_TESTNAME_LEN];

public:
	virtual void init()
	{
		tmt_ImpedanceParas::init();
		m_nK0CalMode = 0;
		m_fK0Angle = 0;
		m_fCalCoef = 0.9f;
		m_fTSetting = 2.0f;
		m_fPostSensAngle = 78.0f;
		m_fOffsetAngleLN = 0.0f;
		m_fOffsetAngleLL = 0.0f;

		//2022.5.26 caoxc
		memset(m_pszTestName, 0, TMT_POWERFREQ_TESTNAME_LEN);
	}

	void CopyOwn(tmt_power_freq_paras* pDest)
	{
		tmt_ImpedanceParas::CopyOwn(pDest);
		pDest->m_fTSetting = m_fTSetting;
	}

}tmt_PowerFreqParas;

typedef struct tmt_power_freq_paras_ex :public tmt_PowerFreqParas
{
public:
	char m_pszImpAngle[PARAS_RSLT_EXPR_LEN];

	virtual void init()
	{
		tmt_PowerFreqParas::init();
		memset(m_pszImpAngle,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_PowerFreqParasEx;

typedef struct tmt_power_freq_results :public tmt_ImpedanceResults
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

	void CopyOwn(tmt_power_freq_results* pDest)
	{
		tmt_ImpedanceResults::CopyOwn(pDest);
		pDest->m_fZshort = m_fZshort;
		pDest->m_fIShortAngle = m_fIShortAngle;
	}

}tmt_PowerFreqResults;

typedef struct tmt_power_freq_test : public TMT_PARAS_HEAD
{
public:
	tmt_PowerFreqParasEx m_oPowerFreqParas;
	tmt_PowerFreqResults m_oPowerFreqResults;
	void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuPowerFreqDist);
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		m_nSelected = 1;

		m_oPowerFreqParas.init();
		m_oPowerFreqResults.init();
	}

	tmt_power_freq_test(){	init();}
	virtual void clear_result(){	m_oPowerFreqResults.init();	}
	virtual ~tmt_power_freq_test(){}
}tmt_PowerFreqTest;

void stt_init_paras(tmt_PowerFreqParas *pParas);
void stt_init_parasEx(tmt_PowerFreqParasEx *pParas);
void stt_init_results(tmt_PowerFreqResults *pResults);

void stt_xml_serialize(tmt_PowerFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_PowerFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_PowerFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_PowerFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
