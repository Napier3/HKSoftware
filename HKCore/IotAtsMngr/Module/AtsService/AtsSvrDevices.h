//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrDevices.h  CAtsSvrDevices

#pragma once

#include "AtsServiceGlobal.h"


#include "AtsSvrDevice.h"

class CAtsSvrDevices : public CExBaseList
{
public:
	CAtsSvrDevices();
	virtual ~CAtsSvrDevices();


//���غ���
public:
	virtual UINT GetClassID() {    return ATSVRCLASSID_CATSSVRDEVICES;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsServiceXmlRWKeys::CAtsSvrDevicesKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

