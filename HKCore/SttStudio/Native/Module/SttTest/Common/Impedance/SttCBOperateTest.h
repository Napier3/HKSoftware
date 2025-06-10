#pragma once

#include "SttImpBaseTest.h"
#include "tmt_cb_operate_test.h"

class CSttCBOperateTest : public CSttImpBaseTest ,public tmt_CBOperateParas
{
public:
    CSttCBOperateTest();
    virtual ~CSttCBOperateTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttCBOperateTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);

protected:
	 virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数
	 void TranslateToStateParas_TimeCtrl_NotTrans();
	 void TranslateToStateParas_TimeCtrl_Trans();
private:
	tmt_CBOperateResults m_oResults;
};
