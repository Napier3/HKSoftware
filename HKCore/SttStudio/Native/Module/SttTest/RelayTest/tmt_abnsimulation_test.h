#pragma once
#include "tmt_state_test.h"

#ifdef _PSX_IDE_QT_
#include "IEC61850CfgMngr.h"
#endif


enum tmt_smv_abnormal_type
{
    TYPE_SMV_NORMAL = 0,
    TYPE_SMV_LOST   = 1,
    TYPE_SMV_JITTE  = 2,
    TYPE_SMV_FLYPOINT = 3,
    TYPE_SMV_ERRCMPT  = 4,
    TYPE_SMV_DELAYOFFSET = 5,
    TYPE_SMV_DELAYMODEFY = 6,
    TYPE_SMV_INDEXERR = 7,
    TYPE_SMV_QUALITYERR = 8
};//0 正常；1 丢帧；2 抖动；3 飞点；4 错序；5 延时偏差；6 延时变化；7 序号偏差；？8 品质错误

enum tmt_SyncMode
{
	NO_SYNC_MODE = 0,
	LOCAL_SYNC_MODE = 1,
	GLOBAL_SYNC_MODE = 2
};//不同步，本地同步，全局同步

enum tmt_abnormal_type
{
    TYPE_NORMAL = 0,
    TYPE_SMV_ABNORMAL = 1,
    TYPE_GOOSE_ABNORMAL = 2
};//不同步，本地同步，全局同步


//typedef struct tmt_61850_9_2_setting
//{
//    CString strSrcMac;//源mac
//    CString strDestMac;//目的mac
//    int           nVlanID;//VLANID
//    int           nVlanPriority;//VLAN优先级
//    int           nNetFlag;//网络标识
//    int           nAppID;//appid
//    tmt_SyncMode nSyncMode;//同步方式
//    int     nVerNo;//版本号
//    int     nSamplingDelayTime;//采样延时
//    CString strDataSet;//数据集
//    CString strSVID;//SVID
//    BOOL    bRefrTm;//未知
//}tmt_Iec61850_9_2Setting;

enum tmt_SendType
{
	TYPE_CIRCLE = 0,
	TYPE_SECOND = 1
};//周波发送，按秒发送

typedef struct tmt_SvQlty_Set
{
    int nValid;//bit0-1: 00-好, 01-无效, 10-保留， 11-可疑
    BOOL bOverflow;//无溢出   溢出
    BOOL bOutRange;//正常   超值域
    BOOL bBadBmVal;//正常 坏基准值
    BOOL bJitter;//无抖动    抖动
    BOOL bFault;//无故障   故障
    BOOL bOldDataOT;//无超时   数据超时
    BOOL bInconformity;//一致  不一致
    BOOL bImprecise;//精确    不精确
    BOOL bSrc;//过程    被取代
    BOOL bTest;//运行    测试
    BOOL bOprLock;//操作员闭锁

    void init()
    {
        nValid = 0;
        bOverflow = false;
        bOutRange = false;
        bBadBmVal = false;
        bJitter = false;
        bFault = false;
        bOldDataOT = false;
        bInconformity = false;
        bImprecise = false;
        bSrc = false;
        bTest = false;
        bOprLock = false;
    }
    tmt_SvQlty_Set()	{}
    virtual ~tmt_SvQlty_Set(){}
}tmt_SvQltySet;

typedef struct tmt_smv_abnormal
{
    int nAbnType;//什么方式的异常
//	int nLoseStep;//失步？
//品质异常
	int nQualityInvalid;//品质？每bit的含义
//	int nTestMode;//检修
    BOOL bQltyInvChannel[50];//50个品质通道
    tmt_SvQltySet QltySet;
	
	float fOffsetTime;//延时偏差；
//	float fModefyTime;//延时变化；
	float fDelayTime;//延时时间
	
	float fFlyPointVolt;//飞点电压值
	float fFlyPointCur;//飞点电流值
    BOOL bVolFly[MAX_VOLTAGE_COUNT];//飞点电压使能
    BOOL bCurFly[MAX_CURRENT_COUNT];//飞点电流使能
//	unsigned int nJitterDirection;//抖动方向，默认单相
	unsigned int nJitter;//抖动值
	int nErrCmpt;//错序--跳变值？
	int nErrIndex;//序号偏差值
	//报文设置
	BOOL bSVAbnSet[80];//80个异常点使能

#ifdef _PSX_IDE_QT_
	tmt_sv_92 oIec61850_9_2Msg;
#endif

	int nSvGroupSel;//报文选择
    tmt_SendType nInvDataSndTyp;//异常数据发送方式0-按周波发送   1-按秒发送
	unsigned int nCircle;//发送周波数
	unsigned int nCirclePerSecond;//每秒发送周波数
	unsigned int nHoldTime;//发送时间，type按秒发送时候生效	

    void init()
    {
        QltySet.init();
        nAbnType = 0;
        fOffsetTime = 0.0f;
        fDelayTime = 0.0f;
        fFlyPointVolt = 0.0f;
        fFlyPointCur = 0.0f;
        for(int i = 0; i<MAX_VOLTAGE_COUNT; i++)
        {
            bVolFly[i] = false;
            bCurFly[i] = false;
        }
        nJitter = 0.0f;
        nErrCmpt = 0.0f;
        nErrIndex = 0.0f;
        nSvGroupSel = 0;
        nInvDataSndTyp = TYPE_CIRCLE;
        nCircle = 0;
        nCirclePerSecond = 0;
        nHoldTime = 0;

        for(int i=0; i<50; i++)
        {
            bQltyInvChannel[i] = false;
        }

        for(int i=0; i<80; i++)
        {
            bSVAbnSet[i] = false;
        }
    }
    tmt_smv_abnormal()	{init();}
    virtual ~tmt_smv_abnormal(){}
}tmt_SmvAbnormal;

typedef struct tmt_goose_abnormal
{
	CString strSrcMac;//源mac
	CString strDestMac;//目的mac
	CString strGcRef;
	CString strGoID;
	CString strDataSet;
	int     nVerNo;//版本号
	int     nSt;
	int     nSq;
	int     nTTL;
	int     nAppID;
	BOOL    bEntrust;//委托
    BOOL    bTest;//null
	int     nVlanID;
    int     nNetFlag;//null
	int     nVlanPriority;
	int     nTimeQlty;

    tmt_goose_abnormal()	{}
    virtual ~tmt_goose_abnormal(){}
}tmt_GooseAbnormal;

//enum tmt_state_bin_reversal		// PSU 开入翻转参考设置:0：	1：	2：
//{
//	TMT_MDSTATE_BINRVS_SWITCH=0,	    //0--开入翻转触发
//	TMT_MDSTATE_BINRVS_UP=1,			//1--开入上升沿触发
//	TMT_MDSTATE_BINRVS_DOWN=2,			//2--开入下降沿触发
//};

typedef struct tmt_abnstate_para
{
public:
    int                         m_nTriggerCondition;    //触发条件
    int                         m_nTrigJumpStateIndex;	//PSU 触发后跳转的状态序号
	tmt_state_bin_reversal   m_eBinReversal;//PSU 开入翻转参考设置:0：开入翻转触发	1：开入上升沿触发	2：开入下降沿触发
    float                     m_fTimeState;//输出时间
    float                     m_fTimeAfterTrigger;	//触发后延时
    tmt_time           m_tGps;
	//开关量
    int		          		   m_nBinLogic;			//0-或 1-与
    int		   				   m_nBinAndSelect;		// PSU	开入与触发有效位选择bit9~bit0对应通道9~通道0
    int		   				   m_nBinOrSelect;		// PSU	开入或触发有效位选择bit9~bit0对应通道9~通道0
    tmt_BinaryIn      m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut  m_binOut[MAX_BINARYOUT_COUNT];
	//通道
	tmt_channel         m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel         m_uiCUR[MAX_CURRENT_COUNT];	


    int                                       m_nAbnormalType;//0 正常 、SV异常、goose异常模拟
    tmt_SmvAbnormal     m_smvAbnormalPara;

#ifdef _PSX_IDE_QT_
	tmt_goose m_gooseAbnormalPara;
#endif


    BOOL	            m_bDC;			// 是否直流输出
    void init()
	{
        m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_fTimeState = 5;
		m_fTimeAfterTrigger = 0;
		m_nBinLogic = 0;
        m_nAbnormalType = 0;
        m_bDC = false;
        float fAng[3] = {0,-120,120};
        for (int j=0;j<6;j++)
        {
            m_uiVOL[j].Harm[1].fAmp = 57.74f;
            m_uiCUR[j].Harm[1].fAmp = 0;
            m_uiVOL[j].Harm[1].fAngle = m_uiCUR[j].Harm[1].fAngle = fAng[j%3];
            m_uiVOL[j].Harm[1].fFreq = m_uiCUR[j].Harm[1].fFreq = 50;
        }

        for (int j=0;j<MAX_BINARYOUT_COUNT;j++)
        {
            m_binOut[j].nState = 0;
            m_binOut[j].nMode = 0;
            m_binOut[j].fTimeTrig = 0;
            m_binOut[j].fHoldTime = 0;
            if(j<MAX_PARACOUNT_BINARY)
            {
                m_binIn[j].nSelect = 1;
            }
            else
            {
                m_binIn[j].nSelect = 0;
            }
            m_binIn[j].nTrigMode = 0;
        }
        m_nBinLogic = 0;
	}
    tmt_abnstate_para()	{}
    virtual ~tmt_abnstate_para(){}
}tmt_AbnStatePara;

typedef struct tmt_abnsimulation_paras
{
public:
    int         m_nStateNumbers;
    BOOL   m_bRepeat;				//是否循环输出
    int		   m_nRepeatNumbers;		//状态序列的重复次数
    int		   m_nBinTripRef;			//开入翻转参考状态 0-上一个状态 1-第一个状态
    BOOL   m_bPlusDC;				//是否叠加直流分量
    float	   m_fTao;			//直流分量的衰减时间常数: 所有UI通道共用
    BOOL   m_bSequence;			//是否为顺序状态序列

    tmt_AbnStatePara       m_AbnStatepara[MAX_STATE_COUNT];

    void init(long nStateNumbers = MAX_STATE_COUNT)
    {
        m_nStateNumbers = nStateNumbers;
        m_bRepeat = FALSE;
        m_nRepeatNumbers = 0;
        m_nBinTripRef = 1;
        m_bPlusDC = FALSE;
        m_fTao = 0;
        m_bSequence = true;

        for (int i=0;i<m_nStateNumbers;i++)
        {
            m_AbnStatepara[i].init();
        }
    }

    tmt_abnsimulation_paras(){}
    virtual ~tmt_abnsimulation_paras(){}
}tmt_AbnsimulationParas;

typedef struct tmt_abnsimulation_test
{
public:
    tmt_AbnsimulationParas       m_oAbnSimulationParas;
    tmt_StateResults   m_oStateResults;

    void init(long nStateNumbers = MAX_STATE_COUNT)
    {
        m_oAbnSimulationParas.init(nStateNumbers);
        m_oStateResults.init(nStateNumbers);
    }

    tmt_abnsimulation_test()	{}
    virtual ~tmt_abnsimulation_test(){}
}tmt_AbnSimulationTest;




/////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_write_AbnStateTest();
void stt_init_paras(tmt_AbnsimulationParas *pParas);
//void stt_init_results(tmt_StateResults *pResults);
void stt_xml_serialize(tmt_AbnsimulationParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//void stt_xml_serialize(tmt_StateResults *pResults,int nStateNums, CSttXmlSerializeBase *pXmlSierialize);







