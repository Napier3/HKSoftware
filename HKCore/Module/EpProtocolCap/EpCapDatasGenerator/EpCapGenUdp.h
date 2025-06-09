//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapGenUdp.h  CEpCapGenUdp

#pragma once

#include "EpCapGenBase.h"



class CEpCapGenUdp : public CEpCapGenBase
{
public:
	CEpCapGenUdp();
	virtual ~CEpCapGenUdp();


	CString  m_strLocalIP;
	CString  m_strLocalPort;
	CString  m_strRemotePort;
	CString  m_strRemoteIP;
//重载函数
public:
	virtual UINT GetClassID() {    return ECGCLASSID_CEPCAPGENUDP;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDatasGeneratorXmlRWKeys::CEpCapGenUdpKey();     }
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

