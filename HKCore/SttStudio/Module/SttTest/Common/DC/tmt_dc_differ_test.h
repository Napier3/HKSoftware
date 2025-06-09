#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"
#include "../SearchBase/tmt_search_base.h"

#define DCDIFF_INSEL 1       //基准电流选择 0-高侧二次额定电流 1-设定值 2-各侧二次额定电流
#define DCDIFF_MINAXIS 1     //定制整定方式 0-有名值 1-标幺值
#define DCDIFF_ANGLEMODE 2   //校正选择	0-无校正 1-△侧校正 2-Y侧校正
#define DCDIFF_WINDH 0       //高压侧绕组接线形式 0-Y 1-△ 0
#define DCDIFF_WINDM 0       //中压侧绕组接线形式 0-Y 1-△
#define DCDIFF_WINDL 0       //低压侧绕组接线形式 0-Y 1-△
#define DCDIFF_WINDSIDE 0    //测试绕组	0-高-低  1-高-中    2-中-低
#define DCDIFF_CONNECTMODE 0 //测试绕组之间角差（钟点数）0-11 12点、1点--11点
#define DCDIFF_PHASE 3       //测试相 0-A,1-B,2-C,3-A,B,C
#define DCDIFF_CTSTARPOINT 0 //CT极性0-两侧指向变压器 1-一侧指向变压器
#define DCDIFF_JXFACTOR 0    //平衡系数计算方法	0-不考虑绕组接线型式  1-考虑绕组接线型式

typedef struct tmt_dc_differ_cur_paras : public tmt_SearchBase
{
	int		m_nTestType;	//测试类型，0-启动电流，1-比率制动，2-动作时间，3-其他
	//整定值
	float m_fIStart;//启动电流
	int m_nKneePoints;//拐点个数
	float m_fIp1;     //拐点1电流
	float m_fIp2;     //拐点2电流
	float m_fKRation1; //比率制动系数1
	float m_fKRation2; //比率制动系数2
	float m_fActTime; //动作时间
	float m_fKid0;//启动电流斜率

	//通用参数
	float m_fBeforeTime; //变化前时间
	float m_fPreFaultTime;//故障前时间
	float m_fMarginTime;//故障时间裕度
	float m_fK1;        //平衡系数1
	float m_fK2;        //平衡系数2
	int m_nCurChannel1; //电流1通道
	int m_nCurChannel2; //电流2通道
	int m_nSearchMode; //搜索模式 0,二分法 1，单步进法
	int m_nDiffCal;     //差动方程
	int m_nIbiasCal;    //制动方程
	float m_fFactor1;   //K1
	float m_fFactor2;   //K2
	
	//开关量
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
	int	m_nBinLogic;			//0-或 1-与

	//试验参数
	char m_pszTestName[EXPR_MAX_COUNT];	//项目名称
	float	m_fIbias;		//制动电流
	float   m_fIdiff;       //差动电流

public:
	virtual void init()
	{
		m_nTestType = 0;
		m_fIStart = 5.000f;
		m_nKneePoints = 1;
		m_fIp1 = 1.0f;
		m_fIp2 = 2.5f;
		m_fKRation1 = 0.15f;
		m_fKRation2 = 0.12f;
		m_fActTime = 0.0f;

		m_fBeforeTime = 2.000f;
		m_fPreFaultTime = 2.000f;
		m_fMarginTime = 0.2f;
		m_fK1 = 1.000f;
		m_fK2 = 1.000f;
		m_nCurChannel1 = 0;
		m_nCurChannel2 = 0;
		m_nSearchMode = 0;
		m_nDiffCal = 0;
		m_nIbiasCal = 0;
		m_fFactor1 = 2.000f;
		m_fFactor2 = 1.000f;
		m_fKid0 = 0.200f;

		m_fIbias = 1.200f;
		m_fIdiff = 0.600f;

		for (int i = 0; i < MAX_ExBINARY_COUNT; i++)
		{
			m_binIn[i].init();
			m_binOut[i].init();
		}

		for (int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binInEx[i].init();
		}

		for (int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binOutEx[i].init();
		}

		memset(m_pszTestName, 0, EXPR_MAX_COUNT);
	}
}tmt_DcDifferCurParas;

typedef struct tmt_dc_differ_results
{
	float	m_fIdiffActValue;	//差动电流动作值
	float	m_fIdiffSettingValue;	// 当前搜索的差动电流值
	float	m_fIbiasValue;	//制动电流
	float	m_fIrCoef;		//制动系数
	float   m_fRateKid; //比率制动系数
	float	m_fTripTime;		//动作时间: 负值无效
	int		m_nActFlag;			//动作标志
	float	m_fI1Ie;
	float	m_fI1;
	float	m_fI2Ie;
	float	m_fI2;

public:
	virtual void init()
	{
		m_fIdiffActValue = 0;
		m_fIdiffSettingValue = 0;
		m_fIbiasValue = 0;
		m_fIrCoef = 0;
		m_fRateKid = 0;
		m_nActFlag = 0;
		m_fI1Ie = 0;
		m_fI1 = 0;
		m_fI2Ie = 0;
		m_fI2 = 0;
	}
}tmt_DcDifferCurResults;

typedef struct tmt_dc_differ_cur_test : public TMT_PARAS_HEAD
{
public:
	tmt_DcDifferCurParas m_oDcDifferCurParas;
	tmt_DcDifferCurResults m_oDcDifferCurResults;
	int m_nThrType;		//0-启动电流；1-动作特性曲线

	virtual void init()
	{
		init_head();
		strcpy(m_pszMacroID, STT_MACRO_ID_DCDifferCurrTest);
		m_nTestState = 0;
		m_oDcDifferCurParas.init();
		m_oDcDifferCurResults.init();
		m_nThrType = 0;
	}

	tmt_dc_differ_cur_test(){init();}
	virtual void clear_result(){m_oDcDifferCurResults.init();}
	virtual ~tmt_dc_differ_cur_test(){}
}tmt_DcDifferCurTest;

typedef struct tmt_dc_differ_cur_rate_test : public tmt_DcDifferCurTest //比率制动系数
{
public:
	int m_nRateType; //0-比率制动系数1 1-比率制动系数2
	virtual void init()
	{
		tmt_DcDifferCurTest::init();
		m_nRateType = 0;
		strcpy(m_pszMacroID, STT_MACRO_ID_DCDifferRateTest);
	}

	tmt_dc_differ_cur_rate_test(){init();}
	virtual ~tmt_dc_differ_cur_rate_test(){}
}tmt_DcDifferCurRateTest;

typedef struct tmt_dc_differ_cur_acttime_test : public tmt_DcDifferCurTest
{
public:
	virtual void init()
	{
		tmt_DcDifferCurTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_DCDifferTimeTest);
	}
	tmt_dc_differ_cur_acttime_test(){init();}
	virtual ~tmt_dc_differ_cur_acttime_test(){}
}tmt_DcDifferActTimeTest;

void stt_init_paras(tmt_DcDifferCurParas *pParas);
void stt_init_results(tmt_DcDifferCurResults *pResults);

void stt_xml_serialize_diff_search_results(tmt_DcDifferCurParas *pParas, tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_rate(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_rate(tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_acttime(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_acttime(tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_DcDifferCurTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(tmt_DcDifferCurTest *pTests, CSttXmlSerializeBase *pXmlSerialize, BOOL bResultOnly);
void stt_xml_serialize_write_DCDifferTest();