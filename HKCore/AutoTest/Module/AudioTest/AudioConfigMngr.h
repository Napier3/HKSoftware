#ifndef _AUDIOCONFIGMNGR_H_
#define _AUDIOCONFIGMNGR_H_

#include "MatchKeyWords.h"
#include "Audio/AudioTestWords.h"

//���ù���ģ��
class CAudioConfigMngr
{
public:
	CDvmDataset m_oAppConfig;			//��������ļ�
	CAudioTestWords* m_pAudioConfig;		//���������ļ�
	CMatchKeyWords m_oMatchWords;

	CDvmDataset m_DlgConfig;			//�����������
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