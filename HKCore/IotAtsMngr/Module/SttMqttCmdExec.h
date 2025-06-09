#pragma once

#include "SensorProtocol/SttGlobalSensorDef.h"
#include "PpProject/PpPrjDevices.h"
#include "MqttPpTemplate/MqttPpTemplate.h"
#include "../../Module/DataMngr/DvmDevice.h"

#define MODEL_DEVICE_ID_Attr		_T("dsDeviceAttr")
#define ATS_ID_ItemPath				_T("item-path")

enum _tagEngineSystemDefine
{//2020-5-21  lijunqing
	engineConnectDeviceFailed= 1, //0,
	engineConnectDeviceSuccessful=2, //1,
	engineCommError = 3, //2,
	engineCommFinish = 4, //3,
	engineCommCmdError=5, //4
	engineException=6 //5
};

class CSttMqttCmdExec : public CExBaseList
{
public:
	CSttMqttCmdExec(const CString &strPpTemplateFile, const CString &strDeviceFile,const CString &strDeviceID);
	virtual ~CSttMqttCmdExec();

	//�ⲿ��Ϣ����
	unsigned long  m_hMsgWnd;
	unsigned long  m_nMsg;
	unsigned long  m_hSysMsgWnd;
	unsigned long  m_nSysMsg;	

	CString m_strCurItemPath;			//��ǰ������
	CDvmDataset *m_pModelDataset;		//��ǰ�������ݼ�
	CDvmDevice m_oDvmDevice;			//�����豸ģ��
	CPpPrjDevices *m_pPrjDevices;		//װ���б�
	CMqttPpTemplate m_oMqttPpTemplate;	//��Լģ��

	virtual BOOL OnMqttMsgRecieve(CPpPrjDevice *pPrjDevice,char *pBuf,long nLen);
	virtual void OnTestItemFinish();
public:
	BOOL ConnectDevice();
	BOOL IsConnectSuccessful();
	long RunProcedure(const CString &strProcedureID, const CString &strDsID);

	CDvmDataset *GetDeviceAttr();
	CDvmDataset *FindDataset(const CString &strDatasetID);
	BOOL GetDeviceAttrValueByID(const CString &strID,CString &strValue);
	BOOL GetDeviceAttrValueByID(const CString &strID,long &nValue);

public:
	BOOL IsTestItemFinish();
	void SetSuspendThread();

protected:
	BOOL m_bExitThread;
	BOOL m_bSuspendThread;

	//��鵱ǰItem�Ƿ���ɻ�ʱ�߳�
	HANDLE m_pThread;
	static void *TestCmdExecThread(LPVOID lParam);
};

//////////////////////////////
void CommVm_PostDeviceSysMessage(CSttMqttCmdExec *pTestCtrl, WPARAM wParam, LPARAM lParam);
void CommVm_PostDeviceCommCmdMessage(CSttMqttCmdExec *pTestCtrl, WPARAM wParam, LPARAM lParam);
CString GetIDFromPath(const CString &strPath,char chSeperator='$');