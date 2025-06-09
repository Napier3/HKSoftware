// RtGenShortDrawConfig.h: interface for the CRtGenShortDrawConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTGENSHORTDRAWCONFIG_H__1EC76D2B_B30E_472D_A9EC_384C259E1F5C__INCLUDED_)
#define AFX_RTGENSHORTDRAWCONFIG_H__1EC76D2B_B30E_472D_A9EC_384C259E1F5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\MODULE\BASECLASS\ExBaseObject.h"

class CRtGenShortDrawConfig : public CExBaseObject  
{
public:
	long m_nDrawState;
	CString m_strXVariableID;
	CString m_strYVariableID;

public:
	CRtGenShortDrawConfig();
	virtual ~CRtGenShortDrawConfig();
	virtual UINT GetClassID()	{	return RTCLASSID_GENSHORTDRAWCONFIG;	}	

};

#endif // !defined(AFX_RTGENSHORTDRAWCONFIG_H__1EC76D2B_B30E_472D_A9EC_384C259E1F5C__INCLUDED_)
