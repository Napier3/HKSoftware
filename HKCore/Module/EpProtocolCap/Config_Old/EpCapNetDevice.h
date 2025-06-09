//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapNetDevice.h  CEpCapNetDevice

#pragma once

#include "EpCapConfigGlobal.h"



class CEpCapNetDevice : public CExBaseObject
{
public:
	CEpCapNetDevice();
	virtual ~CEpCapNetDevice();


	long  m_nIndex;
	CString  m_strIP;
	CString  m_strProtocol;
	long  m_nTcp;
	long  m_nUdp;
//���غ���
public:
	virtual UINT GetClassID() {    return ECCLASSID_CEPCAPNETDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapConfigXmlRWKeys::CEpCapNetDeviceKey();     }
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

