//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrRsTestApp.h  CAtsSvrRsTestApp

#pragma once

#include "AtsServiceGlobal.h"



class CAtsSvrRsTestApp : public CDataGroup
{
public:
	CAtsSvrRsTestApp();
	virtual ~CAtsSvrRsTestApp();


	CString  m_strtype;
//���غ���
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

