#include "StdAfx.h"
#include "XUserTcpClient.h"
#include "..\Sentinel LDK\SentinelLDKInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXUserTcpClientBase::CXUserTcpClientBase(void)
{
	ZeroMemory(m_byteReceiveBuffer, XUSER_TCP_BUFFERLEN);
	ZeroMemory(m_byteSendBuffer, XUSER_TCP_BUFFERLEN);
	ZeroMemory(m_xdecrypt_buffer, 8192);
	m_nFullReceiveBufferLen = 0;

	m_bIsTcpConnectSucc = FALSE;
	m_pMsgRcvWnd = NULL;
	m_pRcvCmdData = new CDvmData();
	m_nFullReceiveBufferLen_Send = 0;
}

CXUserTcpClientBase::~CXUserTcpClientBase(void)
{
	delete m_pRcvCmdData;
}

BOOL CXUserTcpClientBase::IsTcpConnectSucc()
{
	return m_bIsTcpConnectSucc;
}

BOOL CXUserTcpClientBase::IsSendCmdFinished()
{
#ifdef _DVM_VALUE_USE_CHAR_
	return (wcslen(m_oSendCmd.m_strValue) > 0);
#else
	return (m_oSendCmd.m_strValue.GetLength() > 0);
#endif
}

long CXUserTcpClientBase::GetSendCmdResult()
{
#ifdef _DVM_VALUE_USE_CHAR_
	if (wcslen(m_oSendCmd.m_strValue) > 0)
	{
		return m_oSendCmd.ValueToLong();
	}
#else
	if (m_oSendCmd.m_strValue.GetLength() > 0)
	{
		return CString_To_long(m_oSendCmd.m_strValue);
	}
#endif
	else
	{
		return -1;
	}
}

void CXUserTcpClientBase::SetMsgRcvWnd(CWnd *pMsgRcvWnd)
{
	m_pMsgRcvWnd = pMsgRcvWnd;
}

long CXUserTcpClientBase::XEncrypt(const CString &strText, char *pszBuffer)
{
	char *pText = NULL;
	long nLen = CString_to_char(strText, &pText);

	ValueToHex((const BYTE*)pText, nLen, pszBuffer);

	delete pText;

	long nRet = strlen(pszBuffer);
	return nRet;
}

long CXUserTcpClientBase::XDecrypt(char *strSrcText, CString &strDest)
{
	long nLen = HexToValue((const char*)strSrcText, (BYTE*)m_xdecrypt_buffer);
	ASSERT (nLen <= 8192);
	m_xdecrypt_buffer[nLen] = 0;

	strDest = m_xdecrypt_buffer;
	return nLen;
}

void CXUserTcpClientBase::OnReceive(int nErrorCode)
{
	BYTE *pTemp = m_byteReceiveBuffer;
	long nRcvLen = Receive(pTemp, XUSER_TCP_BUFFERLEN); //Get the whole thing
	long nXDecryptLen = 0;
	CSocket::OnReceive(nErrorCode);

	if (nRcvLen < 3)
	{
		return;
	}

	CString strXml;

	if (m_byteReceiveBuffer[0] == '$' && m_byteReceiveBuffer[1] == '$'
		&& m_byteReceiveBuffer[6] == '$' && m_byteReceiveBuffer[7] == '$')
	{
		long nSendLen = *((long*)&m_byteReceiveBuffer[2]);

		if (nSendLen+8 == nRcvLen)
		{//数据接受完毕
			m_byteReceiveBuffer[nRcvLen] = 0;
			OnReceive_Cmd((char*)(&m_byteReceiveBuffer[8]), nSendLen);
		}
		else
		{
			m_nFullReceiveBufferLen = 0;
			m_nFullReceiveBufferLen_Send = nSendLen;
			memcpy(m_byteFullReceiveBuffer+m_nFullReceiveBufferLen, m_byteReceiveBuffer+8, nRcvLen);
			m_nFullReceiveBufferLen += nRcvLen-8;
			m_byteReceiveBuffer[m_nFullReceiveBufferLen] = 0;
		}
	}
	else
	{
		memcpy(m_byteFullReceiveBuffer+m_nFullReceiveBufferLen, m_byteReceiveBuffer, nRcvLen);
		m_nFullReceiveBufferLen += nRcvLen;
		m_byteReceiveBuffer[m_nFullReceiveBufferLen] = 0;

		if (m_nFullReceiveBufferLen+8 == m_nFullReceiveBufferLen_Send)
		{
			OnReceive_Cmd((char*)m_byteFullReceiveBuffer, m_nFullReceiveBufferLen);
			m_nFullReceiveBufferLen = 0;
		}
	}

}

void CXUserTcpClientBase::OnReceive_Cmd(char *pBuffer, long nLen)
{
	//CString strXml;
	//long nXDecryptLen = XDecrypt(pBuffer, strXml);
	//strXml = pBuffer;

	m_pRcvCmdData->DeleteAll();
	BSTR bstrData = _bstr_t(pBuffer);//::SysAllocString(pBuffer, nLen);
	BOOL bTrue = m_pRcvCmdData->SetXml(bstrData, CDataMngrXmlRWKeys::g_pXmlKeys);
	::SysFreeString(bstrData);

	if (bTrue)
	{
		ProcessXUserCmd(m_pRcvCmdData);
		m_nFullReceiveBufferLen = 0;
	}
}

BOOL CXUserTcpClientBase::ProcessXUserCmd(CDvmData *pData)
{
	return FALSE;
}


BOOL CXUserTcpClientBase::SendXUserCmd(CDvmData *pData)
{
	CString strCmd;
	pData->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strCmd);

	return SendXUserCmd(strCmd);
}

BOOL CXUserTcpClientBase::SendXUserCmd(const CString &strCmd)
{
	char *pBegin = (char*)(&m_byteSendBuffer[8]);
	//long nLen = XEncrypt(strCmd, pBegin);
	long nLen = CString_to_char(strCmd, pBegin);
	
	m_byteSendBuffer[0]='$';
	m_byteSendBuffer[1]='$';
	m_byteSendBuffer[6]='$';
	m_byteSendBuffer[7]='$';
	*((long*)&m_byteSendBuffer[2]) = nLen;

	nLen = Send(m_byteSendBuffer, nLen+8);

	return (nLen > 0);
}

BOOL CXUserTcpClientBase::Login(const CString &strUserID, const CString &strPsw)
{
	m_oSendCmd.DeleteAll();
	m_oSendCmd.m_strID = XUSER_CMD_LOGIN;
	m_oSendCmd.AddValue(XUSER_CMD_PARA_USERID, strUserID);
	m_oSendCmd.AddValue(XUSER_CMD_PARA_USERPSW, strPsw);
	
	return SendXUserCmd(&m_oSendCmd);
}

BOOL CXUserTcpClientBase::Logoff(const CString &strUserID)
{
	m_oSendCmd.DeleteAll();
	m_oSendCmd.m_strID = XUSER_CMD_LOGOUT;
	m_oSendCmd.AddValue(XUSER_CMD_PARA_USERID, strUserID);

	return SendXUserCmd(&m_oSendCmd);
}

//软件授权
BOOL CXUserTcpClientBase::hasp_has_catalog(UINT nFetureID)
{
	CString strValue;
	m_oSendCmd.DeleteAll();

	strValue.Format(_T("%d"), nFetureID);
	m_oSendCmd.m_strID = XUSER_CMD_HASFETURE;
	m_oSendCmd.AddValue(XUSER_CMD_PARA_FETUREID, strValue);

	return SendXUserCmd(&m_oSendCmd);
}

BOOL CXUserTcpClientBase::hasp_get_infor()
{
	m_oSendCmd.DeleteAll();
	m_oSendCmd.m_strID = XUSER_CMD_GETINFOR;

	return SendXUserCmd(&m_oSendCmd);
}
