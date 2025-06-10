#ifndef STTSTEP6U6I_H
#define STTSTEP6U6I_H

#include "../Common/SttRecord.h"

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
	virtual void Init();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
	virtual void EventProcess();
	virtual void TtmToDrv();
	virtual bool NeedCheckHeartbeat()	{	return false;		}

private:
	CSttRecord *m_pCSttRecord;
};

#endif // STTTIMEMEASURETEST_H
