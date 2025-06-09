#pragma once


#include "../../../AutoTest/Module/TestControl/TestControlBase.h"

class CSttNativeTestCltlCntr: public CTestControlBase
{
public:
     CSttNativeTestCltlCntr();
    virtual ~CSttNativeTestCltlCntr();

public:
	//����ͨѶ��Լ�������
	virtual void CreatePpEngineDevice(CProtocolEngineInterface *pEngine, CPpDeviceRef *pDevieceRef);
	virtual BOOL CreatePpEngineDevice(CCommCmd *pCmd);

	virtual long TestItemSafety(CSafety* pItem);
	virtual long TestItemSysParaEdit(CSysParaEdit* pItem);

};
