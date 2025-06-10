#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include"tmt_shake_test.h"

#ifdef _PSX_IDE_QT_
#include"drv_shake_test.h"
#include "drv_abnormal_test.h"
#include "../../SttDevice/RelayTest/SttDevice.h"
#endif

#include "../../SttDevice/RelayTest/drv_define.h"

class CSttShakeTest : public CSttTestBase, public tmt_ShakeTest
{
public:
    CSttShakeTest();
    virtual ~CSttShakeTest(void);

#ifdef _PSX_IDE_QT_
	drv_shake_test       m_oDrvShakeData;
#endif
 //   drv_resultitems  m_oDrvResults;

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttShakeTest();
	}
public:

	//过程参数
	Complex *m_CmpUI[2][MAX_VOLTAGE_COUNT];

    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();
	virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);

     virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();

	virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual void EventProcess();
	virtual void Stop();

    //将上层结构体转为底层结构体
public:
    virtual void TtmToDrv();

private:
    int m_nOut;
	void sendRealOutPut(structResult oItem);
	void sendRealDataChanged(structResult oItem);
};
