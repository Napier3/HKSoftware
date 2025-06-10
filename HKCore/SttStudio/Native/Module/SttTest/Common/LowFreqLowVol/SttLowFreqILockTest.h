#pragma once

#include "SttLowFreqActTest.h"


class CSttLowFreqILockTest : public CSttLowFreqActTest
{
public:
    CSttLowFreqILockTest();
    virtual ~CSttLowFreqILockTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttLowFreqILockTest();
	}
public:

	virtual void Init();
	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual BOOL IsGradientFinished();

protected:
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数
};
