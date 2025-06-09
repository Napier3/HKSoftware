// SystemMessageSingle.h: interface for the CSystemMessageSingle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMMESSAGESINGLE_H__D7064B1B_F0AF_4DA6_9504_52B1DEB644D7__INCLUDED_)
#define AFX_SYSTEMMESSAGESINGLE_H__D7064B1B_F0AF_4DA6_9504_52B1DEB644D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SystemMessage.h"
#include "SystemKeys.h"
class CSystemMessages;

#define KEYSTATE_ERROR    -1
#define KEYSTATE_DOWN     0
#define KEYSTATE_UP       1
#define KEYSTATE_CLICK    2
#define KEYSTATE_DBCLICK  3

class CSystemMessageSingle : public CSystemMessage  
{
public:
	CSystemMessageSingle();
	virtual ~CSystemMessageSingle();

public:
	CString m_strKeyName;
	long    m_nKeyState;
	DWORD   m_nSysKeyID;
	
	static const char* g_pszKey_KeyName;
	static const char* g_pszKey_KeyState;
	static const char* g_pszKeySingleSysMsg;

	static const char* g_pszKey_KeyStateDown;
	static const char* g_pszKey_KeyStateUp;
	static const char* g_pszKey_KeyStateClick;
	static const char* g_pszKey_KeyStateDbClick;
	
public:
	virtual UINT GetClassID()      {     return CLASSID_SYSTEMMESSAGE_SINGLE;    }
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);

public:
	void InitSingleSystemMessage(CSystemKeys *pSysKeys);

	virtual CSystemMessage* Clone();
	static long GetSysKeyState(UINT nMsg, long &nKeyState);
	
	BOOL IsKeyDown(UINT nKeyID)    {    return ((m_nSysKeyID == nKeyID) && (m_nKeyState == KEYSTATE_DOWN));      }
	BOOL IsKeyUp(UINT nKeyID)      {    return ((m_nSysKeyID == nKeyID) && (m_nKeyState == KEYSTATE_UP));        }
	BOOL IsKeyClick(UINT nKeyID)   {    return ((m_nSysKeyID == nKeyID) && (m_nKeyState == KEYSTATE_CLICK));     }
	BOOL IsKeyDbClick(UINT nKeyID) {    return ((m_nSysKeyID == nKeyID) && (m_nKeyState == KEYSTATE_DBCLICK));   }
	BOOL IsKeyDown()               {    return (m_nKeyState == KEYSTATE_DOWN);                                   }
	BOOL IsKeyUp()                 {    return (m_nKeyState == KEYSTATE_UP);                                     }
	BOOL IsKeyClick()              {    return (m_nKeyState == KEYSTATE_CLICK);                                  }
	BOOL IsKeyDbClick()            {    return (m_nKeyState == KEYSTATE_DBCLICK);                                }
};

inline BOOL SysMsg_IsSingle(CSystemMessage *pSysMsg)      {    return (pSysMsg->GetClassID() ==  CLASSID_SYSTEMMESSAGE_SINGLE);   }
BOOL SysMsg_IsKeyDown(CSystemMessage *pSysMsg, UINT nKeyID);
BOOL SysMsg_IsKeyUp(CSystemMessage *pSysMsg, UINT nKeyID);
BOOL SysMsg_IsKeyClick(CSystemMessage *pSysMsg, UINT nKeyID);
BOOL SysMsg_IsKeyDbClick(CSystemMessage *pSysMsg, UINT nKeyID);
BOOL SysMsg_IsKeyDown(CSystemMessage *pSysMsg);
BOOL SysMsg_IsKeyUp(CSystemMessage *pSysMsg);
BOOL SysMsg_IsKeyClick(CSystemMessage *pSysMsg);
BOOL SysMsg_IsKeyDbClick(CSystemMessage *pSysMsg);

#endif // !defined(AFX_SYSTEMMESSAGESINGLE_H__D7064B1B_F0AF_4DA6_9504_52B1DEB644D7__INCLUDED_)
