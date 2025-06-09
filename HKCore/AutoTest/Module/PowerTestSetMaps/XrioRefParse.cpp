#include "StdAfx.h"
#include "XrioRefParse.h"
#include "..\XrioRead\XrioCustomBlock.h"
#include "..\XrioRead\XrioCustomParameter.h"

CXrioRefParse::CXrioRefParse(void)
{
	m_nCurrParsePos = 0;
}

CXrioRefParse::~CXrioRefParse(void)
{
}

BOOL CXrioRefParse::ReadFromRefFile(CPowerTestSetMaps *pPtMaps,const CString &strFile)
{
	ASSERT(pPtMaps);

	if (!m_oBuffer.ReadFromFile(strFile))
	{
		return FALSE;
	}

	pPtMaps->DeleteAll();
 	Parse_Xrio_Ref(pPtMaps,m_oBuffer.GetBufferBeginPos(), m_oBuffer.GetLength());
	return TRUE;
}

void CXrioRefParse::Offset()
{
	char *pHeadPos = m_oBuffer.GetBufferBeginPos();

	if (m_nCurrParsePos >= m_oBuffer.GetLength())
	{
		return;
	}

	char chCurr = pHeadPos[m_nCurrParsePos];

	while (chCurr == VK_SPACE || chCurr == VK_TAB || chCurr == '\r' || chCurr == '\n')
	{
		m_nCurrParsePos++;
		chCurr = pHeadPos[m_nCurrParsePos];
	}
}

BOOL CXrioRefParse::GetRootBlockID(CPowerTestSetMaps *pPtMaps)
{
	char *pHeadPos = m_oBuffer.GetBufferBeginPos();
	char *pCurPos = NULL;
	pCurPos = pHeadPos+m_nCurrParsePos;
	Offset();

	if (strstr(pCurPos,"Block Id") != pCurPos)
	{
		return FALSE;
	}

	m_nCurrParsePos += 8;
	Offset();

	pCurPos = pHeadPos+m_nCurrParsePos;
	char chCurr = pHeadPos[m_nCurrParsePos];

	while ((chCurr != '\r') && (chCurr != '\n'))
	{
		m_nCurrParsePos++;
		chCurr = pHeadPos[m_nCurrParsePos];
	}

	CStringA strRootBlockID;
	strRootBlockID.SetString(pCurPos ,(pHeadPos+m_nCurrParsePos-pCurPos));
	pPtMaps->m_strID = strRootBlockID;
	pPtMaps->m_strName = pPtMaps->m_strID;
	return TRUE;
}

BOOL CXrioRefParse::Parse_Xrio_Ref(CPowerTestSetMaps *pPtMaps,char *_pTplBuff, long nLen)
{
//	char chCurr;
	m_nCurrParsePos = 0;

	//跳过无效字符
	GetRootBlockID(pPtMaps);
	Offset();

	while(m_nCurrParsePos<nLen)
	{
		GetCurLineMapObj(pPtMaps);
		m_nCurrParsePos+=2;
		Offset();
	}

	return TRUE;
}

BOOL CXrioRefParse::GetCurLineMapObj(CPowerTestSetMaps *pPtMaps)
{
	CStringA strPTName,strXRIOName,strForeignID;

	if (!GetSettingName(strPTName))
	{
		return FALSE;
	}

	m_nCurrParsePos++;

	if (!GetSettingName(strXRIOName))
	{
		return FALSE;
	}

	if (!GetForeignId(strForeignID))
	{
		return FALSE;
	}

	CSetMap *pSetMap = new CSetMap;
	pSetMap->m_strName = strPTName;
	pSetMap->m_strID = strForeignID;
	pSetMap->m_strMap = strXRIOName;
	pPtMaps->AddNewChild(pSetMap);

	return TRUE;
}

BOOL CXrioRefParse::GetSettingName(CStringA &strName)
{
	char *pSettingNameHead = m_oBuffer.GetBufferBeginPos() + m_nCurrParsePos;
	char *pCurrPos = pSettingNameHead;

	while((*pCurrPos != ',')&&(*pCurrPos != ';'))
	{
		pCurrPos++;

		if (!m_oBuffer.IsPoiterInBuffer(pCurrPos))
		{
			return FALSE;
		}
	}

	long nLenth = pCurrPos- pSettingNameHead;
	m_nCurrParsePos += nLenth;
	strName.SetString(pSettingNameHead,nLenth);
	strName.Trim();

	return TRUE;
}

BOOL CXrioRefParse::GetForeignId(CStringA &strForeignId)
{
	char *pSettingNameHead = m_oBuffer.GetBufferBeginPos() + m_nCurrParsePos;

	if (*pSettingNameHead == ';')
	{
		return TRUE;
	}

	m_nCurrParsePos++;
	pSettingNameHead++;
	char *pCurrPos = pSettingNameHead;

	while((*pCurrPos != ',')&&(*pCurrPos != ';'))
	{
		pCurrPos++;

		if (!m_oBuffer.IsPoiterInBuffer(pCurrPos))
		{
			return FALSE;
		}
	}

	if (*pCurrPos == ',')
	{
		return FALSE;
	}

	long nLenth = pCurrPos- pSettingNameHead;
	m_nCurrParsePos += nLenth;
	strForeignId.SetString(pSettingNameHead,nLenth);
	strForeignId.Trim();

	return TRUE;
}

//BOOL CXrioRefParse::TransRefPathToFullPath(CXrioCustom *pXrioCustom)
//{
//	CSetMap *pSetMap = NULL;
//	CXrioCustomBlock *pCustomBlock = (CXrioCustomBlock*)pXrioCustom->FindByID(m_pPtMaps->m_strID);
//	CXrioCustomParameter *pParameter = NULL;
//	CString strMSG;
//
//	if (pCustomBlock == NULL)
//	{
//		return FALSE;
//	}
//
//	POS pos_map = m_pPtMaps->GetHeadPosition();
//
//	while(pos_map)
//	{
//		pSetMap = (CSetMap *)m_pPtMaps->GetNext(pos_map);
//		pParameter = (CXrioCustomParameter*)pCustomBlock->FindParaByName(pSetMap->m_strMap,pSetMap->m_strID);
//
//		if (pParameter == NULL)
//		{
//			strMSG.Format(_T("参数(%s)在XRIO文件中未找到."),pSetMap->m_strMap);
//			AfxMessageBox(strMSG);
//			continue;
//		}
//
//		pParameter->GetParameterFullPath(pSetMap->m_strMap); 
//	}
//
//	m_bHasMap = TRUE;
//	return TRUE;
//}



