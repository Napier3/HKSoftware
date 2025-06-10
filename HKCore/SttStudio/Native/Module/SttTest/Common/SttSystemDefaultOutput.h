#pragma once

#include"../../SttTestBase/SttComplexp.h"
#include "../../SttTestBase/SttXmlSerializeBase.h"
#include"tmt_common_def.h"

class CSttSystemDefaultOutput:public TMT_SYSTEM_DEFAULT_OUTPUT_PARAS
{
public:
	CSttSystemDefaultOutput();
	virtual ~CSttSystemDefaultOutput(void);
	static CString m_strMacroID;
	static CString m_strMacroName;

public:
	void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	void StartTest();
	void StopTest();
};

extern CSttSystemDefaultOutput g_theSystemDefaultOutput;
