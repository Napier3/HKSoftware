#pragma once

#include "GbWzdAiBase.h"

class CGbAiOptrAnd :public CGbAiOptrBase
{
public:
	CGbAiOptrAnd(void);
	virtual ~CGbAiOptrAnd(void);

public:
	//Serialize mathods
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiDATASCPTOPTR_AND;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataScptOptrAndKey ;	}

	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);
};

class CGbAiOptrOr :public CGbAiOptrBase
{
public:
	CGbAiOptrOr(void);
	virtual ~CGbAiOptrOr(void);

public:
	//Serialize mathods
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiDATASCPTOPTR_OR;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataScptOptrOrKey ;	}

	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);
};


class CGbAiOptrNot :public CGbAiOptrBase
{
public:
	CGbAiOptrNot(void);
	virtual ~CGbAiOptrNot(void);

public:
	//Serialize mathods
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiDATASCPTOPTR_NOT;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataScptOptrNotKey ;	}

	virtual CBaseObject* Clone();

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);
};
