#include "StdAfx.h"
#include "PdfTextParse.h"
#include "PdfFileToText.h"

CPdfTextParse::CPdfTextParse()
{
	m_nKeyCount = 0;
	memset(m_ppszGlobalKey, 0, PDEF_PARSE_MAX_KEY_COUNT*24);
	m_nInvalidKeyCount = 0;
	memset(m_ppszInvalidGlobalKey, 0, PDEF_PARSE_MAX_KEY_COUNT*24);
	m_nFormatKeyCount = 0;
	memset(m_ppszFormatGlobalKey, 0, PDEF_PARSE_MAX_KEY_COUNT*24);
	m_nMergeKeyCount = 0;
	memset(m_ppszMergeGlobalKey, 0, PDEF_PARSE_MAX_KEY_COUNT*24);
}

CPdfTextParse::~CPdfTextParse()
{
}

BOOL CPdfTextParse::ParsePdfFile(const CString &strFile, BOOL bSaveTxtFile)
{
	CExpandMemBuf oBuffer;
	const char *pszFile = strFile.GetString();

	if (!PdfToText(pszFile, oBuffer))
	{
		return FALSE;
	}

	BYTE pszBuff[5] = {0};
	oBuffer.AppendBuffer(pszBuff, 5);

	if (bSaveTxtFile)
	{
		CString strTemp;
		strTemp = ChangeFilePostfix(strFile, _T("txt"));
		CFile oFile;

		if (oFile.Open(strTemp, CFile::modeCreate | CFile::modeWrite))
		{
			oFile.Write(oBuffer.GetBuffer(), oBuffer.GetDataLength());
			oFile.Close();
		}
	}

	Parse(&oBuffer);


	return TRUE;
}

void CPdfTextParse::ProcessTextData()
{
	CPdfTextLine *pLine = NULL;
	POS pos = GetHeadPosition();
	CString strKey;

	while (pos != NULL)
	{
		pLine = (CPdfTextLine *)GetNext(pos);

		if (IsLineDatasetTitle(pLine, strKey))
		{
			break;
		}

		ProcessTextData(pLine);
	}
}

void CPdfTextParse::ProcessTextData(CPdfTextLine *pLine)
{
	POS pos = pLine->GetHeadPosition();
	CPdfTextData *pData = NULL;
	CPdfTextData *pNew = NULL;
	POS posCurr = NULL;

	while (pos != NULL)
	{
		posCurr = pos;
		pData = (CPdfTextData *)pLine->GetNext(pos);
		pNew = ProcessTextData(pData);

		if (pNew != NULL)
		{
			pos = pLine->InsertAfter(posCurr, pNew);
		}
	}
}

CPdfTextData* CPdfTextParse::ProcessTextData(CPdfTextData *pData)
{
	long nIndex = 0;
	long nPos = -1;
	CString strKey;

	for (nIndex=0; nIndex<m_nKeyCount; nIndex++)
	{
		nPos = pData->m_strName.Find(m_ppszGlobalKey[nIndex]);

		if (nPos >= 0)
		{
			strKey = m_ppszGlobalKey[nIndex];
			break;
		}
	}

	if (nPos < 0)
	{
		return NULL;
	}

	if (nPos == 0)
	{
		pData->TrimRight();
		return NULL;
	}

	//厂站名称: 晨阳站母线PT变比: 220000/1.732:100/1.732:100 保护型号: CSC-103A-DA-G-RPLD
	//前面的为值
	CString strNext = pData->m_strName.Mid(nPos);
	pData->m_strName = pData->m_strName.Left(nPos);
	CPdfTextData *pNew = new CPdfTextData();
	pNew->m_strName = strNext;

	return pNew;
}

BOOL CPdfTextParse::IsKey(const CString &strText)
{
	long nIndex = 0;
	for (nIndex=0; nIndex<m_nKeyCount; nIndex++)
	{
		if(strText == m_ppszGlobalKey[nIndex])
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CPdfTextParse::FormatEx(CBufferBase *pBuffer)
{
	
}

void CPdfTextParse::Parse(CExpandMemBuf *pBuffer)
{
	CBufferBase oBuffer;
	oBuffer.Attatch((char*)pBuffer->GetBuffer());
	oBuffer.FormatBuffer('\r', 0);
	oBuffer.FormatBuffer('\n', 0);
	
	//格式化
	long nIndex = 0;
	for (nIndex=0; nIndex<m_nFormatKeyCount; nIndex++)
	{
		oBuffer.FormatBuffer(m_ppszFormatGlobalKey[nIndex], 0);
	}

	FormatEx(&oBuffer);

	oBuffer.ResetPointer();

	char *pszLine = oBuffer.GetString();
	char *pszNext = NULL;
	CPdfTextLine *pLine = NULL;

	while (oBuffer.IsPoiterInBuffer(pszLine))
	{
		pLine = new CPdfTextLine(pszLine);
		pszNext = oBuffer.NextString();
		AddNewChild(pLine);
		pszLine = pszNext;
	}

	//去掉无效的字符
	for (nIndex=0; nIndex<m_nInvalidKeyCount; nIndex++)
	{
		oBuffer.FormatBuffer(m_ppszInvalidGlobalKey[nIndex], 0);
	}

	//处理
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pLine = (CPdfTextLine*)GetNext(pos);
		pLine->Formart();
	}

	ProcessTextData();
}

void CPdfTextParse::OpenKeyTextFile(const CString &strFile)
{
	OpenKeyTextFile(strFile, m_ppszGlobalKey, m_nKeyCount);
}

void CPdfTextParse::OpenInvalidKeyTextFile(const CString &strFile)
{
	OpenKeyTextFile(strFile, m_ppszInvalidGlobalKey, m_nInvalidKeyCount);
}

void CPdfTextParse::OpenFormatKeyTextFile(const CString &strFile)
{
	OpenKeyTextFile(strFile, m_ppszFormatGlobalKey, m_nFormatKeyCount);
}

void CPdfTextParse::OpenMergeKeyTextFile(const CString &strFile)
{
	OpenKeyTextFile(strFile, m_ppszMergeGlobalKey, m_nMergeKeyCount);
}

void CPdfTextParse::OpenKeyTextFile(const CString &strFile, char ppKey[PDEF_PARSE_MAX_KEY_COUNT][24], long &nKeyCount)
{
	CString strTemp;
	strTemp = _P_GetConfigPath();
	strTemp += strFile;

	CBufferBase oBuffer;
	oBuffer.ReadFromFile(strTemp);
	oBuffer.FormatBuffer('\r');
	oBuffer.FormatBuffer('\n');

	char *pszString = oBuffer.GetString();

	while (pszString != NULL)
	{
		strcpy(ppKey[nKeyCount], pszString);
		pszString = oBuffer.NextString();
		nKeyCount++;
	}
}

