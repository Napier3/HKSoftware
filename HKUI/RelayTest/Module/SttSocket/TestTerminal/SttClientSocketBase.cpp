#include "stdafx.h"
#include "SttClientSocketBase.h"
#include "../../Engine/SttTestEngineBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttClientSocketBase::CSttClientSocketBase()
{

}

CSttClientSocketBase::~CSttClientSocketBase()
{

}

void CSttClientSocketBase::CloseSocket()
{
	if (m_pTestEngine != NULL)
	{
		m_pTestEngine->CloseSocket(this);
	}
}