// EpProcedure104ToModbus.h: interface for the CEpProcedure104ToModbus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPROCEDURE104TOMODBUS_H__)
#define _EPPROCEDURE104TOMODBUS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpProcedure.h"

class CEpProcedure104ToModbus : public CEpProcedure
{
public:
	CEpProcedure104ToModbus();
	virtual ~CEpProcedure104ToModbus();

public:
	
public:
	//��������
	virtual void Init()	{}
	virtual UINT GetClassID()		{ return EPCLASSID_PROCEDURE; }

	//ִ��
	virtual void RunInitScript() {}
	virtual void RunEndScript() {}
	virtual DWORD Run();
	virtual DWORD Process(CEpFrameBase *pFrame);
	virtual BOOL IsProcedureExit();
	virtual void CopyDataInterfaceToFrame();
};

#endif // !defined(_EPPROCEDURE104TOMODBUS_H__)
