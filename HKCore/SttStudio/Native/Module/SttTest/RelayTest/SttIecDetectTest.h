#ifndef STTIECDETECTTEST_H
#define STTIECDETECTTEST_H

#include"../../SttTestBase/SttTestBase.h"
#include "tmt_record.h"

#ifdef OS_QT_LINUX
#include "drv_record.h"
#include "../../SttDevice/SttDeviceBase.h"
#include "QThread"
#include "../../../Module/Socket/Qt/WinTcpSocket.h"
#include "QTime"
#endif


class CSttIecDetectTest:public tmt_RecordTest,public CSttTestBase
{
public:
	CSttIecDetectTest(void);
	virtual ~CSttIecDetectTest(void);
#ifdef OS_QT_LINUX
	GooseSubData       m_oDrvGooseSubData;
#endif
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
	virtual void EventProcess();	
	virtual CSttParas *GetCurrParas();
	//将上层结构体转为底层结构体
public:
	virtual void TtmToDrv();

private:
	char *m_pszBuff;	
};

#endif // STTRECORD_H
