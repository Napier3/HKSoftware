//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenEnable.h  CRptTemp_Enable

#pragma once

#include "TestMacroRptTemplateGlobal.h"

class CRptTemp_ParaOptr : public CExBaseObject
{
public:
	CRptTemp_ParaOptr();
	virtual ~CRptTemp_ParaOptr();


	CString  m_strOptr;
	CString  m_strValue;
	//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_PARAOPTR;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_ParaOptrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	//���Ա������ʷ���
public:
	BOOL IsEnable_Optr_Eql()	{	return m_strOptr == RPT_TEMPLATE_ENABLE_OPTR_EQL;	}
	BOOL IsEnable_Optr_UnEql()	{	return m_strOptr == RPT_TEMPLATE_ENABLE_OPTR_UNEQL;	}
	BOOL IsEnable(CExBaseList *pParas);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRptTemp_Enable : public CExBaseList
{
public:
	CRptTemp_Enable();
	virtual ~CRptTemp_Enable();

	CString  m_strMode;  //ʹ��ģʽ����=and����=or��
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_ENABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_EnableKey();     }
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

//���Ա������ʷ���
public:
	BOOL IsEnableMode_And()	{	return m_strMode == RPT_TEMPLATE_ENABLE_MODE_AND;	}
	BOOL IsEnableMode_Or()	{	return m_strMode == RPT_TEMPLATE_ENABLE_MODE_OR;		}
	BOOL IsEnable(CExBaseList *pParas);
	BOOL IsEnable_And(CExBaseList *pParas);
	BOOL IsEnable_Or(CExBaseList *pParas);

};

