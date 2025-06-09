#include "stdafx.h"

#include "AtsRpcClientloghandle.h"

CAtsRpcClientLogHandle::CAtsRpcClientLogHandle()
{

}

void CAtsRpcClientLogHandle::log(int level, const char* msg)
{
	CString strMsg;
	strMsg = msg;
	CLogPrint::LogString(LOGLEVEL_TRACE, strMsg);
}
