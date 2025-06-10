#pragma once

#include "../Common/tmt_common_def.h"

#define TMT_RESULT_ID_EventTime	_T("EventTime")

//记录测试过程中测试仪状态结构体
typedef struct tmt_event_result
{
	long m_nUdc;			//辅助直流输出
	long m_nOverHeat;	//过热
	long m_nIOverLoad;	//电流过载
	long m_nUOverLoad;	//电压过载

	long m_nUShort;		//电压短路
	long m_IBreak[MAX_CURRENT_COUNT];		//电流开路

	long m_BinIn[MAX_BINARYIN_COUNT];		//开关量状态:断开0，合并1
	long m_BinOut[MAX_BINARYOUT_COUNT];

	long m_nCurrStateIndex;		//当前状态索引

	void init()
	{
		m_nUdc = 0;
		m_nOverHeat = 0;
		m_nIOverLoad = 0;
		m_nUOverLoad = 0;

		m_nUShort = 0;
		memset(m_IBreak,0,sizeof(long)*MAX_CURRENT_COUNT);

		memset(m_BinIn,0,sizeof(long)*MAX_BINARYIN_COUNT);
		memset(m_BinOut,0,sizeof(long)*MAX_BINARYOUT_COUNT);
	}
	void UpdateBinOut(tmt_BinaryOut	*parrBinOut,int nBinOutNum)
	{
		for(int i=0; i<nBinOutNum; i++)
		{
			m_BinOut[i] = parrBinOut[i].nState;
		}
	}
	tmt_event_result(){	init();	}
}tmt_EventResult;