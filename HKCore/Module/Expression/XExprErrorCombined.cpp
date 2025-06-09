//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprErrorCombined.cpp  CXExprErrorCombined


#include "stdafx.h"
#include "XExprErrorCombined.h"
#include <math.h>

CXExprErrorCombined::CXExprErrorCombined()
{
	//初始化属性

	//初始化成员变量
	m_pValue = NULL;
	m_pValueStd = NULL;
	m_pErrorRel = NULL;
	m_pErrorAbs = NULL;
	m_pValueRslt = NULL;
	m_pValueErrorRslt = NULL;
}

CXExprErrorCombined::~CXExprErrorCombined()
{
}

long CXExprErrorCombined::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	return 0;
}

long CXExprErrorCombined::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	return 0;
}

long CXExprErrorCombined::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXExprErrorCombined::InitAfterRead()
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
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUESTD)
		{
			m_pValueStd = (CXExprValueStd*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
		{
			m_pValueRslt = (CXExprValueRslt*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORREL)
		{
			m_pErrorRel = (CXExprValueErrorRel*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABS)
		{
			m_pErrorAbs = (CXExprValueErrorAbs*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORRSLT)
		{
			m_pValueErrorRslt = (CXExprValueErrorRslt*)p;
		}
	}

	//单独新建，全部为空
	if (m_pValue == NULL)
	{
		m_pValue = (CXExprValue*)AddNewChild(new CXExprValue());
	}

	if (m_pValueStd == NULL)
	{
		m_pValueStd = (CXExprValueStd*)AddNewChild(new CXExprValueStd());
	}

	if (m_pErrorRel == NULL)
	{
		m_pErrorRel = (CXExprValueErrorRel*)AddNewChild(new CXExprValueErrorRel());
	}

	if (m_pErrorAbs == NULL)
	{
		m_pErrorAbs = (CXExprValueErrorAbs*)AddNewChild(new CXExprValueErrorAbs());
	}

	if (m_pValueErrorRslt == NULL)
	{
		m_pValueErrorRslt = (CXExprValueErrorRslt *)AddNewChild(new CXExprValueErrorRslt());
	}
}

BOOL CXExprErrorCombined::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXExprBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXExprErrorCombined *p = (CXExprErrorCombined*)pObj;

	if(m_strOptr != p->m_strOptr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprErrorCombined::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase::CopyOwn(pDest);
	CXExprErrorCombined *p = (CXExprErrorCombined*)pDest;

	p->m_strOptr = m_strOptr;
	return TRUE;
}

CBaseObject* CXExprErrorCombined::Clone()
{
	CXExprErrorCombined *p = new CXExprErrorCombined();
	Copy(p);
	return p;
}

CBaseObject* CXExprErrorCombined::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprErrorCombined *p = new CXExprErrorCombined();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprErrorCombined::CanPaste(UINT nClassID)
{
	if (nClassID == XEXPRCLASSID_CXEXPRVALUE)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUESTD)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORREL)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABS)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORRSLT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXExprErrorCombined::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;


	if (strClassID == CXExprXmlRWKeys::CXExprValueStdKey())
	{
		m_pValueStd = new CXExprValueStd();
		return m_pValueStd;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueErrorRelKey())
	{
		m_pErrorRel = new CXExprValueErrorRel();
		return m_pErrorRel;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueErrorAbsKey())
	{
		m_pErrorAbs = new CXExprValueErrorAbs();
		return m_pErrorAbs;
	}

	if (strClassID == CXExprXmlRWKeys::ValueKey())
	{
		m_pValue = new CXExprValue();
		return m_pValue;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueRsltKey())
	{
		m_pValueRslt = new CXExprValueRslt();
		return m_pValueRslt;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueErrorRsltKey())
	{
		m_pValueErrorRslt = new CXExprValueErrorRslt();
		return m_pValueErrorRslt;
	}

	return pNew;
}

CExBaseObject* CXExprErrorCombined::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE)
	{
		m_pValue = new CXExprValue();
		return m_pValue;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORREL)
	{
		m_pErrorRel = new CXExprValueErrorRel();
		return m_pErrorRel;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABS)
	{
		m_pErrorAbs = new CXExprValueErrorAbs();
		return m_pErrorAbs;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUESTD)
	{
		m_pValueStd = new CXExprValueStd();
		return m_pValueStd;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUERSLT)
	{
		m_pValueRslt = new CXExprValueRslt();
		return m_pValueRslt;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORRSLT)
	{
		m_pValueErrorRslt = new CXExprValueErrorRslt();
		return m_pValueErrorRslt;
	}

	return pNew;
}

// long CXExprErrorCombined::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	m_pValueStd->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueStdKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValue->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pError->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprErrorCombinedKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueRslt->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueRsltKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 
// 	return 0;
// }

long CXExprErrorCombined::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	double dValStd = 0;
	double dValue = 0;
	double dErrorRel = 0;
	double dErrorAbs = 0;
	double dCal = 0;
	m_nResult = 0;
	CString strValStd, strValue, strErrorRel, strErrorAbs;
	
	if ( !CalcEx(pExprParent, pCalInterface, dValStd, dValue, dErrorRel, dErrorAbs
		,strValStd, strValue, strErrorRel, strErrorAbs))
	{
		return 0;
	}

	dErrorRel = dErrorRel / 100.0;
	dCal = dValue - dValStd;
	double dLimit = dValStd * dErrorRel + dErrorAbs;

	if (m_strOptr == _T("<="))
	{
		m_nResult = (fabs(dCal) <= dLimit);
	}
	else if (m_strOptr == _T("<"))
	{
		m_nResult = (fabs(dCal) < dLimit);
	}

	//将误差结果，存入误差结果数据对象
	CXExprValueErrorRslt *pValueErrorRslt = GetExprValueErrorRslt();

	if (pValueErrorRslt->IsValueUint_ms())
	{
		dCal *= 1000;
	}

	if (strValue == _T("未动作"))
	{
		pValueErrorRslt->m_strValue = _T("--");
		m_nResult = 0;
	}
	else
	{
		pValueErrorRslt->m_strValue.Format(_T("%.3f"), dCal);
	}

	pValueErrorRslt->ExprRsltBind(pExprParent, pCalInterface);

	//计算结束后，将结果绑定回对应的参数
	CXExprValueRslt* pRslt = GetExprValueRslt();
	pRslt->m_strValue.Format(_T("%d"), m_nResult);
	pRslt->ExprRsltBind(pExprParent, pCalInterface);

	//基准值，也需要回填。因为基准值可能从界面过来，
	if (m_pValueStd != NULL)
	{
		m_pValueStd->ExprRsltBind(pExprParent, pCalInterface);
	}

	//报告数据，修约后，也需要回绑  2023-8-29
	//对于动作时间测试，底层上送的数据以s为单位，填入到word报告中以ms为单位。
	//此处不能进行修约后回绑，否则填入到word中的数据将会失真。2023-8-31
// 	if (m_pValue != NULL)
// 	{
// 		m_pValue->ExprRsltBind(pExprParent, pCalInterface);
// 	}

	return m_nResult;
}

long CXExprErrorCombined::CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, double &dValStd, double &dVal, double &dErrRel, double &dErrAbs
								 , CString &strValStd, CString &strValue, CString &strErrorRel, CString &strErrorAbs)
{
	if (! m_pValueStd->Calc(pExprParent, pCalInterface, dValStd, strValStd))
	{
		return 0;
	}

	if (! m_pValue->Calc(pExprParent, pCalInterface, dVal, strValue))
	{
		return 0;
	}

	if (! m_pErrorAbs->Calc(pExprParent, pCalInterface, dErrAbs, strErrorRel))
	{
		return 0;
	}

	if (! m_pErrorRel->Calc(pExprParent, pCalInterface, dErrRel, strErrorAbs))
	{
		return 0;
	}

	return 1;
}

void CXExprErrorCombined::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->ExprRsltBind(pExprParent, pCalInterface);
	}

	if (m_pValueErrorRslt != NULL)
	{
		m_pValueErrorRslt->ExprRsltBind(pExprParent, pCalInterface);
	}

	//基准值，也需要回填。因为基准值可能从界面过来，
	if (m_pValueStd != NULL)
	{
		m_pValueStd->ExprRsltBind(pExprParent, pCalInterface);
	}

	//报告数据，修约后，也需要回绑  2023-8-29
	//对于动作时间测试，底层上送的数据以s为单位，填入到word报告中以ms为单位。
	//此处不能进行修约后回绑，否则填入到word中的数据将会失真。2023-8-31
// 	if (m_pValue != NULL)
// 	{
// 		m_pValue->ExprRsltBind(pExprParent, pCalInterface);
// 	}
}

void CXExprErrorCombined::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (m_pValue != NULL)
	{
		m_pValue->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueStd != NULL)
	{
		m_pValueStd->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pErrorRel != NULL)
	{
		m_pErrorRel->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pErrorAbs != NULL)
	{
		m_pErrorAbs->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueErrorRslt != NULL)
	{
		m_pValueErrorRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}
}

BOOL CXExprErrorCombined::GetValueName(const CString &strID, CString &strName)
{
	if (m_pValue != NULL)
	{
		if (m_pValue->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValueStd != NULL)
	{
		if (m_pValueStd->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pErrorRel != NULL)
	{
		if (m_pErrorRel->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pErrorAbs != NULL)
	{
		if (m_pErrorAbs->GetValueName(strID, strName))
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

	if (m_pValueErrorRslt != NULL)
	{
		if (m_pValueErrorRslt->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	return FALSE;
}
//获取结果参数
CXExprValue* CXExprErrorCombined::GetExprValue()
{
	if (m_pValue == NULL)
	{
		m_pValue = new CXExprValue();
		AddNewChild(m_pValue);
	}

	return m_pValue;
}

//获取基准参数
CXExprValueStd* CXExprErrorCombined::GetExprValueStd()
{
	if (m_pValueStd == NULL)
	{
		m_pValueStd = new CXExprValueStd();
		AddNewChild(m_pValueStd);
	}

	return m_pValueStd;
}

//获取相对误差限
CXExprValueErrorRel* CXExprErrorCombined::GetExprValueErrorRel()
{
	if (m_pErrorRel == NULL)
	{
		m_pErrorRel = new CXExprValueErrorRel();
		AddNewChild(m_pErrorRel);
	}

	return m_pErrorRel;
}

//获取绝对误差限
CXExprValueErrorAbs* CXExprErrorCombined::GetExprValueErrorAbs()
{
	if (m_pErrorAbs == NULL)
	{
		m_pErrorAbs = new CXExprValueErrorAbs();
		AddNewChild(m_pErrorAbs);
	}

	return m_pErrorAbs;
}

//获取表达式计算结果（合格 or 不合格）
CXExprValueRslt* CXExprErrorCombined::GetExprValueRslt()
{
	if (m_pValueRslt == NULL)
	{
		m_pValueRslt = new CXExprValueRslt();
		AddNewChild(m_pValueRslt);
	}

	return m_pValueRslt;
}

//获取误差计算值
CXExprValueErrorRslt* CXExprErrorCombined::GetExprValueErrorRslt()
{
	if (m_pValueErrorRslt == NULL)
	{
		m_pValueErrorRslt = new CXExprValueErrorRslt();
		AddNewChild(m_pValueErrorRslt);
	}

	return m_pValueErrorRslt;
}