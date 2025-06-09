//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//BkmkDataProcess.cpp  CBkmkDataProcess


#include "stdafx.h"
#include "BkmkDataProcess.h"
#include "../../../../../Module/API/MathApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBkmkDataProcess::CBkmkDataProcess()
{
	//初始化属性
	m_dValue = 0;
	m_dwOptr = BKMKDATA_OPTR_NONE;

	//初始化成员变量
}

CBkmkDataProcess::~CBkmkDataProcess()
{
}

long CBkmkDataProcess::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strTextTrueKey, oNode, m_strTextTrue);
	xml_GetAttibuteValue(pXmlKeys->m_strTextFalseKey, oNode, m_strTextFalse);
	xml_GetAttibuteValue(pXmlKeys->m_strTextAppendKey, oNode, m_strTextAppend);

	return 0;
}

long CBkmkDataProcess::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strTextTrueKey, oElement, m_strTextTrue);
	xml_SetAttributeValue(pXmlKeys->m_strTextFalseKey, oElement, m_strTextFalse);
	xml_SetAttributeValue(pXmlKeys->m_strTextAppendKey, oElement, m_strTextAppend);

	return 0;
}

long CBkmkDataProcess::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strTextTrue);
		BinarySerializeCalLen(oBinaryBuffer, m_strTextFalse);
		BinarySerializeCalLen(oBinaryBuffer, m_strTextAppend);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strOptr);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strTextTrue);
		BinarySerializeRead(oBinaryBuffer, m_strTextFalse);
		BinarySerializeRead(oBinaryBuffer, m_strTextAppend);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strOptr);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strTextTrue);
		BinarySerializeWrite(oBinaryBuffer, m_strTextFalse);
		BinarySerializeWrite(oBinaryBuffer, m_strTextAppend);
	}
	return 0;
}

BOOL CBkmkDataProcess::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CBkmkDataProcess *p = (CBkmkDataProcess*)pObj;

	if(m_strOptr != p->m_strOptr)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strTextTrue != p->m_strTextTrue)
	{
		return FALSE;
	}

	if(m_strTextFalse != p->m_strTextFalse)
	{
		return FALSE;
	}

	if(m_strTextAppend != p->m_strTextAppend)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CBkmkDataProcess::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CBkmkDataProcess *p = (CBkmkDataProcess*)pDest;

	p->m_strOptr = m_strOptr;
	p->m_strValue = m_strValue;
	p->m_strTextTrue = m_strTextTrue;
	p->m_strTextFalse = m_strTextFalse;
	p->m_strTextAppend = m_strTextAppend;
	return TRUE;
}

CBaseObject* CBkmkDataProcess::Clone()
{
	CBkmkDataProcess *p = new CBkmkDataProcess();
	Copy(p);
	return p;
}

CExBaseObject* CBkmkDataProcess::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CBkmkDataProcess::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}


void CBkmkDataProcess::InitAfterRead()
{
	m_strOptr.MakeLower();

	if (m_strOptr == _T(">"))
	{
		m_dwOptr = BKMKDATA_OPTR_GT;
	}
	else if (m_strOptr == _T(">="))
	{
		m_dwOptr = BKMKDATA_OPTR_GTE;
	}
	else if (m_strOptr == _T("<"))
	{
		m_dwOptr = BKMKDATA_OPTR_LT;
	}
	else if (m_strOptr == _T("<="))
	{
		m_dwOptr = BKMKDATA_OPTR_LTE;
	}
	else if (m_strOptr == _T("=="))
	{
		m_dwOptr = BKMKDATA_OPTR_E;
	}
	else if (m_strOptr == _T("*"))
	{
		m_dwOptr = BKMKDATA_OPTR_MUL;
	}
	else if (m_strOptr == _T("/"))
	{
		m_dwOptr = BKMKDATA_OPTR_DIV;
	}
	else if (m_strOptr == _T("+"))
	{
		m_dwOptr = BKMKDATA_OPTR_ADD;
	}
	else if (m_strOptr == _T("-"))
	{
		m_dwOptr = BKMKDATA_OPTR_SUB;
	}
	else
	{
		m_dwOptr = BKMKDATA_OPTR_NONE;
	}

	if (m_strValue.GetLength() > 0)
	{
		m_dValue = CString_To_double(m_strValue);
	}
}



BOOL CBkmkDataProcess::ProcessData(CString &strValue, CString &strAdd, long nPrecision)
{
// 	CString strPrev = strValue;
	BOOL bTrue = FALSE;

	switch (m_dwOptr)
	{
	case BKMKDATA_OPTR_NONE://  0
		break;

	case BKMKDATA_OPTR_GT://    1
		bTrue = ProcessData_GT(strValue);
		break;

	case BKMKDATA_OPTR_LT://    2
		bTrue = ProcessData_GT(strValue);
		break;

	case BKMKDATA_OPTR_GTE://   3
		bTrue = ProcessData_GT(strValue);
		break;

	case BKMKDATA_OPTR_LTE://   4
		bTrue = ProcessData_LTE(strValue);
		break;

	case BKMKDATA_OPTR_E://     5
		bTrue = ProcessData_E(strValue);
		break;

	case BKMKDATA_OPTR_ADD://   6
		bTrue = ProcessData_ADD(strValue);
		break;

	case BKMKDATA_OPTR_SUB://   7
		bTrue = ProcessData_SUB(strValue);
		break;

	case BKMKDATA_OPTR_DIV://   8
		bTrue = ProcessData_DIV(strValue);
		break;

	case BKMKDATA_OPTR_MUL://   9
		bTrue = ProcessData_MUL(strValue);
		break;

	case BKMKDATA_OPTR_VALREVISED://   10
		bTrue = ProcessData_ValRevised(strValue, nPrecision);
		break;

	default:
		break;
	}

	if (m_strTextAppend.GetLength() > 0)
	{
		strAdd = m_strTextAppend;
	}

	return bTrue;
}


BOOL CBkmkDataProcess::ProcessData_GT(CString &strValue)
{
	double dValue = CString_To_double(strValue);

	if (dValue > m_dValue)
	{
		if (m_strTextTrue.GetLength() > 0)
		{
			strValue = m_strTextTrue;
		}
		
	}
	else
	{
		if (m_strTextFalse.GetLength() > 0)
		{
			strValue = m_strTextFalse;
		}
	}

	return TRUE;
}

BOOL CBkmkDataProcess::ProcessData_LT(CString &strValue)
{
	double dValue = CString_To_double(strValue);

	if (dValue < m_dValue)
	{
		if (m_strTextTrue.GetLength() > 0)
		{
			strValue = m_strTextTrue;
		}

	}
	else
	{
		if (m_strTextFalse.GetLength() > 0)
		{
			strValue = m_strTextFalse;
		}
	}

	return TRUE;
}

BOOL CBkmkDataProcess::ProcessData_GTE(CString &strValue)
{
	double dValue = CString_To_double(strValue);

	if (dValue >= m_dValue)
	{
		if (m_strTextTrue.GetLength() > 0)
		{
			strValue = m_strTextTrue;
		}

	}
	else
	{
		if (m_strTextFalse.GetLength() > 0)
		{
			strValue = m_strTextFalse;
		}
	}

	return TRUE;
}

BOOL CBkmkDataProcess::ProcessData_LTE(CString &strValue)
{
	double dValue = CString_To_double(strValue);

	if (dValue <= m_dValue)
	{
		if (m_strTextTrue.GetLength() > 0)
		{
			strValue = m_strTextTrue;
		}

	}
	else
	{
		if (m_strTextFalse.GetLength() > 0)
		{
			strValue = m_strTextFalse;
		}
	}

	return TRUE;
}

BOOL CBkmkDataProcess::ProcessData_E(CString &strValue)
{
	double dValue = CString_To_double(strValue);

	if (dValue == m_dValue)
	{
		if (m_strTextTrue.GetLength() > 0)
		{
			strValue = m_strTextTrue;
		}

	}
	else
	{
		if (m_strTextFalse.GetLength() > 0)
		{
			strValue = m_strTextFalse;
		}
	}

	return TRUE;
}

BOOL CBkmkDataProcess::ProcessData_ADD(CString &strValue)
{
	double dValue = CString_To_double(strValue);

	dValue = dValue + m_dValue;
	strValue.Format(_T("%f"), dValue);

	return TRUE;
}

BOOL CBkmkDataProcess::ProcessData_SUB(CString &strValue)
{
	double dValue = CString_To_double(strValue);

	dValue = dValue - m_dValue;
	strValue.Format(_T("%f"), dValue);

	return TRUE;
}

BOOL CBkmkDataProcess::ProcessData_DIV(CString &strValue)
{
	double dValue = CString_To_double(strValue);

	dValue = dValue / m_dValue;
	strValue.Format(_T("%f"), dValue);

	return TRUE;
}

BOOL CBkmkDataProcess::ProcessData_MUL(CString &strValue)
{
	double dValue = CString_To_double(strValue);

	dValue = dValue * m_dValue;
	strValue.Format(_T("%f"), dValue);

	return TRUE;
}


BOOL CBkmkDataProcess::ProcessData_ValRevised(CString &strValue, long nPrecision)
{
	double dValue = CString_To_double(strValue);

	dValue = math_ValueRevised(dValue, nPrecision);// * m_dValue;
	strValue.Format(_T("%f"), dValue);

	return TRUE;
}
