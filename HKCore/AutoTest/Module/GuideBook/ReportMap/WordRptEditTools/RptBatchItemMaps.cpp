//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptBatchItemMaps.cpp  CRptBatchItemMaps


#include "stdafx.h"
#include "RptBatchItemMaps.h"

CRptBatchItemMaps::CRptBatchItemMaps()
{
	//��ʼ������

	//��ʼ����Ա����
}

CRptBatchItemMaps::~CRptBatchItemMaps()
{
}

long CRptBatchItemMaps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptBatchItemMaps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CRptBatchItemMaps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptBatchItemMapKey)
	{
		pNew = new CRptBatchItemMap();
	}

	return pNew;
}

CExBaseObject* CRptBatchItemMaps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == RBACLASSID_CRPTBATCHITEMMAP)
	{
		pNew = new CRptBatchItemMap();
	}

	return pNew;
}

void CRptBatchItemMaps::ClearMaps()
{
	POS pos = GetHeadPosition();
	CRptBatchItemMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CRptBatchItemMap *)GetNext(pos);
		pMap->ClearMap();
	}
}

CExBaseObject* CRptBatchItemMaps::GetFirstMapItem()
{
	POS pos = GetHeadPosition();
	CRptBatchItemMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CRptBatchItemMap *)GetNext(pos);
		
		if (pMap->m_pItemRef != NULL)
		{
			return pMap->m_pItemRef;
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//
CRptBatchItemMapsListCtrl::CRptBatchItemMapsListCtrl()
{

}

CRptBatchItemMapsListCtrl::~CRptBatchItemMapsListCtrl()
{

}

void CRptBatchItemMapsListCtrl::InitCollumns()
{
	CExBaseListListCtrl::InitCollumns();
}

void CRptBatchItemMapsListCtrl::UpdateListCtrl(CExBaseObject *pObj, long nIndex)
{
	CExBaseListListCtrl::UpdateListCtrl(pObj, nIndex);
}


