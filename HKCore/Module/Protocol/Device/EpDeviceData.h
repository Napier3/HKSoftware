//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpDeviceData.h  CEpDeviceData

#pragma once

#include "EpDeviceGlobal.h"



class CEpDeviceData : public CExBaseObject
{
public:
	CEpDeviceData();
	virtual ~CEpDeviceData();

	long     m_nUsed;

//���غ���
public:
	virtual UINT GetClassID() {    return EPDCLASSID_CEPDEVICEDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CEpDeviceXmlRWKeys::CEpDeviceDataKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
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

