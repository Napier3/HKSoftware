// SystemMessage.h: interface for the CSystemMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMMESSAGE_H__ACE54457_89A0_43C2_8605_637D7AB48138__INCLUDED_)
#define AFX_SYSTEMMESSAGE_H__ACE54457_89A0_43C2_8605_637D7AB48138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\MODULE\BASECLASS\ExBaseObject.h"

#define CLASSID_SYSTEMMESSAGE           (CLASSID_BASECLASS+0X00001000)
#define CLASSID_SYSTEMMESSAGE_SINGLE    (CLASSID_SYSTEMMESSAGE+0X00000001)
#define CLASSID_SYSTEMMESSAGE_MULTI     (CLASSID_SYSTEMMESSAGE+0X00000002)

#define NONE_SYSTEMMESSAGEID     ("none")

class CSystemMessage : public CExBaseObject  
{
public:
	CSystemMessage();
	virtual ~CSystemMessage();

public:
	long  m_nID;
	long  m_nIndex;
	DWORD m_dwTickCount;
	BOOL  m_bMsgHasPosted;

public:
	virtual UINT GetClassID()      {     return CLASSID_SYSTEMMESSAGE;    }
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual CSystemMessage* Clone() = 0;
};

#endif // !defined(AFX_SYSTEMMESSAGE_H__ACE54457_89A0_43C2_8605_637D7AB48138__INCLUDED_)
