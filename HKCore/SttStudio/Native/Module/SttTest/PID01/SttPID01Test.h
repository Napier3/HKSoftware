#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include"tmt_pid01_test.h"
#include "../../SttTestBase/SttTestBase.h"


class CSttPid01Test : public CSttTestBase, public tmt_Pid01Test
{
public:
	CSttPid01Test();
	virtual ~CSttPid01Test(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
		return new CSttPid01Test();
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

public:
    virtual void Init();
    virtual void StartTest();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
	virtual void TtmToDrv();
	virtual BOOL EventProcess();
};
