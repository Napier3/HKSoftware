#ifndef STTIEDTEST_H
#define STTIEDTEST_H

#include"../../SttTestBase/SttTestBase.h"
#include "tmt_ied_test.h"
#ifdef OS_QT_LINUX
#include "../../SttDevice/SttDeviceBase.h"
#endif
#include "QThread"
#include "../../../Module/Socket/Qt/WinTcpSocket.h"
#include "QTime"


class CSttIEDTest:public tmt_IEDTest,public CSttTestBase
{
public:
	CSttIEDTest(void);
	virtual ~CSttIEDTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttIEDTest();
	}
public:
	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
	virtual void EventProcess();	
	//将上层结构体转为底层结构体
public:
	virtual void TtmToDrv();

private:
	char *m_pszBuff;	
};

#endif // STTRECORD_H
