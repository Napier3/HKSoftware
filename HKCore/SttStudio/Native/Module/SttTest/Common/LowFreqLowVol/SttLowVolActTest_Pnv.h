#pragma once

#include "../SttStateTest.h"
#include "SttLowVolActTest.h"


class CSttLowVolActPnvTest : public CSttLowVolActTest
{
public:
    CSttLowVolActPnvTest();
    virtual ~CSttLowVolActPnvTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttLowVolActPnvTest();
	}
public:

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
    virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数
};
