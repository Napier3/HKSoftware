//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbFileCfg.h  CSmDbFileCfg

#pragma once

#include "SmDbConfigGlobal.h"



class CSmDbFileCfg : public CExBaseList
{
public:
	CSmDbFileCfg();
	virtual ~CSmDbFileCfg();

	long  m_nSize;
	long  m_nView;
	CString  m_strFile;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEPCAPDBFILECFG;   }
	virtual BSTR GetXmlElementKey()  {      return CSmDbConfigXmlRWKeys::CSmDbFileCfgKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
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
	virtual BSTR GetXmlElementKey()  {      return CSmDbConfigXmlRWKeys::CEpCapDbFileAreaKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
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

