#include "stdafx.h"
#include "GbDevXMLKeys.h"

CGbDevXMLKeys* CGbDevXMLKeys::g_pGbDevXMLKeys = NULL;
long CGbDevXMLKeys::g_nGbXmlKeysRef = 0;

CGbDevXMLKeys* CGbDevXMLKeys::CreateGbDevXMLKeys()
{
	g_nGbXmlKeysRef ++;

	if(g_nGbXmlKeysRef == 1)
	{
		g_pGbDevXMLKeys = new CGbDevXMLKeys();
	}

	return g_pGbDevXMLKeys;
}

void CGbDevXMLKeys::Release()
{
	g_nGbXmlKeysRef --;

	if(g_nGbXmlKeysRef == 0)
	{
		delete g_pGbDevXMLKeys;
		g_pGbDevXMLKeys = NULL;
	}
}

CGbDevXMLKeys::CGbDevXMLKeys()
{
	m_strXSINoNamespaceSchemaLocationKey = L"xsi:noNamespaceSchemaLocation";
	m_strXmlnsKey = L"xmlns:xsi";

	//TttItemCfgInfors.xsd���õ���XML Keys
	m_strNodeClassMngrKey = L"classMngr";
	m_strNodeClassKey = L"class";
	m_strNIDKey = L"nid";

	m_strChildOptrButtonsKey = L"btns";
	m_strChildOptrButtonKey = L"btn";
	m_strFuncIDKey = L"func-id";

	m_strChildGridColsKey = L"cols";
	m_strChildGridColKey = L"col";
	m_strWidthKey = L"width";

	m_strOwnPopMenuItemsKey = L"menus";
	m_strOwnPopMenuItemKey = L"menu";
	m_strMenuIDKey = L"menu-id";

	//GbDevItemFileMngr.xsd���õ���XML keys
	//����Ҫ�Ļ�������
	m_strGbDevItemFileMngrKey = L"GbDevItemFileMngr";
	m_strGbItemFileKey = L"file";
	m_strGbItemFolderKey = L"folder";
	m_strPathKey = L"path";
	m_strFileTypeKey = L"type";
}