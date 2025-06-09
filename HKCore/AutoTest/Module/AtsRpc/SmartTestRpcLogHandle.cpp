#include "stdafx.h"

#include "SmartTestRpcloghandle.h"

CSmartTestRpcLogHandle::CSmartTestRpcLogHandle()
{

}

void CSmartTestRpcLogHandle::log(int level, const char* msg)
{
	CString strMsg;
	strMsg = msg;
	CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
}
