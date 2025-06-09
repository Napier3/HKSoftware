#pragma once

#include "../SttStateTest.h"
#include "tmt_voltage_pnv_test.h"


class CSttVoltagePnvTest : public CSttStateTest ,public tmt_VoltagePnvParas
{
public:
    CSttVoltagePnvTest();
    virtual ~CSttVoltagePnvTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttVoltagePnvTest();
	}
public:

    virtual void AfterSetParameter();

    virtual long CalReport(UINT nState=0);
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();
protected:
    tmt_VoltagePnvResults m_oVoltagePnvResults;
};
