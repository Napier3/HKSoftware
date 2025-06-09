#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"

typedef struct tmt_low_vol_paras 
{
public:
	//故障参数
	int		m_nTestType;	//测试类型 0-低压减载动作值 1-动作时间 2-电压滑差动作值 3-低电流闭锁值
	float	m_fDvdt;		//电压滑差
	float	m_fVstart;		//电压变化始值
	float	m_fVend;		//电压变化终值
	float	m_fVstep;		//电压变化步长
	float	m_fHoldTime;	//保持时间
	int		m_nFaultType;	//故障类型

	float	m_fDvdtStart;	//滑差变化始值
	float	m_fDvdtEnd;		//滑差变化终值
	float	m_fDvdtStep;	//滑差变化步长
    int     m_nDvdtTiming;    //滑差计时设置参数  0：开始滑差递变作为计时起点，1：滑差递变到整定值时开始计时

	float   m_fCurrSearchDvdt;//中间参数,当前搜索的滑差值

	float	m_fIStart;		//电流变化始值
	float	m_fIEnd;		//电流变化终值
	float	m_fIStep;		//电流变化步长
	int		m_nIPhase;		//电流输出相 0:A相;1-B相;2-C相

	//通用参数
// 	float	m_fInom;	//额定电流
// 	float	m_fVnom;	//额定电压
// 	float	m_fFnom;	//额定频率
	float	m_fPreFaultTime;//故障前时间
	int		m_nChangeMode;	//变化模式：0连续变化 1 按时间变化 
	float	m_fChangeTime;	//变化时间 仅ChangeMode==1时有效

	//整定值
	float	m_fUAct;		//低压闭锁值
	float	m_fUActTime;	//动作时间
	float	m_fDvdtClose;	//电压变化率闭锁值
	int		m_nUSetMode;	//闭锁电压定义  0-相电压 1-线电压 VSetMode
	float	m_fIAct;		//电流

	int		m_nBinLogic;	//开入逻辑

	//开关量
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	//
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];//

    //Pnv
    tmt_channel m_uiVOL[2][3];	//(故障前+故障)*最大电压数3
    tmt_channel m_uiCUR[2][3];
public:
	virtual void init()
	{
		m_fDvdt=68;
		m_fCurrSearchDvdt = 68;
		m_fVstart=49.5f;
		m_fVend=22.5f;
		m_fVstep=0.9f;
		m_fHoldTime=4.8f;
		m_nFaultType = 0;
		m_fDvdtStart = 88;
		m_fDvdtEnd = 68;
		m_fDvdtStep = 1.6f;
        m_nDvdtTiming = 0;

// 		m_fInom=0;
// 		m_fVnom=100;	//默认为线电压
// 		m_fFnom=50;
		m_fPreFaultTime = 5.0f;
		m_nChangeMode = 0;
		m_fChangeTime = 0.1f;

		m_fUAct=45;
		m_fUActTime=4;
		m_fDvdtClose=80;
		m_nUSetMode=1;
		m_fIAct=1;

		m_fIStart = 0.8f;
		m_fIEnd = 1.2f;
		m_fIStep = 0.1f;
		m_nIPhase = 0;

		m_nBinLogic = TMT_BINLOGIC_OR;
        float fAngle[3]={0,-120,120};
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<3; j++)
            {
                m_uiVOL[i][j].Harm[1].fAmp = 0;
                m_uiVOL[i][j].Harm[1].fAngle = fAngle[j];
                m_uiVOL[i][j].Harm[1].fFreq = 50;
                m_uiCUR[i][j].Harm[1].fAmp = 0;
                m_uiCUR[i][j].Harm[1].fAngle = fAngle[j];
                m_uiCUR[i][j].Harm[1].fFreq = 50;
            }
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

}tmt_LowVolParas;

typedef struct tmt_low_vol_paras_ex :public tmt_LowVolParas
{
public:
	char	m_pszDvdt[PARAS_RSLT_EXPR_LEN];		//电压滑差
	char	m_pszVstart[PARAS_RSLT_EXPR_LEN];		//电压变化始值
	char	m_pszVend[PARAS_RSLT_EXPR_LEN];		//电压变化终值
	char	m_pszVstep[PARAS_RSLT_EXPR_LEN];		//电压变化步长
	char	m_pszHoldTime[PARAS_RSLT_EXPR_LEN];	//保持时间
	char	m_pszDvdtStart[PARAS_RSLT_EXPR_LEN];	//滑差变化始值
	char	m_pszDvdtEnd[PARAS_RSLT_EXPR_LEN];		//滑差变化终值
	char	m_pszDvdtStep[PARAS_RSLT_EXPR_LEN];	//滑差变化步长

	char	m_pszIStart[PARAS_RSLT_EXPR_LEN];		//电流变化始值
	char	m_pszIEnd[PARAS_RSLT_EXPR_LEN];		//电流变化终值
	char	m_pszIStep[PARAS_RSLT_EXPR_LEN];		//电流变化步长

	virtual void init()
	{
		tmt_LowVolParas::init();
		memset(m_pszDvdt,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszVstart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszVend,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszVstep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszHoldTime,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDvdtStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDvdtEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDvdtStep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIStep,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_LowVolParasEx;

typedef struct tmt_low_vol_results
{
public:
	//结果参数
	float	m_fLowUAct;
	float	m_fLowUActTime;
	float	m_fDvdtAct;
	float	m_fIAct;

	long   m_nAct;//动作描述


public:
	virtual void init()
	{
		m_fLowUAct = 0.0f;
		m_fLowUActTime = 0.00f;
		m_fDvdtAct = 0.0f;
		m_fIAct = 0.0f;
		m_nAct = 0;
	} 

}tmt_LowVolResults;

typedef struct tmt_low_vol_test : public TMT_PARAS_HEAD
{
public:
	tmt_LowVolParasEx m_oLowVolParas;
	tmt_LowVolResults m_oLowVolResults;
	virtual void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowVolAct);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oLowVolParas.init();
		m_oLowVolResults.init();
	}

	tmt_low_vol_test(){	init();}
	virtual void clear_result(){	m_oLowVolResults.init();	}
	virtual ~tmt_low_vol_test(){}
}tmt_LowVolTest;

typedef struct tmt_low_vol_time_test : public tmt_LowVolTest
{
public:
	virtual void init()
	{
		tmt_LowVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowVolTime);
	}

	tmt_low_vol_time_test(){	init();}
	virtual ~tmt_low_vol_time_test(){}
}tmt_LowVolTimeTest;

typedef struct tmt_low_vol_dvdt_test : public tmt_LowVolTest
{
public:
	virtual void init()
	{
		tmt_LowVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowVolDvdt);
	}

	tmt_low_vol_dvdt_test(){	init();}
	virtual ~tmt_low_vol_dvdt_test(){}
}tmt_LowVolDvDtTest;

typedef struct tmt_low_vol_pnv_test : public TMT_PARAS_HEAD
{
public:
    tmt_LowVolParas m_oLowVolParas;
    tmt_LowVolResults m_oLowVolResults;
    virtual void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowVolAct);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oLowVolParas.init();
        m_oLowVolResults.init();
    }

    tmt_low_vol_pnv_test(){	init();}
    virtual void clear_result(){	m_oLowVolResults.init();	}
    virtual ~tmt_low_vol_pnv_test(){}
}tmt_PnvLowVolTest;

typedef struct tmt_low_vol_ilock_test : public tmt_LowVolTest
{
public:
	virtual void init()
	{
		tmt_LowVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowVolILock);
	}

	tmt_low_vol_ilock_test(){	init();}
	virtual ~tmt_low_vol_ilock_test(){}
}tmt_LowVolILockTest;

typedef struct tmt_low_vol_time_pnv_test : public tmt_PnvLowVolTest
{
public:
    virtual void init()
    {
        tmt_PnvLowVolTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowVolTime);
    }

    tmt_low_vol_time_pnv_test(){	init();}
    virtual ~tmt_low_vol_time_pnv_test(){}
}tmt_LowVolTimePnvTest;

typedef struct tmt_low_vol_dvdt_pnv_test : public tmt_PnvLowVolTest
{
public:
    virtual void init()
    {
        tmt_PnvLowVolTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowVolDvdt);
    }

    tmt_low_vol_dvdt_pnv_test(){	init();}
    virtual ~tmt_low_vol_dvdt_pnv_test(){}
}tmt_LowVolDvDtPnvTest;
void stt_init_paras(tmt_LowVolParas *pParas);
void stt_init_paras_ex(tmt_LowVolParasEx *pParas);
void stt_init_results(tmt_LowVolResults *pResults);

void stt_xml_serialize_PsuLowVolAct(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolTime(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolDvDt(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolILock(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_PnvLowVolAct(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowVolTime(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowVolDvDt(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_PsuLowVolAct_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolTime_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolDvDt_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolILock_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);


void stt_xml_serialize_PsuLowVolAct(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolTime(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolDvDt(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolILock(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_PnvLowVolAct(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowVolTime(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowVolDvDt(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_LowVolTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_PnvLowVolTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_LowVol_search_results(tmt_LowVolParas *pParas,tmt_LowVolResults *pResults,CSttXmlSerializeBase *pXmlSerialize);



