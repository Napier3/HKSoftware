// RtScript.h: interface for the CRtScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTSCRIPT_H__A091A318_BCDE_4A5F_AC53_929BD234BD27__INCLUDED_)
#define AFX_RTSCRIPT_H__A091A318_BCDE_4A5F_AC53_929BD234BD27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../RtScriptBase/RtScriptBase.h"

double* rt_GetValueRefByID(const CString &strID);

//定值启动计算脚本
class CRtScript : public CRtScriptBase
{
public:
	CRtScript();
	virtual ~CRtScript();
	virtual void* GetValueRefByID(char *pszID)
	{
		return rt_GetValueRefByID(pszID);
	}
};

//属性值计算脚本和通道计算脚本
class CRtAttrScript : public CRtScriptBase
{
public:
	CRtAttrScript();
	virtual ~CRtAttrScript();
	virtual void* GetValueRefByID(char *pszID)
	{
		return rt_GetValueRefByID(pszID);//应该改为rt_GetAttrRefByID(pszID)
	}
	
};


#endif // !defined(AFX_RTSCRIPT_H__A091A318_BCDE_4A5F_AC53_929BD234BD27__INCLUDED_)
