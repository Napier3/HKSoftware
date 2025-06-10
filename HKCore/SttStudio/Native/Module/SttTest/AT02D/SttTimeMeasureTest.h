#ifndef STTTIMEMEASURETEST_H
#define STTTIMEMEASURETEST_H

#include "../Common/SttStateTest.h"
#include "tmt_timemeasure_test.h"

class CSttTimeMeasureTest : public CSttTestBase,public tmt_TimeMeasureTest
{
public:
	CSttTimeMeasureTest(void);
	virtual ~CSttTimeMeasureTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttTimeMeasureTest();
	}
public:
	virtual void Init();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual BOOL EventProcess();
	virtual void TtmToDrv();
};

#endif // STTTIMEMEASURETEST_H
