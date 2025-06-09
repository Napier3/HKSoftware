#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include "SttGradientTest.h"

class CSttIRampTest : public CSttGradientTest
{
public:
	CSttIRampTest();
	virtual ~CSttIRampTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
		return new CSttIRampTest();
	}
public:


public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
//	virtual double GetTestTimeLong();
//	virtual long CalReport(UINT nState=0);

public:
    virtual void Init();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void AfterSetParameter();
//	virtual long SetParameter(DWORD dwState=0);
//    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
};
