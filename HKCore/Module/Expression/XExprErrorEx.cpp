//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprErrorEx.cpp  CXExprErrorEx


#include "stdafx.h"
#include "XExprErrorEx.h"
#include <math.h>

CXExprErrorEx::CXExprErrorEx()
{
	//初始化属性

	//初始化成员变量
	m_pValue = NULL;
	m_pValueStd = NULL;
	m_pErrorRel = NULL;
	m_pErrorAbs = NULL;
	m_pValueRslt = NULL;
	m_pValueErrorRelRslt = NULL;
	m_pValueErrorAbsRslt = NULL;
}

CXExprErrorEx::~CXExprErrorEx()
{
}

long CXExprErrorEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strMode);
	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	return 0;
}

long CXExprErrorEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strMode);
	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	return 0;
}

long CXExprErrorEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXExprBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strOptr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMode);
		BinarySerializeRead(oBinaryBuffer, m_strOptr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMode);
		BinarySerializeWrite(oBinaryBuffer, m_strOptr);
	}
	return 0;
}

void CXExprErrorEx::InitAfterRead()
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
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORRELRSLT)
		{
			m_pValueErrorRelRslt = (CXExprValueErrorRelRslt*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABSRSLT)
		{
			m_pValueErrorAbsRslt = (CXExprValueErrorAbsRslt*)p;
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

	if (m_pValueErrorRelRslt == NULL)
	{
		m_pValueErrorRelRslt = (CXExprValueErrorRelRslt *)AddNewChild(new CXExprValueErrorRelRslt());
	}

	if (m_pValueErrorAbsRslt == NULL)
	{
		m_pValueErrorAbsRslt = (CXExprValueErrorAbsRslt *)AddNewChild(new CXExprValueErrorAbsRslt());
	}
}

BOOL CXExprErrorEx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXExprBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXExprErrorEx *p = (CXExprErrorEx*)pObj;

	if(m_strMode != p->m_strMode)
	{
		return FALSE;
	}

	if(m_strOptr != p->m_strOptr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprErrorEx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase::CopyOwn(pDest);
	CXExprErrorEx *p = (CXExprErrorEx*)pDest;

	p->m_strMode = m_strMode;
	p->m_strOptr = m_strOptr;
	return TRUE;
}

CBaseObject* CXExprErrorEx::Clone()
{
	CXExprErrorEx *p = new CXExprErrorEx();
	Copy(p);
	return p;
}

CBaseObject* CXExprErrorEx::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprErrorEx *p = new CXExprErrorEx();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprErrorEx::CanPaste(UINT nClassID)
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

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORRELRSLT)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABSRSLT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXExprErrorEx::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

	if (strClassID == CXExprXmlRWKeys::CXExprValueErrorRelRsltKey())
	{
		m_pValueErrorRelRslt = new CXExprValueErrorRelRslt();
		return m_pValueErrorRelRslt;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueErrorAbsRsltKey())
	{
		m_pValueErrorAbsRslt = new CXExprValueErrorAbsRslt();
		return m_pValueErrorAbsRslt;
	}

	return pNew;
}

CExBaseObject* CXExprErrorEx::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORRELRSLT)
	{
		m_pValueErrorRelRslt = new CXExprValueErrorRelRslt();
		return m_pValueErrorRelRslt;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABSRSLT)
	{
		m_pValueErrorAbsRslt = new CXExprValueErrorAbsRslt();
		return m_pValueErrorAbsRslt;
	}

	return pNew;
}

// long CXExprErrorEx::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	m_pValueStd->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueStdKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValue->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pError->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprErrorExKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueRslt->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueRsltKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 
// 	return 0;
// }

long CXExprErrorEx::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	double dValStd = 0;
	double dValue = 0;
	double dErrorRel = 0;
	double dErrorAbs = 0;
	double dCalRel = 0;
	double dCalAbs = 0;
	m_nResult = 0;
	CString strValStd, strValue, strErrorRel, strErrorAbs;
	
	if ( !CalcEx(pExprParent, pCalInterface, dValStd, dValue, dErrorRel, dErrorAbs
		, strValStd, strValue, strErrorRel, strErrorAbs))
	{
		return 0;
	}

	dErrorRel = dErrorRel / 100.0;

	if (m_strMode == _T("abs"))
	{
		m_nResult = Calc_Abs(dCalAbs, dValStd, dValue, dErrorAbs);

		//将误差结果，存入误差结果数据对象
		CXExprValueErrorAbsRslt *pValueErrorAbsRslt = GetExprValueErrorAbsRslt();

		if (pValueErrorAbsRslt->IsValueUint_ms())
		{
			dCalAbs *= 1000;
		}

		if (strValue == _T("未动作"))
		{
			pValueErrorAbsRslt->m_strValue = _T("--");
			m_nResult = 0;
		}
		else
		{
			pValueErrorAbsRslt->m_strValue.Format(_T("%.3f"), dCalAbs);
		}

		//计算结束后，将结果绑定回对应的参数
		pValueErrorAbsRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
	else if (m_strMode == _T("real"))
	{
		m_nResult = Calc_Rel(dCalRel, dValStd, dValue, dErrorRel);

		//将误差结果，存入误差结果数据对象
		CXExprValueErrorRelRslt *pValueErrorRelRslt = GetExprValueErrorRelRslt();

		if (strValue == _T("未动作"))
		{
			dCalRel = -100.0;
			m_nResult = 0;
		}

		if (dValStd == 0.0 || strValue == _T("未动作"))
		{
			pValueErrorRelRslt->m_strValue = _T("--");
		}
		else
		{
			pValueErrorRelRslt->m_strValue.Format(_T("%.3f"), dCalRel);
		}
		
		//计算结束后，将结果绑定回对应的参数
		pValueErrorRelRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
	else if (m_strMode == _T("combined"))
	{
		m_nResult = Calc_Combined(dCalAbs, dValStd, dValue, dErrorRel, dErrorAbs);

		//将误差结果，存入误差结果数据对象
		CXExprValueErrorAbsRslt *pValueErrorAbsRslt = GetExprValueErrorAbsRslt();

		if (pValueErrorAbsRslt->IsValueUint_ms())
		{
			dCalAbs *= 1000;
		}

		if (strValue == _T("未动作"))
		{
			pValueErrorAbsRslt->m_strValue = _T("--");
			m_nResult = 0;
		}
		else
		{
			pValueErrorAbsRslt->m_strValue.Format(_T("%.3f"), dCalAbs);
		}

		//计算结束后，将结果绑定回对应的参数
		pValueErrorAbsRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
	else if (m_strMode == _T("or"))
	{
		m_nResult = Calc_Or(dCalRel, dCalAbs, dValStd, dValue, dErrorRel, dErrorAbs);

		//将误差结果，存入误差结果数据对象
		CXExprValueErrorRelRslt *pValueErrorRelRslt = GetExprValueErrorRelRslt();
		CXExprValueErrorAbsRslt *pValueErrorAbsRslt = GetExprValueErrorAbsRslt();

		if (pValueErrorAbsRslt->IsValueUint_ms())
		{
			dCalAbs *= 1000;
		}

		if (strValue == _T("未动作"))
		{
			dCalRel = -100.0;
			pValueErrorAbsRslt->m_strValue = _T("--");
			m_nResult = 0;
		}
		else
		{
			pValueErrorAbsRslt->m_strValue.Format(_T("%.3f"), dCalAbs);
		}

		if (dValStd == 0.0 || strValue == _T("未动作"))
		{
			pValueErrorRelRslt->m_strValue = _T("--");
		}
		else
		{
			pValueErrorRelRslt->m_strValue.Format(_T("%.3f"), dCalRel);
		}

		//计算结束后，将结果绑定回对应的参数
		pValueErrorRelRslt->ExprRsltBind(pExprParent, pCalInterface);
		pValueErrorAbsRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
	else if (m_strMode == _T("and"))
	{
		m_nResult = Calc_And(dCalRel, dCalAbs, dValStd, dValue, dErrorRel, dErrorAbs);

		//将误差结果，存入误差结果数据对象
		CXExprValueErrorRelRslt *pValueErrorRelRslt = GetExprValueErrorRelRslt();
		CXExprValueErrorAbsRslt *pValueErrorAbsRslt = GetExprValueErrorAbsRslt();

		if (pValueErrorAbsRslt->IsValueUint_ms())
		{
			dCalAbs *= 1000;
		}

		if (strValue == _T("未动作"))
		{
			dCalRel = -100.0;
			pValueErrorAbsRslt->m_strValue = _T("--");
			m_nResult = 0;
		}
		else
		{
			pValueErrorAbsRslt->m_strValue.Format(_T("%.3f"), dCalAbs);
		}

		if (dValStd == 0.0 || strValue == _T("未动作"))
		{
			pValueErrorRelRslt->m_strValue = _T("--");
		}
		else
		{
			pValueErrorRelRslt->m_strValue.Format(_T("%.3f"), dCalRel);
		}

		//计算结束后，将结果绑定回对应的参数
		pValueErrorRelRslt->ExprRsltBind(pExprParent, pCalInterface);
		pValueErrorAbsRslt->ExprRsltBind(pExprParent, pCalInterface);
	}

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

long CXExprErrorEx::CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, double &dValStd, double &dVal, double &dErrRel, double &dErrAbs
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

	if (m_strMode == _T("abs"))
	{
		return m_pErrorAbs->Calc(pExprParent, pCalInterface, dErrAbs, strErrorAbs);
	}

	if (m_strMode == _T("real"))
	{
		return m_pErrorRel->Calc(pExprParent, pCalInterface, dErrRel, strErrorRel);
	}

	if (! m_pErrorRel->Calc(pExprParent, pCalInterface, dErrRel, strErrorRel))
	{
		return 0;
	}

	if (! m_pErrorAbs->Calc(pExprParent, pCalInterface, dErrAbs, strErrorAbs))
	{
		return 0;
	}

	return 1;
}

long CXExprErrorEx::Calc_Abs(double &dCal, double dValStd, double dVal, double dErrAbs)
{
	long nRslt = 0;
	dCal = dVal - dValStd;

	if (m_strOptr == _T("<="))
	{
		//nRslt = (fabs(dCal) <= dErrAbs);
		double d1 = (fabs(fabs(dCal) - dErrAbs));
		double d2 = ( 0.0001 + dErrAbs);
		nRslt = ( (fabs(dCal)) <= ( 0.0001 + dErrAbs) );
	}
	else if (m_strOptr == _T("<"))
	{
		//nRslt = (fabs(dCal) < dErrAbs);
		nRslt = ( (fabs(dCal)) < ( 0.0001 + dErrAbs) );
	}

	return nRslt;
}

long CXExprErrorEx::Calc_Rel(double &dCal, double dValStd, double dVal, double dErrRel)
{
	long nRslt = 0;
	dCal = dVal - dValStd;

	if (dVal == 0)
	{
		m_nResult = 0;
		dCal = 100.0;
	}
	else
	{
		if (dValStd == 0.0)
		{
			dCal = -100.0;
		}
		else
		{
			dCal = (dVal - dValStd) / dValStd/* * 100*/;
			double dCalEx = fabs(dCal);

			if (m_strOptr == _T("<="))
			{
				nRslt = (dCalEx <= dErrRel); 
				//nRslt = ( (fabs(dCalEx - dErrRel)) <= 0.000001 );
			}
			else if (m_strOptr == _T("<"))
			{
				nRslt = (dCalEx < dErrRel);
				//nRslt = ( (fabs(dCalEx - dErrRel)) < 0.000001 );
			}

			dCal = dCal * 100.0;
		}
	}

	return nRslt;
}

long CXExprErrorEx::Calc_Or(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs)
{
	long nRsltRel = Calc_Rel(dCalRel, dValStd, dVal, dErrRel);
	long nRsltAbs = Calc_Abs(dCalAbs, dValStd, dVal, dErrAbs);

	return ( nRsltAbs || nRsltRel);
}

long CXExprErrorEx::Calc_And(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs)
{
	long nRsltRel = Calc_Rel(dCalRel, dValStd, dVal, dErrRel);
	long nRsltAbs = Calc_Abs(dCalAbs, dValStd, dVal, dErrAbs);

	return ( nRsltAbs && nRsltRel);
}

long CXExprErrorEx::Calc_Combined(double &dCal, double dValStd, double dVal, double dErrRel, double dErrAbs)
{
	long nRslt = 0;
	dCal = dVal - dValStd;
	double dLimit = dValStd * dErrRel + dErrAbs;

	if (m_strOptr == _T("<="))
	{
		//nRslt = (fabs(dCal) <= dLimit);
		nRslt = ( (fabs(dCal)) <= ( 0.0001 + dLimit) );
	}
	else if (m_strOptr == _T("<"))
	{
		//nRslt = (fabs(dCal) < dLimit);
		nRslt = ( (fabs(dCal)) < ( 0.0001 + dLimit) );
	}

	return nRslt;
}

void CXExprErrorEx::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->ExprRsltBind(pExprParent, pCalInterface);
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

	if (m_strMode == _T("real"))
	{
		if (m_pValueErrorRelRslt != NULL)
		{
			m_pValueErrorRelRslt->ExprRsltBind(pExprParent, pCalInterface);
		}
	}
	else if (m_strMode == _T("abs") || m_strMode == _T("combined"))
	{
		if (m_pValueErrorAbsRslt != NULL)
		{
			m_pValueErrorAbsRslt->ExprRsltBind(pExprParent, pCalInterface);
		}
	}
	else
	{
		if (m_pValueErrorAbsRslt != NULL)
		{
			m_pValueErrorAbsRslt->ExprRsltBind(pExprParent, pCalInterface);
		}

		if (m_pValueErrorRelRslt != NULL)
		{
			m_pValueErrorRelRslt->ExprRsltBind(pExprParent, pCalInterface);
		}
	}
}

void CXExprErrorEx::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValue != NULL)
	{
		m_pValue->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueStd != NULL)
	{
		m_pValueStd->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_strMode == _T("abs"))
	{
		if (m_pErrorAbs != NULL)
		{
			m_pErrorAbs->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pValueErrorAbsRslt != NULL)
		{
			m_pValueErrorAbsRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}
	}
	else if (m_strMode == _T("real"))
	{
		if (m_pErrorRel != NULL)
		{
			m_pErrorRel->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pValueErrorRelRslt != NULL)
		{
			m_pValueErrorRelRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}
	}
	else if (m_strMode == _T("combined"))
	{
		if (m_pErrorAbs != NULL)
		{
			m_pErrorAbs->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pErrorRel != NULL)
		{
			m_pErrorRel->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pValueErrorAbsRslt != NULL)
		{
			m_pValueErrorAbsRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}
	}
	else
	{
		if (m_pErrorAbs != NULL)
		{
			m_pErrorAbs->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pValueErrorAbsRslt != NULL)
		{
			m_pValueErrorAbsRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pErrorRel != NULL)
		{
			m_pErrorRel->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pValueErrorRelRslt != NULL)
		{
			m_pValueErrorRelRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}
	}

	GetRsltExprValues_ExprMode(m_strMode, pRsltExprValues);
}

BOOL CXExprErrorEx::GetValueName(const CString &strID, CString &strName)
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

	if (m_pValueErrorRelRslt != NULL)
	{
		if (m_pValueErrorRelRslt->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pValueErrorAbsRslt != NULL)
	{
		if (m_pValueErrorAbsRslt->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	return FALSE;
}

//获取结果参数
CXExprValue* CXExprErrorEx::GetExprValue()
{
	if (m_pValue == NULL)
	{
		m_pValue = new CXExprValue();
		AddNewChild(m_pValue);
	}

	return m_pValue;
}

//获取基准参数
CXExprValueStd* CXExprErrorEx::GetExprValueStd()
{
	if (m_pValueStd == NULL)
	{
		m_pValueStd = new CXExprValueStd();
		AddNewChild(m_pValueStd);
	}

	return m_pValueStd;
}

//获取相对误差限
CXExprValueErrorRel* CXExprErrorEx::GetExprValueErrorRel()
{
	if (m_pErrorRel == NULL)
	{
		m_pErrorRel = new CXExprValueErrorRel();
		AddNewChild(m_pErrorRel);
	}

	return m_pErrorRel;
}

//获取绝对误差限
CXExprValueErrorAbs* CXExprErrorEx::GetExprValueErrorAbs()
{
	if (m_pErrorAbs == NULL)
	{
		m_pErrorAbs = new CXExprValueErrorAbs();
		AddNewChild(m_pErrorAbs);
	}

	return m_pErrorAbs;
}

//获取表达式计算结果（合格 or 不合格）
CXExprValueRslt* CXExprErrorEx::GetExprValueRslt()
{
	if (m_pValueRslt == NULL)
	{
		m_pValueRslt = new CXExprValueRslt();
		AddNewChild(m_pValueRslt);
	}

	return m_pValueRslt;
}

//获取相对误差计算值
CXExprValueErrorRelRslt* CXExprErrorEx::GetExprValueErrorRelRslt()
{
	if (m_pValueErrorRelRslt == NULL)
	{
		m_pValueErrorRelRslt = new CXExprValueErrorRelRslt();
		AddNewChild(m_pValueErrorRelRslt);
	}

	return m_pValueErrorRelRslt;
}

//获取绝对误差计算值
CXExprValueErrorAbsRslt* CXExprErrorEx::GetExprValueErrorAbsRslt()
{
	if (m_pValueErrorAbsRslt == NULL)
	{
		m_pValueErrorAbsRslt = new CXExprValueErrorAbsRslt();
		AddNewChild(m_pValueErrorAbsRslt);
	}

	return m_pValueErrorAbsRslt;
}