// AppSysKeyMap.h: interface for the CAppSysKeyMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPSYSKEYMAP_H__9F22941E_CB6D_4DCB_B8C7_6AA17B8B0286__INCLUDED_)
#define AFX_APPSYSKEYMAP_H__9F22941E_CB6D_4DCB_B8C7_6AA17B8B0286__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\MODULE\BASECLASS\ExBaseObject.h"

class CAppSysKeyMap : public CExBaseObject  
{
public:
	CAppSysKeyMap();
	virtual ~CAppSysKeyMap();

public:
	//Ϊ�˴����ϵķ��㣬��m_strName�ȼ���m_strAppKey��m_strID�ȼ���m_strSysKey
	static const char* g_pszKeyAppKey;
	static const char* g_pszKeySysKey;
	
public:
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
};

#endif // !defined(AFX_APPSYSKEYMAP_H__9F22941E_CB6D_4DCB_B8C7_6AA17B8B0286__INCLUDED_)
