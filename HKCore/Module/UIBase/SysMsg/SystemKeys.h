// SystemKeys.h: interface for the CSystemKeys class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMKEYS_H__06B7BA96_411E_4A6C_BC27_90A19F63E2A3__INCLUDED_)
#define AFX_SYSTEMKEYS_H__06B7BA96_411E_4A6C_BC27_90A19F63E2A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\MODULE\BASECLASS\ExBaseList.h"
#include "SystemKey.h"

class CSystemKeys : public CExBaseList  
{
public:
	CSystemKeys();
	virtual ~CSystemKeys();

public:
	static const char* g_pszKeySysKeys;
	
public:
	//XML¶ÁÐ´
	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	CSystemKey* FindByKeyName(const CString &strKeyName);
	CSystemKey* FindByKeyID(long nKeyID);
};

#endif // !defined(AFX_SYSTEMKEYS_H__06B7BA96_411E_4A6C_BC27_90A19F63E2A3__INCLUDED_)
