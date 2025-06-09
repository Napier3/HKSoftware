#pragma once

#include "../SttStateTest.h"
#include "tmt_state_diff_coef_pnv_test.h"

class CSttDiffCoefPnvTest : public CSttStateTest ,public tmt_DiffCoefPnvParas
{
public:
    CSttDiffCoefPnvTest();
    virtual ~CSttDiffCoefPnvTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDiffCoefPnvTest();
	}
public:

    virtual void AfterSetParameter();

    virtual long CalReport(UINT nState=0);
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();
    void uiRampCh(tmt_channel *m_uiRamp);
protected:
    tmt_DiffCoefPnvResults m_oDiffCoefPnvResults;
};

enum StateRampPnv{
    StateRampPnvUa,
    StateRampPnvUb,
    StateRampPnvUc,
    StateRampPnvUabc,
    StateRampPnvUap,
    StateRampPnvUbp,
    StateRampPnvUcp,
    StateRampPnvUabcp,
    StateRampPnvIa,
    StateRampPnvIb,
    StateRampPnvIc,
    StateRampPnvIabc,
    StateRampPnvIap,
    StateRampPnvIbp,
    StateRampPnvIcp,
    StateRampPnvIabcp,
};
