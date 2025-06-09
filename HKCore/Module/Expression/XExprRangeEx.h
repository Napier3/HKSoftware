//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprRangeEx.h  CXExprRangeEx

#pragma once

#include "XExprBase.h"

//��չ��Χ�жϣ���������1������2����������������ٺ����������ж�
//��չ����жϣ�������real��abs��or��and
class CXExprRangeEx : public CXExprBase
{
public:
	CXExprRangeEx();
	virtual ~CXExprRangeEx();

	CString  m_strCalOptr;  //�������+��-��*����
	CString m_strMinOptr;  //����Сֵ�ıȽ��߼���>= ���� >
	CString m_strMaxOptr;  //�����ֵ�ıȽ��߼���<= ���� <


//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRRANGEEX;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprRangeExKey();     }
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
	CXExprValue1 *m_pValue1;          //���Խ������1������ֵ
	CXExprValue2 *m_pValue2;          //���Խ������2������ֵ

	CXExprValueRslt *m_pValueRslt;  //V1��V2�������������޵ķ�Χ�ȽϽ�������ֵ��0��1
	CXExprValueCalRslt *m_pValueCalRslt;  //����1������2��������γɵ������������ֵ


//˽�г�Ա�������ʷ���
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValueMin* GetExprValueMin();
	CXExprValueMax* GetExprValueMax();
	CXExprValue1* GetExprValue1();
	CXExprValue2* GetExprValue2();
	CXExprValueCalRslt* GetExprValueCalRslt();
	CXExprValueRslt* GetExprValueRslt();
};

