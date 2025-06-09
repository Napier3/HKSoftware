//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDataset.cpp  CDvmDataset


#include "stdafx.h"
#include "DvmDataset.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CDvmDataset::CDvmDataset()
{
    m_strName = /*g_sLangTxt_DataSets*/_T("Dataset");
	m_strID = _T("dataset");

	//初始化属性
	m_nIndex = 0;
	m_nWriteMode = 0;

#ifdef _DVMDATASET_USE_ADDR_
	m_nAddr = 0;
#endif

	//初始化成员变量
	m_pDvmBrcb = NULL;
}

CDvmDataset::~CDvmDataset()
{
	if (m_pDvmBrcb != NULL)
	{
		delete m_pDvmBrcb;
		m_pDvmBrcb = NULL;
	}
}

long CDvmDataset::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strWriteModeKey, oNode, m_nWriteMode);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
#ifdef _DVMDATASET_USE_ADDR_
	xml_GetAttibuteValue(pXmlKeys->m_strAddrKey, oNode, m_nAddr);
#endif

	return 0;
}

long CDvmDataset::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strWriteModeKey, oElement, m_nWriteMode);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
#ifdef _DVMDATASET_USE_ADDR_
	xml_SetAttributeValue(pXmlKeys->m_strAddrKey, oElement, m_nAddr);
#endif
	return 0;
}

long CDvmDataset::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_nWriteMode);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
#ifdef _DVMDATASET_USE_ADDR_
		BinarySerializeCalLen(oBinaryBuffer, m_nAddr);
#endif
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		if (oBinaryBuffer.m_dwVersionFind >= DATAMNGR_VERSION_1_6)
		{
			BinarySerializeRead(oBinaryBuffer, m_strDataType);
			BinarySerializeRead(oBinaryBuffer, m_nWriteMode);
			BinarySerializeRead(oBinaryBuffer, m_nIndex);
#ifdef _DVMDATASET_USE_ADDR_
			BinarySerializeRead(oBinaryBuffer, m_nAddr);
#endif
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_nWriteMode);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
#ifdef _DVMDATASET_USE_ADDR_
		BinarySerializeWrite(oBinaryBuffer, m_nAddr);
#endif
	}
	return 0;
}

BOOL CDvmDataset::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDvmDataset *p = (CDvmDataset*)pObj;

	return TRUE;
}

BOOL CDvmDataset::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDvmDataset *p = (CDvmDataset*)pDest;
	p->m_strDataType = m_strDataType;
	p->m_nWriteMode = m_nWriteMode;
	p->m_nIndex = m_nIndex;
#ifdef _DVMDATASET_USE_ADDR_
	p->m_nAddr = m_nAddr;
#endif

	return TRUE;
}

CBaseObject* CDvmDataset::Clone()
{
	CDvmDataset *p = new CDvmDataset();
	Copy(p);
	return p;
}

CBaseObject* CDvmDataset::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CDvmDataset *pNew = new CDvmDataset();
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

CExBaseObject* CDvmDataset::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmDataKey)
	{
		pNew = new CDvmData();
	}
	else if (strClassID == pXmlKeys->m_strCDvmBrcbKey)
	{
		m_pDvmBrcb = new CDvmBrcb();
		pNew = m_pDvmBrcb;
	}

	return pNew;
}

CExBaseObject* CDvmDataset::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		pNew = new CDvmData();
	}
	else if (nClassID == DVMCLASSID_CDVMBRCB)
	{
		m_pDvmBrcb = new CDvmBrcb();
		pNew = m_pDvmBrcb;
	}

	return pNew;
}

BOOL CDvmDataset::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		return TRUE;
	}

	return FALSE;
}

void CDvmDataset::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	POS posBrcb = NULL;

	while (pos != NULL)
	{
		posBrcb = pos;
		p = GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMBRCB)
		{
			m_pDvmBrcb = (CDvmBrcb *)p;
			break;
		}
	}

	if (m_pDvmBrcb != NULL)
	{
		RemoveAt(posBrcb);
	}
}

long CDvmDataset::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (m_pDvmBrcb != NULL)
	{
		m_pDvmBrcb->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

long CDvmDataset::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
{
	if (m_pDvmBrcb != NULL)
	{
		m_pDvmBrcb->Serialize(oBinaryBuffer);
	}

	return CExBaseList::SerializeChildren(oBinaryBuffer);
}

CDvmData* CDvmDataset::AddNewData(CDvmData *pSrc)
{
	CDvmData *pData = NULL;

	if (pSrc != NULL)
	{
		pData = (CDvmData *)pSrc->Clone();
	}
	else
	{
		pData = new CDvmData();
	}

	AddNewChild(pData);

	return pData;
}

CDvmData* CDvmDataset::FindByIndex(long nIndex)
{
	CDvmData *p = NULL;
	CDvmData *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmData *)GetNext(pos);

		if (p->m_nIndex == nIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDvmData *CDvmDataset::FindByDataType(const CString& strDataType)
{
	CDvmData *p = NULL;
	CDvmData *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmData *)GetNext(pos);

		if (p->m_strDataType == strDataType)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL CDvmDataset::UpdateDataValue(CDvmDataset *pSrcDataset, BOOL bIsNew)
{
	BOOL bRet = TRUE;
	POS pos = pSrcDataset->GetHeadPosition();
	CDvmData *pSrcData = NULL;
	CDvmData *pDstData = NULL;
	CString strSrcID;

	while (pos != NULL)
	{
		pSrcData = (CDvmData *)pSrcDataset->GetNext(pos);
		strSrcID = pSrcData->m_strID;
		pDstData = (CDvmData *)FindByID(strSrcID);
		
		if (pDstData == NULL)
		{
			if (bIsNew)
			{
				pDstData = (CDvmData *)pSrcData->CloneEx(TRUE,TRUE);
				AddNewChild(pDstData);
				continue;
			}
			else
			{
				bRet = FALSE;
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("数据集数据更新，数据【%s】未找到"), strSrcID.GetString());
				continue;
			}
		}
		else
		{
			pDstData->m_strValue = pSrcData->m_strValue;
			bRet = pDstData->UpdateChildValue(pSrcData, bIsNew);
			pDstData->m_nChange = 0;
		}
	}

	return bRet;
}

void CDvmDataset::InitValue(CDvmDataset *pSrcDataset, BOOL bNoChangeWhenSame)
{
	POS pos = pSrcDataset->GetHeadPosition();
	CDvmData *p = NULL;
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmData *)pSrcDataset->GetNext(pos);

		pFind = (CDvmData*)FindByID(p->m_strID);

		if (pFind == NULL)
		{
			pFind = (CDvmData*)FindByName(p->m_strName);
		}

		if (pFind != NULL)
		{
			if (bNoChangeWhenSame)
			{
				if (!dvm_IsValueEqual(pFind->m_strValue, p->m_strValue))
				{
#ifdef _DVM_VALUE_USE_CHAR_
					wcscpy(pFind->m_strValue, p->m_strValue);
#else
					pFind->m_strValue = p->m_strValue;
#endif
					pFind->m_nChange = 1;
				}
			}
			else
			{
#ifdef _DVM_VALUE_USE_CHAR_
				wcscpy(pFind->m_strValue, p->m_strValue);
#else
				pFind->m_strValue = p->m_strValue;
#endif
				pFind->m_nChange = 1;
			}
		}
	}
}


CDvmData* CDvmDataset::FindByID_Has(const CString &strIDPath)
{
	CDvmData *pDataObj = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;
	long nLen1, nLen2;

	while (pos != NULL)
	{
		pDataObj = (CDvmData*)GetNext(pos);
		nLen1 = pDataObj->m_strID.GetLength();
		nLen2 = strIDPath.GetLength();

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
			if (strIDPath.GetAt(nLen2 - nLen1 - 1) == '$')
			{	
				if(strIDPath.Right(nLen1) == pDataObj->m_strID)
				{
					pFind = pDataObj;
					break;
				}
			}
		}
		else
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
BOOL CDvmDataset::HasValueID(const CString &strValueID)
{
	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strNameKey)
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIDKey)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CDvmDataset::SetAttr(const CString &strAttrID, const CString &strValue)
{
	if (strAttrID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strNameKey)
	{
		m_strName = strValue;
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIDKey)
	{
		m_strID = strValue;
		return TRUE;
	}

	return FALSE;
}

CDvmData* CDvmDataset::AddNewData(const CString &strName, const CString &strID, const CString &strDataType, const CString &strValue
					 , const CString &strUnit, const CString &strMin, const CString &strMax, const CString &strStep)
{
	CDvmData *pNew = new CDvmData();

	pNew->m_strName = strName;
	pNew->m_strID = strID;
	pNew->m_strDataType = strDataType;
	pNew->m_strUnit = strUnit;
	pNew->m_strMin = strMin;
	pNew->m_strMax = strMax;
	pNew->m_strStep = strStep;
	
#ifdef _DVM_VALUE_USE_CHAR_
#ifdef UNICODE
	wcscpy(pNew->m_strValue, strValue);
#else
	BSTR bstr = strValue.AllocSysString();
	wcscpy(pNew->m_strValue, bstr);
	::SysFreeString(bstr);
#endif
#else
	pNew->m_strValue = strValue;
#endif

	AddNewChild(pNew);

	return pNew;
}
CDvmData* CDvmDataset::AddNewDataEx(const CString &strName, const CString &strID, const CString &strDataType, const CString &strValue
								  , const CString &strUnit, const CString &strMin, const CString &strMax, const CString &strStep)
{
	CDvmData *pNew = (CDvmData *)FindByID(strID);

	if (pNew != NULL)
	{
		pNew->m_strValue = strValue;
		return pNew;
	}

	return AddNewData(strName, strID, strDataType, strValue, strUnit, strMin, strMax, strStep);
}

//2023-2-18  lijunqing
CDvmData* CDvmDataset::AddNewDataEx(CDvmData *pSrc)
{
    CDvmData *pNew = (CDvmData *)FindByID(pSrc->m_strID);

	if (pNew != NULL)
	{
        pNew->m_strValue = pSrc->m_strValue;
		return pNew;
	}

    pNew = (CDvmData *)pSrc->Clone();
	AddNewChild(pNew);

	return pNew;
}

CDvmData* CDvmDataset::AddNew2(const CString &strName,const CString &strID, const CString &strUnit, const CString &strDataTypeID
					, const CString &strValue, const CString &strFormat,BOOL bAddSame)
{
	CDvmData *pData = NULL;

	if (bAddSame)
	{
		pData = new CDvmData();
		AddNewChild(pData);
	}
	else
	{
		pData = (CDvmData *)FindByID(strID);

		if (pData == NULL)
		{
			pData = new CDvmData();
			AddNewChild(pData);
		}
	}

	pData->m_strName = strName;
	pData->m_strID = strID;
	pData->m_strUnit = strUnit;
	pData->m_strDataType = strDataTypeID;

#ifdef _DVM_VALUE_USE_CHAR_
#ifdef UNICODE
	wcscpy(pData->m_strValue, strValue);
#else
	BSTR bstr = strValue.AllocSysString();
	wcscpy(pData->m_strValue, bstr);
	::SysFreeString(bstr);
#endif
#else
	pData->m_strValue = strValue;
#endif

	pData->m_strFormat = strFormat;

	return pData;
}

long CDvmDataset::ClearByReserved(DWORD dwReserved)
{
	CExBaseList listDatas;
	POS pos = GetHeadPosition();
	POS posPrev = NULL;
	CDvmData *pData = NULL;
	long nDelCount = 0;

	while (pos != NULL)
	{
		posPrev = pos;
		pData = (CDvmData *)GetNext(pos);

#ifndef exbase_not_use_m_dwReserved
		if (pData->m_dwReserved != dwReserved)
#else
		if (pData->m_dwItemData != dwReserved)
#endif
		{
			DeleteAt(posPrev);
			nDelCount++;
		}
	}

	return nDelCount;
}

//2021-8-4  lijunqing CDvmDataset *pDatasetSrc ==>> CExBaseList *pListSrc
void CDvmDataset::AppendCloneWithoutRepeat(CExBaseList *pListSrc)
{
	POS pos = pListSrc->GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;
	CDvmData *pNew = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pListSrc->GetNext(pos);

		if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		pFind = (CDvmData *)FindByID(pData->m_strID);

		if (pFind == NULL)
		{
			pNew = (CDvmData *)pData->Clone();
			AddNewChild(pNew);
		}
		else
		{//2021-8-4  lijunqing  如果存在，在设置值
			pFind->m_strValue = pData->m_strValue;
		}
	}
}

long CDvmDataset::SerializeRead(char *pBuffer, long nLen)
{
	CBinarySerialBuffer oBuffer;
	oBuffer.ResetVersion();
	oBuffer.AttachBuffer(pBuffer, nLen);
	return SerializeRead(oBuffer);
}

long CDvmDataset::SerializeRead(CBinarySerialBuffer &oBinaryBuffer)
{
	oBinaryBuffer.SetCharSet(CHAR_SET_ASCII);
	dvm_InitDvmVersion(oBinaryBuffer);
	oBinaryBuffer.SetReadMode();
	oBinaryBuffer.ReadVersion();
//	oBinaryBuffer.SetVersionFind(g_dwDataMngrCurrVersion);
	oBinaryBuffer.SetVersionFind(oBinaryBuffer.m_dwVersion);

//	try
	{
		Serialize(oBinaryBuffer);
	}
// 	catch (...)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CDvmDataset::SerializeRead Error......"));
// 	}

	return 0;
}

long CDvmDataset::SerializeWrite(CBinarySerialBuffer &oBinaryBuffer)
{
	dvm_InitDvmVersion(oBinaryBuffer);
	oBinaryBuffer.SetCharSet(CHAR_SET_ASCII);
	oBinaryBuffer.SetVersionFind(g_dwDataMngrCurrVersion);

	oBinaryBuffer.SetCalSizeMode();
	oBinaryBuffer.WriteVersion();
	Serialize(oBinaryBuffer);
	oBinaryBuffer.AllocBuffer(0);

	oBinaryBuffer.SetWriteMode();
	oBinaryBuffer.WriteVersion();
	Serialize(oBinaryBuffer);

	return 0;
}

#ifdef _DBLIB_USE_SHAREMEM_
long CDvmDataset::SerializeWrite(CShareMemSerialize *pBinaryBuffer)
{
	pBinaryBuffer->ResetBufferPointer();
	dvm_InitDvmVersion(*pBinaryBuffer);
	pBinaryBuffer->SetCharSet(CHAR_SET_ASCII);
	pBinaryBuffer->SetVersionFind(g_dwDataMngrCurrVersion);

	pBinaryBuffer->SetWriteMode();
	pBinaryBuffer->WriteVersion();
	Serialize(*pBinaryBuffer);

	return 0;
}
#endif

//2021-1-3 lijunqing
void CDvmDataset::ResetDvmDataValues()
{
	POS pos = GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)GetNext(pos);
		pData->m_strValue.Empty();
	}
}

void CDvmDataset::SetDataChange(long nChange)
{
	POS pos = GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)GetNext(pos);
		pData->m_nChange = nChange;
	}
}


CValues* CDvmDataset::GetValues()
{
	CValues *pValues = new CValues();
	POS pos = GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)GetNext(pos);
		pValues->AddNew(pData->m_strID, pData->m_strName, pData->m_strValue);
	}

	return pValues;
}


long CDvmDataset::GetValueLong(const CString &strValueID)
{
	CDvmData *pDataObj = NULL;
	long nValue = 0;

	if (::IsStringNumber(strValueID.GetString()))
	{
		nValue = CString_To_long(strValueID);
	}
	else
	{
		pDataObj = (CDvmData *)FindByID(strValueID);

		if (pDataObj != NULL)
		{
			nValue = CString_To_long(pDataObj->m_strValue);
		}
	}

	return nValue;
}

double CDvmDataset::GetValueDouble(const CString &strValueID)
{
	CDvmData *pDataObj = NULL;
	double dValue = 0;

	if (::IsStringNumber(strValueID.GetString()))
	{
		dValue = CString_To_double(strValueID);
	}
	else
	{
		pDataObj = (CDvmData *)FindByID(strValueID);

		if (pDataObj != NULL)
		{
			dValue = CString_To_double(pDataObj->m_strValue);
		}
	}

	return dValue;
}


CDvmData* CDvmDataset::FindByNameEx(CDvmData *pDataSrc)
{
	CDvmData *p = NULL;
	CDvmData *pFind = NULL;
	POS pos = GetHeadPosition();
	CExBaseList oListFind;

	while (pos != NULL)
	{
		p = (CDvmData *)GetNext(pos);

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
		pFind = (CDvmData *)oListFind.GetHead();
		oListFind.RemoveAll();
		return pFind;
	}

	pos = oListFind.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmData *)oListFind.GetNext(pos);

		if (p->CmpDataType(pDataSrc))
		{//查找数据类型相同的对象，如果是结构体的定值，则需要判断子对象
			pFind = p;
			break;
		}
	}

	if (pFind == NULL)
	{
		pFind = (CDvmData *)oListFind.GetHead();
	}

	oListFind.RemoveAll();
	return pFind;
}

CDvmData* CDvmDataset::FindDataByID(const CString &strID)
{
	CString strDatasetPath = GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE, TRUE);
	long nLen = strDatasetPath.GetLength();
	CString strTemp = strID.Left(nLen);
	CDvmData *pFind = NULL;

	if (strTemp == strDatasetPath)
	{
		strTemp = strID.Mid(nLen+1);
		pFind = (CDvmData*)FindByID(strTemp);
	}
	else
	{
		pFind = (CDvmData*)FindByID(strID);
	}

	return pFind;
}


void  CDvmDataset::InitValueByDvmDataset(CDvmDataset *pDataset, BOOL bSetMinMax, DWORD dwMode_Name_ID)
{
	InitValueList(pDataset, bSetMinMax, dwMode_Name_ID);
}

void  CDvmDataset::InitValueList(CExBaseList *pList, BOOL bSetMinMax, DWORD dwMode_Name_ID)
{
	CDvmData *pDataObj = NULL;
	POS pos = pList->GetHeadPosition();
	CDvmData *pDvmData = NULL;

	while (pos != NULL)
	{
		pDvmData = (CDvmData*)pList->GetNext(pos);
		InitValueByDvmData(pDvmData, bSetMinMax, dwMode_Name_ID);
	}
}

void  CDvmDataset::InitValueByDvmData(CDvmData *pDvmData, BOOL bSetMinMax, DWORD dwMode_Name_ID)
{
	CDvmData *pDataObj = NULL;

	if ( (dwMode_Name_ID & DVM_DATASET_FIND_MODE_ID) == DVM_DATASET_FIND_MODE_ID )
	{
		pDataObj = (CDvmData*)FindByID(pDvmData->m_strID);

		if (pDataObj != NULL)
		{
			pDataObj->InitValueByData(pDvmData, bSetMinMax);
			return;
		}

		pDataObj = (CDvmData*)FindDataObjByID_Has2(pDvmData->m_strID);

		if (pDataObj != NULL)
		{
			pDataObj->InitValueByData(pDvmData, bSetMinMax);
			return;
		}
	}

	if ( (dwMode_Name_ID & DVM_DATASET_FIND_MODE_NAME) == DVM_DATASET_FIND_MODE_NAME)
	{
		pDataObj = (CDvmData*)FindByNameEx(pDvmData);

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


CDvmData* CDvmDataset::FindDataObjByID_Has(const CString &strIDPath)
{
	CDvmData *pDataObj = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;
	long nLen1, nLen2;

	while (pos != NULL)
	{
		pDataObj = (CDvmData*)GetNext(pos);
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

CDvmValue* CDvmDataset::FindDataObjValueByID_Has(const CString &strIDPath)
{
	CDvmData *pDataObj = NULL;
	POS pos = GetHeadPosition();
	CDvmValue *pFind = NULL;

	while (pos != NULL)
	{
		pDataObj = (CDvmData*)GetNext(pos);
		pFind = (CDvmValue *)pDataObj->FindDataObjValueByID_Has(strIDPath);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CDvmData* CDvmDataset::FindDataObjByID_Has2(const CString &strIDPath)
{
	CDvmData *pDataObj = NULL;
	POS pos = GetHeadPosition();
	CDvmData *pFind = NULL;
	long nLen1, nLen2;
	nLen2 = strIDPath.GetLength();

	while (pos != NULL)
	{
		pDataObj = (CDvmData*)GetNext(pos);
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

//////////////////////////////////////////////////////////////////////////
//
CDvmLogControl::CDvmLogControl()
{
	
}

CDvmLogControl::~CDvmLogControl()
{
	
}

long CDvmLogControl::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}


//xxy 20181113
long dvm_SerializeWrite(CExBaseObject *pObject, CBinarySerialBuffer &oBinaryBuffer)
{
	UINT nClassID = pObject->GetClassID();
	if((nClassID != DVMCLASSID_CDVMDATA) 
		&& (nClassID != DTMCLASSID_CDATAGROUP)
		&& (nClassID != DVMCLASSID_CDVMDATASET)
		&& (nClassID != DVMCLASSID_CDVMLOGICDEVICE))
	{
		return FALSE;
	}

	dvm_InitDvmVersion(oBinaryBuffer);
	oBinaryBuffer.SetCharSet(CHAR_SET_ASCII);
	oBinaryBuffer.SetVersionFind(g_dwDataMngrCurrVersion);

	oBinaryBuffer.SetCalSizeMode();
	oBinaryBuffer.WriteVersion();
	pObject->Serialize(oBinaryBuffer);
	oBinaryBuffer.AllocBuffer(0);

	oBinaryBuffer.SetWriteMode();
	oBinaryBuffer.WriteVersion();
	pObject->Serialize(oBinaryBuffer);

	return 0;
}

#ifdef _DBLIB_USE_SHAREMEM_
BOOL dvm_SerializeWrite(CExBaseObject *pObject, CShareMemSerialize *pBinaryBuffer)
{
	UINT nClassID = pObject->GetClassID();
	
	if((nClassID != DVMCLASSID_CDVMDATA) 
		&& (nClassID != DTMCLASSID_CDATAGROUP)
		&& (nClassID != DVMCLASSID_CDVMDATASET)
		&& (nClassID != DVMCLASSID_CDVMLOGICDEVICE))
	{
		return FALSE;
	}
	
	pBinaryBuffer->ResetBufferPointer();
	dvm_InitDvmVersion(*pBinaryBuffer);
	pBinaryBuffer->SetCharSet(CHAR_SET_ASCII);
	pBinaryBuffer->SetVersionFind(g_dwDataMngrCurrVersion);

	pBinaryBuffer->SetWriteMode();
	pBinaryBuffer->WriteVersion();
	pObject->Serialize(*pBinaryBuffer);

	return TRUE;
}
#endif

long dvm_SerializeRead(CExBaseObject *pObject, CBinarySerialBuffer &oBinaryBuffer)
{
	oBinaryBuffer.SetCharSet(CHAR_SET_ASCII);
	dvm_InitDvmVersion(oBinaryBuffer);
	oBinaryBuffer.SetReadMode();
	oBinaryBuffer.ReadVersion();
//	oBinaryBuffer.SetVersionFind(g_dwDataMngrCurrVersion);
	oBinaryBuffer.SetVersionFind(oBinaryBuffer.m_dwVersion);

	pObject->Serialize(oBinaryBuffer);

	return 0;
}

long dvm_SerializeRead(CExBaseObject *pObject, char *pBuffer, long nLen)
{
	CBinarySerialBuffer oBuffer;
	oBuffer.ResetVersion();
	oBuffer.AttachBuffer(pBuffer, nLen);
	return dvm_SerializeRead(pObject,oBuffer);
}
