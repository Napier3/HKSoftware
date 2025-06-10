#pragma once

#include "../../tmt_test_paras_head.h"
#include "../../tmt_common_def.h"
#include "../../SearchBase/tmt_search_base.h"

#define BP2_DIFF_U_LOCK_TYPE_UA                              0
#define BP2_DIFF_U_LOCK_TYPE_UAB                             1
#define BP2_DIFF_U_LOCK_TYPE_3U0                             2
#define BP2_DIFF_U_LOCK_TYPE_U2                              3

	
typedef struct tmt_bp2_diff_paras :public tmt_SearchBase
{
	int		m_nTestType;	//测试类型，本参数需要在每个派生类中写死：	0-启动电流，1-比率制动，2-整组试验
	int		m_nDiffType;	//测试模式 0-大差试验 1-小差试验
	float	m_fUmag[3];			//三相电压幅值
	float	m_fUang[3];			//三相电压相位
	float	m_fIdSetting;	//差动电流定值（测试无用，专供模板）

	//整定值
	float	m_fIcdqd;//差动动作电流门槛值 0.500In或A	用以计算IBIAS，可无视
	float m_fCompoundKh;//复式比率系数高值
	float m_fCompoundKl;//复式比率系数低值
	float m_fTA1;
	float m_fTA2;
	float m_fTA3;
	float m_fTAmax;
	
	//通用参数
	float m_fPreFaultTime;	//故障前时间 1.000
	float m_fFaultTime;		//故障时间 0.500
	float m_fAfterFaultTime;//故障后持续时间

	//差动参数
	float	m_fIdiff;		//差动电流
	float	m_fIr_Id;		//复式比率制动横坐标即【Ir-Id】

	int    m_nULockType;//电压闭锁元件选择  0-Ua   1-Uab   2-U0   3-U2
	float  m_fULockValue;//闭锁电压值

	//开关量
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
	int	m_nBinLogic;			//0-或 1-与
	int m_nAutoSearch;	//是否自动搜索 (0:手动搜索;1:自动搜索)
	
	//上位机单用
	int  m_nKAType;							//0:低值  1:高值
	char m_pszId[PARAS_RSLT_EXPR_LEN];		//Id表达式
	char m_pszIrId[PARAS_RSLT_EXPR_LEN];	//Ir-Id表达式
public:
	virtual void init()
	{
		tmt_SearchBase::InitSearch();
		m_nTestType = 0;	//默认测试启动电流
		m_nDiffType = 0;
		m_fUmag[0]=57.74f;
		m_fUmag[1]=57.74f;
		m_fUmag[2]=57.74f;
		m_fUang[0]=0.0f;
		m_fUang[1]=-120.0f;
		m_fUang[2]=120.0f;
		m_fIdSetting = 1;

		m_fCompoundKh = 0.85f;
		m_fCompoundKl = 0.5f;

		m_fTA1 = 120.0f;
		m_fTA2 = 120.0f;
		m_fTA3 = 120.0f;
		m_fTAmax = 240.0f;

		//通用参数
		m_fPreFaultTime = 1.000;
		m_fFaultTime = 0.500;

		//差动参数
		m_fIdiff = 0.600f;
		m_fIr_Id = 0.600f;
		m_fIcdqd=0.5;

		m_nAutoSearch = 1;
		m_nULockType = BP2_DIFF_U_LOCK_TYPE_UA;
		m_fULockValue = 12.0f;


		m_nBinLogic = 0;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			m_binOut[i].init();
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binInEx[i].init();
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binOutEx[i].init();
		}

		//上位机单用
		m_nKAType = 0;
		memset(m_pszId,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIrId,0,PARAS_RSLT_EXPR_LEN);
	} 

}tmt_BP2DiffParas;

typedef struct tmt_bp2_diff_results
{
	float	m_fIdiffActValue;	//差动电流动作值
	float	m_fIdiffSettingValue;	// 当前搜索的差动电流值
	float	m_fIbiasValue;	//制动电流
	float	m_fIrCoef;		//制动系数
	BOOL	m_bLastPoint;	//是否最后一个搜索点
	int		m_nZDRatioIndex;	//比例制动序号1 1-2 2 2-2 3 3-2 值：1 2 3 4 5 6 7 8
	int		m_rltBin[MAX_BINARYIN_COUNT];	//开入状态

	float	m_fTripTime;		//动作时间: 负值无效
	int		m_nActFlag;			//动作标志

	float	m_fI1;
	float	m_fI2;
	float	m_fIRbase[6];
	float	m_fIharm[6];

	//上位机用
	float   m_fRateKid; //比率制动系数

public:
	virtual void init()
	{
		m_fIdiffActValue = 0;	//差动电流
		m_fIdiffSettingValue = 0;
		m_fIbiasValue = 0;	//制动电流
		m_fIrCoef = 0;		//制动系数
		m_bLastPoint = 0;	//是否最后一个搜索点
		m_nZDRatioIndex = 0;	//比例制动序号1 1-2 2 2-2 3 3-2 值：1 2 3 4 5 6 7 8
		memset(m_rltBin, 0, MAX_BINARYIN_COUNT*sizeof(int));
		m_fTripTime = 0;			//动作时间: 负值无效
		m_nActFlag = 0;

		m_fI1 = 0;
		m_fI2 = 0;

		m_fRateKid = 0;

		for (int i=0;i<6;i++)
		{
			m_fIRbase[0] = m_fIharm[0] = 0;
		}
	} 

}tmt_BP2DiffResults;


typedef struct tmt_bp2_diff_thr_test : public TMT_PARAS_HEAD // 差动启动电流测试
{
public:
	tmt_BP2DiffParas      m_oDiffCurrParas ;
	tmt_BP2DiffResults   m_oDiffCurrResults;
	int m_nThrType;		//0-启动电流；1-动作特性曲线

	virtual void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_BP2DiffTCurrTest);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oDiffCurrParas.init();
		m_oDiffCurrResults.init();
		m_nThrType = 0;
	}

	tmt_bp2_diff_thr_test()	{init();}
	virtual void clear_result(){	m_oDiffCurrResults.init();	}
	virtual ~tmt_bp2_diff_thr_test(){}
}tmt_BP2DiffThrTest;

typedef struct tmt_bp2_diff_rate_test : public tmt_BP2DiffThrTest // 差动比率制动
{
public:
	int m_nRateType;		//0-启动段斜率；1、2-比率制动系数一；3、4-比率制动系数二；5、6-比率制动系数三；7、8-比率制动系数四；
	virtual void init()
	{
		tmt_BP2DiffThrTest::init();
		m_nRateType = 0;
		strcpy(m_pszMacroID, STT_MACRO_ID_BP2DiffRateTest);
	}

	tmt_bp2_diff_rate_test()	{init();}
	virtual ~tmt_bp2_diff_rate_test(){}
}tmt_BP2DiffRateTest;


typedef struct tmt_bp2_cboperate_test : public tmt_BP2DiffThrTest // 差动整组试验
{
public:
	virtual void init()
	{
		tmt_BP2DiffThrTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_BP2CBOperateTest);
	}

	tmt_bp2_cboperate_test()	{init();}
	virtual ~tmt_bp2_cboperate_test(){}
}tmt_BP2CBOperateTest;


void stt_init_paras(tmt_BP2DiffParas *pParas);
void stt_init_results(tmt_BP2DiffResults *pResults);

void stt_xml_serialize_diff_search_results(tmt_BP2DiffParas *pParas, tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr_ex(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_rate(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_rate_ex(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_rate(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_cboperate(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_cboperate_ex(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_cboperate(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_BP2DiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(tmt_BP2DiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly);
