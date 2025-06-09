#pragma once
#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

//触发条件:0无触发，1手动触发，2GPS触发，3开入量触发
#define COMTRADE_TRIGGRE_TYPE_No		0
#define COMTRADE_TRIGGRE_TYPE_Manual	1
#define COMTRADE_TRIGGRE_TYPE_GPS		2
#define COMTRADE_TRIGGRE_TYPE_Binary	3

//条件触发后模式：1循环播放完后切换，0：立即切换
#define COMTRADE_TRIGGRE_AFTER_TYPE_Immediately	0
#define COMTRADE_TRIGGRE_AFTER_TYPE_Normal		1

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
typedef struct tmt_replay_module
{
	long m_nSel;
	long m_nIndex;//绝地位置
	long m_nChUseCount;

	typedef struct tmt_module_ch
	{
		char m_strChID[8];
	}TMT_MODULE_CH;

	TMT_MODULE_CH m_oChMap[6];

}TMT_REPLAY_MODULE;

typedef struct tmt_replay_test
{
	int m_nSampleFreq;
	long m_nModuleCount;
	TMT_REPLAY_MODULE m_oModule[MAX_MODULE_COUNT];

	int m_nTripType;       //触发方式	0无触发，1手动触发，2GPS触发，3开入量触发
	int m_nTrigTimeS;		//GPS时间触发有效
	int m_nTrigTimeNS;
	int m_nStartCycleNum;	//起始循环周波数，无触发有效
	int m_nTrigAfterMode;	//条件触发后模式：循环播放完后切换，：立即切换

	int  m_nBinLogic;
	tmt_BinaryIn m_binIn[MAX_BINARYIN_COUNT];

	tmt_replay_test()
	{
		init();
	}
	void init()
	{
		int i=0;
		m_nSampleFreq = 50000;
		m_nTripType = COMTRADE_TRIGGRE_TYPE_No;
		m_nTrigTimeS = 0;
		m_nTrigTimeNS = 0;
		m_nStartCycleNum = 6;
		m_nTrigAfterMode = COMTRADE_TRIGGRE_AFTER_TYPE_Immediately;

		m_nModuleCount = 0;
		memset(m_oModule,0,sizeof(TMT_REPLAY_MODULE)*MAX_MODULE_COUNT);

		for (i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			if(i<MAX_PARACOUNT_BINARY)
			{
				m_binIn[i].nSelect = 1;
			}
			else
			{
				m_binIn[i].nSelect = 0;
			}
			m_binIn[i].nTrigMode = 0;
		}
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
		for (int i=0; i<m_nModuleCount; i++)
		{
			if (m_oModule[i].m_nSel != 0)
			{
				nSelCount++;
			}
		}
		return nSelCount;
	}
	int GetChSelCount()
	{
		int nChCount = 0;
		for (int i=0; i<m_nModuleCount; i++)
		{
			if (m_oModule[i].m_nSel != 0)
			{
				nChCount += m_oModule[i].m_nChUseCount;
			}
		}
		return nChCount;
	}
}tmt_ReplayTest;



void stt_xml_serialize(tmt_ReplayTest *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_module(TMT_REPLAY_MODULE *pModule, int nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_write_ReplayTest();

