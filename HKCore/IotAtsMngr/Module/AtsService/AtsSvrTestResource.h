//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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


//���غ���
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

//˽�г�Ա����
private:
	CAtsSvrRsAllocDefMngr *m_pRsAllocDefMngr;
	CAtsSvrRsTestApp *m_pTestApp;

//˽�г�Ա�������ʷ���
public:
};

