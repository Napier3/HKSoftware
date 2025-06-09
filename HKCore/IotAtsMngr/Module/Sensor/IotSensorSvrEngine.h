#pragma once

#include "../../../Module/DataMngr/DvmDevices.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "../EngineServer/MqttEngineBase.h"
#include "RTDeviceCtrl/RTDeviceCtrl.h"
#include "IotPpTemplate/IotPpTemplate.h"
#include "RTDeviceCtrl/IotPpProcedureRun.h"
#include "..\..\..\Module\mysqlapp\mysqlbaseapp.h"

/**************************************
������Э�������ģ��:
1��ȫ��Ψһ����g_pIotSensorSvrEngine��Mqtt�ͻ���
2�����Ĵ�����ҵ��������Monitor��
3������ʵʱװ���б�m_listRTDevice�������б�m_listPrcdr����Լģ���б�m_listTemplate

��CreateDeviceʱ������װ���б��������򴴽����װ���б�͹�Լģ���б�
��CloseDeviceʱ��ɾ��ָ��װ�ú͹����Ĺ��̣�

��ȫ�ֹ��̴����߳�Engine_ProcedureRunThread�У�
ѭ��ִ�й����б���ÿ�����̵�Run,����TRUE˵�����̽���
**************************************/

class CIotSensorSvrEngine:public CMqttEngineBase,public CMySqlBaseApp
{
public:
	CIotSensorSvrEngine();
	virtual ~CIotSensorSvrEngine();

	static CIotSensorSvrEngine *Create();
	static void Release();

public:
	CExBaseList m_listPrcdr;		//ִ�й����ܱ�
	CExBaseList m_listTempPrcdr;	//��ʱ��������
	CExBaseList m_listRTDevice;		//ʵʱװ���б�
	CExBaseList m_listTemplate;		//��Լģ������
	CAutoCriticSection m_oPrcdrTmpCriticSection;  //m_listTmpPrcdr���ʵĻ�����
	BOOL m_bInsertHisDataTimer;

	void InitMySql();
	//������ݿ�ʵʱװ�ñ�����������룬���������
	BOOL UpdateRTDeviceData(const CString &strDeviceID,CDvmDataset *pDataset,BOOL bWarning);
	//��ѯ�����������ݱ�д���Ӧ����ʷʵʱ����
	BOOL UpdateRTDeviceHisData(const CString &strDeviceID,CDvmDataset *pDataset);
	//��ѯ�豸���ж��ǻ�������豸������л���������ݲ���
	BOOL UpdateMonitorData(const CString &strDeviceID, CDvmDataset *pDataset);
	//���¸澯�¼�����Ҫ�����豸������ȷ�ϸ澯����
	BOOL UpdateWarningEvent(const CString &strDeviceType, const CString &strDeviceID, CDvmDataset *pDataset);
	//��MainFrame����Ϣ����ʱ����RTDeviceHisData
	void PostRTDeviceHisDataMessage(CRTDeviceCtrl *pDeviceCtrl);
	//����װ���б�ɾ����Чװ�úͱ���
	void DeleteUnvalidDeviceAndPkgs();
	//ɾ��װ��֮ǰ,ɾ�����и�װ�õĹ���
	virtual void DeleteDeviceProcedureRun(CRTDeviceCtrl *pRTDeviceCtrl);
	//����Ϣ���ڣ����ڷ���ʱ�������ݼ�ˢ����ʾ��
	void AttachMsgWnd(CWnd *pWnd)	{	m_pMsgWnd = pWnd;	}

	//Mqtt�ͻ��˳�ʼ��
	BOOL Init(const char *pszIP,long nPort);
	//Mqtt�ͻ������ݴ������
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);
	virtual void OnClose(char *pszErr);

	//��ȡRTDeviceCtrl,û���򴴽�
	CRTDeviceCtrl *GetRTDeviceCtrl(const CString &strDeviceID
		,const CString &strPpxmlFile,const CString &strDvmFile);
	//���ҹ�Լģ�����,û���򴴽�
	CIotPpTemplate *GetIotTemplate(const CString &strPpxmlFile);
	CRTDeviceCtrl *FindRTDeviceCtrl(const CString &strDeviceID);

	//��ӵ���ʱ����m_listTempPrcdr�У���Engine_*Thread��ѭ����ͷ����m_listTempPrcdr����ӵ�m_listPrcdr��
	void AddProcedureRun(CRTDeviceCtrl *pRTDeviceCtrlRef,CIotPpProcedure *pProcedure
		, CExBaseList *pInterface,CDvmDataset *pDataset,const CString &strRecordMode);

	//�̴߳���ӿ�
protected:
	void OnRunProcedure();
	void StartEngineThread();
	void ExitEngineThread() ;
	BOOL m_bExitEngineThread;
	CWinThread *m_pProcedureRunThread;
	static UINT Engine_ProcedureRunThread(LPVOID pParam);

private:
	CWnd *m_pMsgWnd;
};

extern CIotSensorSvrEngine *g_pIotSensorSvrEngine;
extern long g_nIotSensorSvrEngineRef;