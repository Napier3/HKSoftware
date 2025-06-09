//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapDbFileCfg.h  CEpCapDbFileCfg

#pragma once

#include "EpCapDbConfigGlobal.h"



class CEpCapDbFileCfg : public CExBaseList
{
public:
	CEpCapDbFileCfg();
	virtual ~CEpCapDbFileCfg();

	long  m_nSize;
	long  m_nView;
	CString  m_strFile;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEPCAPDBFILECFG;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDbConfigXmlRWKeys::CEpCapDbFileCfgKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CString GetSmDBFilePath();
};


class CEpCapDbFileArea : public CExBaseObject
{
public:
	CEpCapDbFileArea();
	virtual ~CEpCapDbFileArea();


	long  m_nSize;
	long  m_nView;
	long m_nBeginPos;

	//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEPCAPDBFILEAREA;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDbConfigXmlRWKeys::CEpCapDbFileAreaKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

