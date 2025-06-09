//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprErrorCombined.h  CXExprErrorCombined

#pragma once

#include "XExprBase.h"
//�����ͨ������ʱ����
//��׼ֵ * x% + y

class CXExprErrorCombined : public CXExprBase
{
public:
	CXExprErrorCombined();
	virtual ~CXExprErrorCombined();

	CString  m_strOptr;  //�����������޵ıȽ��߼���<= ���� <
//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRERRORCOMBINED;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprErrorCombinedKey();     }
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
	CXExprValueErrorRel *m_pErrorRel;   //���������ݶ����������ޣ�
	CXExprValueErrorAbs *m_pErrorAbs;   //����������ݶ��󣨾�������ޣ�

	CXExprValueRslt *m_pValueRslt;  //����жϽ�����Ƿ���������ޣ����ֵ
	CXExprValueErrorRslt *m_pValueErrorRslt;  //�������������ֵ������ֵ�������ֵ

//˽�г�Ա�������ʷ���
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	long CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, double &dValStd, double &dVal, double &dErrRel, double &dErrAbs
		, CString &strValStd, CString &strValue, CString &strErrorRel, CString &strErrorAbs);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValue* GetExprValue();
	CXExprValueStd* GetExprValueStd();
	CXExprValueErrorRel* GetExprValueErrorRel();
	CXExprValueErrorAbs* GetExprValueErrorAbs();
	CXExprValueRslt* GetExprValueRslt();
	CXExprValueErrorRslt* GetExprValueErrorRslt();
};

