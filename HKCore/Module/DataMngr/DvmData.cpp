//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmData.cpp  CDvmData


#include "stdafx.h"
#include "DvmData.h"
#include "../MemBuffer/StringToSystimeBuffer.h"

#include "../API/MathApi.h"
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

CDvmValueKeyMngr g_oXDvmValueKeyMngr;


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

long CDvmData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	//20220408  shaolei   只保存id和value
	if (pXmlKeys->m_nXmlOnlyWrite_Id_Value >= 1)
	{
		if (pXmlKeys->m_nXmlOnlyWrite_Id_Value > 0xFFFF)
		{//特殊处理：返回名称 2022-3-18
			xml_GetAttibuteValue(pXmlRWKeys->m_strNameKey, oNode, m_strName);
		}


		xml_GetAttibuteValue(pXmlRWKeys->m_strIDKey, oNode, m_strID);
		xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
		//shaolei 2022-1-18 JSON模式下，需要根据数据类型，去写数值
		//xml_SetAttributeValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
		XmlReadOwn_Value(oNode, pXmlRWKeys);

		//20240717 huangliang 定值关联添加
		xml_GetAttibuteValue(pXmlKeys->m_strFormatKey, oNode, m_strFormat);

		return 0;
	}

	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strDefaultValueKey2, oNode, m_strDefaultValue);
//	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);//zhouhj 2022-2-21 JSON模式下，需要根据数据类型分别处理
	XmlReadOwn_Value(oNode,pXmlKeys);
	xml_GetAttibuteValue(pXmlKeys->m_strFormatKey, oNode, m_strFormat);

	if (pXmlKeys->m_nXmlOnlyRead_MainAttr >= 1)
	{
		return 0;
	}

	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strMinKey, oNode, m_strMin);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxKey, oNode, m_strMax);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);

	//xxy 20200618 time属性为字符串
#ifdef USE_ATTR_DVMDATA_TIME_STRING
	xml_GetAttibuteValue(pXmlKeys->m_strTimeKey, oNode, m_strTime);
#else
	xml_GetAttibuteValue(pXmlKeys->m_strTimeKey, oNode, m_dTime);
#endif
	

	xml_GetAttibuteValue(pXmlKeys->m_strChangeKey, oNode, m_nChange);
	xml_GetAttibuteValue(pXmlKeys->m_strStepKey, oNode, m_strStep);

#ifdef _USE_IN_PPPROTOCOL_
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeIDKey, oNode, m_nDataTypeID);
	xml_GetAttibuteValue(pXmlKeys->m_strExprRcvKey, oNode, m_strExprRcv);
	xml_GetAttibuteValue(pXmlKeys->m_strExprSendKey, oNode, m_strExprSend);
#endif

	return 0;
}

long CDvmData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	//2020-10-23  只保存id和value
    if (pXmlKeys->m_nXmlOnlyWrite_Id_Value >= 1)
	{
		if (pXmlKeys->m_nXmlOnlyWrite_Id_Value > 0xFFFF)
		{//特殊处理：返回名称 2022-3-18
			xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, oElement, m_strName);
		}


		xml_SetAttributeValue(pXmlRWKeys->m_strIDKey, oElement, m_strID);
        xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
		//shaolei 2022-1-18 JSON模式下，需要根据数据类型，去写数值
        //xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
		XmlWriteOwn_Value(oElement, pXmlRWKeys);

		//20240717 huangliang 定值关联添加
		xml_SetAttributeValue(pXmlKeys->m_strFormatKey, oElement, m_strFormat);

		return 0;
	}

	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strDefaultValueKey2, oElement, m_strDefaultValue);
	//xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	XmlWriteOwn_Value(oElement, pXmlRWKeys);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strMinKey, oElement, m_strMin);
	xml_SetAttributeValue(pXmlKeys->m_strMaxKey, oElement, m_strMax);
	xml_SetAttributeValue(pXmlKeys->m_strFormatKey, oElement, m_strFormat);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
//	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_dTime);

	//xxy 20200618 time属性为字符串
#ifdef USE_ATTR_DVMDATA_TIME_STRING
	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_strTime);
#else
	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_dTime);
#endif

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
	if (oBinaryBuffer.m_dwVersionFind == DATAMNGR_VERSION_FF)
	{
		return SerializeOwn_FF(oBinaryBuffer);
	}

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
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_strDefaultValue);
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

		if (oBinaryBuffer.m_dwVersionFind >= DATAMNGR_VERSION_1_7)
		{
			BinarySerializeRead(oBinaryBuffer, m_nIndex);
		}

		if (oBinaryBuffer.m_dwVersionFind >= DATAMNGR_VERSION_1_9)
		{
			BinarySerializeRead(oBinaryBuffer, m_strDefaultValue);
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
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
		BinarySerializeWrite(oBinaryBuffer, m_strDefaultValue);
	}

	return 0;
}

long CDvmData::SerializeOwn_FF(CBinarySerialBuffer &oBinaryBuffer)
{
	//CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strFormat);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strFormat);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strFormat);
	}

	return 0;
}

BOOL CDvmData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDvmData *p = (CDvmData*)pObj;

	if (CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsEqualOwn_Id_Value >= 1)
	{
		if (p->m_strID != m_strID)
		{
			return FALSE;
		}

		if( !IsEqualOwn_Value(pObj) )
		{
			return FALSE;
		}

		//20240717 huangliang
		if (p->m_strFormat != m_strFormat)
		{
			return FALSE;
		}

		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if( !IsEqualOwn_Value(pObj) )
	{
		return FALSE;
	}
// 	if(m_strValue != p->m_strValue)
// 	{
// 		return FALSE;
// 	}

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

	if(m_strDefaultValue != p->m_strDefaultValue)
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
	p->m_strTime = m_strTime;
	p->m_strDefaultValue = m_strDefaultValue;
	p->m_nIndex = m_nIndex;//zhouhj 2023.12.12

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

CBaseObject* CDvmData::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CDvmData *pNew = new CDvmData();
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

//shaolei 2022-1-18 JSON模式下，需要根据数据类型分别处理
void CDvmData::XmlWriteOwn_Value(CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (oElement.GetXmlRWType() != _JSON_TYPE_)//zhouhj 2024.9.19 只对json做特殊处理
	{
		xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
		return;
	}

	if (m_strDataType == DATAMNGR_DATATYPE_STRING)
	{
		xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	}
	else if (m_strDataType == DATAMNGR_DATATYPE_LONG || m_strDataType == DATAMNGR_DATATYPE_INT)
	{
		long nValue = CString_To_long(m_strValue);
		xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, nValue);
	}
	else if (m_strDataType == DATAMNGR_DATATYPE_INT64)
	{
		__int64 nValue = CString_To_i64(m_strValue);
		xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, nValue);
	}
	else if (m_strDataType == DATAMNGR_DATATYPE_DOUBLE || m_strDataType == DATAMNGR_DATATYPE_FLOAT
		|| m_strDataType == DATAMNGR_DATATYPE_NUMBER)
	{
		double dValue = CString_To_double(m_strValue);
		xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, dValue);
	}
	else
	{
		xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	}
}

//zhouhj 2022-2-21 JSON模式下，需要根据数据类型分别处理
void CDvmData::XmlReadOwn_Value(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	//2024.9.19 Xuzt 如果不是json格式则直接读字符串
	if (oNode.GetXmlRWType() != _JSON_TYPE_)
	{
		xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
		return;
	}

	if (m_strDataType == DATAMNGR_DATATYPE_STRING)
	{
		xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	}
	else if (m_strDataType == DATAMNGR_DATATYPE_LONG || m_strDataType == DATAMNGR_DATATYPE_INT)
	{
		long nValue = 0;
		xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, nValue);
		m_strValue.Format(_T("%d"),nValue);
	}
	else if (m_strDataType == DATAMNGR_DATATYPE_INT64)
	{
		__int64 nValue = 0;
		xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, nValue);
		m_strValue.Format(_T("%lld"),nValue);
	}
	else if (/*m_strDataType == DATAMNGR_DATATYPE_DOUBLE || */m_strDataType == DATAMNGR_DATATYPE_FLOAT
		|| m_strDataType == DATAMNGR_DATATYPE_NUMBER)
	{
		double dValue = 0.0f;
		xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, dValue);
		m_strValue.Format(_T("%lf"),dValue);
	}
	else if (m_strDataType == DATAMNGR_DATATYPE_DOUBLE)
	{
		double dValue = 0.0f;
		xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, dValue);
		m_strValue.Format(_T("%lf"),dValue);
	}
	else
	{
		xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	}
}

BOOL CDvmData::IsEqualOwn_Value(CBaseObject* pObj)
{
	CDvmData *p = (CDvmData*)pObj;

	if (m_strDataType == DATAMNGR_DATATYPE_STRING)
	{
		if (m_strValue != p->m_strValue)
		{
			return FALSE;
		}
	}
	else if (m_strDataType == DATAMNGR_DATATYPE_LONG || m_strDataType == DATAMNGR_DATATYPE_INT)
	{
		long nValue1 = CString_To_long(m_strValue);
		long nValue2 = CString_To_long(p->m_strValue);
		
		if (nValue1 != nValue2)
		{
			return FALSE;
		}
	}
	else if (m_strDataType == DATAMNGR_DATATYPE_INT64)
	{
		__int64 nValue1 = CString_To_i64(m_strValue);
		__int64 nValue2 = CString_To_i64(p->m_strValue);
		
		if (nValue1 != nValue2)
		{
			return FALSE;
		}
	}
	else if (m_strDataType == DATAMNGR_DATATYPE_DOUBLE || m_strDataType == DATAMNGR_DATATYPE_FLOAT
		|| m_strDataType == DATAMNGR_DATATYPE_NUMBER)
	{
		double dValue1 = CString_To_double(m_strValue);
		double dValue2 = CString_To_double(p->m_strValue);
		
		if (dValue1 != dValue2)
		{
			return FALSE;
		}
	}
	else
	{
		if (m_strValue != p->m_strValue)
		{
			return FALSE;
		}
	}

	return TRUE;
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

//判断子对象是否strValueID == strValue的。有返回子对象。shaolei 2021-12-04
CDvmValue* CDvmData::HasValueEx_Child(const CString &strValueID, const CString &strValue)
{
	POS pos = GetHeadPosition();
	CDvmValue *pValue = NULL;
	CString strTemp;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)GetNext(pos);

		if (pValue->GetValueByID(strValueID, strTemp))
		{
			if (strTemp == strValue)
			{
				return pValue;
			}
		}
	}

	return NULL;
}

CDvmValue* CDvmData::HasValueHasStr_Child(const CString &strValueID, const CString &strValue)
{
	POS pos = GetHeadPosition();
	CDvmValue *pValue = NULL;
	CString strTemp;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)GetNext(pos);

		if (pValue->GetValueByID(strValueID, strTemp))
		{
			if (strTemp.Find(strValue) >= 0)
			{
				return pValue;
			}
		}
	}

	return NULL;
}

CDvmValue* CDvmData::HasValueHasNoStr_Child(const CString &strValueID, const CString &strValue)
{
	POS pos = GetHeadPosition();
	CDvmValue *pValue = NULL;
	CString strTemp;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)GetNext(pos);

		if (pValue->GetValueByID(strValueID, strTemp))
		{
			if (strTemp.Find(strValue) < 0)
			{
				return pValue;
			}
		}
	}

	return NULL;
}

BOOL CDvmData::GetValueByID(const CString &strValueID, CString &strValue, BOOL bUseHas)
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


	CDvmValue *pValue = FindValueByID(strValueID, bUseHas);

	if (pValue != NULL)
	{
		strValue = pValue->m_strValue;
		return TRUE;
	}

	return FALSE;
}

BOOL CDvmData::GetTime(CString &strTime)
{
	POS pos = GetHeadPosition();
	CDvmValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)GetNext(pos);

		if (pValue->m_strID.Right(2) == _T("$t"))
		{
			strTime = pValue->m_strValue;
			return TRUE;
		}
	}

	SYSTEMTIME tmSys;
	CTime tm((__int64)m_dTime);
	tm.GetAsSystemTime(tmSys);
	strTime.Format(_T("%d-%d-%d %d:%d:%d %d"), tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour
		, tmSys.wMinute, tmSys.wSecond, tmSys.wMilliseconds);

	return FALSE;
}

CString CDvmData::GetTime()
{
	CString strTime;
	GetTime(strTime);
	return strTime;
}

CDvmValue* CDvmData::FindValueByID(const CString &strValueID, BOOL bUseHas)
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

#ifdef _DVM_VALUE_USE_CHAR_
long CDvmData::ValueToLong()
{
	wchar_t *pEnd = NULL;
	return wcstol(m_strValue, &pEnd, 10);
}

#else
#endif

CString CDvmData::GetValueByID(const CString &strValueID, BOOL bUseHas)
{
	CString strValue;
	GetValueByID(strValueID, strValue, bUseHas);
	return strValue;
}

CString CDvmData::GetValueByID(BSTR bstrValueID, BOOL bUseHas)
{
	CString strValueID;
	strValueID = bstrValueID;
	return  GetValueByID(strValueID, bUseHas);
}

BOOL CDvmData::GetValueByID(const CString &strValueID, long &nValue)
{
	CString strValue;
	GetValueByID(strValueID, strValue);
	nValue = CString_To_long(strValue);

	return TRUE;
}

BOOL CDvmData::GetValueByID(const CString &strValueID, DWORD &nValue)
{
	CString strValue;
	GetValueByID(strValueID, strValue);
	nValue = CString_To_ulong(strValue);

	return TRUE;
}

BOOL CDvmData::GetValueByID(const CString &strValueID, float &fValue)
{
	CString strValue;
	GetValueByID(strValueID, strValue);
	fValue = (float)CString_To_double(strValue);

	return TRUE;
}

// BOOL CDvmData::GetValueByID(const CString &strValueID, BOOL &bValue)
// {
// 	CString strValue;
// 
// 	BOOL bRet = GetValueByID(strValueID, strValue);
// 	bValue = CString_To_long(strValue);
// 
// 	return bRet;
// }

BOOL CDvmData::GetValueByID(const CString &strValueID, SYSTEMTIME &tmValue)
{
	CString strValue;
	GetValueByID(strValueID, strValue);

	CStringToSystimeBuffer oBuffer;
	oBuffer.CString_To_SystemTime(strValue, tmValue);
	return TRUE;
}

BOOL CDvmData::GetValueByID(BSTR &bstrValueID, CString &strValue, BOOL bUseHas)
{
	CString strValueID;
	strValueID = bstrValueID;
	return GetValueByID(strValueID,strValue, bUseHas);
}

BOOL CDvmData::GetValueByID(BSTR &bstrValueID, long &nValue)
{
	CString strValueID;
	strValueID = bstrValueID;
	return GetValueByID(strValueID,nValue);
}

BOOL CDvmData::GetValueByID(BSTR &bstrValueID, float &fValue)
{
	CString strValueID;
	strValueID = bstrValueID;
	return GetValueByID(strValueID,fValue);
}

// BOOL CDvmData::GetValueByID(BSTR &bstrValueID, BOOL &bValue)
// {
// 	CString strValueID;
// 	strValueID = bstrValueID;
// 	return GetValueByID(strValueID,bValue);
// }

BOOL CDvmData::GetValueByID(BSTR &bstrValueID, SYSTEMTIME &tmValue)
{
	CString strValueID;
	strValueID = bstrValueID;
	return GetValueByID(strValueID,tmValue);
}

BOOL CDvmData::SetAttr(const CString &strAttrID, long &nValue)
{
	CString strValue;
	strValue.Format(_T("%d"),nValue);
	return SetAttr(strAttrID, strValue);
}

BOOL CDvmData::SetAttr(BSTR &bstrAttrID, const CString &strValue)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return SetAttr(strAttrID, strValue);
}

BOOL CDvmData::SetAttr(BSTR &bstrAttrID, long &nValue)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return SetAttr(strAttrID, nValue);
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

	if (strAttrID == CDataMngrXmlRWKeys::MaxKey())
	{
		m_strMax = strValue;
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::MinKey())
	{
		m_strMin = strValue;
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::StepKey())
	{
		m_strStep = strValue;
		return TRUE;
	}

	if (strAttrID == CDataMngrXmlRWKeys::UnitKey())
	{
		m_strUnit = strValue;
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

BOOL CDvmData::SetValue(const CString &strAttrID, const CString &strValue)
{
	CDvmValue *pValue = (CDvmValue*)FindValueByID(strAttrID, FALSE);

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
		return FALSE;
	}
}

BOOL CDvmData::SetValue(const CString &strAttrID, long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	
	return SetValue(strAttrID, strValue);
}

BOOL CDvmData::SetValue(const CString &strAttrID, DWORD nValue)
{
	CString strValue;
	strValue.Format(_T("%u"), nValue);

	return SetValue(strAttrID, strValue);
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

BOOL CDvmData::SetValue_Mms(const CString &strAttrID, const CString &strValue)
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

BOOL CDvmData::SetValue_Mms(const CString &strAttrID, long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);

	return SetValue_Mms(strAttrID, strValue);
}

BOOL CDvmData::SetValue_Mms(const CString &strAttrID, unsigned long nValue)
{
	CString strValue;
	strValue.Format(_T("%u"), nValue);

	return SetValue_Mms(strAttrID, strValue);
}

BOOL CDvmData::SetValue_Mms_Hex(const CString &strAttrID, unsigned long nValue)
{
	CString strValue;
	strValue.Format(_T("0x%08X"), nValue);

	return SetValue_Mms(strAttrID, strValue);
}

BOOL CDvmData::SetValue_Mms(const CString &strAttrID, float fValue, long nDecimal)
{
	CString strValue;
	strValue.Format(_T("%f"), fValue);

	return SetValue_Mms(strAttrID, strValue);
}

BOOL CDvmData::SetValue_Mms(const CString &strAttrID, double dValue, long nDecimal)
{
	CString strValue;
	strValue.Format(_T("%f"), dValue);

	return SetValue_Mms(strAttrID, strValue);
}



CDvmValue* CDvmData::AddValue(const CString &strAttrID, long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);

	return AddValue(strAttrID, strValue);
}

CDvmValue* CDvmData::AddValue(const CString &strAttrID, BOOL bValue)
{
	return AddValue(strAttrID,(long)bValue);
}

CDvmValue* CDvmData::AddValue(const CString &strAttrID, SYSTEMTIME tmValue)
{
	CString strValue;
	strValue.Format(_T("%d-%d-%d %d:%d:%d"), tmValue.wYear, tmValue.wMonth, tmValue.wDay
		, tmValue.wHour, tmValue.wMinute, tmValue.wSecond);

	return AddValue(strAttrID, strValue);
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

CDvmValue* CDvmData::AddValue2(const CString &strAttrID, const CString &strValue, const CString &strDataType)
{
	CDvmValue *pValue = AddValue(strAttrID, strValue);
	pValue->m_strDataType = strDataType;

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

void CDvmData::ResetDvmMap()
{
	m_dwReserved = 0;
	ResetDvmMapEx();
}

//不对m_dwReserved进行复位;
//对于主变，保护定值和跳闸矩阵，有好多定值名称上相差不大
//不对m_dwReserved复位，保证已经有映射的数据，在创建新的数据集映射时，不建立映射
void CDvmData::ResetDvmMapEx()
{
	m_pDvmMapObj = NULL;

	POS pos = GetHeadPosition();
	CDvmValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmValue *)GetNext(pos);
		p->ResetDvmMap();
	}
}

#endif

CDvmValue* CDvmData::AddValue(BSTR &bstrAttrID, const CString &strValue)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return AddValue(strAttrID,strValue);
}

CDvmValue* CDvmData::AddValue(BSTR &bstrAttrID, long nValue)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return AddValue(strAttrID,nValue);
}

CDvmValue* CDvmData::AddValue(BSTR &bstrAttrID, BOOL bValue)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return AddValue(strAttrID,bValue);
}

CDvmValue* CDvmData::AddValue(BSTR &bstrAttrID, SYSTEMTIME tmValue)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return AddValue(strAttrID,tmValue);
}

CDvmValue* CDvmData::AddValue(const CString &strName,const CString &strAttrID, long &nValue)
{
	CDvmValue* pValue = AddValue(strAttrID,nValue);
	if (pValue != NULL)
	{
		pValue->m_strName = strName;
	}

	return pValue;
}

CDvmValue* CDvmData::AddValue(const CString &strName, const CString &strAttrID, const CString &strDataType, const CString &strValue)
{
	CDvmValue* pValue = AddValue(strAttrID, strValue);

	if (pValue != NULL)
	{
		pValue->m_strName = strName;
		pValue->m_strDataType = strDataType;
	}

	return pValue;
}

CDvmValue* CDvmData::AddValue(const CString &strName, const CString &strAttrID, const CString &strValue)
{
	CDvmValue* pValue = AddValue(strAttrID,strValue);
	if (pValue != NULL)
	{
		pValue->m_strName = strName;
	}

	return pValue;
}

CDvmValue* CDvmData::AddValue(const CString &strName, const CString &strAttrID, BOOL bValue)
{
	CDvmValue* pValue = AddValue(strAttrID,bValue);
	if (pValue != NULL)
	{
		pValue->m_strName = strName;
	}

	return pValue;
}

CDvmValue* CDvmData::AddValue(const CString &strName, const CString &strAttrID, SYSTEMTIME tmValue)
{
	CDvmValue* pValue = AddValue(strAttrID,tmValue);
	if (pValue != NULL)
	{
		pValue->m_strName = strName;
	}

	return pValue;
}

CDvmValue* CDvmData::AddValue(const CString &strName,BSTR &bstrAttrID, long &nValue)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return AddValue(strName,strAttrID,nValue);
}

CDvmValue* CDvmData::AddValue(const CString &strName, BSTR &bstrAttrID, BOOL bValue)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return AddValue(strName,strAttrID,bValue);
}

CDvmValue* CDvmData::AddValue(const CString &strName, BSTR &bstrAttrID, SYSTEMTIME tmValue)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return AddValue(strName,strAttrID,tmValue);
}

CDvmValue* CDvmData::AddValue(const CString &strName, BSTR &bstrAttrID, const CString &strValue)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return AddValue(strName,strAttrID,strValue);
}

BOOL CDvmData::GetValueByID(const CString &strAttrID, long &nValue, CString &strName)
{
	CDvmValue *pValue = (CDvmValue *)FindByID(strAttrID);

	if (pValue == NULL)
	{
		return FALSE;
	}

	strName = pValue->m_strName;
	nValue = CString_To_long(pValue->m_strValue);

	return TRUE;
}

BOOL CDvmData::GetValueByID(BSTR &bstrAttrID, long &nValue, CString &strName)
{
	CString strAttrID;
	strAttrID = bstrAttrID;
	return GetValueByID(strAttrID,nValue,strName);
}

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


long CDvmBrcb::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
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

CDvmValue* CDvmData::FindByID_Has(const CString &strDataID)
{
	return dvm_FindByID_Has(this, strDataID);
// 	CDvmValue *pDvmValue = NULL;
// 	CDvmValue *pFind = NULL;
// 
// 	if (strDataID.Find(_T("Abs_")) >= 0 || strDataID.Find(_T("Rst_")) >= 0 || strDataID.Find(_T("Rel_")) >= 0)
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
// 		if (strDataID.Find(pDvmValue->m_strID) >= 0)
// 		{
// 			pFind = pDvmValue;
// 			return pFind;
// 		}
// 	}
// 
// 	return pFind;
}

CDvmValue* CDvmData::FindByID_MmsAttr(const CString &strAttrID)
{
	return dvm_FindByID_MmsAttr(this, strAttrID);
}

BOOL CDvmData::GetChildValueByID( const CString &strID, CString &strValue )
{
	CDvmValue *pValue = (CDvmValue *)FindByID(strID);

	if (pValue == NULL)
	{
		return FALSE;
	}

	strValue = pValue->m_strValue;
	return TRUE;
}

BOOL CDvmData::GetChildValueByID(const CString &strID, long &nValue)
{
	CString strValue;
	BOOL bRet = GetChildValueByID(strID, strValue);

	if (!bRet)
	{
		return bRet;
	}

	nValue = CString_To_long(strValue);
	return TRUE;
}

BOOL CDvmData::GetChildValueByID(const CString &strID, double &dValue)
{
	CString strValue;
	BOOL bRet = GetChildValueByID(strID, strValue);

	if (!bRet)
	{
		return bRet;
	}

	dValue = CString_To_double(strValue);
	return TRUE;
}


BOOL CDvmData::UpdateChildValue(CDvmData *pSrcData, BOOL bIsNew)
{
	BOOL bRet = TRUE;
	POS pos = pSrcData->GetHeadPosition();
	CDvmValue *pSrcValue = NULL;
	CDvmValue *pDstValue = NULL;
	CString strSrcID;

	while (pos != NULL)
	{
		pSrcValue = (CDvmValue *)pSrcData->GetNext(pos);
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
			pDstValue->m_strValue = pSrcValue->m_strValue;
			bRet = pDstValue->UpdateChildValue(pSrcValue, bIsNew);
		}	
	}

	return bRet;
}

BOOL CDvmData::UpdateOwn(CBaseObject* pDest)
{
	if (GetClassID() != pDest->GetClassID())
	{
		return FALSE;
	}

	CDvmData *pDesDvmData = (CDvmData*)pDest;
	pDesDvmData->m_strValue = m_strValue;
	pDesDvmData->m_strFormat = m_strFormat;	//20240717 huangliang
	return TRUE;
}

void CDvmData::ResetData()
{
	m_strValue = _T("0");
}


//2021-10-13 lijunqing
CString CDvmData::GetIDPath_Root_Dataset(const CString &strPathSp)
{
	CExBaseObject *pDataset = (CExBaseObject*)GetParent();
	CString strID;
	UINT nClassID = pDataset->GetClassID();

	if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		strID = m_strID;
	}
	else
	{
		CExBaseList oList;
		GetAllAncestorEqClassID(&oList, DVMCLASSID_CDVMDATASETGROUP);
		POS pos = oList.GetHeadPosition();
		CExBaseObject *p = NULL;
		oList.GetNext(pos);

		while (pos != NULL)
		{
			p = oList.GetNext(pos);
			strID.AppendFormat(_T("%s%s"), p->m_strID.GetString(), strPathSp.GetString());
		}

		strID += m_strID;
		oList.RemoveAll();
	}

	return strID;
}

void CDvmData::InitByValues(CExBaseList *pValues) //2021-10-22  lijunqing
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

//shaolei 20220518
void CDvmData::InitDataTypeByGsData(const CString &strDataType)
{
	if (strDataType == _T("BOOLEAN"))
	{
		m_strDataType = _T("单点");
	}
	else if (strDataType == _T("Dbpos"))
	{
		m_strDataType = _T("双点");
	}
	else if (strDataType == _T("Timestamp"))
	{
		m_strDataType = _T("时间");
	}
	else if (strDataType == _T("Quality"))
	{
		m_strDataType = _T("品质");
	}
	else if (strDataType == _T("FLOAT32"))
	{
		m_strDataType = _T("float");
	}
	else if (strDataType == _T("VisString64"))
	{
		m_strDataType = _T("位串");//20220613  zhouhj  
	}
	else if (strDataType == _T("Struct"))
	{
		m_strDataType = _T("STRUCT");
	}
	else if (strDataType == _T("INT32"))
	{
		m_strDataType = _T("整型");
	}
	else if (strDataType == _T("INT32U"))
	{
		m_strDataType = strDataType;
	}
	else
	{
		m_strDataType = _T("整型");
	}
}


CDvmValue* CDvmData::FindDataObjValueByID_Has(const CString &strIDPath)
{
	CDvmValue *pDataObjVal = NULL;
	POS pos = GetHeadPosition();
	CDvmValue *pFind = NULL;
	long nLen1, nLen2;

	while (pos != NULL)
	{
		pDataObjVal = (CDvmValue *)GetNext(pos);
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


void CDvmData::InitValueByData(CDvmData *pData, BOOL bSetMinMax)
{
	m_strValue = pData->m_strValue;

	if (bSetMinMax)
	{
		m_strMin = pData->m_strMin;
		m_strMax = pData->m_strMax;
	}

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


CExBaseObject* CDvmData::FindValueObject(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);

		if (g_oXDvmValueKeyMngr.IsValueID(p->m_strID))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL CDvmData::CmpDataType(CDvmData *pDataSrc)
{
	if (GetCount() == 0 && pDataSrc->GetCount() == 0)
	{
		return m_strDataType == pDataSrc->m_strDataType;
	}

	if (GetCount() > 0 && pDataSrc->GetCount() > 0)
	{
		CDvmValue *pFind = (CDvmValue*)FindValueObject(pDataSrc);
		CDvmValue *pFind2 = (CDvmValue*)FindValueObject(this);

		if (pFind == NULL || pFind2 == NULL)
		{
			return FALSE;
		}
		else
		{
			return pFind2->m_strDataType == pFind->m_strDataType;
		}
	}

	if (GetCount() > 0)
	{
		CDvmValue *pFind2 = (CDvmValue*)FindValueObject(this);

		if (pFind2 == NULL)
		{
			return FALSE;
		}
		else
		{
			return pFind2->m_strDataType == m_strDataType;
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


BOOL CDvmData::CmpDataType(const CString &strDataType)
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

//返回除$t  $q之外的第一个pDvmData子对象
CDvmValue* CDvmData::GetDataValue()
{
	if (GetCount() == 0)
	{
		return NULL;
	}

	POS pos = GetHeadPosition();
	CDvmValue *p = NULL;
	CString strRight;

	while (pos != NULL)
	{
		p = (CDvmValue *)GetNext(pos);
		strRight = p->m_strID.Right(2);

		if (strRight == "$t" || strRight == "$q")
		{
			continue;
		}

		return p;
	}

	return (CDvmValue*)GetHead();
}

BOOL dvm_CmpDvmDataValue(const CString &strDataType, const CString &strValue1, const CString &strValue2)
{
	if ((strDataType.CompareNoCase(_T("FLOAT")) == 0) || (strDataType.CompareNoCase(_T("STRUCT")) == 0))
	{
		double dValue1 = CString_To_double(strValue1);
		double dValue2 = CString_To_double(strValue2);
		return math_IsEqual(dValue1, dValue2);
	}
	else
	{
		return (strValue2 == strValue1);
	}
}

BOOL dvm_CmpDvmDataValues(CExBaseList *pValues1, CExBaseList *pValues2)
{
	POS pos = pValues1->GetHeadPosition();
	CDvmValue *p = NULL;
	CDvmValue *pFind = NULL;
	BOOL bSame = TRUE;

	while (pos != NULL)
	{
		p = (CDvmValue *)pValues1->GetNext(pos);
		pFind = (CDvmValue *)pValues2->FindByID(p->m_strID);

		if (pFind == NULL)
		{
			bSame = FALSE;
			break;
		}

		bSame = dvm_CmpDvmDataValue(p, pFind);

		if (!bSame)
		{
			break;
		}
	}

	return bSame;
}


BOOL dvm_CmpDvmData(CDvmData *pData1, CDvmData *pData2)
{
	if (pData1->m_strDataType != pData2->m_strDataType)
	{
		return FALSE;
	}

	if (pData1->m_strDataType.CompareNoCase(_T("STRUCT")) == 0)
	{
		if (pData1->GetCount() > 0)
		{
		        return dvm_CmpDvmDataValues(pData1, pData2);
   	        }
        	else
        	{
	        	return dvm_CmpDvmDataValue(pData1->m_strDataType, pData1->m_strValue, pData2->m_strValue);
	        }
	}
	else
	{
		return dvm_CmpDvmDataValue(pData1->m_strDataType, pData1->m_strValue, pData2->m_strValue);
	}
}

BOOL dvm_CmpDvmDataValue(CDvmValue *pValue1, CDvmValue *pValue2)
{
	if (pValue1->m_strDataType.CompareNoCase(_T("STRUCT")) == 0)
	{
		return dvm_CmpDvmDataValues(pValue1, pValue2);
	}
	else
	{
		return dvm_CmpDvmDataValue(pValue1->m_strDataType, pValue1->m_strValue, pValue2->m_strValue);
	}
}


BOOL XDS_InStringDataPath(const CString &strText)
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
