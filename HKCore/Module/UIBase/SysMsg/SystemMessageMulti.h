// systemmessagemulti.h: interface for the CSystemMessageMulti class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMMESSAGEMULTI_H__6E85BB3C_7603_41B1_AB61_C183FB6112BC__INCLUDED_)
#define AFX_SYSTEMMESSAGEMULTI_H__6E85BB3C_7603_41B1_AB61_C183FB6112BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SystemMessage.h"
#include "SystemKeys.h"

#define MULTI_SYSMSG_MODE_ORDER       0
#define MULTI_SYSMSG_MODE_ATONETIME   1

class CSystemMessages;

class CSystemMessageMulti : public CSystemMessage  
{
public:
	CSystemMessageMulti();
	virtual ~CSystemMessageMulti();

public:
	static const char* g_pszKeyMode;
	static const char* g_pszKeyMultiSysMsg;
	static const char* g_pszKeyModeOrder;
	static const char* g_pszKeyModeAtOneTime;

	long   m_nMode;
	CDWordArray m_anSingleSysMsg;

private:
	CStringArray m_astrSingleSysMsg;

public:
	virtual UINT GetClassID()      {     return CLASSID_SYSTEMMESSAGE_MULTI;    }
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);

public:
	void InitMultiSystemMessage(CSystemMessages *pSingleSysMsgs);

	CSystemMessage* Clone();
		
};

#endif // !defined(AFX_SYSTEMMESSAGEMULTI_H__6E85BB3C_7603_41B1_AB61_C183FB6112BC__INCLUDED_)
