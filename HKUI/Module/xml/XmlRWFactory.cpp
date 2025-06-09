#include "stdafx.h"
#include "XmlRWFactory.h"
#include "XmlRWInterface.h"

#ifdef XML_USE_MSXML
#include "XmlRW_MS.h"
#endif

#ifdef XML_USE_TINYXML
#include "XmlRW_Tiny.h"
#endif

#ifdef XML_USE_PUGIXML
#include "XmlRW_Pugi.h"
#endif

#ifdef JSON_USE_
#include "JsonRW.h"
#endif

CXmlRWFactory::CXmlRWFactory(void)
{
}

CXmlRWFactory::~CXmlRWFactory(void)
{
}

CXmlRWDocBase* CXmlRWFactory::CreateXmlRWDoc(const CString &strFile, long nType)
{
	CXmlRWDocBase *pRWDocBase = CreateXmlRWDoc(nType);

	if (pRWDocBase == NULL)
	{
		return pRWDocBase;
	}

	try
	{
		if ( !xml_OpenFile(pRWDocBase, strFile) )//调用XMLInterface.h中的全局函数，加载资源，入口返回给oDoc；
		{
			delete pRWDocBase;
			return NULL;
		}
	}
	catch (...)
	{
		delete pRWDocBase;
		return NULL;
	}

	return pRWDocBase;
}

CXmlRWDocBase* CXmlRWFactory::CreateXmlRWDoc(long nType)
{
	CXmlRWDocBase *pRWDocBase = NULL;

#ifdef XML_USE_MSXML
	if (nType == _MS_XML_TYPE_)
	{
		pRWDocBase = CXmlRWDoc_MS::CreateXmlRWDoc();
	}
#endif

#ifdef XML_USE_TINYXML
	if (nType == _TINY_XML_TYPE_)
	{
		pRWDocBase = CXmlRWDoc_Tiny::CreateXmlRWDoc();
		pRWDocBase->CreateInstruction(_T("1.0"),_T("GB2312"));
	}
#endif

#ifdef XML_USE_PUGIXML
	if (nType == _PUGI_XML_TYPE_)
	{
		pRWDocBase = CXmlRWDoc_Pugi::CreateXmlRWDoc();
	}
#endif

#ifdef JSON_USE_
	if (nType == _JSON_TYPE_)
	{
		pRWDocBase = CJsonRWDoc::CreateXmlRWDoc();
	}
#endif

	ASSERT(pRWDocBase != NULL);

	return pRWDocBase;
}


CXmlRWDocBase* xml_CreateXmlRWDoc(long nType)
{
	return CXmlRWFactory::CreateXmlRWDoc(nType);
}

CXmlRWDocBase* xml_CreateXmlRWDoc(const CString &strFile, long nType)
{
	return CXmlRWFactory::CreateXmlRWDoc(strFile, nType);
}