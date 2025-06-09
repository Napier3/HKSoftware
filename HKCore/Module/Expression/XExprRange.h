//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprRange.h  CXExprRange

#pragma once

#include "XExprBase.h"

class CXExprRange : public CXExprBase
{
public:
	CXExprRange();
	virtual ~CXExprRange();

	CString m_strMinOptr;  //����Сֵ�ıȽ��߼���>= ���� >
	CString m_strMaxOptr;  //�����ֵ�ıȽ��߼���<= ���� <


//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRRANGE;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprRangeKey();     }
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
	CXExprValueMin *m_pValueMin;    //��׼ֵ-��Сֵ������ֵ
	CXExprValueMax *m_pValueMax;    //��׼ֵ-���ֵ������ֵ
	CXExprValue *m_pValue;          //���Խ�����ݣ�����ֵ

	CXExprValueRslt *m_pValueRslt;  //���Խ�����׼ֵ�ķ�Χ�ȽϽ�������ֵ

//˽�г�Ա�������ʷ���
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValueMin* GetExprValueMin();
	CXExprValueMax* GetExprValueMax();
	CXExprValue* GetExprValue();
	CXExprValueRslt* GetExprValueRslt();
};

