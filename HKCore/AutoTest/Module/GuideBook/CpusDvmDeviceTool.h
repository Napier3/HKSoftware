#pragma once

#include "Cpus.h"
#include "../../Module/DataMngr/DvmDevice.h"


class CCpusDvmDeviceTool
{
public:
	CCpusDvmDeviceTool(void);
	virtual ~CCpusDvmDeviceTool(void);

public:
	void Cpus_to_DvmDevice(CCpus *pSrc, CDvmDevice *pDest);
	void DvmDevice_to_Cpus(CDvmDevice *pSrc, CCpus *pDest);

protected:
	void Cpu_to_DvmLdevice(CCpu *pSrc, CDvmLogicDevice *pDest);
	void DataSet_to_DvmDataset(CDataSet *pSrc, CDvmDataset *pDest);
	void DataObj_to_DvmData(CDataObj *pSrc, CDvmData *pDest);
	void DataObjValue_to_DvmValue(CDataObjValue *pSrc, CDvmValue *pDest);

	void DvmLdevice_to_Cpu(CDvmLogicDevice *pSrc, CCpu *pDest);
	void DvmDataset_to_DataSet(CDvmDataset *pSrc, CDataSet *pDest);
	void DvmData_to_DataObj(CDvmData *pSrc, CDataObj *pDest);
	void DvmValue_to_DataObjValue(CDvmValue *pSrc, CDataObjValue *pDest);
protected:
	CCpus *m_pCpus;
	CDvmDevice *m_pDvmDevice;
};
