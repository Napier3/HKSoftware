#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include"tmt_pik100_test.h"
#include "../../SttTestBase/SttTestBase.h"


class CSttPik100Test : public CSttTestBase, public tmt_Pik100Test
{
public:
	CSttPik100Test();
	virtual ~CSttPik100Test(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
		return new CSttPik100Test();
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

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
	virtual void TtmToDrv();
	virtual BOOL EventProcess();
};
