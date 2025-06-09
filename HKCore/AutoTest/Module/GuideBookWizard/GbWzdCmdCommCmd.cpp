#include "stdafx.h"
#include "GbWzdCmdCommCmd.h"


CGbWzdCmdCommCmd::CGbWzdCmdCommCmd()
{
	
}


CGbWzdCmdCommCmd::~CGbWzdCmdCommCmd()
{
	
}

BOOL CGbWzdCmdCommCmd::Execute(DWORD dwExecMode)
{
	CGbWzdCmd::Execute(dwExecMode);
	return FALSE;
}


void CGbWzdCmdCommCmd::GetCmdInfor(CString &strText)
{
	CGbWzdCmd::GetCmdInfor(strText);
}

BOOL CGbWzdCmdCommCmd::IsCmdFinish()
{
	
	return TRUE;
}

