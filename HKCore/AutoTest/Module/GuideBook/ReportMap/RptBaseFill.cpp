#include "stdafx.h"
#include "RptBaseFill.h"

CRptBaseFill::CRptBaseFill(void)
{
	m_pGuideBook = NULL;
	//m_nMatchCount = 0;
}

CRptBaseFill::~CRptBaseFill(void)
{
}

CValue* CRptBaseFill::FindRptValueByID(const CString &strPath)
{

	return NULL;
}

CValue* CRptBaseFill::FindRptDataByPath(const CString &strPath)
{
	if (strPath.GetLength() == 0)
	{
		return NULL;
	}

	if(m_pGuideBook == NULL)
	{
		return NULL;
	}

	if (strPath.GetAt(0) == '$')
	{
		return FindRptData(m_pGuideBook, strPath.Mid(1));
	}

	//只处理一个Device
	CDevice *pDevice = m_pGuideBook->GetDevice();
	long nPos = MatchID(pDevice, strPath);

	if (nPos > 0)
	{
		return FindRptDataByPath(pDevice, strPath.Mid(nPos));
	}
	else
	{
		return FindRptDataByPath(pDevice, strPath);
	}
}

long CRptBaseFill::MatchID(CGbItemBase *pCurrItem, const CString &strPath)
{
// 	m_nMatchCount++;
// 
// 	if (m_nMatchCount >= 15120)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("+++++++MatchID ++++ %d"), m_nMatchCount);
// 	}

	CString strID = pCurrItem->m_strID;
	strID += _T("$");

	if (strPath.GetLength() < strID.GetLength())
	{
		return -1;
	}

	if (strID == strPath.Left(strID.GetLength()))
	{
		return strID.GetLength();
	}
	else
	{
		return -1;
	}
}

CValue* CRptBaseFill::FindRptDataByPath(CGbItemBase *pCurrItem, const CString &strPath)
{
	POS pos = pCurrItem->GetHeadPosition();
	CExBaseObject *p = NULL;
	CString strID;
	long nPos = 0;
	CValue *pFind = NULL;
	CString strPath2;
	long nSubItemCount = 0;

	while (pos != NULL)
	{
		p = pCurrItem->GetNext(pos);

		if (! Gb_IsItemBaseClassID(p->GetClassID()))
		{
			continue;
		}

		nSubItemCount++;
		nPos = MatchID((CGbItemBase*)p, strPath);

		if (nPos < 0)
		{
			continue;
		}

		strPath2 = strPath.Mid(nPos);
		pFind = FindRptDataByPath((CGbItemBase*)p, strPath2);

		if (pFind == NULL)
		{//没有找到，就在项目p中查找报告数据
			return FindRptData((CGbItemBase*)p, strPath2);
		}
		else
		{
			return pFind;
		}
	}

	if (nSubItemCount == 0)
	{//没有子项目，则表示可能是根节点，查找报告数据
		return FindRptData(pCurrItem, strPath);
	}
	else
	{
		return NULL;
	}
}

CValue* CRptBaseFill::FindRptData(CGbItemBase *pCurrItem, const CString &strPath)
{
	CReport *pReport = pCurrItem->GetReport(-1);

	if (pReport == NULL)
	{
		return NULL;
	}

	return (CValue*)pReport->m_pValues->FindByID(strPath);
}

