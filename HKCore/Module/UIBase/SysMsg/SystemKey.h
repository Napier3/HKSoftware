// SystemKey.h: interface for the CSystemKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMKEY_H__B2DC069D_3ECD_4459_9150_7BC52E823EC4__INCLUDED_)
#define AFX_SYSTEMKEY_H__B2DC069D_3ECD_4459_9150_7BC52E823EC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\MODULE\BASECLASS\ExBaseObject.h"

class CSystemKey : public CExBaseObject  
{
public:
	CSystemKey();
	virtual ~CSystemKey();

public:
	static const char* g_pszKeySysKey;
	
	long m_nID;   //¼üÖµ
public:
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
};

#endif // !defined(AFX_SYSTEMKEY_H__B2DC069D_3ECD_4459_9150_7BC52E823EC4__INCLUDED_)
