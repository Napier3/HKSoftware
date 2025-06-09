#pragma once
#include "..\..\..\..\module\baseclass\exbaselist.h"

#include "..\EpCmmGlobalDefine.h"
#include "EpCmmConfigXmlKeys.h"

class CEpCmmConfigBase :	public CExBaseList
{
public:
	CEpCmmConfigBase(void);
	~CEpCmmConfigBase(void);

	long m_nSendTimeout;
	long m_nReceiveTimeout;

public:
	virtual UINT GetClassID(){return EPCLASSID_CMM_CONFIG_BASE;};
	
	//���л�
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//�༭
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

};
