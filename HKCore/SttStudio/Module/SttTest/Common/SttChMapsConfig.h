#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include "../../SttCmd/SttChMaps.h"

class CSttChMapsConfig : public CSttTestBase
{
public:
    CSttChMapsConfig();
    virtual ~CSttChMapsConfig(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase *CreateTest()
    {
        return new CSttChMapsConfig();
    }

public:


public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
    virtual void AfterSetParameter();
    virtual double GetTestTimeLong();
    virtual long CalReport(UINT nState = 0);

public:
    virtual void Init();
    virtual void Stop() {}
    virtual long SetParameter(DWORD dwState = 0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

private:
    void ChMapsConfig(CSttChMaps &oChMaps);
};
