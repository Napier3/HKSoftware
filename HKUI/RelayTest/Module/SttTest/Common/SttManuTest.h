#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"

#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

class CSttManuTest : public CSttTestBase
{
public:
    CSttManuTest();
    virtual ~CSttManuTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttManuTest();
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

    tmt_ManualTest *m_pManualTest;

public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
    virtual void AfterSetParameter();
    virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	virtual long OnTimer(BOOL &bFinish, long nTimerLongMs=500);
    virtual void StartTest();
    virtual BOOL EventProcess();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Stop();
    void Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);//zhouhj 20210903 供高级试验调用
    BOOL CheckBeforeUpdatePara();//zhouhj 20211201 在更新参数前检查
	void GetBinStatus();

public:
    virtual void TtmToDrv();
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
protected:
	float m_fOutPutTime;//输出限时
};

class CSttMUAccuracyTest : public CSttManuTest
{
public:
	CSttMUAccuracyTest()
	{
		m_strName = m_strMacroName;
		m_strID = m_strMacroID;//"1";
		m_strTestID = m_strMacroID;
	}
	virtual ~CSttMUAccuracyTest(void){}

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strFilePostFix;

	static CSttTestBase* CreateTest()
	{
		return new CSttMUAccuracyTest();
	}
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
