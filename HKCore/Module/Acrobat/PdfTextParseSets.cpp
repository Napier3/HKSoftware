#include "StdAfx.h"
#include "PdfTextParseSets.h"
#include "..\BaseClass\XUnit.h"


CPdfTextParseSets::CPdfTextParseSets()
{
	//单位管理对象，定义一次，创建全局对象
	CXUnit oXUnits;
	m_bCan_ParseLine_attr = TRUE;
}

CPdfTextParseSets::~CPdfTextParseSets()
{
}

void CPdfTextParseSets::Parse(CExpandMemBuf *pBuffer)
{
	CPdfTextParse::Parse(pBuffer);

	m_pCurrDataset = new CDvmDataset();
	m_pCurrDataset->m_strName = _T("Attrs");
	m_pDestLogicDevice->AddNewChild(m_pCurrDataset);

	POS pos = GetHeadPosition();
	CPdfTextLine *pLine = NULL;

	while (pos != NULL)
	{
		pLine = (CPdfTextLine *)GetNext(pos);
		ParseLine(pLine);
	}
}

void CPdfTextParseSets::ParseLine(CPdfTextLine *pLine)
{
	CString strKey;

	if (IsLineDatasetTitle(pLine, strKey))
	{
		CString strTitle;
		strTitle = GetDatasetTitle(strKey);

		m_pCurrDataset = (CDvmDataset *)m_pDestLogicDevice->FindByName(strTitle);

		if (m_pCurrDataset == NULL)
		{
			m_pCurrDataset = new CDvmDataset();
			m_pCurrDataset->m_strName = strTitle;
			m_pDestLogicDevice->AddNewChild(m_pCurrDataset);
		}

		m_nDataIndex = 0;
		m_bCan_ParseLine_attr = FALSE;

		return;
	}

	if (pLine->GetCount() <= 1)
	{
		return;
	}

	if  (IsDatasetTitle(m_pCurrDataset->m_strName, strKey))
	{
		ParseLine_data(pLine);
	}
	else
	{
		ParseLine_attr(pLine);
	}
}

BOOL CPdfTextParseSets::IsDatasetTitle(const CString &strText, CString &strKey)
{
	long nCount = m_astrDatasetTitle.GetSize();
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strKey = m_astrDatasetTitle.GetAt(nIndex);

		if (strText.Right(strKey.GetLength()) == strKey)
		{
			return TRUE;
		}
	}

	strKey.Empty();
	return FALSE;
}

BOOL CPdfTextParseSets::IsLineDatasetTitle(CPdfTextLine *pLine, CString &strKey)
{
	CPdfTextData *pText = (CPdfTextData*)pLine->GetHead();

	if (pText == NULL)
	{
		return FALSE;
	}

	return IsDatasetTitle(pText->m_strName, strKey);
}

CString CPdfTextParseSets::GetDatasetTitle(const CString &strKey)
{
	long nCount = m_astrDatasetTitle.GetSize();
	long nIndex = 0;
	CString strTitle;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strTitle = m_astrDatasetTitle.GetAt(nIndex);

		if (strTitle.Find(strKey) >= 0)
		{
			return strTitle;
		}
	}

	return strKey;
}

void CPdfTextParseSets::ParseLine_attr(CPdfTextLine *pLine)
{
	if (!m_bCan_ParseLine_attr)
	{//属性，只解析一次
		return;
	}

	if (pLine->GetCount() == 1)
	{
		return;
	}

	long nCount = pLine->GetCount();
	long nIndex = 0;

	//暂时不考虑后面的异常    校验码: 2D2A 5288

	for (nIndex=0; nIndex<nCount; )
	{
		CPdfTextData *pText1 = (CPdfTextData*)pLine->GetAtIndex(nIndex);
		CPdfTextData *pText2 = (CPdfTextData*)pLine->GetAtIndex(nIndex+1);
		CPdfTextData *pText3 = (CPdfTextData*)pLine->GetAtIndex(nIndex+2);

		if (pText1 == NULL || pText2 == NULL)
		{
			break;
		}

		CDvmData *pData = new CDvmData();
		pData->m_strName = pText1->m_strName;
		m_pCurrDataset->AddNewChild(pData);
	
		if (IsKey(pText2->m_strName))
		{
			nIndex++;
		}
		else
		{
			if (pText3 != NULL)
			{
				if (IsKey(pText3->m_strName))
				{
					pData->m_strValue = pText2->m_strName;
					nIndex += 2;
				}
				else
				{
					pData->m_strValue = pText2->m_strName;
					pData->m_strValue += _T(" ");
					pData->m_strValue += pText3->m_strName;
					nIndex += 3;
				}
			}
			else
			{
				pData->m_strValue = pText2->m_strName;
				nIndex += 2;
			}
		}
	}
}

void CPdfTextParseSets::GetNameAndUnit(const CString &strText, CString &strName, CString &strUnit)
{
	long nIndex = 0;
	CString *pUnits = CXUnit::g_strXUnit;

	for (nIndex=0; nIndex<_XUNITS_MAX_COUNT_; nIndex++)
	{
		if (pUnits[nIndex].GetLength() == 0)
		{
			continue;
		}

		if (pUnits[nIndex] == strText.Right(pUnits[nIndex].GetLength()))
		{
			strName = strText.Left(strText.GetLength() - pUnits[nIndex].GetLength());
			strUnit = pUnits[nIndex];
			return;
		}
	}

	strName = strText;
}

void CPdfTextParseSets::GetNameUnitValue(const CString &strText, CString &strName, CString &strUnit, CString &strValue)
{
	long nLen = strText.GetLength();
	long nPos = 0;
	BOOL bHasValue = FALSE;
	TCHAR ch;

	for (nPos=nLen-1; nPos> 0; nPos--)
	{
		ch = strText.GetAt(nPos);

		if ( ('0' <= ch && ch <= '9') || (ch=='.') )
		{
			bHasValue = TRUE;
		}
		else
		{
			break;
		}
	}

	CString strTemp;
	if (bHasValue)
	{
		strValue = strText.Mid(nPos+1);
		strTemp = strText.Left(nPos+1);
	}
	else
	{
		strTemp = strText;
	}

	GetNameAndUnit(strTemp, strName, strUnit);
}

//序号符号名称单位原定值现定值
//9 DO08 本侧小电抗器阻抗定值Ω 9000.00
void CPdfTextParseSets::ParseLine_data_prev(CPdfTextLine *pLine)
{
	
}

void CPdfTextParseSets::ParseLine_data(CPdfTextLine *pLine)
{
	if (pLine->GetCount() < 3)
	{
		return;
	}

	long nBeginIndex = 0;

	CPdfTextData *pTextIndex = (CPdfTextData*)pLine->GetAtIndex(nBeginIndex);
	
	if (! IsStringNumber(pTextIndex->m_strName))
	{
		return;
	}

	ParseLine_data_prev(pLine);

	CPdfTextData *pTextID = (CPdfTextData*)pLine->GetAtIndex(nBeginIndex+1);
	CPdfTextData *pTextName = (CPdfTextData*)pLine->GetAtIndex(nBeginIndex+2);
	CPdfTextData *pTextValue = (CPdfTextData*)pLine->GetAtIndex(nBeginIndex+3);
	CPdfTextData *pTextValue2 = (CPdfTextData*)pLine->GetAtIndex(nBeginIndex+4);
	CString strName, strUnit, strValue;

	 if ( pTextName == NULL)
	 {
		 return;
	 }

	 if (pTextID->m_strName == _T("DO49"))
	 {
		 int i = 0;
	 }

	CString strIndex;
	m_nDataIndex = CString_To_long(pTextIndex->m_strName);

// 	if (pTextValue == NULL)
// 	{
// 		CDvmData *pData = new CDvmData();
// 		m_pCurrDataset->AddNewChild(pData);
// 		GetNameUnitValue(pTextName->m_strName, pData->m_strName, pData->m_strUnit, pData->m_strValue);
// 		return;
// 	}

	CDvmData *pData = new CDvmData();
	m_pCurrDataset->AddNewChild(pData);

NewDataParse:
	pData->m_strID = pTextID->m_strName;

	if (pTextID->m_strName == _T("DO49"))
	{
		int i = 0;
	}

	if (pTextValue == NULL)
	{
		GetNameUnitValue(pTextName->m_strName, pData->m_strName, pData->m_strUnit, pData->m_strValue);
		return;
	}

	if (MergeName(pTextName, pTextValue))
	{
		pTextValue = pTextValue2;
		pTextValue2 = (CPdfTextData*)pLine->GetAtIndex(nBeginIndex+5);
	}

	GetNameAndUnit(pTextName->m_strName, pData->m_strName, pData->m_strUnit);
	CString strIndexNext;
	strValue = GetValue(m_nDataIndex, pTextValue, pTextValue2, strIndexNext);
	pData->m_strValue = strValue;

	if (pLine->GetCount() < nBeginIndex+7)
	{
		//pData->m_strValue = strValue;
		return;
	}

	strIndex.Format(_T("%d"), m_nDataIndex+1);

	if (strIndex != strIndexNext)//strValue.Right(strIndex.GetLength()))
	{
		//pData->m_strValue = strValue;
		return;
	}

	//pData->m_strValue = strValue.Left(strValue.GetLength() - strIndex.GetLength());
	
	//获得下一个Index
	nBeginIndex = pLine->FindIndex(pTextValue);
	CPdfTextData *pTemp = (CPdfTextData*)pLine->GetAt(nBeginIndex);

	while (pTemp != NULL)
	{
		if (!IsStringNumber(pTemp->m_strName))
		{
			break;
		}

		nBeginIndex++;
		pTemp = (CPdfTextData*)pLine->GetAt(nBeginIndex);
	}

	pTextID = (CPdfTextData*)pLine->GetAtIndex(nBeginIndex+0);
	pTextName = (CPdfTextData*)pLine->GetAtIndex(nBeginIndex+1);
	pTextValue = (CPdfTextData*)pLine->GetAtIndex(nBeginIndex+2);
	pTextValue2 = (CPdfTextData*)pLine->GetAtIndex(nBeginIndex+3);

	if (pTextID == NULL || pTextName == NULL)
	{
		return;
	}
	
	pData = new CDvmData();
	m_pCurrDataset->AddNewChild(pData);

	goto NewDataParse;
}

CString CPdfTextParseSets::GetValue(long nIndex, CPdfTextData *pTextValue, CPdfTextData *pTextValue2, CString &strIndexNext)
{
	strIndexNext.Empty();

	if (pTextValue2 == NULL)
	{
		long nPos = pTextValue->m_strName.Find(' ');
	
		if ( nPos > 0)
		{
			return pTextValue->m_strName.Mid(nPos+1);
		}

		return pTextValue->m_strName;
	}

	if (pTextValue2->m_strName.Find(_T("默认")) >= 0)
	{
		return pTextValue->m_strName;
	}
	else
	{
		CString strTemp;
		strTemp.Format(_T("%d"), nIndex+1);
		long nLen = strTemp.GetLength();

		if (pTextValue->m_strName.Right(nLen) == strTemp)
		{//粘连到Value1情况处理
			long nLeft = pTextValue->m_strName.GetLength() - nLen;
			CString strRet = pTextValue->m_strName.Left(nLeft);
			strIndexNext = strTemp;
			return strRet;
		}

		if (pTextValue2->m_strName.Right(nLen) == strTemp)
		{//粘连到Value2情况处理
			long nLeft = pTextValue2->m_strName.GetLength() - nLen;
			CString strRet = pTextValue2->m_strName.Left(nLeft);
			strIndexNext = strTemp;
			return strRet;
		}


		if (pTextValue2->m_strName.GetLength() > 0)
		{
			return pTextValue2->m_strName;
		}
		
		return pTextValue->m_strName;
	}
}

BOOL CPdfTextParseSets::MergeName(CPdfTextData *pTextName, CPdfTextData *pTextValue)
{
	if (CanMergeName(pTextName))
	{
		pTextName->m_strName += pTextValue->m_strName;
		return TRUE;
	}

	return FALSE;
}

BOOL CPdfTextParseSets::CanMergeName(CPdfTextData *pTextName)
{
	long  nIndex = 0;
	long nLen = 0;

	for (nIndex=0; nIndex<m_nMergeKeyCount; nIndex++)
	{
		nLen = strlen(m_ppszMergeGlobalKey[nIndex]);

		if (pTextName->m_strName.Right(nLen) == m_ppszMergeGlobalKey[nIndex])
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CPdfTextParseSets::FormatEx(CBufferBase *pBuffer)
{
	FormatEx_Degree(pBuffer);
}

void CPdfTextParseSets::FormatEx_Degree(CBufferBase *pBuffer)
{
	char pszDegree[6];
	strcpy(pszDegree, "角度");

	char *pBegin = pBuffer->GetBufferBeginPos();
	char *pEnd = pBuffer->GetBufferEndPos() - 4;

	while (pBegin < pEnd)
	{
		if (memcmp(pBegin, pszDegree, 4) == 0)
		{
			if (pBegin[5] > 0)
			{//避免处理类似    44 DO49 固定角度差定值度0    这类的异常处理
				pBegin[2] = ' ';
				pBegin[3] = ' ';
			}

			pBegin += 4;
		}
		else
		{
			pBegin++;
		}
	}
}

