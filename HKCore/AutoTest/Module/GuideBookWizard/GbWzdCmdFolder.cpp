#include "stdafx.h"
#include "GbWzdCmdFolder.h"


CGbWzdCmdFolder::CGbWzdCmdFolder()
{
	
}


CGbWzdCmdFolder::~CGbWzdCmdFolder()
{
	
}


BOOL CGbWzdCmdFolder::Execute(DWORD dwExecMode)
{
	CGbWzdCmd::Execute(dwExecMode);

	return FALSE;
}


BOOL CGbWzdCmdFolder::IsCmdFinish()
{
	
	return TRUE;
}

