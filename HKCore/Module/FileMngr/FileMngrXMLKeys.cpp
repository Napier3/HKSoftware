#include "stdafx.h"
#include "FileMngrXMLKeys.h"

CFileMngrXMLKeys* CFileMngrXMLKeys::g_pFileMngrXMLKeys = NULL;
long CFileMngrXMLKeys::g_nFileMngrXmlKeysRef = 0;

CFileMngrXMLKeys* CFileMngrXMLKeys::CreateFileMngrXMLKeys()
{
	g_nFileMngrXmlKeysRef ++;

	if(g_nFileMngrXmlKeysRef == 1)
	{
		g_pFileMngrXMLKeys = new CFileMngrXMLKeys();
	}

	return g_pFileMngrXMLKeys;
}

void CFileMngrXMLKeys::Release()
{
	g_nFileMngrXmlKeysRef --;

	if(g_nFileMngrXmlKeysRef == 0)
	{
		delete g_pFileMngrXMLKeys;
		g_pFileMngrXMLKeys = NULL;
	}
}

CFileMngrXMLKeys::CFileMngrXMLKeys()
{
	m_strXSINoNamespaceSchemaLocationKey = L"xsi:noNamespaceSchemaLocation";
	m_strXmlnsKey = L"xmlns:xsi";

	m_strFileKey = L"file";
	m_strFolderKey = L"folder";
	m_strFileTypeKey = L"type";

	//GbDevItemFileMngr.xsd中用到的XML keys
	m_strGbDevItemFileMngrKey = L"GbDevItemFileMngr";
	
	//GbFileMngr.xsd中用到的XML keys
	m_strGbFileMngrKey = L"GbFileMngr";
	m_strGbNameKey = L"GbName";
	m_strGbFactoryKey = L"factory";

	m_strPpTemplateMngrkey = L"PpTemplateFileMngr";
}