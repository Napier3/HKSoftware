#pragma once

#include"../../SttTestBase/SttTestBase.h"

//…œµÁƒ¨»œ≈‰÷√
//nBand = 115200;
//nCheck = 0;
//nStopBit = 0;
//nDatalen = 8;

class CSttUartConfig:public CSttTestBase
{
public:
	CSttUartConfig();
	virtual ~CSttUartConfig(void);
	static CString m_strMacroID;
	static CString m_strMacroName;

	static CSttTestBase* CreateTest()
	{
		return new CSttUartConfig();
	}

public:
	virtual void StartTest();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
