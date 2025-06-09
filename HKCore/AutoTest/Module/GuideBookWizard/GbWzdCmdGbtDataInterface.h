#pragma once

#include "GbWzdCmd.h"

class CGbWzdCmdGbtDataInterface : public CGbWzdCmd
{
public:
	CGbWzdCmdGbtDataInterface();
	virtual ~CGbWzdCmdGbtDataInterface();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_GBTDATAINTERFACE;	} 
public:


public:
	virtual BOOL Execute(DWORD dwExecMode);
	virtual BOOL IsCmdFinish();
	virtual void GetCmdInfor(CString &strText);
};