#ifndef STTTIMEMEASURETEST_H
#define STTTIMEMEASURETEST_H

#include "SttStateTest.h"
#include "tmt_timemeasure_test.h"

class CSttTimeMeasureTest : public CSttStateTest,public tmt_TimeMeasureTest
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
	virtual void Init(long nStateNums);
	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void EventProcess();
	virtual void TtmToDrv();

private:
	unsigned int nPreBinVal;
	char *m_pszResultBuff;
	char *m_pszBuff;
};

#endif // STTTIMEMEASURETEST_H
