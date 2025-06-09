// FormatTextConvert.cpp: implementation of the CFormatTextConvert class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FormatTextConvert.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//const long MAX_OF_CONVERT_STRING = 20;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFormatTextConvert::CFormatTextConvert(long lType)
{
	InitIt();	
	m_nConvertType = lType;
}

CFormatTextConvert::CFormatTextConvert(const char *pszSrc,long lType)
{
	InitIt();
	m_nConvertType = lType;
	SetData(pszSrc);
}

CFormatTextConvert::CFormatTextConvert(const CString &strSrc,long lType)
{
	m_nConvertType = lType;
	InitIt();
	SetData(strSrc);
}

CFormatTextConvert::~CFormatTextConvert()
{
	int iIndex = 0;
	for (iIndex = 0; iIndex < m_nKeyCount; iIndex++)
	{
		delete m_arrKeyWord[iIndex];	//关键字
		delete m_arrKeyFormat[iIndex];	//格式化数据
	}
	FreeBuffer();
}

void CFormatTextConvert::SetData(const char *pszSrc)
{
	FreeBuffer();
	
	if (pszSrc == NULL)
	{
		return ;
	}
	long lLen = strlen(pszSrc) + 1;
	m_pBufferSrc = new char [lLen];
	strcpy(m_pBufferSrc,pszSrc);

	Convert();
}

void CFormatTextConvert::SetData(const CString &strSrc)
{
	FreeBuffer();

	long lLen = strSrc.GetLength() + 1;
	m_pBufferSrc = new char [lLen];
	strcpy(m_pBufferSrc,strSrc);
	
	Convert();
}

const char* CFormatTextConvert::GetData() const
{
	return m_pBufferDest;
}

void CFormatTextConvert::GetData(CString &strDest)
{
	if (m_pBufferDest != NULL)
	{
		strDest.Format("%s",m_pBufferDest);
	}
}

void CFormatTextConvert::Convert(const char *pszSrc,CString &strDest)
{
	SetData(pszSrc);
	GetData(strDest);
}

void CFormatTextConvert::Convert(const CString &strSrc,CString &strDest)
{
	SetData(strSrc);
	GetData(strDest);	
}

void CFormatTextConvert::InitKeyWords()
{
	char pszTab[20];
	sprintf(pszTab,"%c",VK_TAB);

	AddKeyWord("#","#amp");
	AddKeyWord("=","#eq");
	AddKeyWord(">","#krt");
	AddKeyWord("<","#klt");
	AddKeyWord(pszTab,"#tb");
	AddKeyWord(" ","#sp");
	AddKeyWord(";","#sk");
	AddKeyWord("]","#rt");
	AddKeyWord("[","#lt");
}

BOOL CFormatTextConvert::AddKeyWord(const char *pszKeyWord,const char *pszKeyFormat)
{
	if (pszKeyWord == NULL || pszKeyFormat == NULL)
	{
		return FALSE;
	}
	if (m_nKeyCount == MAX_OF_CONVERT_STRING - 1)
	{
		return FALSE;
	}
	if (IsKeyWordExist(pszKeyWord) || IsKeyFormatExist(pszKeyFormat))
	{
		return FALSE;
	}
	if (strlen(pszKeyWord) == 0 || 0 == strlen(pszKeyFormat))
	{
		return FALSE;
	}
	
	long lLen = 0;

	lLen = strlen(pszKeyWord);
	m_arrKeyWord[m_nKeyCount] = new char [lLen+1];
	strcpy(m_arrKeyWord[m_nKeyCount],pszKeyWord);

	lLen = strlen(pszKeyFormat);
	m_arrKeyFormat[m_nKeyCount] = new char [lLen+1];
	strcpy(m_arrKeyFormat[m_nKeyCount],pszKeyFormat);

	m_nKeyCount++;

	return TRUE;
}

BOOL CFormatTextConvert::AddKeyWord(const CString &strKeyWord,const CString &strKeyFormat)
{
	if (m_nKeyCount == MAX_OF_CONVERT_STRING - 1)
	{
		return FALSE;
	}
	if (IsKeyWordExist(strKeyWord) || IsKeyFormatExist(strKeyFormat))
	{
		return FALSE;
	}
	if (strKeyWord.GetLength() == 0 || 0 == strKeyFormat.GetLength())
	{
		return FALSE;
	}
	
	long lLen = 0;
	
	lLen = strKeyWord.GetLength();
	m_arrKeyWord[m_nKeyCount] = new char [lLen+1];
	strcpy(m_arrKeyWord[m_nKeyCount],strKeyWord);
	
	lLen = strKeyFormat.GetLength();
	m_arrKeyFormat[m_nKeyCount] = new char [lLen+1];
	strcpy(m_arrKeyFormat[m_nKeyCount],strKeyFormat);
	
	m_nKeyCount++;
	
	return TRUE;
}


BOOL CFormatTextConvert::IsKeyWordExist(const char *pszKeyWord)
{
	int iIndex = 0;
	BOOL bFind = FALSE;
	for (iIndex = 0; iIndex < m_nKeyCount; iIndex++)
	{
		if (strcmp(m_arrKeyWord[iIndex],pszKeyWord) == 0)
		{
			bFind = TRUE;
		}
	}
	return bFind;
}

BOOL CFormatTextConvert::IsKeyWordExist(const CString &strKeyWord)
{
	int iIndex = 0;
	BOOL bFind = FALSE;
	for (iIndex = 0; iIndex < m_nKeyCount; iIndex++)
	{
		if (strcmp(m_arrKeyWord[iIndex],strKeyWord) == 0)
		{
			bFind = TRUE;
		}
	}
	return bFind;
}

BOOL CFormatTextConvert::IsKeyFormatExist(const char *pszKeyFormat)
{
	int iIndex = 0;
	BOOL bFind = FALSE;
	for (iIndex = 0; iIndex < m_nKeyCount; iIndex++)
	{
		if (strcmp(m_arrKeyFormat[iIndex],pszKeyFormat) == 0)
		{
			bFind = TRUE;
		}
	}
	return bFind;
}

BOOL CFormatTextConvert::IsKeyFormatExist(const CString &strKeyFormat)
{
	int iIndex = 0;
	BOOL bFind = FALSE;
	for (iIndex = 0; iIndex < m_nKeyCount; iIndex++)
	{
		if (strcmp(m_arrKeyFormat[iIndex],strKeyFormat) == 0)
		{
			bFind = TRUE;
		}
	}
	return bFind;
}

void CFormatTextConvert::InitIt()
{
	m_pBufferSrc = NULL;	//源数据
	m_pBufferDest = NULL;	//转换后数据	
	m_pBufferDestTemp = NULL;	//转换后数据	
	m_nKeyCount = 0;
	m_nKeyCount = 0;
	int iIndex = 0;
	for (iIndex = 0; iIndex < MAX_OF_CONVERT_STRING; iIndex++)
	{
		m_arrKeyWord[iIndex] = NULL;	//关键字
		m_arrKeyFormat[iIndex] = NULL;	//格式化数据
	}
	InitKeyWords();	
}

void CFormatTextConvert::FreeBuffer()
{
	if (m_pBufferSrc != NULL)
	{
		delete m_pBufferSrc;
		m_pBufferSrc = NULL;
	}

	if (m_pBufferDest != NULL)
	{
		delete m_pBufferDest;
		m_pBufferDest = NULL;
	}

	if (m_pBufferDestTemp != NULL)
	{
		delete m_pBufferDestTemp;
		m_pBufferDestTemp = NULL;
	}
}

void CFormatTextConvert::Convert()
{
	long lIndex = 0;

	AllocateBufferDest();
	
	if ( m_nConvertType == CONVERTTOFORMARTDATA )
	{
		for (lIndex = 0; lIndex < m_nKeyCount; lIndex++)
		{
			Replace(lIndex);
		}
	}
	else if ( m_nConvertType == CONVERTTONORMALDATA)
	{
		for (lIndex = m_nKeyCount - 1; lIndex >= 0; lIndex--)
		{
			Replace(lIndex);
		}
	}
	else
	{
	}
}

void CFormatTextConvert::AllocateBufferDest()
{
	long lLenOld = 0;
	long lLenNew = 0;
	long lLenKeyOld = 0;
	long lLenKeyNew = 0;
	long lIndex = 0;
	long lCount = 0;

	for (lIndex = 0; lIndex < m_nKeyCount; lIndex++)
	{
		switch (m_nConvertType) 
		{
		case CONVERTTOFORMARTDATA:
			lLenKeyOld = strlen(m_arrKeyWord[lIndex]);
			lLenKeyNew = strlen(m_arrKeyFormat[lIndex]);
			break;
		case CONVERTTONORMALDATA:
			lLenKeyNew = strlen(m_arrKeyWord[lIndex]);
			lLenKeyOld = strlen(m_arrKeyFormat[lIndex]);
			break;
		default:
			break;
		}
		lCount = GetKeyWordCount(lIndex);
		lLenOld = lLenOld + lLenKeyOld * lCount;
		lLenNew = lLenNew + lLenKeyNew * lCount;
	}

	m_nBufferLength = strlen(m_pBufferSrc) + 1;
	if (lLenNew > lLenOld)
	{
		m_nBufferLength += lLenNew - lLenOld;
	}
	//lLen = strlen(m_pBufferSrc) + lLenNew - lLenOld + 1;
	m_pBufferDest = new char [m_nBufferLength];
	m_pBufferDestTemp = new char [m_nBufferLength];
	memset(m_pBufferDest,0,m_nBufferLength);
	memset(m_pBufferDestTemp,0,m_nBufferLength);
	strcpy(m_pBufferDestTemp,m_pBufferSrc);
}

long CFormatTextConvert::GetKeyWordCount(long lIndex)
{
	if (lIndex < 0 || lIndex >= m_nKeyCount)
		return 0;

	long lCount = 0;
	char *pKey = NULL;
	switch (m_nConvertType) 
	{
	case CONVERTTOFORMARTDATA:
		pKey = m_arrKeyWord[lIndex];
		break;
	case CONVERTTONORMALDATA:
		pKey = m_arrKeyFormat[lIndex];
		break;
	default:
		break;
	}

	char *pTemp = NULL;
	pTemp = m_pBufferSrc;
	long lLen = strlen(pKey);
	while (*pTemp != 0)
	{
		if (strncmp(pTemp,pKey,lLen) == 0)
		{
			lCount++;
			pTemp += strlen(pKey);
		}
		else
		{
			pTemp++;
		}
	}
	return lCount;
}

void CFormatTextConvert::Replace(long lIndex)
{
	if (lIndex < 0 || lIndex >= m_nKeyCount)
		return;
	
	char *pszOld = NULL;
	char *pszNew = NULL;
	switch (m_nConvertType) 
	{
	case CONVERTTOFORMARTDATA:
		pszOld = m_arrKeyWord[lIndex];
		pszNew = m_arrKeyFormat[lIndex];
		break;
	case CONVERTTONORMALDATA:
		pszOld = m_arrKeyFormat[lIndex];
		pszNew = m_arrKeyWord[lIndex];
		break;
	default:
		break;
	}
	
	if (pszOld != NULL && pszNew != NULL)
	{
		Replace(pszOld,pszNew);
	}
}

void CFormatTextConvert::Replace(const char *pszOld,const char *pszNew)
{
	char *pSrc = m_pBufferDestTemp;
	char *pDest = m_pBufferDest;
	long lLenOld = strlen(pszOld);
	long lLenNew = strlen(pszNew);
	long lPosNew = 0;
	long lPosOld = 0;

	while (*pSrc != 0)
	{
		if (strncmp(pSrc,pszOld,lLenOld) == 0)
		{
			memcpy(pDest,pszNew,lLenNew);
			pDest += lLenNew;
			pSrc += lLenOld;
			lPosNew += lLenNew;
			lPosOld += lLenOld;
		}
		else
		{
			*pDest = *pSrc;
			pDest++;
			pSrc++;
			lPosNew++;
			lPosOld++;
		}
	}
	*(m_pBufferDest + lPosNew) = 0;
	memcpy(m_pBufferDestTemp,m_pBufferDest,lPosNew+1);
}

