#pragma once

#include "GbWzdCmd.h"

class CGbWzdCmdFolder : public CGbWzdCmd
{
public:
	CGbWzdCmdFolder();
	virtual ~CGbWzdCmdFolder();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_FOLDER;	} 
public:


public:
	virtual BOOL Execute(DWORD dwExecMode);
	virtual BOOL IsCmdFinish();
};