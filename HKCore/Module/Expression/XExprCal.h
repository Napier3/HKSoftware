//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprCal.h  

#pragma once
#include "XExprGlobal.h"
#include "XExprNode.h"

//CXExprQueryMax
class CXExprQueryMax : public CExBaseObject
{
public:
	CXExprQueryMax();
	virtual ~CXExprQueryMax();

	CString m_strValueSrcID;

//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRQUERYMAX;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprQueryMaxKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes, double &dValRet);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprQueryMin
class CXExprQueryMin : public CExBaseObject
{
public:
	CXExprQueryMin();
	virtual ~CXExprQueryMin();

	CString m_strValueSrcID;

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRQUERYMIN;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprQueryMinKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
	BOOL CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes, double &dValRet);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprCal
//���ڹ̶�����������ֵ����Сֵ
class CXExprCal : public CExBaseList
{
public:
	CXExprCal();
	virtual ~CXExprCal();


	CString  m_strValue;  
	CString  m_strValueDstID;  //�������󶨻ؽ������
	CString  m_strValueName;   //�������󶨻ؽ������������
	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRCAL;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprCalKey();     }
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

	//˽�г�Ա����
private:
	CXExprQueryMax *m_pQueryMax;
	CXExprQueryMin *m_pQueryMin;

	//˽�г�Ա�������ʷ���
public:
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual BOOL CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	void AddQueryMax(const CString &strValueSrcID);
	void AddQueryMin(const CString &strValueSrcID);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprCalSRpt
//���ڼ��㵥�α����У�ָ���������ݵ�min��max��avgֵ
//������CXExprCalSRpt������CXExprCalSRpt�ڵ�Ľ������н���������ڵ㲻����������
class CXExprNode;
class CXExprCalSRpt : public CXExprNode
{
public:
	CXExprCalSRpt();
	virtual ~CXExprCalSRpt();


	CString  m_strValue;  
	CString  m_strValueDstID;  //�������󶨻ؽ������
	CString  m_strValueName;   //�������󶨻ؽ������������
	CString  m_strValueSrcIdHas;   //��Ҫ����ı������ݵ�ID��������ֻҪ��������ID�������ⲿ�֣�����Ҫ���㡣��Сд����
	CString  m_strCalMode;     //����ģʽ��max��min��avg
	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRCALSRPT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprCalSRptKey();     }
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

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);
};