#include "stdafx.h"
#include "GbtBatchItem.h"
#include "GbInsertStxmlFileTool.h"

//////////////////////////////////////////////////////////////////////////
//批量添加
CWzdGuideBookItemsRef::CWzdGuideBookItemsRef()
{
	m_nUse = 1;
}

CWzdGuideBookItemsRef::~CWzdGuideBookItemsRef()
{

}

CBaseObject* CWzdGuideBookItemsRef::Clone()
{
	CWzdGuideBookItemsRef *pNew = new CWzdGuideBookItemsRef();
	Copy(pNew);
	return pNew;
}

BOOL CWzdGuideBookItemsRef::CopyOwn(CBaseObject* pDest)
{
	((CWzdGuideBookItemsRef*)pDest)->m_nUse = m_nUse;
	((CWzdGuideBookItemsRef*)pDest)->m_strValue = m_strValue;

	return CExBaseObject::CopyOwn(pDest);
}

long CWzdGuideBookItemsRef::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseKey, oNode, m_nUse);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CWzdGuideBookItemsRef::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strUseKey, oElement, m_nUse);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);

	return 0;
}


CWzdInsertItemsLevel::CWzdInsertItemsLevel()
{
	m_nRefItemClassID = 0;
	CGbItemVariableIDReplace::g_bShowReplaceItemPath = FALSE;
}

CWzdInsertItemsLevel::~CWzdInsertItemsLevel()
{
	CGbItemVariableIDReplace::g_bShowReplaceItemPath = TRUE;
}

CBaseObject* CWzdInsertItemsLevel::Clone()
{
	CWzdInsertItemsLevel *pNew = new CWzdInsertItemsLevel();
	Copy(pNew);
	return pNew;
}

BOOL CWzdInsertItemsLevel::CopyOwn(CBaseObject* pDest)
{
	((CWzdInsertItemsLevel*)pDest)->m_strDatasetPath = m_strDatasetPath;
	((CWzdInsertItemsLevel*)pDest)->m_nRefItemClassID = m_nRefItemClassID;

	return CExBaseList::CopyOwn(pDest);
}

long CWzdInsertItemsLevel::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDatasetPathKey, oNode, m_strDatasetPath);

	return 0;
}

long CWzdInsertItemsLevel::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strDatasetPathKey, oElement, m_strDatasetPath);

	return 0;
}

CExBaseObject* CWzdInsertItemsLevel::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CValueKey())
	{
		return new CWzdGuideBookItemsRef();
	}

	return NULL;
	//return CValues::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

void CWzdInsertItemsLevel::InitByCopy(CWzdInsertItemsLevel *pSrc)
{
	POS pos = GetHeadPosition();
	CWzdGuideBookItemsRef *pValue = NULL;
	CWzdGuideBookItemsRef *pFind = NULL;

	m_strDatasetPath = pSrc->m_strDatasetPath;

	while (pos != NULL)
	{
		pValue = (CWzdGuideBookItemsRef *)GetNext(pos);
		pFind = (CWzdGuideBookItemsRef *)pSrc->FindByID(pValue->m_strID);

		if (pFind != NULL)
		{
			pValue->m_strValue = pFind->m_strValue;
			pValue->m_strName = pFind->m_strName;
			pValue->m_nUse = pFind->m_nUse;
		}
	}
}

long CWzdInsertItemsLevel::GetUsedBatchItemRefValues(CExBaseList &oListValue)
{
	POS pos = GetHeadPosition();
	CWzdGuideBookItemsRef* pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CWzdGuideBookItemsRef *)GetNext(pos);

		if (pValue->m_nUse != 0)
		{
			oListValue.AddTail(pValue);
		}
	}

	return oListValue.GetCount();
}

void CWzdInsertItemsLevel::InitBatchItemRef(CValues *pValues)
{
	DeleteAll();
	POS pos = pValues->GetHeadPosition();
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)pValues->GetNext(pos);
		CWzdGuideBookItemsRef *pRefValue = new CWzdGuideBookItemsRef();
		pRefValue->m_strID = pValue->m_strID;
		pRefValue->m_strName = pValue->m_strName;
		pRefValue->m_strValue = pValue->m_strValue;
		AddNewChild(pRefValue);
	}
}

CWzdGuideBookInsertMngr::CWzdGuideBookInsertMngr()
{
	m_strName = _T("批量枚举组");
	m_strID = _T("BatchEnum");
}

CWzdGuideBookInsertMngr::~CWzdGuideBookInsertMngr()
{

}

CBaseObject* CWzdGuideBookInsertMngr::Clone()
{
	CWzdGuideBookInsertMngr *pNew = new CWzdGuideBookInsertMngr();
	Copy(pNew);
	return pNew;
}

BOOL CWzdGuideBookInsertMngr::CopyOwn(CBaseObject* pDest)
{
	return CExBaseObject::CopyOwn(pDest);
}

long CWzdGuideBookInsertMngr::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CWzdGuideBookInsertMngr::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}


CExBaseObject* CWzdGuideBookInsertMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CWzdInsertItemsLevelKey())
	{
		return new CWzdInsertItemsLevel();
	}

	return NULL;
}


void CWzdGuideBookInsertMngr::InitByCopy(CWzdGuideBookInsertMngr *pSrc)
{
	POS pos = GetHeadPosition();
	 CWzdInsertItemsLevel *p = NULL;
	 CWzdInsertItemsLevel *pFind = NULL;

	m_strID = pSrc->m_strID;
	m_strName = pSrc->m_strName;

	while (pos != NULL)
	{
		p = (CWzdInsertItemsLevel *)GetNext(pos);
		pFind = (CWzdInsertItemsLevel *)pSrc->FindByID(p->m_strID);

		if (pFind != NULL)
		{
			p->InitByCopy(pFind);
		}
	}
}


CWzdInsertItemsLevel* CWzdGuideBookInsertMngr::NewBatchItemRef(CExBaseObject *pItem)
{
	CWzdInsertItemsLevel *pNew = NULL;
	UINT nClassID = pItem->GetClassID();
	CGbItemBase *pGbItem = (CGbItemBase*)pItem;

	if (pGbItem->m_nBatchItem != 1)
	{
		return NULL;
	}

	switch (nClassID)
	{
	case GBCLASSID_COMMCMD:
		pNew = NewBatchItemRef_CommCmd(pItem);
		break;

	default:
		break;
	}

	if (pNew != NULL)
	{
		pNew->m_nRefItemClassID = nClassID;
	}

	return pNew;
}


BOOL CWzdGuideBookInsertMngr::HasBatchItems()
{
	return (GetCount() > 0);
}

BOOL CWzdGuideBookInsertMngr::IsAllCommCmdItems()
{
	return FALSE;
}

BOOL CWzdGuideBookInsertMngr::IsAllMacroTestItems()
{
	return FALSE;
}

long CWzdGuideBookInsertMngr::GetValuesCount()
{
	POS pos = GetHeadPosition();
	CWzdInsertItemsLevel *pItemRef = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pItemRef = (CWzdInsertItemsLevel *)GetNext(pos);
		nCount +=pItemRef->GetCount();
	}

	return nCount;
}

void CWzdGuideBookInsertMngr::SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath)
{
	CWzdInsertItemsLevel *pRef = (CWzdInsertItemsLevel*)GetAtIndex(nItemRefIndex);

	if (pRef == NULL)
	{
		return;
	}

	if (pRef->m_nRefItemClassID != GBCLASSID_COMMCMD)
	{
		return;
	}

	pRef->m_strDatasetPath = strDatasetPath;
}

void CWzdGuideBookInsertMngr::ChangeBatchItemRefValueSel(long nItemRefIndex, CWzdGuideBookItemsRef *pValue)
{
	CWzdInsertItemsLevel *pRef = (CWzdInsertItemsLevel*)GetAtIndex(nItemRefIndex);

	if (pRef == NULL)
	{
		return;
	}

	CWzdGuideBookItemsRef *pFind = NULL;
	pFind = (CWzdGuideBookItemsRef*)pRef->FindByID(pValue->m_strID);
	ASSERT (pFind != NULL);

	if (pFind != NULL)
	{
		if (pFind->m_nUse > 0)
		{
			pFind->m_nUse = 0;
		}
		else
		{
			pFind->m_nUse = 1;
		}
	}

}

BOOL CWzdGuideBookInsertMngr::ValidateBatchItemsGroup(CString &strErrorMsg)
{
	POS pos = GetHeadPosition();
	CWzdInsertItemsLevel *pItemRef = NULL;
	long nCount = 0;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pItemRef = (CWzdInsertItemsLevel *)GetNext(pos);
		
		if (pItemRef->m_strID.GetLength() == 0)
		{
			bTrue = FALSE;
			strErrorMsg = _T("批量项目没有输入ID");
			break;
		}

		if (pItemRef->m_strName.GetLength() == 0)
		{
			bTrue = FALSE;
			strErrorMsg = _T("批量项目没有输入名称");
			break;
		}

		if (pItemRef->m_strDatasetPath.GetLength() == 0)
		{
			bTrue = FALSE;
			strErrorMsg = _T("批量项目没有关联数据集");
			break;
		}
	}

	return bTrue;
}

long CWzdGuideBookInsertMngr::GetUsedBatchItemRefValues(CExBaseList &oListValue)
{
	oListValue.RemoveAll();
	POS pos = GetHeadPosition();
	CWzdInsertItemsLevel *pItemRef = NULL;

	while (pos != NULL)
	{
		pItemRef = (CWzdInsertItemsLevel *)GetNext(pos);
		pItemRef->GetUsedBatchItemRefValues(oListValue);
	}

	return oListValue.GetCount();
}


CWzdInsertItemsLevel* CWzdGuideBookInsertMngr::NewBatchItemRef_CommCmd(CExBaseObject *pItem)
{
	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd *pCmd = pCommCmd->GetCmd();
	
	CWzdInsertItemsLevel *pNew = new CWzdInsertItemsLevel();
	pNew->m_strName = pItem->m_strName;
	pNew->m_strID = pItem->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
	pNew->m_strDatasetPath = pCmd->m_strDatasetPath;
	AddNewChild(pNew);

	pNew->InitBatchItemRef(pCmd);//, TRUE);

	CGbInsertStxmlFileTool *pToolRef = (CGbInsertStxmlFileTool*)GetAncestor(GBTWZDCLASSID_GBTINSERTSTXMLFILETOOL);

	if (pToolRef == NULL)
	{
		return pNew;
	}

	CDevice *pDevice = pToolRef->m_pGuideBookDest->GetDevice();

	if (pDevice != NULL)
	{
		CExBaseList oListDataset;
		pDevice->GetDataSetList(pNew->m_strDatasetPath, oListDataset);

		if (oListDataset.GetCount() == 1)
		{
			CDataSet *pDataset = (CDataSet*)oListDataset.GetHead();
			pNew->m_strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE);
		}

		oListDataset.RemoveAll();
	}

	if (pNew->m_strDatasetPath.GetLength() > 0)
	{
		return pNew;
	}

	//获取通讯命令的每个数据，与关联的数据组进行匹配
	POS pos = pCmd->GetHeadPosition();
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CValue*)pCmd->GetNext(pos);
	}

	return pNew;
}



CGbInsertGbxmlFileTool::CGbInsertGbxmlFileTool()
{
	m_pGbtBatchItemGroupRef = new CWzdGuideBookInsertMngr();
	m_nBatchVariableMode = 0;
	m_nBatchItemsMode = BATCH_ITEMS_MODE_EXTERNER;
	m_pGbtBatchItemGroupRef->SetParent(this);
}

CGbInsertGbxmlFileTool::~CGbInsertGbxmlFileTool()
{
	if (m_pGbtBatchItemGroupRef != NULL)
	{
		delete m_pGbtBatchItemGroupRef;
		m_pGbtBatchItemGroupRef = NULL;
	}
}


long CGbInsertGbxmlFileTool::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strBatchVariableModeKey, oNode, m_nBatchVariableMode);
	xml_GetAttibuteValue(pXmlKeys->m_strBatchItemsModeKey, oNode, m_nBatchItemsMode);

	return 0;
}

long CGbInsertGbxmlFileTool::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strBatchVariableModeKey, oElement, m_nBatchVariableMode);
	xml_SetAttributeValue(pXmlKeys->m_strBatchItemsModeKey, oElement, m_nBatchItemsMode);

	return 0;
}

CExBaseObject* CGbInsertGbxmlFileTool::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CWzdGuideBookInsertMngrKey())
	{
		return new CWzdGuideBookInsertMngr();
	}

	return NULL;
}

void CGbInsertGbxmlFileTool::InitAfterRead()
{
// 	if (GetCount() == 0)
// 	{
// 		return;
// 	}
// 
// 	CWzdGuideBookInsertMngr *pHead = (CWzdGuideBookInsertMngr*)GetHead();
// 	long nRefIndex = 0;
// 	long nValueIndex = 0;
// 	long nRefCount = pHead->GetCount();
// 	
// 	for (nRefIndex == 0; nRefIndex<nRefCount; nRefIndex++)
// 	{	
// 		CWzdInsertItemsLevel *pSrc = (CWzdInsertItemsLevel*)pHead->GetAtIndex(nRefIndex);
// 		POS pos = pSrc->GetHeadPosition();
// 		CWzdGuideBookItemsRef *pValue = NULL;
// 
// 		while (pos != NULL)
// 		{
// 			pValue = (CWzdGuideBookItemsRef *)pSrc->GetNext(pos);
// 			m_pGbtBatchItemGroupRef->ChangeBatchItemRefValueSel(nRefIndex, pValue);
// 		}
// 	}
}

void CGbInsertGbxmlFileTool::InitByCopy(CGbInsertGbxmlFileTool *pSrc)
{
	DeleteAll();

	if (pSrc->GetCount() == 0)
	{
		return;
	}

	POS pos = pSrc->GetHeadPosition();
	CWzdGuideBookInsertMngr *p = NULL;
	CWzdGuideBookInsertMngr *pFind = NULL;

	m_nBatchVariableMode = pSrc->m_nBatchVariableMode;
	m_nBatchItemsMode = pSrc->m_nBatchItemsMode;

	while (pos != NULL)
	{
		p = (CWzdGuideBookInsertMngr *)pSrc->GetNext(pos);
		pFind = NewBatchItemGroup();
		pFind->InitByCopy(p);
	}

	CWzdGuideBookInsertMngr *pHead = (CWzdGuideBookInsertMngr*)pSrc->GetHead();
	long nRefIndex = 0;
	long nValueIndex = 0;
	long nRefCount = pHead->GetCount();

	for (nRefIndex = 0; nRefIndex<nRefCount; nRefIndex++)
	{	
		CWzdInsertItemsLevel *pSrcRef = (CWzdInsertItemsLevel*)pHead->GetAtIndex(nRefIndex);
		POS pos = pSrcRef->GetHeadPosition();
		CWzdGuideBookItemsRef *pValue = NULL;
		CWzdInsertItemsLevel *pDestRef = (CWzdInsertItemsLevel*)m_pGbtBatchItemGroupRef->GetAtIndex(nRefIndex);

		if (pDestRef == NULL)
		{
			break;
		}

		pDestRef->m_strDatasetPath = pSrcRef->m_strDatasetPath;

		while (pos != NULL)
		{
			pValue = (CWzdGuideBookItemsRef *)pSrcRef->GetNext(pos);
			CWzdGuideBookItemsRef *pDestValue = (CWzdGuideBookItemsRef*)pDestRef->FindByID(pValue->m_strID);
			
			if (pDestValue != NULL)
			{
				pDestValue->m_nUse = pValue->m_nUse;
			}
		}
	}
}

BOOL CGbInsertGbxmlFileTool::HasBatchItems()
{
	if (m_pGbtBatchItemGroupRef == NULL)
	{
		return FALSE;
	}
	else
	{
		return m_pGbtBatchItemGroupRef->HasBatchItems();
	}
}

BOOL CGbInsertGbxmlFileTool::IsAllCommCmdItems()
{
	if (m_pGbtBatchItemGroupRef == NULL)
	{
		return FALSE;
	}
	else
	{
		return m_pGbtBatchItemGroupRef->IsAllCommCmdItems();
	}
}

BOOL CGbInsertGbxmlFileTool::IsAllMacroTestItems()
{
	if (m_pGbtBatchItemGroupRef == NULL)
	{
		return FALSE;
	}
	else
	{
		return m_pGbtBatchItemGroupRef->IsAllMacroTestItems();
	}
}

void CGbInsertGbxmlFileTool::SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath)
{
	POS pos = GetHeadPosition();
	CWzdGuideBookInsertMngr *p = NULL;
	m_pGbtBatchItemGroupRef->SetBatchItemRefDatasetPath(nItemRefIndex, strDatasetPath);

	while (pos != NULL)
	{
		p = (CWzdGuideBookInsertMngr *)GetNext(pos);
		p->SetBatchItemRefDatasetPath(nItemRefIndex, strDatasetPath);
	}
}

void CGbInsertGbxmlFileTool::ChangeBatchItemRefValueSel(long nItemRefIndex, CWzdGuideBookItemsRef *pValue)
{
	POS pos = GetHeadPosition();
	CWzdGuideBookInsertMngr *p = NULL;
	m_pGbtBatchItemGroupRef->ChangeBatchItemRefValueSel(nItemRefIndex, pValue);

	while (pos != NULL)
	{
		p = (CWzdGuideBookInsertMngr *)GetNext(pos);
		p->ChangeBatchItemRefValueSel(nItemRefIndex, pValue);
	}
}

BOOL CGbInsertGbxmlFileTool::ValidateBatchItemsGroups(CString &strErrorMsg)
{
	if (m_pGbtBatchItemGroupRef->GetCount() == 0)
	{
		return TRUE;
	}

	if (GetCount() == 0)
	{
		return TRUE;
	}

	POS pos = GetHeadPosition();
	CWzdGuideBookInsertMngr *pGroup = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pGroup = (CWzdGuideBookInsertMngr *)GetNext(pos);
		bTrue = pGroup->ValidateBatchItemsGroup(strErrorMsg);

		if (!bTrue)
		{
			break;
		}
	}

	return bTrue;
}

void CGbInsertGbxmlFileTool::InitListBatchItem(CGuideBook *pGuideBook)
{
	CDevice *pDevice = pGuideBook->GetDevice();
	CExBaseList oListItems;
	pDevice->SelectAllRootItem(oListItems);
	InitListBatchItemRef(&oListItems);
	oListItems.RemoveAll();
}

void CGbInsertGbxmlFileTool::InitListBatchItemRef(CExBaseList *pList)
{
	UINT nClassID = 0;
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;

	while (pos != NULL)
	{
		pItem = (CExBaseObject *)pList->GetNext(pos);
		nClassID = pItem->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			InitListBatchItemRef((CExBaseList*)pItem);
		}
		else if ( (nClassID == GBCLASSID_MACROTEST) || (nClassID == GBCLASSID_COMMCMD) )
		{
			m_pGbtBatchItemGroupRef->NewBatchItemRef(pItem);
		}
	}
}

CWzdGuideBookInsertMngr* CGbInsertGbxmlFileTool::NewBatchItemGroup()
{
	CWzdGuideBookInsertMngr *pNew = (CWzdGuideBookInsertMngr*)m_pGbtBatchItemGroupRef->Clone();
	AddNewChild(pNew, TRUE);
	return pNew;
}

//////////////////////////////////////////////////////////////////////////
//映射组别功能
