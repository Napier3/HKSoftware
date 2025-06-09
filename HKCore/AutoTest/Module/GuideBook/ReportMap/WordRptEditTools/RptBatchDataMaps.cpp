//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptBatchDataMaps.cpp  CRptBatchDataMaps


#include "stdafx.h"
#include "RptBatchDataMaps.h"
#include "..\..\..\XLanguageResourceAts.h"

CRptBatchDataMaps::CRptBatchDataMaps()
{
	//��ʼ������

	//��ʼ����Ա����
}

CRptBatchDataMaps::~CRptBatchDataMaps()
{
}

long CRptBatchDataMaps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptBatchDataMaps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CRptBatchDataMaps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptBatchDataMapKey)
	{
		pNew = new CRptBatchDataMap();
	}

	return pNew;
}

CExBaseObject* CRptBatchDataMaps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == RBACLASSID_CRPTBATCHDATAMAP)
	{
		pNew = new CRptBatchDataMap();
	}

	return pNew;
}


void CRptBatchDataMaps::ClearMaps()
{
	POS pos = GetHeadPosition();
	CRptBatchDataMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CRptBatchDataMap *)GetNext(pos);
		pMap->ClearMap();
	}
}



//////////////////////////////////////////////////////////////////////////
//
CRptBatchDataMapsListCtrl::CRptBatchDataMapsListCtrl()
{
	m_pBkmkDataProcessMngr = NULL;
}

CRptBatchDataMapsListCtrl::~CRptBatchDataMapsListCtrl()
{

}

void CRptBatchDataMapsListCtrl::InitCollumns()
{
	InsertColumn(LIST_COL_INDEX,g_sLangTxt_Index/*_T("���")*/,LVCFMT_LEFT,40);
	InsertColumn(LIST_COL_NAME,g_sLangTxt_Name/*_T("����")*/,LVCFMT_LEFT,100);
	InsertColumn(LIST_COL_ID,_T("ID"),LVCFMT_LEFT,50);
	InsertColumn(RPTBATCH_DATA_COL_ATTR,g_sLangTxt_Atrribute/*_T("����")*/,LVCFMT_LEFT,50);
	InsertColumn(RPTBATCH_DATA_COL_REPEAT,g_sLangTxt_Times/*_T("����")*/,LVCFMT_LEFT,50);
	InsertColumn(RPTBATCH_DATA_COL_PROCESS,g_sLangTxt_DataPro/*_T("���ݴ���")*/,LVCFMT_LEFT,100);
}

void CRptBatchDataMapsListCtrl::UpdateListCtrl(CExBaseObject *pObj, long nIndex)
{
	CExBaseListListCtrl::UpdateListCtrl(pObj, nIndex);
	CString strText;

	CRptBatchDataMap *pDataMap = (CRptBatchDataMap*)pObj;
	SetItemText(nIndex, RPTBATCH_DATA_COL_ATTR, pDataMap->m_strDataAttr);
	
	strText.Format(_T("%d"), pDataMap->m_nRepeatIndex);
	SetItemText(nIndex, RPTBATCH_DATA_COL_REPEAT, strText);

	ASSERT (m_pBkmkDataProcessMngr != NULL);
	CBkmkDataProcess *p = (CBkmkDataProcess*)m_pBkmkDataProcessMngr->FindByID(pDataMap->m_strDataProcess);
	strText.Empty();

	if (p != NULL)
	{
		strText = p->m_strName;
	}

	SetItemText(nIndex, RPTBATCH_DATA_COL_PROCESS, strText);
}


