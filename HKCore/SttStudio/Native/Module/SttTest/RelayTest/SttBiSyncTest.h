#ifndef STTBISYNCTEST_H
#define STTBISYNCTEST_H

#include "SttStateTest.h"
#include "tmt_bisync_test.h"

class CSttBiSyncTest : public CSttStateTest,public tmt_BiSyncTest
{
public:
	CSttBiSyncTest(void);
	virtual ~CSttBiSyncTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttBiSyncTest();
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
};

#endif // STTBISYNCTEST_H
