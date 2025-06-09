//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprErrorEx_I.cpp  CXExprErrorEx_I


#include "stdafx.h"
#include "XExprErrorEx_I.h"
#include <math.h>

CXExprErrorEx_I::CXExprErrorEx_I()
{
	//初始化属性

	//初始化成员变量
	m_pValue = NULL;
	m_pValueStd = NULL;
	m_pErrorRel = NULL;
	m_pErrorAbs_P = NULL;
	m_pErrorAbs_N = NULL;
	m_pValueRslt = NULL;
	m_pValueErrorRelRslt = NULL;
	m_pValueErrorAbsRslt = NULL;
}

CXExprErrorEx_I::~CXExprErrorEx_I()
{
}

long CXExprErrorEx_I::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strMode);
	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	return 0;
}

long CXExprErrorEx_I::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXExprXmlRWKeys *pXmlKeys = CXExprXmlRWKeys::g_pXmlKeys;
	CXExprBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strMode);
	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	return 0;
}

long CXExprErrorEx_I::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXExprErrorEx_I::InitAfterRead()
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
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABS_P)
		{
			m_pErrorAbs_P = (CXExprValueErrorAbs_P*)p;
		}
		else if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABS_N)
		{
			m_pErrorAbs_N = (CXExprValueErrorAbs_N*)p;
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

	if (m_pErrorAbs_P == NULL)
	{
		m_pErrorAbs_P = (CXExprValueErrorAbs_P*)AddNewChild(new CXExprValueErrorAbs_P());
	}

	if (m_pErrorAbs_N == NULL)
	{
		m_pErrorAbs_N = (CXExprValueErrorAbs_N*)AddNewChild(new CXExprValueErrorAbs_N());
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

BOOL CXExprErrorEx_I::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CXExprBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXExprErrorEx_I *p = (CXExprErrorEx_I*)pObj;

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

BOOL CXExprErrorEx_I::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXExprBase::CopyOwn(pDest);
	CXExprErrorEx_I *p = (CXExprErrorEx_I*)pDest;

	p->m_strMode = m_strMode;
	p->m_strOptr = m_strOptr;
	return TRUE;
}

CBaseObject* CXExprErrorEx_I::Clone()
{
	CXExprErrorEx_I *p = new CXExprErrorEx_I();
	Copy(p);
	return p;
}

CBaseObject* CXExprErrorEx_I::CloneEx(BOOL bCopyOwn, BOOL bCopyChildren)
{
	CXExprErrorEx_I *p = new CXExprErrorEx_I();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXExprErrorEx_I::CanPaste(UINT nClassID)
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

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABS_P)
	{
		return TRUE;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABS_N)
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

CExBaseObject* CXExprErrorEx_I::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

	if (strClassID == CXExprXmlRWKeys::CXExprValueErrorAbs_PKey())
	{
		m_pErrorAbs_P = new CXExprValueErrorAbs_P();
		return m_pErrorAbs_P;
	}

	if (strClassID == CXExprXmlRWKeys::CXExprValueErrorAbs_NKey())
	{
		m_pErrorAbs_N = new CXExprValueErrorAbs_N();
		return m_pErrorAbs_N;
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

CExBaseObject* CXExprErrorEx_I::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABS_P)
	{
		m_pErrorAbs_P = new CXExprValueErrorAbs_P();
		return m_pErrorAbs_P;
	}

	if (nClassID == XEXPRCLASSID_CXEXPRVALUEERRORABS_N)
	{
		m_pErrorAbs_N = new CXExprValueErrorAbs_N();
		return m_pErrorAbs_N;
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

// long CXExprErrorEx_I::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	m_pValueStd->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprValueStdKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValue->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pError->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::CXExprErrorEx_IKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 	m_pValueRslt->XmlWrite(oXMLDoc, oElement, CXExprXmlRWKeys::ValueRsltKey(), CXExprXmlRWKeys::g_pXmlKeys);
// 
// 	return 0;
// }

long CXExprErrorEx_I::Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	CXExprValueRslt* pRslt = GetExprValueRslt();

	if (m_strMode == _T("not"))
	{
		//不评估，默认合格
		m_nResult = 1;
		pRslt->m_strValue = _T("2");
		pRslt->ExprRsltBind(pExprParent, pCalInterface);
		return 1;
	}

	double dValStd = 0;
	double dValue = 0;
	double dErrorRel = 0;
	double dErrorAbs_P = 0;
	double dErrorAbs_N = 0;
	double dCalRel = 0;
	double dCalAbs = 0;
	m_nResult = 0;
	CString strValStd, strValue, strErrorRel, strErrorAbs_P, strErrorAbs_N;
	
	if ( !CalcEx(pExprParent, pCalInterface, dValStd, dValue, dErrorRel, dErrorAbs_P, dErrorAbs_N
		, strValStd, strValue, strErrorRel, strErrorAbs_P, strErrorAbs_N))
	{
		return 0;
	}

	dErrorRel = dErrorRel / 100.0;

	if (m_strMode == _T("abs"))
	{
		m_nResult = Calc_Abs(dCalAbs, dValStd, dValue, dErrorAbs_P, dErrorAbs_N);

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

		if (dCalRel == -100.0)
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
		m_nResult = Calc_Combined(dCalAbs, dValStd, dValue, dErrorRel, dErrorAbs_P, dErrorAbs_N);

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
		m_nResult = Calc_Or(dCalRel, dCalAbs, dValStd, dValue, dErrorRel, dErrorAbs_P, dErrorAbs_N);

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

		if (dCalRel == -100.0)
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
		m_nResult = Calc_And(dCalRel, dCalAbs, dValStd, dValue, dErrorRel, dErrorAbs_P, dErrorAbs_N);

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

		if (dCalRel == -100.0)
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
	else if (m_strMode == _T("notact"))
	{
		//未动作 | 不动作。不进行误差计算，直接判结果数据是否大于0。（当成cmp逻辑处理）
		//应用场景：例如距离保护1.05倍，可靠不动作时。
		m_nResult = Calc_NotAct(dValue);
	}

	//计算结束后，将结果绑定回对应的参数
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

long CXExprErrorEx_I::CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, double &dValStd, double &dVal, double &dErrRel, double &dErrAbs_P, double &dErrAbs_N
						   , CString &strValStd, CString &strValue, CString &strErrorRel, CString &strErrorAbs_P, CString &strErrorAbs_N)
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
		bool bRet1 = m_pErrorAbs_P->Calc(pExprParent, pCalInterface, dErrAbs_P, strErrorAbs_P);
		bool bRet2 = m_pErrorAbs_N->Calc(pExprParent, pCalInterface, dErrAbs_N, strErrorAbs_N);
		return (bRet1 & bRet2);
	}

	if (m_strMode == _T("real"))
	{
		return m_pErrorRel->Calc(pExprParent, pCalInterface, dErrRel, strErrorRel);
	}

	if (! m_pErrorRel->Calc(pExprParent, pCalInterface, dErrRel, strErrorRel))
	{
		return 0;
	}

	if (! m_pErrorAbs_P->Calc(pExprParent, pCalInterface, dErrAbs_P, strErrorAbs_P))
	{
		return 0;
	}

	if (! m_pErrorAbs_N->Calc(pExprParent, pCalInterface, dErrAbs_N, strErrorAbs_N))
	{
		return 0;
	}

	return 1;
}

/*
误差 = 实测值 - 整定值。正误差限和负误差限，均为正值
1、误差 = 0 时，合格。
2、误差 > 0 时，误差判定小于正误差，为合格
3、误差 < 0 时，误差的绝对值判定小于负误差，为合格
*/
long CXExprErrorEx_I::Calc_Abs(double &dCal, double dValStd, double dVal, double dErrAbs_P, double dErrAbs_N)
{
	long nRslt = 0;
	dCal = dVal - dValStd;

	if (dCal == 0)
	{
		return 1;
	}
	else if (dCal < 0)
	{
		if (m_strOptr == _T("<="))
		{
			nRslt = ( (fabs(dCal)) <= ( 0.0001 + dErrAbs_N) );
		}
		else if (m_strOptr == _T("<"))
		{
			nRslt = ( (fabs(dCal)) < ( 0.0001 + dErrAbs_N) );
		}
	}
	else
	{
		if (m_strOptr == _T("<="))
		{
			nRslt = ( dCal <= ( 0.0001 + dErrAbs_P) );
		}
		else if (m_strOptr == _T("<"))
		{
			nRslt = ( dCal < ( 0.0001 + dErrAbs_P) );
		}
	}

	return nRslt;
}

long CXExprErrorEx_I::Calc_Rel(double &dCal, double dValStd, double dVal, double dErrRel)
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

long CXExprErrorEx_I::Calc_Or(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs_P, double dErrAbs_N)
{
	long nRsltRel = Calc_Rel(dCalRel, dValStd, dVal, dErrRel);
	long nRsltAbs = Calc_Abs(dCalAbs, dValStd, dVal, dErrAbs_P, dErrAbs_N);

	return ( nRsltAbs || nRsltRel);
}

long CXExprErrorEx_I::Calc_And(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs_P, double dErrAbs_N)
{
	long nRsltRel = Calc_Rel(dCalRel, dValStd, dVal, dErrRel);
	long nRsltAbs = Calc_Abs(dCalAbs, dValStd, dVal, dErrAbs_P, dErrAbs_N);

	return ( nRsltAbs && nRsltRel);
}

/* 组合误差
误差 = 实测值 - 整定值。正误差限和负误差限，均为正值
1、误差 = 0 时，直接判定合格。
2、误差 > 0 时，Limit = 基准值 * 相对误差限 + 绝对误差限正值
3、误差 < 0 时，Limit = 基准值 * 相对误差限 + 绝对误差限负值
4、误差取绝对值后，与Limit比，判定是否合格
*/
long CXExprErrorEx_I::Calc_Combined(double &dCal, double dValStd, double dVal, double dErrRel, double dErrAbs_P, double dErrAbs_N)
{
	long nRslt = 0;
	dCal = dVal - dValStd;
	double dLimit = dValStd * dErrRel;

	if(dCal < 0)
	{
		dLimit += dErrAbs_N;
	}
	else
	{
		dLimit += dErrAbs_P;
	}	

	if (dCal == 0)
	{
		nRslt = 1;
	}
	else 
	{
		if (m_strOptr == _T("<="))
		{
			//nRslt = (fabs(dCal) <= dLimit);
			nRslt = ( (fabs(dCal)) <= (0.0001 + dLimit) );
		}
		else if (m_strOptr == _T("<"))
		{
			//nRslt = (fabs(dCal) < dLimit);
			nRslt = ( (fabs(dCal)) <= (0.0001 + dLimit) );
		}
	}

	return nRslt;
}

//未动作 | 不动作。当成是cmp特殊处理，固定判定动作时间 < 0.001为合格
long CXExprErrorEx_I::Calc_NotAct(double dVal)
{
	long nRslt = ( dVal < 0.0001);
	return nRslt;
}

void CXExprErrorEx_I::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
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

	if (m_strMode == _T("not"))
	{
		//不评估
		if (m_pValueRslt != NULL)
		{
			m_pValueRslt->m_strValue = _T("2");
			m_pValueRslt->ExprRsltBind(pExprParent, pCalInterface);
		}

		return;
	}

	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->ExprRsltBind(pExprParent, pCalInterface);
	}

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
	else if(m_strMode == _T("notact"))
	{
		//未动作 | 不动作。当成cmp处理，不用回绑
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

void CXExprErrorEx_I::GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues)
{
	GetRsltExprValues_ExprMode(m_strMode, pRsltExprValues);

	if (m_pValue != NULL)
	{
		m_pValue->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_pValueStd != NULL)
	{
		m_pValueStd->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_strMode == _T("not"))
	{
		//不评估
		if (m_pValueRslt != NULL)
		{
			m_pValueRslt->m_strValue = _T("2");
			m_pValueRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		return;
	}

	if (m_pValueRslt != NULL)
	{
		m_pValueRslt->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
	}

	if (m_strMode == _T("abs"))
	{
		if (m_pErrorAbs_P != NULL)
		{
			m_pErrorAbs_P->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pErrorAbs_N != NULL)
		{
			m_pErrorAbs_N->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
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
		if (m_pErrorAbs_P != NULL)
		{
			m_pErrorAbs_P->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pErrorAbs_N != NULL)
		{
			m_pErrorAbs_N->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
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
	else if (m_strMode == _T("notact"))
	{
		//不动作 | 未动作。当成cmp处理，不存在误差计算。因此不用返回误差限、误差结果信息
	}
	else
	{
		if (m_pErrorAbs_P != NULL)
		{
			m_pErrorAbs_P->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
		}

		if (m_pErrorAbs_N != NULL)
		{
			m_pErrorAbs_N->GetRsltExprValues(pExprParent, pReportValues, pCalInterface, pRsltExprValues, pListXExprValues);
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
}

BOOL CXExprErrorEx_I::GetValueName(const CString &strID, CString &strName)
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

	if (m_pErrorAbs_P != NULL)
	{
		if (m_pErrorAbs_P->GetValueName(strID, strName))
		{
			return TRUE;
		}
	}

	if (m_pErrorAbs_N != NULL)
	{
		if (m_pErrorAbs_N->GetValueName(strID, strName))
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
CXExprValue* CXExprErrorEx_I::GetExprValue()
{
	if (m_pValue == NULL)
	{
		m_pValue = new CXExprValue();
		AddNewChild(m_pValue);
	}

	return m_pValue;
}

//获取基准参数
CXExprValueStd* CXExprErrorEx_I::GetExprValueStd()
{
	if (m_pValueStd == NULL)
	{
		m_pValueStd = new CXExprValueStd();
		AddNewChild(m_pValueStd);
	}

	return m_pValueStd;
}

//获取相对误差限
CXExprValueErrorRel* CXExprErrorEx_I::GetExprValueErrorRel()
{
	if (m_pErrorRel == NULL)
	{
		m_pErrorRel = new CXExprValueErrorRel();
		AddNewChild(m_pErrorRel);
	}

	return m_pErrorRel;
}

//获取绝对误差限：误差正值
CXExprValueErrorAbs_P* CXExprErrorEx_I::GetExprValueErrorAbs_P()
{
	if (m_pErrorAbs_P == NULL)
	{
		m_pErrorAbs_P = new CXExprValueErrorAbs_P();
		AddNewChild(m_pErrorAbs_P);
	}

	return m_pErrorAbs_P;
}

//获取绝对误差限：误差负值
CXExprValueErrorAbs_N* CXExprErrorEx_I::GetExprValueErrorAbs_N()
{
	if (m_pErrorAbs_N == NULL)
	{
		m_pErrorAbs_N = new CXExprValueErrorAbs_N();
		AddNewChild(m_pErrorAbs_N);
	}

	return m_pErrorAbs_N;
}

//获取表达式计算结果（合格 or 不合格）
CXExprValueRslt* CXExprErrorEx_I::GetExprValueRslt()
{
	if (m_pValueRslt == NULL)
	{
		m_pValueRslt = new CXExprValueRslt();
		AddNewChild(m_pValueRslt);
	}

	return m_pValueRslt;
}

//获取相对误差计算值
CXExprValueErrorRelRslt* CXExprErrorEx_I::GetExprValueErrorRelRslt()
{
	if (m_pValueErrorRelRslt == NULL)
	{
		m_pValueErrorRelRslt = new CXExprValueErrorRelRslt();
		AddNewChild(m_pValueErrorRelRslt);
	}

	return m_pValueErrorRelRslt;
}

//获取绝对误差计算值
CXExprValueErrorAbsRslt* CXExprErrorEx_I::GetExprValueErrorAbsRslt()
{
	if (m_pValueErrorAbsRslt == NULL)
	{
		m_pValueErrorAbsRslt = new CXExprValueErrorAbsRslt();
		AddNewChild(m_pValueErrorAbsRslt);
	}

	return m_pValueErrorAbsRslt;
}