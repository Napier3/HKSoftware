// XrioTextFile.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioTextFile.h"

//////////////////////////////////////////////////////////////////////////
//CXrioAttr
CXrioAttr::CXrioAttr(const char *pszText)
{
	m_strName = pszText;
}

CXrioAttr::~CXrioAttr()
{

}


//////////////////////////////////////////////////////////////////////////
//CXrioData
CXrioData::CXrioData(const char *pszText)
{
	m_strName = pszText;
}

CXrioData::~CXrioData()
{

}

CString CXrioData::GetAttr(long nIndex)
{
	CXrioAttr *pAttr = (CXrioAttr*)GetAtIndex(nIndex);

	if (pAttr == NULL)
	{
		return _T("");
	}
	else
	{
		return pAttr->m_strName;
	}
}

BOOL CXrioData::GetAttr(long nIndex, CString &strValue)
{
	CXrioAttr *pAttr = (CXrioAttr*)GetAtIndex(nIndex);

	if (pAttr == NULL)
	{
		return FALSE;
	}
	
	strValue = pAttr->m_strName;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//CXrioGroup
CXrioGroup::CXrioGroup(const char *pszText)
{
	m_strName = pszText;
}

CXrioGroup::~CXrioGroup()
{

}

CString CXrioGroup::GetData(const CString &strID)
{
	CString strValue;

	GetData(strID, strValue);

	return strValue;
}

BOOL CXrioGroup::GetData(const CString &strID, CString &strValue)
{
	CXrioData *pFind = (CXrioData*)FindByName(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->GetClassID() != XRIOCLASSID_RIO_DATA)
	{
		return FALSE;
	}

	CXrioAttr *pAttr = (CXrioAttr*)pFind->GetHead();

	if (pAttr == NULL)
	{
		return FALSE;
	}

	strValue = pAttr->m_strName;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//CXrioTextFile
CXrioTextFile::CXrioTextFile()
{

}

CXrioTextFile::~CXrioTextFile()
{

}

BOOL CXrioTextFile::ReadXrioTextFile(CWnd *pParentWnd)
{
	CString strXFileFilter, strXFilePostFix;
	strXFileFilter = RIO_TEXT_FILE_FILTER;
	strXFilePostFix = RIO_TEXT_FILE_POSTFIX;
	CString strRioFile;
	strRioFile = _P_GetInstallPath();
	strRioFile.AppendFormat(_T("*.%s"), RIO_TEXT_FILE_POSTFIX);

	if (!PopupOpenFileDialog(pParentWnd, strRioFile, strXFileFilter, strXFilePostFix))
	{
		return FALSE;
	}

	return ReadXrioTextFile(strRioFile);
}

BOOL CXrioTextFile::WriteXrioTextFile(CWnd *pParentWnd)
{
	return FALSE;
}

BOOL CXrioTextFile::ReadXrioTextFile(const CString &strTextFile)
{
	CBufferBase oBuffer;

	if ( ! oBuffer.ReadFromFile(strTextFile))
	{
		return FALSE;
	}

	m_strRioFile = strTextFile;
	DeleteAll();
	oBuffer.FormatBuffer('\r', 0);
	oBuffer.FormatBuffer('\n', 0);
	char *pszLine = oBuffer.GetString();
	pszLine = OffsetString(pszLine);
	char pszText[XRIO_TEXT_WORD_MAX_LEN];

	if ( ! ReadOneTextWord(&pszLine, pszText) )
	{
		return FALSE;
	}

	if (stricmp(pszText, "begin") != 0)
	{
		return FALSE;
	}

	if (!ReadOneTextWord(&pszLine, pszText))
	{
		return FALSE;
	}

	m_strName = pszText;
	ParseGroupChildren(oBuffer, this);
	
	return TRUE;
}

BOOL CXrioTextFile::WriteXrioTextFile(const CString &strTextFile)
{
	return FALSE;
}


void CXrioTextFile::ParseGroupChildren(CBufferBase &oBuffer, CXrioGroup *pGroup)
{
	if (!oBuffer.IsPoiterInBuffer())
	{
		return;
	}

	char pszText[XRIO_TEXT_WORD_MAX_LEN];

	while (TRUE)
	{
		char *pszLine = oBuffer.NextString();

		if (pszLine == NULL)
		{
			return;
		}

		if ( ! ReadOneTextWord(&pszLine, pszText) )
		{
			return;
		}

		if (stricmp(pszText, "begin") == 0)
		{
			if (!ReadOneTextWord(&pszLine, pszText))
			{
				return;
			}

			CXrioGroup *pNew = new CXrioGroup(pszText);
			pGroup->AddNewChild(pNew);
			ParseGroupChildren(oBuffer, pNew);
		}
		else if (stricmp(pszText, "end") == 0)
		{
			return;
		}
		else
		{
			CXrioData *pData = new CXrioData(pszText);
			pGroup->AddNewChild(pData);
			ParseData(pData, pszLine);
		}
	}
}

void CXrioTextFile::ParseData(CXrioData *pData, char *pszLine)
{
	Offset(&pszLine);
	char *pszEnd = pszLine + strlen(pszLine);
	char pszText[XRIO_TEXT_WORD_MAX_LEN];

	while (pszLine < pszEnd)
	{
		if ( ! ReadOneTextWord(&pszLine, pszText) )
		{
			return;
		}

		CXrioAttr *pNew = new CXrioAttr(pszText);
		pData->AddNewChild(pNew);
	}
}

BOOL CXrioTextFile::ReadOneTextWord(char **ppszLine, char *pszTextWord)
{
	Offset(ppszLine);
	char *p = *ppszLine;
	char *pDest = pszTextWord;
	long nStringSp = 0;

	if (*p == '"')
	{
		nStringSp = 1;
	}

	while (*p != 0)
	{
		if (nStringSp == 0)
		{
			if (*p == VK_SPACE || *p == VK_TAB || *p == ',')
			{
				break;
			}
		}
		else
		{
			if (*p == ',')
			{
				break;
			}
		}

		*pDest = *p;
		pDest++;
		p++;
	}

	*pDest = 0;
	*ppszLine = p;

	return (pDest - pszTextWord) > 0;
}

void CXrioTextFile::Offset(char **ppszLine)
{
	*ppszLine = OffsetString(*ppszLine);

	if (**ppszLine == ',')
	{
		*ppszLine = *ppszLine + 1;
		*ppszLine = OffsetString(*ppszLine);
	}
}

