#pragma once

#include "PxProtocolImpInterface.h"
#include "PxProtoEventInterface.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "PxProtocolBase.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

class CPxProtoDeviceBase:public CPxProtocolImpInterface,public CExBaseList
{//m_strID:DeviceID
public:
	CPxProtoDeviceBase();
	virtual ~CPxProtoDeviceBase();

	CDvmDevice m_oDvmDevice;				//����ģ��
	CPxProtocolBase *m_pPxProtocol;			//��Լģ��ָ��
	CString m_strIotEngineSN;//��ǰ���Ե�iotengine

	//�����б�
	CExBaseList m_listRcvPkg;
	CExBaseList m_listSendPkg;

	CWnd* m_pDatasetView;

	void AttachProtoEventInterface(CPxProtoEventInterface *pProtoEventInterface);

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

	//��ȡ����δ����ı��ģ����ڹ��̴���
	void GetNotProcessedPkgs(CExBaseList &oList);
	
	//ɾ��������Ч���ģ���֤������Ϊ��
	void DeleteUnvalidPkgs(SYSTEMTIME &tmCur,long nValidTimeLong);

	//��������ҵ�����߼�
	void ProcessPkg(char *pBuf,long nLen);


	//����ָ�����ݼ�
	CDvmDataset *UpdateDataset(CDvmDataset *pSrcDataset);
	
	//Engine���ýӿڣ�����Э���¼�����
	void OnPrcdrFinished(const CString &strEventID,CDvmDataset *pDataset);
public:
	CPxProtoEventInterface *m_pProtoEventInterface;	//����Э���¼����أ�����ָ��CIotEngineTo

	//CloseDeviceʱ����ɾ����־�������߳���ͳһɾ��
	BOOL m_bCanDelete;	
};
