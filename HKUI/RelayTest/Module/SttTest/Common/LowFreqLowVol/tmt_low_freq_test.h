#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"

#define LOW_FREQ_VOL_GRADIENT_TYPE_LOW_VOL                 0
#define LOW_FREQ_VOL_GRADIENT_TYPE_U2                      1
#define LOW_FREQ_VOL_GRADIENT_TYPE_3U0                     2


typedef struct tmt_low_freq_paras 
{
public:
    //故障参数
    int		m_nTestType;	//测试类型 0-频率动作值 1-动作时间 2-滑差闭锁值 3-低电流闭锁值 4-低电压闭锁值
    float	m_fDfdt;		//频率滑差
    float	m_fFstart;		//频率变化始值
    float	m_fFend;		//频率变化终值
    float	m_fFstep;		//频率变化步长
    float	m_fHoldTime;	//保持时间
    float   m_fMarginTime;  //故障时间裕度

    float	m_fDfdtStart;	//滑差变化始值
    float	m_fDfdtEnd;		//滑差变化终值
    float	m_fDfdtStep;	//滑差变化步长
    int     m_nDfdtTiming;    //滑差计时设置参数  0：开始滑差递变作为计时起点，1：滑差递变到整定值时开始计时  20240625Xuzt

    float	m_fIStart;		//电流变化始值
    float	m_fIEnd;		//电流变化终值
    float	m_fIStep;		//电流变化步长
    int		m_nIPhase;		//电流输出相 0:A相;1-B相;2-C相

    float	m_fUStart;		//电压变化始值
    float	m_fUEnd;		//电压变化终值
    float	m_fUStep;		//电压变化步长
    int		m_nUPhase;		//电压输出相

    float   m_fCurrSearchDfdt;//中间参数,当前搜索的滑差值

    //通用参数
// 	float	m_fInom;	//额定电流
// 	float	m_fUnom;	//额定电压
    float	m_fFnom;	//额定频率
    float	m_fPreFaultTime;//故障前时间
	int		m_nChangeMode;	//变化模式：0连续变化 1 按时间变化 
    float	m_fChangeTime;	//变化时间 仅ChangeMode==1时有效

    //整定值
    float	m_fFAct;		//动作频率
    float	m_fFActTime;	//动作时间
    float	m_fDfdtClose;	//滑差闭锁值
    float	m_fUlow;		//闭锁电压
    float	m_fILow;		//闭锁电流
    int		m_nUSetMode;	//闭锁电压定义  0-相电压 1-线电压 VSetMode

    int		m_nBinLogic;	//开入逻辑

    //Pvn新增
    float   m_fUabc[6];//0-2故障前，3-5故障后
    float   m_fUabcPh[6];
    float   m_fIabc[6];
    float   m_fIabcPh[6];

    //开关量
    tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
    tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	//
    tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];//

public:
    virtual void init()
    {
        m_nTestType = 0;
        m_fDfdt = 2.55f;
        m_fCurrSearchDfdt = 2.55f;
        m_fFstart = 48.65f;
        m_fFend = 48.35f;
        m_fFstep = 0.05f;
        m_fHoldTime = 1.2f;
        m_fMarginTime = 0;

        m_fDfdtStart = 3.3f;
        m_fDfdtEnd = 2.4f;
        m_fDfdtStep = 0.3f;
        m_nDfdtTiming = 0;

        m_fIStart = 0.8f;
        m_fIEnd = 1.2f;
        m_fIStep = 0.1f;
        m_nIPhase = 0;

        m_fUStart = 24;
        m_fUEnd = 36;
        m_fUStep = 1;
        m_nUPhase = 0;

        //通用参数
// 		m_fInom=0;
// 		m_fUnom=100;
        m_fFnom=50;
        m_fPreFaultTime = 5.0f;
        m_nChangeMode = 0;
        m_fChangeTime = 0.1f;

        //整定值
        m_fFAct = 48.5f;
        m_fFActTime = 1;
        m_fDfdtClose = 3;
        m_fUlow = 30;
        m_fILow = 1;
        m_nUSetMode = 1;
        m_nBinLogic = TMT_BINLOGIC_OR;

        float fAngle[3]={0,-120,120};
        for (int i=0;i<6;i++)
        {
            m_fUabc[i] = 57.74f;
            m_fIabc[i] = 0;
            m_fIabcPh[i] = m_fUabcPh[i] = fAngle[i%3];
        }

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
    }

}tmt_LowFreqParas;

typedef struct tmt_low_freq_paras_ex :public tmt_LowFreqParas
{
public:
    char	m_pszDfdt[PARAS_RSLT_EXPR_LEN];		//频率滑差
    char	m_pszFstart[PARAS_RSLT_EXPR_LEN];		//频率变化始值
    char	m_pszFend[PARAS_RSLT_EXPR_LEN];		//频率变化终值
    char	m_pszFstep[PARAS_RSLT_EXPR_LEN];		//频率变化步长
    char	m_pszHoldTime[PARAS_RSLT_EXPR_LEN];	//保持时间

    char	m_pszDfdtStart[PARAS_RSLT_EXPR_LEN];	//滑差变化始值
    char	m_pszDfdtEnd[PARAS_RSLT_EXPR_LEN];		//滑差变化终值
    char	m_pszDfdtStep[PARAS_RSLT_EXPR_LEN];	//滑差变化步长

    char	m_pszIStart[PARAS_RSLT_EXPR_LEN];		//电流变化始值
    char	m_pszIEnd[PARAS_RSLT_EXPR_LEN];		//电流变化终值
    char	m_pszIStep[PARAS_RSLT_EXPR_LEN];		//电流变化步长

    char	m_pszUStart[PARAS_RSLT_EXPR_LEN];		//电压变化始值
    char	m_pszUEnd[PARAS_RSLT_EXPR_LEN];		//电压变化终值
    char	m_pszUStep[PARAS_RSLT_EXPR_LEN];		//电压变化步长


    virtual void init()
    {
        tmt_LowFreqParas::init();
		memset(m_pszDfdt,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFstart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFend,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFstep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszHoldTime,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszHoldTime,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDfdtStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDfdtEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDfdtStep,0,PARAS_RSLT_EXPR_LEN);

		memset(m_pszIStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIStep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszUStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszUEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszUStep,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_LowFreqParasEx;

typedef struct tmt_low_freq_results
{
public:
    float	m_fLowFAct;
    float	m_fLowFActTime;
    float	m_fDfdtAct;
    float	m_fIAct;
    float	m_fUAct;
    long   m_nAct;//动作描述

public:
    virtual void init()
    {
        m_fLowFAct = 0.0f;
        m_fLowFActTime = 0.0f;
        m_fDfdtAct = 0.0f;
        m_fIAct = 0.0f;
        m_fUAct = 0.0f;
        m_nAct = 0.0f;
	} 

}tmt_LowFreqResults;

typedef struct tmt_low_freq_test : public TMT_PARAS_HEAD
{
public:
    tmt_LowFreqParasEx m_oLowFreqParas;
    tmt_LowFreqResults m_oLowFreqResults;
    virtual void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowFreqAct);
        m_nVersion = 0x00010001;
        m_nTestState = 0;
        memset(&m_oRsltExprMngr, 0, sizeof(TMT_PARAS_RSLT_EXPR_MNGR));

        m_oLowFreqParas.init();
        m_oLowFreqResults.init();
    }

	tmt_low_freq_test(){	init();}
	virtual void clear_result(){	m_oLowFreqResults.init();	}
	virtual ~tmt_low_freq_test(){}
}tmt_LowFreqTest;

typedef struct tmt_low_freq_time_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowFreqTime);
    }

	tmt_low_freq_time_test(){	init();}
	virtual ~tmt_low_freq_time_test(){}
}tmt_LowFreqTimeTest;

typedef struct tmt_low_freq_dfdt_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowFreqDfdt);
    }

	tmt_low_freq_dfdt_test(){	init();}
	virtual ~tmt_low_freq_dfdt_test(){}
}tmt_LowFreqDfDtTest;

typedef struct tmt_low_freq_ilock_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowFreqILock);
    }

	tmt_low_freq_ilock_test(){	init();}
	virtual ~tmt_low_freq_ilock_test(){}
}tmt_LowFreqILockTest;

typedef struct tmt_low_freq_ulock_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowFreqULock);
    }

	tmt_low_freq_ulock_test(){	init();}
	virtual ~tmt_low_freq_ulock_test(){}
}tmt_LowFreqULockTest;

typedef struct tmt_low_freq_time_pnv_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowFreqTime);
    }

    tmt_low_freq_time_pnv_test(){	init();}
    virtual ~tmt_low_freq_time_pnv_test(){}
}tmt_LowFreqTimePnvTest;

typedef struct tmt_low_freq_act_pnv_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowFreqAct);
    }

    tmt_low_freq_act_pnv_test(){	init();}
    virtual ~tmt_low_freq_act_pnv_test(){}
}tmt_LowFreqActPnvTest;

typedef struct tmt_low_freq_dfdt_pnv_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowFreqDfdt);
    }

    tmt_low_freq_dfdt_pnv_test(){	init();}
    virtual ~tmt_low_freq_dfdt_pnv_test(){}
}tmt_LowFreqDfdtPnvTest;

void stt_init_paras(tmt_LowFreqParas *pParas);
void stt_init_paras_ex(tmt_LowFreqParasEx *pParas);
void stt_init_results(tmt_LowFreqResults *pResults);

void stt_xml_serialize_PsuLowFreqAct(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqTime(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqDfDt(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqILock(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqULock(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqTime(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqAct(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqDfdt(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);


void stt_xml_serialize_PsuLowFreqAct_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqTime_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqDfDt_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqILock_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqULock_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);


void stt_xml_serialize_PsuLowFreqAct(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqTime(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqDfDt(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqILock(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqULock(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqTime(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqAct(tmt_LowFreqResults *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqDfdt(tmt_LowFreqResults *pParas, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_LowFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_LowFreq_search_results(tmt_LowFreqParas *pParas,tmt_LowFreqResults *pResults,CSttXmlSerializeBase *pXmlSerialize);

void stt_xml_serialize_ex(tmt_LowFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize, BOOL bResultOnly=FALSE);



