#pragma once

#include "../../SttTestBase/SttTestBase.h"
#include "tmt_light_anglectrl.h"

class CSttLightAngleCtrl : public CSttTestBase, public tmt_LightAngleTest
{
public:
	CSttLightAngleCtrl();
	virtual ~CSttLightAngleCtrl(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
		return new CSttLightAngleCtrl();
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
	virtual BOOL EventProcess();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void TtmToDrv();
};
