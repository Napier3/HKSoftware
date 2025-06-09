#pragma once

#include "GbItemBase.h"
#include "GuideBookDefine.h"

#define HdResReqType_request  _T("request")
#define HdResReqType_release  _T("release")

class CHdResReqest : public CGbItemBase
{
public:
	CHdResReqest();
	virtual ~CHdResReqest();
	virtual CGbItemBase* CloneForTempFile();

	static CHdResReqest* _New(CBaseObject *pParent=NULL)
	{
		CHdResReqest *pNew = new CHdResReqest();
		pNew->InitAfterRead();
		pNew->SetParent(pParent);
		return pNew;
	}

public:
	CString m_strType;    //request、release
	CDataGroup* m_pPara;


public:
	CDataGroup* GetHdResReqestPara();

//重写父类方法
public:
	virtual UINT GetClassID()		{		return GBCLASSID_HDRESREQUEST;			}

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	virtual BSTR GetXmlElementKey(){		return CGbXMLKeys::g_pGbXMLKeys->m_strHdResReqestKey;	};

	virtual void InitAfterRead();

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);

	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

public:
	BOOL IsRequest()	{	return m_strType == HdResReqType_request;	}
	BOOL IsRelease()	{	return m_strType == HdResReqType_release;	}

	void SetRequest()	{	m_strType = HdResReqType_request;	}
	BOOL SetRelease()	{	m_strType = HdResReqType_release;	}

};
