#pragma once

#include "tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_ZEROCURRENT_SETTING_NUM                     5
#define TMT_ZEROCURRENT_TESTNAME_LEN	64
#define TMT_ZEROCURRENT_GROUPID_LEN		16

typedef struct tmt_zero_current_paras :public tmt_ImpedanceParas
{
public:
	float	m_fTSetting;		//װ�ù��϶���ʱ�䶨ֵ

	float   m_fSettingZeroCur[TMT_ZEROCURRENT_SETTING_NUM];//
	float   m_fSettingTime[TMT_ZEROCURRENT_SETTING_NUM];//
	float   m_fUnom;//���ѹ(Ϊ�����ϰ�ӿڳ�������)
	long    m_nIsAutoTest;//20230504 zhouhj ���Ӳ������������Ƿ��Զ�����ģʽ��,���ڴ���StateI0Current���ϴ�����ʽ����������Զ����Բ�һ�µ����
	float  m_fVolAmp[8];//��̬������̬��ѹ��ֵUa\Ub\Uc\Uz
	float  m_fVolAng[8];//��̬������̬��ѹ��λUa\Ub\Uc\Uz
	
	//2022.5.26 caoxc ������Ŀ���ƺͷ���
	char m_pszTestName[TMT_ZEROCURRENT_TESTNAME_LEN];
	char m_pszGroupID[TMT_ZEROCURRENT_GROUPID_LEN];

public:
	virtual void init()
	{
		tmt_ImpedanceParas::init();
		m_fTSetting = 5.0f;
		m_fUnom = 57.74f;

		m_fSettingZeroCur[0] = 8.0f;
		m_fSettingZeroCur[1] = 7.0f;
		m_fSettingZeroCur[2] = 6.0f;
		m_fSettingZeroCur[3] = 5.0f;
		m_fSettingZeroCur[4] = 3.0f;
		m_fSettingTime[0] = 0.0f;
		m_fSettingTime[1] = 0.5f;
		m_fSettingTime[2] = 1.0f;
		m_fSettingTime[3] = 1.5f;
		m_fSettingTime[4] = 2.0f;
		m_nIsAutoTest = 0;

		for (int nIndex = 0;nIndex<8;nIndex++)
		{
			m_fVolAmp[nIndex] = 57.74f;
			m_fVolAng[nIndex] = 0.0f;
		}

		m_fVolAng[1] = -120.0f;
		m_fVolAng[2] = 120.0f;

		m_fVolAng[5] = -120.0f;
		m_fVolAng[6] = 120.0f;
		//2022.5.26 caoxc
		memset(m_pszTestName, 0, TMT_ZEROCURRENT_TESTNAME_LEN);
		memset(m_pszGroupID, 0 ,TMT_ZEROCURRENT_GROUPID_LEN);
	}

}tmt_ZeroCurrentParas;

typedef struct tmt_zero_current_paras_ex :public tmt_ZeroCurrentParas
{
public:
	char m_pszSetting[PARAS_RSLT_EXPR_LEN];
	char m_pszTSetting[PARAS_RSLT_EXPR_LEN];

	virtual void init()
	{
		tmt_ZeroCurrentParas::init();
		memset(m_pszSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszTSetting,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_ZeroCurrentParasEx;

typedef struct tmt_zero_current_results :public tmt_ImpedanceResults
{
public:
	float    m_fZshort;    //��·�迹
	float    m_fIShortAngle;   //��·������λ�� 

public:
	virtual void init()
	{
		m_fZshort = 0.0f;
		m_fIShortAngle = 90.0f;
		tmt_ImpedanceResults::init();
	} 

}tmt_ZeroCurrentResults;


typedef struct tmt_zero_current_test : public TMT_PARAS_HEAD
{
public:
	tmt_ZeroCurrentParasEx m_oZeroCurrentParas;
	tmt_ZeroCurrentResults m_oZeroCurrentResults;
	virtual void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_ZeroCurrent);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oZeroCurrentParas.init();
		m_oZeroCurrentResults.init();
	}

	tmt_zero_current_test(){	init();}
	virtual void clear_result(){	m_oZeroCurrentResults.init();	}
	virtual ~tmt_zero_current_test(){}
}tmt_ZeroCurrentTest;

typedef struct tmt_state_zero_current_test : public tmt_ZeroCurrentTest
{
public:
	virtual void init()
	{
		tmt_ZeroCurrentTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_StateI0Current);
	}

	tmt_state_zero_current_test(){	init();}
	virtual ~tmt_state_zero_current_test(){}
}tmt_StateZeroCurrentTest;

void stt_init_paras(tmt_ZeroCurrentParas *pParas);
void stt_init_paras_ex(tmt_ZeroCurrentParasEx *pParas);
void stt_init_results(tmt_ZeroCurrentResults *pResults);

void stt_xml_serialize_ZeroCurrent(tmt_ZeroCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_StateZeroCurrent(tmt_ZeroCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ZeroCurrent_ex(tmt_ZeroCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_StateZeroCurrent_ex(tmt_ZeroCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ZeroCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_ZeroCurrentTest *pTests, CSttXmlSerializeBase *pXmlSerialize);



