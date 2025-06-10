#pragma once

#include"../../SttTestBase/SttTestBase.h"

class CSttLcPowerTest: public CSttTestBase
{
public:
	CSttLcPowerTest();
	virtual ~CSttLcPowerTest(void);
	static CString m_strMacroID;
	static CString m_strMacroName;

	static CSttTestBase* CreateTest()
	{
		return new CSttLcPowerTest();
	}

public:
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
