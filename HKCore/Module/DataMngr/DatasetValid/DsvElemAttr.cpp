//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvElemAttr.cpp  CDsvElemAttr


#include "stdafx.h"
#include "DsvElemAttr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const CString CDsvElemAttr::g_astrAttrOptrID[DSV_OPTR_COUNT] = 
{
	_T("=="), //等于==
	_T("<"), //小于<
	_T("<="), //小于等于<=
	_T(">"), //大于>
	_T(">="), //大于等于>=
	_T("!="), //不等于!=
	_T("[]"), //包含[]
	_T("![]"), //不包含![]
	_T("<>"), //范围<>
	_T("<=>"), //范围带边界<=>
	_T("++") //数据变量赋值
};

const CString CDsvElemAttr::g_astrAttrDataTypeID[DSV_ATTR_TYPE_COUNT] = 
{
	_T("int"),
	_T("float"),
	_T("string"),
	_T("date")
};

CDsvElemAttr::CDsvElemAttr()
{
	//初始化属性
	m_strName = _T("value");
	m_strID = m_strName;
	m_strOptr = g_astrAttrOptrID[0];
	m_strDataType = g_astrAttrDataTypeID[0];
	m_dwOptr = DSV_OPTR_EQ;
	m_dwDataType = DSV_ATTR_TYPE_INT;
	m_strValue = _T("0");

	//初始化成员变量
}

CDsvElemAttr::~CDsvElemAttr()
{
}

void CDsvElemAttr::InitOptrString()
{
	ASSERT (0<= m_dwOptr && m_dwOptr <= DSV_OPTR_EQRANGE);

	if (0<= m_dwOptr && m_dwOptr <= DSV_OPTR_EQRANGE)
	{
		m_strOptr = g_astrAttrOptrID[m_dwOptr];
	}
	else
	{
		m_strOptr = g_astrAttrOptrID[0];
	}
}

void CDsvElemAttr::InitOptrDWORD()
{
	long nIndex = 0;
	m_dwOptr = DSV_OPTR_EQ;

	for (nIndex=0; nIndex<= DSV_OPTR_EQRANGE; nIndex++)
	{
		if (m_strOptr == g_astrAttrOptrID[nIndex])
		{
			m_dwOptr = nIndex;
			break;
		}
	}
}

void CDsvElemAttr::InitDataTypeString()
{
	ASSERT (0<= m_dwDataType && m_dwDataType <= DSV_ATTR_TYPE_COUNT);

	if (0<= m_dwDataType && m_dwDataType <= DSV_ATTR_TYPE_COUNT)
	{
		m_strDataType = g_astrAttrDataTypeID[m_dwDataType];
	}
	else
	{
		m_strDataType = g_astrAttrDataTypeID[0];
	}
}

void CDsvElemAttr::InitDataTypeDWORD()
{
	long nIndex = 0;
	m_dwDataType = DSV_ATTR_TYPE_STRING;

	for (nIndex=0; nIndex< DSV_ATTR_TYPE_COUNT; nIndex++)
	{
		if (m_strDataType == g_astrAttrDataTypeID[nIndex])
		{
			m_dwDataType = nIndex;
			break;
		}
	}
}

void CDsvElemAttr::SetOptr(const CString &strOptr)
{
	m_strOptr = strOptr;
	InitOptrDWORD();
}

void CDsvElemAttr::SetDataType(const CString &strDataType)
{
	m_strDataType = strDataType;
	InitDataTypeDWORD();
}

long CDsvElemAttr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strValue2Key, oNode, m_strValue2);
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strVariableKey, oNode, m_strVariable);

	InitOptrDWORD();
	InitDataTypeDWORD();

	return 0;
}

long CDsvElemAttr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strValue2Key, oElement, m_strValue2);
	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strVariableKey, oElement, m_strVariable);

	return 0;
}

long CDsvElemAttr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_dwDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_dwOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue2);
		BinarySerializeCalLen(oBinaryBuffer, m_strVariable);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_dwDataType);
		BinarySerializeRead(oBinaryBuffer, m_dwOptr);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strValue2);

		if (oBinaryBuffer.m_dwVersionFind >= DATAMNGR_VERSION_1_2)
		{
			BinarySerializeRead(oBinaryBuffer, m_strVariable);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_dwDataType);
		BinarySerializeWrite(oBinaryBuffer, m_dwOptr);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strValue2);
		BinarySerializeWrite(oBinaryBuffer, m_strVariable);
	}

	return 0;
}

void CDsvElemAttr::InitAfterRead()
{
}

BOOL CDsvElemAttr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDsvElemAttr *p = (CDsvElemAttr*)pObj;

	if(m_strOptr != p->m_strOptr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDsvElemAttr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDsvElemAttr *p = (CDsvElemAttr*)pDest;

	p->m_strOptr = m_strOptr;
	p->m_strDataType = m_strDataType;
	p->m_strValue = m_strValue;
	p->m_strValue2 = m_strValue2;
	p->m_strVariable = m_strVariable;

	p->InitOptrDWORD();
	p->InitDataTypeDWORD();

	return TRUE;
}

CBaseObject* CDsvElemAttr::Clone()
{
	CDsvElemAttr *p = new CDsvElemAttr();
	Copy(p);
	return p;
}


//////////////////////////////////////////////////////////////////////////

BOOL CDsvElemAttr::ValidateData(CDvmData *pDvmData)
{
	CString strValue;
	
	if (!pDvmData->GetValueByID(m_strID, strValue))
	{
		return FALSE;
	}

	BOOL bTrue = FALSE;

	switch (m_dwDataType)
	{
	case DSV_ATTR_TYPE_INT:
		bTrue = Validate_Int(strValue);
		break;

	case DSV_ATTR_TYPE_FLOAT:
		bTrue = Validate_Float(strValue);
		break;

	case DSV_ATTR_TYPE_STRING:
		bTrue = Validate_String(strValue);
		break;

	case DSV_ATTR_TYPE_DATE:
		bTrue = Validate_Date(strValue);
		break;

	default:
		bTrue = Validate_Int(strValue);
		break;

	}

	return bTrue;
}

BOOL CDsvElemAttr::SetValuesByData(CDvmData *pDvmData, CValues *pRptValues)
{
	if (pRptValues == NULL)
	{
		return FALSE;
	}

	CString strValue;

	if (!pDvmData->GetValueByID(m_strID, strValue))
	{
		return FALSE;
	}

	if (m_strVariable.GetLength() > 0)
	{
		pRptValues->SetValue(m_strVariable, strValue);
	}

	return TRUE;
}

BOOL CDsvElemAttr::Validate_Int(const CString &strValue)
{
#ifdef _UNICODE
	long nValue = _wtoi(strValue);
	long nValue1 = _wtoi(m_strValue);
	long nValue2 = _wtoi(m_strValue2);
#else
//	long nValue = atoi(strValue);
//	long nValue1 = atoi(m_strValue);
//	long nValue2 = atoi(m_strValue2);
	long nValue = CString_To_long(strValue);
	long nValue1 = CString_To_long(m_strValue);
	long nValue2 = CString_To_long(m_strValue2);
#endif

	BOOL bTrue = FALSE;

	switch(m_dwOptr)
	{
		//等于==
	case DSV_OPTR_EQ:    //0
		bTrue = (nValue == nValue1);
		break;

		//小于<
	case DSV_OPTR_LT:    //1
		bTrue = (nValue < nValue1);
		break;

		//小于等于<=
	case DSV_OPTR_LTEQ:    //2
		bTrue = (nValue <= nValue1);
		break;

		//大于>
	case DSV_OPTR_GT:    //3
		bTrue = (nValue > nValue1);
		break;

		//大于等于>=
	case DSV_OPTR_GTEQ:    //4
		bTrue = (nValue >= nValue1);
		break;

		//不等于!=
	case DSV_OPTR_NOTEQ:    //5
		bTrue = (nValue != nValue1);
		break;

		//包含[]
	case DSV_OPTR_HAS:    //6
		bTrue = (nValue == nValue1);
		break;

		//不包含![]
	case DSV_OPTR_HASNOT:    //7
		bTrue = (nValue != nValue1);
		break;

		//范围<>
	case DSV_OPTR_INRANGE:    //8
		bTrue = ((nValue1 < nValue) && (nValue < nValue2));
		break;

		//范围带边界<=>
	case DSV_OPTR_EQRANGE:    //9
		bTrue = ((nValue1 <= nValue) && (nValue <= nValue2));
		break;

		//数据变量赋值
	case DSV_OPTR_GETVALUE:    //10
		bTrue = TRUE;
		break;

	default:
		bTrue = (nValue == nValue1);
		break;

	}

	return bTrue;
}

BOOL CDsvElemAttr::Validate_Float(const CString &strValue)
{
#ifdef _UNICODE
	double fValue = _wtof(strValue);
	double fValue1 = _wtof(m_strValue);
	double fValue2 = _wtof(m_strValue2);
#else
//	double fValue = atof(strValue);
//	double fValue1 = atof(m_strValue);
//	double fValue2 = atof(m_strValue2);
	double fValue = CString_To_double(strValue);
	double fValue1 = CString_To_double(m_strValue);
	double fValue2 = CString_To_double(m_strValue2);
#endif

	BOOL bTrue = FALSE;

	switch(m_dwOptr)
	{
		//等于==
	case DSV_OPTR_EQ:    //0
		bTrue = (fValue == fValue1);
		break;

		//小于<
	case DSV_OPTR_LT:    //1
		bTrue = (fValue < fValue1);
		break;

		//小于等于<=
	case DSV_OPTR_LTEQ:    //2
		bTrue = (fValue <= fValue1);
		break;

		//大于>
	case DSV_OPTR_GT:    //3
		bTrue = (fValue > fValue1);
		break;

		//大于等于>=
	case DSV_OPTR_GTEQ:    //4
		bTrue = (fValue >= fValue1);
		break;

		//不等于!=
	case DSV_OPTR_NOTEQ:    //5
		bTrue = (fValue != fValue1);
		break;

		//包含[]
	case DSV_OPTR_HAS:    //6
		bTrue = (fValue == fValue1);
		break;

		//不包含![]
	case DSV_OPTR_HASNOT:    //7
		bTrue = (fValue != fValue1);
		break;

		//范围<>
	case DSV_OPTR_INRANGE:    //8
		bTrue = ((fValue1 < fValue) && (fValue < fValue2));
		break;

		//范围带边界<=>
	case DSV_OPTR_EQRANGE:    //9
		bTrue = ((fValue1 <= fValue) && (fValue <= fValue2));
		break;

		//数据变量赋值
	case DSV_OPTR_GETVALUE:    //10
		bTrue = TRUE;
		break;

	default:
		bTrue = (fValue == fValue1);
		break;

	}

	return bTrue;
}

BOOL CDsvElemAttr::Validate_String(const CString &strValue)
{
	BOOL bTrue = FALSE;

	switch(m_dwOptr)
	{
		//等于==
	case DSV_OPTR_EQ:    //0
		bTrue = (strValue == m_strValue);
		break;

		//小于<
	case DSV_OPTR_LT:    //1
		bTrue = (strValue < m_strValue);
		break;

		//小于等于<=
	case DSV_OPTR_LTEQ:    //2
		bTrue = (strValue <= m_strValue);
		break;

		//大于>
	case DSV_OPTR_GT:    //3
		bTrue = (strValue > m_strValue);
		break;

		//大于等于>=
	case DSV_OPTR_GTEQ:    //4
		bTrue = (strValue >= m_strValue);
		break;

		//不等于!=
	case DSV_OPTR_NOTEQ:    //5
		bTrue = (strValue != m_strValue);
		break;

		//包含[]
	case DSV_OPTR_HAS:    //6
		bTrue = (strValue.Find(m_strValue) >= 0);
		break;

		//不包含![]
	case DSV_OPTR_HASNOT:    //7
		bTrue = (strValue.Find(m_strValue) < 0);
		break;

		//范围<>
	case DSV_OPTR_INRANGE:    //8
		bTrue = FALSE;
		break;

		//范围带边界<=>
	case DSV_OPTR_EQRANGE:    //9
		bTrue = FALSE;
		break;

		//数据变量赋值
	case DSV_OPTR_GETVALUE:    //10
		bTrue = TRUE;
		break;

	default:
		bTrue = (strValue == m_strValue);
		break;

	}

	return bTrue;
}

BOOL CDsvElemAttr::Validate_Date(const CString &strValue)
{
	return TRUE;
}

