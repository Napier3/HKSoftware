#pragma once

#include "../../SttStateTest.h"
#include "tmt_bp2_diff_test.h"
#include "../../../../SttTestBase/SttDiffCurrCalculatTool.h"


class CSttBP2DiffThrTest : public CSttStateTest ,public tmt_BP2DiffParas
{
public:
    CSttBP2DiffThrTest();
    virtual ~CSttBP2DiffThrTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttBP2DiffThrTest();
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
	void SetResultValues_I1I2();

protected:
	virtual void TranslateToStateParas();
	void SetStatePreFault_3U3I();//在此函数中设置故障前电压电流、开入开出等,并设置故障态电压值
	tmt_BP2DiffResults m_oResults;
	CSttDiffCurrCalculatTool m_oDiffCalTool;
};
