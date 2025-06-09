//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprCmp.cpp  CXExprCmp


#include "stdafx.h"
#include "XExprCmp.h"

CXExprCmp::CXExprCmp()
{
	//初始化属性

	//初始化成员变量
	m_pValueLeft = NULL;
	m_pValueRight = NULL;
	m_pValueRslt = NULL;
}

CXExprCmp::~CXExprCmp()
{
}

long CXExprCmp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	CXExprBase::XmlReadOwn(oNode, pXmlRWKeys);
	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	return 0;
}

long CXExprCmp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	CXExprBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	return 0;
}

long CXExprCmp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXExprBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strOptr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strOptr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strOptr);
	}
	return 0;
}

void CXExprCmp::InitAfterRead()
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
			m_pValueLeft = (CXExprValue1*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUE2)
		{
			m_pValueRight = (CXExprValue2*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
		{
			m_pValueRslt = (CXExprValueRslt*)p;
		}
	}

	//单独新建，全部为空
	if (m_pValueLeft == NULL)
	{
		m_pValueLeft = (CXExprValue1*)AddNewChild(new CXExprValue1());
	}

	if (m_pValueRight == NULL)
	{
		m_pValueRight = (CXExprValue2*)AddNewChild(new CXExprValue2());
	}

}

BOOL CXExprCmp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXExprBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXExprCmp *p = (CXExprCmp*)pObj;

	if(m_strOptr != p->m_strOptr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprCmp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase::CopyOwn(pDest);
	CXExprCmp *p = (CXExprCmp*)pDest;

	p->m_strOptr = m_strOptr;
	return TRUE;
}

CBaseObject* CXExprCmp::Clone()
{
	CXExprCmp *p = new CXExprCmp();
	Copy(p);
	return p;
}

CBaseObject* CXExprCmp::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprCmp *p = new CXExprCmp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprCmp::CanPaste(UINT nClassID)
{
	if (nClassID == XEXPRCLASSID_CXEXPRVALUE1)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE2)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXExprCmp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	if (strClassID == CXExprXmlRWKeys::CXExprValue1Key())
	{
		m_pValueLeft = new CXExprValue1();
		return m_pValueLeft;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValue2Key())
	{
		m_pValueRight = new CXExprValue2();
		return m_pValueRight;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueRsltKey())
	{
		m_pValueRslt = new CXExprValueRslt();
		return m_pValueRslt;
	}

	return pNew;
}

CExBaseObject* CXExprCmp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE1)
	{
		m_pValueLeft = new CXExprValue1();
		return m_pValueLeft;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE2)
	{
		m_pValueRight = new CXExprValue2();
		return m_pValueRight;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
	{
		m_pValueRslt = new CXExprValueRslt();
		return m_pValueRslt;
	}

	return pNew;
}

// long CXExprCmp::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	m_pValueLeft->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValue1Key(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueRight->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValue2Key(), CXExprXmlRWKeys::g_pXmlKeys);
// 
// 	if (m_pValueRslt != NULL)
// 	{	
// 		m_pValueRslt->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueRsltKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	}
// 
// 	return 0;
// }

long CXExprCmp::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	double dLeft = 0;
	double dRight = 0;
	m_nResult = 0;
	CString strLeft, strRight;

	if (! m_pValueLeft->Calc(pExprParent, pCalInterface, dLeft, strLeft))
	{
		return 0;
	}

	if (! m_pValueRight->Calc(pExprParent, pCalInterface, dRight, strRight))
	{
		return 0;
	}

	if (m_strOptr == _T("<"))
	{
		m_nResult = dLeft < dRight;
	}
	else if (m_strOptr == _T("<="))
	{
		m_nResult = dLeft <= dRight;
	}
	else if (m_strOptr == _T(">"))
	{
		m_nResult = dLeft > dRight;
	}
	else if (m_strOptr == _T(">="))
	{
		m_nResult = dLeft >= dRight;
	}
	else if (m_strOptr == _T("=="))
	{
		m_nResult = dLeft == dRight;
	}
	else
	{
		m_nResult = 0;
	}

	//计算结束后，将结果绑定回对应的参数
	CXExprValueRslt* pRslt = GetValueRslt();
	pRslt->m_strValue.Format(_T("%d"), m_nResult);
	pRslt->ExprRsltBind(pExprParent, pCalInterface);

	if (m_pValueLeft->m_strType == _T("dataset"))
	{
		m_pValueLeft->m_strType = _T("report");//临时改一下，用于回填
		m_pValueLeft->ExprRsltBind(pExprParent, pCalInterface);
		m_pValueLeft->m_strType = _T("dataset");
	}
	else
	{
		//直接回填
		m_pValueLeft->ExprRsltBind(pExprParent, pCalInterface);
	}

	if (m_pValueRight->m_strType == _T("dataset"))
	{
		m_pValueRight->m_strType = _T("report");//临时改一下，用于回填
		m_pValueRight->ExprRsltBind(pExprParent, pCalInterface);
		m_pValueRight->m_strType = _T("dataset");
	}
	else
	{
		//直接回填
		m_pValueRight->ExprRsltBind(pExprParent, pCalInterface);
	}

	return m_nResult;
}

void CXExprCmp::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
}

void CXExprCmp::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueLeft != NULL)
	{
		m_pValueLeft->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueRight != NULL)
	{
		m_pValueRight->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}
}

BOOL CXExprCmp::GetValueName(const CString &strID, CString &strName)
{
	if (m_pValueRslt != NULL)
	{
		if (m_pValueRslt->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValueLeft != NULL)
	{
		if (m_pValueLeft->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValueRight != NULL)
	{
		if (m_pValueRight->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	return FALSE;
}

CXExprValue1* CXExprCmp::GetExprValue1()
{
	if (m_pValueLeft == NULL)
	{
		m_pValueLeft = new CXExprValue1();
		AddNewChild(m_pValueLeft);
	}

	return m_pValueLeft;
}

CXExprValue2* CXExprCmp::GetExprValue2()
{
	if (m_pValueRight == NULL)
	{
		m_pValueRight = new CXExprValue2();
		AddNewChild(m_pValueRight);
	}

	return m_pValueRight;
}

CXExprValueRslt* CXExprCmp::GetValueRslt()
{
	if (m_pValueRslt == NULL)
	{
		m_pValueRslt = new CXExprValueRslt();
		AddNewChild(m_pValueRslt);
	}

	return m_pValueRslt;
}