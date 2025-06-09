#pragma once
#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_test_paras_head.h"

//触发条件:0无触发，1手动触发，2GPS触发，3开入量触发
#define COMTRADE_TRIGGRE_TYPE_No		0
#define COMTRADE_TRIGGRE_TYPE_Manual	1
#define COMTRADE_TRIGGRE_TYPE_GPS		2
#define COMTRADE_TRIGGRE_TYPE_Binary	3

//条件触发后模式：1循环播放完后切换，0：立即切换
#define COMTRADE_TRIGGRE_AFTER_TYPE_Immediately	0
#define COMTRADE_TRIGGRE_AFTER_TYPE_Normal		1

#define REPLAY_CHID_MAX_LENTH                   24
#define REPLAY_MODULE_CH_MAX_NUM               48
#define REPLAY_BINARY_MODULE_CH_MAX_NUM			16	//主板开出量通道数量
#define REPLAY_BINARYEX_MODULE_CH_MAX_NUM       64	//系统扩展开出量通道数量
#define REPLAY_FILE_PATH_MAX_LENTH			  2048

#define REPLAY_ACTIONTIMEZERO_COUNT            4


#define REPLAY_MODULE_TYPE_ANALOG		0		//模块类型-模拟量
#define REPLAY_MODULE_TYPE_BINARY		1		//模块类型-开出量
#define REPLAY_MODULE_TYPE_DIGITAL		2		//模块类型-数字量
#define REPLAY_MODULE_TYPE_WEEK			3		//模块类型-弱信号

#define INSERT_WAVE_TYPE_TIME			0		//插入原波形类型-时间
#define INSERT_WAVE_TYPE_POINT_INDEX	1		//插入原波形类型-点号

#define REPLAY_WEEK_CH_ELETYPE_VOL		0		//弱信号电气类型-电压
#define REPLAY_WEEK_CH_ELETYPE_CURR		1		//弱信号电气类型-电流

/*

<group name="模块1" id="Module1" data-type="Module">
<data name="选择" id="Sel" data-type="bool" unit="" value="1"/>
<data name="Index" id="Index" data-type="long" unit="" value="1"/>
<data name="Ch1ID" id="Ch1ID" data-type="string" unit="" value="Ua"/>
<data name="Ch2ID" id="Ch2ID" data-type="string" unit="" value="Ub"/>
<data name="Ch3ID" id="Ch3ID" data-type="string" unit="" value="Uc"/>
<data name="Ch4ID" id="Ch4ID" data-type="string" unit="" value="Uz"/>
</group>

*/

typedef struct tmt_module_ch_Binary
{
	long m_nBinaryChSel; 
	long m_nBinaryCh_Index;
}TMT_MODULE_CH_BINARY;

typedef struct tmt_module_ch
{
	char m_strChID[REPLAY_CHID_MAX_LENTH];
	long m_nChSel;

	long m_nChA_Index;
	long m_nChB_Index;
	float m_fChRate;

	//弱信号通道电气类型
	int m_nEeType;//0-电压 1-电流

}TMT_MODULE_CH;

typedef struct tmt_replay_module
{
    long m_nSel;
    long m_nIndex;//绝对位置
    long m_nChUseCount;
	long m_nModuleType;//模块类型 0-模拟量 1-开出量 2-数字量 3-弱信号


	float m_fPT_Prim;
	float m_fPT_Second;
	float m_fCT_Prim;
	float m_fCT_Second;

    void init()
	{
		m_nSel = 0;
		m_nModuleType = 0;

		m_fPT_Prim = 1.0f;
		m_fPT_Second = 1.0f;
		m_fCT_Prim = 1.0f;
		m_fCT_Second = 1.0f;
        for (int nIndex = 0;nIndex<REPLAY_MODULE_CH_MAX_NUM;nIndex++)
        {
            m_oChMap[nIndex].m_nChSel = 1;
            memset(m_oChMap[nIndex].m_strChID,0,REPLAY_CHID_MAX_LENTH);
			m_oChMap[nIndex].m_nChA_Index = 1;
			m_oChMap[nIndex].m_nChB_Index = 0;
			m_oChMap[nIndex].m_fChRate = 1.0f;

			m_oChMap[nIndex].m_nEeType = 0;
        }

		for (int nIndex = 0;nIndex<REPLAY_BINARYEX_MODULE_CH_MAX_NUM;nIndex++)
		{
			m_oBinaryChMap[nIndex].m_nBinaryChSel = 1;
			m_oBinaryChMap[nIndex].m_nBinaryCh_Index = 0;
		}
    }

    TMT_MODULE_CH m_oChMap[REPLAY_MODULE_CH_MAX_NUM];
	TMT_MODULE_CH_BINARY m_oBinaryChMap[REPLAY_BINARYEX_MODULE_CH_MAX_NUM];


}TMT_REPLAY_MODULE;

typedef struct tmt_replay_module_Binary
{
// 	long m_nSel;//有无主板开出
// 	long m_nIndex;//绝对位置
	long m_nChUseCount;

	void init()
	{
		m_nChUseCount = g_nBoutCount;
		for (int nIndex = 0;nIndex<REPLAY_BINARY_MODULE_CH_MAX_NUM;nIndex++)
		{
			m_oChMap[nIndex].m_nBinaryChSel = 1;
			m_oChMap[nIndex].m_nBinaryCh_Index = 0;
		}
	}

	TMT_MODULE_CH_BINARY m_oChMap[REPLAY_BINARY_MODULE_CH_MAX_NUM];

	void CloneOwn(tmt_replay_module_Binary *pDest)
	{
		pDest->m_nChUseCount = m_nChUseCount;
		for (int nIndex = 0;nIndex<REPLAY_BINARY_MODULE_CH_MAX_NUM;nIndex++)
		{
			pDest->m_oChMap[nIndex].m_nBinaryChSel = m_oChMap[nIndex].m_nBinaryChSel;
			pDest->m_oChMap[nIndex].m_nBinaryCh_Index = m_oChMap[nIndex].m_nBinaryCh_Index;
		}
	}

}TMT_REPLAY_MODULE_BINARY;

typedef struct tmt_replay_WaveEditPara
{	
	int m_nInsertWaveType;//插入原波形编辑类型 0-时间 1-点号

	//插入段
	typedef struct tmt_InsertWave_Data
	{
		double m_dBegin;//起点
		double m_dEnd;//终点
		long m_nBeginPoint;//起始点
		long m_nEndPoint;//终止点
		long m_nCycleIndex;//循环次数

	}TMT_INSERTWAVE_DATA;

	//删除段
	typedef struct tmt_DeleteWave_Data
	{
		double m_dBegin;//起点
		double m_dEnd;//终点

	}TMT_DELETEWAVE_DATA;

	//常态波形段
	typedef struct tmt_NormalWave_Insert
	{
		float m_fVoltage;//电压
		float m_fCurrent;//电流
		double m_dOutputTime;//输出时间

	}TMT_NORMALWAVE_INSERT;

	tmt_InsertWave_Data m_oInsertWaveData;
	tmt_DeleteWave_Data m_oDeleteWaveData;
	tmt_NormalWave_Insert m_oInsertNormalWaveData;

	void init()
	{	
		m_nInsertWaveType = INSERT_WAVE_TYPE_TIME;
		m_oInsertWaveData.m_dBegin = 0.0f;
		m_oInsertWaveData.m_dEnd= 0.0f;
		m_oInsertWaveData.m_nBeginPoint = 1;
		m_oInsertWaveData.m_nEndPoint = 1;
		m_oInsertWaveData.m_nCycleIndex = 1;

		m_oDeleteWaveData.m_dBegin = 0.0f;
		m_oDeleteWaveData.m_dEnd= 0.0f;

		m_oInsertNormalWaveData.m_fCurrent = 0.0f;
		m_oInsertNormalWaveData.m_fVoltage = 57.735f;
		m_oInsertNormalWaveData.m_dOutputTime = 0.0;

	}

	void CloneOwn(tmt_replay_WaveEditPara *pDest)
	{
		if(!pDest)
		{
			return;
		}
		pDest->m_nInsertWaveType = m_nInsertWaveType;

		pDest->m_oInsertWaveData.m_dBegin = m_oInsertWaveData.m_dBegin;
		pDest->m_oInsertWaveData.m_dEnd = m_oInsertWaveData.m_dEnd;
		pDest->m_oInsertWaveData.m_nBeginPoint = m_oInsertWaveData.m_nBeginPoint;
		pDest->m_oInsertWaveData.m_nEndPoint = m_oInsertWaveData.m_nEndPoint;
		pDest->m_oInsertWaveData.m_nCycleIndex = m_oInsertWaveData.m_nCycleIndex;

		pDest->m_oDeleteWaveData.m_dBegin = m_oDeleteWaveData.m_dBegin;
		pDest->m_oDeleteWaveData.m_dEnd = m_oDeleteWaveData.m_dEnd;

		pDest->m_oInsertNormalWaveData.m_fCurrent = m_oInsertNormalWaveData.m_fCurrent;
		pDest->m_oInsertNormalWaveData.m_fVoltage = m_oInsertNormalWaveData.m_fVoltage;
		pDest->m_oInsertNormalWaveData.m_dOutputTime = m_oInsertNormalWaveData.m_dOutputTime;
	}

}TMT_REPLAY_WAVEEDITPARA;

typedef struct tmt_replay_para
{
	TMT_REPLAY_MODULE_BINARY m_oBinaryModule;//主板开出
	BOOL m_bUseBinaryModule;//是否使用主板开出

    int m_nSampleFreq;
    long m_nModuleCount;
    TMT_REPLAY_MODULE m_oModule[MAX_MODULE_COUNT];
	TMT_REPLAY_WAVEEDITPARA m_oWaveEditPara;

    int m_nTripType;       //触发方式	0无触发，1手动触发，2GPS触发，3开入量触发
//     int m_nTrigTimeS;		//GPS时间触发有效
//     int m_nTrigTimeNS;
	tmt_time	    m_tGps;
    int m_nStartCycleNum;	//起始循环周波数，无触发有效
    int m_nTrigAfterMode;	//条件触发后模式：循环播放完后切换，：立即切换


	//电压电流功放
	float m_fPT_Prim;
	float m_fPT_Second;
	float m_fCT_Prim;
	float m_fCT_Second;

    int  m_nBinLogic;
    tmt_BinaryIn m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn m_binInEx[MAX_ExBINARY_COUNT];//系统扩展开关量
	char m_pszComtradeFilePath[REPLAY_FILE_PATH_MAX_LENTH];//20230803-wxy-录波文件名
	bool m_bInitChMapConfig;//20230907 wxy 是否初始化映射通道，使用于批量导入
	int m_bManualControl;//20230926 wxy 手动控制
	int m_nCycleIndex;//20230926 wxy 全部循环次数
	double m_dReplayInterval;//20240123 gongyiping 时间间隔(s)
	long m_nFileSize;//文件大小
	float m_frActionTimeZero[REPLAY_ACTIONTIMEZERO_COUNT];//2023-11-07 wuxinyi 计时起点
	tmt_BinaryIn m_frActionTimebinIn[MAX_BINARYIN_COUNT];//2023-11-07 wuxinyi 动作时间开关量
	tmt_BinaryIn m_frActionTimeBinInEx[MAX_ExBINARY_COUNT];//动作时间扩展开关量
	int m_nActionTimeBinLogic;//0-或 1-与

	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];//开出量
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];//系统扩展开关量

    tmt_replay_para()
    {
        init();
		initCommon();
		initActionTime();
		m_oWaveEditPara.init();
    }
    void init()
    {
        int nIndex = 0;
        m_nSampleFreq = 50000;
        m_nTripType = COMTRADE_TRIGGRE_TYPE_No;
		m_fPT_Prim = 1.0f;
		m_fPT_Second = 1.0f;
		m_fCT_Prim = 1.0f;
		m_fCT_Second = 1.0f;
//         m_nTrigTimeS = 0;
//         m_nTrigTimeNS = 0;
		m_tGps.init();
        m_nStartCycleNum = 0;
        m_nTrigAfterMode = COMTRADE_TRIGGRE_AFTER_TYPE_Immediately;

        m_nModuleCount = 0;
		m_bInitChMapConfig = FALSE;
        memset(m_oModule,0,sizeof(TMT_REPLAY_MODULE)*MAX_MODULE_COUNT);
        for (nIndex = 0;nIndex<MAX_MODULE_COUNT;nIndex++)
        {
            m_oModule[nIndex].init();
        }
		//2024-02-23 wuxinyi 新增开出量模块初始化
		m_bUseBinaryModule = FALSE;
		m_oBinaryModule.init();

        for (nIndex=0; nIndex<MAX_BINARYIN_COUNT; nIndex++)
        {
#ifdef _STT_NOT_IN_TEST_SERVER_
            if(nIndex<g_nBinCount)
            {
                m_binIn[nIndex].nSelect = 1;
            }
            else
            {
                m_binIn[nIndex].nSelect = 0;
            }
#else
			m_binIn[nIndex].nSelect = 0;
#endif
            m_binIn[nIndex].nTrigMode = 0;
        }

        for(nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
		{
			m_binInEx[nIndex].nSelect = 0;
			m_binInEx[nIndex].nTrigMode = 0;
		}

		for(nIndex = 0; nIndex < g_nBoutCount && nIndex < MAX_BINARYOUT_COUNT; nIndex++)
		{
			m_binOut[nIndex].nState = 0;
// 			m_binOut[nIndex].nTrigMode = 0;
		}

		for(nIndex = 0; nIndex < g_nBoutExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
		{
			m_binOutEx[nIndex].nState = 0;
// 			m_binOutEx[nIndex].nTrigMode = 0;
		}

		memset(m_pszComtradeFilePath,0,REPLAY_FILE_PATH_MAX_LENTH);
        m_nBinLogic = 0;
    }
    bool IsLoop()
    {
        if ((m_nTripType == COMTRADE_TRIGGRE_TYPE_No) && (m_nStartCycleNum == 0))
        {
            return false;
        }
        return true;
    }
    int GetModuleSelCount()
    {
        int nSelCount = 0;
		for (int i=0; i < MAX_MODULE_COUNT; i++)
        {
            if (m_oModule[i].m_nSel)
            {
                nSelCount++;
            }
        }
        return nSelCount;
    }
    int GetChSelCount()
    {
        int nChCount = 0;
		for (int i=0; i < MAX_MODULE_COUNT; i++)
        {
            if (m_oModule[i].m_nSel)
            {
				if(m_oModule[i].m_nModuleType == REPLAY_MODULE_TYPE_BINARY)
				{
					nChCount += 2;//开关量固定2个通道
				}
				else
				{
					for (int j=0; j<m_oModule[i].m_nChUseCount; j++)
					{
						if(m_oModule[i].m_oChMap[j].m_nChSel)
							nChCount++;
					}
				}
            }
        }

		if(m_bUseBinaryModule)
		{
			nChCount += 2;//主板开关量固定2个通道
		}
        return nChCount;
    }

	void initCommon()
	{
		m_bManualControl = 0;
		m_nCycleIndex = 0;
		m_dReplayInterval = 0;
		m_nFileSize = 0;
    }
	void initActionTime()
	{
		int nIndex = 0;
		for (nIndex=0; nIndex<MAX_BINARYIN_COUNT; nIndex++)
		{
			if(nIndex == 0)
			{
				m_frActionTimebinIn[nIndex].nSelect = 1;

			}
			m_frActionTimebinIn[nIndex].nSelect = 0;
			m_frActionTimebinIn[nIndex].nTrigMode = 0;
		}
		for (nIndex=0; nIndex<MAX_BINARYIN_COUNT; nIndex++)
		{
			if(nIndex == 0)
			{
				m_frActionTimeBinInEx[nIndex].nSelect = 1;

			}
			m_frActionTimeBinInEx[nIndex].nSelect = 0;
			m_frActionTimeBinInEx[nIndex].nTrigMode = 0;
		}
		for (nIndex=0; nIndex<REPLAY_ACTIONTIMEZERO_COUNT; nIndex++)
		{
			m_frActionTimeZero[nIndex] = 0.0f;
		}
		m_nActionTimeBinLogic = 0;
    }

	//主板开出量
	void BoutModuleToTmtBout()
	{
		for(int nChCount = 0; nChCount < m_oBinaryModule.m_nChUseCount; nChCount++)
		{
			m_binOut[nChCount].nState = m_oBinaryModule.m_oChMap[nChCount].m_nBinaryChSel;
		}
	}
	//系统扩展开出量
	void BoutModuleExToTmtBoutEx()
	{
		TMT_REPLAY_MODULE *pModule = NULL;
		int nBoutBeginIndex = 0;

		for(int i = 0; i<MAX_MODULE_COUNT;i++)
		{
			pModule = &m_oModule[i];
			if(pModule->m_nModuleType == REPLAY_MODULE_TYPE_BINARY)
			{
				for(int nChCount = 0; nChCount < pModule->m_nChUseCount;nChCount++)
				{
					m_binOutEx[nBoutBeginIndex].nState = pModule->m_oBinaryChMap[nChCount].m_nBinaryChSel;
					nBoutBeginIndex++;
				}
				nBoutBeginIndex = pModule->m_nChUseCount;
			}
		}
	}

}tmt_ReplayParas;


typedef struct tmt_replay_result
{
public:
    //结果参数,所有时间结果都是相对于实验开始的时间
    float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间
    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT]; //变位次数
    float	m_frTimeBinExAct[MAX_ExBINARY_COUNT][64];		//每一个开入记录64次变位时间
    int		m_nrBinExSwitchCount[MAX_ExBINARY_COUNT]; //变位次数
    float	m_fTestInTime; //触发时刻相对于实验开始的时间

public:
    virtual void init()
    {
        m_fTestInTime = 0;

        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            for (int j=0;j<64;j++)
            {
                m_frTimeBinAct[i][j] = 0;
            }
            m_nrBinSwitchCount[i] = 0;
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            for (int j=0;j<64;j++)
            {
                m_frTimeBinExAct[i][j] = 0;
            }
            m_nrBinExSwitchCount[i] = 0;
        }
    }

    tmt_replay_result()
    {
        init();
    }
}tmt_ReplayResult;

typedef struct tmt_replay_test : public TMT_PARAS_HEAD
{
    tmt_ReplayParas m_oReplayParas;//20230803-wxy-数组参数
    tmt_ReplayResult m_oReplayResult;//20230803-wxy-测试结果

    tmt_replay_test()
    {
        init();
    }
    void init()
    {
        init_head(); 
        strcpy(m_pszMacroID, STT_MACRO_ID_ReplayTest);
        m_nVersion = 0x00010001;
        m_nSelected = 1;
        m_nTestState = 0;
        m_oReplayParas.init();
        m_oReplayResult.init();
		
    }
}tmt_ReplayTest;


#ifndef _STT_NOT_IN_TEST_SERVER_
void stt_xml_serialize_replay(tmt_ReplayParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
#endif
void stt_xml_serialize(tmt_ReplayParas *pParas, CSttXmlSerializeBase *pXmlSierialize, int nHasAnalogMode = 1, int nHasDigitalMode = 1, int nHasWeekMode = 1);
void stt_xml_serialize_module(TMT_REPLAY_MODULE *pModule, int nIndex, CSttXmlSerializeBase *pXmlSierialize, int nHasAnalogMode = 1, int nHasDigitalMode = 1, int nHasWeekMode = 1);
void stt_xml_serialize_module_Binary(TMT_REPLAY_MODULE_BINARY *pBinaryModule, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_WaveEditParas(TMT_REPLAY_WAVEEDITPARA *pWaveEidtParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ReplayResult *pResult,  CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_write_ReplayTest();
CSttXmlSerializeBase* stt_xml_serialize(tmt_ReplayTest *pTests, CSttXmlSerializeBase *pXmlSerialize, int nHasAnalogMode = 1, int nHasDigitalMode = 1, int nHasWeekMode = 1);
CString stt_get_test_item_file_size(PTMT_PARAS_HEAD pParas);	//20231102 wxy 获取测试项文件大小

