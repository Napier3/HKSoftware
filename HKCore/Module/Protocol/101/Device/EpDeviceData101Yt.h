//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpDeviceData101Yt.h  CEpDeviceData101Yt

#pragma once

#include "EpDevice_101Global.h"

#include "..\..\Device\EpDeviceData.h"


class CEpDeviceData101Yt : public CEpDeviceData
{
public:
	CEpDeviceData101Yt();
	virtual ~CEpDeviceData101Yt();


	float  m_fValue;
	float  m_fMax;
	float  m_fMin;

//���غ���
public:
	virtual UINT GetClassID() {    return EPDCLASSID_CEPDEVICEDATA101YT;   }
	virtual BSTR GetXmlElementKey()  {      return CEpDevice_101XmlRWKeys::CEpDeviceData101YtKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
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

