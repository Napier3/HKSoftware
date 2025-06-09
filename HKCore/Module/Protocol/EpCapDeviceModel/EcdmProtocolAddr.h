//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EcdmProtocolAddr.h  CEcdmProtocolAddr

#pragma once

#include "EpCapDeviceModelGlobal.h"



class CEcdmProtocolAddr : public CExBaseObject
{
public:
	CEcdmProtocolAddr();
	virtual ~CEcdmProtocolAddr();


	long  m_nYxAddr;
	long  m_nYcAddr;
	long  m_nYtAddr;
//重载函数
public:
	virtual UINT GetClassID() {    return ECDMCLASSID_CECDMPROTOCOLADDR;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDeviceModelXmlRWKeys::CEcdmProtocolAddrKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

