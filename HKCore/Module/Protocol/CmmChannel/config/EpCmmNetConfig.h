#pragma once
#include "..\..\..\..\module\baseclass\exbaselist.h"
#include "EpCmmTcpClientConfig.h"
#include "EpCmmTcpServerConfig.h"
#include "EpCmmUdpConfig.h"

class CEpCmmNetConfig :	public CExBaseList
{
public:
	CEpCmmNetConfig(void);
	~CEpCmmNetConfig(void);

public:
	//基本方法
	virtual void Init();
	virtual long InitAfterSerialize();
	virtual UINT GetClassID(){return EPCLASSID_NET_CONFIG;};

	//串行化
	virtual BSTR GetXmlElementKey()  {      return CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strNetKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//编辑
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//创建子对象
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	CExBaseObject* GetChildByClassID(UINT nClassID);
};
