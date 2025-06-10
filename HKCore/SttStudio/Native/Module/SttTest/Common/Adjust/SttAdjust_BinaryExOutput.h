#pragma once

#include	"../../../SttTestBase/SttTestBase.h"
#include	"tmt_adjust_test.h"
#include "../../../SttDevice/SttDeviceBase.h"

class CSttAdjust_BinaryExOutput : public CSttTestBase, public TMT_ADJ_BINARYEX_OUTPUT
{
public:
	CSttAdjust_BinaryExOutput();
	virtual ~CSttAdjust_BinaryExOutput(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

	static CSttTestBase *CreateTest()
	{
		return new CSttAdjust_BinaryExOutput;
	}

public:
	virtual void Init();
	virtual void StartTest();
	virtual long OnTimer(BOOL &bFinish, long nTimerLongMs = 500);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Stop();
private:
	long nModuleDrvIdx;
	Drv_BIStatus m_oBIStatus;

};

