//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmData.cpp  CDvmData


#include "stdafx.h"
#include "DvmData.h"

#ifdef DVM_USE_MAP
#include "DvmCmp\DvmMapObject.h"
#endif	

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CDvmData
CDvmData::CDvmData()
{
	//初始化属性
	m_nIndex = 0;
	m_nChange = 0;
#ifdef _USE_IN_PPPROTOCOL_
	m_nDataTypeID = 0;
#endif

	//初始化成员变量
	m_dTime = 0;
#ifdef DVM_USE_MAP
	m_pDvmMapObj = NULL;
#endif

#ifdef _DVM_VALUE_USE_CHAR_
	ZeroMemory(m_strValue , _DVM_VALUE_LENGTH_*sizeof(wchar_t));
#else
#endif
}

CDvmData::~CDvmData()
{
}

long CDvmData::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strMinKey, oNode, m_strMin);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxKey, oNode, m_strMax);
	xml_GetAttibuteValue(pXmlKeys->m_strFormatKey, oNode, m_strFormat);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strTimeKey, oNode, m_dTime);

	xml_GetAttibuteValue(pXmlKeys->m_strChangeKey, oNode, m_nChange);
	xml_GetAttibuteValue(pXmlKeys->m_strStepKey, oNode, m_strStep);

#ifdef _USE_IN_PPPROTOCOL_
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeIDKey, oNode, m_nDataTypeID);
	xml_GetAttibuteValue(pXmlKeys->m_strExprRcvKey, oNode, m_strExprRcv);
	xml_GetAttibuteValue(pXmlKeys->m_strExprSendKey, oNode, m_strExprSend);
#endif

	return 0;
}

long CDvmData::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strMinKey, oElement, m_strMin);
	xml_SetAttributeValue(pXmlKeys->m_strMaxKey, oElement, m_strMax);
	xml_SetAttributeValue(pXmlKeys->m_strFormatKey, oElement, m_strFormat);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_dTime);

	xml_SetAttributeValue(pXmlKeys->m_strChangeKey, oElement, m_nChange);
	xml_SetAttributeValue(pXmlKeys->m_strStepKey, oElement, m_strStep);

#ifdef _USE_IN_PPPROTOCOL_
	xml_SetAttributeValue(pXmlKeys->m_strDataTypeIDKey, oElement, m_nDataTypeID);
	xml_SetAttributeValue(pXmlKeys->m_strExprRcvKey, oElement, m_strExprRcv);
	xml_SetAttributeValue(pXmlKeys->m_strExprSendKey, oElement, m_strExprSend);
#endif

	return 0;
}

long CDvmData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
#ifdef _DVM_VALUE_USE_CHAR_
		ASSERT(FALSE);
#else
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
#endif
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_strMin);
		BinarySerializeCalLen(oBinaryBuffer, m_strMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strFormat);
		BinarySerializeCalLen(oBinaryBuffer, m_dTime);
		BinarySerializeCalLen(oBinaryBuffer, m_nChange);
		BinarySerializeCalLen(oBinaryBuffer, m_strStep);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
#ifdef _DVM_VALUE_USE_CHAR_
		ASSERT (FALSE);
#else
		BinarySerializeRead(oBinaryBuffer, m_strValue);
#endif
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
		BinarySerializeRead(oBinaryBuffer, m_strMin);
		BinarySerializeRead(oBinaryBuffer, m_strMax);
		BinarySerializeRead(oBinaryBuffer, m_strFormat);

		if (oBinaryBuffer.m_dwVersionFind >= DATAMNGR_VERSION_1_1)
		{
			BinarySerializeRead(oBinaryBuffer, m_dTime);
		}

		if (oBinaryBuffer.m_dwVersionFind >= DATAMNGR_VERSION_1_4)
		{
			BinarySerializeRead(oBinaryBuffer, m_nChange);
		}

		if (oBinaryBuffer.m_dwVersionFind >= DATAMNGR_VERSION_1_5)
		{
			BinarySerializeRead(oBinaryBuffer, m_strStep);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
#ifdef _DVM_VALUE_USE_CHAR_
		ASSERT (FALSE);
#else
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
#endif
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
		BinarySerializeWrite(oBinaryBuffer, m_strMin);
		BinarySerializeWrite(oBinaryBuffer, m_strMax);
		BinarySerializeWrite(oBinaryBuffer, m_strFormat);
		BinarySerializeWrite(oBinaryBuffer, m_dTime);
		BinarySerializeWrite(oBinaryBuffer, m_nChange);
		BinarySerializeWrite(oBinaryBuffer, m_strStep);
	}

	return 0;
}

BOOL CDvmData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDvmData *p = (CDvmData*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	if(m_strMin != p->m_strMin)
	{
		return FALSE;
	}

	if(m_strMax != p->m_strMax)
	{
		return FALSE;
	}

	if(m_strFormat != p->m_strFormat)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDvmData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDvmData *p = (CDvmData*)pDest;

	p->m_strDataType = m_strDataType;
#ifdef _DVM_VALUE_USE_CHAR_
	wcscpy(p->m_strValue, m_strValue);
#else
	p->m_strValue = m_strValue;
#endif
	p->m_strUnit = m_strUnit;
	p->m_strMin = m_strMin;
	p->m_strMax = m_strMax;
	p->m_strFormat = m_strFormat;
	p->m_nChange = m_nChange;
	p->m_strStep = m_strStep;
	p->m_dTime = m_dTime;

#ifdef _USE_IN_PPPROTOCOL_
	p->m_nDataTypeID = m_nDataTypeID;
	p->m_strExprRcv = m_strExprRcv;
	p->m_strExprSend = m_strExprSend;
#endif

	return TRUE;
}

CBaseObject* CDvmData::Clone()
{
	CDvmData *p = new CDvmData();
	Copy(p);
	return p;
}

CExBaseObject* CDvmData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmValueKey)
	{
		pNew = new CDvmValue();
	}

	return pNew;
}

CExBaseObject* CDvmData::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDVMVALUE)
	{
		pNew = new CDvmValue();
	}
	else
	{
		pNew = new CDvmValue();
	}

	return pNew;
}

BOOL CDvmData::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDVMVALUE)
	{
		return TRUE;
	}

	return FALSE;
}


long CDvmData::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
#ifdef UNICODE
	pListCtrl->SetItemText(lItemIndex, 3, m_strValue);
#else
	pListCtrl->SetItemText(lItemIndex, 3, CString(m_strValue));
#endif
	pListCtrl->SetItemText(lItemIndex, 4, m_strUnit);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BOOL CDvmData::HasValueID(const CString &strValueID)
{
	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strNameKey)
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIDKey)
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::ValueKey())
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::DataTypeKey())
	{
		return TRUE;
	}

	if (strValueID == _T("datatype"))
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::FormatKey())
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::ChangeKey())
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::TimeKey())
	{
		return TRUE;
	}

	if (strValueID == _T("item-index"))
	{
		return TRUE;
	}

#ifdef _USE_IN_PPPROTOCOL_
	if (strValueID == CDataMngrXmlRWKeys::DataTypeIDKey())
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::ExprRcvKey())
	{
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::ExprSendKey())
	{
		return TRUE;
	}
#endif

	CDvmValue *pValue = FindValueByID(strValueID);

	if (pValue != NULL)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CDvmData::HasValue(const CString &strValueID, const CString &strValue)
{
	CString strTemp;
	
	if (GetValueByID(strValueID, strTemp))
	{
		return strTemp == strValue;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDvmData::HasValueEx(const CString &strValueID, const CString &strValue)
{
	CString strTemp;

	if (GetValueByID(strValueID, strTemp))
	{
		//兼容  ####$mag$f == mag$f
		if (strTemp.Find('$') > 0)
		{
			if (strTemp.GetLength() == strValue.GetLength())
			{
				return strTemp == strValue; 
			}
			else if (strTemp.GetLength() > strValue.GetLength())
			{
				return (strTemp.Right(strValue.GetLength()) == strValue);
			}
			else
			{
				return (strValue.Right(strTemp.GetLength()) == strTemp);
			}		
		}
		else
		{//如果不包含$，则直接判相等
			return (strTemp == strValue);
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CDvmData::HasValueHasStr(const CString &strValueID, const CString &strValue)
{
	CString strTemp;

	if (GetValueByID(strValueID, strTemp))
	{
		return (strTemp.Find(strValue) >= 0);
	}
	else
	{
		return FALSE;
	}
}

BOOL CDvmData::HasValueHasNoStr(const CString &strValueID, const CString &strValue)
{
	CString strTemp;

	if (GetValueByID(strValueID, strTemp))
	{
		return (strTemp.Find(strValue) < 0);
	}
	else
	{
		return FALSE;
	}
}

BOOL CDvmData::GetValueByID(const CString &strValueID, CString &strValue)
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

	if (strValueID == CDataMngrXmlRWKeys::FormatKey())
	{
		strValue = m_strFormat;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::ChangeKey())
	{
		strValue.Format(_T("%d"), m_nChange);;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::StepKey())
	{
		strValue = m_strStep;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::TimeKey())
	{
		strValue = dvm_GetTimeString(m_dTime);

		return TRUE;
	}

	if (strValueID == _T("item-index"))
	{
		strValue.Format(_T("%d"), m_nIndex);
		return TRUE;
	}


#ifdef _USE_IN_PPPROTOCOL_
	if (strValueID == CDataMngrXmlRWKeys::DataTypeIDKey())
	{
		strValue.Format(_T("%d"), m_nDataTypeID);
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::ExprRcvKey())
	{
		strValue = m_strExprRcv;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::ExprSendKey())
	{
		strValue = m_strExprSend;
		return TRUE;
	}
#endif


	CDvmValue *pValue = FindValueByID(strValueID);

	if (pValue != NULL)
	{
		strValue = pValue->m_strValue;
		return TRUE;
	}

	return FALSE;
}

void CDvmData::GetTime(CString &strTime)
{
	POS pos = GetHeadPosition();
	CDvmValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)GetNext(pos);

		if (pValue->m_strID.Right(2) == _T("$t"))
		{
			strTime = pValue->m_strValue;
			return;
		}
	}

	SYSTEMTIME tmSys;
	CTime tm((__int64)m_dTime);
	tm.GetAsSystemTime(tmSys);
	strTime.Format(_T("%d-%d-%d %d:%d:%d %d"), tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour
		, tmSys.wMinute, tmSys.wSecond, tmSys.wMilliseconds);
}

CString CDvmData::GetTime()
{
	CString strTime;
	GetTime(strTime);
	return strTime;
}

CDvmValue* CDvmData::FindValueByID(const CString &strValueID)
{
	CDvmValue *pValue;
	CDvmValue *pFind = (CDvmValue*)FindByID(strValueID);

	if (pFind != NULL)
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
			pFind = pValue->FindValueByID(strValueID);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

#ifdef _DVM_VALUE_USE_CHAR_
long CDvmData::ValueToLong()
{
	wchar_t *pEnd = NULL;
	return wcstol(m_strValue, &pEnd, 10);
}

#else
#endif

CString CDvmData::GetValueByID(const CString &strValueID)
{
	CString strValue;
	GetValueByID(strValueID, strValue);
	return strValue;
}


BOOL CDvmData::SetAttr(const CString &strAttrID, const CString &strValue)
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

	if (strAttrID == CDataMngrXmlRWKeys::ValueKey())
	{
#ifdef _DVM_VALUE_USE_CHAR_
#ifdef UNICODE
		wcscpy(m_strValue, strValue);
#else
		BSTR bstr = strValue.AllocSysString();
		wcscpy(m_strValue, bstr);
		::SysFreeString(bstr);
#endif
#else
		m_strValue = strValue;
#endif
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::DataTypeKey())
	{
		m_strDataType = strValue;
		return TRUE;
	}

	if (strAttrID == _T("datatype"))
	{
		m_strDataType = strValue;
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::FormatKey())
	{
		m_strFormat = strValue;
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::ChangeKey())
	{
		m_nChange = CString_To_long(strValue);
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::TimeKey())
	{
		CTime tm;
		tm.Format(strValue);
		m_dTime = (double)tm.GetTime();

		return TRUE;
	}

	if (strAttrID == _T("item-index"))
	{
		m_nIndex = CString_To_long(strValue);
		return TRUE;
	}


#ifdef _USE_IN_PPPROTOCOL_
	if (strAttrID == CDataMngrXmlRWKeys::DataTypeIDKey())
	{
		m_nDataTypeID = CString_To_long(strValue);
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::ExprRcvKey())
	{
		m_strExprRcv = strValue;
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::ExprSendKey())
	{
		m_strExprSend = strValue;
		return TRUE;
	}
#endif

	CDvmValue *pValue = (CDvmValue*)FindValueByID(strAttrID);

	if (pValue != NULL)
	{
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
		return TRUE;
	}
	else
	{
		pValue = new CDvmValue();
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
	}

	return FALSE;
}

CDvmValue* CDvmData::AddNewValue(CDvmValue *pSrc)
{
	CDvmValue *pValue = NULL;

	if (pSrc != NULL)
	{
		pValue = (CDvmValue *)pSrc->Clone();
	}
	else
	{
		pValue = new CDvmValue();
	}

	AddNewChild(pValue);

	return pValue;
}
CDvmValue* CDvmData::AddValue(const CString &strAttrID, const CString &strValue)
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

#ifdef DVM_USE_MAP

BOOL CDvmData::IsAllMap()
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

#endif


//////////////////////////////////////////////////////////////////////////
//CDvmBrcb
CDvmBrcb::CDvmBrcb()
{

}

CDvmBrcb::~CDvmBrcb()
{

}

CBaseObject* CDvmBrcb::Clone()
{
	CDvmBrcb *p = new CDvmBrcb();
	Copy(p);
	return p;
}


CExBaseObject* CDvmBrcb::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCDvmDataKey)
	{
		pNew = new CDvmBrcbValue();
	}

	return pNew;
}

CExBaseObject* CDvmBrcb::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDVMVALUE)
	{
		pNew = new CDvmBrcbValue();
	}
	else
	{
		pNew = new CDvmBrcbValue();
	}

	return pNew;
}


long CDvmBrcb::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	
	return 0;
}


CString dvm_GetTimeString(double dTime)
{
	CString strTime;
	SYSTEMTIME tmSys;
	CTime tm((__int64)dTime);

	tm.GetAsSystemTime(tmSys);
	strTime.Format(_T("%d-%d-%d %d:%d:%d %d"), tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour
		, tmSys.wMinute, tmSys.wSecond, tmSys.wMilliseconds);
	
	return strTime;
}

