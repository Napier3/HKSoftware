#pragma once

#include "../../SttManuTest.h"
#include "../tmt_diff_curr_test.h"
#include "../../../../SttTestBase/SttDiffCurrCalculatTool.h"


class CSttManuDiffCurrThrTest : public CSttManuTest ,public tmt_DiffCurrParas
{
public:
    CSttManuDiffCurrThrTest();
    virtual ~CSttManuDiffCurrThrTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttManuDiffCurrThrTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);

public:
    virtual void Init();
    virtual void StartTest();
    virtual void Stop();
	virtual long SetParameter(DWORD dwState=0);
	void SetResultValues_I1IeI2Ie();

protected:
	virtual void TranslateToStateParas();
	void InitManuDiffParas_6U6I();//在此函数中初始化电压值及电流频率等参数
	tmt_DiffCurrResults m_oResults;
	CSttDiffCurrCalculatTool m_oDiffCalTool;
};
