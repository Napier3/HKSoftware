//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprRangeEx.cpp  CXExprRangeEx


#include "stdafx.h"
#include "XExprRangeEx.h"

CXExprRangeEx::CXExprRangeEx()
{
	//初始化属性

	//初始化成员变量
	m_pValueMin = NULL;
	m_pValueMax = NULL;
	m_pValue1 = NULL;
	m_pValue2 = NULL;
	m_pValueCalRslt = NULL;
	m_pValueRslt = NULL;
}

CXExprRangeEx::~CXExprRangeEx()
{
}

long CXExprRangeEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strMinOptrKey, oNode, m_strMinOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxOptrKey, oNode, m_strMaxOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strCalOptrKey, oNode, m_strCalOptr);

	return 0;
}

long CXExprRangeEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strMinOptrKey, oElement, m_strMinOptr);
	xml_SetAttributeValue(pXmlKeys->m_strMaxOptrKey, oElement, m_strMaxOptr);
	xml_SetAttributeValue(pXmlKeys->m_strCalOptrKey, oElement, m_strCalOptr);
	return 0;
}

long CXExprRangeEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXExprBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMinOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_strMaxOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_strCalOptr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMinOptr);
		BinarySerializeRead(oBinaryBuffer, m_strMaxOptr);
		BinarySerializeRead(oBinaryBuffer, m_strCalOptr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMinOptr);
		BinarySerializeWrite(oBinaryBuffer, m_strMaxOptr);
		BinarySerializeWrite(oBinaryBuffer, m_strCalOptr);
	}
	return 0;
}

void CXExprRangeEx::InitAfterRead()
{
	CXExprBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == XEXPRCLASSID_CXEXPRVALUE1)
		{
			m_pValue1 = (CXExprValue1*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUE2)
		{
			m_pValue2 = (CXExprValue2*)p;
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
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUECALRSLT)
		{
			m_pValueCalRslt = (CXExprValueCalRslt*)p;
		}
	}

	//单独新建，全部为空
	if (m_pValueMin == NULL)
	{
		m_pValueMin = (CXExprValueMin *)AddNewChild(new CXExprValueMin());
	}

	if (m_pValue1 == NULL)
	{
		m_pValue1 = (CXExprValue1 *)AddNewChild(new CXExprValue1());
	}

	if (m_pValue2 == NULL)
	{
		m_pValue2 = (CXExprValue2 *)AddNewChild(new CXExprValue2());
	}

	if (m_pValueMax == NULL)
	{
		m_pValueMax = (CXExprValueMax *)AddNewChild(new CXExprValueMax());
	}

	if (m_pValueCalRslt == NULL)
	{
		m_pValueCalRslt = (CXExprValueCalRslt *)AddNewChild(new CXExprValueCalRslt());
	}
}

BOOL CXExprRangeEx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXExprBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXExprRangeEx *p = (CXExprRangeEx*)pObj;

	if(m_strMinOptr != p->m_strMinOptr)
	{
		return FALSE;
	}

	if(m_strMaxOptr != p->m_strMaxOptr)
	{
		return FALSE;
	}

	if(m_strCalOptr != p->m_strCalOptr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprRangeEx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase::CopyOwn(pDest);
	CXExprRangeEx *p = (CXExprRangeEx*)pDest;
	p->m_strMinOptr = m_strMinOptr;
	p->m_strMaxOptr = m_strMaxOptr;
	p->m_strCalOptr = m_strCalOptr;

	return TRUE;
}

CBaseObject* CXExprRangeEx::Clone()
{
	CXExprRangeEx *p = new CXExprRangeEx();
	Copy(p);
	return p;
}

CBaseObject* CXExprRangeEx::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprRangeEx *p = new CXExprRangeEx();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprRangeEx::CanPaste(UINT nClassID)
{
	if (nClassID == XEXPRCLASSID_CXEXPRVALUE1)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE2)
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

	if (nClassID == XEXPRCLASSID_CXEXPRVALUECALRSLT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXExprRangeEx::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

	if (strClassID == CXExprXmlRWKeys::CXExprValue1Key())
	{
		m_pValue1 = new CXExprValue1();
		return m_pValue1;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValue2Key())
	{
		m_pValue2 = new CXExprValue2();
		return m_pValue2;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueCalRsltKey())
	{
		m_pValueCalRslt = new CXExprValueCalRslt();
		return m_pValueCalRslt;
	}

	return pNew;
}

CExBaseObject* CXExprRangeEx::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE1)
	{
		m_pValue1 = new CXExprValue1();
		return m_pValue1;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE2)
	{
		m_pValue2 = new CXExprValue2();
		return m_pValue2;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUECALRSLT)
	{
		m_pValueCalRslt = new CXExprValueCalRslt();
		return m_pValueCalRslt;
	}

	return pNew;
}

// long CXExprRangeEx::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	m_pValueMin->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueMinKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValue->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueMax->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueMaxKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueRslt->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueRsltKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 
// 	return 0;
// }

long CXExprRangeEx::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	double dMin = 0;
	double dMax = 0;
	double dValue1 = 0;
	double dValue2 = 0;
	double dValueCal = 0;

	m_nResult = 0;
	CString strMin, strMax, strValue1, strValue2;

	if (! m_pValueMin->Calc(pExprParent, pCalInterface, dMin, strMin))
	{
		return 0;
	}

	if (! m_pValue1->Calc(pExprParent, pCalInterface, dValue1, strValue1))
	{
		return 0;
	}

	if (! m_pValue2->Calc(pExprParent, pCalInterface, dValue2, strValue2))
	{
		return 0;
	}

	if (! m_pValueMax->Calc(pExprParent, pCalInterface, dMax, strMax))
	{
		return 0;
	}

	if (m_strCalOptr == _T("+"))
	{
		dValueCal = dValue1 + dValue2;
	}
	else if (m_strCalOptr == _T("-"))
	{
		dValueCal = dValue1 - dValue2;
	}
	else if (m_strCalOptr == _T("*"))
	{
		dValueCal = dValue1 * dValue2;
	}
	else if (m_strCalOptr == _T("/"))
	{
		dValueCal = dValue1 / dValue2;
	}

	BOOL bRstMin = FALSE;
	BOOL bRstMax = FALSE;

	if (m_strMinOptr == _T(">="))
	{
		bRstMin = (dMin <= dValueCal);
	}
	else if (m_strMinOptr == _T(">"))
	{
		bRstMin = (dMin < dValueCal);
	}

	if (m_strMaxOptr == _T("<="))
	{
		bRstMax = (dValueCal <= dMax);
	}
	else if (m_strMaxOptr == _T("<"))
	{
		bRstMax = (dValueCal < dMax);
	}

	m_nResult = bRstMin && bRstMax;

	if (m_nResult == 0)
	{
		int x = 0;
	}
	//m_nResult = (dMin <= dValue) && (dValue <= dMax);

	//计算结束后，将结果绑定回对应的参数
	CXExprValueRslt* pRslt = GetExprValueRslt();
	pRslt->m_strValue.Format(_T("%d"), m_nResult);
	pRslt->ExprRsltBind(pExprParent, pCalInterface);

	CXExprValueCalRslt *pCalRslt = GetExprValueCalRslt();
	pCalRslt->m_strValue.Format(_T("%.3f"), dValueCal);
	pCalRslt->ExprRsltBind(pExprParent, pCalInterface);
	//最大值和最小值，可能从界面来，需要回填
	m_pValueMax->ExprRsltBind(pExprParent, pCalInterface);
	m_pValueMin->ExprRsltBind(pExprParent, pCalInterface);

	return m_nResult;
}

void CXExprRangeEx::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->ExprRsltBind(pExprParent, pCalInterface);
	}

	//基准值，也需要回填。因为基准值可能从界面过来，
	if (m_pValue1 != NULL)
	{
		m_pValue1->ExprRsltBind(pExprParent, pCalInterface);
	}

	//基准值，也需要回填。因为基准值可能从界面过来，
	if (m_pValue2 != NULL)
	{
		m_pValue2->ExprRsltBind(pExprParent, pCalInterface);
	}

	if (m_pValueCalRslt != NULL)
	{
		m_pValueCalRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
}

void CXExprRangeEx::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (m_pValueMin != NULL)
	{
		m_pValueMin->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueMax != NULL)
	{
		m_pValueMax->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValue1 != NULL)
	{
		m_pValue1->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValue2 != NULL)
	{
		m_pValue2->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueCalRslt != NULL)
	{
		m_pValueCalRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}
}

BOOL CXExprRangeEx::GetValueName(const CString &strID, CString &strName)
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

	if (m_pValue1 != NULL)
	{
		if (m_pValue1->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValue2 != NULL)
	{
		if (m_pValue2->GetValueName(strID, strName))
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

	if (m_pValueCalRslt != NULL)
	{
		if (m_pValueCalRslt->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	return FALSE;
}

CXExprValueMin* CXExprRangeEx::GetExprValueMin()
{
	if (m_pValueMin == NULL)
	{
		m_pValueMin = new CXExprValueMin();
		AddNewChild(m_pValueMin);
	}

	return m_pValueMin;
}

CXExprValueMax* CXExprRangeEx::GetExprValueMax()
{
	if (m_pValueMax == NULL)
	{
		m_pValueMax = new CXExprValueMax();
		AddNewChild(m_pValueMax);
	}

	return m_pValueMax;
}

//获取结果参数1
CXExprValue1* CXExprRangeEx::GetExprValue1()
{
	if (m_pValue1 == NULL)
	{
		m_pValue1 = new CXExprValue1();
		AddNewChild(m_pValue1);
	}

	return m_pValue1;
}

//获取结果参数2
CXExprValue2* CXExprRangeEx::GetExprValue2()
{
	if (m_pValue2 == NULL)
	{
		m_pValue2 = new CXExprValue2();
		AddNewChild(m_pValue2);
	}

	return m_pValue2;
}

//获取结果参数1与结果参数2的数据运算结果
CXExprValueCalRslt* CXExprRangeEx::GetExprValueCalRslt()
{
	if (m_pValueCalRslt == NULL)
	{
		m_pValueCalRslt = new CXExprValueCalRslt();
		AddNewChild(m_pValueCalRslt);
	}

	return m_pValueCalRslt;
}

CXExprValueRslt* CXExprRangeEx::GetExprValueRslt()
{
	if (m_pValueRslt == NULL)
	{
		m_pValueRslt = new CXExprValueRslt();
		AddNewChild(m_pValueRslt);
	}

	return m_pValueRslt;
}