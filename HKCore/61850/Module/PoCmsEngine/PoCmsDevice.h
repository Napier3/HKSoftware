
#pragma once

#include "../PoEngine/PoMmsDevice.h"

class CPoCmsDevice : public CPoMmsDevice
{
public:
	CPoCmsDevice();
	virtual ~CPoCmsDevice();

	void InitRegisterRptPara();
	void InitChangeSetZone(long &nZone,long nLdIndex);
	virtual void InitReadJournalFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, const CString &strDsPath);
	virtual BOOL WriteEnaOne(long nDeviceIndex, long  nLdIndex);
	virtual BOOL ReadOne();
	virtual long UnLoad(void);

public:
	virtual long CommConfig(const CString &strCmmConfig);
	virtual CPoMmsLogicDevice* GetItem(long nIndex);
	virtual CPoMmsDataSet* FindDataSet(const CString &strDataSetName);
	virtual long RunProcedure(const CString &strProcedureID, const CString &strDatasetPath);

	//2020-9-8  lijunqing
	virtual BOOL InitCmmConfig(CDataGroup *pGroup, BOOL bConnect);

protected:
	virtual void InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart, const CString &strDsPath);
	virtual void InitStopReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, const CString &strDsPath);

	virtual BOOL Run_CMDID_writesetting(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex);
	virtual void Run_CMDID_writeena(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex, const CString &strTitle, const char* pszKey);
	virtual void Run_CMDID_readena(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex);
	virtual long IniSetWriteFuncParasEx(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex, long nZone);
	virtual void Run_CMDID_readsetting(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex);
	virtual void Run_CMDID_readparameter(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex);
};


