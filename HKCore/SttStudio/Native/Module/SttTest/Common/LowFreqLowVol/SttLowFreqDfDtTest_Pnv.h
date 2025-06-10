#pragma once

#include "SttLowFreqDfDtTest.h"


class CSttLowFreqDfDtPnvTest : public CSttLowFreqDfDtTest
{
public:
    CSttLowFreqDfDtPnvTest();
    virtual ~CSttLowFreqDfDtPnvTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttLowFreqDfDtPnvTest();
	}
public:

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数
};
