#pragma once

#include "../../Module/BaseClass/ExBaseObject.h"

class CFileMngrXMLKeys : public CXmlRWKeys
{
private:
	CFileMngrXMLKeys();
	virtual ~CFileMngrXMLKeys()									{	}

	static long g_nFileMngrXmlKeysRef;

public:
	static CFileMngrXMLKeys* g_pFileMngrXMLKeys;
	static CFileMngrXMLKeys* CreateFileMngrXMLKeys();
	static void Release();

public:
	BSTR m_strXSINoNamespaceSchemaLocationKey;
	BSTR m_strXmlnsKey;

	BSTR m_strFileKey;
	BSTR m_strFolderKey;
	BSTR m_strFileTypeKey;

	//GbDevItemFileMngr.xsd中用到的XML keys
	BSTR m_strGbDevItemFileMngrKey;

	//GbFileMngr.xsd中用到的XML keys
	BSTR m_strGbFileMngrKey;
	BSTR m_strGbNameKey;
	BSTR m_strGbFactoryKey;

	//PpTemplateFileMngr.xsd中用到的XML keys
	BSTR m_strPpTemplateMngrkey;
};