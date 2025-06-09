#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include"tmt_adjust_test.h"

class CSttAdjust_BinaryOutput : public CSttTestBase, public TMT_ADJ_BINARY_OUTPUT
{
public:
	CSttAdjust_BinaryOutput();
	virtual ~CSttAdjust_BinaryOutput(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
		return new CSttAdjust_BinaryOutput();
    }

public:
    virtual void Init();
    virtual void StartTest();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Stop();

};

