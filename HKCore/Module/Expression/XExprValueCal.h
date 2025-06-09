//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprValueCal.h  CXExprValueCal

#pragma once

#include "XExprBase.h"

//�������㣬��������1������2����������������ٺͻ�׼ֵ������ж�
//���У�real�ǰٷֱ��������������������/��׼ֵ*100%��Ŀǰ������ң������
class CXExprValueCal : public CXExprBase
{
public:
	CXExprValueCal();
	virtual ~CXExprValueCal();

	CString  m_strCalOptr;  //�������+��-��*��/
	CString  m_strMode;  //����ж�ģʽ��abs��real
	CString  m_strOptr;  //�����������޵ıȽ��߼���<= ���� <

//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUECAL;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueCalKey();     }
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
	CXExprValueCalRslt *m_pValueCalRslt;  //����1������2��������γɵ������������ֵ
	CXExprValueStd *m_pValueStd;  //��������Ļ�׼ֵ������ֵ
	CXExprValueError *m_pError;   //������ݶ�������ޣ�������ֵ
	CXExprValueRslt *m_pValueRslt;  //����жϽ�����Ƿ���������ޣ����ֵ
	CXExprValueErrorRslt *m_pValueErrorRslt;  //�������������ֵ�����ֵ

//˽�г�Ա�������ʷ���
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);
	virtual void GetRsltExprValues_ExprMode(const CString &strMode, CExBaseList *pRsltExprValues);

	CXExprValue1* GetExprValue1();
	CXExprValue2* GetExprValue2();
	CXExprValueCalRslt* GetExprValueCalRslt();
	CXExprValueStd* GetExprValueStd();
	CXExprValueError* GetExprValueError();
	CXExprValueRslt* GetExprValueRslt();
	CXExprValueErrorRslt* GetExprValueErrorRslt();
};

