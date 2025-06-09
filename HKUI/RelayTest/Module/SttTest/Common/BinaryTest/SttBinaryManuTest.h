#pragma once


#include"tmt_binary_manu_test.h"
#include"../../../SttTestBase/SttTestBase.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/Module/Driver466/SttDeviceComm.h"
#endif

class CSttBinaryManuTest : public CSttTestBase
{
public:
	CSttBinaryManuTest();
	virtual ~CSttBinaryManuTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
		return new CSttBinaryManuTest();
	}
public:  
    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

	tmt_ManualTest *m_pManualTest;
public:
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);	
	virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual BOOL EventProcess();

public:
	virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	virtual void StartTest();

    //将上层结构体转为底层结构体
public:
    virtual void TtmToDrv();
};




