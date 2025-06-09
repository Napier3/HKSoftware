// SystemMessageMngr.h: interface for the CSystemMessageMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMMESSAGEMNGR_H__356FE362_4931_4AB1_9873_6349F2A92AA3__INCLUDED_)
#define AFX_SYSTEMMESSAGEMNGR_H__356FE362_4931_4AB1_9873_6349F2A92AA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\MODULE\BASECLASS\ExBaseMngr.h"
#include "SystemKeys.h"
#include "SystemMessages.h"
#include "AppSysKeyMaps.h"

//#define _SysMsg_WriteToFile

class CSystemMessageMngr : public CExBaseMngr  
{
public:
	static CSystemMessageMngr* g_pSystemMessageMngr;
	static long g_nSysMsgMngrRefCount;	
	static CSystemMessageMngr* CreateSystemMessageMngr();
	long   Release();

private:
	CSystemMessageMngr();
	virtual ~CSystemMessageMngr();

public:
	static const char* g_pszKeySystemMessageDefine;//system-message-define
	static const char* g_pszKeySystemMessageFile;

	CSystemKeys *m_pSystemKeys;
	CSystemMessages *m_pSingleSysMsgs;
	CSystemMessages *m_pMultiSysMsgs;
	CAppSysKeyMaps *m_pAppSysKeyMaps;
	CSystemMessages m_oSysMsgs;

	//系统消息时间长度
	DWORD  m_dwKeyDownTime;
	DWORD  m_dwKeyDownTimeAccel;
	DWORD  m_dwKeyDownTimeDoubleClick;
	
public:
	//XML读写
	BOOL ReadSystemMessageXmlFile();
	BOOL OpenXmlFile(const CString &strFile);
	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	long GetSystemMessageID(const CString &strSysMsg);
	
	//消息处理
	CSystemMessage* TranslateMessage(MSG *pMsg);
	BOOL HasSysMsgNeedPost();
	CSystemMessages* GetSystemMessages()   {      return &m_oSysMsgs;     }

private:
	BOOL   m_bHasInited;
	CSystemMessage* AddMessage(MSG *pMsg);
	CSystemMessage* AddMessage(CSystemMessageSingle *pSysMsg, MSG *pMsg, long nKeyState);
	CSystemMessage* AddKeyDownMessage(MSG *pMsg);
	CSystemMessage* AddKeyUpMessage(MSG *pMsg);
	CSystemMessage* AddClickMessage(MSG *pMsg);
	CSystemMessage* AddDbClickMessage(CSystemMessageSingle *pSysMsg, MSG *pMsg);
	
	void DeleteTopMessages();

//	CRITICAL_SECTION m_CriticalSection;
#ifdef _SysMsg_WriteToFile
	CFile m_oSysMsgFile;
	BOOL  m_bSysMsgFile;
public:
	void WriteSystemMessageFile();
#endif
};

long  SysMsg_GetSystemMessageID(const CString &strSysMsg);

#endif // !defined(AFX_SYSTEMMESSAGEMNGR_H__356FE362_4931_4AB1_9873_6349F2A92AA3__INCLUDED_)
