//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapSerialDevice.h  CEpCapSerialDevice

#pragma once

#include "EpCapConfigGlobal.h"



class CEpCapSerialDevice : public CExBaseObject
{
public:
	CEpCapSerialDevice();
	virtual ~CEpCapSerialDevice();


	CString  m_strComID;
	long  m_nIndex;
	CString  m_strProtocol;
//���غ���
public:
	virtual UINT GetClassID() {    return ECCLASSID_CEPCAPSERIALDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapConfigXmlRWKeys::CEpCapSerialDeviceKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

