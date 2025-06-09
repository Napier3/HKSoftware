#pragma once

#include "tmt_common_def.h"
#include "../../../../Module/BaseClass/ExBaseObject.h"

#define TMT_RESULT_ID_Time       		_T("Time")
#define TMT_RESULT_ID_RealTime  		_T("RealTime")
#define TMT_RESULT_ID_TimeStr  		    _T("TimeStr")

#define TMT_RESULT_ID_EventTime	_T("EventTime")

//记录测试过程中测试仪状态结构体
class CEventResult : public CExBaseObject
{
public:
	CString m_strEventID;
	SYSTEMTIME m_tmStart;		//开始测试时间
	double m_fActStart;	//计算动作时间的起始时间，Update后清0
	SYSTEMTIME m_tmEvent;
	double m_fActTime;			//开入量变位的动作时间
	double m_fTime; //开入量变位的真实时间
	CString m_strTimeStr;//底层上送的时间字符串

	long m_nUdc;			//辅助直流输出
	long m_nOverHeat;	//过热
	long m_nIOverLoad;	//电流过载
	long m_nUOverLoad;	//电压过载

	long m_nUShort;		//电压短路
	long m_IBreak[MAX_CURRENT_COUNT];		//电流开路

	long m_BinIn[MAX_BINARYIN_COUNT];		//开关量状态:断开0，合并1
	long m_BinOut[MAX_BINARYOUT_COUNT];

	long m_BinInEx[MAX_ExBINARY_COUNT];		//系统扩展开关量
	long m_BinOutEx[MAX_ExBINARY_COUNT];	

	long m_nCurrStateIndex;		//当前状态索引
	long m_nCurrStepIndex;		//当前递变步骤 add by yyj 2021.05.17

	virtual BOOL CopyOwn(CBaseObject* pDest)
	{
		CExBaseObject::CopyOwn(pDest);

		CEventResult *p = (CEventResult*)pDest;

		p->m_strEventID = m_strEventID;
		p->m_tmStart = m_tmStart;
		p->m_fActStart = m_fActStart;
		p->m_tmEvent = m_tmEvent;
		p->m_strTimeStr = m_strTimeStr;
		p->m_fActTime = m_fActTime;
		p->m_fTime = m_fTime;

		p->m_nUdc = m_nUdc;
		p->m_nOverHeat = m_nOverHeat;
		p->m_nIOverLoad = m_nIOverLoad;
		p->m_nUOverLoad = m_nUOverLoad;
		p->m_nUShort = m_nUShort;

		p->m_nCurrStateIndex = m_nCurrStateIndex;
		p->m_nCurrStepIndex = m_nCurrStepIndex;		//add by yyj 2021.05.17

		memcpy(p->m_IBreak,m_IBreak,sizeof(long)*MAX_CURRENT_COUNT);
		memcpy(p->m_BinIn,m_BinIn,sizeof(long)*MAX_BINARYIN_COUNT);
		memcpy(p->m_BinOut,m_BinOut,sizeof(long)*MAX_BINARYOUT_COUNT);
		memcpy(p->m_BinInEx,m_BinInEx,sizeof(long)*MAX_ExBINARY_COUNT);
		memcpy(p->m_BinOutEx,m_BinOutEx,sizeof(long)*MAX_ExBINARY_COUNT);

		return TRUE;
	}
	virtual CBaseObject* Clone()
	{
		CEventResult *p = new CEventResult();
		Copy(p);
		return p;
	}
	void init(bool bInitSwitch)
	{
		m_strEventID = _T("");
		GetLocalTime(&m_tmStart);
		m_fActStart = 0;
//		GetLocalTime(&m_tmActStart);
		GetLocalTime(&m_tmEvent);
		m_fActTime = 0;
		m_fTime = 0;
		m_strTimeStr = _T("");

		m_nUdc = 0;
		m_nOverHeat = 0;
		m_nIOverLoad = 0;
		m_nUOverLoad = 0;
		m_nCurrStateIndex = 0;
		m_nCurrStepIndex = 0;

		m_nUShort = 0;
		memset(m_IBreak,0,sizeof(long)*MAX_CURRENT_COUNT);

		if (bInitSwitch)
		{
			memset(m_BinIn,0,sizeof(long)*MAX_BINARYIN_COUNT);
			memset(m_BinOut,0,sizeof(long)*MAX_BINARYOUT_COUNT);
			memset(m_BinInEx,0,sizeof(long)*MAX_ExBINARY_COUNT);
			memset(m_BinOutEx,0,sizeof(long)*MAX_ExBINARY_COUNT);
		}	
	}
	void UpdateBinOut(tmt_BinaryOut	*parrBinOut,int nBinOutNum)
	{
		for(int i=0; i<nBinOutNum; i++)
		{
			m_BinOut[i] = parrBinOut[i].nState;
		}
	}
	void UpdateBinOutEx(tmt_BinaryOut *parrBinOut,int nBinOutNum)
	{
		for(int i=0; i<nBinOutNum; i++)
		{
			m_BinOutEx[i] = parrBinOut[i].nState;
		}
	}
	void GenEventDataGroup(CDataGroup& dataGroup,tmt_BinaryConfig* pBinaryCfg)
	{
		char strID[10];
		int i;

		dataGroup.DeleteAll();
		dataGroup.AddNewData("Udc",m_nUdc);
		dataGroup.AddNewData("OH",m_nOverHeat);
		dataGroup.AddNewData("OI",m_nIOverLoad);
		dataGroup.AddNewData("OV",m_nUOverLoad);
		dataGroup.AddNewData("UShort",m_nUShort);

		for (i=1; i<=MAX_BINARYIN_COUNT; i++)
		{
			sprintf(strID,"Bin%03d",i);
			long lValue = m_BinIn[i-1];
			if (pBinaryCfg)
			{
				lValue = (lValue<<1) + pBinaryCfg->m_binIn[i-1].nSelect;
			}
			
			dataGroup.AddNewData(strID,lValue);
		}

		for (i=1; i<=MAX_BINARYOUT_COUNT; i++)
		{
			sprintf(strID,"Bout%03d",i);
			long lValue = m_BinOut[i-1];
			if (pBinaryCfg)
			{
				lValue = (lValue<<1) + pBinaryCfg->m_binOut[i-1].nState;
			}

			dataGroup.AddNewData(strID,lValue);
		}
	}
	CEventResult(){	init(true);	}
};