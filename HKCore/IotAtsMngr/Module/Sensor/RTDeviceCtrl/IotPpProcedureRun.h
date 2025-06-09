#pragma once

#include "../IotPpTemplate/IotPpTemplate.h"
#include "../XSensorPkg.h"

class CRTDeviceCtrl;

class CIotPpProcedureRun : public CExBaseObject
{//m_strID:DeviceID
private:
	CIotPpProcedureRun(){}

public:
	//������ҵ�����б�,ΪCRTDeviceCtrl���������иù��̵ı������ã�����ʱ��RemoveAll
	CExBaseList m_listRcvPkg;
	CExBaseList m_listSendPkg;

	CIotPpProcedureRun(CRTDeviceCtrl *pRTDeviceCtrlRef,CIotPpProcedure *pProcedure
			, CExBaseList *pInterface,CDvmDataset *pDataset,const CString &strRecordMode);
	virtual ~CIotPpProcedureRun(void);

	//����Engine���õ����ӿ�
	BOOL Run();
	void DeletePkgList();//����ɾ����־�������������

	CString GetResultEvent(){return m_strResultEvent;}
	void SetResultEvent(const CString &strEventID){m_strResultEvent = strEventID;}
	CRTDeviceCtrl *GetRTDeviceCtrlRef(){return m_pRTDeviceCtrlRef;}
	CDvmDataset *GetDatasetRef(){return m_pDatasetRef;}
	void ExitProcedureRun(){m_bProcedureExit=TRUE;}
	void DeleteProcedureRun(){m_bIsValid=FALSE;}

private:
	CRTDeviceCtrl *m_pRTDeviceCtrlRef;	//����ʵʱ�豸
	CIotPpProcedure *m_pProcedure;		//��ǰ����
	CDvmDataset *m_pDatasetRef;			//�������ݼ�
	CString m_strRecordMode;			//¼��ģʽ���ݲ�����
	CString m_strResultEvent;			//�����¼�ID

	CIotPpNode *m_pCurrNode;			//��ǰִ��Node
	BOOL m_bProcedureExit;				//���̽������
	BOOL m_bIsValid;					//�����Ƿ���Ч

	//���õ�ǰִ�е�Node
	void SetCurrNode(CIotPpNode *pNode);

	//ִ��Node:�ж��Ƿ��ͱ��ģ����ó�ʱ
	void RunNode();	
	//�жϳ�ʱ�����������б�
	void ProcessNode();
	//���ͱ���
	void RunNodePkg(const CString &strPackageID);
	//������ʱ��
	void BeginTimer(DWORD dwCurrTick);
	//�ж��Ƿ�ʱ������ʱ�����ص���ִ�е�Node�ڵ�
	BOOL IsTimerOut(DWORD dwCurTime,CIotPpNode **ppCurNode);

	//�������߼�
	void ProcessRecvPkgs();
	BOOL ProcessPackageDetail(CXSensorPkg *pPkgDetail);
	BOOL ProcessPackageAck(CIotPpAck *pAck,CXSensorPkg *pPkgDetail);
	BOOL IsMatchJump(CIotPpJump *pJump,CXSensorPkg *pPkgDetail);
	CIotPpNode *GetJumpNode(CIotPpJump *pJump);
};