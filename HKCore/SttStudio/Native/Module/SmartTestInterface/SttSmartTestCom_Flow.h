#pragma once

#include "SttSmartTestCom.h"

//2021-7-27   lijunqing 由  CDynDialogEx  改为 CWnd，简化基类的引用
//2021-8-3  lijunqing 总的接口CXSttSmartTestXInterface，方便访问
class CSttSmartTestCom_Flow : public CSttSmartTestCom
{
	DECLARE_DYNCREATE(CSttSmartTestCom_Flow)

public:
	static CSttSmartTestCom_Flow * CreateSmartTest()
	{
		CSttSmartTestCom_Flow *pSttSmartTestCom_Flow = new CSttSmartTestCom_Flow();
		pSttSmartTestCom_Flow->CreateWnd();
		pSttSmartTestCom_Flow->ShowWindow(SW_HIDE);
		return pSttSmartTestCom_Flow;
	}

public:
    CSttSmartTestCom_Flow();
    virtual ~CSttSmartTestCom_Flow();

public:
	//以下函数，返回0表示成功，返回非零值表示失败
    virtual long Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_ConfigTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);

public:

public:

};
