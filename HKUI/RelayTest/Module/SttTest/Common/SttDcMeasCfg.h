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
	unsigned int m_nDCInGear_I;//����ֱ������������λ,0-��1-С
};

extern CSttDcMeasCfg g_oDcMeasCfg;
