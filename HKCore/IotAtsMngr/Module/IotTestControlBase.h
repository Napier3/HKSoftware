#pragma once


#include "AtsMngrDB/Ats_RTTaskBatch.h"
#include "../../Module/MySqlApp/MySqlBaseApp.h"

enum _tagEngineSystemDefine
{//2020-5-21  lijunqing
	engineConnectDeviceFailed= 1, //0,
	engineConnectDeviceSuccessful=2, //1,
	engineCommError = 3, //2,
	engineCommFinish = 4, //3,
	engineCommCmdError=5, //4
	engineException=6 //5
};

#define MODEL_DEVICE_ID_Attr		_T("device-attr")
#define MODEL_DEVICE_Attr_TimeOut	_T("timeout")
#define ATS_ID_ItemPath				_T("item-path")

typedef struct _ats_msg_info_
{
	long m_nIndex_TestHistroy;
	CString m_strDeviceType;
	CString m_strItemPath;
	CString m_strData;
}AtsMsgInfo;

class CIotTestControlBase : public CExBaseList
{
public:
	CIotTestControlBase();
	virtual ~CIotTestControlBase();

	CMySqlBaseApp m_oMySqlBaseApp;			//主线程数据库客户端

	//外部消息定义
	unsigned long  m_hMsgWnd;
	unsigned long  m_nMsg;
	unsigned long  m_hSysMsgWnd;
	unsigned long  m_nSysMsg;

	//m_strName:分类名称，m_strID:分类ID
	CAts_RTTaskBatch *m_pRTTaskBatchRef;//装置列表，包含数据模型m_pDvmDeviceRef

public:
	CDvmDataset *GetDeviceAttr();
	BOOL GetDeviceAttrValueByID(const CString &strID,CString &strValue);
	BOOL GetDeviceAttrValueByID(const CString &strID,long &nValue);
	CDvmDataset *FindDataset(const CString &strDatasetID);
};

BOOL InitMySqlApp(CMySqlBaseApp &oMySqlBaseApp);
CString GetIDFromPath(const CString &strPath,char chSeperator='$');

void CommVm_PostDeviceSysMessage(CIotTestControlBase *pTestCtrl, WPARAM wParam, LPARAM lParam);
void CommVm_PostDeviceCommCmdMessage(CIotTestControlBase *pTestCtrl, WPARAM wParam, LPARAM lParam);