//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpDeviceData101Yx.h  CEpDeviceData101Yx

#pragma once

#include "EpDevice_101Global.h"

#include "..\..\Device\EpDeviceData.h"


class CEpDeviceData101Yx : public CEpDeviceData
{
public:
	CEpDeviceData101Yx();
	virtual ~CEpDeviceData101Yx();


	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return EPDCLASSID_CEPDEVICEDATA101YX;   }
	virtual BSTR GetXmlElementKey()  {      return CEpDevice_101XmlRWKeys::CEpDeviceData101YxKey();     }
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

