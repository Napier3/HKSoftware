#pragma once
#include "..\CfgDataMngr\StCfgData6044.h"
#include "..\CfgDataMngr\StCfgData91.h"
#include "..\CfgDataMngr\StCfgData92.h"
#include "..\CfgDataMngr\StCfgDataGin.h"
#include "..\CfgDataMngr\StCfgDataGout.h"

#include "CapDevice\StCapDevice91.h"
#include "CapDevice\StCapDevice92.h"
#include "CapDevice\StCapDeviceGoose.h"


class CCapDeviceToCfgDataTool
{
public:
	CCapDeviceToCfgDataTool(void);
	~CCapDeviceToCfgDataTool(void);

	//添加到配置数据
	BOOL CreateCfgData91(CStCapDevice91 *pCapDevice);
	BOOL CreateCfgData92(CStCapDevice92 *pCapDevice);
	BOOL CreateCfgDataGin(CStCapDeviceGoose *pCapDevice);
	BOOL CreateCfgDataGout(CStCapDeviceGoose *pCapDevice);

	//覆盖配置数据
	BOOL OverwriteCfgData(CStCapDeviceBase *pCapDevice, CStCfgDataBase *pCfgData);
	BOOL OverwriteCfgData(CStCapDevice91 *pCapDevice, CStCfgData91 *pCfgData);
	BOOL OverwriteCfgData(CStCapDevice92 *pCapDevice, CStCfgData92 *pCfgData);
	BOOL OverwriteCfgData(CStCapDeviceGoose *pCapDevice, CStCfgDataGin *pCfgData);
	BOOL OverwriteCfgData(CStCapDeviceGoose *pCapDevice, CStCfgDataGout *pCfgData);

	
	UINT m_nCfgDataClassID;
	BOOL m_bUseChs;
protected:
	CStCfgDataBase *m_pCfgData;

	void CopyDataFromCapDeviceToCfg(CStCapDevice91 *pCapDevice, CStCfgData91 *pCfgData);
	void CopyDataFromCapDeviceToCfg(CStCapDevice92 *pCapDevice, CStCfgData92 *pCfgData);
	void CopyDataFromCapDeviceToCfg(CStCapDeviceGoose *pCapDevice, CStCfgDataGin *pCfgData);
	void CopyDataFromCapDeviceToCfg(CStCapDeviceGoose *pCapDevice, CStCfgDataGout *pCfgData);
	//void CopyDataFromCapDeviceToCfg(CStCfgData6044 *pCfgData);

};
