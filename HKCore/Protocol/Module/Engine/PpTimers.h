#pragma once
#include "../../../module/baseclass/exbaselist.h"
#include "ProtocolXmlRWKeys.h"
#include "PpTimer.h"


class CPpNode;

class CPpTimers :	public CExBaseList
{
public:
	CPpTimers(void);
	virtual ~CPpTimers(void);

public:
	virtual UINT GetClassID(){ return PPCLASSID_PPTIMERS; };
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpTimersKey;     }

public:
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	

public:
	void BeginTimer();
	void ResetTimer();
	void KillTimer();
	CPpNode* RunTimer(DWORD dwCurrTick);
};
