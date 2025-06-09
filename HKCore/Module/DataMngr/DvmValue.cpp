//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmValue.cpp  CDvmValue


#include "stdafx.h"
#include "DvmValue.h"
#include "DvmData.h"
//2021-5-18  shaolei,lijunqing 
//AtsWorkBench：可能是61850的代码与CValue存在冲突，导致编译出错
//因此将CValue改为CXValue，同时保持兼容性
#ifdef _use_cxvalue_
#include "XValue.h"
#else
#include "Value.h"
#endif

#ifdef DVM_USE_MAP
#include "DvmCmp/DvmMapObject.h"
#endif	

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CDvmValue
CDvmValue::CDvmValue()
{
	//初始化属性
#ifdef DVM_USE_MAP
	m_pDvmMapObj = NULL;
#endif
	//初始化成员变量

#ifdef _DVM_VALUE_USE_CHAR_
	ZeroMemory(m_strValue , _DVM_VALUE_LENGTH_*sizeof(wchar_t));
#endif
}

CDvmValue::~CDvmValue()
{
}

long CDvmValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CDvmValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

    //2020-11-30  lijunqing
    if (pXmlKeys->m_nXmlOnlyWrite_Id_Value >= 1)
    {
		if (pXmlKeys->m_nXmlOnlyWrite_Id_Value > 0xFFFF)
		{//特殊处理：返回名称 2022-3-18
			xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, oElement, m_strName);
		}

		xml_SetAttributeValue(pXmlRWKeys->m_strIDKey, oElement, m_strID);
		xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
		xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);

		return 0;
	}

	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CDvmValue::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
#ifdef UNICODE
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
#else
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
#endif
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
#ifdef _DVM_VALUE_USE_CHAR_
#else
		BinarySerializeRead(oBinaryBuffer, m_strValue);
#endif
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
#ifdef _DVM_VALUE_USE_CHAR_
#else
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
#endif
	}
	return 0;
}


long CDvmValue::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.m_dwVersionFind != 0)
	{
		CExBaseList::SerializeChildren(oBinaryBuffer);
	}
	else
	{
	}

	return 0;
}


BOOL CDvmValue::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDvmValue *p = (CDvmValue*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDvmValue::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDvmValue *p = (CDvmValue*)pDest;

	p->m_strDataType = m_strDataType;
#ifdef _DVM_VALUE_USE_CHAR_
	wcscpy(p->m_strValue, m_strValue);
#else
	p->m_strValue = m_strValue;
#endif
	return TRUE;
}

CBaseObject* CDvmValue::Clone()
{
	CDvmValue *p = new CDvmValue();
	Copy(p);
	return p;
}

CBaseObject* CDvmValue::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CDvmValue *pNew = new CDvmValue();
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

CExBaseObject* CDvmValue::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmValueKey)
	{
		pNew = new CDvmValue();
	}

	return pNew;
}

CExBaseObject* CDvmValue::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDVMVALUE)
	{
		pNew = new CDvmValue();
	}

	return pNew;
}

#ifdef DVM_USE_MAP

BOOL CDvmValue::IsAllMap()
{
	if (m_pDvmMapObj == NULL)
	{
		return FALSE;
	}

	BOOL bAllMap = TRUE;
	POS pos = GetHeadPosition();
	CDvmValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmValue *)GetNext(pos);

		if (!p->IsAllMap())
		{
			bAllMap = FALSE;
			break;
		}
	}

	if (bAllMap)
	{
		if ( ((CDvmMapObject*)m_pDvmMapObj)->m_pMap == NULL)
		{
			bAllMap = FALSE;
		}
	}

	return bAllMap;
}

void CDvmValue::ResetDvmMap()
{
	m_pDvmMapObj = NULL;
	m_dwReserved = 0;

	POS pos = GetHeadPosition();
	CDvmValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmValue *)GetNext(pos);
		p->ResetDvmMap();
	}
}

#endif
CDvmValue* CDvmValue::FindValueByID(const CString &strValueID, BOOL bUseHas)
{
	CDvmValue *pValue;
	CDvmValue *pFind = (CDvmValue*)FindByID(strValueID);

	if (pFind != NULL)
	{
		return pFind;
	}

	if (!bUseHas)
	{
		return pFind;
	}

	POS pos = GetHeadPosition();
	long nLen = strValueID.GetLength();

	while (pos != NULL)
	{
		pValue = (CDvmValue *)GetNext(pos);

		if (pValue->m_strID.Right(nLen) == strValueID)
		{
			pFind = pValue;
			break;
		}

		if (pValue->GetCount() > 0)
		{
			pFind = pValue->FindValueByID(strValueID, bUseHas);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

CDvmValue* CDvmValue::AddValue(const CString &strAttrID, const CString &strValue)
{
	CDvmValue *pValue = new CDvmValue();
	pValue->m_strID = strAttrID;

#ifdef _DVM_VALUE_USE_CHAR_
#ifdef UNICODE
	wcscpy(pValue->m_strValue, strValue);
#else
	BSTR bstr = strValue.AllocSysString();
	wcscpy(pValue->m_strValue, bstr);
	::SysFreeString(bstr);
#endif
#else
	pValue->m_strValue = strValue;
#endif
	AddNewChild(pValue);

	return pValue;
}

CDvmValue* CDvmValue::AddValue(const CString &strName, const CString &strAttrID, const CString &strValue)
{
	CDvmValue* pValue = AddValue(strAttrID,strValue);
	if (pValue != NULL)
	{
		pValue->m_strName = strName;
	}

	return pValue;
}

CDvmValue* CDvmValue::AddValue(const CString &strName, const CString &strAttrID, const CString &strDataType, const CString &strValue)
{
	CDvmValue* pValue = AddValue(strAttrID,strValue);
	
	if (pValue != NULL)
	{
		pValue->m_strName = strName;
		pValue->m_strDataType = strDataType;
	}

	return pValue;
}

BOOL CDvmValue::UpdateChildValue(CDvmValue *pSrcParentValue, BOOL bIsNew)
{
	BOOL bRet = TRUE;
	POS pos = pSrcParentValue->GetHeadPosition();
	CDvmValue *pSrcValue = NULL;
	CDvmValue *pDstValue = NULL;
	CString strSrcID;

	while (pos != NULL)
	{
		pSrcValue = (CDvmValue *)pSrcParentValue->GetNext(pos);
		strSrcID = pSrcValue->m_strID;
		pDstValue = (CDvmValue *)FindByID(strSrcID);

		if (pDstValue == NULL)
		{
			if (bIsNew)
			{
				pDstValue = (CDvmValue *)pSrcValue->CloneEx(TRUE,TRUE);
				AddNewChild(pDstValue);
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
			pDstValue->m_strValue = pSrcParentValue->m_strValue;
			bRet = pDstValue->UpdateChildValue(pSrcValue, bIsNew);
		}

	}

	return bRet;
}

//2021-10-22  lijunqing
void CDvmValue::InitByValues(CExBaseList *pValues)
{
	CString strID = GetIDPath_Root_Dataset();
	CValue *pValue = (CValue*)pValues->FindByID(strID);

	if (pValue == NULL)
	{
		return;
	}

	m_strValue = pValue->m_strValue;

	POS pos = GetHeadPosition();
	CDvmValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmValue *)GetNext(pos);
		p->InitByValues(pValues);
	}
}

CString CDvmValue::GetIDPath_Root_Dataset(const CString &strPathSp)
{
	CDvmData *pData = (CDvmData*)GetAncestor(DVMCLASSID_CDVMDATA);
	CString strID = pData->GetIDPath_Root_Dataset();

	CExBaseList oList;
	GetAllAncestorEqClassID(&oList, DVMCLASSID_CDVMVALUE);
	POS pos = oList.GetHeadPosition();

	if (pos != NULL)
	{
		CExBaseObject *p = NULL;
		oList.GetNext(pos);

		while (pos != NULL)
		{
			p = oList.GetNext(pos);
			strID.AppendFormat(_T("%s%s"), p->m_strID.GetString(), strPathSp.GetString());
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

BOOL CDvmValue::GetValueByID(const CString &strValueID, CString &strValue)
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

	return FALSE;
}


void CDvmValue::InitValueByData(CDvmValue *pData)
{
	m_strValue = pData->m_strValue;

	if (GetCount() == 0)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CDvmValue *pDest = NULL;
	CDvmValue *pSrc = NULL;

	while (pos != NULL)
	{
		pDest = (CDvmValue *)GetNext(pos);
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


//2022-5-13  lijunqing
CDvmValue* dvm_FindByID_Has(CExBaseList *pParent, const CString &strValueID)
{
	CDvmValue *pDvmValue = NULL;
	CDvmValue *pFind = NULL;

	if (strValueID.Find(_T("Abs_")) >= 0 || strValueID.Find(_T("Rst_")) >= 0 || strValueID.Find(_T("Rel_")) >= 0)
	{
		return NULL;
	}

	POS pos = pParent->GetHeadPosition();

	while (pos != NULL)
	{
		pDvmValue = (CDvmValue *)pParent->GetNext(pos);

		if (strValueID.Find(pDvmValue->m_strID) >= 0)
		{
			pFind = pDvmValue;
			return pFind;
		}
	}

	return pFind;
}

CDvmValue* dvm_FindByID_MmsAttr(CExBaseList *pParent, const CString &strAttrID)
{
	CDvmValue *pDvmValue = NULL;
	CDvmValue *pFind = NULL;

	POS pos = pParent->GetHeadPosition();

	while (pos != NULL)
	{
		pDvmValue = (CDvmValue *)pParent->GetNext(pos);

		if (strAttrID == pDvmValue->m_strID.Right(strAttrID.GetLength()) )
		{
			pFind = pDvmValue;
			return pFind;
		}
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////
//CDvmBrcbValue
CDvmBrcbValue::CDvmBrcbValue()
{

}

CDvmBrcbValue::~CDvmBrcbValue()
{

}


CBaseObject* CDvmBrcbValue::Clone()
{
	CDvmBrcbValue *p = new CDvmBrcbValue();
	Copy(p);
	return p;
}

CDvmValue* CDvmValue::FindByID_Has(const CString &strID)
{
	return dvm_FindByID_Has(this, strID);
// 	CDvmValue *pDvmValue = NULL;
// 	CDvmValue *pFind = NULL;
// 
// 	if (strID.Find(_T("Abs_")) >= 0 || strID.Find(_T("Rst_")) >= 0 || strID.Find(_T("Rel_")) >= 0)
// 	{
// 		return NULL;
// 	}
// 
// 	POS pos = GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pDvmValue = (CDvmValue *)GetNext(pos);
// 
// 		if (strID.Find(pDvmValue->m_strID) >= 0)
// 		{
// 			pFind = pDvmValue;
// 			break;
// 		}
// 	}
// 
// 	return pFind;
}


CDvmValue* CDvmValue::FindByID_MmsAttr(const CString &strAttrID)
{
	return dvm_FindByID_MmsAttr(this, strAttrID);
}

CString CDvmValue::GetAttrByID_MmsAttr(const CString &strAttrID)
{
	CDvmValue *p = dvm_FindByID_MmsAttr(this, strAttrID);

	if (p == NULL)
	{
		return _T("");
	}

	return p->m_strValue;
}

CDvmValue* CDvmValue::FindByID_HasEx(const CString &strSubID)
{
	CDvmValue *pDvmValue = NULL;
	CDvmValue *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDvmValue = (CDvmValue *)GetNext(pos);

		if (pDvmValue->m_strID.Find(strSubID) >= 0)
		{
			pFind = pDvmValue;
			break;
		}
	}

	return pFind;
}


BOOL CDvmValue::SetValue_Mms(const CString &strAttrID, const CString &strValue)
{
	CDvmValue *pValue = FindByID_MmsAttr(strAttrID);

	if (pValue == NULL)
	{
		return FALSE;
	}
	else
	{
		pValue->m_strValue = strValue;
		return TRUE;
	}
}

BOOL CDvmValue::SetValue_Mms(const CString &strAttrID, long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);

	return SetValue_Mms(strAttrID, strValue);
}

BOOL CDvmValue::SetValue_Mms(const CString &strAttrID, unsigned long nValue)
{
	CString strValue;
	strValue.Format(_T("%u"), nValue);

	return SetValue_Mms(strAttrID, strValue);
}

BOOL CDvmValue::SetValue_Mms_Hex(const CString &strAttrID, unsigned long nValue)
{
	CString strValue;
	strValue.Format(_T("0x%08X"), nValue);

	return SetValue_Mms(strAttrID, strValue);
}

BOOL CDvmValue::SetValue_Mms(const CString &strAttrID, float fValue, long nDecimal)
{
	CString strValue;
	strValue.Format(_T("%f"), fValue);

	return SetValue_Mms(strAttrID, strValue);
}

BOOL CDvmValue::SetValue_Mms(const CString &strAttrID, double dValue, long nDecimal)
{
	CString strValue;
	strValue.Format(_T("%f"), dValue);

	return SetValue_Mms(strAttrID, strValue);
}


//////////////////////////////////////////////////////////////////////////
//CDvmValueKeyMngr

// #define VarID_max    7//6 金智增加
// static ST_CHAR g_pszVarID[VarID_max][15] = {"$setMag$f", "$mag$f", "$mag$i","$setVal","$general", "$stVal","$setCharact"};//zhouhj 解决金智读模型描述为空问题

CDvmValueKeyMngr::CDvmValueKeyMngr()
{
	strcpy(m_pszValueKey[0], "stVal");
	strcpy(m_pszValueKey[1], "setMag");
	strcpy(m_pszValueKey[2], "setVal");
	strcpy(m_pszValueKey[3], "general");
	strcpy(m_pszValueKey[4], "mag$f");
	strcpy(m_pszValueKey[5], "ang$f");
	strcpy(m_pszValueKey[6], "ctlVal");
	strcpy(m_pszValueKey[7], "setMag$f");
	strcpy(m_pszValueKey[8], "mag$i");
	strcpy(m_pszValueKey[9], "setCharact");
	strcpy(m_pszValueKey[10], "posVal");//zhouhongjun 20210610 增加用于遥调数据对象

	m_nKeyCount = 11;

	m_astrLdIDKey.Add(_T("LD0$"));
	m_astrLdIDKey.Add(_T("PROT$"));
	m_astrLdIDKey.Add(_T("RCD$"));
	m_astrLdIDKey.Add(_T("PQLD$"));//zhowTest20180111 为电能质量装置新增
}

CDvmValueKeyMngr::~CDvmValueKeyMngr()
{

}

void CDvmValueKeyMngr::InitValueKeyMngr(const CString &strFile)
{
	FILE *pFile = NULL;

    char *pszFile = NULL;
    CString_to_char(strFile, &pszFile);
    pFile = fopen(pszFile, "r");
    delete pszFile;

	if (pFile == NULL)
	{
		return;
	}

	char pszKey[20];
	long nLen = 0;

	while (ftell(pFile) != EOF)
	{
		nLen = fscanf(pFile,"%s", pszKey);
		
		if (nLen > 0)
		{
			if (IsValueID(pszKey))
			{
				continue;;
			}

			strcpy(m_pszValueKey[m_nKeyCount], pszKey);
			m_nKeyCount++;

			if (m_nKeyCount >= VALUE_KEY_MAX_COUNT)
			{
				break;
			}
		}
	}

	fclose(pFile);
}
