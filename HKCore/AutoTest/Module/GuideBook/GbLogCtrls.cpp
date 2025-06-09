#include "StdAfx.h"
#include "GbLogCtrls.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////////
//CGbLogCtrl
CGbLogCtrl::CGbLogCtrl(void)
{

}

CGbLogCtrl::~CGbLogCtrl(void)
{
}

long CGbLogCtrl::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CGbLogCtrl::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

long CGbLogCtrl::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	return 0;
}


CBaseObject* CGbLogCtrl::Clone()
{
	CGbLogCtrl* pGbLogCtrs = new CGbLogCtrl();
	Copy(pGbLogCtrs);

	return pGbLogCtrs;
}


////////////////////////////////////////////////////////////////////////////////////////
//
CGbLogCtrls::CGbLogCtrls(void)
{

}

CGbLogCtrls::~CGbLogCtrls(void)
{
}

long CGbLogCtrls::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CGbLogCtrls::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

long CGbLogCtrls::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);

	return 0;
}

CExBaseObject* CGbLogCtrls::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strLogCtrlKey)
	{
		CGbLogCtrl* pObject = new CGbLogCtrl;
		return pObject;
	}

	return NULL;
}

CExBaseObject* CGbLogCtrls::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GBLOGCTRL)
	{
		CGbLogCtrl* pObject = new CGbLogCtrl;
		return pObject;
	}

	return NULL;
}

CBaseObject* CGbLogCtrls::Clone()
{
	CGbLogCtrls* pGbLogCtrs = new CGbLogCtrls();
	Copy(pGbLogCtrs);

	return pGbLogCtrs;
}

BOOL CGbLogCtrls::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_GBLOGCTRL)
	{
		return TRUE;
	}

	return FALSE;
}
