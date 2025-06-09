#include "stdafx.h"

#include "SttCloudServerSocketBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttCloudServerSocketBase *g_pSttCloudSvrSocket = NULL;

CSttCloudServerSocketBase::CSttCloudServerSocketBase()
{
	g_pSttCloudSvrSocket = this;
}

CSttCloudServerSocketBase::~CSttCloudServerSocketBase()
{

}

BOOL CSttCloudServerSocketBase::Bind(CSttCloudServerClientSocketBase *pSocket, const CString &strCode_Register,DWORD nIDTester)
{
	BOOL bRet = FALSE;

	CSttCloudServerClientSocketBase *pRegisterSocket = FindByRegisterCode(strCode_Register);
	if (pRegisterSocket != NULL)
	{
		{
			CAutoSimpleLock oLock(m_oClientSocketMngrLock);
			Remove(pSocket);	
		}

		pRegisterSocket->AddBindSocket(pSocket,nIDTester);

		bRet = TRUE;
	}
	
	return bRet;
}

void CSttCloudServerSocketBase::OnSttScktClose(CSttSocketDataBase_File *pSttSckt)
{
	CAutoSimpleLock oLock(m_oClientSocketMngrLock);
	Delete(pSttSckt);
}

CSttCloudServerClientSocketBase *CSttCloudServerSocketBase::FindByRegisterCode(const CString &strCode_Register)
{
	POS pos = GetHeadPosition();
	CSttCloudServerClientSocketBase *pFind = NULL;

	while (pos != NULL)
	{
		pFind = (CSttCloudServerClientSocketBase *)GetNext(pos);

		if (pFind->m_strCode_Register == strCode_Register)
		{
			return pFind;
		}
	}

	return NULL;
}

BOOL CSttCloudServerSocketBase::HasRegisteredByTestApp(const CString &strSN_TestApp)
{
	POS pos = GetHeadPosition();
	CSttCloudServerClientSocketBase *pFind = NULL;

	while (pos != NULL)
	{
		pFind = (CSttCloudServerClientSocketBase *)GetNext(pos);

		if (pFind->m_strSN_TestApp == strSN_TestApp)
		{
			return TRUE;
		}
	}

	return FALSE;
}

// void CSttCloudServerSocketBase::OnCloseNativeSocket(CSttSocketDataBase *pSocket)
// {
// 
// }

void CSttCloudServerSocketBase::OnSttSktAccept(CSttSocketDataBase *pSttSkt)
{
	CAutoSimpleLock oLock(m_oClientSocketMngrLock);
	AddNewChild(pSttSkt);
}