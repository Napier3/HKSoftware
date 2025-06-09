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

//��ֵ��������ű�
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

//����ֵ����ű���ͨ������ű�
class CRtAttrScript : public CRtScriptBase
{
public:
	CRtAttrScript();
	virtual ~CRtAttrScript();
	virtual void* GetValueRefByID(char *pszID)
	{
		return rt_GetValueRefByID(pszID);//Ӧ�ø�Ϊrt_GetAttrRefByID(pszID)
	}
	
};


#endif // !defined(AFX_RTSCRIPT_H__A091A318_BCDE_4A5F_AC53_929BD234BD27__INCLUDED_)
