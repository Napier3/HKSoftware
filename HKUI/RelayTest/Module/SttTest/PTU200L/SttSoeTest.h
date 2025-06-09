#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"tmt_soe_test.h"

typedef struct{
	unsigned int init_time[8]; //初始时间
	unsigned int firstfliptime[8]; // 第一次翻转时间
	unsigned int secondfliptime[8]; // 第二次翻转时间
	unsigned int flipcnt[8]; //翻转次数
	unsigned int init_val[8]; //初始值
}Drv_SoeState;

typedef struct{
	unsigned int triptype; //0: 立即触发 1: GPS 触发
	unsigned int sec;           //GPS s
	unsigned int nsec;          //GPS ns
	unsigned int holdtime;      //持续时间毫秒值
	Drv_SoeState soe;
}Drv_SOETest;

//时间单位是 100us
//初始值是0 开  1 合

class CSttSoeTest : public CSttTestBase, public tmt_SoeTest
{
public:
	CSttSoeTest();
	virtual ~CSttSoeTest(void);

	Drv_SOETest     m_oDrv_SOETest;

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

	static CSttTestBase* CreateTest()
	{
		return new CSttSoeTest();
	}
public:
	UINT m_uStartTimeS;
	UINT m_uStartTimeMS;
	UINT m_uChangeTime;
	UINT m_uChangeTimeMS;
	UINT m_uStartTimeNS;
	bool m_bIsReturn;
	UINT m_uReturnTimeMS;
	UINT m_uReturnTime;

public:
	//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();

	virtual long CalReport(UINT nState=0);

public:
	virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
	virtual void StartTest();
	virtual void EventProcess();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Stop();
	virtual BOOL NeedReadDeviceStatatus() {return FALSE;}

};
