#pragma once
#include "SttTestClientBase.h"
#include "../SttTestAppConfig/SttTestDeviceCfg.h"
#include "../SttCmd/SttIotCmd.h"

class CPpSttIotClient :	public CSttTestClientBase
{
public:
	CPpSttIotClient(void);
	virtual ~CPpSttIotClient(void);

public:
	//��ʱ��д�������濼����������
	CSttTestDeviceCfg m_oTestDeviceCfg;   //�������ã����÷���˵�IP���˿�

public:
	virtual long SendIotCmd(CSttIotCmd &oIotCmd);
	virtual BOOL ConnectSttServer();

	//2022-11-15  lijunqing
	void InitSttTestDeviceCfg(const CString &strCfgFile);
};
