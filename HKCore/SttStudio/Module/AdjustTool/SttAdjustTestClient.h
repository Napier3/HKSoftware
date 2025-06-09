//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttAdjustTestClient.h  CSttAdjustTestClient

#pragma once

#include "SttAdjDevice.h"
#include "SttMesLocalDb.h"

#include "..\..\..\Module\TestMacro\TestMacros.h"
#include "..\Engine\SttClientTestEngine.h"

#include "../../Module/SttTestAppConfig/SttTestAppConfigTool.h"
#include "..\..\Module\SttTestAppConfig\Dialog\SttTestAppConfigDlg.h"
#include "..\..\..\Module\BaseClass\SttFileTransferProgress.h"
#include "..\TestClient\SttTestClientBase.h"

#include "SttAdjustTestMacro.h"

#define STT_ADJUST_MACRO_ID_ModuleAttrs		_T("ModuleAttrs")
#define STT_ADJUST_MACRO_ID_DeviceAttrs		_T("DeviceAttrs")

#define WM_MEAS_DATA  (WM_USER + 1048)

class CSttAdjustTestClient : public CSttTestClientBase
{
public:
	CSttAdjustTestClient();
	virtual ~CSttAdjustTestClient();

	void InitTestMacros(CTestMacros*pTestMacros);
	void InitModuleOutput(const CString &strAdjMacroID);
	void InitAdjustTestItem(const CString &strAdjMacroID);
	void InitAdjustSwitch(const CString &strAdjMacroID);
	void InitAdjustThree(const CString &strAdjMacroID);

	//2021-9-22  lijunqing
	void InitTestMacro(const CString &strAdjMacroID, CSttAdjTest_Base *pAdjTest);

private:
	CTestMacros *m_pAdjustTestMacros;

public:
	CSttAdjTest_ModuleOutput *m_pAdjModuleOutput;
	CSttAdjTest_AdjustOne *m_pAdjModuleAdjust;
	CSttAdjTest_AdjustSwitch *m_pAdjustSwitch;
	CSttAdjTest_AdjustThree *m_pAdjModuleAdjustThree;

	//2021-9-22  lijunqing
	CSttAdjTest_AdjustOne2Points *m_pAdjustOne2Points;
	CSttAdjTest_AdjustOneAngle *m_pAdjustOneAngle;
	CSttAdjTest_AdjustOneFreq *m_pAdjustOneFreq;
	CSttAdjTest_AdjustOneDcZero *m_pAdjustOneDcZero;

	CDataGroup* GetFaultParas_ModuleOutput()	{	return m_pAdjModuleOutput->m_pFaultParas;	}
	CDataGroup* GetFaultParas_Adjust()	{	return m_pAdjModuleAdjust->m_pFaultParas;	}

	void TestConfig();
	void ModuleOutput();
	BOOL AdjustTest();
	BOOL AdjustThree();
	BOOL AdjustFPGAUpdate(CDataGroup *pMoudleDataGroup);//FPGA����
	//BOOL AdjustGetUTC();//��ȡUTCʱ��
	//BOOL AdjustSetUTC(CDataGroup *pUTCTime);//����UTCʱ��
	BOOL WriteFile();
	BOOL AdjustSwitch();
	BOOL BinaryOutput(CDataGroup *pBinary);
	BOOL SttSystemConfig(CDataGroup *pParas, BOOL bSendCmdAsync=FALSE, BOOL bDoEvents=TRUE);
	void StopTest();
	void CloseDevice();
	long AdjustWriteFile(const CString &strLocalFile);
	long AdjustReadFile(const CString &strLocalPath);
	long AdjustSendFile(const CString &strLocalFile,const CString &strRemoteFile);//2023-3-16 Zhouyy ���߶��ǹ̶�·���ļ��Ĵ���

	//2023/10/8 wjs ��SetUTC��GetUTC��RWCoefficent�ϲ���һ������
	BOOL AdjustMoudleParasCmdSend(CDataGroup *pMoudleDataGroup,const CString &strMacroID);

	//2021-9-28  lijunqing
	BOOL Adjust(CSttAdjTest_Base *pAdjustTest, const CString &strMacroID);
	BOOL AdjustOne2Points();
	BOOL AdjustOneAngle();
	BOOL AdjustOneFreq();
	BOOL AdjustOneDcZero();

// 	//2021-9-29  lijunqing
// 	BOOL Meas_Read();

public:
	void ConfigTest(CSttTestAppConfigTool *pTool);

public:
	//���Թ����¼��ӿ�
	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas);
// 	virtual long OnMeas(CDataGroup *pParas);

public:
	//2021-9-29  lijunqing
	BOOL Meas_Read();
	virtual long OnMeas(CDataGroup *pParas);

	CWnd *m_pMeasRcvWnd;
};

