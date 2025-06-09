//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprValueCalEx.cpp  CXExprValueCalEx


#include "stdafx.h"
#include "XExprValueCalEx.h"
#include <math.h>

CXExprValueCalEx::CXExprValueCalEx()
{
	//初始化属性

	//初始化成员变量
	m_pValue1 = NULL;
	m_pValue2 = NULL;
	m_pValueCalRslt = NULL;
	m_pValueStd = NULL;
	m_pErrorRel = NULL;
	m_pErrorAbs = NULL;
	m_pValueRslt = NULL;
	m_pValueErrorRelRslt = NULL;
	m_pValueErrorAbsRslt = NULL;
}

CXExprValueCalEx::~CXExprValueCalEx()
{
}

long CXExprValueCalEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strMode);
	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strCalOptrKey, oNode, m_strCalOptr);
	return 0;
}

long CXExprValueCalEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strMode);
	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	xml_SetAttributeValue(pXmlKeys->m_strCalOptrKey, oElement, m_strCalOptr);
	return 0;
}

long CXExprValueCalEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CXExprBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_strCalOptr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMode);
		BinarySerializeRead(oBinaryBuffer, m_strOptr);
		BinarySerializeRead(oBinaryBuffer, m_strCalOptr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMode);
		BinarySerializeWrite(oBinaryBuffer, m_strOptr);
		BinarySerializeWrite(oBinaryBuffer, m_strCalOptr);
	}
	return 0;
}

void CXExprValueCalEx::InitAfterRead()
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
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUECALRSLT)
		{
			m_pValueCalRslt = (CXExprValueCalRslt*)p;
		}
	}

	//单独新建，全部为空
	if (m_pValue1 == NULL)
	{
		m_pValue1 = (CXExprValue1*)AddNewChild(new CXExprValue1());
	}

	if (m_pValue2 == NULL)
	{
		m_pValue2 = (CXExprValue2*)AddNewChild(new CXExprValue2());
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

	if (m_pValueCalRslt == NULL)
	{
		m_pValueCalRslt = (CXExprValueCalRslt *)AddNewChild(new CXExprValueCalRslt());
	}
}

BOOL CXExprValueCalEx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXExprBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXExprValueCalEx *p = (CXExprValueCalEx*)pObj;

	if(m_strMode != p->m_strMode)
	{
		return FALSE;
	}

	if(m_strOptr != p->m_strOptr)
	{
		return FALSE;
	}

	if(m_strCalOptr != p->m_strCalOptr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXExprValueCalEx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase::CopyOwn(pDest);
	CXExprValueCalEx *p = (CXExprValueCalEx*)pDest;

	p->m_strMode = m_strMode;
	p->m_strOptr = m_strOptr;
	p->m_strCalOptr = m_strCalOptr;
	return TRUE;
}

CBaseObject* CXExprValueCalEx::Clone()
{
	CXExprValueCalEx *p = new CXExprValueCalEx();
	Copy(p);
	return p;
}

CBaseObject* CXExprValueCalEx::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprValueCalEx *p = new CXExprValueCalEx();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprValueCalEx::CanPaste(UINT nClassID)
{
	if (nClassID == XEXPRCLASSID_CXEXPRVALUE1)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUE2)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUECALRSLT)
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

CExBaseObject* CXExprValueCalEx::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

	if (strClassID == CXExprXmlRWKeys::CXExprValueCalRsltKey())
	{
		m_pValueCalRslt = new CXExprValueCalRslt();
		return m_pValueCalRslt;
	}

	return pNew;
}

CExBaseObject* CXExprValueCalEx::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

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

	if (nClassID == XEXPRCLASSID_CXEXPRVALUECALRSLT)
	{
		m_pValueCalRslt = new CXExprValueCalRslt();
		return m_pValueCalRslt;
	}

	return pNew;
}

// long CXExprValueCalEx::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	m_pValueStd->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueStdKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValue->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pError->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprErrorKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueRslt->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueRsltKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 
// 	return 0;
// }

long CXExprValueCalEx::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	double dValStd = 0;
	double dValue1 = 0;
	double dValue2 = 0;
	double dErrorRel = 0;
	double dErrorAbs = 0;

	double dValueCal = 0;
	double dErrorCalRel = 0;
	double dErrorCalAbs = 0;
	m_nResult = 0;
	CString strValStd, strValue1, strValue2, strErrorRel, strErrorAbs;

	if ( !CalcEx(pExprParent, pCalInterface, dValStd, dValue1, dValue2, dErrorRel, dErrorAbs
		, strValStd, strValue1, strValue2, strErrorRel, strErrorAbs))
	{
		return 0;
	}

	dErrorRel = dErrorRel / 100.0;

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

	//将数据1与数据2的运算结果，存入运算结果对象
	CXExprValueCalRslt *pValueCalRslt = GetExprValueCalRslt();
	pValueCalRslt->m_strValue.Format(_T("%.3f"), dValueCal);
	//计算结束后，将结果绑定回对应的参数
	pValueCalRslt->ExprRsltBind(pExprParent, pCalInterface);

	if (m_strMode == _T("abs"))
	{
		m_nResult = Calc_Abs(dErrorCalAbs, dValStd, dValueCal, dErrorAbs);

		//将误差结果，存入误差结果数据对象
		CXExprValueErrorAbsRslt *pValueErrorAbsRslt = GetExprValueErrorAbsRslt();

		if (pValueErrorAbsRslt->IsValueUint_ms())
		{
			dErrorCalAbs *= 1000;
		}

		if (strValue1 == _T("未动作") || strValue2 == _T("未动作"))
		{
			pValueErrorAbsRslt->m_strValue = _T("--");
			m_nResult = 0;
		}
		else
		{
			pValueErrorAbsRslt->m_strValue.Format(_T("%.3f"), dErrorCalAbs);
		}

		//计算结束后，将结果绑定回对应的参数
		pValueErrorAbsRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
	else if (m_strMode == _T("real"))
	{
		m_nResult = Calc_Rel(dErrorCalRel, dValStd, dValueCal, dErrorRel);

		//将误差结果，存入误差结果数据对象
		CXExprValueErrorRelRslt *pValueErrorRelRslt = GetExprValueErrorRelRslt();

		if (strValue1 == _T("未动作") || strValue2 == _T("未动作"))
		{
			dErrorCalRel = -100.0;
			m_nResult = 0;
		}

		if (dValStd == 0.0 || strValue1 == _T("未动作") || strValue2 == _T("未动作"))
		{
			pValueErrorRelRslt->m_strValue = _T("--");
		}
		else
		{
			pValueErrorRelRslt->m_strValue.Format(_T("%.3f"), dErrorCalRel);
		}

		//计算结束后，将结果绑定回对应的参数
		pValueErrorRelRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
	else if (m_strMode == _T("or"))
	{
		m_nResult = Calc_Or(dErrorCalRel, dErrorCalAbs, dValStd, dValueCal, dErrorRel, dErrorAbs);

		//将误差结果，存入误差结果数据对象
		CXExprValueErrorRelRslt *pValueErrorRelRslt = GetExprValueErrorRelRslt();
		CXExprValueErrorAbsRslt *pValueErrorAbsRslt = GetExprValueErrorAbsRslt();

		if (pValueErrorAbsRslt->IsValueUint_ms())
		{
			dErrorCalAbs *= 1000;
		}

		if (strValue1 == _T("未动作") || strValue2 == _T("未动作"))
		{
			dErrorCalRel = -100.0;
			pValueErrorAbsRslt->m_strValue = _T("--");
			m_nResult = 0;
		}
		else
		{
			pValueErrorAbsRslt->m_strValue.Format(_T("%.3f"), dErrorCalAbs);
		}

		if (dValStd == 0.0 || strValue1 == _T("未动作") || strValue2 == _T("未动作"))
		{
			pValueErrorRelRslt->m_strValue = _T("--");
		}
		else
		{
			pValueErrorRelRslt->m_strValue.Format(_T("%.3f"), dErrorCalRel);
		}

		//计算结束后，将结果绑定回对应的参数
		pValueErrorRelRslt->ExprRsltBind(pExprParent, pCalInterface);
		pValueErrorAbsRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
	else if (m_strMode == _T("and"))
	{
		m_nResult = Calc_And(dErrorCalRel, dErrorCalAbs, dValStd, dValueCal, dErrorRel, dErrorAbs);

		//将误差结果，存入误差结果数据对象
		CXExprValueErrorRelRslt *pValueErrorRelRslt = GetExprValueErrorRelRslt();
		CXExprValueErrorAbsRslt *pValueErrorAbsRslt = GetExprValueErrorAbsRslt();

		if (pValueErrorAbsRslt->IsValueUint_ms())
		{
			dErrorCalAbs *= 1000;
		}

		if (strValue1 == _T("未动作") || strValue2 == _T("未动作"))
		{
			dErrorCalRel = -100.0;
			pValueErrorAbsRslt->m_strValue = _T("--");
			m_nResult = 0;
		}
		else
		{
			pValueErrorAbsRslt->m_strValue.Format(_T("%.3f"), dErrorCalAbs);
		}

		if (dValStd == 0.0 || strValue1 == _T("未动作") || strValue2 == _T("未动作"))
		{
			pValueErrorRelRslt->m_strValue = _T("--");
		}
		else
		{
			pValueErrorRelRslt->m_strValue.Format(_T("%.3f"), dErrorCalRel);
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
// 	if (m_pValue1 != NULL)
// 	{
// 		m_pValue1->ExprRsltBind(pExprParent, pCalInterface);
// 	}

	return m_nResult;
}


long CXExprValueCalEx::CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface
							  , double &dValStd, double &dValue1, double &dValue2, double &dErrRel, double &dErrAbs
							  , CString &strValStd, CString &strValue1, CString &strValue2, CString &strErrorRel, CString &strErrorAbs)
{
	if (! m_pValueStd->Calc(pExprParent, pCalInterface, dValStd, strValStd))
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

long CXExprValueCalEx::Calc_Abs(double &dCal, double dValStd, double dVal, double dErrAbs)
{
	long nRslt = 0;
	dCal = dVal - dValStd;

	if (m_strOptr == _T("<="))
	{
		//nRslt = (fabs(dCal) <= dErrAbs);
		nRslt = ( (fabs(dCal)) <= ( 0.0001 + dErrAbs) );
	}
	else if (m_strOptr == _T("<"))
	{
		//nRslt = (fabs(dCal) < dErrAbs);
		nRslt = ( (fabs(dCal)) < ( 0.0001 + dErrAbs) );
	}

	return nRslt;
}

long CXExprValueCalEx::Calc_Rel(double &dCal, double dValStd, double dVal, double dErrRel)
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
			}
			else if (m_strOptr == _T("<"))
			{
				nRslt = (dCalEx < dErrRel);
			}

			dCal = dCal * 100.0;
		}	
	}

	return nRslt;
}

long CXExprValueCalEx::Calc_Or(double &dErrorCalRel, double &dErrorCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs)
{
	long nRsltRel = Calc_Rel(dErrorCalRel, dValStd, dVal, dErrRel);
	long nRsltAbs = Calc_Abs(dErrorCalAbs, dValStd, dVal, dErrAbs);

	return ( nRsltAbs || nRsltRel);
}

long CXExprValueCalEx::Calc_And(double &dErrorCalRel, double &dErrorCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs)
{
	long nRsltRel = Calc_Rel(dErrorCalRel, dValStd, dVal, dErrRel);
	long nRsltAbs = Calc_Abs(dErrorCalAbs, dValStd, dVal, dErrAbs);

	return ( nRsltAbs && nRsltRel);
}

void CXExprValueCalEx::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
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

	if (m_strMode == _T("abs"))
	{
		if (m_pValueErrorAbsRslt != NULL)
		{
			m_pValueErrorAbsRslt->ExprRsltBind(pExprParent, pCalInterface);
		}
	}
	else if (m_strMode == _T("real"))
	{
		if (m_pValueErrorRelRslt != NULL)
		{
			m_pValueErrorRelRslt->ExprRsltBind(pExprParent, pCalInterface);
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

	if (m_pValueCalRslt != NULL)
	{
		m_pValueCalRslt->ExprRsltBind(pExprParent, pCalInterface);
	}
}

void CXExprValueCalEx::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	if (m_pValue1 != NULL)
	{
		m_pValue1->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValue2 != NULL)
	{
		m_pValue2->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueStd != NULL)
	{
		m_pValueStd->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueCalRslt != NULL)
	{
		m_pValueCalRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
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

		return;
	}

	if (m_strMode == _T("real"))
	{
		if (m_pErrorRel != NULL)
		{
			m_pErrorRel->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pValueErrorRelRslt != NULL)
		{
			m_pValueErrorRelRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		return;
	}

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

	GetRsltExprValues_ExprMode(m_strMode, pRsltExprValues);
}

BOOL CXExprValueCalEx::GetValueName(const CString &strID, CString &strName)
{
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

	if (m_pValueCalRslt != NULL)
	{
		if (m_pValueCalRslt->GetValueName(strID, strName))
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

//获取结果参数1
CXExprValue1* CXExprValueCalEx::GetExprValue1()
{
	if (m_pValue1 == NULL)
	{
		m_pValue1 = new CXExprValue1();
		AddNewChild(m_pValue1);
	}

	return m_pValue1;
}

//获取结果参数2
CXExprValue2* CXExprValueCalEx::GetExprValue2()
{
	if (m_pValue2 == NULL)
	{
		m_pValue2 = new CXExprValue2();
		AddNewChild(m_pValue2);
	}

	return m_pValue2;
}

//获取结果参数1与结果参数2的数据运算结果
CXExprValueCalRslt* CXExprValueCalEx::GetExprValueCalRslt()
{
	if (m_pValueCalRslt == NULL)
	{
		m_pValueCalRslt = new CXExprValueCalRslt();
		AddNewChild(m_pValueCalRslt);
	}

	return m_pValueCalRslt;
}

//获取基准参数
CXExprValueStd* CXExprValueCalEx::GetExprValueStd()
{
	if (m_pValueStd == NULL)
	{
		m_pValueStd = new CXExprValueStd();
		AddNewChild(m_pValueStd);
	}

	return m_pValueStd;
}

//获取相对误差限
CXExprValueErrorRel* CXExprValueCalEx::GetExprValueErrorRel()
{
	if (m_pErrorRel == NULL)
	{
		m_pErrorRel = new CXExprValueErrorRel();
		AddNewChild(m_pErrorRel);
	}

	return m_pErrorRel;
}

//获取绝对误差限
CXExprValueErrorAbs* CXExprValueCalEx::GetExprValueErrorAbs()
{
	if (m_pErrorAbs == NULL)
	{
		m_pErrorAbs = new CXExprValueErrorAbs();
		AddNewChild(m_pErrorAbs);
	}

	return m_pErrorAbs;
}

//获取表达式计算结果（合格 or 不合格）
CXExprValueRslt* CXExprValueCalEx::GetExprValueRslt()
{
	if (m_pValueRslt == NULL)
	{
		m_pValueRslt = new CXExprValueRslt();
		AddNewChild(m_pValueRslt);
	}

	return m_pValueRslt;
}

//获取相对误差值（相对误差计算结果）
CXExprValueErrorRelRslt* CXExprValueCalEx::GetExprValueErrorRelRslt()
{
	if (m_pValueErrorRelRslt == NULL)
	{
		m_pValueErrorRelRslt = new CXExprValueErrorRelRslt();
		AddNewChild(m_pValueErrorRelRslt);
	}

	return m_pValueErrorRelRslt;
}

//获取绝对误差值（绝对误差计算结果）
CXExprValueErrorAbsRslt* CXExprValueCalEx::GetExprValueErrorAbsRslt()
{
	if (m_pValueErrorAbsRslt == NULL)
	{
		m_pValueErrorAbsRslt = new CXExprValueErrorAbsRslt();
		AddNewChild(m_pValueErrorAbsRslt);
	}

	return m_pValueErrorAbsRslt;
}