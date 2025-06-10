#pragma once

#include "SttRecloseAccTest.h"

class CSttStateRecloseAccTest : public CSttRecloseAccTest
{
public:
    CSttStateRecloseAccTest();
    virtual ~CSttStateRecloseAccTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttStateRecloseAccTest();
	}
public:

    virtual void AfterSetParameter();
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

};
