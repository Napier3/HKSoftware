//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprValue.h  CXExprValue

#pragma once

#include "XExprGlobal.h"

class CXExprValue : public CExBaseObject
{
public:
	CXExprValue();
	virtual ~CXExprValue();

/*
m_strType���󶨵����ݶ�������ࣺ
������dataset��sys-para��global-para��report��number(��ֵ���ͣ��ް�����)��script(������ʽ)

m_strValueType��m_strValueֵ���������ͣ�bool��number��utc_time��
m_strValueID���󶨵����ݶ����ID����û�а�ʱ��m_strValueIDΪ���ַ���
m_strValueName�����������ơ���û�а����ݶ���ʱ�������������Ը�����Ϊ׼����ʱ���Ա��󶨲���������Ϊ׼
m_strValueUnit�������ĵ�λ����û�а����ݶ���ʱ�������ĵ�λ�Ը�����Ϊ׼����ʱ���Ա��󶨲����ĵ�λΪ׼
m_strItemPath�����󶨵����ݶ�����report����ʱ�������Լ�¼report������������Ŀ�����·��
*/
	CString  m_strType;   
	CString  m_strValue;
	CString  m_strValueID;
	CString  m_strValueName;
	CString  m_strValueUnit;   //��λ����ʱֻ����ʱ����ĵ�λ��ms��s
	CString  m_strValueType;
	CString  m_strItemPath;
//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

protected:
	BOOL m_bRelCalVal;  //�Ƿ��������������

//˽�г�Ա�������ʷ���
public:
	virtual BOOL IsValueUint_ms();
	virtual void SetRelCalVal(BOOL bRelCalVal)	{	m_bRelCalVal = bRelCalVal;	}
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	//2023-11-8 �����β� CString &strValRet�����ڷ����ַ�����������硰δ������
	virtual BOOL Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, double &dValRet, CString &strValRet);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual void GetRsltExprValues_RelPath(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues);//�����������Ŀ·��
	virtual BOOL GetValueName(const CString &strID, CString &strName);
};

