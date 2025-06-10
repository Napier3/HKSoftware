#pragma once

#include "../tmt_manu_test.h"
#include "../tmt_common_def.h"

typedef struct tmt_fa_paras_set
{
	float m_fRatedVoltage;   		//额定电压
	float m_fResidualVoltage;   		//残压
	float m_fRatedCurrent;   		//额定电流
	float m_fFaultCurrent;  		//故障电流
	float m_fFailureDuration;		//故障持续时间
	float m_fErrorAssessTime;   //误差评估时间
	float m_fxTime;			 //来电延时合闸时间
	float m_fyTime;			//合闸后无故障确认时间
	float m_fzTime;			//失压跳闸时间
	float m_fxlTime;			//联络模式单侧失压延时合闸时间
	float m_fsTime;			//自适应型无故障得电延时合闸时间
	
	void init()
	{
		m_fRatedVoltage = 100.00f;
		m_fResidualVoltage = 30.00f;
		m_fRatedCurrent = 5.000f;
		m_fFaultCurrent = 5.000f;
		m_fFailureDuration = 0.500f;
		m_fErrorAssessTime = 0.500f;
		m_fxTime = 7.000f;
		m_fyTime = 5.000f;
		m_fzTime = 0.000f;
		m_fxlTime = 50.000f;
		m_fsTime = 57.000f;

		m_nTermPowerVol = 0;		//0-UAB 1-UCB
		m_nTermLoadVol = 1;			//0-UAB 1-UCB

		m_strCloseOutput = "开入A";
		m_strOpenOutput = "开入B";

		m_strCloseSignal = "开出1";
		m_strQuantileSignal = "开出2";
	}
	tmt_fa_paras_set()
	{
		init();
	}

	int m_nTermPowerVol;		//0-UAB 1-UCB
	int m_nTermLoadVol;			//0-UAB 1-UCB

	QString m_strCloseOutput;
	QString m_strOpenOutput;

	QString m_strCloseSignal;
	QString m_strQuantileSignal;

 	tmt_BinaryIn    m_binCloseIn[MAX_BINARYIN_COUNT];   //合闸开入
 	tmt_BinaryOut   m_binQuantileout[MAX_BINARYOUT_COUNT]; //分位开出

	tmt_BinaryIn    m_binOpenIn[MAX_BINARYIN_COUNT];   //分闸开入
	tmt_BinaryOut   m_binFitout[MAX_BINARYOUT_COUNT]; //合位开出

}tmt_FaParasSet;


typedef struct tmt_fa_paras_set_result  : public tmt_ManualResult
{
public:
	virtual void init()
	{
		tmt_ManualResult::init();
	}

	tmt_fa_paras_set_result()
	{
		init();
	}
} tmt_FaParasSetResult;


typedef struct tmt_fa_paras_set_test : public TMT_PARAS_HEAD
{
public:
	tmt_FaParasSetResult    m_oFaParasSetResult;
	tmt_FaParasSet			m_oFaParasSet;


	void init()
	{
		strcpy(m_pszMacroID, STT_MACRO_ID_VolTimeTypeSecTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
		m_oFaParasSet.init();
		m_oFaParasSetResult.init();
	}

	tmt_fa_paras_set_test()
	{
		init();
	}
} tmt_FaParasSetTest;



//界面 基础值 序列化
void stt_xml_serialize_base(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize);
//合闸开入
void stt_xml_serialize_binary_closein(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize);
//合位开出
void stt_xml_serialize_binary_openin(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize);
//分闸开入
void stt_xml_serialize_binary_Fitout(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize);
//分位开出
void stt_xml_serialize_binary_Quantileout(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize);
//测试，文件生成 查看
void stt_xml_serialize_write_FaultGradientTest();