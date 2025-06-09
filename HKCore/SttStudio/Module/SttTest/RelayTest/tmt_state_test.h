#pragma once

#include "tmt_common_def.h"
#include "../../SttTestBase/SttXmlSerialize.h"
#include "../../SttDevice/RelayTest/drv_define.h"


#define MAX_STATE_COUNT		20
#define MAX_BINARYIN_COUNT	20//xupf 20190620 修改数量为256，原64，内存越界处理
#define MAX_BINARYOUT_COUNT	20//xupf 20190620 修改数量为256，原64，内存越界处理
#define MAX_VOLTAGE_COUNT	32
#define MAX_CURRENT_COUNT	32
#define MAX_GOOSEPUB_COUNT	16
#define MAX_GOOSE_CHANNEL_COUNT	256

#define MAX_PARACOUNT_BINARY 8
#define MAX_STATETEST_COUNT	6

#define pi 3.1415926536

//////////////////////////////////////////////////////////////////////////
// 状态序列测试相关参数
#define  TMT_MDSTATE_TIMETRIGGER                       0	    //0--时间触发
#define  TMT_MDSTATE_TIMEBINTRIGGER                1    	//1--时间+开入量触发
#define  TMT_MDSTATE_BINTRIGGER                          2		//2--开入量触发
#define  TMT_MDSTATE_MEARSURETRIGGER          3      //3--手动触发
#define  TMT_MDSTATE_GPSBTRIGGER                      4		//4--GPS/B码触发
#define  TMT_MDSTATE_LOWVOLTRIGGER                 5     //5--低电压触发


enum tmt_state_bin_reversal		// PSU 开入翻转参考设置:0：	1：	2：
{
	TMT_MDSTATE_BINRVS_SWITCH=0,	    //0--开入翻转触发
	TMT_MDSTATE_BINRVS_UP=1,			//1--开入上升沿触发
	TMT_MDSTATE_BINRVS_DOWN=2,			//2--开入下降沿触发
};

typedef struct tmt_state_gradient		// PSU 状态内递变参数
{
	int  iVar;			//递变通道
	float fdfdt;        //df/dt值
	float fdvdt;        //dv/dt值
	float fTrigerV;		//触发电压
	float fStep;        //变化步长
	float fStepTime;    //步长时间
	float fEnd;         //变化终值
	float fStart;       //普通递变始值   

    void init()
    {
        iVar = 0;
       fdfdt=0;
        fdvdt=0;
        fStart=0;
        fEnd=0;
        fTrigerV=0;
        fStep=0;
        fStepTime=0;
    }

    tmt_state_gradient(){}
    virtual ~tmt_state_gradient(){}
}tmt_StateGradient;

typedef struct tmt_goose_pub
{
    BOOL m_bTest;// 是否置检修(0不置检修,1置检修)
    CString m_strChannel[MAX_GOOSE_CHANNEL_COUNT];

    void init()
    {
        m_bTest=0;

        for(int nIndex=0;nIndex<MAX_GOOSE_CHANNEL_COUNT;nIndex++)
        {
            m_strChannel[nIndex] = "";
        }
    }

    tmt_goose_pub(){}
    virtual ~tmt_goose_pub(){}
}tmt_GoosePub;

typedef struct tmt_state_para
{
public:
    int		            m_nTriggerCondition;
    int		            m_nTrigJumpStateIndex;	//PSU 触发后跳转的状态序号
    float	            m_fTimeState;
    float	            m_fTimeAfterTrigger;	//触发后延时
    tmt_time	    m_tGps;

	//开关量
	int		m_nBinLogic;			//0-或 1-与
	int		m_nBinAndSelect;		// PSU	开入与触发有效位选择bit9~bit0对应通道9~通道0
    int		m_nBinOrSelect;			// PSU	开入或触发有效位选择bit9~bit0对应通道9~通道0

    tmt_state_bin_reversal   m_eBinReversal;		//PSU 开入翻转参考设置:0：开入翻转触发	1：开入上升沿触发	2：开入下降沿触发
    tmt_BinaryIn                        m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut                    m_binOut[MAX_BINARYOUT_COUNT];

	//通道
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    float	                m_fVolAux;		// 辅助直流电压（仅模拟）
    float	                m_fCurAux;		// 辅助直流电流（仅模拟）
    BOOL	            m_bDC;			// 是否直流输出
    BOOL	            m_bTestMode;	// 是否检修模式
    int		                m_nRampType;	// 递变类型
    int		                m_nRampTimeGrad;// 递变时间分度
    tmt_StateGradient	m_sttGradient;

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_GOOSEPUB_COUNT];

    void init()
	{
        m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_fTimeState = 5;
		m_fTimeAfterTrigger = 0;
		m_nBinLogic = 0;
        m_fVolAux = 15;
		m_fCurAux = 0;

        // 递变参数
        m_nRampType = 0;
        m_sttGradient.init();

        float fAng[3] = {0,-120,120};

        for (int j=0;j<3;j++)
        {
            m_uiVOL[j].Harm[1].fAmp = 57.74f;
            m_uiCUR[j].Harm[1].fAmp = 0;
            m_uiVOL[j].Harm[1].fAngle = m_uiCUR[j].Harm[1].fAngle = fAng[j];
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

        // 递变参数
        m_nRampType = 0;
        m_sttGradient.init();

        for(int nIndex=0;nIndex<MAX_GOOSEPUB_COUNT;nIndex++)
            m_oGoosePub[nIndex].init();
	}

    tmt_state_para()	{}
    virtual ~tmt_state_para(){}

}tmt_StatePara;

typedef struct tmt_state_result
{
public://试验结果
    float	m_frTestTime;							//实际试验时间
    float	m_frInTime;		//状态进入时刻
    float	m_frTimeStateBegin;
    float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间
    float	m_frFlagBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间
    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT];

    void init()
    {
        m_frTestTime = 0;
        m_frInTime = 0;
        m_frTimeStateBegin = 0;

        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            for (int j=0;j<64;j++)
            {
                m_frTimeBinAct[i][j] = 0;
                m_frFlagBinAct[i][j] = 0;
            }

            m_nrBinSwitchCount[i] = 0;
        }
    }

    tmt_state_result()	{}
    virtual ~tmt_state_result(){}
}tmt_StateResult;

typedef struct tmt_state_paras
{
public:
    int		         m_nStateNumbers;
    BOOL	     m_bRepeat;				//是否循环输出
    int		         m_nRepeatNumbers;		//状态序列的重复次数
    int		         m_nBinTripRef;			//开入翻转参考状态 0-上一个状态 1-第一个状态
    BOOL	     m_bPlusDC;				//是否叠加直流分量
    float	         m_fTao;					//直流分量的衰减时间常数: 所有UI通道共用
    BOOL    	m_bSequence;			//是否为顺序状态序列

    tmt_StatePara       m_paraState[MAX_STATE_COUNT];

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
            m_paraState[i].init();
        }
    }

    tmt_state_paras(){}
    virtual ~tmt_state_paras(){}
}tmt_StateParas;

typedef struct tmt_state_results
{
public:
    tmt_StateResult       m_resultState[MAX_STATE_COUNT];

    void init(long nStateNumbers = MAX_STATE_COUNT)
    {
        for (int i=0;i<nStateNumbers;i++)
        {
            m_resultState[i].init();
        }
    }

    tmt_state_results(){}
    virtual ~tmt_state_results(){}
}tmt_StateResults;


typedef struct tmt_state_test
{
public:
    tmt_StateParas       m_oStateParas;
    tmt_StateResults   m_oStateResults;

    void init(long nStateNumbers = MAX_STATE_COUNT)
    {
        m_oStateParas.init(nStateNumbers);
        m_oStateResults.init(nStateNumbers);
    }

    tmt_state_test()	{}
    virtual ~tmt_state_test(){}
}tmt_StateTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_StateTest();
void stt_init_paras(tmt_StateParas *pParas);
void stt_init_results(tmt_StateResults *pResults);
void stt_xml_serialize(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_StateResults *pResults,int nStateNums, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ChannelHarm &oChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize);
