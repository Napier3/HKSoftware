//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrRsTestApp.h  CAtsSvrRsTestApp

#pragma once

#include "AtsServiceGlobal.h"



class CAtsSvrRsTestApp : public CDataGroup
{
public:
	CAtsSvrRsTestApp();
	virtual ~CAtsSvrRsTestApp();


	CString  m_strtype;
//重载函数
public:
	virtual UINT GetClassID() {    return ATSVRCLASSID_CATSSVRRSTESTAPP;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsServiceXmlRWKeys::CAtsSvrRsTestAppKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

