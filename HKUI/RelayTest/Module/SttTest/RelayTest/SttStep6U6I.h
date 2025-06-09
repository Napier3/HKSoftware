#ifndef STTSTEP6U6I_H
#define STTSTEP6U6I_H

#include "tmt_harm_test.h"
#include "SttRecord.h"
#include "drv_step6u6i.h"

class CSttStep6U6I :public tmt_harm_test,public CSttTestBase
{
public:
	CSttStep6U6I(void);
	virtual ~CSttStep6U6I(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttStep6U6I();
	}
public:
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
	virtual void EventProcess();
	virtual void TtmToDrv();

private:
	CSttRecord *m_pCSttRecord;
#ifdef _PSX_QT_LINUX_
	structManuData m_oManuData;
#endif
	bool m_Start;
};

#endif // STTTIMEMEASURETEST_H
