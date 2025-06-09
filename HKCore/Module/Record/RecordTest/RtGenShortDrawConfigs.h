// RtGenShortDrawConfigs.h: interface for the CRtGenShortDrawConfigs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTGENSHORTDRAWCONFIGS_H__213BFD9F_74A1_479C_8443_AE72F8A25F96__INCLUDED_)
#define AFX_RTGENSHORTDRAWCONFIGS_H__213BFD9F_74A1_479C_8443_AE72F8A25F96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\MODULE\BASECLASS\ExBaseList.h"

class CRtGenShortDrawConfigs : public CExBaseList  
{
public:
	static CRtGenShortDrawConfigs *g_pRtGenShortDrawConfigs;
	static CRtGenShortDrawConfigs* CreategRtGenShortDrawConfigs();
	static long  g_nRtGenShortDrawConfigsCount;
	static long  Release();	

public:
	virtual UINT GetClassID()				{	return RTCLASSID_GENSHORTDRAWCONFIGS;		}
	virtual CExBaseObject* CreateNewChild()	{	return NULL;		}
	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID) {	return NULL;		}
	virtual CExBaseObject* CreateNewChild(long nClassID);
	void InitDrawConfigs(CUIDraws *pDraws);
	
private:
	CRtGenShortDrawConfigs();
	virtual ~CRtGenShortDrawConfigs();

};

#endif // !defined(AFX_RTGENSHORTDRAWCONFIGS_H__213BFD9F_74A1_479C_8443_AE72F8A25F96__INCLUDED_)
