#include "stdafx.h"
#include "SttMqttCmdExecBase.h"
#include "..\..\Module\System\TickCount32.h"

CSttMqttCmdExecBase::CSttMqttCmdExecBase()
{
	
}

CSttMqttCmdExecBase::~CSttMqttCmdExecBase()
{
	
}



//////////////////////////////////////

CString GetIDFromPath(const CString &strPath,char chSeperator)
{
	CString strID;
	long nPos = strPath.ReverseFind(chSeperator);
	if (nPos >= 0)
	{
		strID = strPath.Mid(nPos + 1);
	}
	else
	{
		strID = strPath;
	}

	return strID;
}