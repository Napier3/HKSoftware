//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrRsTestAppRef.h  CAtsSvrRsTestAppRef

#pragma once

#include "AtsServiceGlobal.h"



class CAtsSvrRsTestAppRef : public CExBaseObject
{
public:
	CAtsSvrRsTestAppRef();
	virtual ~CAtsSvrRsTestAppRef();


//���غ���
public:
	virtual UINT GetClassID() {    return ATSVRCLASSID_CATSSVRRSTESTAPPREF;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsServiceXmlRWKeys::CAtsSvrRsTestAppRefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual CBaseObject* Clone();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

