//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprBase.cpp  CXExprBase


#include "stdafx.h"
#include "XExprBase.h"

CXExprBase::CXExprBase()
{
	m_nIsUse = -1;  //是否启用
	m_nResult = 1;
	m_nCntRslt = 1;

	InitAfterRead();
}

CXExprBase::~CXExprBase()
{
}


long CXExprBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseKey, oNode, m_strUse);
	xml_GetAttibuteValue(pXmlKeys->m_strCntRsltKey, oNode, m_nCntRslt);
	return 0;
}

long CXExprBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUseKey, oElement, m_strUse);
	xml_SetAttributeValue(pXmlKeys->m_strCntRsltKey, oElement, m_nCntRslt);
	return 0;
}

long CXExprBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strUse);
		BinarySerializeCalLen(oBinaryBuffer, m_nCntRslt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strUse);
		BinarySerializeRead(oBinaryBuffer, m_nCntRslt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strUse);
		BinarySerializeWrite(oBinaryBuffer, m_nCntRslt);
	}
	return 0;
}

BOOL CXExprBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXExprBase *p = (CXExprBase*)pObj;

	if(m_strUse != p->m_strUse)
	{
		return FALSE;
	}

	if(m_nIsUse != p->m_nIsUse)
	{
		return FALSE;
	}

	if(m_nCntRslt != p->m_nCntRslt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase *p = (CXExprBase*)pDest;

	p->m_strUse = m_strUse;
	p->m_nIsUse = m_nIsUse;
	p->m_nCntRslt = m_nCntRslt;
	return TRUE;
}

void CXExprBase::InitAfterRead()
{
	if (m_strUse.IsEmpty())
	{
		m_strUse = _T("1");
	}

	if(m_strUse == _T("1") || m_strUse == _T("0"))
	{
		m_nIsUse = CString_To_long(m_strUse);
	}
}

void CXExprBase::GetRsltExprValues_ExprMode(const CString &strMode, CExBaseList *pRsltExprValues)
{
	if (! ExprModeValid(strMode))
	{
		return;
	}

	CDvmValue *pValue = new CDvmValue;
	pValue->m_strID = _T("ErrorLogic");
	pValue->m_strName = _T("误差判断逻辑");
	pRsltExprValues->AddNewChild(pValue, TRUE);

	if (strMode == _T("abs"))
	{
		pValue->m_strValue = _T("绝对误差");
	}
	else if (strMode == _T("real"))
	{
		pValue->m_strValue = _T("相对误差");
	}
	else if (strMode == _T("or"))
	{
		pValue->m_strValue = _T("绝对误差 or 相对误差");
	}
	else if (strMode == _T("and"))
	{
		pValue->m_strValue = _T("绝对误差 & 相对误差");
	}
	else if (strMode == _T("combined"))
	{
		pValue->m_strValue = _T("组合误差");
	}
}

BOOL CXExprBase::ExprModeValid(const CString &strMode)
{
	if (strMode == _T("abs")
		|| strMode == _T("real")
		|| strMode == _T("or")
		|| strMode == _T("and")
		|| strMode == _T("combined"))
	{
		return TRUE;
	}

	return FALSE;
}
