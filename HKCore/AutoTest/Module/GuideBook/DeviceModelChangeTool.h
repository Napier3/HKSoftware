#pragma once

#include "Device.h"

//数据对象，管理CDataChangeMsgRcvRefObj
class CDvmDataChangeDeviceWndRef  : public CExBaseList
{
public:
	CDvmDataChangeDeviceWndRef();
	virtual ~CDvmDataChangeDeviceWndRef();

public:
	CWnd *m_pDeviceWndRef;
	BOOL m_bDataChanged;
};

class CDvmDataChangeDeviceObj : public CExBaseList
{
public:
	CDvmDataChangeDeviceObj()	
	{
		m_pDevice = NULL;
	}

	virtual ~CDvmDataChangeDeviceObj()	{}

	CDevice *m_pDevice;

public:
	CDvmDataChangeDeviceWndRef *Register(CWnd *pWnd);
	BOOL HasRegister(CWnd *pWndRef);
	void SetDataChanged(BOOL bChanged);
	BOOL HasMsgNeedProcess(CWnd *pWndRef);
	void ProcessMsg(CWnd *pWnd);

	CDvmDataChangeDeviceWndRef* FindDataChangeMsgRcvRefObj(CWnd *pWndRef);

};

class CDvmDataChangeMsgTool : public CExBaseList
{
protected:
	CDvmDataChangeMsgTool();
	virtual ~CDvmDataChangeMsgTool();

public:
	static CDvmDataChangeMsgTool* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CDvmDataChangeMsgTool *g_pGlobal;

public:
	static CDvmDataChangeDeviceObj *Register(CDevice *pDevice);
	static void UnRegister(CDevice *pDevice);
	static void SetDataChanged(CDevice *pDevice, BOOL bChanged);
	
	static CDvmDataChangeDeviceWndRef *Register(CDevice *pDevice, CWnd *pWndRef);
	static void UnRegister(CWnd *pWndRef);
	static BOOL HasMsgNeedProcess(CWnd *pWndRef);
	static void ProcessMsg(CWnd *pWnd);
	static void OnDeleteObj(CExBaseObject *pObj);
	static void OnDeleteObjs(CExBaseList *pList);
	static void OnAddObj(CExBaseObject *pObj);
	static void OnAddObjs(CExBaseList *pList);

protected:
	CDvmDataChangeDeviceObj *In_Register(CDevice *pDevice);
	void In_UnRegister(CDevice *pDevice);
	void In_SetDataChanged(CDevice *pDevice, BOOL bChanged);

	CDvmDataChangeDeviceWndRef* In_Register(CDevice *pDevice, CWnd *pWndRef);
	void In_UnRegister(CWnd *pWndRef);
	BOOL In_HasMsgNeedProcess(CWnd *pWndRef);
	void In_ProcessMsg(CWnd *pWnd);

	static void In_OnDeleteObj(CExBaseObject *pObj);
	static void In_OnDeleteObjs(CExBaseList *pList);
	static void In_OnAddObj(CExBaseObject *pObj);
	static void In_OnAddObjs(CExBaseList *pList);

	CDvmDataChangeDeviceObj *FindDevice(CDevice *pDevice);
	CDvmDataChangeDeviceWndRef* FindDeviceWndRef(CWnd *pWndRef);
};

