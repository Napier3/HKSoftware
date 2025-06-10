#pragma once

#include "SttElecRailwayDiffThrTest.h"


class CSttElecRailwayDiffHarmTest : public CSttElecRailwayDiffThrTest
{
public:
    CSttElecRailwayDiffHarmTest();
    virtual ~CSttElecRailwayDiffHarmTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttElecRailwayDiffHarmTest();
	}

public:
	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
	virtual void TranslateToStateParas();
};
