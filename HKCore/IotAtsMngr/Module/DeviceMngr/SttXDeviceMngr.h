//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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


//重载函数
public:
	//查询设备，如果nUse=-1，表示所有满足条件的设备

	long QueryDevices(CExBaseList &oList, CDataGroup *pQuery); 
	//注册指令成功注册，发送WM_IOT_DEVICEMGR_ADD消息
	long AddDevice(CDataGroup *pParas, BOOL bPostMsg=TRUE);
	
	//注销指令，成功注销，发送WM_IOT_DEVICEMGR_DELETE消息
	long DeleteDevice(CDataGroup *pParas);
	
	//处理CreateTest、CloseTest指令，更新状态，发送WM_IOT_DEVICEMGR_UPDATE
	long UpdateDeviceState(CDataGroup *pParas); 
	
	//添加多个设备
	void AddDevices(CDataGroup *pParas, BOOL bPostMsg);

	CSttXDevice* FindDevice(const CString &strAttrID, const CString &strAttrValue);
	long FindDevice(CExBaseList &listDevice, const CString &strAttrID, const CString &strAttrValue);

	long GetAllSelectDevices(CExBaseList &listDevices);
//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	CWnd *m_pMsgRcvWnd;
};

