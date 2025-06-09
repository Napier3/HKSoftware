#include "StdAfx.h"
#include "DataSet.h"
// #include "Set.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDataSet::CDataSet(void)
{
	m_strName = g_sLangTxt_DataSets/*_T("数据集")*/;
}

CDataSet::~CDataSet(void)
{
}


CDataObj* CDataSet::InsertData(CDataObj *pData)
{
	CDataObj *pNew = (CDataObj*)pData->CloneEx(TRUE, FALSE);
	AddNewChild(pNew);

	return pNew;
}


long CDataSet::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strRWAttrKey, oNode, m_strRWAttr);

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CDataSet::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strRWAttrKey, oElement, m_strRWAttr);

	if (m_strType.GetLength() == 0)
	{
		m_strType = m_strID;
	}
	
	return 0;
}

long CDataSet::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_strType);
		BinarySerializeCalLen(oBinaryBuffer,m_strRWAttr);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_strType);
		BinarySerializeRead(oBinaryBuffer,m_strRWAttr);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strType);
		BinarySerializeWrite(oBinaryBuffer,m_strRWAttr);
	}
	
	return 0;
}

CExBaseObject* CDataSet::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strDataKey)
	{
		return new CDataObj();
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strLogCtrlKey)
	{//2018-3-4  lijq
		return new CDataObj();
	}

	return NULL;
}

CExBaseObject* CDataSet::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_DATAOBJ)
	{
		return new CDataObj();
	}
	else
	{
		ASSERT (FALSE);
	}

	return NULL;
}

CBaseObject* CDataSet::Clone()
{
	CDataSet* pDataSet = new CDataSet();
	Copy(pDataSet);

	return pDataSet;
}

CBaseObject* CDataSet::CloneEx(BOOL bCopyOwn/*=TRUE*/,BOOL bCopyChildren/*=FALSE*/)
{
	CDataSet *p = new CDataSet();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CDataSet::CanPaste(UINT nClassID)
{
	if (nClassID != GBCLASSID_DATAOBJ)
	{
		return FALSE;
	}

	return TRUE;
}


BSTR CDataSet::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey;     
}

void CDataSet::SetDataSetValue(CValues* pValues)
{
	CValue *pValue = NULL;
	CDataObj *pData = NULL;
	POS pos = pValues->GetHeadPosition();
	CExBaseObject *pCpu = (CExBaseObject *)GetParent();
	CString strPath;
    strPath.Format(_T("%s$%s$"), pCpu->m_strID.GetString(), m_strID.GetString());
	CString strID;
	long nPos = 0;

	while (pos != NULL)
	{
		pValue = (CValue*)pValues->GetNext(pos);

		if (pValue->m_strValue.GetLength() == 0)
		{
			continue;
		}

		nPos = pValue->m_strID.Find(strPath);

		if (nPos >= 0)
		{
			nPos += strPath.GetLength();
			strID = pValue->m_strID.Mid(nPos);
		}
		else
		{
			strID = pValue->m_strID;
		}

		pData = (CDataObj*)FindByID(strID);

		if (pData != NULL)
		{
			pData->m_strValue = pValue->m_strValue;
		}
	}
}

void CDataSet::InitValueByDatas(CShortDatas *pDatas)
{
	CShortData *pSet = NULL;
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pSet = (CShortData *)GetNext(pos);
		pData = (CShortData*)pDatas->FindByName(pSet->m_strName);

		if (pData != NULL)
		{
			pSet->m_strValue = pData->m_strValue;
			continue;
		}

		pData = (CShortData*)pDatas->FindByID(pSet->m_strID);

		if (pData != NULL)
		{
			pSet->m_strValue = pData->m_strValue;
			continue;
		}
	}
}

void CDataSet::InitValueByDvmDataset(CDvmDataset *pSrcDataset)
{
	CDataObj *pSet = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pSet = (CDataObj *)GetNext(pos);
		pData = (CDvmData*)pSrcDataset->FindByID(pSet->m_strID);

		if (pData != NULL)
		{
			pSet->m_strValue = pData->m_strValue;
			continue;
		}

		pData = (CDvmData*)pSrcDataset->FindByName(pSet->m_strName);

		if (pData != NULL)
		{
			pSet->m_strValue = pData->m_strValue;
			continue;
		}
	}
}

void CDataSet::WriteToDatas(CShortDatas *pDatas)
{
	CShortData *pSet = NULL;
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pSet = (CShortData *)GetNext(pos);
		pData = new CShortData();
		pSet->Copy(pData);
		pDatas->AddNewChild(pData);
	}
}

CDataObj* CDataSet::AddNewDataObj(CShortData *pData)
{
	CDataObj *pNew = (CDataObj*)FindByID(pData->m_strID);

	if (pNew != NULL)
	{
		return pNew;
	}
	
	pNew = new CDataObj();
	pNew->m_strName = pData->m_strName;
	pNew->m_strID = pData->m_strID;
	pNew->m_strDataType = pData->m_strDataTypeID;
	pNew->m_strDefaultValue = pData->m_strDefaultValue;
	pNew->m_strValue = pData->m_strValue;
	pNew->m_strUnit = pData->m_strUnit;
	AddNewChild(pNew);

	return pNew;
}

CDataObj* CDataSet::AddNewDataObj(CDvmData *pData)
{
	CDataObj *pNew = (CDataObj*)FindByID(pData->m_strID);

	if (pNew == NULL)
	{
		pNew = new CDataObj();
		AddNewChild(pNew);
		pNew->m_strName = pData->m_strName;
		pNew->m_strID = pData->m_strID;
		pNew->m_strDataType = pData->m_strDataType;
		pNew->m_strUnit = pData->m_strUnit;
	}

	pNew->m_strDefaultValue = pData->m_strValue;
	pNew->m_strValue = pData->m_strValue;

	return pNew;
}

CDataObj* CDataSet::AddNewDataObj(const CString &strName, const CString &strID)
{
	CDataObj *pNew = new CDataObj();
	pNew->m_strName = strName;
	pNew->m_strID = strID;
	AddNewChild(pNew);
	return pNew;
}

CValues* CDataSet::GetValues()
{
	CValues *pValues = new CValues();
	POS pos = GetHeadPosition();
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDataObj *)GetNext(pos);
		pValues->AddNew(pData->m_strID, pData->m_strName, pData->m_strValue);
	}

	return pValues;
}

CDataObj* CDataSet::FindByNameEx(CDvmData *pDataSrc)
{
	CDataObj *p = NULL;
	CDataObj *pFind = NULL;
	POS pos = GetHeadPosition();
	CExBaseList oListFind;

	while (pos != NULL)
	{
		p = (CDataObj *)GetNext(pos);

		if (p->m_strName == pDataSrc->m_strName)
		{
			oListFind.AddTail(p);
		}
	}

	if (oListFind.GetCount() == 0)
	{
		return NULL;
	}

	if (oListFind.GetCount() == 1)
	{//只有一个对象，返回
		pFind = (CDataObj *)oListFind.GetHead();
		oListFind.RemoveAll();
		return pFind;
	}
	
	pos = oListFind.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDataObj *)oListFind.GetNext(pos);

		if (p->CmpDataType(pDataSrc))
		{//查找数据类型相同的对象，如果是结构体的定值，则需要判断子对象
			pFind = p;
			break;
		}
	}

	if (pFind == NULL)
	{
		pFind = (CDataObj *)oListFind.GetHead();
	}

	oListFind.RemoveAll();
	return pFind;
}

long CDataSet::CompareVersionInfo(CDvmData *pStandInfo, CDvmDataset *pRlstDs)
{
	long nIndex = 0;
	long nRslt = 1;
	
	//数据集第一条是无效信息
	if ((GetCount() - 1) != pStandInfo->GetCount())
	{
		return 0;
	}

	CDataObj *pDataObj = NULL;
	CDvmValue *pStandValue = NULL;
	long nCount = pStandInfo->GetCount();

	while (nIndex < nCount)
	{
		pDataObj = (CDataObj *)GetAt(nIndex+1);
		pStandValue = (CDvmValue *)pStandInfo->GetAt(nIndex);
		
		ASSERT(pDataObj != NULL);

		if (pDataObj == NULL)
		{
			return 0;
		}

		ASSERT(pStandValue != NULL);

		if (pStandValue == NULL)
		{
			return 0;
		}

		if (pDataObj->m_strValue != pStandValue->m_strValue)
		{
			nRslt = 0;
			CDvmData *pData = new CDvmData;
			pData->m_strName = pDataObj->m_strName;
			pData->m_strValue = pDataObj->m_strValue;
			pData->m_strID = pDataObj->m_strID;

			pRlstDs->AddNewChild(pData);
		}

		nIndex++;
	}

	return nRslt;
}

//全部转成小写，兼容大小写
void CDataSet::GetDataObjsByNameHas(const CString &strDataNameHas, CExBaseList *pList)
{
	POS pos = GetHeadPosition();
	CString strNameHas = strDataNameHas;
	strNameHas.MakeLower();
	CString strDataName;

	while (pos != NULL)
	{
		CDataObj *pData = (CDataObj *)GetNext(pos);
		strDataName = pData->m_strName;
		strDataName.MakeLower();

		if (strDataName.Find(strNameHas) >= 0)
		{
			pList->AddTail(pData);
		}
	}
}

//模型更新  shaolei 20220716
void CDataSet::UpdateDataObjValue(CDataSet *pSrcDataSet, BOOL bNewNotExist)
{
	POS pos = pSrcDataSet->GetHeadPosition();
	CDataObj *pSrcDataObj = NULL;
	CDataObj *pDstDataObj = NULL;
	CString strSrcID;

	while (pos != NULL)
	{
		pSrcDataObj = (CDataObj *)pSrcDataSet->GetNext(pos);
		strSrcID = pSrcDataObj->m_strID;
		pDstDataObj = (CDataObj *)FindByID(strSrcID);

		if (pDstDataObj == NULL)
		{
			if (bNewNotExist)
			{
				pDstDataObj = (CDataObj *)pSrcDataObj->CloneEx(TRUE,TRUE);
				AddNewChild(pDstDataObj);
				continue;
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("设备数据模型更新，数据【%s】未找到"), strSrcID.GetString());
				continue;
			}
		}
		else
		{
			//pDstDataObj->InitValueByData(pSrcDataObj);
			pDstDataObj->m_strValue = pSrcDataObj->m_strValue;
			pDstDataObj->UpdateDataObjValue(pSrcDataObj, bNewNotExist);
		}
	}
}

void  CDataSet::InitValueByDvmData(CDvmData *pDvmData, BOOL bSetMinMax, DWORD dwMode_Name_ID)
{
	CDataObj *pDataObj = NULL;

	if (dvm_dataset_find_mode_id(dwMode_Name_ID))
	{
		pDataObj = (CDataObj*)FindByID(pDvmData->m_strID);

		if (pDataObj != NULL)
		{
			pDataObj->InitValueByData(pDvmData, bSetMinMax);
			return;
		}

		pDataObj = (CDataObj*)FindDataObjByID_Has2(pDvmData->m_strID);

		if (pDataObj != NULL)
		{
			pDataObj->InitValueByData(pDvmData, bSetMinMax);
			return;
		}
	}

	if (dvm_dataset_find_mode_name(dwMode_Name_ID))
	{
		pDataObj = (CDataObj*)FindByNameEx(pDvmData);

		if (pDataObj != NULL)
		{
			pDataObj->InitValueByData(pDvmData, bSetMinMax);
			return;
		}
	}

#ifndef _PSX_QT_LINUX_
	if (pDataObj == NULL)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DataDataUnExist/*_T("数据【%s】在数据集【%s】不存在")*/, pDvmData->m_strID.GetString(), m_strID.GetString());
	}
#endif
}

void  CDataSet::InitValueByDvmDataset(CDvmDataset *pDataset, BOOL bSetMinMax, DWORD dwMode_Name_ID)
{
	CDataObj *pDataObj = NULL;
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;

	while (pos != NULL)
	{
		pDvmData = (CDvmData*)pDataset->GetNext(pos);
		InitValueByDvmData(pDvmData, bSetMinMax, dwMode_Name_ID);
    }
}

void CDataSet::InitValueByDataset(CDataSet *pSrcDataset)
{
	CDataObj *pDataObj = NULL;
	POS pos = pSrcDataset->GetHeadPosition();
	CDataObj *pDvmData = NULL;

	while (pos != NULL)
	{
		pDvmData = (CDataObj*)pSrcDataset->GetNext(pos);
		pDataObj = (CDataObj*)FindByID(pDvmData->m_strID);

		if (pDataObj != NULL)
		{
			pDataObj->InitValueByData(pDvmData);
			continue;
		}

#ifndef _PSX_QT_LINUX_
        if (pDataObj == NULL)
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DataDataUnExist/*_T("数据【%s】在数据集【%s】不存在")*/, pDvmData->m_strID, m_strID);
		}
#endif
    }
}

long CDataSet::GetValueLong(const CString &strValueID)
{
	CDataObj *pDataObj = NULL;
	long nValue = 0;

    if (::IsStringNumber(strValueID.GetString()))
	{
		nValue = CString_To_long(strValueID);
	}
	else
	{
		pDataObj = (CDataObj *)FindByID(strValueID);

		if (pDataObj != NULL)
		{
			nValue = CString_To_long(pDataObj->m_strValue);
		}
	}

	return nValue;
}

double CDataSet::GetValueDouble(const CString &strValueID)
{
	CDataObj *pDataObj = NULL;
	double dValue = 0;

    if (::IsStringNumber(strValueID.GetString()))
	{
		dValue = CString_To_double(strValueID);
	}
	else
	{
		pDataObj = (CDataObj *)FindByID(strValueID);

		if (pDataObj != NULL)
		{
			dValue = CString_To_double(pDataObj->m_strValue);
		}
	}

	return dValue;
}

//获取所有子对象，及嵌套子对象的名称；
//子对象和嵌套子对象有CDataObj，CDataObjValue，故直接返回字符串
CString CDataSet::FindDataObjValue_Name(const CString &strIDPath)
{
	//strIDPath = file$name
	CDataObj *pDataObj = NULL;
	CExBaseObject *pObj = NULL;

	pDataObj = (CDataObj *)FindDataByID(strIDPath);

	if (pDataObj != NULL)
	{
		return pDataObj->m_strName;
	}

	CString strName;
	long nPos = strIDPath.Find(_T("$"));

	if (nPos < 0)
	{
		return strName;
	}

	CString strLeft, strRight;
	strLeft = strIDPath.Left(nPos);
	strRight = strIDPath.Mid(nPos + 1);

	while(strLeft.GetLength() > 0)
	{
		pObj = FindByID(strLeft);

		if (pObj == NULL)
		{
			return strName;
		}

		if (strRight.GetLength() > 0)
		{
			nPos = strRight.Find(_T("$"));

			if (nPos < 0)
			{
				//说明是叶子节点了
				if (IsBaseList(pObj->GetClassID()))
				{
					pObj = ((CExBaseList *)pObj)->FindByID(strRight);

					if (pObj != NULL)
					{
						return pObj->m_strName;
					}
				}
			}
			else
			{
				strLeft = strRight.Left(nPos);
				strRight = strRight.Mid(nPos + 1);
			}
		}
		else
		{
			strName = pObj->m_strName;
		}
	}

	return strName;
}

void  CDataSet::WriteToDvmDataset(CDvmDataset *pDataset)
{
	CDataObj *pDataObj = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pDvmData = NULL;

	while (pos != NULL)
	{
		pDataObj = (CDataObj*)GetNext(pos);
		pDvmData = new CDvmData();
		pDataset->AddNewChild(pDvmData);

		pDvmData->m_strName = pDataObj->m_strName;
		pDvmData->m_strID = pDataObj->m_strID;
		pDvmData->m_strDataType = pDataObj->m_strDataType;
		pDvmData->m_strValue = pDataObj->m_strValue;
		pDvmData->m_strUnit = pDataObj->m_strUnit;
	}
}

void  CDataSet::AddToDvmDataset(CDvmDataset *pDataset)
{
	CDataObj *pDataObj = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pDataObj = (CDataObj*)GetNext(pos);
		pFind = (CDvmData*)pDataset->FindByName(pDataObj->m_strName);

		if (pFind == NULL)
		{
			pFind = (CDvmData*)pDataset->FindByID(pDataObj->m_strID);
		}
		
		if (pFind == NULL)
		{
			pDvmData = new CDvmData();
			pDataset->AddNewChild(pDvmData);
			pDataObj->AddToDvm(pDvmData);
// 			pDvmData->m_strName = pDataObj->m_strName;
// 			pDvmData->m_strID = pDataObj->m_strID;
// 			pDvmData->m_strDataType = pDataObj->m_strDataTypeID;
// 			pDvmData->m_strUnit = pDataObj->m_strUnit;
		}
		else
		{
			pDvmData = pFind;
		}

		pDvmData->m_strValue = pDataObj->m_strValue;
	}
}

CDataObj* CDataSet::FindDataByID(const CString &strID)
{
	CString strDatasetPath = GetIDPathEx(GBCLASSID_CPU, TRUE);
	long nLen = strDatasetPath.GetLength();
	CString strTemp = strID.Left(nLen);
	CDataObj *pFind = NULL;

	if (strTemp == strDatasetPath)
	{
		strTemp = strID.Mid(nLen+1);
		pFind = (CDataObj*)FindByID(strTemp);
	}
	else
	{
		pFind = (CDataObj*)FindByID(strID);
	}

	return pFind;
}

CDataObj* CDataSet::FindDataObjByID_Has(const CString &strIDPath)
{
	CDataObj *pDataObj = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;
	long nLen1, nLen2;

	while (pos != NULL)
	{
		pDataObj = (CDataObj*)GetNext(pos);
		nLen1 = pDataObj->m_strID.GetLength();
		nLen2 = strIDPath.GetLength();
		
		if (nLen2 == nLen1)
		{
			if(pDataObj->m_strID == strIDPath)
			{
				pFind = pDataObj;
				break;
			}
		}

		else if (nLen2 > nLen1)
		{
			if (strIDPath.GetAt(nLen2 - nLen1 - 1) == '$')
			{	
				if(strIDPath.Right(nLen1) == pDataObj->m_strID)
				{
					pFind = pDataObj;
					break;
				}
			}
		}
		else if (nLen2 < nLen1)
		{
			if (pDataObj->m_strID.GetAt(nLen1 - nLen2 - 1) == '$')
			{
				if(pDataObj->m_strID.Right(nLen2) == strIDPath)
				{
					pFind = pDataObj;
					break;
				}
			}
		}
	}

	return pFind;
}

CDataObjValue* CDataSet::FindDataObjValueByID_Has(const CString &strIDPath)
{
	CDataObj *pDataObj = NULL;
	POS pos = GetHeadPosition();
	CDataObjValue *pFind = NULL;

	while (pos != NULL)
	{
		pDataObj = (CDataObj*)GetNext(pos);
		pFind = (CDataObjValue *)pDataObj->FindDataObjValueByID_Has(strIDPath);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CDataObj* CDataSet::FindDataObjByID_Has2(const CString &strIDPath)
{
	CDataObj *pDataObj = NULL;
	POS pos = GetHeadPosition();
	CDataObj *pFind = NULL;
	long nLen1, nLen2;
	nLen2 = strIDPath.GetLength();

	while (pos != NULL)
	{
		pDataObj = (CDataObj*)GetNext(pos);
		nLen1 = pDataObj->m_strID.GetLength();

		if (nLen2 == nLen1)
		{
			if(pDataObj->m_strID == strIDPath)
			{
				pFind = pDataObj;
				break;
			}

			continue;
		}

		if (nLen2 > nLen1)
		{
			if (strIDPath.GetAt(nLen1) == '$')
			{
				if(strIDPath.Left(nLen1) == pDataObj->m_strID)
				{
					pFind = pDataObj;
					break;
				}
			}
		}
		else
		{
			if (pDataObj->m_strID.GetAt(nLen2) == '$')
			{
				if(pDataObj->m_strID.Left(nLen2) == strIDPath)
				{
					pFind = pDataObj;
					break;
				}
			}
		}
	}

	return pFind;
}


void CDataSet::ResetDvmValue()
{
	POS pos = GetHeadPosition();
	CDataObj *p = NULL;

	while (pos != NULL)
	{
		p = (CDataObj *)GetNext(pos);
		p->ResetDvmValue();
	}
}


#ifdef GUIDEBOOK_DEV_MODE

long CDataSet::ExpandDsAin(CAinExpandMngr *pAinExpandMngr)
{
	m_nExpandCount = 0;
	m_pAinExpandMngr = pAinExpandMngr;

	CExBaseList oList;
	CDataObj *pDataObj = NULL;
	POS pos = GetHeadPosition();
	long nCount = 0;

	while (pos != NULL)
	{
		pDataObj = (CDataObj*)GetNext(pos);
		nCount += ExpandDsAin(pAinExpandMngr, pDataObj, oList);
	}

	AppendEx(oList, TRUE);
	oList.RemoveAll();

	return nCount;
}

long CDataSet::ExpandDsAin(CAinExpandMngr *pAinExpandMngr, CDataObj *pData, CExBaseList &oList)
{
	CString strLeft = pData->m_strName.Left(4);

	if (GetCount() == 0)
	{
		if (strLeft == g_strAinExand_Abs || strLeft == g_strAinExand_Rel || strLeft == g_strAinExand_Rst)
		{
			return 0;
		}

		m_nExpandCount += ExpandDsAin(pData, g_strAinExand_Abs, oList);
		m_nExpandCount += ExpandDsAin(pData, g_strAinExand_Rel, oList);
		m_nExpandCount += ExpandDsAin(pData, g_strAinExand_Rst, oList);

		return m_nExpandCount;
	}
	
	POS pos = pData->GetHeadPosition();
	CDataObjValue *pValue = NULL;
	CAinExpand *pAinExpand = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)pData->GetNext(pos);
		ExpandDsAin((CExBaseList*)pData, pValue);
	}

	return m_nExpandCount;
}

long CDataSet::ExpandDsAin(CDataObj *pData, const CString &strExpand, CExBaseList &oList)
{
	CString strID = strExpand + pData->m_strID;

	if (FindByID(strID) != NULL)
	{
		return 0;
	}


	CDataObj *pNew = (CDataObj*)pData->Clone();
	pNew->m_strID = strExpand + pData->m_strID;
	pNew->m_strName = strExpand + pData->m_strName;
	oList.AddTail(pNew);

	return 1;
}

long CDataSet::ExpandDsAin(CDataObj *pData, CDataObjValue *pValue, const CString &strExpand)
{
	CString strLeft = pValue->m_strID.Left(4);

	if (strLeft == g_strAinExand_Abs || strLeft == g_strAinExand_Rel || strLeft == g_strAinExand_Rst)
	{
		return 0;
	}

	CString strID = strExpand + pValue->m_strID;

	if (pData->FindByID(strID) != NULL)
	{
		return 0;
	}


	CDataObjValue *pNew = (CDataObjValue*)pValue->Clone();
	pNew->m_strID = strExpand + pValue->m_strID;

	if (pValue->m_strName.GetLength() == 0)
	{
		pNew->m_strName = pNew->m_strID;
	}
	else
	{
		pNew->m_strName = strExpand + pValue->m_strName;
	}

	pData->AddHead(pNew);
	pNew->SetParent(pData);

	return 1;
}

long CDataSet::ExpandDsAin(CExBaseList *pParent, CDataObjValue *pValue)
{
	CString strLeft = pValue->m_strID.Left(4);

	if (strLeft == g_strAinExand_Abs || strLeft == g_strAinExand_Rel || strLeft == g_strAinExand_Rst)
	{
		return 0;
	}

	CAinExpand *pAinExpand = NULL;

	if (pValue->GetCount() == 0)
	{
		pAinExpand = CanExpand(m_pAinExpandMngr, pValue);

		if (pAinExpand != NULL)
		{
			if (pAinExpand->m_nAbs == 1)
			{
				m_nExpandCount += ExpandDsAin(pParent, pValue, g_strAinExand_Abs);
			}

			if (pAinExpand->m_nReal == 1)
			{
				m_nExpandCount += ExpandDsAin(pParent, pValue, g_strAinExand_Rel);
			}

			if (pAinExpand->m_nRslt == 1)
			{
				m_nExpandCount += ExpandDsAin(pParent, pValue, g_strAinExand_Rst);
			}
		}
	}
	else
	{
		POS pos = pValue->GetHeadPosition();
		CDataObjValue *p = NULL;

		while (pos != NULL)
		{
			p = (CDataObjValue *)pParent->GetNext(pos);
			ExpandDsAin((CExBaseList*)pValue, p);
		}
	}

	return 1;
}


long CDataSet::ExpandDsAin(CExBaseList *pParent, CDataObjValue *pValue, const CString &strExpand)
{
	CString strLeft = pValue->m_strID.Left(4);

	if (strLeft == g_strAinExand_Abs || strLeft == g_strAinExand_Rel || strLeft == g_strAinExand_Rst)
	{
		return 0;
	}

	CString strID = strExpand + pValue->m_strID;

	if (pParent->FindByID(strID) != NULL)
	{
		return 0;
	}


	CDataObjValue *pNew = (CDataObjValue*)pValue->Clone();
	pNew->m_strID = strExpand + pValue->m_strID;

	if (pValue->m_strName.GetLength() == 0)
	{
		pNew->m_strName = pNew->m_strID;
	}
	else
	{
		pNew->m_strName = strExpand + pValue->m_strName;
	}

	pParent->AddHead(pNew);
	pNew->SetParent(pParent);

	return 1;
}

CAinExpand* CDataSet::CanExpand(CAinExpandMngr *pAinExpandMngr, CDataObjValue *pValue)
{
	POS pos = pAinExpandMngr->GetHeadPosition();
	CAinExpand *pAinExpand = NULL;
	CAinExpand *pFind = NULL;

	while (pos != NULL)
	{
		pAinExpand = (CAinExpand *)pAinExpandMngr->GetNext(pos);

		if (pValue->m_strID.Find(pAinExpand->m_strID) > 0)
		{
			pFind = pAinExpand;
			break;
		}
	}

	return pFind;
}

#endif

//2021-10-14  lijunqing
CDvmDataset* CDataSet::GetWriteDvmDataset(CValues *pValues)
{
	CDvmDataset *pDvmDataset = new CDvmDataset();

	if (pValues == NULL)
	{
		GetWriteDvmDataset(pDvmDataset);
	}
	else
	{
		GetWriteDvmDataset(pDvmDataset, pValues);
	}

	return pDvmDataset;
}

void CDataSet::GetWriteDvmDataset(CDvmDataset *pDvmDataset)
{
	POS pos = NULL;
	CDataObj *pData = NULL;
	CDvmData *pNew = NULL;

	pos = GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CDataObj *)GetNext(pos);
		pNew = new CDvmData();
		pData->WriteToData(pNew);
		pDvmDataset->AddNewChild(pNew);
	}
}

void CDataSet::GetWriteDvmDataset(CDvmDataset *pDvmDataset, CValues *pValues)
{
	POS pos = pValues->GetHeadPosition();
	CValue *pValue = NULL;
	CDataObj *pData = NULL;
	CDvmData *pNew = NULL;
	CExBaseObject *pDevice = (CExBaseObject*)GetAncestor(GBCLASSID_DEVICE);

	while (pos != NULL)
	{
		pValue = (CValue *)pValues->GetNext(pos);
		pData = (CDataObj*)FindByID(pValue->m_strID);

		if (pData == NULL)
		{
			continue;
		}

		if (pData != NULL)
		{
			pNew = new CDvmData();
			pData->WriteToData(pNew);

// 			if (bIsEmptyDataset)
// 			{
// 				pNew->m_strValue = pValue->m_strValue;
// 			}
// 			else
			{
				pNew->m_strValue = Gb_CalValue(pDevice, pValue);
			}

			pData->m_strValue = pNew->m_strValue; // 保存计算的数据
			pDvmDataset->AddTail(pNew);
		}
	}
}


//shaolei 2022-12-06   CDataSet对象转换成CDvmDataset对象
void CDataSet::Data_Gb_to_Dvm(CDvmDataset *pDestDvm)
{
	CDataObj *pDataObj = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pDvmData = NULL;

	pDestDvm->m_strID = m_strID;
	pDestDvm->m_strName = m_strName;
	pDestDvm->m_strDataType = m_strType;

	while (pos != NULL)
	{
		pDataObj = (CDataObj*)GetNext(pos);
		pDvmData = new CDvmData();
		pDestDvm->AddNewChild(pDvmData);
		pDataObj->Data_Gb_to_Dvm(pDvmData);
	}
}

//////////////////////////////////////////////////////////////////////////
//lijunqing 2020-09-05
void Gb_Append_Datas(CExBaseList *pDvmList, CExBaseList *pSrcDataObjList)
{
	POS pos = pSrcDataObjList->GetHeadPosition();
	CDataObj *pDataObj = NULL;
	CDvmData *pDvmData = NULL;

	while (pos != NULL)
	{
		pDataObj = (CDataObj *)pSrcDataObjList->GetNext(pos);
		pDvmData = new CDvmData();
		pDataObj->WriteToData(pDvmData);
		pDataObj->AddToDvm(pDvmData);
		pDvmList->AddNewChild(pDvmData);
	}
}


void Gb_InitValueByDvmDatas(CExBaseList *pSrcDvmDatas, CExBaseList *pDestList)
{
    CDataObj *pDataObj = NULL;
    POS pos = pSrcDvmDatas->GetHeadPosition();
    CDvmData *pDvmData = NULL;

    while (pos != NULL)
    {
        pDvmData = (CDvmData*)pSrcDvmDatas->GetNext(pos);
        pDataObj = (CDataObj*)pDestList->FindByID(pDvmData->m_strID);

        if (pDataObj != NULL)
        {
            pDataObj->m_strValue = pDvmData->m_strValue;
        }
    }
}

