#ifndef STTGSETOBOTEST_H
#define STTGSETOBOTEST_H

#include"../../SttTestBase/SttTestBase.h"
#include "tmt_ied_test.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/PNI302/SttDevicePNI302.h"
#endif


class CSttGSEtoBinTest:public tmt_IEDTest,public CSttTestBase
{
public:
	CSttGSEtoBinTest(void);
	virtual ~CSttGSEtoBinTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttGSEtoBinTest();
	}
public:
	virtual void AfterSetParameter();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
	virtual void EventProcess();
	virtual void Init();
	//将上层结构体转为底层结构体
public:
	virtual void TtmToDrv();
	virtual BOOL NeedReadDeviceStatatus() {return FALSE;}
private:
	tmt_IEDPara m_oPreTmtIEDPara;
};

#endif // STTGSETOBOTEST_H
