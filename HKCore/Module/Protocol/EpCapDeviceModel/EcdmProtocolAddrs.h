//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EcdmProtocolAddrs.h  CEcdmProtocolAddrs

#pragma once

#include "EpCapDeviceModelGlobal.h"


#include "EcdmProtocolAddr.h"

class CEcdmProtocolAddrs : public CExBaseList
{
public:
	CEcdmProtocolAddrs();
	virtual ~CEcdmProtocolAddrs();


//���غ���
public:
	virtual UINT GetClassID() {    return ECDMCLASSID_CECDMPROTOCOLADDRS;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDeviceModelXmlRWKeys::CEcdmProtocolAddrsKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
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

