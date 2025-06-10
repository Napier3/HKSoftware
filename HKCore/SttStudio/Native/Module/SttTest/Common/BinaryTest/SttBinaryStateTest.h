#pragma once

//#include "../SttStateTest.h"
#include"tmt_binary_state_test.h"
#include"../../../SttTestBase/SttTestBase.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/Module/Driver466/SttDeviceComm.h"
#endif


class CSttBinaryStateTest : public CSttTestBase//, public tmt_StateTest
{
public:
    CSttBinaryStateTest();
    virtual ~CSttBinaryStateTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttBinaryStateTest();
	}
public:  
    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

	tmt_StateTest *m_pStateTest;
	tmt_BinaryStateResults m_oResults;
public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();
	virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
	{
		CSttTestBase::ReturnTestStateEvent_TestStart(dTime,dRealTime,bWithEvent);
	}

public:
	virtual void Init();

	virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
	virtual BOOL EventProcess();
	virtual void InitStateLoopResults();
	virtual void SyncSingleStateTmtResult();
    virtual void StartTest();
	virtual void Stop(){CSttTestBase::Stop();}
	virtual void Triger();

    //将上层结构体转为底层结构体
public:
    virtual void TtmToDrv();

protected:
    long m_nfd;
#ifdef _PSX_QT_LINUX_
    Drv_ResultItem m_oDrvResItem;
#endif
    long m_nDrvResItemLen;
};




