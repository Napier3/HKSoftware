//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprValueCalEx.h  CXExprValueCalEx

#pragma once

#include "XExprBase.h"

//��չ�������㣬��������1������2����������������ٺͻ�׼ֵ����չ����ж�
//��չ����жϣ�������real��abs��or��and
class CXExprValueCalEx : public CXExprBase
{
public:
	CXExprValueCalEx();
	virtual ~CXExprValueCalEx();

	CString  m_strCalOptr;  //�������+��-��*����
	CString  m_strMode;  //����ж�ģʽ��abs��real��or��and
	CString  m_strOptr;  //�����������޵ıȽ��߼���<= ���� <

//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUECALEX;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueCalExKey();     }
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

	//WriteXml
	//virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

//˽�г�Ա����
private:
	CXExprValue1 *m_pValue1;      //����1������ֵ
	CXExprValue2 *m_pValue2;      //����2������ֵ
	CXExprValueStd *m_pValueStd;  //��������Ļ�׼ֵ������ֵ
	CXExprValueErrorRel *m_pErrorRel;   //���������ݶ����������ޣ�������ֵ
	CXExprValueErrorAbs *m_pErrorAbs;   //����������ݶ��󣨾�������ޣ�������ֵ

	CXExprValueCalRslt *m_pValueCalRslt;  //����1������2��������γɵ������������ֵ
	CXExprValueRslt *m_pValueRslt;  //����жϽ�����Ƿ���������ޣ����ֵ
	CXExprValueErrorRelRslt *m_pValueErrorRelRslt;  //�������������������ֵ�����ֵ
	CXExprValueErrorAbsRslt *m_pValueErrorAbsRslt;  //���������������������ֵ�����ֵ

//˽�г�Ա�������ʷ���
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	long CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface
		, double &dValStd, double &dValue1, double &dValue2, double &dErrRel, double &dErrAbs
		, CString &strValStd, CString &strValue1, CString &strValue2, CString &strErrorRel, CString &strErrorAbs);
	long Calc_Abs(double &dCal, double dValStd, double dVal, double dErrAbs);
	long Calc_Rel(double &dCal, double dValStd, double dVal, double dErrRel);
	long Calc_Or(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs);
	long Calc_And(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValue1* GetExprValue1();
	CXExprValue2* GetExprValue2();
	CXExprValueCalRslt* GetExprValueCalRslt();
	CXExprValueStd* GetExprValueStd();
	CXExprValueErrorRel* GetExprValueErrorRel();
	CXExprValueErrorAbs* GetExprValueErrorAbs();
	CXExprValueRslt* GetExprValueRslt();
	CXExprValueErrorRelRslt* GetExprValueErrorRelRslt();
	CXExprValueErrorAbsRslt* GetExprValueErrorAbsRslt();
};

