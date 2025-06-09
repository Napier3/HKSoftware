#pragma once

#include "SttElecRailwayDiffThrTest.h"


class CSttElecRailwayDiffRateTest : public CSttElecRailwayDiffThrTest
{
public:
    CSttElecRailwayDiffRateTest();
    virtual ~CSttElecRailwayDiffRateTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttElecRailwayDiffRateTest();
	}

public:
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
