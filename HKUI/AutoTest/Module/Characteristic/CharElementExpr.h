//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementExpr.h  CcharElementExpr

#pragma once
#include "CharElement.h"
#include "CharInterfaceVariable.h"

#define XRIO_CHARACTER_DIFF_EXPR_FIRST                  _T("(2*(S1/100-S2/100)*B1^2*B2^2/(B1-B2)^3)+((S2/100*B1*(B1^2+B1*B2+4*B2^2)-S1/100*B2*(4*B1^2+B1*B2+B2^2))/(B1-B2)^3*X)+(2*(S1/100-S2/100)*(B1^2+B1*B2+B2^2)/(B1-B2)^3*X^2)+((S2/100-S1/100)*(B1+B2)/(B1-B2)^3*X^3)")
#define XRIO_CHARACTER_DIFF_EXPR_SECOND                 _T("Diff-Expr")

class CCharElementExpr : public CCharElement, public CXDrawData_Points
{
public:
    CCharElementExpr();
    virtual ~CCharElementExpr();
	CString  m_strXb;
	CString  m_strYb;
	CString  m_strXe;
	CString  m_strYe;
    double  m_fXb;
    double  m_fYb;
    double  m_fXe;
    double  m_fYe;
    CString  m_strExpr;//当前使用的表达式
//重载函数
public:
    virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTEXPR;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementExprFuncKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
    virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);
public:
    CString m_strScript;//从Xrio文件获得的Script节点的VB.NET代码；
    CStringArray m_strArrayExprRefIDs;//用于存储当前表达式的所有参数ID包括X
    BOOL m_bIsStdExpr;//标记当前的表达式是否是标准的表达式。(只要不存在VB.NET代码中的函数名字，就认为是标准表达式)
//私有成员变量
private:
    BOOL GetStdExprResult(double dX,double &dY);//标准的表达式，不含有VB.NET中的函数 如：ID_33_08/100*X+IS1
    double GetStdExprResult(double &dVal);//标准的表达式，不含有VB.NET中的函数 如：ID_33_08/100*X+IS1
    CString GetXVarIDPath();
protected:
    virtual BOOL IncreaseX(double &dValX);
    virtual void CalExprPolyline();
//私有成员变量访问方法
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	double CalExpr(double dVal);
    virtual CXDrawBase* CreateDrawElement();
	virtual void BeforeCalTestLines();
	virtual void CalTestLines(UINT nTestLineMode);
};

