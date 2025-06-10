#pragma once

#include "tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_DISTANCE_SETTING_NUM                     5
#define TMT_DISTANCE_TESTNAME_LEN	64
#define TMT_DISTANCE_GROUPID_LEN	16

typedef struct tmt_distance_paras :public tmt_ImpedanceParas
{
public:
	float	m_fTSetting;		//装置故障动作时间定值
	float   m_fSettingLN[TMT_DISTANCE_SETTING_NUM];//接地距离整定值
	float   m_fSettingLL[TMT_DISTANCE_SETTING_NUM];//相间距离整定值
	float   m_fTSettingLN[TMT_DISTANCE_SETTING_NUM];//接地距离动作时间定值
	float   m_fTSettingLL[TMT_DISTANCE_SETTING_NUM];//相间距离动作时间定值

	//2022.5.25 caoxc
	char m_pszTestName[TMT_DISTANCE_TESTNAME_LEN];
	char m_pszGroupID[TMT_DISTANCE_GROUPID_LEN];

    //2024-3-26 Xuzhantao Pnv新增
    float m_fUNom;//额定电压

public:
	virtual void init()
	{
		tmt_ImpedanceParas::init();
		m_fTSetting = 5.0f;
		m_fSettingLN[0] = 3.0f;
		m_fSettingLN[1] = 5.0f;
		m_fSettingLN[2] = 6.0f;
		m_fSettingLN[3] = 7.0f;
		m_fSettingLN[4] = 8.0f;
		m_fSettingLL[0] = 6.0f;
		m_fSettingLL[1] = 7.0f;
		m_fSettingLL[2] = 8.0f;
		m_fSettingLL[3] = 9.0f;
		m_fSettingLL[4] = 10.0f;
		
		m_fTSettingLN[0] = 0.0f;
		m_fTSettingLN[1] = 0.5f;
		m_fTSettingLN[2] = 1.0f;
		m_fTSettingLN[3] = 1.5f;
		m_fTSettingLN[4] = 2.0f;
		m_fTSettingLL[0] = 0.0f;
		m_fTSettingLL[1] = 0.5f;
		m_fTSettingLL[2] = 1.0f;
		m_fTSettingLL[3] = 1.5f;
		m_fTSettingLL[4] = 2.0f;

		m_fPostFaultTime = 0.0f;//2023-12-04 wuxinyi 修改保护动作后持续时间默认0s；
        m_fUNom = 0;
		//2022.5.25 caoxc
		memset(m_pszTestName, 0, TMT_DISTANCE_TESTNAME_LEN);
		memset(m_pszGroupID, 0, TMT_DISTANCE_GROUPID_LEN);
	}

	void CopyOwn(tmt_distance_paras* pDest)
	{
		tmt_ImpedanceParas::CopyOwn(pDest);
		pDest->m_fTSetting = m_fTSetting;
        pDest->m_fUNom = m_fUNom;
	}

}tmt_DistanceParas;

typedef struct tmt_distance_paras_ex :public tmt_DistanceParas
{
public:
	char m_pszSetting[PARAS_RSLT_EXPR_LEN];
	char m_pszTSetting[PARAS_RSLT_EXPR_LEN];

	virtual void init()
	{
		tmt_DistanceParas::init();
		memset(m_pszSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszTSetting,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_DistanceParasEx;

typedef struct tmt_distance_paras_I :virtual public tmt_DistanceParas
{
public:
    int m_nBinState[MAX_BINARYIN_COUNT];//开入量状态.
    int m_nBinLogic;//0-或 1-与

    virtual void init()
    {
        tmt_DistanceParas::init();
        m_nBinLogic = 0;
        for (int nIndex = 0;  nIndex  <  MAX_BINARYIN_COUNT;  nIndex++)
        {
            m_nBinState[nIndex] = 0;
        }
    }
}tmt_DistanceParas_I;

typedef struct tmt_distance_results :public tmt_ImpedanceResults
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

	void CopyOwn(tmt_distance_results* pDest)
	{
		tmt_ImpedanceResults::CopyOwn(pDest);
		pDest->m_fZshort = m_fZshort;
		pDest->m_fIShortAngle = m_fIShortAngle;
	}

}tmt_DistanceResults;

typedef struct tmt_distance_test : public TMT_PARAS_HEAD
{
public:
	tmt_DistanceParasEx m_oDistanceParas;
	tmt_DistanceResults m_oDistanceResults;
	void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_Distance);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oDistanceParas.init();
		m_oDistanceResults.init();
//		init_head(); //2021-9-13  lijunqing
	}

	tmt_distance_test(){	init();}
	virtual void clear_result(){	m_oDistanceResults.init();	}
	virtual ~tmt_distance_test(){}
}tmt_DistanceTest;

typedef struct tmt_distance_test_I : public TMT_PARAS_HEAD
{
public:
    tmt_DistanceParas_I m_oDistanceParas;
    tmt_DistanceResults m_oDistanceResults;
    void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_Distance);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oDistanceParas.init();
        m_oDistanceResults.init();
//		init_head(); //2021-9-13  lijunqing
    }

    tmt_distance_test_I(){	init();}
    virtual void clear_result(){	m_oDistanceResults.init();	}
    virtual ~tmt_distance_test_I(){}
}tmt_DistanceTest_I;

void stt_init_paras(tmt_DistanceParas *pParas);
void stt_init_paras(tmt_DistanceParas_I *pParas);
void stt_init_paras_ex(tmt_DistanceParasEx *pParas);
void stt_init_results(tmt_DistanceResults *pResults);

void stt_xml_serialize(tmt_DistanceParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_I(tmt_DistanceParas_I *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_DistanceParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_DistanceResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DistanceTest_I *pTests, CSttXmlSerializeBase *pXmlSerialize);
