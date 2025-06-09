#include "stdafx.h"
#include "GbtBatchItem.h"
#include "GbInsertStxmlFileTool.h"
#include "..\XLanguageResourceAts.h"
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

long CGbtBatchItemRefValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseKey, oNode, m_nUse);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CGbtBatchItemRefValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
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

long CGbtBatchItemRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDatasetPathKey, oNode, m_strDatasetPath);

	return 0;
}

long CGbtBatchItemRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
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

void CGbtBatchItemRef::InitReplace()
{
	POS pos =GetHeadPosition();
	CGbtBatchItemRefValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CGbtBatchItemRefValue *)GetNext(pos);
		pValue->InitReplace();
	}
}

CGbtBatchItemGroup::CGbtBatchItemGroup()
{
	m_strName = /*_T("批量枚举组")*/g_sLangTxt_BatchEnumGroup;
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

long CGbtBatchItemGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbtBatchItemGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
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

void CGbtBatchItemGroup::InitReplace()
{
	CGbtBatchItemRef *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CGbtBatchItemRef *)GetNext(pos);
		p->InitReplace();
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
			strErrorMsg = /*_T("批量项目没有输入ID")*/g_sLangTxt_BatchItemNoId;
			break;
		}

		if (pItemRef->m_strName.GetLength() == 0)
		{
			bTrue = FALSE;
			strErrorMsg = /*_T("批量项目没有输入名称")*/g_sLangTxt_BatchItemNoName;
			break;
		}

		if (pItemRef->m_strDatasetPath.GetLength() == 0)
		{
			bTrue = FALSE;
			strErrorMsg = /*_T("批量项目没有关联数据集")*/g_sLangTxt_BatchItemNoDataset;
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
		pDevice->GetDataSetList(pNew->m_strDatasetPath, oListDataset, DSID_ALL_DVM);

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


//////////////////////////////////////////////////////////////////////////

CGbtBatchGbtDataRef::CGbtBatchGbtDataRef()
{
	CGbItemVariableIDReplace::g_bShowReplaceItemPath = FALSE;
	
}

CGbtBatchGbtDataRef::~CGbtBatchGbtDataRef()
{
	CGbItemVariableIDReplace::g_bShowReplaceItemPath = TRUE;
}

CBaseObject* CGbtBatchGbtDataRef::Clone()
{
	CGbtBatchGbtDataRef *pNew = new CGbtBatchGbtDataRef();
	Copy(pNew);
	return pNew;
}

BOOL CGbtBatchGbtDataRef::CopyOwn(CBaseObject* pDest)
{
	((CGbtBatchGbtDataRef*)pDest)->m_strGbtDataValue = m_strGbtDataValue;

	return CExBaseObject::CopyOwn(pDest);
}

long CGbtBatchGbtDataRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strGbtDataValue);

	return 0;
}

long CGbtBatchGbtDataRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strGbtDataValue);

	return 0;
}

void CGbtBatchGbtDataRef::InitByCopy(CGbtBatchGbtDataRef *pSrc)
{
	m_strGbtDataValue = pSrc->m_strGbtDataValue;
	m_strName = pSrc->m_strName;
	m_strID = pSrc->m_strID;
}

void CGbtBatchGbtDataRef::InitBatchItemRef(CGbtData *pGbtData)
{
	m_strGbtDataValue = pGbtData->m_strValue;
	m_strName = pGbtData->m_strName;
	m_strID = pGbtData->m_strID;
}

void CGbtBatchGbtDataRef::InitReplace()
{
	
}

//////////////////////////////////////////////////////////////////////////
CGbtBatchGbtDataGroup::CGbtBatchGbtDataGroup()
{
	m_strName = /*_T("批量枚举组")*/g_sLangTxt_BatchEnumGroup;
	m_strID = _T("BatchEnum");
}

CGbtBatchGbtDataGroup::~CGbtBatchGbtDataGroup()
{

}

CBaseObject* CGbtBatchGbtDataGroup::Clone()
{
	CGbtBatchGbtDataGroup *pNew = new CGbtBatchGbtDataGroup();
	Copy(pNew);
	return pNew;
}

BOOL CGbtBatchGbtDataGroup::CopyOwn(CBaseObject* pDest)
{
	return CExBaseObject::CopyOwn(pDest);
}

long CGbtBatchGbtDataGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbtBatchGbtDataGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}


CExBaseObject* CGbtBatchGbtDataGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtBatchGbtDataRefKey())
	{
		return new CGbtBatchGbtDataRef();
	}

	return NULL;
}


void CGbtBatchGbtDataGroup::InitByCopy(CGbtBatchItemGroup *pSrc)
{
	POS pos = GetHeadPosition();
	CGbtBatchGbtDataRef *p = NULL;
	CGbtBatchGbtDataRef *pFind = NULL;

	m_strID = pSrc->m_strID;
	m_strName = pSrc->m_strName;

	while (pos != NULL)
	{
		p = (CGbtBatchGbtDataRef *)GetNext(pos);
		pFind = (CGbtBatchGbtDataRef *)pSrc->FindByID(p->m_strID);

		if (pFind != NULL)
		{
			p->InitByCopy(pFind);
		}
	}
}


CGbtBatchGbtDataRef* CGbtBatchGbtDataGroup::NewBatchGbtDataRef(CExBaseObject *pData)
{
	CGbtBatchGbtDataRef *pNew = NULL;
	CGbtData *pGbtData = (CGbtData*)pData;

	if (!pGbtData->IsBatchObj())
	{
		return NULL;
	}

	pNew = new CGbtBatchGbtDataRef();
	pNew->InitBatchItemRef(pGbtData);

	return pNew;
}


BOOL CGbtBatchGbtDataGroup::HasBatchItems()
{
	return (GetCount() > 0);
}

BOOL CGbtBatchGbtDataGroup::IsAllCommCmdItems()
{
	return FALSE;
}

BOOL CGbtBatchGbtDataGroup::IsAllMacroTestItems()
{
	return FALSE;
}

long CGbtBatchGbtDataGroup::GetValuesCount()
{
	long nCount = GetCount();

	return nCount;
}

void CGbtBatchGbtDataGroup::InitReplace()
{
	CGbtBatchGbtDataRef *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CGbtBatchGbtDataRef *)GetNext(pos);
		p->InitReplace();
	}
}

void CGbtBatchGbtDataGroup::InitByGbtDatas(CGbtDatas *pGbtDatas)
{
	POS pos = pGbtDatas->GetHeadPosition();
	CGbtData *pData = NULL;
	CGbtBatchGbtDataRef *pNew = NULL;

	while (pos != NULL)
	{
		pData = (CGbtData *)pGbtDatas->GetNext(pos);

		if (pData->IsBatchObj())
		{
			pNew = new CGbtBatchGbtDataRef();
			pNew->InitBatchItemRef(pData);
			AddNewChild(pNew);
		}
	}
}

BOOL CGbtBatchGbtDataGroup::ValidateBatchItemsGroup(CString &strErrorMsg)
{
	BOOL bTrue = TRUE;

	if (m_strID.GetLength() == 0)
	{
		bTrue = FALSE;
		strErrorMsg = /*_T("批量项目没有输入ID")*/g_sLangTxt_BatchItemNoId;
	}

	if (m_strName.GetLength() == 0)
	{
		bTrue = FALSE;
		strErrorMsg = /*_T("批量项目没有输入名称")*/g_sLangTxt_BatchItemNoName;
	}

	return bTrue;
}

//////////////////////////////////////////////////////////////////////////
CGbtBatchItemGroups::CGbtBatchItemGroups()
{
	m_pGbtBatchItemGroupRef = NULL;//new CGbtBatchItemGroup();
	m_nBatchVariableMode = BATCHMODE_ITEM;
	m_nBatchItemsMode = BATCH_ITEMS_MODE_EXTERNER;
	//m_pGbtBatchItemGroupRef->SetParent(this);
}

CGbtBatchItemGroups::~CGbtBatchItemGroups()
{
	FreeBatchItemGroupRef();
}

long CGbtBatchItemGroups::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strBatchVariableModeKey, oNode, m_nBatchVariableMode);
	xml_GetAttibuteValue(pXmlKeys->m_strBatchItemsModeKey, oNode, m_nBatchItemsMode);

	return 0;
}

long CGbtBatchItemGroups::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
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

	if (strClassID == CGbWzdToolXmlRWKeys::CGbtBatchGbtDataGroupKey())
	{
		return new CGbtBatchGbtDataGroup();
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

	if (pHead->GetClassID() == GBTWZDCLASSID_BATCHGBTDATAGROUP)
	{
		for (nRefIndex = 0; nRefIndex<nRefCount; nRefIndex++)
		{	
			CGbtBatchGbtDataRef *pSrcRef = (CGbtBatchGbtDataRef*)pHead->GetAtIndex(nRefIndex);
			CGbtBatchGbtDataRef *pDestRef = (CGbtBatchGbtDataRef*)m_pGbtBatchItemGroupRef->GetAtIndex(nRefIndex);

			if (pDestRef !=NULL)
			{
				pDestRef->m_strGbtDataValue = pSrcRef->m_strGbtDataValue;
			}
		}
	}
	else
	{
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
	FreeBatchItemGroupRef();
	ASSERT (pDevice->m_pGbtDataInterfaces != NULL);

	if (pDevice->m_pGbtDataInterfaces->IsBatchGbtDataMode())
	{//数据接口批量模式
		CGbtBatchGbtDataGroup *pGbtBatchGbtDataGroup = new CGbtBatchGbtDataGroup();
		pGbtBatchGbtDataGroup->InitByGbtDatas(pDevice->m_pGbtDataInterfaces->m_pGbtDatas);
		m_pGbtBatchItemGroupRef = pGbtBatchGbtDataGroup;
		m_nBatchVariableMode = BATCHMODE_GBTDATA;
	}
	else
	{//通讯命令批量模式
		m_pGbtBatchItemGroupRef = new CGbtBatchItemGroup();
		CExBaseList oListItems;
		pDevice->SelectAllRootItem(oListItems);
		InitListBatchItemRef(&oListItems);
		oListItems.RemoveAll();
		m_nBatchVariableMode = BATCHMODE_ITEM;
	}

	m_pGbtBatchItemGroupRef->SetParent(this);
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

void CGbtBatchItemGroups::SetBatchItemGroupCount(long nCount)
{
	long nOldCount = GetCount();
	long nIndex = 0;

	if (nOldCount == nCount)
	{
		return;
	}

	if (nOldCount < nCount)
	{
		for (nIndex=0; nIndex<nCount - nOldCount; nIndex++)
		{
			NewBatchItemGroup();
		}

		return;
	}

	for (nIndex=0; nIndex<nOldCount - nCount; nIndex++)
	{
		Delete(nCount);
	}
}

BOOL CGbtBatchItemGroups::IsBatchGbtDataMode()
{
	ASSERT (m_pGbtBatchItemGroupRef != NULL);

	if (m_pGbtBatchItemGroupRef == NULL)
	{
		return FALSE;
	}

	return (m_pGbtBatchItemGroupRef->GetClassID() == GBTWZDCLASSID_BATCHGBTDATAGROUP);
}

BOOL CGbtBatchItemGroups::IsBatchItemMode()
{
	ASSERT (m_pGbtBatchItemGroupRef != NULL);

	if (m_pGbtBatchItemGroupRef == NULL)
	{
		return FALSE;
	}

	return (m_pGbtBatchItemGroupRef->GetClassID() == GBTWZDCLASSID_BATCHITEMGROUP);
}


//////////////////////////////////////////////////////////////////////////
//映射组别功能
