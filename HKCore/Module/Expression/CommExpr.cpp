//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CommExpr.cpp  CCommExpr


#include "stdafx.h"
#include "CommExpr.h"
#include "OleAuto.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCommExpr::CCommExpr()
{
	//初始化属性

	//初始化成员变量
}

CCommExpr::~CCommExpr()
{
}

long CCommExpr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCommExprXmlRWKeys *pXmlKeys = (CCommExprXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strOptrKey, oNode, m_strOptr);
	return 0;
}

long CCommExpr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCommExprXmlRWKeys *pXmlKeys = (CCommExprXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strOptrKey, oElement, m_strOptr);
	return 0;
}

long CCommExpr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strOptr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strOptr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strOptr);
	}
	return 0;
}

void CCommExpr::InitAfterRead()
{
}

BOOL CCommExpr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCommExpr *p = (CCommExpr*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strOptr != p->m_strOptr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCommExpr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCommExpr *p = (CCommExpr*)pDest;

	p->m_strID = m_strID;
	p->m_strValue = m_strValue;
	p->m_strOptr = m_strOptr;
	return TRUE;
}

CBaseObject* CCommExpr::Clone()
{
	CCommExpr *p = new CCommExpr();
	Copy(p);
	return p;
}

CBaseObject* CCommExpr::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CCommExpr *p = new CCommExpr();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CCommExpr::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CCOMMEXPR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCommExpr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCommExprXmlRWKeys *pXmlKeys = (CCommExprXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCCommExprKey)
	{
		pNew = new CCommExpr();
	}

	return pNew;
}

CExBaseObject* CCommExpr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == MNGRCLASSID_CCOMMEXPR)
	{
		pNew = new CCommExpr();
	}

	return pNew;
}

CCommExpr *CCommExpr::FindByOptr(const CString &strOptr)
{
	POS pos = GetHeadPosition();
	CCommExpr *p = NULL;

	while(pos != NULL)
	{
		p = (CCommExpr *)GetNext(pos);

		if (p->m_strOptr == strOptr)
		{
			return p;
		}
	}

	return NULL;
}

BOOL CCommExpr::HasOrderLimitOptr()
{
	POS pos = GetHeadPosition();
	CCommExpr *p = NULL;

	while(pos != NULL)
	{
		p = (CCommExpr *)GetNext(pos);

		if ((p->m_strOptr == COMM_EXPR_OPTR_Desc)
			|| (p->m_strOptr == COMM_EXPR_OPTR_Asc)
			|| (p->m_strOptr == COMM_EXPR_OPTR_limit))
		{
			return TRUE;
		}
	}

	return FALSE;
}

CCommExpr *CCommExpr::AddExpr(const CString &strID,const CString &strValue,const CString &strOptr)
{
	CCommExpr *pNew = new CCommExpr;
	pNew->m_strID = strID;
	pNew->m_strValue.Format(_T("\'%s\'"),strValue);
	pNew->m_strOptr = strOptr;
	AddNewChild(pNew);
	return pNew;
}

CCommExpr *CCommExpr::AddLikeExpr(const CString &strID,const CString &strValue)
{
	CCommExpr *pNew = new CCommExpr;
	pNew->m_strID = strID;
	pNew->m_strValue = strValue;
	pNew->m_strOptr = COMM_EXPR_OPTR_like;
	AddNewChild(pNew);
	return pNew;
}

CCommExpr *CCommExpr::AddOrderExpr(const CString &strValue,const CString &strOptr)
{
	CCommExpr *pNew = new CCommExpr;
	pNew->m_strID = _T("");
	pNew->m_strValue = strValue;
	pNew->m_strOptr = strOptr;
	AddNewChild(pNew);
	return pNew;
}

CCommExpr *CCommExpr::AddExpr(const CString &strID,long nValue,const CString &strOptr)
{
	CCommExpr *pNew = new CCommExpr;
	pNew->m_strID = strID;
	pNew->m_strValue.Format(_T("%d"),nValue);
	pNew->m_strOptr = strOptr;
	AddNewChild(pNew);
	return pNew;
}

CCommExpr *CCommExpr::AddExpr(const CString &strID,double fValue,const CString &strOptr,long nDecimal)
{
	CCommExpr *pNew = new CCommExpr;
	CString strFormat;
	if (nDecimal <= 0)
	{
		strFormat = (_T("%%d"));
	}
	else
	{
		strFormat.Format(_T("%%.%df"),nDecimal);
	}
	
	pNew->m_strID = strID;
	pNew->m_strValue.Format(strFormat,fValue);
	pNew->m_strOptr = strOptr;
	AddNewChild(pNew);
	return pNew;
}

CCommExpr *CCommExpr::AddExpr(const CString &strID,SYSTEMTIME &tm,const CString &strOptr,BOOL bDate)
{
	CString strTime;
	if(bDate)
	{
		SystemTime_To_ShortString(tm,strTime);
	}
	else
	{
		SystemTime_To_String(tm,strTime);
	}

	return AddExpr(strID,strTime,strOptr);
}

BOOL CCommExpr::CheckFilterExpr()
{
	CCommExpr *pLimitExpr = FindByOptr(COMM_EXPR_OPTR_limit);
	CCommExpr *pDescExpr = FindByOptr(COMM_EXPR_OPTR_Desc);
	CCommExpr *pAscExpr = FindByOptr(COMM_EXPR_OPTR_Asc);

	if ((pDescExpr != NULL) && (pAscExpr != NULL))
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("过滤条件Desc和Asc同时存在！"));
		return FALSE;
	}

	CCommExpr *pDescAscExpr = pDescExpr;
	if (pDescExpr == NULL)
	{
		pDescAscExpr = pAscExpr;
	}

	if (pLimitExpr != NULL)
	{
		if (GetTail() != pLimitExpr)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("过滤条件Limit不在最后！"));
			return FALSE;
		}

		if (pDescAscExpr != NULL)
		{
			if (GetAt(GetCount()-2) != pDescAscExpr)
			{
				CLogPrint::LogString(XLOGLEVEL_INFOR,_T("当过滤条件Limit存在：条件Desc/Asc不在倒数第二位！"));
				return FALSE;
			}
		}
	}
	else if (pDescAscExpr != NULL)
	{
		if (GetTail() != pDescAscExpr)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("当过滤条件Limit不存在：条件Desc/Asc不在最后！"));
			return FALSE;
		}
	}

	return TRUE;
}

//解析对象，生成过滤条件
BOOL CCommExpr::AnalysisFilterExpr(CString &strFilterExpr)
{
	CString strExpr = _T("");
	strFilterExpr = _T("");

	if(m_strOptr == COMM_EXPR_OPTR_and || m_strOptr == COMM_EXPR_OPTR_or)
	{
		POS pos = GetHeadPosition();
		CCommExpr *p = NULL;

		while(pos != NULL)
		{
			p = (CCommExpr *)GetNext(pos);

			if (!p->AnalysisFilterExpr(strExpr))
			{
				return FALSE;
			}

			if (strFilterExpr.IsEmpty())
			{
				if (!HasOrderLimitOptr())
				{
					strFilterExpr = _T("(");
				}
				strFilterExpr.AppendFormat(_T("%s"),strExpr);
			}
			else
			{
				if ((p->m_strOptr == COMM_EXPR_OPTR_Desc)
					|| (p->m_strOptr == COMM_EXPR_OPTR_Asc)
					|| (p->m_strOptr == COMM_EXPR_OPTR_limit))
				{
					strFilterExpr.AppendFormat(_T(" %s"),strExpr);
				}
				else
				{
					strFilterExpr.AppendFormat(_T(" %s %s"),m_strOptr,strExpr);
				}
			}
		}

		if (!HasOrderLimitOptr())
		{
			strFilterExpr = strFilterExpr + _T(")");
		}	
	}
	else if ((m_strOptr == COMM_EXPR_OPTR_Equal)
		|| (m_strOptr == COMM_EXPR_OPTR_NotEqual)
		|| (m_strOptr == COMM_EXPR_OPTR_Greater)
		|| (m_strOptr == COMM_EXPR_OPTR_GreaterEqual)
		|| (m_strOptr == COMM_EXPR_OPTR_Lower)
		|| (m_strOptr == COMM_EXPR_OPTR_LowerEqual))
	{
		strFilterExpr.Format(_T("(%s%s%s)"),m_strID,m_strOptr,m_strValue);
	}
	else if (m_strOptr == COMM_EXPR_OPTR_like)
	{
		strFilterExpr.Format(_T("(%s like \'%%%s%%\')"),m_strID,m_strValue);
	}
	else if ((m_strOptr == COMM_EXPR_OPTR_Desc)
		|| (m_strOptr == COMM_EXPR_OPTR_Asc))
	{
		strFilterExpr.Format(_T("Order by %s %s"),m_strValue,m_strOptr);
	}
	else if (m_strOptr == COMM_EXPR_OPTR_limit)
	{
		strFilterExpr.Format(_T("limit %s"),m_strValue);
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCommExpr::AnalysisFilterExpr(const CString &strFilterExpr,CString &strFilter)
{
	if (strFilterExpr.IsEmpty())
	{
		strFilter = _T("");
		return TRUE;
	}

	BSTR bstrText = strFilterExpr.AllocSysString();
	BOOL bRet = SetXml(bstrText, CCommExprXmlRWKeys::g_pXmlKeys);
	::SysFreeString(bstrText); // 用完释放

	if (!bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("SetXml fail"));
		return FALSE;
	}

	if (!CheckFilterExpr())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CheckFilterExpr fail"));
		return FALSE;
	}

	if (!AnalysisFilterExpr(strFilter))
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("AnalysisFilterExpr fail"));
		return FALSE;
	}

	return TRUE;
}

BOOL CCommExpr::GenerateQuerySql(const CString &strTable,CString &strSql)
{
	if (!CheckFilterExpr())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CheckFilterExpr fail"));
		return FALSE;
	}

	CString strFilter = _T("");
	if (!AnalysisFilterExpr(strFilter))
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("AnalysisFilterExpr fail"));
		return FALSE;
	}

	if (GetCount() == 1)
	{
		CCommExpr *p = (CCommExpr *)GetHead();
		if ((p->m_strOptr == COMM_EXPR_OPTR_Desc)
			|| (p->m_strOptr == COMM_EXPR_OPTR_Asc)
			|| (p->m_strOptr == COMM_EXPR_OPTR_limit))
		{
			strSql.Format(_T("select * from %s %s"),strTable,strFilter);
			return TRUE;
		}
	}
	else if (GetCount() == 2)
	{
		CCommExpr *p1 = (CCommExpr *)GetHead();
		CCommExpr *p2 = (CCommExpr *)GetTail();
		if (((p1->m_strOptr == COMM_EXPR_OPTR_Desc) || (p1->m_strOptr == COMM_EXPR_OPTR_Asc))
			&& (p2->m_strOptr == COMM_EXPR_OPTR_limit))
		{
			strSql.Format(_T("select * from %s %s"),strTable,strFilter);
			return TRUE;
		}
	}

	strSql.Format(_T("select * from %s where %s"),strTable,strFilter);

	return TRUE;
}

BOOL CCommExpr::GenerateDeleteSql(const CString &strTable,CString &strSql)
{
	if (!CheckFilterExpr())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CheckFilterExpr fail"));
		return FALSE;
	}

	CString strFilter = _T("");
	if (!AnalysisFilterExpr(strFilter))
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("AnalysisFilterExpr fail"));
		return FALSE;
	}

	strSql.Format(_T("delete from %s where %s"),strTable,strFilter);

	return TRUE;
}

BOOL CommExpr_GenerateQuerySql(const CString &strTable,const CString &strFilterExpr,CString &strSql)
{
	if (strTable.IsEmpty())
	{
		return FALSE;
	}

	if (strFilterExpr.IsEmpty())
	{
		strSql.Format(_T("select * from %s"),strTable);
		return TRUE;
	}

	CCommExpr oCommExpr;
	BSTR bstrText = strFilterExpr.AllocSysString();
	BOOL bRet = oCommExpr.SetXml(bstrText, CCommExprXmlRWKeys::g_pXmlKeys);
	SysFreeString(bstrText); // 用完释放

	return oCommExpr.GenerateQuerySql(strTable,strSql);
}

BOOL CommExpr_GenerateDeleteSql(const CString &strTable,const CString &strFilterExpr,CString &strSql)
{
	if (strTable.IsEmpty())
	{
		return FALSE;
	}

	if (strFilterExpr.IsEmpty())
	{
		strSql.Format(_T("delete from %s"),strTable);
		return TRUE;
	}

	CCommExpr oCommExpr;
	BSTR bstrText = strFilterExpr.AllocSysString();
	BOOL bRet = oCommExpr.SetXml(bstrText, CCommExprXmlRWKeys::g_pXmlKeys);
	SysFreeString(bstrText); // 用完释放

	return oCommExpr.GenerateDeleteSql(strTable,strSql);
}