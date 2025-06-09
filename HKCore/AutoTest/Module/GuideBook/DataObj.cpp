#include "StdAfx.h"
#include "DataObj.h"
#include "GuideBook.h"
#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDataGroup *g_pGlobalDatas_Gb_CalParaExp = NULL;

CDvmValueKeyMngr g_oDvmValueKeyMngr;

CDataObj::CDataObj(void)
{
	m_strName =g_sLangTxt_DataSets/* _T("数据集")*/;
	m_nDataIndex = 0;
	m_dMinVal = 0;
	m_dMaxVal = 0;
	m_dStepVal = 0.001;
}

CDataObj::~CDataObj(void)
{
}

long CDataObj::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strDefaultValueKey, oNode, m_strDefaultValue);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strMinValKey,oNode,m_dMinVal);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strMaxValKey,oNode,m_dMaxVal);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strMinValKey,oNode,m_strMinVal);
// 	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strMaxValKey,oNode,m_strMaxVal);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strDataIndexKey,oNode,m_nDataIndex);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strStepKey,oNode,m_dStepVal);

	return 0;
}

long CDataObj::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strDefaultValueKey, oElement, m_strDefaultValue);

	xml_SetAttributeValue(pXmlKeys->m_strMinValKey, oElement, m_dMinVal);
	xml_SetAttributeValue(pXmlKeys->m_strMaxValKey, oElement, m_dMaxVal);
// 	xml_SetAttributeValue(pXmlKeys->m_strMinValKey, oElement, m_strMinVal);
// 	xml_SetAttributeValue(pXmlKeys->m_strMaxValKey, oElement, m_strMaxVal);
	xml_SetAttributeValue(pXmlKeys->m_strDataIndexKey, oElement, m_nDataIndex);
	xml_SetAttributeValue(pXmlKeys->m_strStepKey, oElement, m_dStepVal);
	
	return 0;
}


long CDataObj::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
{
	//if (oBinaryBuffer.m_dwVersionFind != 0)
	{
		CExBaseList::SerializeChildren(oBinaryBuffer);
	}
	//else
	{
	}

	return 0;
}

long CDataObj::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strDefaultValue);
		BinarySerializeCalLen(oBinaryBuffer,m_dMinVal);
		BinarySerializeCalLen(oBinaryBuffer,m_dMaxVal);
// 		BinarySerializeCalLen(oBinaryBuffer,m_strMinVal);
// 		BinarySerializeCalLen(oBinaryBuffer,m_strMaxVal);
		BinarySerializeCalLen(oBinaryBuffer,m_nDataIndex);
		BinarySerializeCalLen(oBinaryBuffer,m_dStepVal);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strDefaultValue);

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_11)
		{
			BinarySerializeRead(oBinaryBuffer,m_dMinVal);
			BinarySerializeRead(oBinaryBuffer,m_dMaxVal);
		}
		else
		{
			CString strVal;
			BinarySerializeRead(oBinaryBuffer,strVal);
			BinarySerializeRead(oBinaryBuffer,strVal);
		}

		BinarySerializeRead(oBinaryBuffer,m_nDataIndex);

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_21)
		{
			BinarySerializeRead(oBinaryBuffer,m_dStepVal);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strDefaultValue);
// 		BinarySerializeWrite(oBinaryBuffer,m_strMinVal);
// 		BinarySerializeWrite(oBinaryBuffer,m_strMaxVal);
		BinarySerializeWrite(oBinaryBuffer,m_dMinVal);
		BinarySerializeWrite(oBinaryBuffer,m_dMaxVal);
		BinarySerializeWrite(oBinaryBuffer,m_nDataIndex);
		BinarySerializeWrite(oBinaryBuffer,m_dStepVal);
	}
	
	return 0;
}

CBaseObject* CDataObj::Clone()
{
	CDataObj* pDataObj = new CDataObj();
	Copy(pDataObj);

	return pDataObj;
}


CBaseObject* CDataObj::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CDataObj *pNew = new CDataObj();

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

BOOL CDataObj::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CDataObj* pSet = (CDataObj*)pDesObj;
	pSet->m_strValue = m_strValue;
	pSet->m_strDefaultValue = m_strDefaultValue;
	pSet->m_strUnit = m_strUnit;
	pSet->m_strDataType = m_strDataType;
// 	pSet->m_strMinVal = m_strMinVal;
// 	pSet->m_strMaxVal = m_strMaxVal;
	pSet->m_dMinVal = m_dMinVal;
	pSet->m_dMaxVal = m_dMaxVal;
	pSet->m_dStepVal = m_dStepVal;
	pSet->m_nDataIndex = m_nDataIndex;

	CExBaseObject::CopyOwn(pSet);

	return TRUE;
}


CExBaseObject* CDataObj::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strValueKey)
	{
		pNew = new CDataObjValue();
	}

	return pNew;
}

CExBaseObject* CDataObj::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBCLASSID_DATAOBJ_VALUE)
	{
		pNew = new CDataObjValue();
	}

	return pNew;
}


void  CDataObj::GetIDForPath(CString &strID, const CString &strPathSp)
{
	strID = GetIDForPath(strPathSp);
}

CString  CDataObj::GetIDForPath(const CString &strPathSp)
{
	CExBaseObject *pDataset = (CExBaseObject*)GetParent();
	CString strID;

	if (pDataset->GetClassID() == GBCLASSID_DEVICE_SYSPARAS)
	{
		strID = m_strID;
	}
	else
	{
		CExBaseObject *pCpu = (CExBaseObject*)pDataset->GetParent();
		long nDvmIndex = Gb_GetDvmIndexByObj(pCpu);

		if (nDvmIndex <= 0)
		{
            strID.Format(_T("%s%s%s%s%s"), pCpu->m_strID.GetString(), strPathSp.GetString(), pDataset->m_strID.GetString(), strPathSp.GetString(), m_strID.GetString());
		}
		else
		{
            strID.Format(_T("%d%s%s%s%s%s%s"), nDvmIndex, strPathSp.GetString(), pCpu->m_strID.GetString(), strPathSp.GetString(), pDataset->m_strID.GetString(), strPathSp.GetString(), m_strID.GetString());
		}
	}

	return strID;
}

//2021-10-13 lijunqing
CString CDataObj::GetIDPath_Root_Dataset(const CString &strPathSp)
{
	CExBaseObject *pDataset = (CExBaseObject*)GetParent();
	CString strID;
	UINT nClassID = pDataset->GetClassID();

	if (nClassID == GBCLASSID_DEVICE_SYSPARAS || nClassID == GBCLASSID_DATASET)
	{
		strID = m_strID;
	}
	else
	{
		CExBaseList oList;
		GetAllAncestorEqClassID(&oList, GBCLASSID_DATASETGROUP);
		POS pos = oList.GetHeadPosition();
		CExBaseObject *p = NULL;
		oList.GetNext(pos);

		while (pos != NULL)
		{
			p = oList.GetNext(pos);
			strID += p->m_strID;
			strID += strPathSp;
		}

		strID += m_strID;
		oList.RemoveAll();
	}

	return strID;
}

void CDataObj::SetValue(const CString &strValue)
{
	m_strValue = strValue;

	POS pos = GetHeadPosition();
	CDataObjValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)GetNext(pos);

		if (g_oDvmValueKeyMngr.IsValueID(pValue->m_strID))
		{
			pValue->m_strValue = strValue;
		}
	}
}

void CDataObj::InitValueByData(CShortData *pData)
{
	//m_strName = pData->m_strName;
	//m_strID = pData->m_strID;
	m_strValue = pData->m_strValue;
	//m_strUnit = pData->m_strUnit;
	//m_strDataTypeID = pData->m_strDataTypeID;
}

void CDataObj::InitValueByData(CDataObj *pSrcData)
{
	m_strValue = pSrcData->m_strValue;
	
	POS pos = pSrcData->GetHeadPosition();
	CDataObjValue *pValue = NULL;
	CDataObjValue *pFind = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)pSrcData->GetNext(pos);
		pFind = (CDataObjValue *)FindByID(pValue->m_strID);

		if (pFind != NULL)
		{
			pFind->m_strValue = pValue->m_strValue;
		}
	}
}

void CDataObj::WriteToData(CShortData *pData)
{
	pData->m_strName = m_strName;
	pData->m_strID = m_strID;
	pData->m_strValue = m_strValue;
	pData->m_strUnit = m_strUnit;
	pData->m_strDataTypeID = m_strDataType;
}

void CDataObj::AddToDvm(CDvmData *pData)
{
	pData->m_strName = m_strName;
	pData->m_strID = m_strID;
	pData->m_strDataType = m_strDataType;
	pData->m_strUnit = m_strUnit;

	POS pos = GetHeadPosition();
	CDataObjValue *pValue = NULL;
	CDvmValue *pNew = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)GetNext(pos);
		pNew = new CDvmValue();
		pData->AddNewChild(pNew);
		pValue->AddToDvm(pNew);
	}
}

void CDataObj::InitValueByData(CDvmData *pData, BOOL bSetMinMax)
{
	//m_strName = pData->m_strName;
	//m_strID = pData->m_strID;
	m_strValue = pData->m_strValue;
	//m_strUnit = pData->m_strUnit;
	//m_strDataTypeID = pData->m_strDataTypeID;

	if (bSetMinMax)
	{
#ifdef _UNICODE
		m_dMinVal = _wtof(pData->m_strMin) ;
		m_dMaxVal = _wtof(pData->m_strMax) ;
#else
//		m_dMinVal = atof(pData->m_strMin) ;
//		m_dMaxVal = atof(pData->m_strMax) ;
		m_dMinVal = CString_To_double(pData->m_strMin) ;
		m_dMaxVal = CString_To_double(pData->m_strMax) ;
#endif
	}

	if (GetCount() == 0)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CDataObjValue *pDest = NULL;
	CDvmValue *pSrc = NULL;

	while (pos != NULL)
	{
		pDest = (CDataObjValue *)GetNext(pos);
		pSrc = (CDvmValue *)pData->FindByID(pDest->m_strID);

		if (pSrc == NULL)
		{
			pSrc = pData->FindByID_Has(pDest->m_strID);
		}

		if (pSrc == NULL)
		{
			pSrc = (CDvmValue *)pData->FindByName(pDest->m_strName);
		}

		if (pSrc != NULL)
		{
			pDest->InitValueByData(pSrc);
		}
	}
}


CDataObjValue* CDataObj::FindValue(const CString &strIDHas)
{
	POS pos = GetHeadPosition();
	CDataObjValue *p = NULL;
	CDataObjValue *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDataObjValue *)GetNext(pos);

		if (p->m_strID.Find(strIDHas) >= 0)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}


void CDataObj::WriteToData(CDvmData *pData)
{
	pData->m_strName = m_strName;
	pData->m_strID = m_strID;
	pData->m_strValue = m_strValue;
	pData->m_strUnit = m_strUnit;
	pData->m_strDataType = m_strDataType;
}

long CDataObj::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strValue);
	pListCtrl->SetItemText(lItemIndex, 4, m_strUnit);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}


void CDataObj::InitAfterRead()
{
	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}
}

CDataTypes* CDataObj::GetDataTypes()
{
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);
	//2017-10-29 m_strTestMacroFile==>m_strTestMacroFileID
	CTestMacros* pMacros = pGuideBook->m_pTestMacros; //TM_GetTestMacros(pGuideBook->m_strTestMacroFileID);  //lijq 20200227

	if (pMacros != NULL)
	{
		return pMacros->GetDataTypes();
	}
	else
	{
		return NULL;
	}
}


CDataType* CDataObj::GetDataType()
{
	CDataTypes *pDataTypes = GetDataTypes();

	if (pDataTypes == NULL)
	{
		return NULL;
	}

	return (CDataType*)pDataTypes->FindByID(m_strDataType);
}


BOOL CDataObj::GetValueByID(const CString &strValueID, CString &strValue)
{
	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strNameKey)
	{
		strValue = m_strName;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIDKey)
	{
		strValue = m_strID;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::ValueKey())
	{
		strValue = m_strValue;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::DataTypeKey())
	{
		strValue = m_strDataType;
		return TRUE;
	}

	if (strValueID == _T("datatype"))
	{
		strValue = m_strDataType;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::StepKey())
	{
		strValue.Format(_T("%f"), m_dStepVal);
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::MinKey())
	{
		strValue.Format(_T("%f"), m_dMinVal);
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::MaxKey())
	{
		strValue.Format(_T("%f"), m_dMaxVal);
		return TRUE;
	}

	CValue *pValue = (CValue*)FindByID(strValueID);

	if (pValue != NULL)
	{
		strValue = pValue->m_strValue;
		return TRUE;
	}

	return FALSE;
}

void CDataObj::ResetDvmValue()
{
	SetValue(m_strDefaultValue);
}

//20200203   shaolei   相对路径查找数据，重载此函数
long CDataObj::SelectDatas(const CString &strIDPath, CExBaseList &oListDest, const CString &strSeperator)
{
	CExBaseObject *pObj = NULL;

	long nOldCount = oListDest.GetCount();
	CExBaseList::SelectDatas(strIDPath, oListDest, strSeperator);

	long nNewCount = oListDest.GetCount();

	if (nOldCount < nNewCount)
		return nNewCount;
	
	pObj = FindDataObjValueByID_Has(strIDPath);

	if (pObj != NULL)
	{
		oListDest.AddTail(pObj);
	}

	return oListDest.GetCount();
}

CDataObjValue* CDataObj::FindDataObjValueByID_Has(const CString &strIDPath)
{
	CDataObjValue *pDataObjVal = NULL;
	POS pos = GetHeadPosition();
	CDataObjValue *pFind = NULL;
	long nLen1, nLen2;

	while (pos != NULL)
	{
		pDataObjVal = (CDataObjValue *)GetNext(pos);
		nLen1 = pDataObjVal->m_strID.GetLength();
		nLen2 = strIDPath.GetLength();

		if (nLen2 == nLen1)
		{
			if(pDataObjVal->m_strID == strIDPath)
			{
				pFind = pDataObjVal;
				break;
			}
		}

		else if (nLen2 > nLen1)
		{
			if (strIDPath.GetAt(nLen2 - nLen1 - 1) == '$')
			{	
				if(strIDPath.Right(nLen1) == pDataObjVal->m_strID)
				{
					pFind = pDataObjVal;
					break;
				}
			}
		}
		else if (nLen2 < nLen1)
		{
			if (pDataObjVal->m_strID.GetAt(nLen1 - nLen2 - 1) == '$')
			{
				if(pDataObjVal->m_strID.Right(nLen2) == strIDPath)
				{
					pFind = pDataObjVal;
					break;
				}
			}
		}
	}

	return pFind;
}

CExBaseObject* CDataObj::FindValueObject(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);

		if (g_oDvmValueKeyMngr.IsValueID(p->m_strID))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL CDataObj::CmpDataType(CDvmData *pDataSrc)
{
	if (GetCount() == 0 && pDataSrc->GetCount() == 0)
	{
		return m_strDataType == pDataSrc->m_strDataType;
	}

	if (GetCount() > 0 && pDataSrc->GetCount() > 0)
	{
		CDvmValue *pFind = (CDvmValue*)FindValueObject(pDataSrc);
		CDataObjValue *pFind2 = (CDataObjValue*)FindValueObject(this);

		if (pFind == NULL || pFind2 == NULL)
		{
			return FALSE;
		}
		else
		{
			return pFind2->m_strDataTypeID == pFind->m_strDataType;
		}
	}
	
	if (GetCount() > 0)
	{
		CDataObjValue *pFind2 = (CDataObjValue*)FindValueObject(this);

		if (pFind2 == NULL)
		{
			return FALSE;
		}
		else
		{
			return pFind2->m_strDataTypeID == m_strDataType;
		}
	}

	CDvmValue *pFind = (CDvmValue*)FindValueObject(pDataSrc);

	if (pFind == NULL)
	{
		return FALSE;
	}
	else
	{
		return m_strDataType == pFind->m_strDataType;
	}
}


BOOL CDataObj::CmpDataType(const CString &strDataType)
{
	if (GetCount() == 0 )
	{
		return m_strDataType == strDataType;
	}

	POS pos = GetHeadPosition();
	CDvmValue *p = NULL;

	while(pos != NULL)
	{
		p = (CDvmValue *)GetNext(pos);

		if (p->m_strDataType == strDataType)
		{
			return TRUE;
		}
	}

	return FALSE;
}

//2021-3-28  lijunqing   属性是否全部匹配
BOOL CDataObj::IsAttrsMatch(CValues *pAttrs)
{
	if (pAttrs == NULL)
	{
		return TRUE;
	}

	if (pAttrs->GetCount() == 0)
	{
		return TRUE;
	}

	POS pos = pAttrs->GetHeadPosition();
	CValue *pAttr = NULL;
	CString strValue;

	while (pos != NULL)
	{
		pAttr = (CValue *)pAttrs->GetNext(pos);

		if (!GetValueByID(pAttr->m_strID, strValue))
		{
			return FALSE;
		}

		if (strValue != pAttr->m_strValue)
		{
			return FALSE;
		}
	}

	return TRUE;
}

CString CDataObj::GetDataObjPath()
{
	CExBaseObject *pParent = (CExBaseObject *)GetParent();
	UINT nClassID = pParent->GetClassID();
	CString strPath;
	strPath = pParent->m_strID + _T("$") + m_strID;

	pParent = (CExBaseObject *)pParent->GetParent();

	while (pParent != NULL)
	{
		if (nClassID != pParent->GetClassID())
		{
			break;
		}

		strPath = pParent->m_strID + _T("$") + strPath;
		pParent = (CExBaseObject *)pParent->GetParent();
	}

	return strPath;
}

void CDataObj::AddToValues(CValues *pValues)//2021-10-18  lijunqing
{
	CString strID = GetIDPath_Root_Dataset();

	if (pValues->FindByID(strID) != NULL)
	{
		return;
	}

	pValues->AddValue(strID, m_strValue);

	POS pos = GetHeadPosition();
	CDataObjValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDataObjValue *)GetNext(pos);
		p->AddToValues(pValues);
	}
}

void CDataObj::InitByValues(CValues *pValues, BOOL bUseReserved) //2021-10-18  lijunqing
{
	CString strID = GetIDPath_Root_Dataset();
	CValue *pValue = (CValue*)pValues->FindByID(strID);

	if (pValue == NULL)
	{
		return;
	}

	m_strValue = pValue->m_strValue;

	if (bUseReserved)
	{
		m_dwReserved = (DWORD)pValue;
		pValue->m_dwReserved = (DWORD)this;
	}

	POS pos = GetHeadPosition();
	CDataObjValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDataObjValue *)GetNext(pos);
		p->InitByValues(pValues, bUseReserved);
	}
}

//模型更新  shaolei 20220716
void CDataObj::UpdateDataObjValue(CDataObj *pSrcDataObj, BOOL bNewNotExist)
{
	POS pos = pSrcDataObj->GetHeadPosition();
	CDataObjValue *pSrcDataObjValue = NULL;
	CDataObjValue *pDstDataObjValue = NULL;
	CString strSrcID;

	while (pos != NULL)
	{
		pSrcDataObjValue = (CDataObjValue *)pSrcDataObj->GetNext(pos);
		strSrcID = pSrcDataObjValue->m_strID;
		pDstDataObjValue = (CDataObjValue *)FindByID(strSrcID);

		if (pDstDataObjValue == NULL)
		{
			if (bNewNotExist)
			{
				pDstDataObjValue = (CDataObjValue *)pSrcDataObjValue->CloneEx(TRUE,TRUE);
				AddNewChild(pDstDataObjValue);
				continue;
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("设备数据模型更新，数据属性【%s】未找到"), strSrcID.GetString());
				continue;
			}
		}
		else
		{
			pDstDataObjValue->m_strValue = pSrcDataObjValue->m_strValue;
			pDstDataObjValue->UpdateDataObjValue(pSrcDataObjValue, bNewNotExist);
		}
	}
}

//shaolei 2022-12-06   CDataObj对象转换成CDvmData对象
void CDataObj::Data_Gb_to_Dvm(CDvmData *pDestDvm)
{
	CDataObjValue *pDataObjValue = NULL;
	POS pos = GetHeadPosition();
	CDvmValue *pDvmValue = NULL;

	pDestDvm->m_strName = m_strName;
	pDestDvm->m_strID = m_strID;
	pDestDvm->m_strDataType = m_strDataType;
	pDestDvm->m_strValue = m_strValue;
	pDestDvm->m_strUnit = m_strUnit;

	while (pos != NULL)
	{
		pDataObjValue = (CDataObjValue*)GetNext(pos);
		pDvmValue = new CDvmValue();
		pDestDvm->AddNewChild(pDvmValue);
		pDataObjValue->Data_Gb_to_Dvm(pDvmValue);
	}
}

BOOL DS_InStringDataPath(const CString &strText)
{
	char *pText = NULL;
	long nLen = CString_to_char(strText, &pText);
	char *pEnd = pText + nLen;
	char *p = pText;
	BOOL bTrue = TRUE;
	BOOL bHasPathKey = FALSE;

	while (p <pEnd)
	{
		if ((('0'<= *p) && (*p <='9'))
			|| (('a' <= *p) && (*p <= 'z')) 
			|| (('A' <= *p) && (*p <= 'Z'))
			|| (*p == '_'))
		{

		}
		else
		{
			if (*p == '$') 
			{
				bHasPathKey = TRUE;
			}
			else
			{
				bTrue = FALSE;
				break;
			}
		}

		p++;
	}

	delete pText;

	if (!bTrue)
	{
		return bTrue;
	}
	else
	{
		return bHasPathKey;
	}
}

//2021-10-14  lijunqing 从GbItemBase移到此处
inline BOOL Gb_CalParaExp_FindValue(CDevice *pDevice, CValues *pValues, const CString &strVarID, CString &strValue)
{
	if (pValues != NULL)
	{
		if (pValues->GetValue(strVarID, strValue))
		{
			return TRUE;
		}
	}

	if (g_pGlobalDatas_Gb_CalParaExp != NULL)
	{
		if (g_pGlobalDatas_Gb_CalParaExp->GetDataValue(strVarID, strValue))
		{
			return TRUE;
		}
	}

	if (pDevice == NULL)
	{
		return FALSE;
	}

	return pDevice->GetVariableValue(strVarID, strValue, TRUE);
}

//加一个extern CDataGroup *g_pGlobalDatas_Gb_CalParaExp;
BOOL Gb_CalParaExpression(const CString &strExpress, CExBaseList *pObjDevice, double &dValue, BOOL bLogError, CValues *pValues)
{
	CEpExpression oEpExp;

	if (strExpress.GetLength() == 0)
	{
		return FALSE;
	}

	if (oEpExp.ChangeEpExpression(strExpress) == -1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionError.GetString()/*_T("表达式【%s】 错误")*/, strExpress.GetString());
		return FALSE;
	}

	CDevice *pDevice = (CDevice*)pObjDevice;
	CString strValue;
	POS pos = oEpExp.GetHeadPosition();
	CEpExpVariable *pExpVar = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pExpVar = oEpExp.GetNext(pos);

		if (Gb_CalParaExp_FindValue(pDevice, pValues, pExpVar->m_strVarID, strValue))
		{
#ifdef _UNICODE
			pExpVar->m_dValue = _wtof(strValue);
#else
			pExpVar->m_dValue = atof(strValue.GetString());
#endif
		}
		else
		{
			bTrue = FALSE;

			if (bLogError)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionVariable.GetString()/*_T("表达式变量【%s】 错误")*/, pExpVar->m_strVarID.GetString());
			}
		}
	}

	oEpExp.Value(dValue);

	return bTrue;
}

BOOL Gb_CalParaExpressionEx(const CString &strExpress, CExBaseList *pObjDevice, double &dValue, BOOL bLogError, CString &strValue)
{
	CEpExpression oEpExp;

	if (oEpExp.ChangeEpExpression(strExpress) == -1)
	{
		strValue = strExpress;
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionError.GetString()/*_T("表达式【%s】 错误")*/, strExpress.GetString());
		return FALSE;
	}

	CDevice *pDevice = (CDevice*)pObjDevice;
	CString strTemp;
	POS pos = oEpExp.GetHeadPosition();
	CEpExpVariable *pExpVar = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pExpVar = oEpExp.GetNext(pos);

		if (pDevice->GetVariableValue(pExpVar->m_strVarID, strTemp))
		{
			if (IsStringNumber(strTemp))
			{
#ifdef _UNICODE
				pExpVar->m_dValue = _wtof(strTemp);
#else
				pExpVar->m_dValue = atof(strTemp.GetString());
#endif
			}
			else
			{
				//字符串类型，直接返回
				strValue = strTemp;
				bTrue = FALSE;
				break;
			}
		}
		else
		{
			if (bLogError)
			{
				strValue = strExpress;
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionVariable.GetString()/*_T("表达式变量【%s】 错误")*/, pExpVar->m_strVarID.GetString());
				bTrue = FALSE;
			}
		}
	}

	if (bTrue)
	{
		oEpExp.Value(dValue);
	}
	else
	{
		dValue = 0;
	}

	return bTrue;
}

CString Gb_CalValue(CExBaseObject *pDevice, CValue *pValue)
{
	if (pValue->m_strValue.GetAt(0) == '\"')
	{
		return pValue->m_strValue;
	}

	if (pValue->m_strValue.GetLength() == 0)
	{
		return pValue->m_strValue;
	}

	double dValue = 0;

	if (IsStringNumber(pValue->m_strValue))
	{
#ifdef _UNICODE
		dValue = _wtof(pValue->m_strValue);
#else
		//		dValue = atof(pValue->m_strValue);
		dValue = CString_To_double(pValue->m_strValue); //yyj 20200523
#endif
		//return pValue->m_strValue;
	}
	else
	{
		CString strValue;
		if (!Gb_CalParaExpressionEx(pValue->m_strValue, (CDevice*)pDevice, dValue, g_nLog_TestControl_Msg, strValue))
		{
			return strValue;
			//dValue = 0;
			//return pValue->m_strValue;
		}
	}

	return Gb_CalValue_MinMax((CDevice*)pDevice, pValue, dValue);
}

CString Gb_CalValue_MinMax(CExBaseObject *pDevice, CValue *pValue, double dValue)
{
	// 	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
	CDataObj *pData = ((CDevice*)pDevice)->FindDataObjByID(pValue->m_strID, -1);
	CString strValue;

	if (pData != NULL)
	{
		CGuideBook *pGuideBook = (CGuideBook*)pDevice->GetAncestor(GBCLASSID_GUIDEBOOK);

		//2019-10-30  定义修改定值的时候，是否判断最大最小值
		if (pGuideBook->m_bWSetsUseMinMax)
		{
			double d = pData->m_dMinVal - pData->m_dMaxVal;

			if (fabs(d) > 0.001)
			{
				if (dValue >= pData->m_dMaxVal)
				{
					dValue = pData->m_dMaxVal;
				}
				else if (dValue <= pData->m_dMinVal)
				{
					dValue = pData->m_dMinVal;
				}
			}
		}

		strValue.Format(_T("%f"), dValue);
		pData->m_strValue = strValue;
	}
	else
	{
		strValue.Format(_T("%f"), dValue);
	}

	return strValue;
}

