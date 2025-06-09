#pragma once

#include"../../../SttTestBase/SttTestBase.h"
#include"tmt_adjust_test.h"

class CSttAdjust_RegisterTest : public CSttTestBase, public TMT_ADJ_REGISTER_OUTPUT
{
public:
	CSttAdjust_RegisterTest();
	virtual ~CSttAdjust_RegisterTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
		return new CSttAdjust_RegisterTest();
    }

public:
	virtual void Init();
	virtual void StartTest();
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};

