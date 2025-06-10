#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"


#define DC_OVERLOAD_TESTNAME_LEN	64

typedef struct tmt_dc_overload_paras 
{
	float m_fNormaltime;//常态时间
	float m_fFaultMarginTime;//故障时间裕度
	float m_fPreFaultVol;//故障前电压
	float m_fPreFaultCur;//故障前电流


	float m_fTime;//热过负荷时间常数
	float m_fBaseCur;//热过负荷基数电流
	float m_fBaseActionSet;//热过负荷动作定值
	long m_nFaultCurChannel;//故障过负荷电流通道
	double m_fFaultCur;//故障过负荷电流
	double m_fFaultSettingTime;//故障动作时间定值


	float m_fStartCur;//电流变化始值
	float m_fEndCur;//电流变化终值
	float m_fStepCur;//电流变化步长


	//开关量
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-非故障态开出 1-故障态开出
	tmt_BinaryOut m_binOutEx[2][MAX_ExBINARY_COUNT];//0-非故障态开出 1-故障态开出
	int		m_nBinLogic;			//0-或 1-与
	
	char m_pszTestName[DC_OVERLOAD_TESTNAME_LEN];

public:
	virtual void init()
	{
		m_fNormaltime = 5.0f;
		m_fFaultMarginTime = 0.20f;
		m_fPreFaultVol = 0;
		m_fPreFaultCur = 0;
		m_fTime = 1.00f;
		m_fBaseCur =1.00f;
		m_fBaseActionSet =1.00f ;
		m_nFaultCurChannel=DC_CURRENT_COMMON_FAULT_TYPE_I1_1;
		m_fFaultCur = 0;
		m_fFaultSettingTime = 0;
		m_fStartCur = 3.00f;
		m_fEndCur = 20.00f;
		m_fStepCur = 1.00f;

		m_nBinLogic = 0;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			for(int j=0;j<2;j++)
			{
				m_binOut[j][i].init();
			}
		}

		for (int i=0;i<g_nBinExCount;i++)
		{
			m_binInEx[i].init();			
		}

		for (int i=0;i<g_nBoutExCount;i++)
		{
			for(int j=0;j<2;j++)
			{
				m_binOutEx[j][i].init();
			}
		}

		memset(m_pszTestName, 0, DC_OVERLOAD_TESTNAME_LEN);
	} 
}tmt_DC_OverLoadParas;


typedef struct tmt_dc_overload_paras_ex :public tmt_DC_OverLoadParas
{
public:
	char m_pszTimeCoef[PARAS_RSLT_EXPR_LEN];//热过负荷时间常数
	char m_pszCur[PARAS_RSLT_EXPR_LEN];//热过负荷基数电流
	char m_pszActionSet[PARAS_RSLT_EXPR_LEN];//热过负荷动作定值

	virtual void init()
	{
		tmt_DC_OverLoadParas::init();
		memset(m_pszActionSet,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszTimeCoef,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszCur,0,PARAS_RSLT_EXPR_LEN);

	} 
}tmt_DC_OverLoadParasEx;

typedef struct tmt_dc_overload_results
{
	float m_fTripTime;
	long m_nAct;

public:
	virtual void init()
	{
		m_fTripTime = 0.0f;
		m_nAct = 0;
	} 

}tmt_DC_OverLoadTestResults;

typedef struct tmt_dc_overload_test : public TMT_PARAS_HEAD
{
public:
	tmt_DC_OverLoadParasEx   m_oOverLoadParas ;
	tmt_DC_OverLoadTestResults m_oOverLoadTestResults;
	double m_fTsetCal;

	virtual void init()
	{
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_DCOverLoadTest);
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		m_fTsetCal = 0.0f;
		m_oOverLoadParas.init();
		m_oOverLoadTestResults.init();
	}

	tmt_dc_overload_test()	{init();}
	virtual ~tmt_dc_overload_test(){}
}tmt_DC_OverLoadTest;


void stt_init_paras(tmt_DC_OverLoadParas *pParas);
void stt_init_paras_ex(tmt_DC_OverLoadParasEx *pParas);
void stt_init_results(tmt_DC_OverLoadTestResults *pResults);

void stt_xml_serialize(tmt_DC_OverLoadParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_DC_OverLoadParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_DC_OverLoadTestResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_DC_OverLoadTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
