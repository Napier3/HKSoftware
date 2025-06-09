#include "StdAfx.h"
#include "PpProducePackge.h"
#include "ProtocolXmlRWKeys.h"
#include "PpScript.h"
#include "BbVariables.h"
#include "WBbDataSets.h"
#include "WByteBlock.h"

CPpProducePackge::CPpProducePackge(void)
{
}

CPpProducePackge::~CPpProducePackge(void)
{
	
}

long CPpProducePackge::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPpPackage::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;

}
long CPpProducePackge::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

CExBaseObject* CPpProducePackge::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey)
	{
		return new CPpScript(strClassID);
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey)
	{
		return new CPpScript(strClassID);
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strOnDataPakScriptKey)
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
		return new CWBbDataSets();
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CWByteBlock();
	}

	return NULL;
}

CExBaseObject* CPpProducePackge::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
}

