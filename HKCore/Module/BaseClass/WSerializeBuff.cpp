// SerializeBuff.cpp: implementation of the CWSerializeBuff class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WSerializeBuff.h"
//#include "..\AtlBaseClass\AtlFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWSerializeBuff::CWSerializeBuff()
{
	m_bAttach = FALSE;
	Init();
	//AllocDefaultBuffer();//SetBufferLength(DEFAULT_BUFF_LENGTH);
	m_nOperation = MODE_WRITE;
	m_nBufCurLen = 0;
}

CWSerializeBuff::CWSerializeBuff(int nLen)
{
	m_bAttach = FALSE;
	Init();
	SetBufferLength(nLen);
	m_nOperation = MODE_WRITE;
	m_nBufCurLen = 0;
}

CWSerializeBuff::CWSerializeBuff(wchar_t *pBuff,int nLen)
{
	m_bAttach = FALSE;
	Init();
	SetBufferLength(nLen);
	memcpy(m_pchData, pBuff, nLen*2);
	m_nBufCurLen = 0;
}

CWSerializeBuff::CWSerializeBuff(char *pBuff,int nLen)
{
	m_bAttach = FALSE;
	Init();
	SetBufferLength(nLen);
	memcpy(m_pchData, pBuff, nLen);
	m_nBufCurLen = 0;
}

CWSerializeBuff::~CWSerializeBuff()
{
	FreeBuff();
}

void CWSerializeBuff::GetBuffer(wchar_t** pBuffer, long *nBufferLen)
{
	*pBuffer = (wchar_t*)m_pchData;
	*nBufferLen = GetBufferLength();
}

void CWSerializeBuff::GetBuffer(char** pBuffer, long *nBufferLen)
{
	*pBuffer = m_pchData;
	*nBufferLen = GetBufferLength();
}

void CWSerializeBuff::AttachBuffer(wchar_t *pBuffer, long nBufferLen)
{
	FreeBuff();
	m_bAttach = TRUE;
	m_pchData = (char*)pBuffer;
	m_nBufCurLen = nBufferLen*2;
	m_nBufferLength = m_nBufCurLen;
	m_lpBufCur = m_pchData;
	m_lpBufMax = m_pchData + m_nBufCurLen;
	ResetBufferPointer();
}

void CWSerializeBuff::AttachBuffer(char *pBuffer, long nBufferLen)
{
	FreeBuff();
	m_bAttach = TRUE;
	m_pchData = (char*)pBuffer;
	m_nBufCurLen = nBufferLen;
	m_lpBufCur = m_pchData;
	m_nBufferLength = m_nBufCurLen;
	m_lpBufMax = m_pchData + m_nBufCurLen;
	ResetBufferPointer();
}

void CWSerializeBuff::DettachBuffer()
{
	m_bAttach = FALSE;
	m_pchData = NULL;
}

BOOL CWSerializeBuff::ReadFromFile(const CString &strFile, long nAddBuf)
{	
#ifdef UNICODE
	char *pszFile = NULL;
	CString_to_char(strFile, &pszFile);
	FILE *pfile = fopen(pszFile, "r+b");
	delete pszFile;
#else
    FILE *pfile = fopen(strFile.GetString(), "r+b");
#endif

	if (pfile == NULL)
	{
		return FALSE;
	}

	fseek(pfile, 0, SEEK_END);
	long nLen = ftell(pfile);
	long nCalLen = nLen + nLen * nAddBuf / 100;

	if (m_nBufCurLen < nCalLen)
	{
		m_nBufCurLen = nLen;
		AllocBuffer(nAddBuf);
	}
	else
	{
		memset(m_pchData,0,m_nBufCurLen);
	}

	fseek(pfile, 0, SEEK_SET);
	long nReadLen =  ftell(pfile);
	nReadLen = fread(m_pchData, nLen, 1, pfile);
	fclose(pfile);

	ResetBufferPointer();

	return TRUE;

// 	CFile file;
// 	BOOL bOpen = file.Open(strFile, CFile::modeRead);
// 
// 	if (bOpen)
// 	{
// 		long nLen = file.GetLength();
// 		long nCalLen = nLen + nLen * nAddBuf / 100;
// 
// 		if (m_nBufCurLen < nCalLen)
// 		{
// 			m_nBufCurLen = nLen;
// 			AllocBuffer(nAddBuf);
// 		}
// 		else
// 		{
// 			memset(m_pchData,0,m_nBufCurLen);
// 		}
// 
// 		file.Read(m_pchData,nLen);
// 		file.Close();
// 	}
// 	else
// 	{
// 
// 	}
// 
// 	ResetBufferPointer();
// 
// 	return bOpen;
}


BOOL CWSerializeBuff::WriteToFile(const CString &strFile)	
{
 	long nLen = 0;

// 	CFile file;
//     BOOL bOpen = file.Open(strFile,CFile::modeCreate | CFile::modeWrite);
// 
// 	if (bOpen)
// 	{
// 		nLen = GetBufferLength();
// 		file.Write(m_pchData,nLen);
// 		file.Close();
// 	}
// 
// 	return bOpen;

#ifdef UNICODE
	char *pszFile = NULL;
	CString_to_char(strFile, &pszFile);
	FILE *pfile = fopen(pszFile, "w+b");
	delete pszFile;
#else
    FILE *pfile = fopen(strFile.GetString(), "w+b");
#endif


	if (pfile == NULL)
	{
		return FALSE;
	}

	nLen = GetBufferLength();
	fwrite(m_pchData, nLen, 1, pfile);
	fclose(pfile);

	return TRUE;
}

BOOL CWSerializeBuff::CreateFile(const CString &strFile)
{
	return TRUE;
}

void CWSerializeBuff::FreeBuff()
{
	m_nBufCurLen = 0;
	m_nBufferLength = 0;
	if (m_bAttach)
	{
		m_pchData = NULL;
		m_bAttach = FALSE;
	}
	else
	{
		if (m_pchData != NULL)
		{
			delete m_pchData;
			m_pchData = NULL;
		}
	}
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
}

void CWSerializeBuff::SerializeFree()
{
	FreeBuff();
}

BOOL CWSerializeBuff::AllocDefaultBuffer()
{
	FreeBuff();
	m_nBufCurLen = DEFAULT_BUFF_LENGTH;
	m_nBufferLength = DEFAULT_BUFF_LENGTH;
	m_pchData = new char[m_nBufCurLen];

	if (m_pchData != NULL)
	{
		memset(m_pchData,0,m_nBufferLength);
		m_lpBufCur = m_pchData;
		m_lpBufMax = m_pchData + m_nBufferLength;
	}
	
	return (m_pchData != NULL);
}

 BOOL CWSerializeBuff::AllocBuffer(long lExpandPercent)
 {
	 long nBufferLen = m_nBufCurLen + m_nBufCurLen * lExpandPercent / 100;
	 
	 if (m_nBufferLength < nBufferLen /*|| nBufferLen <= 0 */|| m_pchData == NULL)
	 {//需要的缓冲区大于缓冲区最大长度  缓冲区没有分配
		 FreeBuff();
		 m_nBufferLength = nBufferLen + DEFAULT_BUFF_LENGTH; //缓冲区最大长度
		 m_nBufCurLen = nBufferLen;  //当前使用的缓冲区长度
		 m_pchData = new char[m_nBufferLength + 10];
		 m_lpBufMax = m_pchData + m_nBufferLength;
		 m_lpBufCur = m_pchData;
	 }
	 else
	 {
	 }
	 
	 if (m_pchData != NULL)
	 {
		 memset(m_pchData,0,m_nBufferLength);
		 m_lpBufCur = m_pchData;
	 }

	 return (m_pchData != NULL);
 }
 
BOOL CWSerializeBuff::SetBufferLength(int nLen)
{
	m_nBufCurLen = nLen;
	return AllocBuffer(0);	
}

