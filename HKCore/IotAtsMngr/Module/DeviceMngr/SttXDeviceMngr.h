//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttXDeviceMngr.h  CSttXDeviceMngr

#pragma once
#define WM_IOT_DEVICEMGR_ADD   (WM_USER+743)
#define WM_IOT_DEVICEMGR_DELETE   (WM_USER+744)
#define WM_IOT_DEVICEMGR_UPDATE   (WM_USER+745)

#include "SttXDevice.h"
class CSttXDeviceMngr : public CDataGroup
{
public:
	CSttXDeviceMngr();
	virtual ~CSttXDeviceMngr();


//���غ���
public:
	//��ѯ�豸�����nUse=-1����ʾ���������������豸

	long QueryDevices(CExBaseList &oList, CDataGroup *pQuery); 
	//ע��ָ��ɹ�ע�ᣬ����WM_IOT_DEVICEMGR_ADD��Ϣ
	long AddDevice(CDataGroup *pParas, BOOL bPostMsg=TRUE);
	
	//ע��ָ��ɹ�ע��������WM_IOT_DEVICEMGR_DELETE��Ϣ
	long DeleteDevice(CDataGroup *pParas);
	
	//����CreateTest��CloseTestָ�����״̬������WM_IOT_DEVICEMGR_UPDATE
	long UpdateDeviceState(CDataGroup *pParas); 
	
	//��Ӷ���豸
	void AddDevices(CDataGroup *pParas, BOOL bPostMsg);

	CSttXDevice* FindDevice(const CString &strAttrID, const CString &strAttrValue);
	long FindDevice(CExBaseList &listDevice, const CString &strAttrID, const CString &strAttrValue);

	long GetAllSelectDevices(CExBaseList &listDevices);
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	CWnd *m_pMsgRcvWnd;
};

