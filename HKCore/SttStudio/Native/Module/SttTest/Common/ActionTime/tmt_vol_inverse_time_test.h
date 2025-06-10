#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"


#define VOL_INVERSE_FAULT_TYPE_AN                                                    0
#define VOL_INVERSE_FAULT_TYPE_BN                                                    1
#define VOL_INVERSE_FAULT_TYPE_CN                                                    2
#define VOL_INVERSE_FAULT_TYPE_AB                                                    3
#define VOL_INVERSE_FAULT_TYPE_BC                                                    4
#define VOL_INVERSE_FAULT_TYPE_CA                                                    5
#define VOL_INVERSE_FAULT_TYPE_ABC                                                   6
#define VOL_INVERSE_FAULT_TYPE_3U0                                                   7
#define VOL_INVERSE_FAULT_TYPE_U2                                                    8


#define VOL_INVERSE_FAULT_VOL_DEF_LN                                                 0
#define VOL_INVERSE_FAULT_VOL_DEF_LL                                                 1

#define VOL_INVERSE_TESTNAME_LEN	64

typedef struct tmt_vol_inverse_formala_paras
{
	float m_fVp;
	float m_fD;
	float m_fK;
	float m_fA_Td;
	float m_fB;
	float m_fC;
	float m_fE;
	float m_fP;
	float m_fM;

public:
	virtual void init()
	{
		m_fVp = 100.0f;
		m_fD = 0.0f;
		m_fK = 1.0f;
		m_fA_Td = 2.0f;
		m_fB = 1.0f;
		m_fC = 0.0f;

		m_fE = 0.0f;
		m_fB = 0.0f;
		m_fP = 1.0f;
		m_fM = 1.1f;
	} 

}tmt_VolInverseFormulaParas;

typedef struct tmt_vol_inverse_time_paras 
{
	//整定值
//	tmt_VolInverseFormulaParas m_oSetting;

	//通用参数
	float m_fPreFaultTime;//故障前时间
	long m_nCTPoint;
	long m_nFaultType;
	long m_nFaultVolDef;//故障电压定义 0-相电压   1-线电压  (只在ABC三相故障时生效)

	//界面参数
	float m_fPreFaultVol;//故障前电压
	float m_fPreFaultCur;//故障前电流
	float m_fPreFaultAngle;//故障前角差

	double m_fFaultVol;//故障电压
	float m_fFaultCur;//故障电流
	float m_fFaultAngle;//故障角差

	double m_fSettingFaultTime;//整定动作时间
	float m_fFaultTimeMargin;//故障时间裕度 20230419 zhouhj 增加用于330模板生成文件中特性曲线参数处理

	float m_fVp;//20211213 sf

	//开关量
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-非故障态开出 1-故障态开出
	tmt_BinaryOut m_binOutEx[2][MAX_ExBINARY_COUNT];//0-非故障态开出 1-故障态开出
	int		m_nBinLogic;			//0-或 1-与
	
	//2022.5.26 caoxc 增加项目名称
	char m_pszTestName[VOL_INVERSE_TESTNAME_LEN];

public:
	virtual void init()
	{
//		m_oSetting.init();
		m_fVp = 100.0f;//20211213 sf

		m_fPreFaultTime = 5.0f;
		m_nCTPoint = 1;
		m_nFaultType = VOL_INVERSE_FAULT_TYPE_AN;
		m_nFaultVolDef = VOL_INVERSE_FAULT_VOL_DEF_LN;

		m_fPreFaultVol = 57.735f;
		m_fPreFaultCur = 0.0f;
		m_fPreFaultAngle = 0.0f;

		m_fFaultVol = 50.0f;
		m_fFaultCur = 5.0f;
		m_fFaultAngle = 0.0f;
		m_nBinLogic = 0;
		m_fSettingFaultTime = 5.0f;
		m_fFaultTimeMargin = 0.0f;

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
		memset(m_pszTestName, 0, VOL_INVERSE_TESTNAME_LEN);
	} 

}tmt_VolInverseTimeParas;


typedef struct tmt_vol_inverse_time_paras_ex :public tmt_VolInverseTimeParas
{
public:
	char m_pszFaultVol[PARAS_RSLT_EXPR_LEN];//故障电压

	virtual void init()
	{
		tmt_VolInverseTimeParas::init();
		memset(m_pszFaultVol,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_VolInverseTimeParasEx;

typedef struct tmt_vol_inverse_time_results
{
	float m_fTripTime;
	long m_nAct;

public:
	virtual void init()
	{
		m_fTripTime = 0.0f;
		m_nAct = 0;
	} 

}tmt_VolInverseTimeResults;


typedef struct tmt_vol_inverse_time_test : public TMT_PARAS_HEAD
{
public:
	tmt_VolInverseTimeParasEx      m_oVolInverseParas;
	tmt_VolInverseTimeResults   m_oVolInverseResults;
//	double m_fCurrCal;//m_fFaultVol/m_fVp   //20211213 sf 画图用
	double m_fTsetCal;//20211213 sf 画图用

	void init()
	{	
		init_head(); //2021-9-13  lijunqing

		strcpy(m_pszMacroID, STT_MACRO_ID_VoltageInverseTime);
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		m_fTsetCal = 0;
//		m_fCurrCal = 0;

		m_oVolInverseParas.init();
		m_oVolInverseResults.init();
	}

	tmt_vol_inverse_time_test()	{init();}
	virtual void clear_result(){	m_oVolInverseResults.init();	}
	virtual ~tmt_vol_inverse_time_test(){}
}tmt_VolInverseTimeTest;

void stt_init_paras(tmt_VolInverseTimeParas *pParas);
void stt_init_paras_ex(tmt_VolInverseTimeParasEx *pParas);
void stt_init_results(tmt_VolInverseTimeResults *pResults);

void stt_xml_serialize(tmt_VolInverseTimeParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_VolInverseTimeParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_VolInverseTimeResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_VolInverseTimeTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
