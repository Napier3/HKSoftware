#include "StdAfx.h"
#include "GbtBatchDatasetTraverse.h"
#include "..\..\XLanguageResourceAts.h"
CGbtBatchDatasetTraverse::CGbtBatchDatasetTraverse(void)
{
	m_strName = /*L"数据集遍历批量"*/g_sLangTxt_DataBatch;
}

CGbtBatchDatasetTraverse::~CGbtBatchDatasetTraverse(void)
{
	m_listAllDataObj.RemoveAll();
}

void CGbtBatchDatasetTraverse::SetGbInsertStxmlFileMngr(CGbInsertStxmlFileMngr *pStxmlFileMngr)
{
	ASSERT (pStxmlFileMngr != NULL);
	ASSERT(pStxmlFileMngr->GetCount() == 1);
	ASSERT(pStxmlFileMngr->m_pHeadStxmlFile != NULL);

	if (pStxmlFileMngr->GetCount() > 1)
	{
		return;
	}

	m_pGbInsertStxmlFile = pStxmlFileMngr->m_pHeadStxmlFile;
	InitGbtDatasTraverseObj();
}

void CGbtBatchDatasetTraverse::InitGbtDatasTraverseObj()
{
	ASSERT (m_pGbInsertStxmlFile != NULL);
	ASSERT (m_pGbInsertStxmlFile->m_pGbtDataInterfaces != NULL);

	CGbtDatas *pGbtDatas = m_pGbInsertStxmlFile->m_pGbtDataInterfaces->m_pGbtDatas;
	POS pos = pGbtDatas->GetHeadPosition();
	CGbtData *pGbtData = NULL;
	CGbtDataTraverseObj *pNew = NULL;

	while (pos != NULL)
	{
		pGbtData = (CGbtData *)pGbtDatas->GetNext(pos);

		if (pGbtData->IsGbtScriptObj())
		{
			pNew = CGbtDataTraverseObj::_New(pGbtData);
			AddNewChild(pNew);
		}
	}
}

void CGbtBatchDatasetTraverse::Traverse(CExBaseList *pDatasetList)
{
	InitAllDataObj(pDatasetList);
	long nCount = m_listAllDataObj.GetCount();

	m_pGbInsertStxmlFile->m_pGbtDataInterfaces->SetGbtDataInterfaceCount(nCount);
	POS pos = GetHeadPosition();
	m_pGbInsertStxmlFile->UpdateGbtDataInterfaceMaps();
	CGbtDataTraverseObj *pGbtDataTraverseObj = NULL;

	while (pos != NULL)
	{
		pGbtDataTraverseObj = (CGbtDataTraverseObj *)GetNext(pos);
		Traverse(pGbtDataTraverseObj);
	}
}

void CGbtBatchDatasetTraverse::InitAllDataObj(CExBaseList *pDatasetList)
{
	POS pos = pDatasetList->GetHeadPosition();
	CExBaseList *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CExBaseList *)pDatasetList->GetNext(pos);
		m_listAllDataObj.Append(pDataset);
	}
}

void CGbtBatchDatasetTraverse::Traverse(CGbtDataTraverseObj *pGbtDataTraverseObj)
{
	long nIndex = 0;
	POS pos = m_pGbInsertStxmlFile->GetHeadPosition();
	CGbtDataInterfaceMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CGbtDataInterfaceMap *)m_pGbInsertStxmlFile->GetNext(pos);
		Traverse(pGbtDataTraverseObj, pMap, nIndex);
		nIndex++;
	}
}

void CGbtBatchDatasetTraverse::Traverse(CGbtDataTraverseObj *pGbtDataTraverseObj, CGbtDataInterfaceMap *pGbtDataInterfaceMap, long nIndex)
{
	if (pGbtDataTraverseObj->IsModelTypeDataset())
	{
		Traverse_Dataset(pGbtDataTraverseObj, pGbtDataInterfaceMap, nIndex);
		return;
	}

	if (pGbtDataTraverseObj->IsModelTypeValRamp())
	{
		Traverse_ValRamp(pGbtDataTraverseObj, pGbtDataInterfaceMap, nIndex);
		return;
	}
}

void CGbtBatchDatasetTraverse::Traverse_Dataset(CGbtDataTraverseObj *pGbtDataTraverseObj, CGbtDataInterfaceMap *pGbtDataInterfaceMap, long nIndex)
{
	CDataObj *pData = (CDataObj*)m_listAllDataObj.GetAtIndex(nIndex);
	ASSERT( pData != NULL);
	CGbtDataScriptMap *pGbtDataScriptMap = (CGbtDataScriptMap*)pGbtDataInterfaceMap->FindByID(pGbtDataTraverseObj->m_pDataRef->m_strID);
	ASSERT (pGbtDataScriptMap != NULL);

	if (pGbtDataScriptMap != NULL)
	{
		pGbtDataScriptMap->SetRefObject(pData);
		pGbtDataScriptMap->m_strRefObjPath = pData->GetIDPathEx(GBCLASSID_CPUS, FALSE);
		pGbtDataScriptMap->m_strRefObjName = pData->m_strName;
		pGbtDataInterfaceMap->m_strName = pData->m_strName;
		pGbtDataInterfaceMap->m_strID = pData->m_strID;
		pGbtDataInterfaceMap->m_pGbtDataInterface->m_strName = pData->m_strName;//pGbtDataInterfaceMap->m_strName;
		pGbtDataInterfaceMap->m_pGbtDataInterface->m_strID = pData->m_strID;//pGbtDataInterfaceMap->m_strName;
	}

}

void CGbtBatchDatasetTraverse::Traverse_ValRamp(CGbtDataTraverseObj *pGbtDataTraverseObj, CGbtDataInterfaceMap *pGbtDataInterfaceMap, long nIndex)
{
	double dValue = pGbtDataTraverseObj->m_dBeginVal + pGbtDataTraverseObj->m_dStep * nIndex;
	CString strValue;
	strValue.Format(_T("%f"), dValue);
	ChopFloatString(strValue, -1);

	CGbtDataScriptMap *pGbtDataScriptMap = (CGbtDataScriptMap*)pGbtDataInterfaceMap->FindByID(pGbtDataTraverseObj->m_pDataRef->m_strID);
	ASSERT (pGbtDataScriptMap != NULL);

	if (pGbtDataScriptMap != NULL)
	{
		pGbtDataScriptMap->SetRefObject(NULL);
		pGbtDataScriptMap->m_strDataValue = strValue;
		pGbtDataScriptMap->m_strRefObjPath.Empty();
		pGbtDataScriptMap->m_strRefObjName.Empty();
	}
}


