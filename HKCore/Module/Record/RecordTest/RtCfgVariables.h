// RtCfgVariables.h: interface for the CRtCfgVariables class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCFGVARIABLES_H__649F29A1_0F6B_4DCE_A596_BA1D15D76DBD__INCLUDED_)
#define AFX_RTCFGVARIABLES_H__649F29A1_0F6B_4DCE_A596_BA1D15D76DBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseList.h"
#include "RtCfgVariable.h"


class CRtCfgVariables : public CExBaseList  
{
public:
	CRtCfgVariables();
	virtual ~CRtCfgVariables();

//属性
public:
	//关键字属性
	static const char *g_pszKeyVariables;

	CExBaseList m_oUVariList;
	CExBaseList m_oIVariList;
	CExBaseList m_oBVariList;
	
//方法
public:
	//重载的方法
	virtual UINT GetClassID()         {    return RTCLASSID_CFGVARIABLES;    };
	virtual CExBaseObject* CreateNewChild(const char *pszClassID);	
};

#endif // !defined(AFX_RTCFGVARIABLES_H__649F29A1_0F6B_4DCE_A596_BA1D15D76DBD__INCLUDED_)
