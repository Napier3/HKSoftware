#pragma once

#include "../SttStateTest.h"
#include "tmt_dc_differ_test.h"
#include "../../../SttTestBase/SttDiffCurrCalculatTool.h"


class CSttDCDiffCurrThrTest : public CSttStateTest ,public tmt_DcDifferCurParas
{
public:
    CSttDCDiffCurrThrTest();
    virtual ~CSttDCDiffCurrThrTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDCDiffCurrThrTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
	virtual void ReturnTestStateEvent_SearchPoint(double dTime, double dRealTime, bool bWithEvent);
	virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	void SetResultValues_I1IeI2Ie();

protected:
	virtual void TranslateToStateParas();
	void SetStatePreFault_6U6I();//在此函数中设置故障前电压电流、开入开出等,并设置故障态电压值
//	BOOL ActProcess();
    tmt_DcDifferCurResults m_oResults;
	CSttDiffCurrCalculatTool m_oDiffCalTool;
};
