#include "StdAfx.h"
#include "DataSetGroup.h"
// #include "Set.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDataSetGroup::CDataSetGroup(void)
{
	m_strName = _T("DatasetGroup");
	m_strID = m_strName;
}

CDataSetGroup::~CDataSetGroup(void)
{
}

long CDataSetGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataSet::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CDataSetGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataSet::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CDataSetGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDataSet::SerializeOwn(oBinaryBuffer);

	return 0;
}

CExBaseObject* CDataSetGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strDataSetGroupKey)
	{
		return new CDataSetGroup();
	}
	else
	{
		return CDataSet::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
	}
}

CExBaseObject* CDataSetGroup::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_DATASETGROUP)
	{
		return new CDataSetGroup();
	}
	else
	{
		return CDataSet::CreateNewChild(nClassID);
	}
}

CBaseObject* CDataSetGroup::Clone()
{
	CDataSetGroup* pDataSetGroup = new CDataSetGroup();
	Copy(pDataSetGroup);

	return pDataSetGroup;
}

CBaseObject* CDataSetGroup::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CDataSetGroup *pNew = new CDataSetGroup();

	if(bCopyOwn)
	{
		CopyOwn(pNew);
	}

	if(bCopyChildren)
	{
		CopyChildren(pNew);
	}	

	return pNew;
}

BOOL CDataSetGroup::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_DATAOBJ
		|| nClassID == GBCLASSID_DATASETGROUP)
	{
		return TRUE;
	}

	return FALSE;
}


long CDataSetGroup::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BSTR CDataSetGroup::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strDataSetGroupKey;     
}

CDataSetGroup* CDataSetGroup::FindByDataType(const CString &strDataType)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDataSetGroup *pFind = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATASETGROUP)
		{
			if (((CDataSetGroup*)p)->m_strType == strDataType)
			{
				return (CDataSetGroup*)p;
			}
		}
	}

	return NULL;
}

CDataSetGroup* CDataSetGroup::FindByDataType(const CString &strDataType, long nFindIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDataSetGroup *pFind = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATASETGROUP)
		{
			if (((CDataSetGroup*)p)->m_strType == strDataType)
			{
				if (nIndex == nFindIndex)
				{
					return (CDataSetGroup*)p;
				}
				else
				{
					nIndex++;
				}
			}
		}
	}

	return NULL;
}

long CDataSetGroup::FindByDataType(const CString &strDataType, CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDataSetGroup *pFind = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATASETGROUP)
		{
			if (((CDataSetGroup*)p)->m_strType == strDataType)
			{
				oList.AddTail(p);
			}
		}
	}

	return oList.GetCount();
}

long CDataSetGroup::FindByDataType_Data(const CString &strDataType, CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			if (((CDataObj*)p)->m_strDataType == strDataType)
			{
				oList.AddTail(p);
			}
		}
	}

	return oList.GetCount();
}


CDataSetGroup* CDataSetGroup::AddNewGroup(const CString &strName, const CString &strID, const CString &strDataType)
{
	CDataSetGroup *pNew = new CDataSetGroup();
	pNew->m_strName = strName;
	pNew->m_strID = strID;
	pNew->m_strType = strDataType;

	AddNewChild(pNew, TRUE);

	return pNew;
}

CDataObj* CDataSetGroup::InsertData(CDataObj *pData)
{
	CExBaseList listParents;
	pData->GetAllAncestorEqClassID(&listParents, GetClassID());
	CDataSetGroup *p = NULL;
	CDataSetGroup *pFind = NULL;
	CDataSetGroup *pCurr = this;

	POS pos = listParents.GetHeadPosition();

	if (pos != NULL)
	{//跳过根节点
		listParents.GetNext(pos);
	}

	while (pos != NULL)
	{
		p = (CDataSetGroup *)listParents.GetNext(pos);
		pFind = (CDataSetGroup *)pCurr->FindByID(p->m_strID);

		if (pFind == NULL)
		{
			pFind = (CDataSetGroup *)p->CloneEx(TRUE, FALSE);
			pCurr->AddNewChild(pFind);
			pCurr = pFind;
		}
		else
		{
			pCurr = pFind;
		}
	}

	CDataObj *pNew = (CDataObj*)pData->CloneEx(TRUE, TRUE);
	pCurr->AddNewChild(pNew);
	listParents.RemoveAll();

	return pNew;
}

CDataObj* CDataSetGroup::FindByID_InAllChildren(const CString &strID)
{
	CDataObj *pFind = NULL;
	pFind = (CDataObj*)FindByID(strID);

	if (pFind != NULL)
	{
		return pFind;
	}

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;


	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATASETGROUP)
		{
			pFind = ((CDataSetGroup*)p)->FindByID_InAllChildren(strID);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

CDataObj* CDataSetGroup::FindDataByID(const CString &strID)
{
	CString strDatasetPath = GetIDPathEx(GBCLASSID_CPU, TRUE);
	long nLen = strDatasetPath.GetLength();
	CString strTemp = strID.Left(nLen);
	CDataObj *pFind = NULL;

	if (strTemp == strDatasetPath)
	{
		strTemp = strID.Mid(nLen+1);
	}
	else
	{
		strTemp = strID;
	}

	pFind =FindByID_InChildren(strTemp);

	if (pFind == NULL)
	{//找每个DataObj
		pFind = FindByID_InAllChildren(strID);
	}

	return pFind;
}

CDataObj* CDataSetGroup::FindByID_InChildren(const CString &strID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDataObj *pFind = NULL;
	CString strTemp;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATASETGROUP)
		{
			strTemp = p->m_strID + _T("$");

			if (strTemp == strID.Left(strTemp.GetLength()))
			{
				strTemp = strID.Mid(strTemp.GetLength());
				pFind = ((CDataSetGroup*)p)->FindByID_InChildren(strTemp);
			}
		}
		else
		{
			if (strID == p->m_strID)
			{
				pFind = (CDataObj *)p;
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

long CDataSetGroup::SelectAllDatas(CExBaseList &listDatas)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATASETGROUP)
		{
			((CDataSetGroup*)p)->SelectAllDatas(listDatas);
		}
		else
		{
			listDatas.AddTail(p);
		}
	}

	return listDatas.GetCount();
}

void CDataSetGroup::WriteTo(CDvmDatasetGroup *pDest)
{
	pDest->m_strName = m_strName;
	pDest->m_strID = m_strID;
	pDest->m_strDataType = m_strType;
}

void CDataSetGroup::ReadFrom(CDvmDatasetGroup *pSrc)
{
	m_strName = pSrc->m_strName;
	m_strID = pSrc->m_strID ;
	m_strType = pSrc->m_strDataType;
}

CDvmDataset* CDataSetGroup::GetWriteDvmDataset(CValues *pValues)
{
	CDvmDatasetGroup *pDvmDataset = new CDvmDatasetGroup();

	if (pValues == NULL)
	{
		GetWriteDvmDatasetG(pDvmDataset);
	}
	else
	{
		GetWriteDvmDatasetG(pDvmDataset, pValues);
	}

	return pDvmDataset;
}


void CDataSetGroup::GetWriteDvmDatasetG(CDvmDataset *pDvmDataset)
{
	POS pos = NULL;
	CDataObj *pData = NULL;
	CExBaseObject *p = NULL;

	pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATASETGROUP)
		{
			CDataSetGroup *pGbGroup = (CDataSetGroup*)p;
			CDvmDatasetGroup *pNew = new CDvmDatasetGroup();
			pGbGroup->WriteTo(pNew);
			pDvmDataset->AddNewChild(pNew);
			pGbGroup->GetWriteDvmDatasetG(pNew);
		}
		else
		{
			pData = (CDataObj *)p;
			CDvmData *pNew = new CDvmData();
			pData->WriteToData(pNew);
			pDvmDataset->AddNewChild(pNew);
		}
	}
}

CDvmData* CDataSetGroup::AddData(CDvmDatasetGroup *pRoot, CDataObj *pData, CValues *pValues)
{
	CDvmData *pNewData = new CDvmData;

	pRoot->AddNewChild(pNewData);
	pData->AddToDvm(pNewData);

	pNewData->InitByValues(pValues);

	return pNewData;
}
void CDataSetGroup::GetWriteDvmDatasetG(CDvmDatasetGroup *pRoot, CValues *pValues)
{
	POS pos = GetHeadPosition();
	CValue *pValue = NULL;
	CExBaseObject *p = NULL;
	CDvmData *pNew = NULL;
	CExBaseObject *pDevice = (CExBaseObject*)GetAncestor(GBCLASSID_DEVICE);

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATAOBJ)
		{
			CString strID = ((CDataObj*)p)->GetIDPath_Root_Dataset();
			pValue = (CValue*)pValues->FindByID(strID);

			if (pValue != NULL)
			{
				pNew = AddData(pRoot, (CDataObj*)p, (CValues*)pValues);
				pNew->m_strValue = Gb_CalValue(pDevice, pValue);
				((CDataObj*)p)->m_strValue = pNew->m_strValue; // 保存计算的数据
			}
			}
		else
		{
			CDvmDatasetGroup *pNewDvmGroup = new CDvmDatasetGroup();
			pRoot->AddNewChild(pNewDvmGroup);
			((CDataSetGroup*)p)->InitDvmDataGroup(pNewDvmGroup);
			((CDataSetGroup*)p)->GetWriteDvmDatasetG(pNewDvmGroup, pValues);
		}
	}
}

CDvmData* CDataSetGroup::InsertData(CDvmDatasetGroup *pRoot, CDataObj *pData)
{
	CExBaseList listParents;
	pData->GetAllAncestorEqClassID(&listParents, GetClassID());
	CDataSetGroup *p = NULL;
	CDvmDatasetGroup *pFind = NULL;
	CDvmDatasetGroup *pCurr = pRoot;

	POS pos = listParents.GetHeadPosition();

	if (pos != NULL)
	{//跳过根节点
		listParents.GetNext(pos);
	}

	while (pos != NULL)
	{
		p = (CDataSetGroup *)listParents.GetNext(pos);
		pFind = (CDvmDatasetGroup*)pCurr->FindByID(p->m_strID);

		if (pFind == NULL)
		{
			pFind = new CDvmDatasetGroup();
			p->WriteTo(pFind);
			pCurr->AddNewChild(pFind);
			pCurr = pFind;
		}
		else
		{
			pCurr = pFind;
		}
	}

	CDvmData *pNew = new CDvmData();
	pData->WriteToData(pNew);
	pCurr->AddNewChild(pNew);
	listParents.RemoveAll();

	return pNew;
}

void  CDataSetGroup::InitValueByDvmDataset(CDvmDataset *pDataset, BOOL bSetMinMax, DWORD dwMode_Name_ID)
{
	CDataObj *pDataObj = NULL;
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmDatasetGroup *pDvmDatasetGroup = NULL;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pDataset->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			InitValueByDvmData((CDvmData*)p, bSetMinMax, dwMode_Name_ID);
		}
		else
		{
			CDataSetGroup *pGbGroup = (CDataSetGroup*)FindByID(p->m_strID);

			if (pGbGroup == NULL)
			{
				//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("data group [%s][%s] not exist in guidebook device")
				//	, p->m_strName.GetString(), p->m_strID.GetString());
			}
			else
			{
				if (pGbGroup->GetClassID() == GBCLASSID_DATASETGROUP)
				{
					pGbGroup->InitValueByDvmDataset((CDvmDatasetGroup*)p, bSetMinMax, dwMode_Name_ID);
				}
				else
				{
					//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("data group [%s][%s] not exist in guidebook device")
					//	, p->m_strName.GetString(), p->m_strID.GetString());
				}
			}
		} 
	}
}

//2021-10-22  lijunqing
void CDataSetGroup::InitDvmDataGroup(CDvmDatasetGroup *pDvmGroup)
{
	pDvmGroup->m_strName = m_strName;
	pDvmGroup->m_strID = m_strID;
	pDvmGroup->m_strDataType = m_strType;
}

//shaolei 2022-12-06   CDataSet对象转换成CDvmDataset对象
void CDataSetGroup::Data_Gb_to_Dvm(CDvmDataset *pDestDvm)
{
	CDvmDatasetGroup *pDestDvmGroup = (CDvmDatasetGroup *)pDestDvm;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CDataObj *pDataObj = NULL;
	CDataSetGroup *pDataSetGrp = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmDatasetGroup *pDvmDatasetGroup = NULL;

	pDestDvmGroup->m_strID = m_strID;
	pDestDvmGroup->m_strName = m_strName;
	pDestDvmGroup->m_strDataType = m_strType;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_DATAOBJ)
		{
			pDataObj = (CDataObj*)pObj;
			pDvmData = new CDvmData();
			pDestDvmGroup->AddNewChild(pDvmData);
			pDataObj->Data_Gb_to_Dvm(pDvmData);
		}
		else if (nClassID == GBCLASSID_DATASETGROUP)
		{
			pDataSetGrp = (CDataSetGroup *)pObj;
			pDvmDatasetGroup = new CDvmDatasetGroup();
			pDestDvmGroup->AddNewChild(pDvmDatasetGroup);
			pDataSetGrp->Data_Gb_to_Dvm(pDvmDatasetGroup);
		}
		
	}
}