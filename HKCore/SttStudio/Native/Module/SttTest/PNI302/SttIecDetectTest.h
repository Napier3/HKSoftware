#ifndef STTIECDETECTTEST_H
#define STTIECDETECTTEST_H

#include"../../SttTestBase/SttTestBase.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/PNI302/SttDevicePNI302.h"
#endif


class CSttIecDetectTest:public tmt_RecordTest,public CSttTestBase
{
public:
	CSttIecDetectTest(void);
	virtual ~CSttIecDetectTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttIecDetectTest();
	}
public:
	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
	virtual void Init();
	virtual void EventProcess();
	virtual BOOL NeedReadDeviceStatatus() {return FALSE;}
};

#endif // STTRECORD_H
