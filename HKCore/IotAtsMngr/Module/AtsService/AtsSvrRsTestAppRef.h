//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrRsTestAppRef.h  CAtsSvrRsTestAppRef

#pragma once

#include "AtsServiceGlobal.h"



class CAtsSvrRsTestAppRef : public CExBaseObject
{
public:
	CAtsSvrRsTestAppRef();
	virtual ~CAtsSvrRsTestAppRef();


//重载函数
public:
	virtual UINT GetClassID() {    return ATSVRCLASSID_CATSSVRRSTESTAPPREF;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsServiceXmlRWKeys::CAtsSvrRsTestAppRefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual CBaseObject* Clone();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

