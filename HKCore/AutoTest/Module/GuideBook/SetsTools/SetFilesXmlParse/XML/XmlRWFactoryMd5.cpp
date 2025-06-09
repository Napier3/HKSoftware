#include "stdafx.h"
#include "XmlRWFactoryMd5.h"

#ifdef XML_USE_PUGIXML
#include "XmlRW_PugiMd5.h"
#endif

CXmlRWFactoryMd5::CXmlRWFactoryMd5(void)
{
}

CXmlRWFactoryMd5::~CXmlRWFactoryMd5(void)
{
}

CXmlRWDocBase* CXmlRWFactoryMd5::I_CreateXmlRWDoc(long nType)
{
	CXmlRWDocBase *pRWDocBase = NULL;

#ifdef XML_USE_PUGIXML
	if (nType == _PUGI_XML_TYPE_)
	{
		pRWDocBase = CXmlRWDoc_PugiMd5::CreateXmlRWDocMd5();
	}
#endif

	ASSERT(pRWDocBase != NULL);

	return pRWDocBase;
}
