// SystemMessages.h: interface for the CSystemMessages class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMMESSAGES_H__D12109C9_910C_4C60_A87A_310678BAD08F__INCLUDED_)
#define AFX_SYSTEMMESSAGES_H__D12109C9_910C_4C60_A87A_310678BAD08F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\MODULE\BASECLASS\ExBaseList.h"
#include "SystemMessageSingle.h"
#include "SystemMessageMulti.h"

class CSystemMessages : public CExBaseList  
{
public:
	CSystemMessages();
	virtual ~CSystemMessages();

public:
	static const char* g_pszKeySingleSysMsgs;
	static const char* g_pszKeyMultiSysMsgs;
	
public:
	//XML¶ÁÐ´
	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
public:
	void InitSingleSystemMessages(CSystemKeys *pSysKeys);
	void InitMultiSystemMessages(CSystemMessages *pSingleSysMsgs);

	CSystemMessageSingle* FindSingleSysMsg(UINT nKeyID, long nKeyState);
};

#endif // !defined(AFX_SYSTEMMESSAGES_H__D12109C9_910C_4C60_A87A_310678BAD08F__INCLUDED_)
