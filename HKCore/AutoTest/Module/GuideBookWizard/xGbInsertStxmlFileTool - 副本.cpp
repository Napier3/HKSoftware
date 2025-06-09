#include "stdafx.h"
#include "GbInsertStxmlFileTool.h"

//////////////////////////////////////////////////////////////////////////
//批量添加
CGbtBatchItemRefValue::CGbtBatchItemRefValue()
{
	m_nUse = 1;
}

CGbtBatchItemRefValue::~CGbtBatchItemRefValue()
{

}

CBaseObject* CGbtBatchItemRefValue::Clone()
{
	CGbtBatchItemRefValue *pNew = new CGbtBatchItemRefValue();
	Copy(pNew);
	return pNew;
}

BOOL CGbtBatchItemRefValue::CopyOwn(CBaseObject* pDest)
{
	((CGbtBatchItemRefValue*)pDest)->m_nUse = m_nUse;
	((CGbtBatchItemRefValue*)pDest)->m_strValue = m_strValue;

	return CExBaseObject::CopyOwn(pDest);
}

long CGbtBatchItemRefValue::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseKey, oNode, m_nUse);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CGbtBatchItemRefValue::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strUseKey, oElement, m_nUse);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);

	return 0;
}


CGbtBatchItemRef::CGbtBatchItemRef()
{
	m_nRefItemClassID = 0;
	CGbItemVariableIDReplace::g_bShowReplaceItemPath = FALSE;
}

CGbtBatchItemRef::~CGbtBatchItemRef()
{
	CGbItemVariableIDReplace::g_bShowReplaceItemPath = TRUE;
}

CBaseObject* CGbtBatchItemRef::Clone()
{
	CGbtBatchItemRef *pNew = new CGbtBatchItemRef();
	Copy(pNew);
	return pNew;
}

BOOL CGbtBatchItemRef::CopyOwn(CBaseObject* pDest)
{
	((CGbtBatchItemRef*)pDest)->m_strDatasetPath = m_strDatasetPath;
	((CGbtBatchItemRef*)pDest)->m_nRefItemClassID = m_nRefItemClassID;

	return CExBaseList::CopyOwn(pDest);
}

long CGbtBatchItemRef::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDatasetPathKey, oNode, m_strDatasetPath);

	return 0;
}

long CGbtBatchItemRef::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strDatasetPathKey, oElement, m_strDatasetPath);

	return 0;
}

CExBaseObject* CGbtBatchItemRef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CValueKey())
	{
		return new CGbtBatchItemRefValue();
	}

	return NULL;
	//return CValues::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

void CGbtBatchItemRef::InitByCopy(CGbtBatchItemRef *pSrc)
{
	POS pos = GetHeadPosition();
	CGbtBatchItemRefValue *pValue = NULL;
	CGbtBatchItemRefValue *pFind = NULL;

	m_strDatasetPath = pSrc->m_strDatasetPath;

	while (pos != NULL)
	{
		pValue = (CGbtBatchItemRefValue *)GetNext(pos);
		pFind = (CGbtBatchItemRefValue *)pSrc->FindByID(pValue->m_strID);

		if (pFind != NULL)
		{
			pValue->m_strValue = pFind->m_strValue;
			pValue->m_strName = pFind->m_strName;
			pValue->m_nUse = pFind->m_nUse;
		}
	}
}

long CGbtBatchItemRef::GetUsedBatchItemRefValues(CExBaseList &oListValue)
{
	POS pos = GetHeadPosition();
	CGbtBatchItemRefValue* pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CGbtBatchItemRefValue *)GetNext(pos);

		if (pValue->m_nUse != 0)
		{
			oListValue.AddTail(pValue);
		}
	}

	return oListValue.GetCount();
}

void CGbtBatchItemRef::InitBatchItemRef(CValues *pValues)
{
	DeleteAll();
	POS pos = pValues->GetHeadPosition();
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)pValues->GetNext(pos);
		CGbtBatchItemRefValue *pRefValue = new CGbtBatchItemRefValue();
		pRefValue->m_strID = pValue->m_strID;
		pRefValue->m_strName = pValue->m_strName;
		pRefValue->m_strValue = pValue->m_strValue;
		AddNewChild(pRefValue);
	}
}

CGbtBatchItemGroup::CGbtBatchItemGroup()
{
	m_strName = _T("批量枚举组");
	m_strID = _T("BatchEnum");
}

CGbtBatchItemGroup::~CGbtBatchItemGroup()
{

}

CBaseObject* CGbtBatchItemGroup::Clone()
{
	CGbtBatchItemGroup *pNew = new CGbtBatchItemGroup();
	Copy(pNew);
	return pNew;
}

BOOL CGbtBatchItemGroup::CopyOwn(CBaseObject* pDest)
{
	return CExBaseObject::CopyOwn(pDest);
}

long CGbtBatchItemGroup::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbtBatchItemGroup::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}


CExBaseObject* CGbtBatchItemGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtBatchItemRefKey())
	{
		return new CGbtBatchItemRef();
	}

	return NULL;
}


void CGbtBatchItemGroup::InitByCopy(CGbtBatchItemGroup *pSrc)
{
	POS pos = GetHeadPosition();
	 CGbtBatchItemRef *p = NULL;
	 CGbtBatchItemRef *pFind = NULL;

	m_strID = pSrc->m_strID;
	m_strName = pSrc->m_strName;

	while (pos != NULL)
	{
		p = (CGbtBatchItemRef *)GetNext(pos);
		pFind = (CGbtBatchItemRef *)pSrc->FindByID(p->m_strID);

		if (pFind != NULL)
		{
			p->InitByCopy(pFind);
		}
	}
}


CGbtBatchItemRef* CGbtBatchItemGroup::NewBatchItemRef(CExBaseObject *pItem)
{
	CGbtBatchItemRef *pNew = NULL;
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


BOOL CGbtBatchItemGroup::HasBatchItems()
{
	return (GetCount() > 0);
}

BOOL CGbtBatchItemGroup::IsAllCommCmdItems()
{
	return FALSE;
}

BOOL CGbtBatchItemGroup::IsAllMacroTestItems()
{
	return FALSE;
}

long CGbtBatchItemGroup::GetValuesCount()
{
	POS pos = GetHeadPosition();
	CGbtBatchItemRef *pItemRef = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pItemRef = (CGbtBatchItemRef *)GetNext(pos);
		nCount +=pItemRef->GetCount();
	}

	return nCount;
}

void CGbtBatchItemGroup::SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath)
{
	CGbtBatchItemRef *pRef = (CGbtBatchItemRef*)GetAtIndex(nItemRefIndex);

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

void CGbtBatchItemGroup::ChangeBatchItemRefValueSel(long nItemRefIndex, CGbtBatchItemRefValue *pValue)
{
	CGbtBatchItemRef *pRef = (CGbtBatchItemRef*)GetAtIndex(nItemRefIndex);

	if (pRef == NULL)
	{
		return;
	}

	CGbtBatchItemRefValue *pFind = NULL;
	pFind = (CGbtBatchItemRefValue*)pRef->FindByID(pValue->m_strID);
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

BOOL CGbtBatchItemGroup::ValidateBatchItemsGroup(CString &strErrorMsg)
{
	POS pos = GetHeadPosition();
	CGbtBatchItemRef *pItemRef = NULL;
	long nCount = 0;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pItemRef = (CGbtBatchItemRef *)GetNext(pos);
		
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

long CGbtBatchItemGroup::GetUsedBatchItemRefValues(CExBaseList &oListValue)
{
	oListValue.RemoveAll();
	POS pos = GetHeadPosition();
	CGbtBatchItemRef *pItemRef = NULL;

	while (pos != NULL)
	{
		pItemRef = (CGbtBatchItemRef *)GetNext(pos);
		pItemRef->GetUsedBatchItemRefValues(oListValue);
	}

	return oListValue.GetCount();
}


CGbtBatchItemRef* CGbtBatchItemGroup::NewBatchItemRef_CommCmd(CExBaseObject *pItem)
{
	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd *pCmd = pCommCmd->GetCmd();
	
	CGbtBatchItemRef *pNew = new CGbtBatchItemRef();
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



CGbtBatchItemGroups::CGbtBatchItemGroups()
{
	m_pGbtBatchItemGroupRef = new CGbtBatchItemGroup();
	m_nBatchVariableMode = 0;
	m_nBatchItemsMode = BATCH_ITEMS_MODE_EXTERNER;
	m_pGbtBatchItemGroupRef->SetParent(this);
}

CGbtBatchItemGroups::~CGbtBatchItemGroups()
{
	if (m_pGbtBatchItemGroupRef != NULL)
	{
		delete m_pGbtBatchItemGroupRef;
		m_pGbtBatchItemGroupRef = NULL;
	}
}


long CGbtBatchItemGroups::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strBatchVariableModeKey, oNode, m_nBatchVariableMode);
	xml_GetAttibuteValue(pXmlKeys->m_strBatchItemsModeKey, oNode, m_nBatchItemsMode);

	return 0;
}

long CGbtBatchItemGroups::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strBatchVariableModeKey, oElement, m_nBatchVariableMode);
	xml_SetAttributeValue(pXmlKeys->m_strBatchItemsModeKey, oElement, m_nBatchItemsMode);

	return 0;
}

CExBaseObject* CGbtBatchItemGroups::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtBatchItemGroupKey())
	{
		return new CGbtBatchItemGroup();
	}

	return NULL;
}

void CGbtBatchItemGroups::InitAfterRead()
{
// 	if (GetCount() == 0)
// 	{
// 		return;
// 	}
// 
// 	CGbtBatchItemGroup *pHead = (CGbtBatchItemGroup*)GetHead();
// 	long nRefIndex = 0;
// 	long nValueIndex = 0;
// 	long nRefCount = pHead->GetCount();
// 	
// 	for (nRefIndex == 0; nRefIndex<nRefCount; nRefIndex++)
// 	{	
// 		CGbtBatchItemRef *pSrc = (CGbtBatchItemRef*)pHead->GetAtIndex(nRefIndex);
// 		POS pos = pSrc->GetHeadPosition();
// 		CGbtBatchItemRefValue *pValue = NULL;
// 
// 		while (pos != NULL)
// 		{
// 			pValue = (CGbtBatchItemRefValue *)pSrc->GetNext(pos);
// 			m_pGbtBatchItemGroupRef->ChangeBatchItemRefValueSel(nRefIndex, pValue);
// 		}
// 	}
}

void CGbtBatchItemGroups::InitByCopy(CGbtBatchItemGroups *pSrc)
{
	DeleteAll();

	if (pSrc->GetCount() == 0)
	{
		return;
	}

	POS pos = pSrc->GetHeadPosition();
	CGbtBatchItemGroup *p = NULL;
	CGbtBatchItemGroup *pFind = NULL;

	m_nBatchVariableMode = pSrc->m_nBatchVariableMode;
	m_nBatchItemsMode = pSrc->m_nBatchItemsMode;

	while (pos != NULL)
	{
		p = (CGbtBatchItemGroup *)pSrc->GetNext(pos);
		pFind = NewBatchItemGroup();
		pFind->InitByCopy(p);
	}

	CGbtBatchItemGroup *pHead = (CGbtBatchItemGroup*)pSrc->GetHead();
	long nRefIndex = 0;
	long nValueIndex = 0;
	long nRefCount = pHead->GetCount();

	for (nRefIndex = 0; nRefIndex<nRefCount; nRefIndex++)
	{	
		CGbtBatchItemRef *pSrcRef = (CGbtBatchItemRef*)pHead->GetAtIndex(nRefIndex);
		POS pos = pSrcRef->GetHeadPosition();
		CGbtBatchItemRefValue *pValue = NULL;
		CGbtBatchItemRef *pDestRef = (CGbtBatchItemRef*)m_pGbtBatchItemGroupRef->GetAtIndex(nRefIndex);

		if (pDestRef == NULL)
		{
			break;
		}

		pDestRef->m_strDatasetPath = pSrcRef->m_strDatasetPath;

		while (pos != NULL)
		{
			pValue = (CGbtBatchItemRefValue *)pSrcRef->GetNext(pos);
			CGbtBatchItemRefValue *pDestValue = (CGbtBatchItemRefValue*)pDestRef->FindByID(pValue->m_strID);
			
			if (pDestValue != NULL)
			{
				pDestValue->m_nUse = pValue->m_nUse;
			}
		}
	}
}

BOOL CGbtBatchItemGroups::HasBatchItems()
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

BOOL CGbtBatchItemGroups::IsAllCommCmdItems()
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

BOOL CGbtBatchItemGroups::IsAllMacroTestItems()
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

void CGbtBatchItemGroups::SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath)
{
	POS pos = GetHeadPosition();
	CGbtBatchItemGroup *p = NULL;
	m_pGbtBatchItemGroupRef->SetBatchItemRefDatasetPath(nItemRefIndex, strDatasetPath);

	while (pos != NULL)
	{
		p = (CGbtBatchItemGroup *)GetNext(pos);
		p->SetBatchItemRefDatasetPath(nItemRefIndex, strDatasetPath);
	}
}

void CGbtBatchItemGroups::ChangeBatchItemRefValueSel(long nItemRefIndex, CGbtBatchItemRefValue *pValue)
{
	POS pos = GetHeadPosition();
	CGbtBatchItemGroup *p = NULL;
	m_pGbtBatchItemGroupRef->ChangeBatchItemRefValueSel(nItemRefIndex, pValue);

	while (pos != NULL)
	{
		p = (CGbtBatchItemGroup *)GetNext(pos);
		p->ChangeBatchItemRefValueSel(nItemRefIndex, pValue);
	}
}

BOOL CGbtBatchItemGroups::ValidateBatchItemsGroups(CString &strErrorMsg)
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
	CGbtBatchItemGroup *pGroup = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pGroup = (CGbtBatchItemGroup *)GetNext(pos);
		bTrue = pGroup->ValidateBatchItemsGroup(strErrorMsg);

		if (!bTrue)
		{
			break;
		}
	}

	return bTrue;
}

void CGbtBatchItemGroups::InitListBatchItem(CGuideBook *pGuideBook)
{
	CDevice *pDevice = pGuideBook->GetDevice();
	CExBaseList oListItems;
	pDevice->SelectAllRootItem(oListItems);
	InitListBatchItemRef(&oListItems);
	oListItems.RemoveAll();
}

void CGbtBatchItemGroups::InitListBatchItemRef(CExBaseList *pList)
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

CGbtBatchItemGroup* CGbtBatchItemGroups::NewBatchItemGroup()
{
	CGbtBatchItemGroup *pNew = (CGbtBatchItemGroup*)m_pGbtBatchItemGroupRef->Clone();
	AddNewChild(pNew, TRUE);
	return pNew;
}

//////////////////////////////////////////////////////////////////////////
//映射组别功能


//////////////////////////////////////////////////////////////////////////
//
CGbtDataScriptMap::CGbtDataScriptMap()
{
	m_pRefObject = NULL;
}

CGbtDataScriptMap::~CGbtDataScriptMap()
{
	RemoveAll();
}


CBaseObject* CGbtDataScriptMap::Clone()
{
	CGbtDataScriptMap *pNew = new CGbtDataScriptMap();
	Copy(pNew);
	return pNew;
}

BOOL CGbtDataScriptMap::CopyOwn(CBaseObject* pDest)
{
	((CGbtDataScriptMap*)pDest)->m_pGbtDataScript = m_pGbtDataScript;
	((CGbtDataScriptMap*)pDest)->m_pRefObject = m_pRefObject;
	((CGbtDataScriptMap*)pDest)->m_strDataValue = m_strDataValue;
	((CGbtDataScriptMap*)pDest)->m_strRefObjName = m_strRefObjName;
	((CGbtDataScriptMap*)pDest)->m_strRefObjPath = m_strRefObjPath;

	return CExBaseObject::CopyOwn(pDest);
}


long CGbtDataScriptMap::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strDataValueKey, oNode, m_strDataValue);
	xml_GetAttibuteValue(pXmlKeys->m_strRefObjNameKey, oNode, m_strRefObjName);
	xml_GetAttibuteValue(pXmlKeys->m_strRefObjPathKey, oNode, m_strRefObjPath);

	return 0;
}

long CGbtDataScriptMap::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataValueKey, oElement, m_strDataValue);
	xml_SetAttributeValue(pXmlKeys->m_strRefObjNameKey, oElement, m_strRefObjName);
	xml_SetAttributeValue(pXmlKeys->m_strRefObjPathKey, oElement, m_strRefObjPath);

	return 0;
}

CExBaseObject* CGbtDataScriptMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return NULL;
}


void CGbtDataScriptMap::InitByCopy(CGbtDataScriptMap *pSrc)
{
	RemoveAll();
	POS pos = pSrc->GetHeadPosition();

	m_strDataValue = pSrc->m_strDataValue;
	m_strRefObjName = pSrc->m_strRefObjName;
	m_strRefObjPath = pSrc->m_strRefObjPath;
	m_strName = pSrc->m_strName;
	m_strID = pSrc->m_strID;

	CGbInsertStxmlFileTool *pTool = (CGbInsertStxmlFileTool*)GetAncestor(GBTWZDCLASSID_GBTINSERTSTXMLFILETOOL);
	CDevice *pDevice = pTool->GetCurrDeviceDest();

	if (pDevice == NULL)
	{
		return;
	}

	ASSERT (pDevice->m_pCpus != NULL);

	if (pDevice->m_pCpus == NULL)
	{
		return;
	}

	if (m_strRefObjPath.GetLength() > 0)
	{
		CDataObj *pDataObj = pDevice->m_pCpus->SelectDataObj(m_strRefObjPath);

		if (pDataObj != NULL)
		{
			m_pRefObject = pDataObj;
			AddTail(pDataObj);
		}
		else
		{
			CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("【%s】对应的数据集数据不存在"), m_strRefObjPath);
		}
	}
}


BOOL CGbtDataScriptMap::Copy(CBaseObject* pDest)
{	
	CopyOwn(pDest);

	((CExBaseList*)pDest)->RemoveAll();
	((CExBaseList*)pDest)->Append(this);
	
	pDest->InitAfterRead(); 

	return TRUE;
}

void CGbtDataScriptMap::SetRefObject(CExBaseObject *pRefObject, BOOL bRemoveAll)
{
	if (bRemoveAll)
	{
		RemoveAll();
	}

	if (pRefObject != NULL)
	{
		AddTail(pRefObject);
		m_strRefObjName = pRefObject->m_strName;
		m_strRefObjPath = pRefObject->GetIDPathEx(GBCLASSID_CPUS, FALSE);
	}
	else
	{
		m_strRefObjName.Empty();
		m_strRefObjPath.Empty();
	}
}

void CGbtDataScriptMap::InitGbtDataScript(CGbtDataScript *pGbtDataScript)
{
	m_pGbtDataScript = pGbtDataScript;
	m_strName = pGbtDataScript->m_strName;
	m_strID = pGbtDataScript->m_strID;
}

void CGbtDataScriptMap::XMatch(CXMatchList &oXMatchList)
{
	POS pos = oXMatchList.GetHeadPosition();
	CXMatchObject *pXMatch = NULL;
	RemoveAll();

	if (m_pGbtDataScript->m_strStandName.GetLength() > 0)
	{
		while (pos != NULL)
		{
			pXMatch = (CXMatchObject *)oXMatchList.GetNext(pos);

			if (pXMatch->m_pRefObject->m_strName.Find(m_pGbtDataScript->m_strStandName) >= 0)
			{
				AddTail(pXMatch->m_pRefObject);
			}
		}
	}
	
	if (GetCount() == 0)
	{
		while (pos != NULL)
		{
			pXMatch = (CXMatchObject *)oXMatchList.GetNext(pos);

			if (m_pGbtDataScript->ScptCal(pXMatch) > 0)
			{
				AddTail(pXMatch->m_pRefObject);
			}
		}
	}

	if (GetCount() == 1)
	{
		m_pRefObject = (CExBaseObject*)GetTail();
		m_strRefObjName = m_pRefObject->m_strName;
		m_strRefObjPath = m_pRefObject->GetIDPathEx(GBCLASSID_CPUS, FALSE);
	}
	else
	{
		m_pRefObject = NULL;
		m_strRefObjName.Empty();
		m_strRefObjPath.Empty();
	}
}

BOOL CGbtDataScriptMap::HasAllKey(const CStringArray &astrKey, const CString &strName)
{
	long nCount = astrKey.GetCount();
	long nIndex = 0;
	BOOL bTrue = TRUE;
	CString strKey;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strKey = astrKey.GetAt(nIndex);

		if (strName.Find(strKey) < 0)
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

BOOL CGbtDataScriptMap::HasKey(const CStringArray &astrKey, const CString &strName)
{
	long nCount = astrKey.GetCount();
	long nIndex = 0;
	BOOL bTrue = FALSE;
	CString strKey;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strKey = astrKey.GetAt(nIndex);

		if (strName.Find(strKey) >= 0)
		{
			bTrue = TRUE;
			break;
		}
	}

	return bTrue;
}

void CGbtDataScriptMap::XMatch(CXMatchList &oXMatchList, const CStringArray &strKey)
{
	XMatch(oXMatchList);
	
	if (strKey.GetCount() == 0)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CExBaseObject *pRef = NULL;
	POS posCurr = NULL;

	while (pos != NULL)
	{
		posCurr = pos;
		pRef = (CExBaseObject*)GetNext(pos);

		if ( HasKey(strKey, pRef->m_strName) )
		{
			
		}
		else
		{
			RemoveAt(posCurr);
		}
	}

	if (GetCount() == 1)
	{
		m_pRefObject = (CExBaseObject*)GetTail();
	}
	else
	{
		m_pRefObject = NULL;
	}

	SetRefObject(m_pRefObject, FALSE);
}

BOOL CGbtDataScriptMap::InitRefObject()
{
	if (GetCount() == 1)
	{
		m_pRefObject = (CExBaseObject*)GetTail();
	}
	else
	{
		m_pRefObject = NULL;
	}

	return (m_pRefObject != NULL);
}

CString CGbtDataScriptMap::GetGbtDataScriptValue()
{
	CString strText;
	CDevice *pDevice = (CDevice*)m_pGbtDataScript->GetAncestor(GBCLASSID_DEVICE);
	CGbtDatas *pGbtDatas = pDevice->m_pGbtDataInterfaces->m_pGbtDatas;
	CGbtData *pData = (CGbtData*)pGbtDatas->FindByID(m_pGbtDataScript->m_strID);

	if (m_strDataValue.GetLength() > 0)
	{
		strText = m_strDataValue;
	}
	else
	{
		if (pData != NULL)
		{
			strText = pData->m_strValue;
		}
		else
		{
			strText = _T("0");
		}
	}

	return strText;
}

CString CGbtDataScriptMap::GetRefObjIDPath()
{
	CString strText;

	if (m_pRefObject == NULL)
	{
		CDevice *pDevice = (CDevice*)m_pGbtDataScript->GetAncestor(GBCLASSID_DEVICE);
		CGbtDatas *pGbtDatas = pDevice->m_pGbtDataInterfaces->m_pGbtDatas;
		CGbtData *pData = (CGbtData*)pGbtDatas->FindByID(m_pGbtDataScript->m_strID);

		if (m_strDataValue.GetLength() > 0)
		{
			strText = m_strDataValue;
		}
		else
		{
			if (pData != NULL)
			{
				strText = pData->m_strValue;
			}
			else
			{
				strText = _T("0");
			}
		}
	}
	else
	{
		UINT nClassID = m_pRefObject->GetClassID();
		CDataObj *pData = (CDataObj*)m_pRefObject;
		pData->GetIDForPath(strText);
	}

	return strText;
}

//////////////////////////////////////////////////////////////////////////
CGbtDataInterfaceMap::CGbtDataInterfaceMap()
{
	m_pGbtDataInterface = NULL;

}

CGbtDataInterfaceMap::~CGbtDataInterfaceMap()
{

}

CBaseObject* CGbtDataInterfaceMap::Clone()
{
	CGbtDataInterfaceMap *pNew = new CGbtDataInterfaceMap();
	Copy(pNew);
	return pNew;
}

BOOL CGbtDataInterfaceMap::CopyOwn(CBaseObject* pDest)
{
	((CGbtDataInterfaceMap*)pDest)->m_pGbtDataInterface = m_pGbtDataInterface;

	return CExBaseObject::CopyOwn(pDest);
}


long CGbtDataInterfaceMap::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbtDataInterfaceMap::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CGbtDataInterfaceMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtDataScriptMapKey())
	{
		return new CGbtDataScriptMap();
	}

	return NULL;
}

void CGbtDataInterfaceMap::InitByCopy(CGbtDataInterfaceMap *pSrc)
{
	POS pos = pSrc->GetHeadPosition();
	CGbtDataScriptMap *p = NULL;
	CGbtDataScriptMap *pFind = NULL;

	m_strName = pSrc->m_strName;
	m_strID = pSrc->m_strID;

	while (pos != NULL)
	{
		p = (CGbtDataScriptMap *)pSrc->GetNext(pos);
		pFind = (CGbtDataScriptMap *)FindByID(p->m_strID);

		if (pFind != NULL)
		{
			pFind->InitByCopy(p);
		}
	}
}

void CGbtDataInterfaceMap::InitGbtDataInterface(CGbtDataInterface *pGbtDataInterface)
{
	CGbtDataScriptMap *pNew = NULL;
	POS pos = pGbtDataInterface->GetHeadPosition();
	CGbtDataScript *pScript = NULL;
	m_pGbtDataInterface = pGbtDataInterface;

	m_strName = pGbtDataInterface->m_strName;
	m_strID = pGbtDataInterface->m_strID;

	while (pos != NULL)
	{
		pScript = (CGbtDataScript *)pGbtDataInterface->GetNext(pos);
		pNew = new CGbtDataScriptMap();
		AddNewChild(pNew);
		pNew->InitGbtDataScript(pScript);
	}
}

void CGbtDataInterfaceMap::XMatch(CXMatchList &oXMatchList)
{
	POS pos = GetHeadPosition();
	CGbtDataScriptMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataScriptMap *)GetNext(pos);
		pMap->XMatch(oXMatchList);
	}
}

void CGbtDataInterfaceMap::XMatch(CXMatchList &oXMatchList, const CStringArray &strKey)
{
	POS pos = GetHeadPosition();
	CGbtDataScriptMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataScriptMap *)GetNext(pos);
		pMap->XMatch(oXMatchList, strKey);
	}
}

BOOL CGbtDataInterfaceMap::CanInsert()
{
	POS pos = GetHeadPosition();
	CGbtDataScriptMap *pMap = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pMap = (CGbtDataScriptMap *)GetNext(pos);
		
		if (pMap->InitRefObject() != NULL)
		{
			nCount++;
		}
	}

	return (/*(GetCount() == nCount) &&*/( nCount > 0) );
}

BOOL CGbtDataInterfaceMap::ValidateMapKeys(CString &strErrorMsg)
{
	POS pos = GetHeadPosition();
	CGbtDataScriptMap *pMap = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pMap = (CGbtDataScriptMap *)GetNext(pos);

		if (pMap->GetCount() > 1)
		{
			nCount++;
			strErrorMsg.Format(_T("数据接口映射【%s】不唯一"), pMap->m_strName);
		}
	}

	return ( nCount == 0 );
}

CGbInsertStxmlFile::CGbInsertStxmlFile()
{
	m_bInsertFileRoot =  TRUE;
	m_strName = _T("第一组");
	m_strID = _T("Items1");
	m_strKey = _T("");
}

CGbInsertStxmlFile::~CGbInsertStxmlFile()
{
	
}


CBaseObject* CGbInsertStxmlFile::Clone()
{
	CGbInsertStxmlFile *pNew = new CGbInsertStxmlFile();
	Copy(pNew);
	return pNew;
}

BOOL CGbInsertStxmlFile::CopyOwn(CBaseObject* pDest)
{
	((CGbInsertStxmlFile*)pDest)->m_pWordRptEditDest = m_pWordRptEditDest;
	((CGbInsertStxmlFile*)pDest)->m_pWordRptEditSrc = m_pWordRptEditSrc;
	((CGbInsertStxmlFile*)pDest)->m_strStxmlFile = m_strStxmlFile;

	return CExBaseObject::CopyOwn(pDest);
}


long CGbInsertStxmlFile::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strStxmlFileKey, oNode, m_strStxmlFile);
	//xml_GetAttibuteValue(pXmlKeys->m_strDatasetPathKey, oNode, m_bInsertFileRoot);
	xml_GetAttibuteValue(pXmlKeys->m_strIec61850ConfigFileKey, oNode, m_strIec61850ConfigFile);

	return 0;
}

long CGbInsertStxmlFile::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strStxmlFileKey, oElement, m_strStxmlFile);
	//xml_SetAttributeValue(pXmlKeys->m_strInsertFileRootKey, oElement, m_bInsertFileRoot);
	xml_SetAttributeValue(pXmlKeys->m_strIec61850ConfigFileKey, oElement, m_strIec61850ConfigFile);

	return 0;
}

CExBaseObject* CGbInsertStxmlFile::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtDataInterfaceMapKey())
	{
		return new CGbtDataInterfaceMap();
	}

	return NULL;
}


void CGbInsertStxmlFile::InitByCopy(CGbInsertStxmlFile *pSrc)//, CDevice *pDevice, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit)
{
	POS pos = pSrc->GetHeadPosition();
	CGbtDataInterfaceMap *p = NULL;
	CGbtDataInterfaceMap *pFind = NULL;

	SetKey(pSrc->m_strKey);
	
	//ASSERT (m_strStxmlFile == pSrc->m_strStxmlFile);
	m_strIec61850ConfigFile = pSrc->m_strIec61850ConfigFile;
	m_strName = pSrc->m_strName;
	m_strID = pSrc->m_strID;

	while (pos != NULL)
	{
		p = (CGbtDataInterfaceMap *)pSrc->GetNext(pos);
		pFind = (CGbtDataInterfaceMap *)FindByID(p->m_strID);

		if (pFind != NULL)
		{
			pFind->InitByCopy(p);
		}
	}
}

void CGbInsertStxmlFile::InitGbFileInsert(const CString &strStxmlFile, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit)
{
	m_pWordRptEditDest = pDestWordEdit;
	m_pWordRptEditSrc = pSrcWordEdit;
	m_strStxmlFile = strStxmlFile;
}

void CGbInsertStxmlFile::InitGbtDataInterfaceMaps(CDevice *pDevice, const CString &strStxmlFile, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit)
{
	ASSERT (pDevice != NULL);

	if (pDevice == NULL)
	{
		return;
	}

	m_pWordRptEditDest = pDestWordEdit;
	m_pWordRptEditSrc = pSrcWordEdit;
	m_strStxmlFile = strStxmlFile;

	CGbtDataInterfaces *pGbtDataInterfaces =pDevice->m_pGbtDataInterfaces;
	ASSERT (pGbtDataInterfaces != NULL);

	if (pGbtDataInterfaces == NULL)
	{
		return;
	}

	POS pos = pGbtDataInterfaces->GetHeadPosition();
	CGbtDataInterface *pGbtDataInterface = NULL;
	CGbtDataInterfaceMap *pNew = NULL;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pGbtDataInterfaces->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_GBTDATAINTERFACE)
		{
			pGbtDataInterface = (CGbtDataInterface *)p;
			pNew = new CGbtDataInterfaceMap();
			AddNewChild(pNew);
			pNew->InitGbtDataInterface(pGbtDataInterface);
		}
	}
}

void CGbInsertStxmlFile::XMatch(CXMatchList &oXMatchList)
{
	POS pos = GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataInterfaceMap *)GetNext(pos);
		pMap->XMatch(oXMatchList, m_astrKey);
	}
}


CExBaseObject* CGbInsertStxmlFile::ExecInsertByBatchItemGroup(CGbtBatchItemGroup *pBatchItemGroup, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress)
{
	//插入根目录，根目录为BatchItemGroup的名称，下面的分类为File各Map项目分类
	CExBaseList *pStxmlFileItems = pParentItems;

	POS pos = GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataInterfaceMap *)GetNext(pos);
		CItems *pNewItems = InsertByDataterfaceMap(pMap, pStxmlFileItems, oListStxmlItem, pThreadProgress);

		if (pNewItems != NULL)
		{
			if (pThreadProgress != NULL)
			{
				pThreadProgress->StepIt();
				CString strMsg;
				strMsg.Format(_T("插入报告模板【%s】"), pNewItems->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
				pThreadProgress->ShowMsg(strMsg);
			}

			InsertStxmlWord(pNewItems);
		}

		UpdateByBatchGroup(pBatchItemGroup, pNewItems);
	}

	return pStxmlFileItems;
}

CItems* GbtWzd_InsertRootItems(CExBaseList *pParentItems, const CString &strName, const CString &strID)
{
	CItems *pNewItems = new CItems();
	pNewItems->m_strName = strName;
	pNewItems->m_strID;
	pParentItems->AddNewChild(pNewItems, TRUE);
	return pNewItems;
}

void wzd_InsertIecConfigMacroTest(const CString &strIecFile, CExBaseList *pParent)
{
	//插入配置文件项目
	if (strIecFile.GetLength() > 4)
	{
		CMacroTest *pMacroTest = new CMacroTest();
		pMacroTest->m_strName.Format(_T("通道配置：%s"), strIecFile);
		pMacroTest->m_strID = _T("IECConfig");
		pParent->AddNewChild(pMacroTest);
		pMacroTest->InitAfterRead();
		CMacroTestPara *pMacroPara = pMacroTest->GetMacroTestPara();
		CMacroTestParaDatas *pPatas = pMacroPara->GetFaultParaDatas();
		pMacroPara->SetMacroID(_T("IECConfig"));
		CMacroTestParaData* pParaData = (CMacroTestParaData*)pPatas->AddPara(_T("_IecCfgFile"));
		pParaData->SetExpression(strIecFile);
	}
}


CExBaseObject* CGbInsertStxmlFile::ExecInsertByBatchItemGroups(CGbtBatchItemGroups *pBatchItemGroups, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress)
{
	//插入根目录，子模板组的名称，其子目录为BatchItem的各组
	//StxmlFile为根目录，BatchItemGroups为子目录
	CExBaseList *pStxmlFileItems = NULL;
	pStxmlFileItems = new CItems();
	pStxmlFileItems->m_strName = m_strName;
	pStxmlFileItems->m_strID = m_strID;
	pParentItems->AddNewChild(pStxmlFileItems);

	POS pos = pBatchItemGroups->GetHeadPosition();
	CGbtBatchItemGroup *pGroup = NULL;
	//BOOL bBack = m_bInsertFileRoot;
	m_bInsertFileRoot = FALSE;

	//插入配置文件项目
	wzd_InsertIecConfigMacroTest(m_strIec61850ConfigFile, pStxmlFileItems);

	while (pos != NULL)
	{
		pGroup = (CGbtBatchItemGroup *)pBatchItemGroups->GetNext(pos);

		//添加Group对应的Items
		CItems *pItemsGroup = GbtWzd_InsertRootItems(pStxmlFileItems, pGroup->m_strName, pGroup->m_strID);

		//插入子模板到Group对应的Items下
		ExecInsertByBatchItemGroup(pGroup, pItemsGroup, oListStxmlItem, pThreadProgress);
	}

	//m_bInsertFileRoot = bBack;

	return pStxmlFileItems;
}

CDataObj *CGbInsertStxmlFile::FindMapDataObj(const CString &strGbtDataID)
{
	POS pos = GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;
	//CGbtDataScriptMap *

	return NULL;
}

CItems* CGbInsertStxmlFile::ExcuteInsertFile(CExBaseList *pParentItems
											, CExBaseList &oListStxmlItem
											, CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->Step();
	}

	long nOld = g_nCloneReportMapInCopy;
	g_nCloneReportMapInCopy = 1;

	
	if (pThreadProgress != NULL)
	{
		CString strMsg;
		strMsg.Format(_T("插入测试模板【%s】"), pParentItems->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
		pThreadProgress->ShowMsg(strMsg);
		pThreadProgress->StepIt();
	}
	
	pParentItems->AppendCloneEx(oListStxmlItem, TRUE);
	
	if (pThreadProgress != NULL)
	{
		pThreadProgress->StepIt();
		CString strMsg;
		strMsg.Format(_T("插入报告模板【%s】"), pParentItems->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
		pThreadProgress->ShowMsg(strMsg);
	}

	InsertStxmlWord((CItems*)pParentItems);

	return (CItems*)pParentItems;
}

CItems* CGbInsertStxmlFile::InsertByDataterfaceMap(CGbtDataInterfaceMap *pGbtDataInterfaceMap
												   , CExBaseList *pParentItems
												   , CExBaseList &oListStxmlItem
												   , CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->Step();
	}

	if (!pGbtDataInterfaceMap->CanInsert())
	{
		return NULL;
	}

	long nOld = g_nCloneReportMapInCopy;
	g_nCloneReportMapInCopy = 1;


	CItems *pNewItems = new CItems();
	pNewItems->m_strName = pGbtDataInterfaceMap->m_pGbtDataInterface->m_strName;
	pNewItems->m_strID = pGbtDataInterfaceMap->m_pGbtDataInterface->m_strID;
	pParentItems->AddNewChild(pNewItems);

	if (pThreadProgress != NULL)
	{
		CString strMsg;
		strMsg.Format(_T("插入测试模板【%s】"), pNewItems->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
		pThreadProgress->ShowMsg(strMsg);
		pThreadProgress->StepIt();
	}

	pNewItems->AppendCloneEx(oListStxmlItem, TRUE);

	CGbItemVariableIDReplace oReplace;

	POS pos = pGbtDataInterfaceMap->GetHeadPosition();
	CGbtDataScriptMap *pScptMap = NULL;
	CString strSrcID, strDestID;

	while (pos != NULL)
	{
		pScptMap = (CGbtDataScriptMap *)pGbtDataInterfaceMap->GetNext(pos);
		strSrcID = pScptMap->m_pGbtDataScript->m_strID;
		strDestID = pScptMap->GetRefObjIDPath();

		if (IsStringNumber(strDestID))
		{
			CString strDsFunc;
			strDsFunc.Format(_T("GetDsDataValue(\"%s\")"), strSrcID);
			oReplace.Replace(pNewItems, strDsFunc, strDestID);
		}

		oReplace.Replace(pNewItems, strSrcID, strDestID);
	}

	CGbInsertStxmlFileTool *pToolRef = (CGbInsertStxmlFileTool*)GetAncestor(GBTWZDCLASSID_GBTINSERTSTXMLFILETOOL);

	if (pToolRef != NULL)
	{
		CDevice *pDevice = pToolRef->m_pGuideBookDest->GetDevice();
		InitCommCmdItemDatasetPath(pDevice, pNewItems);
	}

	g_nCloneReportMapInCopy = nOld;

	return pNewItems;
}

void CGbInsertStxmlFile::InitCommCmdItemDatasetPath(CDevice *pDevice, CCommCmd *pCommCmd)
{
	pCommCmd->m_bWzdHasInitDataset = FALSE;
	CCmd *pCmd = pCommCmd->GetCmd();
	CExBaseList oListDataset;

	//处理没有关联的数据对象
	CValue *pValue = NULL;
	POS pos = pCmd->GetHeadPosition();

	while (pos != NULL)
	{
		pValue = (CValue *)pCmd->GetNext(pos);

		if (IsStringNumber(pValue->m_strID))
		{
			pCmd->Delete(pValue);
		}
	}


	//根据CommCmd的m_strDatasetPath（数据集的关键字），在设备数据模型中查找数据集
	pDevice->GetDataSetList(pCmd->m_strDatasetPath, oListDataset);
	BOOL bTrue = FALSE;
	CDataSet *pDataset = NULL;

	if (oListDataset.GetCount() == 1)
	{
		pDataset = (CDataSet*)oListDataset.GetHead();
		pCmd->m_strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE);
		bTrue = TRUE;
	}

	oListDataset.RemoveAll();
	pCommCmd->m_bWzdHasInitDataset = bTrue;

	if (bTrue)
	{
		return;
	}

	//根据通讯命令的ID对应的通讯命令配置的数据集关键字，在设备数据模型中查找数据集
	CGuideBook *pGuideBook = (CGuideBook*)pDevice->GetParent();
	CGbCommCmdMms *pGbCommCmd = (CGbCommCmdMms *)pGuideBook->m_oGbCommCmdConfig.FindByID(pCommCmd->m_strCommCmdID);

	if (pGbCommCmd != NULL)
	{
		pDevice->GetDataSetList(Gb_GetDataSetKey(pGbCommCmd->m_strGbDataID), oListDataset);

		if (oListDataset.GetCount() == 1)
		{
			pDataset = (CDataSet*)oListDataset.GetHead();
			pCmd->m_strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE);
			bTrue = TRUE;
		}

		oListDataset.RemoveAll();
	}

	pCommCmd->m_bWzdHasInitDataset = bTrue;

	if (bTrue)
	{
		return;
	}

	//根据通讯命令的参数数据，查找对应的数据对象，并判断所有的数据对象是否为同一个数据集对象的子对象
	//如果是，则初始化数据集
	pValue = NULL;
	pos = pCmd->GetHeadPosition();
	CDataObj *pDataObj = NULL;
	CCpus *pCpus = pDevice->m_pCpus;
	CExBaseList oListData;

	while (pos != NULL)
	{
		pValue = (CValue *)pCmd->GetNext(pos);

		if (IsStringNumber(pValue->m_strID))
		{
			continue;
		}

		pDataObj = pCpus->SelectDataObj(pValue->m_strID);
		
		if (pDataObj != NULL)
		{
			oListData.AddTail(pDataObj);
		}
	}

	if (oListData.GetCount() == 0)
	{
		return ;
	}

	CExBaseObject *p = NULL;
	pos = oListData.GetHeadPosition();
	p = oListData.GetAt(pos);
	pDataset = (CDataSet *)p->GetParent();

	while (pos != NULL)
	{
		p = (CExBaseObject *)oListData.GetNext(pos);

		if (p->GetParent() != pDataset)
		{
			bTrue = FALSE;
			break;
		}
	}

	oListData.RemoveAll();

	if (bTrue)
	{
		CDataSet *pCmdDataset = (CDataSet*)pDataset;
		pCmd->m_strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE);
		pCommCmd->m_bWzdHasInitDataset = TRUE;
	}
}

void CGbInsertStxmlFile::InitCommCmdItemDatasetPath(CDevice *pDevice, CExBaseList *pItems)
{
	if (pDevice == NULL)
	{
		return;
	}

	UINT nClassID = 0;
	nClassID = pItems->GetClassID();

	if (nClassID == GBCLASSID_ITEMS)
	{
		POS pos = pItems->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = (CExBaseObject *)pItems->GetNext(pos);
			nClassID = p->GetClassID();

			if (nClassID == GBCLASSID_ITEMS)
			{
				InitCommCmdItemDatasetPath(pDevice, (CExBaseList*)p);
			}
			else if (nClassID == GBCLASSID_COMMCMD)
			{
				InitCommCmdItemDatasetPath(pDevice, (CCommCmd*)p);

				//如果通讯命令没有通讯参数数据，则删除此命令, 2013-8-15
				CCommCmd *pCommCmd = (CCommCmd*)p;
				CCmd *pCmd = pCommCmd->GetCmd();

				if (pCmd->GetCount() == 0)
				{
					pItems->Delete(pCommCmd);
				}
			}
		}
	}
	else if (nClassID == GBCLASSID_COMMCMD)
	{
		InitCommCmdItemDatasetPath(pDevice, (CCommCmd*)pItems);
	}
}

void CGbInsertStxmlFile::InsertStxmlWord(CItems *pCurrItems)
{
	if (m_pWordRptEditDest == NULL)
	{
		return;
	}

	m_pWordRptEditSrc->m_dwMaxBkmkIndex = m_pWordRptEditDest->m_dwMaxBkmkIndex + 1;
	m_pWordRptEditSrc->OpenWord(m_strStxmlFile);

	//更名标签
	RenameRptBkmks(pCurrItems);

	CString strTitle;
	strTitle = pCurrItems->GetNamePathEx(GBCLASSID_DEVICE, FALSE);

	//插入到Word文档末尾
	m_pWordRptEditDest->InsertTitle(strTitle);
	m_pWordRptEditDest->InsertWordEdit(m_pWordRptEditSrc);
	m_pWordRptEditSrc->CloseWord();
	m_pWordRptEditDest->m_dwMaxBkmkIndex  = m_pWordRptEditSrc->m_dwMaxBkmkIndex + 1;
}

void CGbInsertStxmlFile::RenameRptBkmks(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTBKMK)
		{
			RenameRptBkmk(p);
		}
		else if (p->IsBaseList())
		{
			RenameRptBkmks((CExBaseList*)p);
		}
	}
}

void CGbInsertStxmlFile::RenameRptBkmk(CExBaseObject *pBkmk)
{
	CRptBkmk *p = (CRptBkmk *)pBkmk;

	m_pWordRptEditSrc->UpdateBkmk(p);
}

void CGbInsertStxmlFile::UpdateByBatchGroup(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pRootItems)
{
	if (pBatchGroup == NULL)
	{
		return;
	}

	ASSERT (pRootItems != NULL);

	if (pRootItems == NULL)
	{
		return;
	}

	POS pos = pBatchGroup->GetHeadPosition();
	CGbtBatchItemRef *pRef = NULL;

	while (pos != NULL)
	{
		pRef = (CGbtBatchItemRef *)pBatchGroup->GetNext(pos);
		UpdateByBatchItemRef(pRef, pRootItems);
	}
}


BOOL CGbInsertStxmlFile::ValidateMapKeys(CString &strErrorMsg)
{
	POS pos = GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pMap = (CGbtDataInterfaceMap *)GetNext(pos);

		if (!pMap->ValidateMapKeys(strErrorMsg))
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

void CGbInsertStxmlFile::SetKey(const CString &strKey)
{
	m_strKey = strKey;
	m_strKey.Trim();

	if (m_strKey.GetLength() == 0)
	{
		m_astrKey.RemoveAll();
		return;
	}

	long nPos = 0;
	long nPrevPos = 0;
	CString strTemp;
	long nLen = m_strKey.GetLength();

	while (TRUE)
	{
		nPos = m_strKey.Find(';', nPrevPos);

		if (nPos < 0)
		{
			break;
		}

		if (nPos > nPrevPos)
		{
			strTemp = m_strKey.Mid(nPrevPos, nPos - nPrevPos);
			strTemp.Trim();

			if (strTemp.GetLength() > 0)
			{
				m_astrKey.Add(strTemp);
			}
		}

		nPrevPos = nPos + 1;

		if (nPrevPos >= nLen)
		{
			break;
		}
	}

	if (nPrevPos < nLen)
	{
		strTemp = m_strKey.Mid(nPrevPos);
		strTemp.Trim();

		if (strTemp.GetLength() > 0)
		{
			m_astrKey.Add(strTemp);
		}
	}
}

void CGbInsertStxmlFile::UpdateByBatchItemRef(CGbtBatchItemRef *pBatchItemRef, CExBaseList *pRootItems)
{
	CExBaseObject *pItem = NULL;
	
	//根据BatchItemRef的路径查找到相应的项目
	pItem = SelectByRefItem(pBatchItemRef, pRootItems);

	//更新参数
	ASSERT( pItem != NULL);

	pItem = SelectByRefItem(pBatchItemRef, pRootItems);

	if (pItem == NULL)
	{
		return;
	}

	UINT nClassID = pItem->GetClassID();

	switch (nClassID)
	{
	case GBCLASSID_COMMCMD:
		UpdateItem_CommCmd(pItem, pBatchItemRef);
		break;

	default:
		break;
	}
}

CExBaseObject* CGbInsertStxmlFile::SelectByRefItem(CGbtBatchItemRef *pBatchItemRef, CExBaseList *pRootItems)
{
	CExBaseList *pRootList = pRootItems;


	CExBaseObject *pItem = NULL;
	CExBaseList oListItems;
	long nCount = 0;

	pRootList->SelectDatas(pBatchItemRef->m_strID, oListItems, _T("$"));
	nCount = oListItems.GetCount();

	if (nCount == 1)
	{
		pItem = (CExBaseObject *)oListItems.GetHead();
	}

	oListItems.RemoveAll();

	return pItem;
}

void CGbInsertStxmlFile::UpdateItem_CommCmd(CExBaseObject *pItem, CGbtBatchItemRef *pBatchItemRef)
{
	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd *pCmd = pCommCmd->GetCmd();

	pCmd->m_strDatasetPath = pBatchItemRef->m_strDatasetPath;
// 	pCmd->DeleteAll();
// 	pCmd->AppendCloneEx(*pBatchItemRef, TRUE);
	POS posDest = pCmd->GetHeadPosition();
	POS posSrc = pBatchItemRef->GetHeadPosition();
	CValue *pDest = NULL;
	CGbtBatchItemRefValue *pSrc = NULL;

	while (posSrc != NULL && posDest != NULL)
	{
		pDest = (CValue*)pCmd->GetNext(posDest);
		pSrc  = (CGbtBatchItemRefValue*)pBatchItemRef->GetNext(posSrc);
		pDest->m_strValue = pSrc->m_strValue;
	}
}


//////////////////////////////////////////////////////////////////////////

CGbInsertStxmlFileMngr::CGbInsertStxmlFileMngr()
{
	m_pHeadStxmlFile = NULL;
}

CGbInsertStxmlFileMngr::~CGbInsertStxmlFileMngr()
{
	m_pHeadStxmlFile = NULL;
}


long CGbInsertStxmlFileMngr::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbInsertStxmlFileMngr::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CGbInsertStxmlFileMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbInsertStxmlFileKey())
	{
		return new CGbInsertStxmlFile();
	}

	return NULL;
}

CGbInsertStxmlFile* CGbInsertStxmlFileMngr::NewGbInsertStxmlFile()
{
	CGbInsertStxmlFile *pNew = (CGbInsertStxmlFile*)m_pHeadStxmlFile->Clone();
	long nIndex = GetCount() + 1;
	pNew->m_strName.Format(_T("第%d组"), nIndex);
	pNew->m_strID.Format(_T("StxmlFile%d"), nIndex);
	AddNewChild(pNew, TRUE);
	return pNew;
}

void CGbInsertStxmlFileMngr::InitGbtDataInterfaceMaps(CDevice *pDevice, const CString &strStxmlFile, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit)
{
	if (m_pHeadStxmlFile != NULL)
	{
		return;
	}

	m_pHeadStxmlFile = new CGbInsertStxmlFile();
	m_pHeadStxmlFile->InitGbtDataInterfaceMaps(pDevice, strStxmlFile, pDestWordEdit, pSrcWordEdit);
	AddNewChild(m_pHeadStxmlFile);
}


void CGbInsertStxmlFileMngr::XMatch(CXMatchList &oXMatchList, long nIndex)
{
	if (nIndex < 0)
	{
		POS pos = GetHeadPosition();
		CGbInsertStxmlFile *pStxmlFile = NULL;

		while (pos != NULL)
		{
			pStxmlFile = (CGbInsertStxmlFile *)GetNext(pos);
			pStxmlFile->XMatch(oXMatchList);
		}
	}
	else
	{
		CGbInsertStxmlFile *pStxmlFile = (CGbInsertStxmlFile*)GetAtIndex(nIndex);

		if (pStxmlFile != NULL)
		{
			pStxmlFile->XMatch(oXMatchList);
		}
	}
}

long CGbInsertStxmlFileMngr::GetProgressStepCount()
{
	POS pos = GetHeadPosition();
	CGbInsertStxmlFile *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = (CGbInsertStxmlFile *)GetNext(pos);
		nCount += p->GetCount();
	}

	return nCount;
}

void CGbInsertStxmlFileMngr::InitByCopy(CGbInsertStxmlFileMngr *pSrc)
{
	if (pSrc->GetCount() == 0)
	{
		return;
	}

	//清空链表
	POS pos = GetHeadPosition();
	RemoveAt(pos);
	DeleteAll();
	AddNewChild(m_pHeadStxmlFile);

	pos = pSrc->GetHeadPosition();
	CGbInsertStxmlFile *pFile = NULL;
	CGbInsertStxmlFile *pNew = NULL;
	pFile = (CGbInsertStxmlFile*)pSrc->GetNext(pos);

	m_pHeadStxmlFile->InitByCopy(pFile);

	while (pos != NULL)
	{
		pFile = (CGbInsertStxmlFile*)pSrc->GetNext(pos);
		pNew = NewGbInsertStxmlFile();
		pNew->InitByCopy(pFile);
	}
}

CDataObj *CGbInsertStxmlFileMngr::FindMapDataObj(const CString &strGbtDataID)
{
	return NULL;
}

CExBaseObject* CGbInsertStxmlFileMngr::ExecInsertByBatchItemGroup(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress)
{
	if (GetCount() == 0)
	{
		return NULL;
	}

	Validate();

	POS pos = GetHeadPosition();
	CGbInsertStxmlFile *pStxmlFile = NULL;
	BOOL bInsertFileRoot = TRUE;

	while (pos != NULL)
	{
		pStxmlFile = (CGbInsertStxmlFile *)GetNext(pos);

		//插入子模板的根目录项目
		CItems *pNewItemsFile = GbtWzd_InsertRootItems(pParentItems, pStxmlFile->m_strName, pStxmlFile->m_strID);

		//插入配置文件
		pStxmlFile->InsertIecConfigMacroTest(pNewItemsFile);

		pStxmlFile->ExecInsertByBatchItemGroup(pBatchGroup, pNewItemsFile, oListStxmlItem, pThreadProgress);
	}

	return NULL;
}

void CGbInsertStxmlFileMngr::Validate()
{
	POS pos = GetHeadPosition();
	CGbInsertStxmlFile *p = NULL;
	BOOL bInsertRoot = TRUE;

	if (GetCount() == 1)
	{
		bInsertRoot = FALSE;
	}

	while (pos != NULL)
	{
		p = (CGbInsertStxmlFile *)GetNext(pos);
		p->m_bInsertFileRoot = bInsertRoot;
	}
}

BOOL CGbInsertStxmlFileMngr::ValidateMapKeys(CString &strErrorMsg)
{
	POS pos = GetHeadPosition();
	CGbInsertStxmlFile *pGbInsertStxmlFile = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pGbInsertStxmlFile = (CGbInsertStxmlFile *)GetNext(pos);

		if (!pGbInsertStxmlFile->ValidateMapKeys(strErrorMsg))
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

//////////////////////////////////////////////////////////////////////////

CExBaseObject* CGbWzdDatasetRefMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbWzdDatasetRefKey())
	{
		return new CGbWzdDatasetRef();
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
CGbInsertStxmlFileTool::CGbInsertStxmlFileTool()
{
	m_pGbStxml = NULL;
	m_pWordRptEditSrc = NULL;
	m_pGuideBookDest = NULL;
	m_pWordRptEditDest = NULL;
	m_pParentItems = NULL;
	m_bDataChanged = FALSE;
	m_pNewRootItems = NULL;

// 	m_oGbInsertStxmlFileMngr->SetParent(this);
// 	m_oGbtBatchItemGroups->SetParent(this);

	m_pProgressDlg = NULL;
	m_pInsertThread = NULL;
	m_bExInsertState = FALSE;

	//pThread->ResumeThread();

	m_pGbtBatchItemGroups = new CGbtBatchItemGroups();
	AddNewChild(m_pGbtBatchItemGroups);
	m_pGbInsertStxmlFileMngr = new CGbInsertStxmlFileMngr();
	AddNewChild(m_pGbInsertStxmlFileMngr);
	m_pGbWzdDatasetRefMngr = new CGbWzdDatasetRefMngr();
	AddNewChild(m_pGbWzdDatasetRefMngr);
}

void CGbInsertStxmlFileTool::SetParentWnd(CWnd *pWnd)
{	
	m_pParentWnd = pWnd;
	CGbWzdInsertThread *pThread = CGbWzdInsertThread::CreateTestCtrlThread(m_pParentWnd);
	m_pInsertThread = pThread;
}


CGbInsertStxmlFileTool::~CGbInsertStxmlFileTool()
{
	ClearListDataset();
	Free();
	m_oListStxmlItem.RemoveAll();
	m_oListNewItems.RemoveAll();

	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->DestroyWindow();
		delete m_pProgressDlg;
		m_pProgressDlg = NULL;
	}
}


long CGbInsertStxmlFileTool::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strRootItemsNameKey, oNode, m_strRootItemsName);
	xml_GetAttibuteValue(pXmlKeys->m_strRootItemsIDKey, oNode, m_strRootItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strIec61850ConfigFileKey, oNode, m_strIec61850ConfigFile);

	//m_oGbInsertStxmlFileMngr

	return 0;
}

long CGbInsertStxmlFileTool::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strRootItemsNameKey, oElement, m_strRootItemsName);
	xml_SetAttributeValue(pXmlKeys->m_strRootItemsIDKey, oElement, m_strRootItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strIec61850ConfigFileKey, oElement, m_strIec61850ConfigFile);

	return 0;
}

CExBaseObject* CGbInsertStxmlFileTool::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtBatchItemGroupsKey())
	{
		return new CGbtBatchItemGroups();
	}

	if (strClassID == CGbWzdToolXmlRWKeys::CGbInsertStxmlFileMngrKey())
	{
		return new CGbInsertStxmlFileMngr();
	}

	if (strClassID == CGbWzdToolXmlRWKeys::CGbWzdDatasetRefsKey())
	{
		return new CGbWzdDatasetRefMngr();
	}

	return NULL;
}


void CGbInsertStxmlFileTool::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	CScriptTextMngr *pScriptTextMngr = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBTWZDCLASSID_BTACHITEMGROUPS:
			m_pGbtBatchItemGroups = (CGbtBatchItemGroups*)p;
			break;

		case GBTWZDCLASSID_GBTINSERTSTXMLFILEMNGR:
			m_pGbInsertStxmlFileMngr = (CGbInsertStxmlFileMngr *)p;
			break;

		case GBTWZDCLASSID_GBTDATASETREFMNGR:
			m_pGbWzdDatasetRefMngr = (CGbWzdDatasetRefMngr *)p;
			break;

		default:
			break;
		}
	}

	if (m_pGbtBatchItemGroups == NULL)
	{
		m_pGbtBatchItemGroups = new CGbtBatchItemGroups;
		AddNewChild(m_pGbtBatchItemGroups);
	}

	if (m_pGbInsertStxmlFileMngr == NULL)
	{
		m_pGbInsertStxmlFileMngr = new CGbInsertStxmlFileMngr();
		AddNewChild(m_pGbInsertStxmlFileMngr);
	}

	if (m_pGbWzdDatasetRefMngr == NULL)
	{
		m_pGbWzdDatasetRefMngr = new CGbWzdDatasetRefMngr();
		AddNewChild(m_pGbWzdDatasetRefMngr);
	}
}

void CGbInsertStxmlFileTool::Free()
{
	if (m_pGbStxml != NULL)
	{
		delete m_pGbStxml;
		m_pGbStxml = NULL;
	}

	m_pGbStxml = NULL;

	if (m_pWordRptEditSrc != NULL)
	{
		m_pWordRptEditSrc->ExitWord(FALSE);
		delete m_pWordRptEditSrc;
		m_pWordRptEditSrc = NULL;
	}

	DeleteAll();
	m_pGbtBatchItemGroups = NULL;
	m_pGbInsertStxmlFileMngr = NULL;
	m_pGbWzdDatasetRefMngr = NULL;

	InitAfterRead();
}

BOOL CGbInsertStxmlFileTool::Init(const CString &strStxmlFile)
{
	Free();

	m_strStxmlFile = strStxmlFile;
	m_pWordRptEditSrc = new CWordRptEdit();
	m_pWordRptEditSrc->InitRptEdit();
	m_pGbStxml = new CGuideBook();
	//m_pGbStxml->m_strGuideBookFileType = g_strTGbFileFilter;
	m_pGbStxml->m_strGuideBookFileType = ParseFilePostfix(m_strStxmlFile);
	m_pGbStxml->m_strGuideBookFileType.MakeLower();

	if (m_pWordRptEditDest != NULL)
	{
		m_pWordRptEditSrc->m_WordApp = m_pWordRptEditDest->m_WordApp;
	}

	m_pGbStxml->Open(strStxmlFile);

	//如果是子模板，则处理实例化时的映射关系
	if (m_pGbStxml->m_strGuideBookFileType == g_strTGbFileFilter)
	{
		InitGbtDataInterfaceMaps();
		XMatch();
	}

	return TRUE;
}

BOOL CGbInsertStxmlFileTool::Init(CGuideBook *pGuideBookDest, CXKeyDB *pKeyDB, CWordRptEdit *pWordRptEditDest)
{
	m_pGuideBookDest = pGuideBookDest;
	m_pXKeyDB = pKeyDB;
	m_pWordRptEditDest = pWordRptEditDest;

	ASSERT (m_pGuideBookDest != NULL);
	ASSERT (m_pXKeyDB != NULL);
	//ASSERT (m_pWordRptEditDest != NULL);
	return TRUE;
}

void CGbInsertStxmlFileTool::AddDataset(CDataSet *pDataset)
{
	if (m_listDataset.Find(pDataset) == NULL)
	{
		m_listDataset.AddTail(pDataset);
		m_listRefDatas.Append(pDataset);

		CGbWzdDatasetRef *pNew = new CGbWzdDatasetRef();
		pNew->SetDataSet(pDataset);
		m_pGbWzdDatasetRefMngr->AddNewChild(pNew);
	}

	return;
}

void CGbInsertStxmlFileTool::ClearListDataset()	
{
	m_listDataset.RemoveAll();	
	m_listRefDatas.RemoveAll();	
	m_pGbWzdDatasetRefMngr->DeleteAll();
}

//子模板插入到的项目分类对象，如果没有指定，则插入到Device的根目录下
void CGbInsertStxmlFileTool::SetParentItems(CExBaseList *pParent)
{
	m_pParentItems = pParent;
}

void CGbInsertStxmlFileTool::XMatch(long nIndex)
{
	m_bDataChanged = TRUE;

	m_oXMatchList.DeleteAll();
	m_oXMatchList.Init(&m_listRefDatas, m_pXKeyDB);
	
	m_pGbInsertStxmlFileMngr->XMatch(m_oXMatchList, nIndex);
// 	POS pos = GetHeadPosition();
// 	CGbtDataInterfaceMap *pMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pMap = (CGbtDataInterfaceMap *)GetNext(pos);
// 		pMap->XMatch(m_oXMatchList);
// 	}
}

BOOL CGbInsertStxmlFileTool::ValidateMapKeys(CString &strErrorMsg)
{
	BOOL bTrue = TRUE;
// 	POS pos = GetHeadPosition();
// 	CGbtDataInterfaceMap *pMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pMap = (CGbtDataInterfaceMap *)GetNext(pos);
// 		
// 		if (!pMap->ValidateMapKeys(strErrorMsg))
// 		{
// 			bTrue = FALSE;
// 		}
// 	}

	bTrue = m_pGbInsertStxmlFileMngr->ValidateMapKeys(strErrorMsg);

	return bTrue;
}

BOOL CGbInsertStxmlFileTool::ValidateBatchItemsGroups(CString &strErrorMsg)
{
	return m_pGbtBatchItemGroups->ValidateBatchItemsGroups(strErrorMsg);
}

CDevice* CGbInsertStxmlFileTool::GetCurrDeviceDest()
{
	CDevice *pDevice = NULL;
	
	if (m_pParentItems->GetClassID() == GBCLASSID_DEVICE)
	{
		pDevice = (CDevice*)m_pParentItems;
	}
	else
	{
		pDevice = (CDevice*)m_pParentItems->GetAncestor(GBCLASSID_DEVICE);
	}

	return pDevice;
}

UINT CGbInsertStxmlFileTool::ExecInsertThread(LPVOID pParam)
{
	CGbInsertStxmlFileTool *pTool = (CGbInsertStxmlFileTool*)pParam;

	CWnd *pWnd = CWnd::GetDesktopWindow();
	pTool->m_pProgressDlg = new CThreadProgrssDlg(pWnd);//pTool->m_pParentWnd);
	pTool->m_pProgressDlg->CreateThreadDlg(pWnd, _T(""));//pTool->m_pParentWnd, _T(""));
	//pTool->ExecInsertEx(pTool->m_pProgressDlg);

	while (pTool->m_bExInsertState)
	{
		Sleep(100);
	}

	return 0;
}

CExBaseObject* CGbInsertStxmlFileTool::ExecInsert()
{
	m_bExInsertState = TRUE;

	ExecInsertEx((CGbWzdInsertThread*)m_pInsertThread);
	m_bExInsertState = FALSE;

	return NULL;
}

long CGbInsertStxmlFileTool::GetProgressStepCount()
{
	long nCount = m_pGbInsertStxmlFileMngr->GetProgressStepCount();
	long nBatchGroup = m_pGbtBatchItemGroups->GetCount();

	if (nBatchGroup == 0)
	{
		nBatchGroup = 1;
	}

	return nBatchGroup * nCount * 2 + 4;
}

CExBaseObject* CGbInsertStxmlFileTool::ExecInsertEx(CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->SetMaxRange(GetProgressStepCount());
	}

	InsertRootItems(pThreadProgress);
	InitListStxmlItem();
	InsertSysParas(pThreadProgress);

	if (m_pGbStxml->IsGuideBookTemplateFile())
	{
		wzd_InsertIecConfigMacroTest(m_strIec61850ConfigFile, m_pNewRootItems);

		if (m_pGbtBatchItemGroups->GetCount() == 0)
		{
			//没有批量组别
			InsertByGbtBatchItemGroup(NULL, pThreadProgress);
		}
		else
		{
			if (m_pGbtBatchItemGroups->m_nBatchItemsMode == BATCH_ITEMS_MODE_EXTERNER)
			{
				POS pos = m_pGbtBatchItemGroups->GetHeadPosition();
				CGbtBatchItemGroup *pGroup = NULL;

				while (pos != NULL)
				{
					pGroup = (CGbtBatchItemGroup *)m_pGbtBatchItemGroups->GetNext(pos);
					InsertByGbtBatchItemGroup(pGroup, pThreadProgress);
				}
			}
			else
			{
				POS pos = m_pGbInsertStxmlFileMngr->GetHeadPosition();
				CGbInsertStxmlFile *pStxmlFile = NULL;

				while (pos != NULL)
				{
					pStxmlFile = (CGbInsertStxmlFile *)m_pGbInsertStxmlFileMngr->GetNext(pos);
					pStxmlFile->ExecInsertByBatchItemGroups(m_pGbtBatchItemGroups, m_pNewRootItems, m_oListStxmlItem, pThreadProgress);
				}
			}
		}
	}
	else
	{
		CGbInsertStxmlFile oGbInsertStxmlFile;
		oGbInsertStxmlFile.InitGbFileInsert(m_strStxmlFile, m_pWordRptEditDest, m_pWordRptEditSrc);
		oGbInsertStxmlFile.ExcuteInsertFile(m_pNewRootItems, m_oListStxmlItem, pThreadProgress);
	}

	if (pThreadProgress != NULL)
	{
		pThreadProgress->Exit();
	}

	m_pParentWnd->PostMessage(WM_WZD_INSERT_STXML_FINISH, 0, 0);

	return NULL;
}
void CGbInsertStxmlFileTool::InsertRootItems(CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->StepIt();
		pThreadProgress->ShowMsg(_T("初始化........"));
	}

	m_pNewRootItems = new CItems();
	m_pNewRootItems->m_strName = m_strRootItemsName;
	m_pNewRootItems->m_strID   = m_strRootItemsID;
	m_pParentItems->AddNewChild(m_pNewRootItems);

	m_oListNewItems.AddTail(m_pNewRootItems);
}

void CGbInsertStxmlFileTool::InitListStxmlItem()
{
	CDevice *pDevice = m_pGbStxml->GetDevice();
	pDevice->SelectAllRootItem(m_oListStxmlItem);
}


void CGbInsertStxmlFileTool::InsertSysParas(CThreadProgressInterface *pThreadProgress)
{
	if (pThreadProgress != NULL)
	{
		pThreadProgress->StepIt();
		pThreadProgress->ShowMsg(_T("处理子模板测试参数........"));
	}

	CDevice *pDeviceSrc = m_pGbStxml->GetDevice();
	CDevice *pDeviceDest = m_pGuideBookDest->GetDevice();

	CSysParas *pSysParaSrc = pDeviceSrc->GetSysParas();
	CSysParas *pSysParaDest = pDeviceDest->GetSysParas();

	POS pos = pSysParaSrc->GetHeadPosition();
	CDataObj *pData = NULL;
	CDataObj *pNew = NULL;

	while (pos != NULL)
	{
		pData = (CDataObj *)pDeviceSrc->GetNext(pos);

		if (pSysParaDest->FindByID(pData->m_strID) == NULL)
		{
			pNew = (CDataObj *)pData->Clone();
			pSysParaDest->AddNewChild(pNew);
		}
	}
}
// 
// BOOL CGbInsertStxmlFileTool::ExecInsert(CXMatchList &oXMatchList)
// {
// 	return FALSE;
// }

void CGbInsertStxmlFileTool::InitGbtDataInterfaceMaps()
{
	CDevice *pDevice = m_pGbStxml->GetDevice();
	ASSERT (pDevice != NULL);

	if (pDevice == NULL)
	{
		return;
	}

	m_pGbInsertStxmlFileMngr->InitGbtDataInterfaceMaps(pDevice, m_strStxmlFile, m_pWordRptEditDest, m_pWordRptEditSrc);
	m_pGbtBatchItemGroups->InitListBatchItem(m_pGbStxml);

// 	CGbtDataInterfaces *pGbtDataInterfaces =pDevice->m_pGbtDataInterfaces;
// 	ASSERT (pGbtDataInterfaces != NULL);
// 
// 	if (pGbtDataInterfaces == NULL)
// 	{
// 		return;
// 	}
// 
// 	POS pos = pGbtDataInterfaces->GetHeadPosition();
// 	CGbtDataInterface *pGbtDataInterface = NULL;
// 	CGbtDataInterfaceMap *pNew = NULL;
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = pGbtDataInterfaces->GetNext(pos);
// 
// 		if (p->GetClassID() == GBCLASSID_GBTDATAINTERFACE)
// 		{
// 			pGbtDataInterface = (CGbtDataInterface *)p;
// 			pNew = new CGbtDataInterfaceMap();
// 			AddNewChild(pNew);
// 			pNew->InitGbtDataInterface(pGbtDataInterface);
// 		}
// 	}
}
// 
// void CGbInsertStxmlFileTool::InsertStxmlWord(CItems *pCurrItems)
// {
// 	if (m_pWordRptEditDest == NULL)
// 	{
// 		return;
// 	}
// 
// 	m_pWordRptEditSrc->m_dwMaxBkmkIndex = m_pWordRptEditDest->m_dwMaxBkmkIndex + 1;
// 	m_pWordRptEditSrc->OpenWord(m_strStxmlFile);
// 
// 	//更名标签
// 	RenameRptBkmks(pCurrItems);
// 
// 	//插入到Word文档末尾
// 	m_pWordRptEditDest->InsertWordEdit(m_pWordRptEditSrc);
// 	m_pWordRptEditSrc->CloseWord();
// 	m_pWordRptEditDest->m_dwMaxBkmkIndex  = m_pWordRptEditSrc->m_dwMaxBkmkIndex + 1;
// }
// 
// void CGbInsertStxmlFileTool::RenameRptBkmks(CExBaseList *pList)
// {
// 	POS pos = pList->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CExBaseObject *)pList->GetNext(pos);
// 
// 		if (p->GetClassID() == RPTCLASSID_RPTBKMK)
// 		{
// 			RenameRptBkmk(p);
// 		}
// 		else if (p->IsBaseList())
// 		{
// 			RenameRptBkmks((CExBaseList*)p);
// 		}
// 	}
// }
// 
// void CGbInsertStxmlFileTool::RenameRptBkmk(CExBaseObject *pBkmk)
// {
// 	CRptBkmk *p = (CRptBkmk *)pBkmk;
// 
// 	m_pWordRptEditSrc->UpdateBkmk(p);
// }
// 

void CGbInsertStxmlFileTool::InsertByGbtBatchItemGroup(CGbtBatchItemGroup *pBatchGroup, CThreadProgressInterface *pThreadProgress)
{
	//每一个grou，创建一个Items
	if (pBatchGroup != NULL)
	{
		CItems *pNewItems = new CItems();
		pNewItems->m_strName = pBatchGroup->m_strName;
		pNewItems->m_strID = pBatchGroup->m_strID;
		m_pNewRootItems->AddNewChild(pNewItems, TRUE);
		m_pGbInsertStxmlFileMngr->ExecInsertByBatchItemGroup(pBatchGroup, pNewItems, m_oListStxmlItem, pThreadProgress);
	}
	else
	{	
		//没有定义批量插入组别，则直插入子模板组的项目
		m_pGbInsertStxmlFileMngr->ExecInsertByBatchItemGroup(pBatchGroup, m_pNewRootItems, m_oListStxmlItem, pThreadProgress);
	}
}



void CGbInsertStxmlFileTool::OpenWzdFile(const CString &strWzdFile)
{
	CGbInsertStxmlFileTool oTool;
	oTool.OpenXmlFile(strWzdFile, CGbWzdToolXmlRWKeys::CGbInsertStxmlFileToolKey(), CGbWzdToolXmlRWKeys::g_pXmlKeys);

	m_strRootItemsID = oTool.m_strRootItemsID;
	m_strRootItemsName = oTool.m_strRootItemsName;
	m_strName = oTool.m_strName;
	m_strID = oTool.m_strID;
	m_strIec61850ConfigFile = oTool.m_strIec61850ConfigFile;

	//初始化数据集
	InitDatasetList(oTool.m_pGbWzdDatasetRefMngr);

	//初始化子模板文件组
	InitGbInsertStxmlFileMngr(oTool.m_pGbInsertStxmlFileMngr);

	//初始化批量组
	InitGbtBatchItemGroups(oTool.m_pGbtBatchItemGroups);
}

void CGbInsertStxmlFileTool::InitDatasetList(CGbWzdDatasetRefMngr *pWzdDatasetMngr)
{
	ClearListDataset();
	POS pos = pWzdDatasetMngr->GetHeadPosition();
	CGbWzdDatasetRef *pRef = NULL;
	CDataSet *pDataset = NULL;

	CDevice *pDevice = m_pGuideBookDest->GetDevice();
	ASSERT (pDevice != NULL);

	if (pDevice == NULL)
	{
		return;
	}

	while (pos != NULL)
	{
		pRef = (CGbWzdDatasetRef *)pWzdDatasetMngr->GetNext(pos);
		pDataset = pDevice->SelectDataSet(pRef->m_strID);

		if (pDataset != NULL)
		{
			AddDataset(pDataset);
		}
	}
}

void CGbInsertStxmlFileTool::InitGbtBatchItemGroups(CGbtBatchItemGroups *pGbtBatchItemGroups)
{
	m_pGbtBatchItemGroups->InitByCopy(pGbtBatchItemGroups);
}

void CGbInsertStxmlFileTool::InitGbInsertStxmlFileMngr(CGbInsertStxmlFileMngr *pGbInsertStxmlFileMngr)
{
	m_pGbInsertStxmlFileMngr->InitByCopy(pGbInsertStxmlFileMngr);
}

//////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DYNCREATE(CGbWzdInsertThread, CWinThread)

CGbWzdInsertThread::CGbWzdInsertThread()
{
	m_pProgressDlg = NULL;
	memset(m_pszMessage, 0, 4096);
	m_nMaxRange = 100;
	m_pParentWnd = NULL;
}


CGbWzdInsertThread::~CGbWzdInsertThread()
{
	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->DestroyWindow();
		delete m_pProgressDlg;
		m_pProgressDlg = NULL;
	}
}


BOOL CGbWzdInsertThread::InitInstance()
{
	CLogPrint::LogString(LOGLEVEL_TRACE, L"TestWorkThread::InitInstance");

	CWnd *pWnd = CWnd::GetDesktopWindow();
	CThreadProgrssDlg *pProgressDlg = new CThreadProgrssDlg(pWnd);//pTool->m_pParentWnd);
	pProgressDlg->CreateThreadDlg(pWnd, _T(""));//pTool->m_pParentWnd, _T(""));
	pProgressDlg->SetMaxRange(m_nMaxRange);

	m_pProgressDlg = pProgressDlg;
	m_pProgressDlg->ShowWindow(SW_HIDE);

	return TRUE;
}

int CGbWzdInsertThread::ExitInstance()
{
	int nReturn = CWinThread::ExitInstance();

	return nReturn;
}


BEGIN_MESSAGE_MAP(CGbWzdInsertThread, CWinThread)
	//{{AFX_MSG_MAP(CGbWzdInsertThread)
	ON_THREAD_MESSAGE(WM_USER + 2355, On2355)
	ON_THREAD_MESSAGE(WM_USER + 2356, On2356)
	ON_THREAD_MESSAGE(WM_USER + 2357, On2357)
	ON_THREAD_MESSAGE(WM_USER + 2358, On2358)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGbWzdInsertThread message handlers

void CGbWzdInsertThread::On2355(WPARAM wParam, LPARAM lParam)
{
	m_nMaxRange = wParam;

	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->ShowWindow(SW_SHOW);
		m_pProgressDlg->SetMaxRange(wParam);
		m_pProgressDlg->ResetProcess();
		CRect rc;
		m_pProgressDlg->GetWindowRect(&rc);
		m_pProgressDlg->SetWindowPos(&CWnd::wndTopMost, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
	}
}

void CGbWzdInsertThread::On2356(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->ResetProcess();
	}
}

void CGbWzdInsertThread::On2357(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		//m_pProgressDlg->StepIt();
		m_pProgressDlg->StepPos(m_nStepIndex);
	}
}

void CGbWzdInsertThread::On2358(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		CString strMsg ;
		strMsg = m_pszMessage;
		m_pProgressDlg->ShowMsg(strMsg);
	}
}
