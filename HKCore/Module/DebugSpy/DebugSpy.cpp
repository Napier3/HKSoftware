// DebugSpy.cpp: implementation of the CDebugSpy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DebugSpy.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDebugData::CDebugData()
{
	m_dwBegin = 0;
	m_dwEnd = 0;
	m_nIndex = 0;
	m_nID = 0;
	m_nPos = 0;
}

CDebugData::~CDebugData()
{

}

void CDebugData::WriteFile(CFile *pFile)
{
	char pszBuffer[MAX_PATH];
	sprintf(pszBuffer, "%d    %d    %d    %d    %d    ", m_nIndex, m_nPos, m_dwBegin, m_dwEnd, m_dwEnd-m_dwBegin);
	pFile->Write(pszBuffer, strlen(pszBuffer));

	CString_to_char(m_strInfor, pszBuffer);
	pFile->Write(pszBuffer, strlen(pszBuffer));

	strcpy(pszBuffer, "\r\n");
	pFile->Write(pszBuffer, strlen(pszBuffer));
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CDebugSpy::CDebugSpy()
{
	m_nIndex = 0;
}

CDebugSpy::~CDebugSpy()
{
	DeleteAll();
}

CDebugData* CDebugSpy::Create(long nID, long nPos, const CString &strInfor)
{
	CDebugData* pDebugData = new CDebugData();

	AddTail(pDebugData);
	pDebugData->m_dwBegin = ::GetTickCount();
	pDebugData->m_nID = nID;
	pDebugData->m_nIndex = m_nIndex++;
	pDebugData->m_strInfor = strInfor;

	return pDebugData;
}

void CDebugSpy::WriteDebugSpy(const CString &strFile)
{
	POS pos = GetHeadPosition();
	CDebugData *pData = NULL;
	CFile file;

	if (! file.Open((LPCTSTR)strFile, CFile::modeCreate | CFile::modeWrite))
	{
		return;
	}

	while (pos != NULL)
	{
		pData = (CDebugData*)GetNext(pos);
		pData->WriteFile(&file);
	}

	file.Close();
}
