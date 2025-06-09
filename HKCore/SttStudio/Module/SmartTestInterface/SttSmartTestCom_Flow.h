#pragma once

#include "SttSmartTestCom.h"

//2021-7-27   lijunqing ��  CDynDialogEx  ��Ϊ CWnd���򻯻��������
//2021-8-3  lijunqing �ܵĽӿ�CXSttSmartTestXInterface���������
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
	//���º���������0��ʾ�ɹ������ط���ֵ��ʾʧ��
    virtual long Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_ConfigTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);

public:

public:

};
