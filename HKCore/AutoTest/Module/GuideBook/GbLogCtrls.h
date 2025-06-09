#pragma once

#include "GuideBookDefine.h"


class CGbLogCtrl :public CExBaseObject
{
public:
	CGbLogCtrl(void);
	virtual ~CGbLogCtrl(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()			{		return GBCLASSID_GBLOGCTRL;	}
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::g_pGbXMLKeys->m_strLogCtrlKey;     }

	virtual CBaseObject* Clone();

protected:

};


class CGbLogCtrls :public CExBaseList
{
public:
	CGbLogCtrls(void);
	virtual ~CGbLogCtrls(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()			{		return GBCLASSID_GBLOGCTRLS;	}
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::g_pGbXMLKeys->m_strLogCtrlsKey;     }

	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

protected:

};

