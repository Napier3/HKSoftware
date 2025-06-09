#include "StdAfx.h"
#include "DataObj.h"
//#include "Set.h"
#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDataObjValue::CDataObjValue(void)
{
	m_strName = g_sLangTxt_Data/*_T("数据")*/;
	m_strDataTypeID = _T("float");
	m_strID = _T("Value");
}

CDataObjValue::~CDataObjValue(void)
{
}


//2021-10-13 lijunqing
CString CDataObjValue::GetIDPath_Root_Dataset(const CString &strPathSp)
{
	CDataObj *pData = (CDataObj*)GetAncestor(GBCLASSID_DATAOBJ);
	CString strID = pData->GetIDPath_Root_Dataset();

	CExBaseList oList;
	GetAllAncestorEqClassID(&oList, GBCLASSID_DATAOBJ_VALUE);
	POS pos = oList.GetHeadPosition();

	if (pos != NULL)
	{
		CExBaseObject *p = NULL;
		oList.GetNext(pos);

		while (pos != NULL)
		{
			p = oList.GetNext(pos);
			strID += p->m_strID;
			strID += strPathSp;
		}
	}
	else
	{
		strID += strPathSp;
	}

	strID += m_strID;
	oList.RemoveAll();

	return strID;
}

long CDataObjValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataTypeID);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CDataObjValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataTypeID);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);

	
	return 0;
}

long CDataObjValue::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataTypeID);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataTypeID);
		BinarySerializeRead(oBinaryBuffer, m_strValue);

	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataTypeID);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	
	return 0;
}

CBaseObject* CDataObjValue::Clone()
{
	CDataObjValue* pDataObj = new CDataObjValue();
	Copy(pDataObj);

	return pDataObj;
}


BOOL CDataObjValue::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CDataObjValue* pSet = (CDataObjValue*)pDesObj;
	pSet->m_strValue = m_strValue;
	pSet->m_strDataTypeID = m_strDataTypeID;

	CExBaseObject::CopyOwn(pSet);

	return TRUE;
}


CExBaseObject* CDataObjValue::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strValueKey)
	{
		pNew = new CDataObjValue();
	}

	return pNew;
}

CExBaseObject* CDataObjValue::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBCLASSID_DATAOBJ_VALUE)
	{
		pNew = new CDataObjValue();
	}

	return pNew;
}

void  CDataObjValue::GetIDForPath(CString &strID, const CString &strPathSp)
{
	strID = GetIDForPath(strPathSp);
}

CString  CDataObjValue::GetIDForPath(const CString &strPathSp)
{
	//20200202  shaolei  修改相对路径
	//CExBaseObject *pDataset = (CExBaseObject*)GetParent();
	//CString strID;

	//if (pDataset->GetClassID() == GBCLASSID_DEVICE_SYSPARAS)
	//{
	//	strID = m_strID;
	//}
	//else
	//{
	//	CExBaseObject *pCpu = (CExBaseObject*)pDataset->GetParent();
	//	strID.Format(_T("%s%s%s%s%s"), pCpu->m_strID, strPathSp, pDataset->m_strID, strPathSp, m_strID);
	//}

	//ldevice-->dataset-->data-->value(value可以嵌套)
	//CExBaseObject *pDataObj = (CExBaseObject*)GetParent();
	CExBaseObject *pDataset = (CExBaseObject*)GetAncestor(GBCLASSID_DATASET);
	CString strID;

	if (pDataset == NULL)
	{
		strID = m_strID;
	}
	else
	{
		CExBaseObject *pCpu = (CExBaseObject*)pDataset->GetParent();
        strID.Format(_T("%s%s%s%s%s"), pCpu->m_strID.GetString(), strPathSp.GetString(), pDataset->m_strID.GetString(), strPathSp.GetString(), m_strID.GetString());
	}
	return strID;
}

void CDataObjValue::InitValueByData(CShortData *pData)
{
	//m_strName = pData->m_strName;
	//m_strID = pData->m_strID;
	m_strValue = pData->m_strValue;
	//m_strUnit = pData->m_strUnit;
	//m_strDataTypeID = pData->m_strDataTypeID;
}

void CDataObjValue::WriteToData(CValue *pData)
{
	pData->m_strName = m_strName;
	pData->m_strID = m_strID;
	pData->m_strValue = m_strValue;
}

void CDataObjValue::AddToDvm(CDvmValue *pData)
{
	CDataObjValue *pValue = NULL;
	POS pos = GetHeadPosition();

	WriteToData(pData);

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)GetNext(pos);
		pValue->AddToDvm(pData);
	}
}

void CDataObjValue::InitValueByData(CDvmValue *pData)
{
	//m_strName = pData->m_strName;
	//m_strID = pData->m_strID;
	m_strValue = pData->m_strValue;
	//m_strUnit = pData->m_strUnit;
	//m_strDataTypeID = pData->m_strDataTypeID;

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

void CDataObjValue::WriteToData(CDvmValue *pData)
{
	pData->m_strName = m_strName;
	pData->m_strID = m_strID;
	pData->m_strValue = m_strValue;
	pData->m_strDataType = m_strDataTypeID;
}

long CDataObjValue::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strValue);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);

	return 0;
}

// 
// // void CDataObjValue::InitAfterRead()
// // {
// // //	m_dMinVal = CString_To_double(m_strMinVal);
// // //	m_dMaxVal = CString_To_double(m_strMaxVal);
// // }
// 
// BOOL DS_InStringDataPath(const CString &strText)
// {
// 	char *pText = NULL;
// 	long nLen = CString_to_char(strText, &pText);
// 	char *pEnd = pText + nLen;
// 	char *p = pText;
// 	BOOL bTrue = TRUE;
// 	BOOL bHasPathKey = FALSE;
// 
// 	while (p <pEnd)
// 	{
// 		if ((('0'<= *p) && (*p <='9'))
// 			|| (('a' <= *p) && (*p <= 'z')) 
// 			|| (('A' <= *p) && (*p <= 'Z'))
// 			|| (*p == '_'))
// 		{
// 
// 		}
// 		else
// 		{
// 			if (*p == '$') 
// 			{
// 				bHasPathKey = TRUE;
// 			}
// 			else
// 			{
// 				bTrue = FALSE;
// 				break;
// 			}
// 		}
// 
// 		p++;
// 	}
// 
// 	delete pText;
// 
// 	if (!bTrue)
// 	{
// 		return bTrue;
// 	}
// 	else
// 	{
// 		return bHasPathKey;
// 	}
// }
// 
// 

void CDataObjValue::AddToValues(CValues *pValues)//2021-10-18  lijunqing
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


void CDataObjValue::InitByValues(CValues *pValues, BOOL bUseReserved) //2021-10-18  lijunqing
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
void CDataObjValue::UpdateDataObjValue(CDataObjValue *pSrcParentValue, BOOL bNewNotExist)
{
	POS pos = pSrcParentValue->GetHeadPosition();
	CDataObjValue *pSrcDataObjValue = NULL;
	CDataObjValue *pDstDataObjValue = NULL;
	CString strSrcID;

	while (pos != NULL)
	{
		pSrcDataObjValue = (CDataObjValue *)pSrcParentValue->GetNext(pos);
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

//shaolei 2022-12-06   CDataObjValue对象转换成CDvmValue对象
void CDataObjValue::Data_Gb_to_Dvm(CDvmValue *pDestDvm)
{
	CDataObjValue *pDataObjValue = NULL;
	POS pos = GetHeadPosition();
	CDvmValue *pDvmValue = NULL;

	pDestDvm->m_strName = m_strName;
	pDestDvm->m_strID = m_strID;
	pDestDvm->m_strDataType = m_strDataTypeID;
	pDestDvm->m_strValue = m_strValue;

	while (pos != NULL)
	{
		pDataObjValue = (CDataObjValue*)GetNext(pos);
		pDvmValue = new CDvmValue();
		pDestDvm->AddNewChild(pDvmValue);
		pDataObjValue->Data_Gb_to_Dvm(pDvmValue);
	}
}