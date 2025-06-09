#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include "SttSystemConfig.h"

class CSttModulesGearSwitch:public STT_SystemParas ,public CSttTestBase
{
public:
	CSttModulesGearSwitch();
	virtual ~CSttModulesGearSwitch(void);
	static CString m_strMacroID;
	static CString m_strMacroName;

	static CSttTestBase* CreateTest()
	{
		return new CSttModulesGearSwitch();
	}

public:
	virtual void StartTest();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};

