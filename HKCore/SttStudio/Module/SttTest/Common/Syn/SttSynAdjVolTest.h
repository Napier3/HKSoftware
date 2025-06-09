#pragma once

#include"../../../SttTestBase/SttTestBase.h"
#include"../../../SttTestBase/SttComplexp.h"

#include "SttSynActVolTest.h"

class CSttSynAdjVolTest : public CSttSynActVolTest
{
public:
    CSttSynAdjVolTest();
    virtual ~CSttSynAdjVolTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttSynAdjVolTest();
    }

public:
    virtual long CalReport(UINT nState=0);

public:
    virtual void Init();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
	virtual void TranslateToStateParas();
    virtual void ReCalVoltCurr(STT_RTDATA_EVENT &oRTDATA);
};
