#pragma once

#include "tmt_system_config.h"

class CSttDevSystemParas:public STT_SystemParas
{
public:
	CSttDevSystemParas();
	virtual ~CSttDevSystemParas(void);
	static CString m_strMacroID;
	static CString m_strMacroName;

public:
	void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};

extern CSttDevSystemParas *g_theSystemConfig;
