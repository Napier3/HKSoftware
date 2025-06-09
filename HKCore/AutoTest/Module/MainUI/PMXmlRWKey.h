#pragma once

#include "..\..\..\Module\BaseClass\BaseObject.h"

class CPMXmlRWKey :
	public CXmlRWKeys 
{
public:
	CPMXmlRWKey(void);
	~CPMXmlRWKey(void);

	static CPMXmlRWKey* g_pPMXmlRWKeys;
	static long g_nPMXmlRWKeysRef;
	static CPMXmlRWKey* Create();
	static void Release();
public:
	BSTR m_strMainUIConfig;
	BSTR m_strConfigFile;
	BSTR m_strVersion;
	BSTR m_strBtnWidth;
	BSTR m_strBmpFile;
	BSTR m_strProgram;
	BSTR m_strSize;
	BSTR m_strItalic;
	BSTR m_strBold;
	BSTR m_strColor;
	BSTR m_strBkColor;
	BSTR m_strFile;
	BSTR m_strShow;
	BSTR m_strOptr;
	BSTR m_strPara;
	BSTR m_strActiveVersion;
	BSTR m_strSubUICfgItem;

	BSTR m_strMacroUIConfig;
	BSTR m_strPage;
	BSTR m_strGroups;
	BSTR m_strGroup;
	BSTR m_strPageButton;
	BSTR m_strItem;
	BSTR m_strExec;
	BSTR m_strVisible;
	BSTR m_strFont;
	BSTR m_strSubUICfg;

	BSTR m_strPageButtons;
	
};
