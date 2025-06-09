// StringSerializeBufferAscii.cpp: implementation of the CStringSerializeBufferAscii class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringSerializeBufferAscii.h"

#ifndef _PSX_IDE_QT_
#include "../AtlBaseClass/AtlFile.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
CStringSerializeBufferAscii oStrBuf;
oStrBuf.SetBufferLength(100);

long nVal=12345678;
double fVal = 12345678.12345678;
oStrBuf.AddBufLenByVal(nVal);
oStrBuf.AddBufLenByVal(fVal);


oStrBuf.AllocBuffer(0);
CString strData;

oStrBuf << "nVal=" << nVal << ";fVal=" << fVal << ";";
strData = _T("fdsfdsfdsfds");
oStrBuf << strData;

strData = _T("<李俊庆><李俊庆>");
oStrBuf << strData;

oStrBuf << _T("**李俊庆****李俊庆**");

oStrBuf >> strData;
*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const long CStringSerializeBufferAscii::DEFAULT_BUFF_LENGTH = 512;
	
CStringSerializeBufferAscii::CStringSerializeBufferAscii()
{
	Init();
}

CStringSerializeBufferAscii::~CStringSerializeBufferAscii()
{
	FreeBuff();
}

BOOL CStringSerializeBufferAscii::ReadFromFile(const CString &strFile)
{	
#ifndef _PSX_IDE_QT_

#ifdef UNICODE
	char *pszFile = NULL;
	CString_to_char(strFile, &pszFile);
	FILE *pfile = fopen(pszFile, "r+b");
	delete pszFile;
#else
	FILE *pfile = fopen(strFile, "r+b");
#endif

	if (pfile == NULL)
	{
		return FALSE;
	}

	fseek(pfile, 0, SEEK_END);
	long nLen = ftell(pfile);
	long nCalLen = nLen;

	long nCurrLen = m_lpBufMax - m_pchData;

	if (nCurrLen < nCalLen)
	{
		nCurrLen = nLen;
		AllocBuffer(0);
	}
	else
	{
		memset(m_pchData,0,nCurrLen);
	}

	fseek(pfile, 0, SEEK_SET);
	long nReadLen =  ftell(pfile);
	nReadLen = fread(m_pchData, nLen, 1, pfile);
	fclose(pfile);

	ResetBufferPointer();

#endif  //#ifndef _PSX_IDE_QT_

	return TRUE;
}


BOOL CStringSerializeBufferAscii::WriteToFile(const CString &strFile)	
{
	long nLen = 0;
#ifndef _PSX_IDE_QT_

#ifdef UNICODE
	char *pszFile = NULL;
	CString_to_char(strFile, &pszFile);
	FILE *pfile = fopen(pszFile, "w+b");
	delete pszFile;
#else
	FILE *pfile = fopen(strFile, "w+b");
#endif

	if (pfile == NULL)
	{
		return FALSE;
	}

	nLen = GetBufferLength();
	fwrite(m_pchData, nLen, 1, pfile);
	fclose(pfile);

#endif  //#ifndef _PSX_IDE_QT_

	return TRUE;
}

void CStringSerializeBufferAscii::RepalceChar(CHAR chSrc, CHAR chDest, long nLen)
{
	CHAR *p = m_pchData;
	CHAR *pEnd = m_pchData + nLen;

	while (p < pEnd )
	{
		if (*p == chSrc)
		{
			*p = chDest;
		}

		p++;
	}
}

void CStringSerializeBufferAscii::Init()
{
	m_pchData = NULL;
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
	m_nBufferLength = 0;
	m_nEncoding = XSTR_EncodingIdx_utf8;
}

int  CStringSerializeBufferAscii::GetBufferLength()
{
	return 	m_nBufferLength;
}

void CStringSerializeBufferAscii::ResetBufferPointer()
{
	m_lpBufCur = m_pchData;
}

long CStringSerializeBufferAscii::Append_ASCII(const CString &strData)
{
#ifdef _UNICODE
	int nLen = strData.GetLength();
#else
	int nLen = strData.GetLength();
#endif

	if (m_lpBufCur + nLen > m_lpBufMax) 
	{
		ExpandAllocBuffer(nLen+DEFAULT_BUFF_LENGTH);
	}

#ifdef _UNICODE
	nLen = CString_to_char(strData, m_lpBufCur);
#else
    strcpy((char*)m_lpBufCur, strData.GetString());
#endif
	m_lpBufCur += nLen;

	return nLen;
}

long CStringSerializeBufferAscii::Append_String(const CString &strData)
{//数据库插字符串数据时，将'\'【0x5c】,'''【0x27】,'"'【0x22】由转义字符表示
	char *pBuffer = NULL;
	long nLen = 0;
	if (m_nEncoding == XSTR_EncodingIdx_gb2312)
	{
		nLen = CString_to_char(strData, &pBuffer);
	}
	else
	{
#ifndef _PSX_QT_LINUX_
		charGBK_to_charUtf8((char *)strData.GetString(), strData.GetLength(), &pBuffer, nLen);
#endif
	}
	

	long nRet = Append_MySql(pBuffer, nLen);
	delete pBuffer;

	return nRet;
}

 void CStringSerializeBufferAscii::StringEnd()
 {
	 if (m_lpBufCur <= m_lpBufMax) 
	 {
		*m_lpBufCur = 0;
	 }
	 else
	 {
		 *(m_lpBufMax-1) = 0;
	 }
 }

//缓冲区方法
void CStringSerializeBufferAscii::Append(const char *pBuffer, long nLen)
{
	if (m_lpBufCur + nLen > m_lpBufMax) 
	{
		ExpandAllocBuffer(nLen+DEFAULT_BUFF_LENGTH);
	}

	memcpy(m_lpBufCur, pBuffer, nLen);
	m_lpBufCur += nLen;
}

void CStringSerializeBufferAscii::AppendEquation(const char *pszID, const char *pszValue)
{
    long nLen1 = strlen(pszID);
    long nLen2 = 0;
	
	if (pszValue != NULL)
	{
		nLen2 = strlen(pszValue);
	}
	
    long nLen = nLen1 + nLen2 + 3;

    if (Tell_Curr_to_End() < nLen)
    {
    ExpandAllocBuffer(nLen+DEFAULT_BUFF_LENGTH);
    }

    Append(pszID, nLen1);
    *m_lpBufCur = '=';
    m_lpBufCur++;

	if (pszValue != NULL)
	{
    Append(pszValue, nLen2);
	}
    
    *m_lpBufCur = ';';
    m_lpBufCur++;
}

//https://blog.csdn.net/cheng_fangang/article/details/8348860
long CStringSerializeBufferAscii::Append_MySql(char *pBuffer, long &nLen)
{//数据库插Blob数据时，将NUL【0x0】,'\'【0x5c】,'''【0x27】,'"'【0x22】由转义字符表示
	char *pSrc = pBuffer;
	char *pEnd = pBuffer + nLen;
	char *pDst = m_lpBufCur;
	long nRet = 0;

	while (pSrc < pEnd)
	{
		if ((*pSrc == 0x22) || (*pSrc == 0x5c)
			|| (*pSrc == 0x27))
		{
			*pDst = 0x5c;
			pDst++;
		}

		*pDst = *pSrc;
		pDst++;
		pSrc++;
	}

	nRet = pDst - m_lpBufCur;
	m_lpBufCur = pDst;

	return nRet;
}

long CStringSerializeBufferAscii::String(const CString &strData)
{
	*this << strData;
	return (m_lpBufCur - m_pchData);
}

long CStringSerializeBufferAscii::String(BSTR strData)
{
	*this << strData;
	return (m_lpBufCur - m_pchData);
}

long CStringSerializeBufferAscii::String(CString *pstrData)
{
	*this >> *pstrData;
	return 0;
}

BOOL CStringSerializeBufferAscii::SetBufferLength(int nLen)	
{	
	m_nBufferLength = nLen;	
	return TRUE;
}


void CStringSerializeBufferAscii::FreeBuff()
{
	if (m_pchData != NULL)
	{
		delete m_pchData;
		m_pchData = NULL;
	}

	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
	m_nBufferLength = 0;
}

// long CStringSerializeBufferAscii::Tell(char *pPos)
// {
// 	return pPos - m_pchData;
// }
// 
// long CStringSerializeBufferAscii::Tell_Curr_to_End(char *pPos)
// {
// 	return pPos - m_lpBufCur;
// }

BOOL CStringSerializeBufferAscii::AllocBuffer(long lExpandPercent)
{
	long nLen = 0;
	m_nBufferLength = m_nBufferLength + m_nBufferLength * lExpandPercent / 100;
	nLen = m_nBufferLength;

	if (m_lpBufMax != NULL)
	{
		long nCurrLen = m_lpBufMax - m_pchData;
		m_lpBufCur = m_pchData;

		if (nCurrLen > m_nBufferLength)
		{
			return TRUE;
		}
	}

	FreeBuff();
	m_nBufferLength = nLen;
	m_pchData = new char[m_nBufferLength];

	if (m_pchData == NULL)
	{
		throw(-1);
	}

	m_lpBufMax = m_pchData + m_nBufferLength;
	m_lpBufCur = m_pchData;

	if (m_pchData != NULL)
	{
		memset(m_pchData,0,m_nBufferLength);
		m_lpBufCur = m_pchData;
	}

	return (m_pchData != NULL);
}

void CStringSerializeBufferAscii::ExpandAllocBuffer(long nAddLen)
{
	long nCurrLen = m_lpBufMax - m_pchData;
	long nNewLen = nCurrLen + nAddLen;
	long nDataLen = m_lpBufCur - m_pchData;

	char *pNew = new char[nNewLen];
	memset(pNew,0,nNewLen);

	if (pNew == NULL)
	{
		throw(-1);
	}

	memcpy(pNew, m_pchData, nDataLen);
	m_lpBufCur = pNew + nDataLen;
	m_lpBufMax = pNew + nNewLen;
	delete m_pchData;
	m_pchData = pNew;
	m_nBufferLength = nNewLen;
}

//////////////////////////////////////////////////////////////////////////
#ifdef _DBLIB_USE_SHAREMEM_

CStringSerializeBufferAscii_ShareMem::CStringSerializeBufferAscii_ShareMem()
{
	m_pBufferSm = NULL;
	m_bAttachShareMemSerialize = FALSE;
}

CStringSerializeBufferAscii_ShareMem::~CStringSerializeBufferAscii_ShareMem()
{
	
}

void CStringSerializeBufferAscii_ShareMem::FreeBuff()
{
	if (m_bAttachShareMemSerialize)
	{
		m_pBufferSm = NULL;
	}
	else
	{
		if (m_pBufferSm != NULL)
		{
			m_pBufferSm->SerializeFree();
			delete m_pBufferSm;
			m_pBufferSm = NULL;
		}
	}

	m_pchData = NULL;
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
	m_nBufferLength = 0;

}

BOOL CStringSerializeBufferAscii_ShareMem::SetBufferLength(int nLen)
{
	m_pBufferSm->GetBuffer(&m_pchData, &m_nBufferLength);
	m_lpBufCur = m_pchData;
	m_nBufferLength = m_pBufferSm->GetBufferLength();
	m_lpBufMax = m_pchData + m_pBufferSm->GetBufferLength();

	ResetBufferPointer();
	return TRUE;
}

BOOL CStringSerializeBufferAscii_ShareMem::AllocBuffer(long lExpandPercent)
{
	m_pBufferSm->GetBuffer(&m_pchData, &m_nBufferLength);
	m_lpBufCur = m_pchData;
	m_nBufferLength = m_pBufferSm->GetBufferLength();
	m_lpBufMax = m_pchData + m_pBufferSm->GetBufferLength();

	ResetBufferPointer();
	return TRUE;
}

void CStringSerializeBufferAscii_ShareMem::ExpandAllocBuffer(long nAddLen)
{
	ResetBufferPointer();
}

void CStringSerializeBufferAscii_ShareMem::AttachShareMemSerialize(CShareMemSerialize *pBufferSm)
{
	FreeBuff();

	ASSERT (pBufferSm != NULL);
	m_bAttachShareMemSerialize = TRUE;
	m_pBufferSm = pBufferSm;
	m_pBufferSm->GetBuffer(&m_pchData, &m_nBufferLength);
	m_lpBufCur = m_pchData;
	m_nBufferLength = m_pBufferSm->GetBufferLength();
	m_lpBufMax = m_pchData + m_nBufferLength;
}

void CStringSerializeBufferAscii_ShareMem::CreateShareMemSerialize(const CString &strSmFile, DWORD dwLen)
{
	FreeBuff();

	m_pBufferSm = new CShareMemSerialize();
	m_pBufferSm->CreateFileEx(strSmFile, dwLen);
	
	m_pBufferSm->GetBuffer(&m_pchData, &m_nBufferLength);
	m_lpBufCur = m_pchData;
	m_nBufferLength = m_pBufferSm->GetBufferLength();
	m_lpBufMax = m_pchData + m_nBufferLength;
}

BOOL CStringSerializeBufferAscii_ShareMem::ReadFromFile(const CString &strFile)
{
	CFile file;
	BOOL bTrue = file.Open(strFile,CFile::modeRead);
	
	if(bTrue)
	{
		long nLen = file.GetLength();
		file.Read(m_pchData, nLen);
		m_pchData[nLen] = 0;
		file.Close();
		ResetBufferPointer();

		return TRUE;
	}

	return FALSE;
}

BOOL CStringSerializeBufferAscii_ShareMem::WriteToFile(const CString &strFile)
{
	CFile file;
	BOOL bOpen = file.Open(strFile,CFile::modeCreate|CFile::modeWrite);
	if (bOpen)
	{
		file.Write(m_pchData, m_lpBufCur - m_pchData);
		file.Close();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

#endif
