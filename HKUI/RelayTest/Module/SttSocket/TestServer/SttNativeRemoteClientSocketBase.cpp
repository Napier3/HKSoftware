#include "stdafx.h"
#include "SttNativeRemoteClientSocketBase.h"
#include "../../Engine/SttTestEngineBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttNativeRemoteClientSocketBase::CSttNativeRemoteClientSocketBase()
{

}

CSttNativeRemoteClientSocketBase::~CSttNativeRemoteClientSocketBase()
{

}

void CSttNativeRemoteClientSocketBase::OnSocketClose(int nErrorCode)
{
	return m_pTestEngine->OnSocketClose(this);
}