//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpDeviceNode101Yc.h  CEpDeviceNode101Yc

#pragma once

#include "EpDevice_101Global.h"

#include "..\..\Device\EpDeviceNode.h"

#include "EpDeviceData101Yc.h"

class CEpDeviceNode101Yc : public CEpDeviceNode
{
public:
	CEpDeviceNode101Yc();
	virtual ~CEpDeviceNode101Yc();


//���غ���
public:
	virtual UINT GetClassID() {    return EPDCLASSID_CEPDEVICENODE101YC;   }
	virtual BSTR GetXmlElementKey()  {      return CEpDevice_101XmlRWKeys::CEpDeviceNode101YcKey();     }
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

