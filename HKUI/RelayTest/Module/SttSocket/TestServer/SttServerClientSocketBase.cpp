#include "stdafx.h"
#include "SttServerClientSocketBase.h"
#include "../../Engine/SttTestEngineBase.h"
//#include "../../Engine/SttTestServerBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttServerClientSocketBase::CSttServerClientSocketBase()
{

}

CSttServerClientSocketBase::~CSttServerClientSocketBase()
{

}

void CSttServerClientSocketBase::OnSocketClose(int nErrorCode, BOOL bDeleteSocket)
{
	if(m_pTestEngine != NULL)
	{
		m_pTestEngine->OnSocketClose(this, bDeleteSocket);
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("nErrorCode=%d[CSttServerClientSocketBase::OnSocketClose]."),nErrorCode);
	} 
}
