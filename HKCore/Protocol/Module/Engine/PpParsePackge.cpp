#include "StdAfx.h"
#include "PpParsePackge.h"
#include "ProtocolXmlRWKeys.h"
#include "PpScript.h"
#include "BbVariables.h"
#include "RBbDataSets.h"
#include "RByteBlock.h"

CPpParsePackge::CPpParsePackge(void)
{
}

CPpParsePackge::~CPpParsePackge(void)
{
	
}

long CPpParsePackge::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPpPackage::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;

}
long CPpParsePackge::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

CExBaseObject* CPpParsePackge::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey)
	{
		return new CPpScript(strClassID);
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey)
	{
		return new CPpScript(strClassID);
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strEndScriptKey)
	{
		return new CPpScript(strClassID);
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVarialblesKey)
	{
		return new CBbVariables(strClassID);
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataSetsKey)
	{
		return new CRBbDataSets();
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CRByteBlock();
	}
	return NULL;
}

CExBaseObject* CPpParsePackge::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
}

