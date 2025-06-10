#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include "SttSystemConfig.h"


class CSttAppRatesConfig:public STT_SystemParas
{
public:
	CSttAppRatesConfig();
	virtual ~CSttAppRatesConfig(void);
	static CString m_strMacroID;
	static CString m_strMacroName;

public:
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};

extern CSttAppRatesConfig g_theAppRatesConfig;
