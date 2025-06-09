//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
//重载函数
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

//私有成员变量
private:

//私有成员变量访问方法
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

	//重载函数
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

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

