//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestResource.h  CAtsSvrTestResource

#pragma once

#include "AtsServiceGlobal.h"


#include "AtsSvrRsTestApp.h"
#include "AtsSvrRsAllocDefMngr.h"

class CAtsSvrTestResource : public CExBaseList
{
public:
	CAtsSvrTestResource();
	virtual ~CAtsSvrTestResource();


//重载函数
public:
	virtual UINT GetClassID() {    return ATSVRCLASSID_CATSSVRTESTRESOURCE;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsServiceXmlRWKeys::CAtsSvrTestResourceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CAtsSvrRsAllocDefMngr *m_pRsAllocDefMngr;
	CAtsSvrRsTestApp *m_pTestApp;

//私有成员变量访问方法
public:
};

