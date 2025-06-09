#pragma once

#include "GbWzdCmd.h"

class CGbWzdCmdCommCmd : public CGbWzdCmd
{
public:
	CGbWzdCmdCommCmd();
	virtual ~CGbWzdCmdCommCmd();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_COMMCMD;	} 
public:


public:
	virtual BOOL Execute(DWORD dwExecMode);
	virtual BOOL IsCmdFinish();
	virtual void GetCmdInfor(CString &strText);
};