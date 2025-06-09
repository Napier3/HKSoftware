#ifndef CPPSTTIOTENGINEDEVICEBASE_H
#define CPPSTTIOTENGINEDEVICEBASE_H

#include "../../../../Module/DataMngr/DvmDevice.h"
#include "../../SttCmd/SttSysState.h"

class CPpSttIotEngineDeviceBase
{
private:
	CDvmDevice* m_pDvmDeviceRef;//引用外部指针,不应该由本类对象来释放

public:
	CPpSttIotEngineDeviceBase();
	virtual ~CPpSttIotEngineDeviceBase();

public:
	virtual void SetDeviceRef(CDvmDevice* pDeviceRef);
	virtual CDvmDevice* GetDeviceRef();

	virtual CSttSysState* GetDataset(const CString& strDeviceSN, const CString& strIDPath);
	virtual CSttSysState* SetDataset(CDvmDataset* pDataset, const CString& strDeviceSN, const CString& strIDPath);
};

#endif//!CPPSTTIOTENGINEDEVICEBASE_H