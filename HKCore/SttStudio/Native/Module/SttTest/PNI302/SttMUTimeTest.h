#ifndef STTMUTIMETEST_H
#define STTMUTIMETEST_H

#include"../../SttTestBase/SttTestBase.h"
#include "tmt_mutime_test.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif
#include "QThread"
#include "../../../Module/Socket/Qt/WinTcpSocket.h"
#include "QTime"

class MUThread : public QThread,public CSttTestBase
{
public:
	MUThread();
	~MUThread();
	 void run();
	 void setCount(int nCount){m_nCount=nCount;}
	 void setRun(BOOL bState){m_bRun=bState;}
	 BOOL getRun(){ return m_bRun;}
private:
	 int m_nCount;
	 BOOL m_bRun;
};

class CSttMUTimeTest:public tmt_mutime_test,public CSttTestBase
{
public:
	CSttMUTimeTest(void);
	virtual ~CSttMUTimeTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttMUTimeTest();
	}
public:
	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
	virtual void Init();
	//将上层结构体转为底层结构体
public:
	virtual void TtmToDrv();

private:	
	MUThread *m_pMUThread;
};

#endif // STTRECORD_H
