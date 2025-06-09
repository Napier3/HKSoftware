#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include "SttSystemConfig.h"


class CSttAuxDCOutput:public STT_SystemParas ,public CSttTestBase
{
public:
	CSttAuxDCOutput();
	virtual ~CSttAuxDCOutput(void);
	static CString m_strMacroID;
	static CString m_strMacroName;

	static CSttTestBase* CreateTest()
	{
		return new CSttAuxDCOutput();
	}

public:
	virtual void StartTest();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
