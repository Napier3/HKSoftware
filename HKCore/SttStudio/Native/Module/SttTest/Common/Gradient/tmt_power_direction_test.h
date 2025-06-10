#pragma once

#include "../tmt_gradient_test.h"
#include "../tmt_test_paras_head.h"

#define POWER_DIR_TEST_PHASE_A                         0 
#define POWER_DIR_TEST_PHASE_B                         1 
#define POWER_DIR_TEST_PHASE_C                         2 
#define POWER_DIR_TEST_PHASE_ZERO                      3
#define POWER_DIR_TEST_PHASE_NEG                       4
#define POWER_DIR_TEST_PHASE_AB                        5
#define POWER_DIR_TEST_PHASE_BC                        6
#define POWER_DIR_TEST_PHASE_CA                        7
#define POWER_DIR_TEST_PHASE_ABC                       8

#define POWER_DIR_FAULT_PHASE_A                        0 
#define POWER_DIR_FAULT_PHASE_B                        1 
#define POWER_DIR_FAULT_PHASE_C                        2 
#define POWER_DIR_FAULT_PHASE_AB                       3 
#define POWER_DIR_FAULT_PHASE_BC                       4 
#define POWER_DIR_FAULT_PHASE_CA                       5 
#define POWER_DIR_FAULT_PHASE_ABC                      6 
#define POWER_DIR_FAULT_PHASE_ZERO                     7 
#define POWER_DIR_FAULT_PHASE_NEG                      8 


typedef struct tmt_power_direction_paras :public tmt_GradientParas
{
public:
	int		m_nTestPhase;	//测试相
	int		m_nFaultPhase;	//故障相
	float	m_fSCVoltage;
	float	m_fSCCurrent;

	int		m_nAngleMode;	//角度定义 0：电压超前电流为正   1：电流超前电压为正  
	int		m_nConnectMode;	//接线方式 0:0度接线     1:90度接线

	float m_fMaxSensAngle;//最大灵敏角度
	float m_fLeadAngle;//超前角度
	float m_fLagAngle;//滞后角度

    //Pnv
    float m_fAngleOffset;//角度测试偏移
    int m_nVarIndex;//测试相别
	
public:
	virtual void init()
	{
		tmt_GradientParas::init();
		m_nSttTestMode = GradientTest_URamp;
		m_fStart = 4.9f;
		m_fStop = 5.1f;
		m_fStep = 0.1f;
		m_fStepTime = 0.1f;
		m_nTestPhase = POWER_DIR_TEST_PHASE_A;
		m_nFaultPhase = POWER_DIR_FAULT_PHASE_A;
		m_nTestMode = Gradient_TestMode_ActValue;

		m_fSCVoltage = 0.0f;
		m_fSCCurrent = 0.0f;
		m_nAngleMode = 0;
		m_nConnectMode = 0;
		m_fMaxSensAngle = 30.0f;
		m_fLeadAngle = 90.0f;
		m_fLagAngle = 90.0f;

        m_fAngleOffset = 5.0f;
        m_nVarIndex = 0;
	} 

}tmt_PowerDirectionParas;

typedef struct tmt_power_direction_paras_ex :public tmt_PowerDirectionParas
{
public:
	char	m_pszSCVoltage[PARAS_RSLT_EXPR_LEN];
	char	m_pszSCCurrent[PARAS_RSLT_EXPR_LEN];
	char	m_pszStart[PARAS_RSLT_EXPR_LEN];
	char	m_pszStop[PARAS_RSLT_EXPR_LEN];
	char	m_pszStepTime[PARAS_RSLT_EXPR_LEN];

	virtual void init()
	{
		tmt_PowerDirectionParas::init();
		memset(m_pszSCVoltage,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszSCCurrent,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszStop,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszStepTime,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_PowerDirectionParasEx;

typedef struct tmt_power_direction_paras_I :public tmt_PowerDirectionParas
{
public:
    float m_fAngleRange;//动作区范围
    float m_fAngleMargin;//角度裕度
    virtual void init()
    {
        tmt_PowerDirectionParas::init();
        m_fAngleRange = 60;
        m_fAngleMargin = 0;
    }
}tmt_PowerDirectionParas_I;

typedef struct tmt_power_direction_results :public tmt_GradientResult
{

public:
	virtual void init()
	{
		tmt_GradientResult::init();
	} 

}tmt_PowerDirectionResults;

typedef struct tmt_power_direction_test : public TMT_PARAS_HEAD
{
public:
	tmt_PowerDirectionParasEx       m_oTmtParas;
	tmt_PowerDirectionResults   m_oTmtResults;

	void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_PowerDirection);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oTmtParas.init();
		m_oTmtResults.init();
	}

	tmt_power_direction_test()	{init();}
	virtual void clear_result(){	m_oTmtResults.init();	}
	virtual ~tmt_power_direction_test(){}
}tmt_PowerDirectionTest;

typedef struct tmt_power_direction_test_I : public TMT_PARAS_HEAD
{
public:
    tmt_PowerDirectionParas_I   m_oTmtParas;
    tmt_PowerDirectionResults   m_oTmtResults;

    void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_PowerDirection_I);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oTmtParas.init();
        m_oTmtResults.init();
    }

    tmt_power_direction_test_I()	{init();}
    virtual void clear_result(){	m_oTmtResults.init();	}
    virtual ~tmt_power_direction_test_I(){}
}tmt_PowerDirectionTest_I;

typedef struct tmt_pnv_power_direction_test : public TMT_PARAS_HEAD
{
public:
    tmt_PowerDirectionParas       m_oTmtParas;
    tmt_GradientResult   m_oTmtResults;

    void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvPowerDirection);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oTmtParas.init();
        m_oTmtResults.init();
    }

    tmt_pnv_power_direction_test()	{init();}
    virtual void clear_result(){	m_oTmtResults.init();	}
    virtual ~tmt_pnv_power_direction_test(){}
}tmt_PnvPowerDirectionTest;

void stt_init_paras(tmt_PowerDirectionParas *pParas);
void stt_init_paras(tmt_PowerDirectionParas_I *pParas);
void stt_init_paras_ex(tmt_PowerDirectionParasEx *pParas);
void stt_init_results(tmt_PowerDirectionResults *pResults);

void stt_xml_serialize(tmt_PowerDirectionParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_PowerDirectionParas_I *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_PowerDirectionParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_power_dir(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_pnv(tmt_PowerDirectionParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_pnv_power_dir(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);



CSttXmlSerializeBase* stt_xml_serialize(tmt_PowerDirectionTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_PowerDirectionTest_I *pTests, CSttXmlSerializeBase *pXmlSerialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_PnvPowerDirectionTest *pTests, CSttXmlSerializeBase *pXmlSerialize);

