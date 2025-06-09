#include "stdafx.h"
#include "GbWzdCmdGbtDataInterface.h"


CGbWzdCmdGbtDataInterface::CGbWzdCmdGbtDataInterface()
{
	
}


CGbWzdCmdGbtDataInterface::~CGbWzdCmdGbtDataInterface()
{
	
}


BOOL CGbWzdCmdGbtDataInterface::Execute(DWORD dwExecMode)
{
	CGbWzdCmd::Execute(dwExecMode);
	return FALSE;
}


void CGbWzdCmdGbtDataInterface::GetCmdInfor(CString &strText)
{
	CGbWzdCmd::GetCmdInfor(strText);
}

BOOL CGbWzdCmdGbtDataInterface::IsCmdFinish()
{
	
	return TRUE;
}

