#pragma once
#include "../../../module/baseclass/exbaselist.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../../Module/DataMngr/DvmDevice.h"

class CPpRecordMngr :	public CExBaseList
{
public:
	CPpRecordMngr();
	virtual ~CPpRecordMngr(void);

public:
	LONG RecordPackage(const CString &strPkgID);
	LONG UnRecordPackage(const CString &strPkgID);
	BOOL IsPackageIDExist(const CString &strPkgID);

	CDvmData* AddPackage(CExBaseObject *pPkg);
	void DeleteAllPackage();

	void OnProcedureExit(const CString &strProcedureID);
	void OnProcedureStart(const CString &strProcedureID);
	
	LONG RecordProcedure(const CString &strProcedureID);
	LONG UnRecordProcedure(const CString &strProcedureID);
	void SetPackageDataset(CDvmDataset *pDataset)	{	m_pPackageDataset = pDataset;	}

	BOOL CanRecordPackage()	{	return m_bCanRecordPackage;	}

	void OnDeleteAllRecordPackage();
private:
	CStringArray m_astrPackageID;
	BOOL m_bRecordAllPackage;
	CString m_strProcedureRecord;
	BOOL m_bCanRecordPackage;
	CDvmDataset *m_pPackageDataset;

	CAutoCriticSection m_oRecordAutoCriticSection;
};
