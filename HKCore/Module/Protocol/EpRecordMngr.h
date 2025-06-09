#pragma once
#include "..\baseclass\exbaselist.h"
#include "..\CriticalSection\SynCriticalSection.h"

class CEpRecordMngr :	public CExBaseList
{
public:
	CEpRecordMngr();
	~CEpRecordMngr(void);

public:
	LONG RecordFrame(const CString &strPkgID);
	LONG UnRecordFrame(const CString &strPkgID);
	BOOL IsFrameIDExist(const CString &strPkgID);

	void AddFrame(CExBaseObject *pPkg);
	void DeleteAllFrame();

private:
	CStringArray m_astrFrameID;

	CAutoCriticSection m_oAutoCriticSection;
};
