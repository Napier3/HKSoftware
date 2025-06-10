#pragma once

#include"../../SttTestBase/SttTestBase.h"

class CSttTestForDebug : public CSttTestBase
{
public:
    CSttTestForDebug();
    virtual ~CSttTestForDebug(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttTestForDebug();
	}
public:

public:
	virtual void AfterSetParameter();
	virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);

     virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
	virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual BOOL EventProcess();
	virtual void Stop();

};
