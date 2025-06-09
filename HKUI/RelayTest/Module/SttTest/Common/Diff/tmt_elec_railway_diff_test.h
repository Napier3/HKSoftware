#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"
#include "../SearchBase/tmt_search_base.h"
#include "tmt_diff_curr_test.h"
	
typedef struct tmt_elec_railway_diff_paras :public tmt_SearchBase
{
    int		m_nTestType;	//测试类型，本参数需要在每个派生类中写死：	0-启动电流，1-比率制动，2-速断电流，3-2次谐波制动系数，4-动作时间，5-其他
    int		m_nTestMethod;	//测试模式 0-手动 1-自动
    float	m_fVg1;			//第一组电压输出值
    float	m_fVg2;			//第二组电压输出值
    float	m_fIdSetting;	//差动电流定值（测试无用，专供模板）

    //整定值
    BOOL	m_bMinAxis;	//定制整定方式 0-有名值 1-标幺值 平台模板没有，恒为1
    float	m_fIbase;	//基准电流设定值

    float	m_fIsd;	//差动速断电流定值 1.500In或A		用以计算IBIAS，可无视
    float	m_fIcdqd;//差动动作电流门槛值 0.500In或A	用以计算IBIAS，可无视

    float m_fIp1;//比率制动特性拐点1电流
    float m_fIp2;//比率制动特性拐点1电流
    float m_fKid1;//基波比率制动特性斜率1
    float m_fKid2;//基波比率制动特性斜率2
	


    //通用参数
	float m_fPreTime;		//准备时间  0.000
    float m_fPreFaultTime;	//故障前时间 1.000
    float m_fFaultTime;		//故障时间 0.500
    float m_fKpl;			//低压侧差动平衡系数 0.637	用以计算KPL
    BOOL	m_bCTStarPoint;	//CT极性0-两侧指向变压器 1-一侧指向变压器  平台模板好像没有，恒为0
    int		m_nIbiasCal;	//制动方程	0-Ir=(|I1-I2|)/K1或Ir=(|I1+I2|)/K1,1-Ir=(|I1|+|I2|*K2)/K1,2-Ir=max(|I1|,,|I2|)
    //,3-Ir=(|Id-|I1|-|I2||)/K1,4-Ir=|I2|,5-Sqrt(K1*I1*I2*Cos(δ)),		1
	int		m_nPhase;		//测试相 0-A,1-B,2-C,3-A,B,C	平台模板没有，恒为3 

	int    m_nTranSort;//变压器接线形式 0-Y/V接线平衡变压器   1-Y/△-11接线  2-单相变压器   
    int    m_nRWCTconnect;//高压侧CT接线方式    0-△型接线   1-Y型接线
	int    m_nKphMode;//平衡系数计算方法   0-匝数比*高压侧CT变比/低压侧CT变比    1-低压侧CT变比/(匝数比*高压侧CT变比)  

    //差动参数
    float	m_fIdiff;		//差动电流
    float	m_fIbias;		//制动电流

    // 谐波参数
    int		m_nHarmIndex;	//谐波制动次数选择，0-2值分别对应2次、3次和5次
    float	m_fCoefHarm2;			//二次谐波制动系数
    float	m_fCoefHarm3;			//三次谐波制动系数
    float	m_fCoefHarm5;			//五次谐波制动系数

    //开关量
    tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	
    tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
    int	m_nBinLogic;			//0-或 1-与
    int m_nAutoSearch;//是否自动搜索 (0:手动搜索;1:自动搜索)
	
    char m_pszTestName[32];	//项目名称
public:
    virtual void init()
    {
        tmt_SearchBase::InitSearch();
        m_nTestType = 0;	//默认测试启动电流
        m_nTestMethod = 1;
		m_fVg1=57.74f;
		m_fVg2=57.74f;
        m_fIdSetting = 1;

        m_fIp1 = 1.0f;
        m_fIp2 = 2.5f;
        m_fKid1 = 0.7f;
        m_fKid2 = 0.4f;

        m_bMinAxis = TRUE;
        m_fIbase = 5.000f;

        //通用参数
		m_fPreTime = 1.000;
        m_fPreFaultTime = 1.000;
		m_fFaultTime = 0.500;	
        m_fKpl = 0.637f;

        m_bCTStarPoint = FALSE;
        m_nIbiasCal = 0;
        m_nPhase = 0;

        m_nTranSort = 0;
        m_nRWCTconnect = 0;
        m_nKphMode = 0;

        //差动参数
        m_fIdiff = 0.600f;
        m_fIbias = 1.200f;
		m_fIsd=5;
		m_fIcdqd=0.5;

        // 谐波参数
        m_nHarmIndex = 0;
        m_fCoefHarm2 = 0.15f;
        m_fCoefHarm3 = 0.12f;
        m_fCoefHarm5 = 0.11f;
        m_nAutoSearch = 1;

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
		
        memset(m_pszTestName, 0, 32);
	} 

    void CopyOwnDiffParas(tmt_DiffCurrParas *pDiffCurrParas)
    {
        tmt_SearchBase::CopyOwnSearchBase(pDiffCurrParas);

        pDiffCurrParas->m_nTestType = m_nTestType;	//默认测试启动电流
        pDiffCurrParas->m_nTestMethod = m_nTestMethod;
		pDiffCurrParas->m_fVg1=m_fVg1;
		pDiffCurrParas->m_fVg2=m_fVg2;
		pDiffCurrParas->m_fIdSetting =m_fIdSetting;

        pDiffCurrParas->m_nKneePoints = 2;
        pDiffCurrParas->m_fIp1 = m_fIp1;
        pDiffCurrParas->m_fIp2 = m_fIp2;
        pDiffCurrParas->m_fIp3 = 3.0f;
        pDiffCurrParas->m_fKid0 = 0.0f;
        pDiffCurrParas->m_fKid1 = m_fKid1;
        pDiffCurrParas->m_fKid2 = m_fKid2;
        pDiffCurrParas->m_fKid3 = 0.4f;

        pDiffCurrParas->m_bMinAxis = m_bMinAxis;
        pDiffCurrParas->m_nInSel = 1;//基准电流选择设定值
        pDiffCurrParas->m_fIbase = m_fIbase;

        //通用参数
        pDiffCurrParas->m_fPreFaultTime = m_fPreFaultTime;
        pDiffCurrParas->m_fFaultTime = m_fFaultTime;
		pDiffCurrParas->m_nKcal = 1;	
        pDiffCurrParas->m_fKpl = m_fKpl;
        pDiffCurrParas->m_nConnectMode = 0;
        pDiffCurrParas->m_nJXFactor = 0;
        pDiffCurrParas->m_bCTStarPoint = m_bCTStarPoint;
        pDiffCurrParas->m_nIbiasCal = m_nIbiasCal;

        pDiffCurrParas->m_fFactor2 = 1;

		if (m_nIbiasCal == 1)
        {
            pDiffCurrParas->m_fFactor1 = 2;
        }
        else
        {
            pDiffCurrParas->m_fFactor1 = 1;
        }

        pDiffCurrParas->m_fFactor2 = 1.000f;
        pDiffCurrParas->m_nPhase = m_nPhase;

        //差动参数
        pDiffCurrParas->m_fIdiff = m_fIdiff;
        pDiffCurrParas->m_fIbias = m_fIbias;
		pDiffCurrParas->m_fIsd=m_fIsd;
		pDiffCurrParas->m_fIcdqd=m_fIcdqd;

        // 谐波参数
        pDiffCurrParas->m_nHarmIndex = m_nHarmIndex;
        pDiffCurrParas->m_fCoefHarm2 = m_fCoefHarm2;
        pDiffCurrParas->m_fCoefHarm3 = m_fCoefHarm3;
        pDiffCurrParas->m_fCoefHarm5 = m_fCoefHarm5;
        pDiffCurrParas->m_nAutoSearch = m_nAutoSearch;


        pDiffCurrParas->m_nBinLogic = m_nBinLogic;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            pDiffCurrParas->m_binIn[i] = m_binIn[i];
            pDiffCurrParas->m_binOut[i] = m_binOut[i];
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            pDiffCurrParas->m_binInEx[i] = m_binInEx[i];
        }

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            pDiffCurrParas->m_binOutEx[i] = m_binOutEx[i];
        }
    }

}tmt_ElecRailwayDiffParas;

typedef struct tmt_elec_railway_diff_results :public tmt_DiffCurrResults
{
public:
    tmt_elec_railway_diff_results()
    {
    }
    virtual ~tmt_elec_railway_diff_results()
    {
    }

    float	m_fIalphaIe;
    float	m_fIalpha;
    float   m_fIbetaIe;
    float   m_fIbeta;

    virtual void init()
    {
        tmt_DiffCurrResults::init();
        m_fIalphaIe = 0;
        m_fIalpha = 0;
        m_fIbetaIe = 0;
        m_fIbeta = 0;
    }
}tmt_ElecRailwayDiffResults;


typedef struct tmt_elec_railway_diff_thr_test : public TMT_PARAS_HEAD // 差动启动电流测试
{
public:
    tmt_ElecRailwayDiffParas      m_oDiffCurrParas ;
    tmt_ElecRailwayDiffResults   m_oDiffCurrResults;
    int m_nThrType;		//0-启动电流；1-动作特性曲线

    virtual void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_ElecRailwayDiffTest);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oDiffCurrParas.init();
        m_oDiffCurrResults.init();
        m_nThrType = 0;
    }

	tmt_elec_railway_diff_thr_test()	{init();}
	virtual void clear_result(){	m_oDiffCurrResults.init();	}
	virtual ~tmt_elec_railway_diff_thr_test(){}
}tmt_ElecRailwayDiffThrTest;

typedef struct tmt_elec_railway_diff_rate_test : public tmt_ElecRailwayDiffThrTest // 差动比率制动
{
public:
    int m_nRateType;		//0-启动段斜率；1、2-比率制动系数一；3、4-比率制动系数二；5、6-比率制动系数三；7、8-比率制动系数四；
    virtual void init()
    {
        tmt_ElecRailwayDiffThrTest::init();
        m_nRateType = 0;
        strcpy(m_pszMacroID, STT_MACRO_ID_ElecRailwayDiffRateTest);
    }

	tmt_elec_railway_diff_rate_test()	{init();}
	virtual ~tmt_elec_railway_diff_rate_test(){}
}tmt_ElecRailwayDiffRateTest;

typedef struct tmt_elec_railway_diff_quick_test : public tmt_ElecRailwayDiffThrTest // 差动速断
{
public:
    virtual void init()
    {
        tmt_ElecRailwayDiffThrTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_ElecRailwayDiffQuickTest);
    }

	tmt_elec_railway_diff_quick_test()	{init();}
	virtual ~tmt_elec_railway_diff_quick_test(){}
}tmt_ElecRailwayDiffQuickTest;

typedef struct tmt_elec_railway_diff_harm_test : public tmt_ElecRailwayDiffThrTest // 谐波制动
{
public:
    virtual void init()
    {
        tmt_ElecRailwayDiffThrTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_ElecRailwayDiffHarmTest);
    }

	tmt_elec_railway_diff_harm_test()	{init();}
	virtual ~tmt_elec_railway_diff_harm_test(){}
}tmt_ElecRailwayDiffHarmTest;

typedef struct tmt_elec_railway_diff_act_time_test : public tmt_ElecRailwayDiffThrTest // 差动动作时间
{
public:
    virtual void init()
    {
        tmt_ElecRailwayDiffThrTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_ElecRailwayDiffTimeTest);
    }

	tmt_elec_railway_diff_act_time_test()	{init();}
	virtual ~tmt_elec_railway_diff_act_time_test(){}
}tmt_ElecRailwayDiffActTimeTest;


void stt_init_paras(tmt_ElecRailwayDiffParas *pParas);

void stt_xml_serialize_diff_search_results(tmt_ElecRailwayDiffParas *pParas, tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_rate(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_rate_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_quick(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_quick_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_harm(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_harm_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_acttime(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_acttime_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_ElecRailwayDiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(tmt_ElecRailwayDiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly);

void stt_xml_serialize_write_ElecRailwayDiffTest();
