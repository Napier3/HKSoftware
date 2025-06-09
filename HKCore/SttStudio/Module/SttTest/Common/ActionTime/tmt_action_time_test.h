#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"

#define ACTION_TIME_FAULT_TYPE_AN                                                    0
#define ACTION_TIME_FAULT_TYPE_BN                                                    1
#define ACTION_TIME_FAULT_TYPE_CN                                                    2
#define ACTION_TIME_FAULT_TYPE_AB                                                    3
#define ACTION_TIME_FAULT_TYPE_BC                                                    4
#define ACTION_TIME_FAULT_TYPE_CA                                                    5
#define ACTION_TIME_FAULT_TYPE_ABC                                                   6
#define ACTION_TIME_FAULT_TYPE_3I0                                                   7
#define ACTION_TIME_FAULT_TYPE_I2                                                    8
#define ACTION_TIME_FAULT_TYPE_Iabc                                                  9
#define ACTION_TIME_FAULT_TYPE_UaIa                                                  10
#define ACTION_TIME_FAULT_TYPE_UaUb                                                  11
#define ACTION_TIME_FAULT_TYPE_A                                                     12
#define ACTION_TIME_FAULT_TYPE_B                                                     13
#define ACTION_TIME_FAULT_TYPE_C                                                     14


#define ACTION_TIME_FAULT_VOL_TYPE_Fault                                          0
#define ACTION_TIME_FAULT_VOL_TYPE_U1                                             1
#define ACTION_TIME_FAULT_VOL_TYPE_U2                                             2
#define ACTION_TIME_FAULT_VOL_TYPE_3U0                                            3

#define ACTION_TIME_TESTNAME_LEN	64

typedef struct tmt_action_time_paras 
{
	float m_fPreFaultTime;//故障前时间
	double m_fSettingFaultTime;//整定动作时间
	float m_fMarginTime;//动作时间裕度

	float m_fPreFaultVol;//故障前电压
	float m_fPreFaultCur;//故障前电流
	float m_fPreFaultAngle;//故障前角差
	int		m_nPhaseSet[2];	// 相序设置 电压电流,用于高级试验,如复压闭锁

	float m_fFaultVol;//故障电压
	double m_fFaultCur;//故障电流
	float m_fFaultAngle;//故障角差
	long m_nFaultType;
	long m_nFaultVolType;//故障电压类型
	long m_nRefValueType;//基准值类型(0-In;1-In*Ip)//1-Iset1;2-Iset2;3-Iset3;
	long m_nCTPoint; //CT正极性 0 指向母线，1指向线路
	float m_fIn;//额定电流
	float m_fIp;

	//开关量
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-非故障态开出 1-故障态开出
	tmt_BinaryOut m_binOutEx[2][MAX_ExBINARY_COUNT];//0-非故障态开出 1-故障态开出
	int		m_nBinLogic;			//0-或 1-与
	
	//2022.5.26 caoxc 增加项目名称
	char m_pszTestName[ACTION_TIME_TESTNAME_LEN];

public:
	virtual void init()
	{
		m_fPreFaultTime = 5.0f;
		m_fSettingFaultTime = 1.2f;
		m_fMarginTime = 0.10f;
		m_fPreFaultVol = 57.735f;
		m_fPreFaultCur = 0.0f;
		m_fPreFaultAngle = 0.0f;
		m_fFaultVol = 50.0f;
		m_fFaultCur = 5.0f;
		m_fFaultAngle = 0.0f;
		m_nFaultType = ACTION_TIME_FAULT_TYPE_AN;
		m_nFaultVolType = ACTION_TIME_FAULT_VOL_TYPE_Fault;
		m_nRefValueType = 0;
		m_nBinLogic = 0;
		m_nCTPoint = 1;
		m_nPhaseSet[0] = m_nPhaseSet[1] = 0;
		m_fIn = 1.0f;
		m_fIp = 1.0f;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			for(int j=0;j<2;j++)
			{
				m_binOut[j][i].init();
			}
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binInEx[i].init();			
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for(int j=0;j<2;j++)
			{
				m_binOutEx[j][i].init();
			}
		}

		//2022.5.26 caoxc
		memset(m_pszTestName, 0, ACTION_TIME_TESTNAME_LEN);
	} 

}tmt_ActionTimeParas;


typedef struct tmt_action_time_paras_ex :public tmt_ActionTimeParas
{
public:
	char m_pszSettingFaultTime[PARAS_RSLT_EXPR_LEN];//整定动作时间
	char m_pszPreFaultAngle[PARAS_RSLT_EXPR_LEN];//故障前角差
	char m_pszFaultVol[PARAS_RSLT_EXPR_LEN];//故障电压
	char m_pszFaultCur[PARAS_RSLT_EXPR_LEN];//故障电流
	char m_pszFaultAngle[PARAS_RSLT_EXPR_LEN];//故障角差

	virtual void init()
	{
		tmt_ActionTimeParas::init();
		memset(m_pszSettingFaultTime,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszPreFaultAngle,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFaultVol,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFaultCur,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFaultAngle,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_ActionTimeParasEx;


// typedef struct tmt_curr_inverse_paras//20211012 sf
// {
// 	float m_fIset1;
// 	float m_fIset2;
// 	float m_fIset3;
// 	float m_fTset1;
// 	float m_fTset2;
// 	float m_fTset3;
// 
// 	float m_fA;
// 	float m_fB;
// 	float m_fP;
// 	float m_fIp;
// 	float m_fQ;
// 	float m_fTd;
// 	float m_fK1;
// 	float m_fK2;
// 
// public:
// 	virtual void init()
// 	{
// 		m_fIset1 = 5.0f;
// 		m_fIset2 = 3.0f;
// 		m_fIset3 = 2.0f;
// 		m_fTset1 = 0.5f;
// 		m_fTset2 = 1.0f;
// 		m_fTset3 = 2.0f;
// 
// 		m_fA = 0.5f;
// 		m_fB = 0.0f;
// 		m_fP = 2.0f;
// 		m_fIp = 1.1f;
// 		m_fQ = 1.0f;
// 		m_fTd = 1.0f;
// 		m_fK1 = 0.0f;
// 		m_fK2 = 0.0f;
// 	} 
// 
// 	void operator = (tmt_curr_inverse_paras &temp)
// 	{
// 		m_fTset1 = temp.m_fTset1;
// 		m_fTset2 = temp.m_fTset2;
// 		m_fTset3 = temp.m_fTset3;
// 		m_fIset1 = temp.m_fIset1;
// 		m_fIset2 = temp.m_fIset2;
// 		m_fIset3 = temp.m_fIset3;
// 
// 		m_fA = temp.m_fA;
// 		m_fB = temp.m_fB;
// 		m_fP = temp.m_fP;
// 		m_fIp = temp.m_fIp;
// 		m_fQ = temp.m_fQ;
// 		m_fTd = temp.m_fTd;
// 		m_fK1 = temp.m_fK1;
// 		m_fK2 = temp.m_fK2;
// 	}
// 
// }tmt_CurrInverseParas;

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
	tmt_ActionTimeParasEx      m_oActionTimeParas ;
	tmt_ActionTimeResults   m_oActionTimeResults;


	virtual void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_ActionTime);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oActionTimeParas.init();
		m_oActionTimeResults.init();
	}

	tmt_action_time_test()	{init();}
	virtual void clear_result(){	m_oActionTimeResults.init();	}
	virtual ~tmt_action_time_test(){}
}tmt_ActionTimeTest;

typedef struct tmt_curr_inverse_time_test : public tmt_action_time_test
{
public:
	double m_fCurrCal;    //m_fCurrCal = m_fFaultCur / BaseVal
	double m_fTsetCal;    //m_fSettingFaultTime = m_fTsetCal
	
	virtual void init()
	{
		tmt_action_time_test::init();
		m_fTsetCal = 0.0f;
		m_fCurrCal = 0.0f;
	}
}tmt_CurrInverseTimeTest;


void stt_init_paras(tmt_ActionTimeParas *pParas);
void stt_init_paras_ex(tmt_ActionTimeParasEx *pParas);
void stt_init_results(tmt_ActionTimeResults *pResults);

//void stt_xml_serialize(tmt_CurrInverseParas *pParas, CSttXmlSerializeBase *pXmlSierialize);//20211012 sf

void stt_xml_serialize(tmt_ActionTimeParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_ActionTimeParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ActionTimeResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_ActionTimeTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
