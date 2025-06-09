//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprRange.cpp  CXExprRange


#include "stdafx.h"
#include "XExprRange.h"

CXExprRange::CXExprRange()
{
	//初始化属性

	//初始化成员变量
	m_pValueMin = NULL;
	m_pValueMax = NULL;
	m_pValue = NULL;
	m_pValueRslt = NULL;
}

CXExprRange::~CXExprRange()
{
}

long CXExprRange::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strMinOptrKey, oNode, m_strMinOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxOptrKey, oNode, m_strMaxOptr);

	return 0;
}

long CXExprRange::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strMinOptrKey, oElement, m_strMinOptr);
	xml_SetAttributeValue(pXmlKeys->m_strMaxOptrKey, oElement, m_strMaxOptr);
	return 0;
}

long CXExprRange::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXExprBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMinOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_strMaxOptr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMinOptr);
		BinarySerializeRead(oBinaryBuffer, m_strMaxOptr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMinOptr);
		BinarySerializeWrite(oBinaryBuffer, m_strMaxOptr);
	}
	return 0;
}

void CXExprRange::InitAfterRead()
{
	CXExprBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRVALUE)
		{
			m_pValue = (CXExprValue*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEMAX)
		{
			m_pValueMax = (CXExprValueMax*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
		{
			m_pValueRslt = (CXExprValueRslt*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEMIN)
		{
			m_pValueMin = (CXExprValueMin*)p;
		}
	}

	//单独新建，全部为空
	if (m_pValueMin == NULL)
	{
		m_pValueMin = (CXExprValueMin *)AddNewChild(new CXExprValueMin());
	}

	if (m_pValue == NULL)
	{
		m_pValue = (CXExprValue *)AddNewChild(new CXExprValue());
	}

	if (m_pValueMax == NULL)
	{
		m_pValueMax = (CXExprValueMax *)AddNewChild(new CXExprValueMax());
	}
}

BOOL CXExprRange::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXExprBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXExprRange *p = (CXExprRange*)pObj;

	if(m_strMinOptr != p->m_strMinOptr)
	{
		return FALSE;
	}

	if(m_strMaxOptr != p->m_strMaxOptr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprRange::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase::CopyOwn(pDest);
	CXExprRange *p = (CXExprRange*)pDest;
	p->m_strMinOptr = m_strMinOptr;
	p->m_strMaxOptr = m_strMaxOptr;

	return TRUE;
}

CBaseObject* CXExprRange::Clone()
{
	CXExprRange *p = new CXExprRange();
	Copy(p);
	return p;
}

CBaseObject* CXExprRange::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprRange *p = new CXExprRange();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprRange::CanPaste(UINT nClassID)
{
	if (nClassID == XEXPRCLASSID_CXEXPRVALUE)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEMAX)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEMIN)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXExprRange::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	if (strClassID == CXExprXmlRWKeys::CXExprValueMinKey())
	{
		m_pValueMin = new CXExprValueMin();
		return m_pValueMin;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueMaxKey())
	{
		m_pValueMax = new CXExprValueMax();
		return m_pValueMax;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueRsltKey())
	{
		m_pValueRslt = new CXExprValueRslt();
		return m_pValueRslt;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueKey())
	{
		m_pValue = new CXExprValue();
		return m_pValue;
	}

	return pNew;
}

CExBaseObject* CXExprRange::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEMIN)
	{
		m_pValueMin = new CXExprValueMin();
		return m_pValueMin;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEMAX)
	{
		m_pValueMax = new CXExprValueMax();
		return m_pValueMax;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
	{
		m_pValueRslt = new CXExprValueRslt();
		return m_pValueRslt;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE)
	{
		m_pValue = new CXExprValue();
		return m_pValue;
	}

	return pNew;
}

// long CXExprRange::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	m_pValueMin->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueMinKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValue->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueMax->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueMaxKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueRslt->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueRsltKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 
// 	return 0;
// }

long CXExprRange::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	double dMin = 0;
	double dMax = 0;
	double dValue = 0;
	m_nResult = 0;
	CString strMin, strMax, strValue;

	if (! m_pValueMin->Calc(pExprParent, pCalInterface, dMin, strMin))
	{
		return 0;
	}

	if (! m_pValue->Calc(pExprParent, pCalInterface, dValue, strValue))
	{
		return 0;
	}

	if (! m_pValueMax->Calc(pExprParent, pCalInterface, dMax, strMax))
	{
		return 0;
	}

	BOOL bRstMin = FALSE;
	BOOL bRstMax = FALSE;

	if (m_strMinOptr == _T(">="))
	{
		bRstMin = (dMin <= dValue);
	}
	else if (m_strMinOptr == _T(">"))
	{
		bRstMin = (dMin < dValue);
	}

	if (m_strMaxOptr == _T("<="))
	{
		bRstMax = (dValue <= dMax);
	}
	else if (m_strMaxOptr == _T("<"))
	{
		bRstMax = (dValue < dMax);
	}

	m_nResult = bRstMin && bRstMax;
	//m_nResult = (dMin <= dValue) && (dValue <= dMax);

	if (strValue == _T("未动作"))
	{
		m_nResult = 0;
	}

	//计算结束后，将结果绑定回对应的参数
	CXExprValueRslt* pRslt = GetExprValueRslt();
	pRslt->m_strValue.Format(_T("%d"), m_nResult);
	pRslt->ExprRsltBind(pExprParent, pCalInterface);

	return m_nResult;
}

void CXExprRange::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
}

void CXExprRange::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (m_pValueMin != NULL)
	{
		m_pValueMin->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueMax != NULL)
	{
		m_pValueMax->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValue != NULL)
	{
		m_pValue->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}
}

BOOL CXExprRange::GetValueName(const CString &strID, CString &strName)
{
	if (m_pValueMin != NULL)
	{
		if (m_pValueMin->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValueMax != NULL)
	{
		if (m_pValueMax->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValue != NULL)
	{
		if (m_pValue->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValueRslt != NULL)
	{
		if (m_pValueRslt->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	return FALSE;
}

CXExprValueMin* CXExprRange::GetExprValueMin()
{
	if (m_pValueMin == NULL)
	{
		m_pValueMin = new CXExprValueMin();
		AddNewChild(m_pValueMin);
	}

	return m_pValueMin;
}

CXExprValueMax* CXExprRange::GetExprValueMax()
{
	if (m_pValueMax == NULL)
	{
		m_pValueMax = new CXExprValueMax();
		AddNewChild(m_pValueMax);
	}

	return m_pValueMax;
}

CXExprValue* CXExprRange::GetExprValue()
{
	if (m_pValue == NULL)
	{
		m_pValue = new CXExprValue();
		AddNewChild(m_pValue);
	}

	return m_pValue;
}

CXExprValueRslt* CXExprRange::GetExprValueRslt()
{
	if (m_pValueRslt == NULL)
	{
		m_pValueRslt = new CXExprValueRslt();
		AddNewChild(m_pValueRslt);
	}

	return m_pValueRslt;
}