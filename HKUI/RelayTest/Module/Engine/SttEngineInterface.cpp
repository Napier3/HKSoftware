#include "stdafx.h"
#include "SttEngineInterface.h"

//////////////////////////////////////////////////////////////////////////
CSttEngineInterface::CSttEngineInterface()
{
	m_pPxCmmOptrInterface = NULL;
	m_bConnected = FALSE;	

	m_pszXmlBuffer = NULL;
	m_nXmlBufferLen = 0;
	SetXmlBufferLen(64000); //1M
}

CSttEngineInterface::~CSttEngineInterface()
{
	FreePxCmmInterface();

	if (m_pszXmlBuffer != NULL)
	{
		delete m_pszXmlBuffer;
		m_pszXmlBuffer = NULL;
	}
}

void CSttEngineInterface::SetXmlBufferLen(long nLen)
{
	if (nLen <= m_nXmlBufferLen)
	{
		return;
	}

	if (m_pszXmlBuffer != NULL)
	{
		delete m_pszXmlBuffer;
		m_pszXmlBuffer = NULL;
	}

	m_pszXmlBuffer = new char [nLen+10];
	m_nXmlBufferLen = nLen;
}

void CSttEngineInterface::BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat)
{
	ASSERT(FALSE);
}


long CSttEngineInterface::OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN, char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	return 0;
}

//mqtt断链
void CSttEngineInterface::OnClose(char *pszErr)
{
	FreePxCmmInterface();
}

long CSttEngineInterface::Send(const CString &strToSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	if (m_pPxCmmOptrInterface == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_pPxCmmInterface == NULL"));
		return -1;
	}

	return m_pPxCmmOptrInterface->Send(strToSN, pBuf,nLen,nCmdType,pszCmdID,pszRetType,pszEventID);
}

long CSttEngineInterface::Send(CExBaseObject *pCmdBase)
{
	if (m_pPxCmmOptrInterface == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_pPxCmmInterface == NULL"));
		return -1;
	}

	return m_pPxCmmOptrInterface->Send(pCmdBase);
}

BOOL CSttEngineInterface::Connect(const char *pszIP,long nPort)
{
	m_bConnected = FALSE;

	if (m_pPxCmmOptrInterface != NULL)
	{
		m_bConnected = m_pPxCmmOptrInterface->Connect(pszIP,nPort, NULL);
	}

	return m_bConnected;
}

void CSttEngineInterface::Disconnect()
{
	m_bConnected = FALSE;

	if (m_pPxCmmOptrInterface != NULL)
	{
		m_pPxCmmOptrInterface->Disconnect();
	}
}
