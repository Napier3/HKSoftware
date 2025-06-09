#ifndef STTRECORD_H
#define STTRECORD_H

#include"../../SttTestBase/SttTestBase.h"
#include "tmt_record.h"
#ifdef _PSX_IDE_QT_
#include "../../SttDevice/SttDeviceBase.h"
#endif
#include "QThread"
#include "QTime"

class CSttRecord:public tmt_RecordTest,public CSttTestBase
{
public:
	CSttRecord(void);
	virtual ~CSttRecord(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttRecord();
	}
public:
	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
	virtual void Init();
	virtual BOOL EventProcess();
	virtual long OnTimer(BOOL &bFinish, long nTimerLongMs=500);
	virtual BOOL NeedReadDeviceStatatus() {return FALSE;}
	//将上层结构体转为底层结构体
public:
	virtual void TtmToDrv();
	virtual bool NeedCheckHeartbeat()	{	return false;		}

};

#endif // STTRECORD_H
