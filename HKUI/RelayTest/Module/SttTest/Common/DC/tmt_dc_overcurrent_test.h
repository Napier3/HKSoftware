#pragma once

#include "../Impedance/tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_DCOVERCURRENT_SETTING_NUM                     4
#define TMT_DCOVERCURRENT_TESTNAME_LEN	64
#define TMT_DCOVERCURRENT_GROUPID_LEN		32

typedef struct tmt_dc_overcurrent_paras:public tmt_ImpedanceParas
{
public:
    long m_nFaultChannel;//故障通道
    float	m_fTSetting;		//装置故障动作时间定值
    double m_fVoltage;

    float m_fPreFaultVol;//故障前电压    //单位为kv
    float m_fPreFaultCur;//故障前电流
    float m_fAfterTriggerFaultTime;		//保护动作后持续时间  2.000f
    float m_fFaultTime;//故障时间裕度

    float   m_fSettingDCOverCur[TMT_DCOVERCURRENT_SETTING_NUM];//
    float   m_fSettingTime[TMT_DCOVERCURRENT_SETTING_NUM];//
	int m_nSettingMethod;//整定方式 0标幺值 1有名值
	float m_fRatePrimaryCurr;//一次额定电流

    char m_pszTestName[TMT_DCOVERCURRENT_TESTNAME_LEN];
    //2022.5.26 caoxc 增加分组id
    char m_pszGroupID[TMT_DCOVERCURRENT_GROUPID_LEN];
    //开关量
    int	  m_nBinLogic;			//0-或 1-与
    tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
    tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-故障前开出 1-故障态开出
    tmt_BinaryOut m_binOutEx[2][MAX_ExBINARY_COUNT];//0-故障前开出 1-故障态开出
public:
    virtual void init()
    {
        tmt_ImpedanceParas::init();
		m_nFaultChannel=0;
        m_fTSetting = 5.0f;
        m_fVoltage = 0.0f;
		m_fFaultTime = 0.0f;
        m_fPreFaultVol = 0.0f;
        m_fPreFaultCur = 0.0f;
        m_fAfterTriggerFaultTime = 0.0f;

        m_fSettingDCOverCur[0] = 8.0f;
        m_fSettingDCOverCur[1] = 7.0f;
        m_fSettingDCOverCur[2] = 6.0f;
        m_fSettingDCOverCur[3] = 5.0f;
        m_fSettingTime[0] = 0.0f;
        m_fSettingTime[1] = 0.5f;
        m_fSettingTime[2] = 1.0f;
        m_fSettingTime[3] = 1.5f;
		m_nSettingMethod = 1;
		m_fRatePrimaryCurr = 2000.0f;

        memset(m_pszTestName, 0, TMT_DCOVERCURRENT_TESTNAME_LEN);
        //2022.5.26 caoxc
        memset(m_pszGroupID, 0, TMT_DCOVERCURRENT_GROUPID_LEN);
    }
}tmt_DCOverCurrentParas;

typedef struct tmt_dc_overcurrent_paras_ex :public tmt_DCOverCurrentParas
{
public:
    char m_pszSetting[PARAS_RSLT_EXPR_LEN];
    char m_pszTSetting[PARAS_RSLT_EXPR_LEN];

    virtual void init()
    {
        tmt_DCOverCurrentParas::init();
		memset(m_pszSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszTSetting,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_DCOverCurrentParasEx;

typedef struct tmt_dc_overcurrent_results :public tmt_ImpedanceResults
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

}tmt_DCOverCurrentResults;

typedef struct tmt_dc_overcurrent_test : public TMT_PARAS_HEAD
{
public:
    tmt_DCOverCurrentParasEx m_oDCOverCurrentParas;
    tmt_DCOverCurrentResults m_oDCOverCurrentResults;
    char m_szName[MAX_NAME_LEN];

    virtual void init()
    {
		init_head();
		strcpy(m_pszMacroID, STT_MACRO_ID_DCOverCurrentTest);
        m_nVersion = 0x00010001;
        m_nTestState = 0;
        memset(m_szName, 0, MAX_NAME_LEN);
        memset(&m_oRsltExprMngr, 0, sizeof(TMT_PARAS_RSLT_EXPR_MNGR));

        m_oDCOverCurrentParas.init();
        m_oDCOverCurrentResults.init();
    }

    tmt_dc_overcurrent_test()
    {
        init();
    }
    virtual void clear_result()
    {
        m_oDCOverCurrentResults.init();
    }
	virtual ~tmt_dc_overcurrent_test(){}

}tmt_DCOverCurrentTest;

void stt_init_paras(tmt_DCOverCurrentParas *pParas);
void stt_init_paras_ex(tmt_DCOverCurrentParasEx *pParas);
void stt_init_results(tmt_DCOverCurrentResults *pResults);

void stt_xml_serialize_DCOverCurrent(tmt_DCOverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_DCOverCurrent_ex(tmt_DCOverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_DCOverCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DCOverCurrentTest *pTests, CSttXmlSerializeBase *pXmlSerialize);


