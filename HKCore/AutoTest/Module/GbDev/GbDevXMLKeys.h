#pragma once

#include "../../../Module/BaseClass/ExBaseObject.h"

class CGbDevXMLKeys : public CXmlRWKeys
{
private:
	CGbDevXMLKeys();
	virtual ~CGbDevXMLKeys()									{	}

	static long g_nGbXmlKeysRef;

public:
	static CGbDevXMLKeys* g_pGbDevXMLKeys;
	static CGbDevXMLKeys* CreateGbDevXMLKeys();
	static void Release();

public:
	BSTR m_strXSINoNamespaceSchemaLocationKey;
	BSTR m_strXmlnsKey;
	//name和id Key已在基类中定义

	//TttItemCfgInfors.xsd中用到的XML Keys

	BSTR m_strNodeClassMngrKey;
	BSTR m_strNodeClassKey;
	BSTR m_strNIDKey;
	
	BSTR m_strChildOptrButtonsKey;
	BSTR m_strChildOptrButtonKey;
	BSTR m_strFuncIDKey;

	BSTR m_strChildGridColsKey;
	BSTR m_strChildGridColKey;
	BSTR m_strWidthKey;

	BSTR m_strOwnPopMenuItemsKey;
	BSTR m_strOwnPopMenuItemKey;
	BSTR m_strMenuIDKey;

	//GbDevItemFileMngr.xsd中用到的XML keys
	//有需要的话再完善
	BSTR m_strGbDevItemFileMngrKey;
	BSTR m_strGbItemFileKey;
	BSTR m_strGbItemFolderKey;
	BSTR m_strPathKey;
	BSTR m_strFileTypeKey;
};