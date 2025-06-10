#pragma once

#define USE_SttImpBaseTest

#include "../SttManuTest.h"
#include "tmt_manuImped_test.h"

class CSttManuaImpedTest : public CSttManuTest ,public tmt_ManualImpedParas

{
public:
    CSttManuaImpedTest();
    virtual ~CSttManuaImpedTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttManuaImpedTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType);
	virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex);
	virtual void SyncGradientResult(int nStep, double dTime, int nTripType);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	virtual void TtmToDrv();

protected:
	void Global_FaultCalculatUI(tmt_ManualImpedParas *pManualImpParas,Complex *pVol_Complex,Complex *pCur_Complex);
	void Global_SetStateUIFromCpl(tmt_ManualParas *pManualPara,Complex *pVol_Complex,Complex *pCur_Complex);
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数
    tmt_ManualImpedResult m_oManualImpedResults;
	tmt_GradientParas m_oGradientParas;
};
