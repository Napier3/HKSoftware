#pragma once

#include"../../../SttTestBase/SttTestBase.h"
#include"../../../SttTestBase/SttComplexp.h"
#include"tmt_pt_test.h"
#include "../../../SttTestBase/SttTestBase.h"

#define PT100_R1_120_Ohm	0b0000
#define PT100_R1_100_Ohm	0b1000
#define PT100_R1_90_Ohm		0b1100
#define PT100_R2_120_Ohm	0b0000
#define PT100_R2_100_Ohm	0b0010
#define PT100_R2_90_Ohm		0b0011

class CSttPtTest : public CSttTestBase, public tmt_PtTest
{
public:
	CSttPtTest();
	virtual ~CSttPtTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
		return new CSttPtTest();
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
    virtual void Stop();

};
