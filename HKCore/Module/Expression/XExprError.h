//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprError.h  CXExprError

#pragma once

#include "XExprBase.h"
//����жϣ����Խ���������ͻ�׼ֵ�����ֵ�����ֵ�ٺ������������ж�
class CXExprError : public CXExprBase
{
public:
	CXExprError();
	virtual ~CXExprError();


	CString  m_strMode;  //����ж�ģʽ��abs��real
	CString  m_strOptr;  //�����������޵ıȽ��߼���<= ���� <
//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRERROR;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprErrorKey();     }
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
	CXExprValue *m_pValue;        //������ݶ�������ֵ
	CXExprValueStd *m_pValueStd;  //��׼ֵ������ֵ
	CXExprValueError *m_pError;   //������ݶ�������ޣ�

	CXExprValueRslt *m_pValueRslt;  //����жϽ�����Ƿ���������ޣ����ֵ
	CXExprValueErrorRslt *m_pValueErrorRslt;  //�������������ֵ�����ֵ

//˽�г�Ա�������ʷ���
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValue* GetExprValue();
	CXExprValueStd* GetExprValueStd();
	CXExprValueError* GetExprValueError();
	CXExprValueRslt* GetExprValueRslt();
	CXExprValueErrorRslt* GetExprValueErrorRslt();
};

