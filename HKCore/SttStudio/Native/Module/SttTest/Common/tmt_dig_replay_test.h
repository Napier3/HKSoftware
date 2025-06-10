#pragma once
#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_test_paras_head.h"

//触发条件:0无触发，1手动触发，2GPS触发，3开入量触发
#define DIG_REPLAY_TRIGGRE_TYPE_No	     	0
#define DIG_REPLAY_TRIGGRE_TYPE_Manual	    1
#define DIG_REPLAY_TRIGGRE_TYPE_GPS		    2
#define DIG_REPLAY_TRIGGRE_TYPE_Binary   	3

#define DIG_REPLAY_MODE_PkgTime     	    0//按报文时间回放
#define DIG_REPLAY_MODE_EqualInterval     	1//按等间隔回放
#define DIG_REPLAY_MODE_Custom          	2//按自定义回放

#define DIG_REPLAY_INTERVAL_TYPE_ALL  	    0//回放区间设置(全部)
#define DIG_REPLAY_INTERVAL_TYPE_Custom     1//回放区间设置(部分)

#define DIG_REPLAY_FIBER_MAX_NUM                   48//光口最大数量
#define DIG_REPLAY_CB_MAX_NUM                      48//控制块最大数量


typedef struct tmt_dig_replay_cb
{
	long m_nSelCB;//选择控制块
    long m_nFiberNum;//光口数量
    long m_oFiberIndex[DIG_REPLAY_FIBER_MAX_NUM];//光口号,从0开始编号
    long m_nAppID;
	long m_nTotalFrames;//总帧数
	long m_nBeginFrameIndex;//起始帧号,对应值小于等于0代表当前区间,未选择报文
	long m_nEndFrameIndex;//结束帧号
	float m_fOffsetTime;//延时补偿(单位:us)


    void init()
    {
		m_nFiberNum = 0;
		m_nSelCB = 1;
        for (int nIndex = 0;nIndex<DIG_REPLAY_FIBER_MAX_NUM;nIndex++)
        {
            m_oFiberIndex[nIndex] = 0;
        }

		m_nAppID = 0x4001;
		m_nTotalFrames = 0;
		m_nBeginFrameIndex = 0;
		m_nEndFrameIndex = 0;
		m_fOffsetTime = 0.0f;
    }

	BOOL HasSendDatas()//判断该控制块是否有发送数据(1:控制块是否选择;2:控制块是否关联输出光口)
	{
		if (m_nSelCB == 0)
		{
			return FALSE;
		}

		if (m_nFiberNum <= 0)
		{
			return FALSE;
		}

		return HasValidPkg();
	}

	BOOL HasSelCurrFiberIndex(long nFiberIndex)
	{
		for (int nIndex = 0;nIndex<m_nFiberNum;nIndex++)
		{
			if (nFiberIndex == m_oFiberIndex[nIndex])
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	BOOL HasValidPkg()
	{
		if (m_nBeginFrameIndex <= 0)
		{
			return FALSE;
		}

		if (m_nBeginFrameIndex>m_nEndFrameIndex)
		{
			return FALSE;
		}

		return TRUE;
	}
}TMT_DIG_REPLAY_CB;

typedef struct tmt_dig_replay_para
{
	long m_nCBNum_SV92;//9-2采样值控制块数量
    long m_nCBNum_GOOSE;//GOOSE控制块数量
	TMT_DIG_REPLAY_CB m_oCB_SV92[DIG_REPLAY_CB_MAX_NUM];
    TMT_DIG_REPLAY_CB m_oCB_GOOSE[DIG_REPLAY_CB_MAX_NUM];

    long m_nTripType;       //触发方式	0无触发，1手动触发，2GPS触发，3开入量触发
	long m_nReplayMode_SV;//SV回放模式
	long m_nReplayMode_GOOSE;//GOOSE回放模式
	float m_fEqualIntervalTimeSV;//SV等间隔的间隔时间(us)
	float m_fEqualIntervalTimeGOOSE;//GOOSE等间隔的间隔时间(us)
	float m_fShakeValue;//抖动值(us)
	long  m_nIsLoop;//是否循环(0不循环,1循环)
	long  m_nLoopNum;//循环次数,循环1次实际输出2次
	long  m_nReplayIntervalType;//回放区间设置类型(0:全部回放,1:部分回放)
	long m_nTotalFrameBeginIndex;//起始帧号
	long m_nTotalFrameEndIndex;//结束帧号
	tmt_time	    m_tGps;
	float       m_fOutPutTime;	// 最长输出时间,无需界面设置,传递给底层,用于控制输出停止

    long  m_nBinLogic;
    tmt_BinaryIn m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn m_binInEx[MAX_ExBINARY_COUNT];//系统扩展开关量

    tmt_dig_replay_para()
    {
        init();
    }
    void init()
    {
        int nIndex = 0;
		m_nCBNum_SV92 = 0;
        m_nCBNum_GOOSE = 0;
        m_nTripType = DIG_REPLAY_TRIGGRE_TYPE_No;
		m_nReplayMode_SV = DIG_REPLAY_MODE_PkgTime;
		m_nReplayMode_GOOSE = DIG_REPLAY_MODE_PkgTime;
		m_fEqualIntervalTimeSV = 250.0f;
		m_fEqualIntervalTimeGOOSE = 5000000.0f;
		m_fShakeValue = 0.0f;
		m_fOutPutTime = 5.0f;
		m_nIsLoop = 0;
		m_nLoopNum = 0;
		m_nReplayIntervalType = DIG_REPLAY_INTERVAL_TYPE_ALL;
		m_nTotalFrameBeginIndex = 0;
		m_nTotalFrameEndIndex = 0;
		m_tGps.init();
		memset(m_oCB_SV92,0,sizeof(TMT_DIG_REPLAY_CB)*DIG_REPLAY_CB_MAX_NUM);
        memset(m_oCB_GOOSE,0,sizeof(TMT_DIG_REPLAY_CB)*DIG_REPLAY_CB_MAX_NUM);

        for (nIndex = 0;nIndex<DIG_REPLAY_CB_MAX_NUM;nIndex++)
        {
			m_oCB_SV92[nIndex].init();
            m_oCB_GOOSE[nIndex].init();
        }

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

        m_nBinLogic = 0;
    }

	long GetUseFiberNum();//获取当前使用的光口总数量SV+GOOSE
	long GetTotalPkgNum(long nFiberIndex);//获取当前光口,SV+GOOSE报文的总帧数
	BOOL HasPcapSendDatas();//判断当前是否包含发送数据
	long GetCurSelCtrlNum_SVGOOSE();//获取当前选择的控制块数量
	void InitAllCB_TotalFrames();//20230824 suyang 初始化所有控制块的起始帧和结束帧

	TMT_DIG_REPLAY_CB* FindTotalPkgCtrl_SV(long nAppID);//获取到当前SV控制块
	TMT_DIG_REPLAY_CB* FindTotalPkgCtrl_GOOSE(long nAppID);//获取到当前GOOSE控制块

}tmt_DigReplayParas;

typedef struct tmt_dig_replay_test : public TMT_PARAS_HEAD
{
    tmt_DigReplayParas m_oReplayParas;

    tmt_dig_replay_test()
    {
        init();
    }
    void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_DigReplayTest);
        m_nVersion = 0x00010001;
        m_nSelected = 1;
        m_nTestState = 0;
        m_oReplayParas.init();
    }
}tmt_DigReplayTest;



void stt_xml_serialize(tmt_DigReplayParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_write_DigReplayTest();
CSttXmlSerializeBase* stt_xml_serialize(tmt_DigReplayTest *pTests, CSttXmlSerializeBase *pXmlSerialize);

