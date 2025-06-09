//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
    CString  m_strExpr;//��ǰʹ�õı��ʽ
//���غ���
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
    CString m_strScript;//��Xrio�ļ���õ�Script�ڵ��VB.NET���룻
    CStringArray m_strArrayExprRefIDs;//���ڴ洢��ǰ���ʽ�����в���ID����X
    BOOL m_bIsStdExpr;//��ǵ�ǰ�ı��ʽ�Ƿ��Ǳ�׼�ı��ʽ��(ֻҪ������VB.NET�����еĺ������֣�����Ϊ�Ǳ�׼���ʽ)
//˽�г�Ա����
private:
    BOOL GetStdExprResult(double dX,double &dY);//��׼�ı��ʽ��������VB.NET�еĺ��� �磺ID_33_08/100*X+IS1
    double GetStdExprResult(double &dVal);//��׼�ı��ʽ��������VB.NET�еĺ��� �磺ID_33_08/100*X+IS1
    CString GetXVarIDPath();
protected:
    virtual BOOL IncreaseX(double &dValX);
    virtual void CalExprPolyline();
//˽�г�Ա�������ʷ���
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	double CalExpr(double dVal);
    virtual CXDrawBase* CreateDrawElement();
	virtual void BeforeCalTestLines();
	virtual void CalTestLines(UINT nTestLineMode);
};

