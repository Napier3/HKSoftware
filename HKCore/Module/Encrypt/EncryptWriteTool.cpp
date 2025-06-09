// EncryptWriteTool.cpp: implementation of the CEncryptWriteTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EncryptWriteTool.h"
#include "..\API\GlobalConfigApi.h"

CEncryptWriteTool g_oEncryptWriteTool;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEncryptWriteTool::CEncryptWriteTool()
{

}

CEncryptWriteTool::~CEncryptWriteTool()
{
	
}
// 
// BOOL CEncryptWriteTool::SeekToEncryptBuffer()
// {
// 	DWORD dwLen = m_oFile.GetLength();
// 	m_pBufferRead = new char [dwLen+10];
// 	DWORD dwReadLen = m_oFile.Read(m_pBufferRead, dwLen);
// 
// 	ASSERT(dwReadLen == dwLen);
// 
// 	if (dwLen != dwReadLen)
// 	{
// 		delete m_pBufferRead;
// 		return FALSE;
// 	}
// 
// 	m_nBeginPos = 0;
// 	m_nEndPos = 0;
// 	char *pCurr = NULL;
// 	char *pEnd = m_pBufferRead + dwReadLen;
// 	char pszBeginBufferFlag[4] = "${{";
// 	char pszEndBufferFlag[4] = "}}$";
// 	BOOL bTrue = FALSE;
// 	
// 	while (pCurr <pEnd)
// 	{
// 		if (memcmp(pszBeginBufferFlag, pCurr, 3) == 0)
// 		{
// 			m_nBeginPos = pCurr - m_pBufferRead + 3;
// 			pCurr += 3;
// 
// 			while (pCurr <pEnd)
// 			{
// 				if (memcmp(pszBeginBufferFlag, pCurr, 3) == 0)
// 				{
// 					break;
// 				}
// 
// 				if (memcmp(pszEndBufferFlag, pCurr, 3) == 0)
// 				{
// 					m_nEndPos = pCurr - m_pBufferRead;
// 					break;
// 				}
// 			}
// 
// 			if (m_nEndPos > 0 && m_nEndPos > m_nBeginPos + 2048)
// 			{
// 				break;
// 			}
// 		}
// 	}
// 
// 	if (m_nEndPos > 0 && m_nEndPos > m_nBeginPos + 2048)
// 	{
// 		long nLen = m_nEndPos - m_nBeginPos;
// 
// 		if (nLen > EncryptTextBuffer_Len)
// 		{
// 			bTrue = FALSE;
// 		}
// 		else
// 		{
// 			memcpy(m_pEncryptTextBuffer, m_pBufferRead + m_nBeginPos, nLen);
// 			bTrue = TRUE;
// 		}
// 	}
// 	else
// 	{
// 		bTrue = FALSE;
// 	}
// 
// 	delete m_pBufferRead;
// 	return bTrue;
// }
// 
// BOOL CEncryptWriteTool::Register(const CString &strExeFile, const CString &strRegCode)
// {
// 	CString strFile;
// 	strFile = _P_GetBinPath();
// 	strFile += strExeFile;
// 
// 	BOOL bTrue = m_oFile.Open(strFile, CFile::typeBinary | CFile::modeReadWrite);
// 
// 	if (!bTrue)
// 	{
// 		return FALSE;
// 	}
// 
// 	if (!SeekToEncryptBuffer())
// 	{
// 		return FALSE;
// 	}
// 
// 	m_strCompany = _T("广东昂立电气自动化有限公司");
// 	//m_strCompany = _T("国电南京自动化股份有限公司");
// 	m_strUser = _T("");
// 	m_strSN = strRegCode;
// 	m_nMaxUseCount = -1;   //最大使用次数
// 	m_nCurrUseCount = 0;  //当前使用次数
// 	m_strDevCode = _T("");      //是否开发者MAC
// 	m_nAutoTest = 1;      //AutoTest程序授权
// 	m_nDev = 1;           //Dev平台程序授权
// 
// 	WriteEncrypt(ENCRYPT_INDEX_COMPANY, m_strCompany);
// 	WriteEncrypt(ENCRYPT_INDEX_USER, m_strUser);
// 	WriteEncrypt(ENCRYPT_INDEX_SN, m_strSN);
// 	WriteEncrypt(ENCRYPT_INDEX_MAXUSECOUNT, m_nMaxUseCount);
// 	WriteEncrypt(ENCRYPT_INDEX_CURUSECOUNT, m_nCurrUseCount);
// 	WriteEncrypt(ENCRYPT_INDEX_DEVCODE, m_strDevCode);
// 	WriteEncrypt(ENCRYPT_INDEX_AUTOTEST, m_nAutoTest);
// 	WriteEncrypt(ENCRYPT_INDEX_DEV, m_nDev);
// 	
// 	m_oFile.Seek(m_nBeginPos, CFile::begin);
// 	m_oFile.Write(m_pEncryptTextBuffer, m_nEndPos - m_nBeginPos);
// 
// 	m_oFile.Close();
// 	return TRUE;
// }
// 
// BOOL CEncryptWriteTool::CanRunRegister()
// {
// 	if (IsProgramExist(_T("autotest.exe")))
// 	{
// 		AfxMessageBox(_T("请关闭自动测试程序AutoTest.exe"));
// 		return FALSE;
// 	}
// 
// 	if (IsProgramExist(_T("guidebookdev.exe")))
// 	{
// 		AfxMessageBox(_T("请关闭自动测试程序GuideBookDev.exe"));
// 		return FALSE;
// 	}
// 
// 	if (IsProgramExist(_T("reporttemplatedev.exe")))
// 	{
// 		AfxMessageBox(_T("请关闭自动测试程序ReportTemplateDev.exe"));
// 		return FALSE;
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CEncryptWriteTool::Register(const CString &strRegCode)
// {
// 	if (!CanRunRegister())
// 	{
// 		return FALSE;
// 	}
// 
// 	Register(_T("AutoTest.exe"), strRegCode);
// 	Register(_T("GuideBookDev.exe"), strRegCode);
// 	Register(_T("ReportTemplateDev.exe"), strRegCode);
// 
// 	return TRUE;
// }
// 
// void CEncryptWriteTool::WriteEncrypt(long nID, CString &strText)
// {
// 	long nBeginPos = GetBeginPos(nID);
// 	long nLen = GetLen(nID);
// 	
// 	if (nLen == 0)
// 	{
// 		return;
// 	}
// 
// 	if (nLen < strText.GetLength())
// 	{
// 		strText = strText.Left(nLen);
// 	}
// 
// 	char *pCurr = m_pEncryptTextBuffer + nBeginPos;
// 	ZeroMemory(pCurr, nLen);
// 	CString_to_char(strText, pCurr);
// }
// 
// void CEncryptWriteTool::WriteEncrypt(long nID, long &nValue)
// {
// 	long nBeginPos = GetBeginPos(nID);
// 	long nLen = GetLen(nID);
// 
// 	if (nLen == 0)
// 	{
// 		return;
// 	}
// 
// 	ASSERT (nLen >= 4);
// 
// 	if (nLen < 4)
// 	{
// 		return;
// 	}
// 
// 	char *pCurr = m_pEncryptTextBuffer + nBeginPos;
// 	ZeroMemory(pCurr, nLen);
// 	*((long*)pCurr) = nValue;
// }
// 
