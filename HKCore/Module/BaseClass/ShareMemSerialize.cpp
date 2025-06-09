// ShareMemSerialize.cpp: implementation of the CShareMemSerialize class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShareMemSerialize.h"
#include "..\AtlBaseClass\AtlFile.h"
#include "..\API\FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShareMemSerialize::CShareMemSerialize()
{
	m_bAttach = FALSE;
	Init();
	AllocDefaultBuffer();//SetBufferLength(DEFAULT_BUFF_LENGTH);
	m_nOperation = MODE_WRITE;
	m_nBufCurLen = 0;
}

CShareMemSerialize::~CShareMemSerialize()
{
	FreeBuff();
}

void CShareMemSerialize::GetBuffer(wchar_t** pBuffer, long *nBufferLen)
{
	*pBuffer = (wchar_t*)m_pchData;
	*nBufferLen = m_nBufCurLen;
}

void CShareMemSerialize::GetBuffer(char** pBuffer, long *nBufferLen)
{
	*pBuffer = m_pchData;
	*nBufferLen = m_lpBufCur - m_pchData;
}

void CShareMemSerialize::AttachBuffer(wchar_t *pBuffer, long nBufferLen)
{

}

void CShareMemSerialize::AttachBuffer(char *pBuffer, long nBufferLen)
{

}

void CShareMemSerialize::DettachBuffer()
{

}

BOOL CShareMemSerialize::ReadFromFile(const CString &strFile, long nAddBuf)
{
	m_nBufCurLen = file_GetFileSize(strFile);
	CreateFile(strFile);
	ResetBufferPointer();

	return TRUE;
}


BOOL CShareMemSerialize::WriteToFile(const CString &strFile)	
{
	m_oShareMem.FlushViewFile();
	return TRUE;
}

BOOL CShareMemSerialize::CreateFile(const CString &strFile)
{
	CString strMapName;
	long nBufLen = m_nBufCurLen;
	strMapName = GetPathFileNameFromFilePathName(strFile);
	m_oShareMem.CreateShareMem(strFile, strMapName, nBufLen);

	m_oShareMem.MapView(0, nBufLen);
	ASSERT (m_oShareMem.IsValid());
	m_pchData = (char*)m_oShareMem.GetBuffer();
	m_lpBufMax = m_pchData + nBufLen;
	ResetBufferPointer();

	return TRUE;
}

//2018-10-12  lijq
BOOL CShareMemSerialize::CreateFileEx(const CString &strFile, DWORD dwLen)
{
	//×î´ó1G¿Õ¼ä
	if (dwLen > 1024)
	{
		dwLen = 1024;
	}

	m_nBufCurLen = dwLen * 1024 * 1024;
	CString strMapName;
	strMapName = GetPathFileNameFromFilePathName(strFile);
	m_oShareMem.CreateShareMem(strFile, strMapName, m_nBufCurLen);

	m_oShareMem.MapView(0, m_nBufCurLen);
	ASSERT (m_oShareMem.IsValid());
	m_pchData = (char*)m_oShareMem.GetBuffer();
	m_lpBufMax = m_pchData + m_nBufCurLen;
	m_nBufferLength = m_nBufCurLen;
	ResetBufferPointer();

	return TRUE;
}

void CShareMemSerialize::SerializeFree()
{
	m_oShareMem.DestoryShareMem();
	m_nBufCurLen = 0;
	m_nBufferLength = 0;
	m_pchData = NULL;
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
}

void CShareMemSerialize::FreeBuff()
{
	SerializeFree();
}

BOOL CShareMemSerialize::AllocDefaultBuffer()
{
	ResetBufferPointer();
	return TRUE;
}

 BOOL CShareMemSerialize::AllocBuffer(long lExpandPercent)
 {
	 ResetBufferPointer();
	 return TRUE;
 }
 
BOOL CShareMemSerialize::SetBufferLength(int nLen)
{
	return AllocBuffer(0);	
}

