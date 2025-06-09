#pragma once

#include"../../SttTestBase/SttTestBase.h"

class CSttBinConfig:public CSttTestBase
{
public:
	CSttBinConfig();
	virtual ~CSttBinConfig(void);
	static CString m_strMacroID;
	static CString m_strMacroName;

	static CSttTestBase* CreateTest()
	{
		return new CSttBinConfig();
	}
public:
	virtual void StartTest();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
