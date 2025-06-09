#pragma once

#include "SttGradientTest.h"

class CSttGradientMaxAngleTest : public CSttGradientTest
{
public:
	CSttGradientMaxAngleTest();
	virtual ~CSttGradientMaxAngleTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
		return new CSttGradientMaxAngleTest();
	}
public:


public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void Init();
	virtual void AfterSetParameter();
	virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent);
	virtual void SyncGradientResult(int nStep,double dTime,int nTripType){}//nTripType: 0-动作段 1-返回段
	virtual void TtmToDrv()
	{
		CSttGradientTest::TtmToDrv();
	}

	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType)
	{
		CSttGradientTest::ProRtDatasEvent(dTime1,dTime2,nStep,nState,nType);
	}

public:
	virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
	BOOL m_bAngleF_TestFinished;//边界角1测试完成
};
