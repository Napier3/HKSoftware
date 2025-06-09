// RtMemBufScript.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RTMEMBUFSCRIPT_H__)
#define _RTMEMBUFSCRIPT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../RtScriptBase/RtScriptBase.h"
#include "../RecordGlobalDefine.h"

//复合缓冲区最大的源缓冲区个数
#define  COMPLEX_MEMBUFFER_SRCBUF_MAXCOUNT  32

float* rt_GetMemValueFloatRefByID(char *pszID);
unsigned short* rt_GetMemValueUnsingedShortRefByID(char *pszID);
long rt_GetMemValueFIFOIndexByID(char *pszID);

class CRtComplexBufLongScript : public CRtScriptBase
{
public:
	CRtComplexBufLongScript();
	virtual ~CRtComplexBufLongScript();

	virtual void* GetValueRefByID(char *pszID)
	{
		return rt_GetMemValueUnsingedShortRefByID(pszID);
	}

	virtual BOOL ReleaseExpNodes();
	
protected:
	virtual BOOL CalExpNode(PEXPNODE pNode, UINT nIndex=0);
	virtual double CalNode(PEXPNODE pNode, UINT nIndex=0);
	
};

class CRtComplexBufUShortScript : public CRtScriptBase
{
public:
	CRtComplexBufUShortScript();
	virtual ~CRtComplexBufUShortScript();
	
	virtual void* GetValueRefByID(char *pszID)
	{
		return NULL;
	}
	
	virtual BOOL ReleaseExpNodes();
	
protected:
	virtual BOOL CalExpNode(PEXPNODE pNode, UINT nIndex=0);
	
};


class CRtComplexBufUShortFloatScript : public CRtScriptBase
{
public:
	CRtComplexBufUShortFloatScript();
	virtual ~CRtComplexBufUShortFloatScript();
	
	virtual void* GetValueRefByID(char *pszID)
	{
		return rt_GetMemValueUnsingedShortRefByID(pszID);
	}
	virtual double GetCoefValueByID(char *pszID);
	
	virtual BOOL ReleaseExpNodes();
	
protected:
	virtual BOOL CalExpNode(PEXPNODE pNode, UINT nIndex=0)   {  return TRUE;  };
	virtual double CalNode(PEXPNODE pNode, UINT nIndex=0);
	
};


#endif // !defined(_RTMEMBUFSCRIPT_H__)
