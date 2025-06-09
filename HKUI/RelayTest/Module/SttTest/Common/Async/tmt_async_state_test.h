#pragma once

#include "../tmt_common_def.h"
// #include "../../../SttTestBase/SttXmlSerialize.h"
#include "../tmt_test_paras_head.h"

//由于异步同步状态序列共同使用相关触发方式宏定义，将其移至tmt_common_def.h

typedef struct tmt_async_state_para
{
	BOOL		m_bSelected;							//状态是否选择
	BOOL	    m_bPlusDC;				//是否叠加直流分量
	float		m_fTao;					//直流分量的衰减时间常数: 所有UI通道共用
	char     	m_strName[MAX_STATE_NAME];		//状态名称，默认最大个汉字
	float	    m_fVolAux;			// 辅助直流电压（仅模拟）

	//开关量
	int							m_nBinLogic;			//0-或1-与
	int							m_nBinAndSelect;		// PSU	开入与触发有效位选择bit9~bit0对应通道~通道
	int							m_nBinOrSelect;		// PSU	开入或触发有效位选择bit9~bit0对应通道~通道
	
	long						m_nBinaryOutType;	//0-开出+Gse,1-只有开出,2-只有Gse
	tmt_BinaryIn				m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryOut				m_binOut[MAX_BINARYOUT_COUNT];
	tmt_BinaryIn				m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut				m_binOutEx[MAX_ExBINARY_COUNT];
	float						m_fOutputHoldTime;	// 开出量保持时间（开出翻转时间）

	//触发
	int					    m_nTriggerCondition;		// 触发方式
	float	          		m_fTimeState;				//输出时间
	float	         		m_fTimeAfterTrigger;		//触发后保持时间
	tmt_time				m_tGps;					//GPS触发时刻

	//模块
	tmt_AsyncModules		m_oStateAsyncModule;	
	//GoosePub
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
	//Ft3Pub
	tmt_Ft3Pub  m_oFt3Pub[MAX_MODULES_FT3PUB_COUNT];

	int		                m_nRampTimeGrad;// 递变时间分度毫秒

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
		m_fVolAux = 0;
		m_nRampTimeGrad = 0;
		memset(m_strName, 0, MAX_STATE_NAME);

		//模块
		m_oStateAsyncModule.init();

		//开关量
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

// 		InitModuleCh()

		//数字量模块固定位18U、18I
		m_oStateAsyncModule.m_oDigitalModules.initChannel(18,18);
		

	}

	tmt_async_state_para()
	{	
		init(); 
// 		initDigitalModule();
	}

	void Copy(tmt_async_state_para &pSrc)
	{
		m_bSelected = pSrc.m_bSelected;
		memcpy(m_strName,pSrc.m_strName,sizeof(pSrc.m_strName));
		m_fVolAux = pSrc.m_fVolAux;

		m_nBinLogic = pSrc.m_nBinLogic;
		m_nBinAndSelect = pSrc.m_nBinAndSelect;
		m_nBinOrSelect = pSrc.m_nBinOrSelect;

		m_nBinaryOutType = pSrc.m_nBinaryOutType;
		memcpy(m_binIn, pSrc.m_binIn, sizeof(m_binIn));
		memcpy(m_binOut, pSrc.m_binOut, sizeof(m_binOut));
		memcpy(m_binInEx, pSrc.m_binInEx, sizeof(m_binInEx));
		memcpy(m_binOutEx, pSrc.m_binOutEx, sizeof(m_binOutEx));
	
		m_fOutputHoldTime = pSrc.m_fOutputHoldTime;

		m_nTriggerCondition = pSrc.m_nTriggerCondition;
		m_fTimeState = pSrc.m_fTimeState;
		m_fTimeAfterTrigger = pSrc.m_fTimeAfterTrigger;
		m_tGps = pSrc.m_tGps;

		m_oStateAsyncModule.CopyOwn(pSrc.m_oStateAsyncModule);
		m_nRampTimeGrad = m_nRampTimeGrad;
	}

	void InitModuleCh(tmt_AsyncModule *pAnsyncModule, int nCurChCount, int nVolChCount)
	{
		pAnsyncModule->initChannel(nCurChCount, nVolChCount);

		float fAng[3] = {0,-120,120};
		for(int nIndex=0;nIndex<nCurChCount;nIndex++)
		{
			pAnsyncModule->m_pCurrChannel[nIndex].m_oHarm.m_bSelect = TRUE;
			pAnsyncModule->m_pCurrChannel[nIndex].m_oHarm.fAmp = 0;
			pAnsyncModule->m_pCurrChannel[nIndex].m_oHarm.fAngle = fAng[nIndex%3];
			pAnsyncModule->m_pCurrChannel[nIndex].m_oHarm.fFreq = 50;
		}
		for(int nIndex=0;nIndex<nVolChCount;nIndex++)
		{
			pAnsyncModule->m_pVolChannel[nIndex].m_oHarm.m_bSelect = TRUE;
			pAnsyncModule->m_pVolChannel[nIndex].m_oHarm.fAmp = 0;
			pAnsyncModule->m_pVolChannel[nIndex].m_oHarm.fAngle = fAng[nIndex%3];
			pAnsyncModule->m_pVolChannel[nIndex].m_oHarm.fFreq = 50;
		}
		
	}

	void setDC(bool bDC, int nModuleType, bool bUpdateAngleFre = false)
	{
		m_oStateAsyncModule.m_nDc[nModuleType] = bDC;

		tmt_AsyncModule *pAnsyncModule = NULL;
		int nNum = 0;
		float fAngle[3] = {0, -120.0, 120.0};

		switch (nModuleType)
		{
		case ASYNC_MODULE_TYPE_ANALOG:
			pAnsyncModule = m_oStateAsyncModule.m_oAnalogModules;
			nNum = m_oStateAsyncModule.m_nAnalogCount;
			break;
		case ASYNC_MODULE_TYPE_DIGITAL:
			pAnsyncModule = &m_oStateAsyncModule.m_oDigitalModules;
			nNum = 1; // 只有一个数字模块
			break;
		case ASYNC_MODULE_TYPE_WEEK:
			pAnsyncModule = m_oStateAsyncModule.m_oWeekModules;
			nNum = m_oStateAsyncModule.m_nWeekCount;
			break;
		default:
			return;
		}

		if (!pAnsyncModule->m_pCurrChannel || !pAnsyncModule->m_pVolChannel)
		{
			return;
		}

		for (int nIndex = 0; nIndex < nNum; nIndex++)
		{
			for (int nChannelIndex = 0; nChannelIndex < pAnsyncModule[nIndex].m_nCurrChCount; nChannelIndex++)
			{
				if (bDC)
				{
					pAnsyncModule[nIndex].m_pCurrChannel[nChannelIndex].m_oHarm.fAngle = 0;
					pAnsyncModule[nIndex].m_pCurrChannel[nChannelIndex].m_oHarm.fFreq = 0;
				}
				if (bUpdateAngleFre && !bDC)
				{
					pAnsyncModule[nIndex].m_pCurrChannel[nChannelIndex].m_oHarm.fFreq = 50;
					pAnsyncModule[nIndex].m_pCurrChannel[nChannelIndex].m_oHarm.fAngle = fAngle[nChannelIndex % 3];
				}
			}

			for (int nChannelIndex = 0; nChannelIndex < pAnsyncModule[nIndex].m_nVolChCount; nChannelIndex++)
			{
				if (bDC)
				{
					pAnsyncModule[nIndex].m_pVolChannel[nChannelIndex].m_oHarm.fAngle = 0;
					pAnsyncModule[nIndex].m_pVolChannel[nChannelIndex].m_oHarm.fFreq = 0;
				}
				if (bUpdateAngleFre && !bDC)
				{
					pAnsyncModule[nIndex].m_pVolChannel[nChannelIndex].m_oHarm.fFreq = 50;
					pAnsyncModule[nIndex].m_pVolChannel[nChannelIndex].m_oHarm.fAngle = fAngle[nChannelIndex % 3];
				}
			}
		}
	}


// 	void initDigitalModule()
// 	{
// 		InitModuleCh(&m_oStateAsyncModule.m_oDigitalModules,18,18);
// 	}
}tmt_AsyncStatePara;

typedef struct tmt_async_state_paras
{
	int	m_nStateNumbers;		//状态序号
	int	m_nStateCount;		//g_nStateCount
	int	m_nRepeatNumbers;		//状态序列的重复次数 0:不循环
	int	m_nBinTripRef;			//开入翻转参考状态 0-上一个状态 1-第一个状态
	int	m_nPlusDC;				//是否叠加直流分量 0-不叠加 1-叠加 2-按状态叠加
	float m_fTao;					//直流分量的衰减时间常数: 所有UI通道共用
	tmt_AsyncStatePara*  m_paraState;
	
	void initCommon()
	{
		m_nBinTripRef = 1;
	}

	void init(long nStateNumbers)
	{
		m_nRepeatNumbers = 0;
		m_nBinTripRef = 1;
		m_nPlusDC = 0;
		m_fTao = 0;
// 		m_nStateCount = nStateCount;
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
			m_paraState = new tmt_AsyncStatePara[g_nStateCount];
		}

		for (int i=0;i<nStateNumbers&&i<g_nStateCount;i++)
		{
			m_paraState[i].init();
		}

		m_nStateCount = g_nStateCount;
	}

	tmt_async_state_paras(){
		m_paraState = NULL;
		m_nStateCount = 0;
		initCommon();
	}

	virtual ~tmt_async_state_paras()
	{
		if (m_paraState != NULL)
		{
			delete[] m_paraState;
			m_paraState = NULL;
		}
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

}tmt_AsyncStateParas;

typedef struct tmt_async_state_result
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

	tmt_async_state_result()	
	{ 
		init(); 
	}
	virtual ~tmt_async_state_result(){}
}tmt_AsyncStateResult;

typedef struct tmt_async_state_results
{
public:
	long m_nLoopIndex;
	int  m_nBinRefState[MAX_BINARYIN_COUNT];//暂存第一态结束开入值
	int  m_nBinExRefState[MAX_ExBINARY_COUNT];//暂存第一态结束开入值
	tmt_AsyncStateResult*  m_resultState;
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
			m_resultState = new tmt_AsyncStateResult[g_nStateCount];
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

	tmt_async_state_results()
	{
		m_resultState = NULL;
		m_nStateCount = 0;
	}
	virtual ~tmt_async_state_results()
	{
		if (m_resultState != NULL)
		{
			delete[] m_resultState;
			m_resultState = NULL;
		}
	}
}tmt_AsyncStateResults;

typedef struct tmt_async_state_test : public TMT_PARAS_HEAD
{
	tmt_AsyncStateParas		m_oStateAsyncParas;
	tmt_AsyncStateResults	m_oStateAsyncResults;

	void init(long nStateNumbers)
	{
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_AnsyncStateTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
		m_oStateAsyncParas.init(nStateNumbers);
		m_oStateAsyncResults.init(nStateNumbers);
	}

	tmt_async_state_test()	{init(0);}

}tmt_AsyncStateTest;




void stt_xml_serialize(tmt_async_channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_AsyncStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
BOOL stt_xml_serialize(tmt_AsyncStatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_AsyncStateResults *pResults,tmt_AsyncStateParas *pStateParas,int nStateNums, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef);
void stt_xml_serialize(tmt_AsyncStateResult &oStateResult, tmt_AsyncStatePara oParaState, long nStateIndex, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef,int *pnFirstBinInitState,int *pnFirstBinExInitState);
void stt_xml_serialize_Analog(tmt_async_module *pModule, int nSubModuleType, int nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex2(tmt_AsyncStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, bool bSel);


CSttXmlSerializeBase* stt_xml_serialize(tmt_async_state_test *pParas, CSttXmlSerializeBase *pXmlSierialize/*, long nVolRsNum,long nCurRsNum,long nHarmCount*/);
void stt_xml_serialize_write_AsyncStateTest();
void stt_xml_serialize_binary_in(tmt_AsyncStatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_binary_out(tmt_AsyncStatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_Modules(tmt_async_modules *pModules, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_Digital(tmt_async_module *pModule, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_Week(tmt_async_module *pModule, int nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_act_rcd(tmt_AsyncStateResult *pResults, CSttXmlSerializeBase *pXmlSierialize)/*动作记录,最大64次,根据实际动作情况,上送总的动作信息 */;

tmt_AsyncStatePara *stt_async_state_paras_insert_after(tmt_AsyncStateParas *pParas, tmt_AsyncStatePara *pSrc, int nAfter);
void stt_async_state_paras_delete(tmt_AsyncStateParas *pParas, int nIndex);
void stt_xml_serialize_common(tmt_AsyncStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
