#pragma once

#include "SttImpBaseTest.h"
#include "tmt_zero_current_test.h"


class CSttZeroCurrentTest : public CSttImpBaseTest ,public tmt_ZeroCurrentParas
{
public:
    CSttZeroCurrentTest();
    virtual ~CSttZeroCurrentTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttZeroCurrentTest();
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

	tmt_ZeroCurrentResults m_oResults;
};
