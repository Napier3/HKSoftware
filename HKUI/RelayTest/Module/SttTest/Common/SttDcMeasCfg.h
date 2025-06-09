#pragma once

#include"../../SttTestBase/SttTestBase.h"

class CSttDcMeasCfg:public CSttTestBase
{
public:
	CSttDcMeasCfg();
	virtual ~CSttDcMeasCfg(void);
	static CString m_strMacroID;
	static CString m_strMacroName;

	static CSttTestBase* CreateTest()
	{
		return new CSttDcMeasCfg();
	}
public:
	virtual void StartTest();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	unsigned int m_nDCInGear_I;//主板直流测量电流档位,0-大，1-小
};

extern CSttDcMeasCfg g_oDcMeasCfg;
