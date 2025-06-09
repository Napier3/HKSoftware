#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"


class CSttHarmTest : public CSttTestBase//,public tmt_HarmTest
{
public:
    CSttHarmTest();
    virtual ~CSttHarmTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttHarmTest();
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

	tmt_HarmTest* m_pHarmTest;
public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
    virtual void AfterSetParameter();
    virtual double GetTestTimeLong();
    virtual long CalReport(UINT nState=0);

public:
    virtual void Init();
    virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual BOOL EventProcess();

	virtual bool TestPara_CheckOK(){return m_bTestParaCheckOk;}
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType);
public:
    virtual void TtmToDrv();
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
protected:
	float m_fOutPutTime;//Êä³öÏÞÊ±
};

class CSttMUHarmTest : public CSttHarmTest
{
public:
	CSttMUHarmTest()
	{
		m_strName = m_strMacroName;
		m_strID = m_strMacroID;//"1";
		m_strTestID = m_strMacroID;
	}
	virtual ~CSttMUHarmTest(void){}
	virtual void AfterSetParameter();

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strFilePostFix;

	static CSttTestBase* CreateTest()
	{
		return new CSttMUHarmTest();
	}
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
