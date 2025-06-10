#ifndef STTBOTOGSETEST_H
#define STTBOTOGSETEST_H

#include"../../SttTestBase/SttTestBase.h"
#include "tmt_ied_test.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#include "../Common/SttRecord.h"
#endif



class CSttBOtoGSETest:public tmt_IEDTest,public CSttTestBase
{
public:
	CSttBOtoGSETest(void);
	virtual ~CSttBOtoGSETest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttBOtoGSETest();
	}
public:
	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
	virtual void Init();
	virtual void EventProcess();	
	virtual bool NeedCheckHeartbeat()	{	return false;		}

	//将上层结构体转为底层结构体
public:
	virtual void TtmToDrv();
	virtual BOOL NeedReadDeviceStatatus() {return FALSE;}
private:	
	CSttRecord *m_pCSttRecord;
	tmt_IEDPara m_oPreTmtIEDPara;
};

#endif // STTBOTOGSETEST_H
