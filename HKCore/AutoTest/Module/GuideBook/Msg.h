#pragma once

#include "GuideBookDefine.h"

class CMsg : public CExBaseObject
{
public:
	CMsg();
	virtual ~CMsg();

	static CMsg* _New(CBaseObject *pParent=NULL)
	{
		CMsg *pNew = new CMsg();
		return pNew;
	}

//����
public:
	CString m_strMsg;
	long m_nUseCData;

//�ӿں���
public:
	void SetMsg(CString strMsg) { m_strMsg = strMsg;}
	CString GetMsg() { return m_strMsg;}

//��д���෽��
public:
	virtual UINT GetClassID()	{		return GBCLASSID_MSG;	}

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	

};