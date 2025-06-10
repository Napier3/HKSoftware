#pragma once

#include "SttOverCurrentTest.h"


class CSttStateOverCurrentTest : public CSttOverCurrentTest
{
public:
    CSttStateOverCurrentTest();
    virtual ~CSttStateOverCurrentTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttStateOverCurrentTest();
	}

public:
	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Init();

protected:
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数
};
