#ifndef _AUDIOCONFIGMNGR_H_
#define _AUDIOCONFIGMNGR_H_

#include "MatchKeyWords.h"
#include "Audio/AudioTestWords.h"

//配置管理模块
class CAudioConfigMngr
{
public:
	CDvmDataset m_oAppConfig;			//软件配置文件
	CAudioTestWords* m_pAudioConfig;		//语音配置文件
	CMatchKeyWords m_oMatchWords;

	CDvmDataset m_DlgConfig;			//界面参数配置
	CDvmData* m_pInspectData;
	CDvmData* m_pDeviceData;
	CDvmData* m_pProtocolData;
public:
	CAudioConfigMngr();
	virtual ~CAudioConfigMngr();

	BOOL InitConfig();
	void SaveConfig();

	void SetConfigValue(CString strID, CString strValue);
	CString GetConfigValue(CString strID);
};

#endif