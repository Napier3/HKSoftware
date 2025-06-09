#pragma once

#include "../../ProtocolBase/PxProtocolImpInterface.h"
#include "../../ProtocolBase/PxProtoEventInterface.h"
#include "../../../../Module/DataMngr/DvmDevice.h"
#include "../IotPpTemplate/IotPpTemplate.h"
#include "../XSensorPkg.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

#define ENGINE_TO_PX_IOTXML	_T("IOTXML")
#define ENGINE_TO_PX_PPXML	_T("PPXML")

#define WM_ID_INSERT_RTDEVICEHISDATA  (WM_USER + 1119)

/****************************************
ʵʱװ���ࣺ
��CreateDeviceʱ����g_pIotSensorSvrEngine��m_listRTDevice����Ƿ���ڣ��������򴴽�
�൱��Э������࣬������Mqtt�ͻ���
****************************************/

class CRTDeviceCtrl:public CPxProtocolImpInterface,public CExBaseList
{//m_strID:DeviceID
public:
	CRTDeviceCtrl();
	virtual ~CRTDeviceCtrl();

	CDvmDevice m_oDvmDevice;				//����ģ��
	CIotPpTemplate *m_pIotTemplate;			//��Լģ��ָ��
	BOOL m_bInsertHisDataTimer;

	//������ҵ�����б�
	CExBaseList m_listRcvPkg;
	CExBaseList m_listSendPkg;

	//��ȡ����δ����ı��ģ����ڹ��̴���
	void GetNotProcessedPkgs(CExBaseList &oList);
	//ɾ��������Ч���ģ���֤������Ϊ��
	void DeleteUnvalidPkgs(SYSTEMTIME &tmCur,long nValidTimeLong);

public:
	//Э�鱻����ִ�нӿ�
	virtual long RunProcedure(const CString &strProcedureID,CExBaseList *pListDatas
		,CDvmDataset *pDataset,const CString &strRecordMode);
	virtual long PkgPrase(char *pBuf,long nLen,CDvmDataset &oRetDataset);
	virtual long PkgProduce(const CString &strProduceID,CDvmDataset &oDataset,char **ppBuf,long &nLen);
	virtual long GetDataset(const CString &strDatasetPath,CDvmDataset &oRetDataset);
	virtual long ConfigDevice(const CString &strConfig);
	virtual long CloseDevice();

	//��ʼ��Э�����ģ��
	virtual void InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);

	//��������ҵ�����߼�
	void ProcessSensorPkg(char *pBuf,long nLen);

	void AttachProtoEventInterface(CPxProtoEventInterface *pProtoEventInterface);
	//����ָ�����ݼ�
	CDvmDataset *UpdateDataset(CDvmDataset *pSrcDataset);
	//Engine���ýӿڣ�����Э���¼�����
	void OnPrcdrFinished(const CString &strEventID,CDvmDataset *pDataset);
public:
	CPxProtoEventInterface *m_pProtoEventInterface;	//����Э���¼����أ�����ָ��CIotEngineToSensor

	//CloseDeviceʱ����ɾ����־�������߳���ͳһɾ��
	BOOL m_bCanDelete;	
};

/////////////////////////////////////////////
//�����ݼ������б����ɵ�ʽ�����浽װ��ʵʱ���ݱ���
void GetEqualExprFromDataset(CDvmDataset *pDataset,CString &strExpr);