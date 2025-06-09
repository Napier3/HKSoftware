#include "StdAfx.h"
#include "PMXmlRWKey.h"

CPMXmlRWKey* CPMXmlRWKey::g_pPMXmlRWKeys = NULL;
long  CPMXmlRWKey::g_nPMXmlRWKeysRef = 0;

CPMXmlRWKey::CPMXmlRWKey(void)
{
	//MainUIConfig
	m_strMainUIConfig = L"PMMainConfig";
	m_strActiveVersion = L"active-version";
	m_strVersion = L"Version";
	m_strSubUICfgItem = L"SubUICfgItem";
	m_strConfigFile= L"cfg-file";

	//SubUIConfig
	m_strSubUICfg = L"SubUIConfig";

	//page
	m_strPage = L"page";
	m_strBtnWidth = L"btn-width";

	//font
	m_strFont = L"font";
	m_strSize = L"size";
	m_strItalic = L"italic";
	m_strBold = L"bold";
	m_strColor = L"color";
	m_strBkColor = L"bkcolor";

	//Groups
	m_strGroups = L"Groups";
	m_strGroup = L"Group";

	//UIItem
	m_strItem = L"UIItem";
	m_strProgram = L"program";
	m_strFile = L"file";
	m_strShow = L"show";
	m_strBmpFile = L"bmp-file";

	//PageButtons
	m_strPageButtons = L"PageButtons";

	//PageButton	
	m_strPageButton = L"PageButton";
	m_strOptr = L"optr";
	m_strPara = L"para";

}

CPMXmlRWKey::~CPMXmlRWKey(void)
{
}

//从XML节点中读取关键字


CPMXmlRWKey* CPMXmlRWKey::Create()
{
	g_nPMXmlRWKeysRef++;

	if (g_pPMXmlRWKeys == NULL)
	{
		g_pPMXmlRWKeys = new CPMXmlRWKey();
	}

	return g_pPMXmlRWKeys;
}

void CPMXmlRWKey::Release()
{
	g_nPMXmlRWKeysRef--;

	if (g_nPMXmlRWKeysRef == 0)
	{
		delete g_pPMXmlRWKeys;
		g_pPMXmlRWKeys = NULL;
	}
}