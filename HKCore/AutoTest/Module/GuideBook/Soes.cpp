#include "StdAfx.h"
#include "Soes.h"
#include "Soe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSoes::CSoes(void)
{
	m_strName = L"Soe";
}

CSoes::~CSoes(void)
{
}


long CSoes::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CSoes::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CSoes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

CExBaseObject* CSoes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSoeKey)
	{
		CSoe* pObject = new CSoe;
		return pObject;
	}

	return NULL;
}

CExBaseObject* CSoes::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_SOE)
	{
		CSoe* pObject = new CSoe;
		return pObject;
	}

	return NULL;
}

CBaseObject* CSoes::Clone()
{
	CSoes* pSoes = new CSoes();
	Copy(pSoes);
	
	return pSoes;
}



BOOL CSoes::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_SOE)
	{
		return TRUE;
	}

	return FALSE;
}
