#include "StdAfx.h"
#include "GbtDataBatchSclChMap.h"
#include "..\..\XLanguageResourceAts.h"

CGbtDataBatchSclChMap::CGbtDataBatchSclChMap()
{
	m_pDataObj = NULL;
	m_pSclGinCh = NULL;
}

CGbtDataBatchSclChMap::~CGbtDataBatchSclChMap()
{

}

CGbtDataBatchSclChMapGen::CGbtDataBatchSclChMapGen(void)
{
	SetAutoNameID(TRUE);
	m_strName = g_sLangTxt_DataBatch/*L"数据集遍历批量"*/;

	m_strDataTypeFilter = _T("BOOLEAN");
}

CGbtDataBatchSclChMapGen::~CGbtDataBatchSclChMapGen(void)
{
	m_listDatas.RemoveAll();
	m_listDataset.RemoveAll();
}

void CGbtDataBatchSclChMapGen::AddDataset(CExBaseList *pDataset)	
{
	m_listDatas.Append(pDataset);
	m_listDataset.AddTail(pDataset);
}

void CGbtDataBatchSclChMapGen::AddDatasets(CExBaseList *pDatasets)
{
	POS posDs = pDatasets->GetHeadPosition();
	CExBaseList *pDataset = NULL;

	while (posDs != NULL)
	{
		pDataset = (CExBaseList *)pDatasets->GetNext(posDs);
		AddDataset(pDataset);
	}
}

void CGbtDataBatchSclChMapGen::SetGbInsertStxmlFileMngr(CGbInsertStxmlFileMngr *pStxmlFileMngr)
{
	ASSERT (pStxmlFileMngr != NULL);
	ASSERT(pStxmlFileMngr->GetCount() == 1);
	ASSERT(pStxmlFileMngr->m_pHeadStxmlFile != NULL);

	if (pStxmlFileMngr->GetCount() > 1)
	{
		return;
	}

	m_pGbInsertStxmlFile = pStxmlFileMngr->m_pHeadStxmlFile;
}
// 
// void CGbtDataBatchSclChMapGen::SetGbtBatchItemGroups(CGbtBatchItemGroups *pBatchItemGroups)
// {
// 	ASSERT (pBatchItemGroups != NULL);
// 
// 	if (pBatchItemGroups == NULL)
// 	{
// 		return;
// 	}
// 
// 	m_pBatchItemGroups = pBatchItemGroups;
// 	InitGbtDatasRampObj();
// }

void CGbtDataBatchSclChMapGen::OpenDinWzdFromSclGinChsFile(const CString &strFile)
{
	m_oDinWzdFromSclGinChs.DeleteAll();
	m_oDinWzdFromSclGinChs.OpenXmlFile(strFile, CGbWzdToolXmlRWKeys::g_pXmlKeys);
	
	Match();
}

void CGbtDataBatchSclChMapGen::Match()
{
	InitGbtDataBatchSclChMapGen();
	m_oXMatchTool.Match(m_pXKeyDB, &m_listDatas, &m_oDinWzdFromSclGinChs);

	POS pos = GetHeadPosition();
	CGbtDataBatchSclChMap *p = NULL;
	CXMatchList *pXMatchList = m_oXMatchTool.GetDstMatchList();

	while (pos != NULL)
	{
		p = (CGbtDataBatchSclChMap *)GetNext(pos);
		InitMapObj(p, pXMatchList);
	}
}

CExBaseList* CGbtDataBatchSclChMapGen::GetXMatchList(CGbtDataBatchSclChMap *pSclChMap)
{
	CXMatchList *pXMatchList = m_oXMatchTool.GetDstMatchList();

	return GetXMatchList(pSclChMap, pXMatchList);
}

void CGbtDataBatchSclChMapGen::InitMatchFirst()
{
	POS pos = GetHeadPosition();
	CGbtDataBatchSclChMap *p = NULL;
	CExBaseList *pListMatch = NULL;
	CXMatchList *pXMatchList = m_oXMatchTool.GetDstMatchList();

	while (pos != NULL)
	{
		p = (CGbtDataBatchSclChMap *)GetNext(pos);
		pListMatch = GetXMatchList(p, pXMatchList);

		if (pListMatch == NULL)
		{
			continue;
		}

		if(pListMatch->GetCount() > 0)
		{
			p->m_pDataObj = (CDataObj *)pListMatch->GetHead();
		}
	}
}

void CGbtDataBatchSclChMapGen::InitGbtDataBatchSclChMapGen()
{
	DeleteAll();

	POS pos = m_oDinWzdFromSclGinChs.GetHeadPosition();
	CDinWzdFromSclGinCh *p = NULL;

	while (pos != NULL)
	{
		p = (CDinWzdFromSclGinCh *)m_oDinWzdFromSclGinChs.GetNext(pos);

		if (m_strDataTypeFilter == _T("none"))
		{
			CGbtDataBatchSclChMap *pNew = new CGbtDataBatchSclChMap();
			pNew->m_pSclGinCh = p;
			AddTail(pNew);
		}
		else
		{
			if (m_strDataTypeFilter == p->m_strDataType)
			{
				CGbtDataBatchSclChMap *pNew = new CGbtDataBatchSclChMap();
				pNew->m_pSclGinCh = p;
				AddTail(pNew);
			}
		}
	}
	

// 	POS posDs = m_listDataset.GetHeadPosition();
// 	CExBaseList *pDataset = NULL;
// 	POS posData = NULL;
// 	CDataObj *pData = NULL;
// 	CGbtDataBatchSclChMap *pNew = NULL;
// 
// 	while (posDs != NULL)
// 	{
// 		pDataset = (CExBaseList *)m_listDataset.GetNext(posDs);
// 		posData = pDataset->GetHeadPosition();
// 
// 		while (posData != NULL)
// 		{
// 			pData = (CDataObj*)pDataset->GetNext(posData);
// 			CGbtDataBatchSclChMap *pNew = new CGbtDataBatchSclChMap();
// 			pNew->m_pDataObj = pData;
// 			AddTail(pData);
// 		}
// 	}
}


void CGbtDataBatchSclChMapGen::InitMapObj(CGbtDataBatchSclChMap *SclChMap, CXMatchList *pDstXMatchList)
{
	POS pos = pDstXMatchList->GetHeadPosition();
	CXMatchObject *p = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject*)pDstXMatchList->GetNext(pos);

		if (p->m_pRefObject == SclChMap->m_pSclGinCh)
		{
			if (p->m_listMacthRefObject.GetCount() == 1)
			{
				SclChMap->m_pDataObj = (CDataObj*)p->m_listMacthRefObject.GetHead();
			}
			else
			{
				SclChMap->m_pDataObj = NULL;
			}
		}
	}
}

CExBaseList* CGbtDataBatchSclChMapGen::GetXMatchList(CGbtDataBatchSclChMap *pSclChMap, CXMatchList *pDstXMatchList)
{
	POS pos = pDstXMatchList->GetHeadPosition();
	CXMatchObject *p = NULL;
	CExBaseList *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject*)pDstXMatchList->GetNext(pos);

		if (p->m_pRefObject == pSclChMap->m_pSclGinCh)
		{
			pFind = &p->m_listMacthRefObject;
			break;
		}
	}

	return pFind;
}

void CGbtDataBatchSclChMapGen::InitGbtDatasRampObj()
{
// 	ASSERT (m_pBatchItemGroups != NULL);
// 	ASSERT (m_pBatchItemGroups->m_pGbtBatchItemGroupRef != NULL);
// 	ASSERT (m_pBatchItemGroups->m_pGbtBatchItemGroupRef->GetClassID() == GBTWZDCLASSID_BATCHGBTDATAGROUP);
// 
// 	CGbtBatchGbtDataGroup *pGbtDatasGroup = (CGbtBatchGbtDataGroup*)m_pBatchItemGroups->m_pGbtBatchItemGroupRef;
// 	POS pos = pGbtDatasGroup->GetHeadPosition();
// 	CGbtBatchGbtDataRef *pBatchGbtData = NULL;
// 	CGbtDataBatchSclChMap *pNew = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pBatchGbtData = (CGbtBatchGbtDataRef *)pGbtDatasGroup->GetNext(pos);
// 		pNew = CGbtDataBatchSclChMap::_New(pBatchGbtData);
// 		AddNewChild(pNew);
// 	}
}


void CGbtDataBatchSclChMapGen::InitNameIDAuto()
{
// 	if (!m_bAutoNameID)
// 	{
// 		return;
// 	}
// 
// 	POS pos = m_pBatchItemGroups->GetHeadPosition();
// 	CGbtBatchItemGroup *pGroup = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pGroup = (CGbtBatchItemGroup *)m_pBatchItemGroups->GetNext(pos);
// 		InitNameIDAuto(pGroup);
// 	}

}

void CGbtDataBatchSclChMapGen::InitNameIDAuto(CGbtBatchItemGroup *pGroup)
{
// 	POS pos = pGroup->GetHeadPosition();
// 	CGbtBatchGbtDataRef *pGbtDataRef = NULL;
// 	CString strName, strID;
// 
// 	while (pos != NULL)
// 	{
// 		pGbtDataRef = (CGbtBatchGbtDataRef *)pGroup->GetNext(pos);
// 		strName.AppendFormat(_T("%s=%s;"), pGbtDataRef->m_strName, pGbtDataRef->m_strGbtDataValue);
// 		strID.AppendFormat(_T("%s%s_"), pGbtDataRef->m_strID, pGbtDataRef->m_strGbtDataValue);
// 	}
// 
// 	strName = strName.Left(strName.GetLength() - 1);
// 	strID = strID.Left(strID.GetLength() - 1);
// 	strID.Replace(_T("i_"), _T(""));
// 	strID.Replace(_T("."), _T(""));
// 
// 	pGroup->m_strName = strName;
// 	pGroup->m_strID   = strID;
}


void CGbtDataBatchSclChMapGen::InitAllDataObj(CExBaseList &listSclChMap)
{
	POS pos = GetHeadPosition();
	CGbtDataBatchSclChMap *p = NULL;

	while (pos != NULL)
	{
		p = (CGbtDataBatchSclChMap *)GetNext(pos);

		if (p->m_pDataObj != NULL)
		{
			listSclChMap.AddTail(p);
		}
	}
}

BOOL CGbtDataBatchSclChMapGen::CanRunTraverse(CString &strMsg, long &nRowIndex)
{
	POS pos = GetHeadPosition();
	CGbtDataBatchSclChMap *p = NULL;
	BOOL bCan = TRUE;
	CXMatchList *pXMatchList = m_oXMatchTool.GetDstMatchList();
	CExBaseList *pListDatas = NULL;
	nRowIndex = 0;

	while (pos != NULL)
	{
		p = (CGbtDataBatchSclChMap *)GetNext(pos);
		pListDatas = GetXMatchList(p, pXMatchList);

		if (p->m_pDataObj == NULL)
		{
			if (pListDatas->GetCount() > 1)
			{
				strMsg.Format(/*_T("【%s】关联关系不唯一")*/g_sLangTxt_RelNotOnly, p->m_pSclGinCh->m_strName);
				bCan = FALSE;
				break;
			}
		}

		nRowIndex++;
	}

	return bCan;
}

void CGbtDataBatchSclChMapGen::Traverse()
{
	CExBaseList listSclChMap;
	InitAllDataObj(listSclChMap);
	long nCount = listSclChMap.GetCount();

	m_pGbInsertStxmlFile->m_pGbtDataInterfaces->SetGbtDataInterfaceCount(nCount);
	POS pos = listSclChMap.GetHeadPosition();
	m_pGbInsertStxmlFile->UpdateGbtDataInterfaceMaps();
	CGbtDataBatchSclChMap *pSclChMap = NULL;
	CGbtDataInterfaceMap  *pGbtDataInterfaceMap = NULL;
	POS posGbt = m_pGbInsertStxmlFile->GetHeadPosition();

	while (pos != NULL && posGbt != NULL)
	{
		pSclChMap = (CGbtDataBatchSclChMap *)GetNext(pos);
		pGbtDataInterfaceMap = (CGbtDataInterfaceMap*)m_pGbInsertStxmlFile->GetNext(posGbt);

		if (pSclChMap == NULL || pGbtDataInterfaceMap == NULL)
		{
			break;
		}

		Traverse(pSclChMap, pGbtDataInterfaceMap);
	}

	listSclChMap.RemoveAll();
}



void CGbtDataBatchSclChMapGen::Traverse(CGbtDataBatchSclChMap *pSclChMap, CGbtDataInterfaceMap *pGbtDataInterfaceMap)
{
	pGbtDataInterfaceMap->m_strName = pSclChMap->m_pDataObj->m_strName;
	pGbtDataInterfaceMap->m_strID = pSclChMap->m_pDataObj->m_strID;
	pGbtDataInterfaceMap->m_pGbtDataInterface->m_strName = pSclChMap->m_pDataObj->m_strName;//pGbtDataInterfaceMap->m_strName;
	pGbtDataInterfaceMap->m_pGbtDataInterface->m_strID = pSclChMap->m_pDataObj->m_strID;//pGbtDataInterfaceMap->m_strName;

	CGbtDataScriptMap *pGbtDataScriptMap = NULL;
	
	//app-id
	pGbtDataScriptMap = (CGbtDataScriptMap*)pGbtDataInterfaceMap->FindByID(_T("i_DvmData"));
	if (pGbtDataScriptMap != NULL)
	{
		pGbtDataScriptMap->SetRefObject(pSclChMap->m_pDataObj);
		pGbtDataScriptMap->m_strRefObjPath = pSclChMap->m_pDataObj->GetIDPathEx(GBCLASSID_CPUS, FALSE);
		pGbtDataScriptMap->m_strRefObjName = pSclChMap->m_pDataObj->m_strName;
	}

	pGbtDataScriptMap = (CGbtDataScriptMap*)pGbtDataInterfaceMap->FindByID(_T("i_AppID"));
	if (pGbtDataScriptMap != NULL)
	{
		pGbtDataScriptMap->m_strDataValue = pSclChMap->m_pSclGinCh->m_strAppID;
	}

	pGbtDataScriptMap = (CGbtDataScriptMap*)pGbtDataInterfaceMap->FindByID(_T("i_ChIndex"));
	if (pGbtDataScriptMap != NULL)
	{
		pGbtDataScriptMap->m_strDataValue = pSclChMap->m_pSclGinCh->m_strGsChIndex;
	}
}
