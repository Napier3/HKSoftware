//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprCmp.h  CXExprCmp

#pragma once

#include "XExprBase.h"

class CXExprCmp : public CXExprBase
{
public:
	CXExprCmp();
	virtual ~CXExprCmp();


	CString  m_strOptr;
//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRCMP;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprCmpKey();     }
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
	CXExprValue1 *m_pValueLeft;    //����1������ֵ
	CXExprValue2 *m_pValueRight;   //����2������ֵ
	CXExprValueRslt *m_pValueRslt; //����1������2�ȽϵĽ��ֵ�����ֵ

//˽�г�Ա�������ʷ���
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValue1* GetExprValue1();
	CXExprValue2* GetExprValue2();
	CXExprValueRslt* GetValueRslt();
};

