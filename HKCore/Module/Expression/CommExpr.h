//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CommExpr.h  CCommExpr

#pragma once

#include "CommExprGlobal.h"

#define COMM_EXPR_OPTR_and				_T("and")
#define COMM_EXPR_OPTR_or				_T("or")
#define COMM_EXPR_OPTR_Desc				_T("Desc")
#define COMM_EXPR_OPTR_Asc				_T("Asc")
#define COMM_EXPR_OPTR_limit			_T("limit")
#define COMM_EXPR_OPTR_Equal			_T("=")
#define COMM_EXPR_OPTR_NotEqual			_T("!=")
#define COMM_EXPR_OPTR_Greater			_T(">")
#define COMM_EXPR_OPTR_GreaterEqual		_T(">=")
#define COMM_EXPR_OPTR_Lower			_T("<")
#define COMM_EXPR_OPTR_LowerEqual		_T("<=")
#define COMM_EXPR_OPTR_like				_T("like")



class CCommExpr : public CExBaseList
{
public:
	CCommExpr();
	virtual ~CCommExpr();


	CString  m_strValue;
	CString  m_strOptr;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CCOMMEXPR;   }
	virtual BSTR GetXmlElementKey()  {      return CCommExprXmlRWKeys::CCommExprKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	CCommExpr *AddExpr(const CString &strID,const CString &strValue,const CString &strOptr);
	CCommExpr *AddLikeExpr(const CString &strID,const CString &strValue);
	CCommExpr *AddOrderExpr(const CString &strValue,const CString &strOptr);
	CCommExpr *AddExpr(const CString &strID,long nValue,const CString &strOptr);
	CCommExpr *AddExpr(const CString &strID,double fValue,const CString &strOptr,long nDecimal=3);
	CCommExpr *AddExpr(const CString &strID,SYSTEMTIME &tm,const CString &strOptr,BOOL bDate=FALSE);	

	CCommExpr *FindByOptr(const CString &strOptr);
	BOOL HasOrderLimitOptr();

	//解析对象，生成过滤条件
	BOOL CheckFilterExpr();
	BOOL AnalysisFilterExpr(CString &strFilterExpr);
	BOOL AnalysisFilterExpr(const CString &strFilterExpr,CString &strFilter);

	BOOL GenerateQuerySql(const CString &strTable,CString &strSql);
	BOOL GenerateDeleteSql(const CString &strTable,CString &strSql);
};

BOOL CommExpr_GenerateQuerySql(const CString &strTable,const CString &strFilterExpr,CString &strSql);
BOOL CommExpr_GenerateDeleteSql(const CString &strTable,const CString &strFilterExpr,CString &strSql);