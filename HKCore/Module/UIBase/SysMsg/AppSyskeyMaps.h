// appsyskeymaps.h: interface for the CAppSysKeyMaps class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPSYSKEYMAPS_H__2A94FBCC_92C3_48D7_9EA9_2DCAB4EE36A4__INCLUDED_)
#define AFX_APPSYSKEYMAPS_H__2A94FBCC_92C3_48D7_9EA9_2DCAB4EE36A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\MODULE\BASECLASS\ExBaseList.h"
#include "AppSysKeyMap.h"

class CAppSysKeyMaps : public CExBaseList  
{
public:
	CAppSysKeyMaps();
	virtual ~CAppSysKeyMaps();

public:
	static const char* g_pszKeyAppName;
	static const char* g_pszKeyKeyMaps;

	CString m_strAppName;
public:
	//XML¶ÁÐ´
	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
};

#endif // !defined(AFX_APPSYSKEYMAPS_H__2A94FBCC_92C3_48D7_9EA9_2DCAB4EE36A4__INCLUDED_)
