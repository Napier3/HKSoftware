#pragma once

#include "SttBP2DiffThrTest.h"


class CSttBP2DiffRateTest : public CSttBP2DiffThrTest
{
public:
    CSttBP2DiffRateTest();
    virtual ~CSttBP2DiffRateTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttBP2DiffRateTest();
	}

public:
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
