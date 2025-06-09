#pragma once

#include "SttPowerDirectionTest.h"
#include "tmt_power_direction_test.h"


class CSttPowerDirectionPnvTest : public CSttPowerDirectionTest
{
public:
    CSttPowerDirectionPnvTest();
    virtual ~CSttPowerDirectionPnvTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttPowerDirectionPnvTest();
	}
public:

    virtual void AfterSetParameter();

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();

protected:

};
