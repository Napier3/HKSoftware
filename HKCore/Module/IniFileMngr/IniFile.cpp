// IniFile.cpp : implementation file
//

#include "stdafx.h"
#include "IniFile.h"
#include "IniFileBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIniFile

CIniFile::CIniFile()
{
	m_strIniFile = "";
}

CIniFile::CIniFile(const CString &strFile)
{
	SetIniFile(strFile);
}

CIniFile::~CIniFile()
{
	m_strIniFile = "";
}

/////////////////////////////////////////////////////////////////////////////
//ͨ��Section���ơ�Key���ƻ�ȡKey����
CString CIniFile::GetKeyValue(const CString &strSectionName,const CString &strKeyName)
{
	CIniSection *pIniSection = NULL;
	CIniKey *pIniKey = NULL;
	pIniSection = GetSection(strSectionName);

	if (pIniSection != NULL)
	{
		pIniKey = pIniSection->GetKey(strKeyName);
	}
	if (pIniKey != NULL)
	{
		return pIniKey->m_strKeyValue;
	}
	else
	{
		return _T("");
	}
}

CString CIniFile::GetKeyValue(const char *pszSectionName,const char *pszKeyName)
{
	ASSERT (pszSectionName != NULL && pszKeyName != NULL);
	return GetKeyValue(CString(pszSectionName), CString(pszKeyName));
}

//ͨ��Section���ơ�Key���ƻ�ȡKey����
CIniKey* CIniFile::GetKey(const CString &strSectionName,const CString &strKeyName)
{
	CIniSection *pIniSection = NULL;
	CIniKey *pIniKey = NULL;

	pIniSection = GetSection(strSectionName);
	if (pIniSection != NULL)
	{
		pIniKey = pIniSection->GetKey(strKeyName);
	}

	return pIniKey;
}

CIniKey* CIniFile::GetKey(const char *pszSectionName,const char *pszKeyName)
{
	ASSERT(pszSectionName != NULL && pszKeyName != NULL);
	return GetKey(CString(pszSectionName), CString(pszKeyName));
}

//�����µ�Key
CIniKey* CIniFile::InsertKey(const CString &strSectionName,const CString &strKeyName,const CString &strKeyValue)
{
	CIniSection *pIniSection = NULL;
	CIniKey *pIniKey = NULL;
	
	pIniSection = GetSection(strSectionName);
	if (pIniSection == NULL)
	{
		pIniSection= new CIniSection(strSectionName);
		AddTail(pIniSection);
	}

	pIniKey = pIniSection->InsertKey(strKeyName,strKeyValue);
	
	return pIniKey;	
}

CIniKey* CIniFile::InsertKey(const char *pszSectionName,const char *pszKeyName,const char *pszKeyValue)
{
	ASSERT(pszSectionName != NULL && pszKeyName != NULL && pszKeyValue != NULL);
	return InsertKey(CString(pszSectionName), CString(pszKeyName), CString(pszKeyValue));
}

//ɾ��Key
BOOL CIniFile::DeleteKey(const CString &strSectionName,const CString &strKeyName)
{
	CIniSection *pIniSection = NULL;
	CIniKey *pIniKey = NULL;

	pIniSection = GetSection(strSectionName);

	if (pIniSection != NULL)
	{
		pIniSection->DeleteKey(strKeyName);
	}

	return TRUE;
}

BOOL CIniFile::DeleteKey(const char *pszSectionName,const char *pszKeyName)
{
	CString strSectionName, strKeyName;
	strSectionName = pszSectionName;
	strKeyName = pszKeyName;

	ASSERT (pszSectionName != NULL && pszKeyName != NULL);

	return DeleteKey(strSectionName, strKeyName);
}


BOOL CIniFile::SetIniFile(const CString &strFile)
{	
	//���
	DeleteAll();

	CIniSection *pSection = NULL;

	CIniFileBuffer buffIniFile;
	CString strSectionName("");
	CString strKeyName("");
	CString strKeyValue("");

	m_strIniFile = strFile;

	buffIniFile.EnableFormartAllChar(false);

	if (!buffIniFile.ReadFromFile(strFile))
	{
		return FALSE;
	}
	
	while (TRUE)
	{
		if (buffIniFile.IsCurrStringASection())
		{
			buffIniFile.GetIniSection(strSectionName);
			strSectionName.TrimLeft();
			strSectionName.TrimRight();
			
			//Section�����Ƶĳ��ȱ������0
			if (strSectionName.GetLength() > 0)
			{
				pSection = new CIniSection(strSectionName);
				AddTail(pSection);
			}
			else
			{
				pSection = NULL;
			}
		}
		else if (buffIniFile.IsCurrStringAKey())
		{
			buffIniFile.GetIniKey(strKeyName,strKeyValue);
			strKeyName.TrimLeft();
			strKeyName.TrimRight();

			if (pSection)
			{
				pSection->InsertKey(strKeyName, strKeyValue);
			}
		}
		else
		{
			break;
		}
	}
		
	return TRUE;
}


//����ini�ļ�
void CIniFile::Save()
{
	CFile file;
	if(!file.Open(m_strIniFile,CFile::modeWrite | CFile::modeCreate))
	{
		return;
	}
	
	Save(&file);

	file.Close();
}

void CIniFile::SaveAs(CString &strFile)
{
	CFile file;
	if(!file.Open(strFile,CFile::modeWrite | CFile::modeCreate))
	{
		return;
	}

	Save(&file);
	
	file.Close();	
}

void CIniFile::Save(CFile *pFile)
{
	CIniSection *pIniSection	= NULL;
	
	POS pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pIniSection = (CIniSection*)GetNext(pos);
		pIniSection->Save(pFile);
	}		
}

void CIniFile::Save(CString &strData)
{
	CString strTemp	;
	CIniSection *pIniSection	= NULL;
	
	POS pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pIniSection = (CIniSection*)GetNext(pos);
		strTemp = "";
		pIniSection->Save(strTemp);
		strData += strTemp;
	}	
}

//ͨ��Section���ƻ�ȡSection����
CIniSection* CIniFile::GetSection(const CString &strSectionName)
{
	CIniSection *pIniSection = NULL;
	CIniSection *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pIniSection = (CIniSection *)GetNext(pos);
		
		if (pIniSection->GetSectionName() == strSectionName)
		{
			pFind = pIniSection;
			break;
		}		
	}

	return pFind;
}

CIniSection* CIniFile::GetSection(const char *pszSectionName)
{
	ASSERT (pszSectionName != NULL);
	CString strSectionName(pszSectionName);
	return GetSection(strSectionName);
}

CIniSection* CIniFile::operator[](const CString &strSectionName)
{
	return GetSection(strSectionName);	
}

CIniSection* CIniFile::operator[](const char *pszSectionName)
{
	return GetSection(pszSectionName);
}

//�����µ�Section����
CIniSection* CIniFile::InsertSection(const CString &strSectionName)
{
	CIniSection *pIniSection = NULL;

	pIniSection = GetSection(strSectionName);
	if (pIniSection != NULL)
	{
		return pIniSection;
	}

	pIniSection = new CIniSection(strSectionName);
	AddTail(pIniSection);

	return pIniSection;
}

CIniSection* CIniFile::InsertSection(const char *pszSectionName)
{
	ASSERT(pszSectionName != NULL);

	CString strSectionName;
	strSectionName = pszSectionName;

	return InsertSection(strSectionName);
}

//ɾ��Section����
BOOL CIniFile::DeleteSection(const CString &strSectionName)
{
	CIniSection *pIniSection = NULL;
	pIniSection = GetSection(strSectionName);
	if (pIniSection != NULL)
	{
		POS pos = Find(pIniSection);
		RemoveAt(pos);
		delete pIniSection;
	}

	return TRUE;
}

BOOL CIniFile::DeleteSection(const char *pszSectionName)
{
	ASSERT(pszSectionName != NULL);
	CString strSectionName(pszSectionName);
	return DeleteSection(strSectionName);
}

//Ϊͨ��Section��������ȡSection�����ṩ�Ľӿ�
long CIniFile::GetSectionCount()
{
	long lCount = GetCount();

	return lCount;
}

CIniSection* CIniFile::GetSection(long lIndex)
{	
	CIniSection* pIniSection = NULL;
	long l = 0, lCount = GetSectionCount();
	POS pos = GetHeadPosition();
	
	if (lIndex < 0 || lIndex >= lCount)
	{
		return NULL;
	}
	
	while (pos != NULL)
	{
		pIniSection = (CIniSection *)GetNext(pos);
		
		if (l == lIndex)
		{
			return pIniSection;
		}	
		
		l++;
	}
		
	return NULL;
}

CIniSection* CIniFile::operator[](long lIndex)
{
	return GetSection(lIndex);	
}
