#include "StdAfx.h"
#include "XmlDbKeys.h"

long CXmlDbKeys::g_nXmlDbKeysRef = 0;
CXmlDbKeys* CXmlDbKeys::g_pXmlDbKeys  = NULL;

CXmlDbKeys::CXmlDbKeys(void)
{
	//元素名称
	m_strDbKey = _T("Db");
	m_strDbTableKey = _T("db-tbl");
	m_strTagsKey = _T("tgs");
	m_strTagKey = _T("tg");
	m_strDataKey = _T("dat");

	//属性名称
	m_strDbIDKey = _T("db-id");
	m_strDbNameKey = _T("db-name");
	m_strUserIDKey = _T("usr-id");
	m_strUserNameKey = _T("usr-name");
	m_strDataTypeKey = _T("datatype");
	m_strIsKeyKey = _T("iskey");
}

CXmlDbKeys::~CXmlDbKeys(void)
{
}

CXmlDbKeys* CXmlDbKeys::CreateXmlDbKeys()
{
	g_nXmlDbKeysRef++;

	if (g_nXmlDbKeysRef == 1)
	{
		g_pXmlDbKeys = new CXmlDbKeys();
	}

	return g_pXmlDbKeys;
}

void CXmlDbKeys::Release()
{
	g_nXmlDbKeysRef--;

	if (g_nXmlDbKeysRef == 0)
	{
		delete g_pXmlDbKeys;
		g_pXmlDbKeys = NULL;
	}

}