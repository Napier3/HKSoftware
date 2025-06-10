#pragma once

#include "tmt_common_def.h"
#include "../../SttTestBase/SttXmlSerialize.h"
#include "tmt_test_paras_head.h"
#include "Abnormal/tmt_abnormal_test.h"

#define STATE_INIT_COUNT	6

//////////////////////////////////////////////////////////////////////////
//由于异步同步状态序列共同使用相关触发方式宏定义，将其移至tmt_common_def.h

// 状态序列测试相关参数
//#define  TMT_MDSTATE_TIMETRIGGER                       0	    //0--时间触发
//#define  TMT_MDSTATE_TIMEBINTRIGGER                1    	//1--时间+开入量触发
//#define  TMT_MDSTATE_BINTRIGGER                          2		//2--开入量触发
//#define  TMT_MDSTATE_MEARSURETRIGGER          3      //3--手动触发
//#define  TMT_MDSTATE_GPSBTRIGGER                      4		//4--GPS/B码触发
//#define  TMT_MDSTATE_LOWVOLTRIGGER                 5     //5--低电压触发


#define  STT_IMPEDANCE_BIN_STATE_SINGLE                                 0 //本开入作为单相跳闸
#define  STT_IMPEDANCE_BIN_STATE_THREE                                  1//本开入作为三相跳闸
#define  STT_IMPEDANCE_BIN_STATE_RECLOCE                                2//本开入作为重合闸

//#define  MAX_STATE_NAME			128  //zhouhj 20211208 对于GOOSE异常模拟此状态序列名称中长度可能超过32字节 将其改为128

//2024-3-27 xuzhantao  Pnv移植有多种UI数量，抽象为一个函数，用宏区分
#define  STT_PNV_STATE_6U6I         0
#define  STT_PNV_STATE_4U3I         1


enum tmt_state_gradient_type
{
	TMT_STATE_GRADIENT_NONE=0,
	TMT_STATE_GRADIENT_DFDT=1,			//按频率
	TMT_STATE_GRADIENT_DVDT=2,			//按电压
	TMT_STATE_GRADIENT_DFDVDT=3,		//组合频率、电压
	TMT_STATE_GRADIENT_COMMON=4,		//普通
};

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
	float fEndV;		//终止电压
	float fStartF;		//起始频率
	float fEndF;		//终止频率
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
        fStep=1;
        fStepTime=0.5;
		fEndV=0;
		fStartF=0;
		fEndF=0;
    }

    tmt_state_gradient()
	{	
		init(); 
	}
}tmt_StateGradient;

typedef struct tmt_state_close_angle		// 合闸角参数  zhouhj 20211015 用于阻抗类高级模块
{
	int   m_nFaultIncMode;		//合闸角选择 0-随机 1-定值  //zhouhj 20211015 增加用于阻抗类的合闸角设置
	float m_fCurCloseAngle;//电流合闸角
	float m_fVolCloseAngle;//电压合闸角
	float m_fRefCloseAngle;//界面设置的自定义合闸角
	int   m_nCloseChannel;//合闸通道

	void init()
	{
		m_nFaultIncMode = 0;
		m_fCurCloseAngle = 0;
		m_fVolCloseAngle=0;
		m_fRefCloseAngle=0;
		m_nCloseChannel=0;
	}

	tmt_state_close_angle()
	{	
		init(); 
	}
}tmt_StateCloseAngle;

typedef struct tmt_state_para
{
public:
	BOOL		 m_bSelected;			//状态是否勾选
	BOOL	     m_bPlusDC;				//是否叠加直流分量
	float				m_fTao;					//直流分量的衰减时间常数: 所有UI通道共用
    int		            m_nTriggerCondition;
    int		            m_nTrigJumpStateIndex;	//PSU 触发后跳转的状态序号
    float	            m_fTimeState;
    float	            m_fTimeAfterTrigger;	//触发后延时
    tmt_time	    m_tGps;
	char         m_strName[MAX_STATE_NAME];		//状态名称，默认最大16个汉字
	char         m_strID[MAX_STATE_ID];         //dingxy 202408 状态id，默认最大是State99,用于报告填充

	//开关量
	int		m_nBinLogic;			//0-或 1-与
	int		m_nBinAndSelect;		// PSU	开入与触发有效位选择bit9~bit0对应通道9~通道0
    int		m_nBinOrSelect;			// PSU	开入或触发有效位选择bit9~bit0对应通道9~通道0

	long	m_nBinaryOutType;//0-开出+Gse,1-只有开出,2-只有Gse
    tmt_state_bin_reversal   m_eBinReversal;		//PSU 开入翻转参考设置:0：开入翻转触发	1：开入上升沿触发	2：开入下降沿触发
	tmt_BinaryIn             m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryOut            m_binOut[MAX_BINARYOUT_COUNT];
	tmt_BinaryIn             m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut            m_binOutEx[MAX_ExBINARY_COUNT];

	//通道
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    float	                m_fVolAux;		// 辅助直流电压（仅模拟）
//    float	                m_fCurAux;		// 辅助直流电流（仅模拟）
	float       m_fOutputHoldTime;	// 开出量保持时间（开出翻转时间）
	BOOL	    m_bDC;			// 是否直流输出
    BOOL	            m_bTestMode;	// 是否检修模式
    int		                m_nRampType;	// 递变类型
	int		                m_nRampTimeGrad;// 递变时间分度毫秒
    tmt_StateGradient	m_sttGradient;

	tmt_StateCloseAngle   m_oCloseAngle;		//合闸角选择 0-随机 1-定值  //zhouhj 20211015 增加用于阻抗类的合闸角设置

    //GoosePub
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
    //Ft3Pub
    tmt_Ft3Pub  m_oFt3Pub[MAX_MODULES_FT3PUB_COUNT];

	tmt_StateAbnormalSMV m_oAbnormalSMV;
	tmt_StateAbnormalGOOSE m_oAbnormalGOOSE;

    void init()
	{
		m_bSelected = true;
		m_bPlusDC = FALSE;
		m_fTao = 0;
        m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_fTimeState = 5;
		m_fTimeAfterTrigger = 0;
		m_fOutputHoldTime = 0;
		m_nBinLogic = TMT_BINLOGIC_OR;
		m_nBinAndSelect = 0;
		m_nBinOrSelect = 0;
		m_nBinaryOutType = 0;
		m_bDC = 0;
      m_fVolAux = 0;
//		m_fCurAux = 0;
		m_bTestMode = false;
//		m_nRampType = TMT_STATE_GRADIENT_NONE;
		m_nRampTimeGrad = 0;
		memset(m_strName, 0, MAX_STATE_NAME);
		memset(m_strID, 0, MAX_STATE_ID);

		m_oCloseAngle.init();
		m_oAbnormalSMV.init();
		m_oAbnormalGOOSE.init();

        // 递变参数
        m_nRampType = 0;
        m_sttGradient.init();

        float fAng[3] = {0,-120,120};

		for (int j=0;j<MAX_VOLTAGE_COUNT;j++)
        {
			for(int k=0;k<MAX_HARM_COUNT;k++)
			{
				m_uiVOL[j].Harm[k].m_bSelect=FALSE;
				m_uiVOL[j].Harm[k].fAmp = 0;
				m_uiVOL[j].Harm[k].fAngle =  fAng[j%3];
				m_uiVOL[j].Harm[k].fFreq =  50;

				m_uiCUR[j].Harm[k].m_bSelect=FALSE;
				m_uiCUR[j].Harm[k].fAmp = 0;
				m_uiCUR[j].Harm[k].fAngle = fAng[j%3];
				m_uiCUR[j].Harm[k].fFreq = 50;
			}

			for (int nRampIndex = 0;nRampIndex < 3;nRampIndex++)
			{
				m_uiVOL[j].Ramp[nRampIndex].init();
				m_uiCUR[j].Ramp[nRampIndex].init();
			}
        }

		for (int j=0;j<MAX_BINARYIN_COUNT;j++)
        {
			m_binIn[j].nSelect = 0;
			m_binIn[j].nTrigMode = 0;

#ifdef _STT_NOT_IN_TEST_SERVER_
            if(j<g_nBinCount)
            {
                m_binIn[j].nSelect = 1;
            }
#endif
		}

        for (int j=0;j<MAX_BINARYOUT_COUNT;j++)
        {
			m_binOut[j].init();
        }

        for(int j = 0; j < g_nBinExCount && j < MAX_ExBINARY_COUNT; j++)
        {
			m_binInEx[j].nSelect = 0;//默认扩增开入不选中
			m_binInEx[j].nTrigMode = 0;
		}

        for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
		{
			m_binOutEx[j].init();//默认扩增开出全断开
		}

        m_nBinLogic = TMT_BINLOGIC_OR;

        // 递变参数
        m_nRampType = 0;
        m_sttGradient.init();

		for(int nIndex=0;nIndex<MAX_MODULES_GOOSEPUB_COUNT;nIndex++)
			m_oGoosePub[nIndex].init();

        for(int nIndex=0;nIndex<MAX_MODULES_FT3PUB_COUNT;nIndex++)
            m_oFt3Pub[nIndex].init();
	}

    void setDC(bool bDC,bool bUpdateAngleFre = false)
	{
		float fAngle[3] = {0, -120.0, 120.0};
		m_bDC = bDC;

		for (int j=0;j<MAX_VOLTAGE_COUNT;j++)
		{
			m_uiVOL[j].Harm[1].bDC = bDC;

			if (bDC)
			{
				m_uiVOL[j].Harm[1].fAngle = 0;
				m_uiVOL[j].Harm[1].fFreq = 0;
			}

			if (bUpdateAngleFre)
			{
				if (!bDC)
				{
					m_uiVOL[j].Harm[1].fFreq = 50;
					m_uiVOL[j].Harm[1].fAngle = fAngle[j%3];
				}
			}
		}

		for (int j=0;j<MAX_CURRENT_COUNT;j++)
		{
			m_uiCUR[j].Harm[1].bDC = bDC;

			if (bDC)
			{
				m_uiCUR[j].Harm[1].fAngle = 0;
				m_uiCUR[j].Harm[1].fFreq = 0;
			}

			if (bUpdateAngleFre)
			{
				if (!bDC)
				{
					m_uiCUR[j].Harm[1].fFreq = 50;
					m_uiCUR[j].Harm[1].fAngle = fAngle[j%3];
				}
			}
		}
	}

	void SetFundFreq(float fFreqValue)//设置基波频率
	{
		for (int nChIndex=0;nChIndex<MAX_VOLTAGE_COUNT;nChIndex++)
		{
			m_uiVOL[nChIndex].Harm[1].fFreq =  fFreqValue;
			m_uiCUR[nChIndex].Harm[1].fFreq = fFreqValue;
		}
	}

    tmt_state_para()
	{	
		init(); 
	}

}tmt_StatePara;

typedef struct tmt_state_result
{
public://试验结果
    float	m_frTestTime;							//实际试验时间,如果是递变相对于递变最后一步开始的时间
	long    m_nCurStepIndex;//当前变化的步数
	int m_nAct;//zhouhj 20210724 增加用于标识该状态中实际触发方式是否为开入量触发动作(否则需要根据与、或关系,遍历整个开入结果)????需讨论增加实际动作时间
	double	m_frInTime;		//状态进入绝对时刻
    float	m_frTimeStateBegin;//进入状态时刻相对开始试验时刻的相对时间

//    float	m_frFlagBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间
    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT];
    int    m_nBinFirstChgState[MAX_BINARYIN_COUNT];//状态内第一次变位的开入状态值(0:断开;1:闭合)
	float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间
	int     m_nRampIndex[MAX_BINARYIN_COUNT];//未动作为-1；0代表初始值即动作;1代表递变1步后动作

	int		m_nrBinExSwitchCount[MAX_ExBINARY_COUNT];
    int    m_nBinExFirstChgState[MAX_ExBINARY_COUNT];//状态内第一次变位的开入状态值(0:断开;1:闭合)
	float	m_frTimeBinExAct[MAX_ExBINARY_COUNT][64];		//每一个开入记录64次变位时间
	int     m_nRampIndexEx[MAX_ExBINARY_COUNT];//未动作为-1；0代表初始值即动作;1代表递变1步后动作
    void init()
    {
        m_frTestTime = 0;
		m_nCurStepIndex = 0;
        m_frInTime = 0;
        m_frTimeStateBegin = 0;
		m_nAct = 0;

        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            for (int j=0;j<64;j++)
            {
                m_frTimeBinAct[i][j] = 0;
            }

            m_nBinFirstChgState[i] = 0;
            m_nrBinSwitchCount[i] = 0;
			m_nRampIndex[i] = -1;
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for (int j=0;j<64;j++)
			{
				m_frTimeBinExAct[i][j] = 0;
			}

            m_nBinExFirstChgState[i] = 0;
			m_nrBinExSwitchCount[i] = 0;
			m_nRampIndexEx[i] = -1;
		}
    }

    tmt_state_result()	
	{ 
		init(); 
	}
    virtual ~tmt_state_result(){}
}tmt_StateResult;

typedef struct tmt_state_paras
{
public:
    int		         m_nStateNumbers;
//    BOOL	     m_bRepeat;				//是否循环输出
	int		         m_nRepeatNumbers;		//状态序列的重复次数 0:不循环
    int		         m_nBinTripRef;			//开入翻转参考状态 0-上一个状态 1-第一个状态
	int				 m_nPlusDC;				//是否叠加直流分量 0-不叠加 1-叠加 2-按状态叠加
    float	         m_fTao;					//直流分量的衰减时间常数: 所有UI通道共用
    BOOL    	m_bSequence;			//是否为顺序状态序列
	BOOL             m_bSearchNext;//用于差动的后续搜索

	//评估
	struct
	{
		BOOL		m_bUseError;//使能评估
		char		m_strTtripBegin_State[MAX_STATE_NAME];//计时起点_状态
		char		m_strTtripEnd_State[MAX_STATE_NAME];//计时终点_状态
		char		m_strTtripBegin_Bin[MAX_STATE_NAME];//计时起点_开入
		char		m_strTtripEnd_Bin[MAX_STATE_NAME];//计时终点_开入
		float		m_fActT_AbsErr;//绝对误差限
		float		m_fActT_RelErr;//相对误差限
		float		m_fTset;//整定值
		long		m_nErrorLogic;//判断逻辑
	}m_paraEstimates[10];

    tmt_StatePara*       m_paraState;
	int m_nStateCount;

	void initCommon()
	{
//		m_bRepeat = FALSE;
		m_nRepeatNumbers = 0;
		m_nBinTripRef = 1;
		m_nPlusDC = 0;
		m_fTao = 0;
		m_bSequence = TRUE;
		m_bSearchNext = FALSE;
		for (int i = 0; i < 10; i++)
		{
			memset(m_paraEstimates[i].m_strTtripBegin_State, 0, MAX_STATE_NAME);
			memset(m_paraEstimates[i].m_strTtripEnd_State, 0, MAX_STATE_NAME);
			memset(m_paraEstimates[i].m_strTtripBegin_Bin, 0, MAX_STATE_NAME);
			memset(m_paraEstimates[i].m_strTtripEnd_Bin, 0, MAX_STATE_NAME);
			m_paraEstimates[i].m_fActT_AbsErr = 0;
			m_paraEstimates[i].m_fActT_RelErr = 0;
			m_paraEstimates[i].m_fTset = 0;
			m_paraEstimates[i].m_nErrorLogic = 0;
			m_paraEstimates[i].m_bUseError = FALSE;
		}
	}

    void init(long nStateNumbers)
    {

		if (g_nStateCount > m_nStateCount)
		{
			if (m_paraState != NULL)
			{
				delete []m_paraState;
				m_paraState = NULL;
			}	
		}


        if(m_paraState == NULL)
        {
            m_paraState = new tmt_StatePara[g_nStateCount];
        }

        for (int i=0;i<nStateNumbers&&i<g_nStateCount;i++)
        {
            m_paraState[i].init();
        }

		m_nStateCount = g_nStateCount;
    }

	void SetSelect(int nIndex,bool bSel)
	{
        if (nIndex >= 0 && nIndex < g_nStateCount)
		{
			m_paraState[nIndex].m_bSelected = bSel;
		}
	}

	int GetSelCount()
	{
		int nCnt = 0;
		for (int i=0; i < m_nStateNumbers; i++)
		{
			if (m_paraState[i].m_bSelected)
			{
				nCnt++;
			}
		}
		return nCnt;
	}

	void SetFundFreq(float fFreqValue)
	{
		if (m_paraState == NULL)
		{
			return;
		}

		for (int i=0; i < m_nStateNumbers; i++)
		{
			m_paraState[i].SetFundFreq(fFreqValue);
		}
	}

    tmt_state_paras(){
		m_paraState = NULL;
		m_nStateCount = 0;
		initCommon();
	}

	virtual ~tmt_state_paras()
	{
		if (m_paraState != NULL)
		{
            delete[] m_paraState;
			m_paraState = NULL;
		}
	}
}tmt_StateParas;

typedef struct tmt_state_results
{
public:
    long m_nLoopIndex;
    int  m_nBinRefState[MAX_BINARYIN_COUNT];//暂存第一态结束开入值
    int  m_nBinExRefState[MAX_ExBINARY_COUNT];//暂存第一态结束开入值
    tmt_StateResult*  m_resultState;
	int m_nStateCount;//dxy 20240118 标记初始化g_nStateCount个数

	//评估
	struct
	{
		float m_fTtrip; //自定义动作时间
		float m_fTtrip_AbsErr;//自定义动作时间绝对误差
		float m_fTtrip_RelErr;//自定义动作时间相对误差
	}m_resultEstimates[10];


    void init(long nStateNumbers)
    {
		for (int i = 0; i < 10; i++)
		{
			m_resultEstimates[i].m_fTtrip = 0;
			m_resultEstimates[i].m_fTtrip_AbsErr = 0;
			m_resultEstimates[i].m_fTtrip_RelErr = 0;
		}

		if (g_nStateCount > m_nStateCount)//dxy 20240118 加判断防止g_nStateCount测试中更改，数组越界
		{
			if (m_resultState != NULL)
			{
				delete []m_resultState;
				m_resultState = NULL;
			}	
		}

        if(m_resultState == NULL)
        {
            m_resultState = new tmt_StateResult[g_nStateCount];
        }

        m_nLoopIndex = 0;
        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            m_nBinRefState[i] = 0;
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            m_nBinExRefState[i] = 0;
        }

        for(int i = 0; i < nStateNumbers && i < g_nStateCount; i++)
        {
            m_resultState[i].init();
        }
		m_nStateCount = g_nStateCount;
    }

    tmt_state_results()
	{
		m_resultState = NULL;
		m_nStateCount = 0;
	}
    virtual ~tmt_state_results()
	{
		if (m_resultState != NULL)
		{
            delete[] m_resultState;
			m_resultState = NULL;
		}
	}
}tmt_StateResults;

typedef struct tmt_state_test : public TMT_PARAS_HEAD
{
public:
    tmt_StateParas       m_oStateParas;
    tmt_StateResults   m_oStateResults;

    void init(long nStateNumbers)
    {
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_StateTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
        m_oStateParas.init(nStateNumbers);
        m_oStateResults.init(nStateNumbers);
    }

	tmt_state_test()	{init(0);}
}tmt_StateTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_StateTest();
void stt_init_paras(tmt_StateParas *pParas);
void stt_init_results(tmt_StateResults *pResults);
void stt_xml_serialize(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nHarmCount = MAX_HARM_COUNT);
void stt_xml_serialize(tmt_StateResults *pResults,tmt_StateParas *pStateParas,int nStateNums, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef);

//2024.5.17 Xuzt 新增pszDataTypeID参数表示电流/电压通道
void stt_xml_serialize(tmt_Channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize,const char *pszDataTypeID,int nHarmCount = MAX_HARM_COUNT);

//2024.5.17 Xuzt 新增pszDataTypeID参数表示电流/电压通道
void stt_xml_serialize_statenUnI_pnv(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,int nMode,long nHarmCount = 1);
void stt_xml_serialize_statenUnI_pnv(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,int nMode,const char *pszDataTypeID,long nHarmCount = 1);
void stt_xml_serialize_statenUnI_pnv(tmt_StateResults *pResults,tmt_StateParas *pStateParas,int nStateNums, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef);

void stt_xml_serialize(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize,int nHarmCount = MAX_HARM_COUNT);
void stt_xml_serialize_ex(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize,bool bSmvAbnormal, bool bGooseAbnormal);

void stt_xml_serialize_ex(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,bool bSel,long nHarmCount);
void stt_xml_serialize_ex2(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,bool bSel,long nHarmCount,bool bSmvAbnormal, bool bGooseAbnormal);
void stt_xml_serialize_ex2(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,bool bSel,long nHarmCount);

tmt_StatePara* stt_state_paras_insert_after(tmt_StateParas *pParas, tmt_StatePara *pSrc, int nAfter);
tmt_StatePara* stt_state_paras_insert_before(tmt_StateParas *pParas, tmt_StatePara *pSrc, int nBefore);
void stt_state_paras_delete(tmt_StateParas *pParas, int nIndex);
void stt_xml_serialize_dc(tmt_ChannelHarm &oChannel, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_act_rcd(tmt_StateResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_common(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_common(tmt_StateResults *pResults, BOOL *bUseErr, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_state_test *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,long nHarmCount);
CSttXmlSerializeBase* stt_xml_serialize(tmt_state_test *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,long nHarmCount, bool bSmvAbnormal, bool bGooseAbnormal);

void stt_xml_serialize_binary_in(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_binary_out(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize);
