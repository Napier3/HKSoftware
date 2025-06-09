//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXDevice.h  CSttXDevice

#pragma once

#include "../../../Module/DataMngr/DataGroup.h"

#define WM_IOT_DEVICEMGR_ADD   (WM_USER+743)
#define WM_IOT_DEVICEMGR_DELETE   (WM_USER+744)
#define WM_IOT_DEVICEMGR_UPDATE   (WM_USER+745)

#define STTX_DEVICE_ATTRID_SN  _T("SN")
#define STTX_DEVICE_ATTRID_Model  _T("Model")
#define STTX_DEVICE_ATTRID_Type  _T("Type")
#define STTX_DEVICE_ATTRID_CategoryID  _T("CategoryID")

class CSttXDevice : public CDataGroup
{
public:
	CSttXDevice();
	virtual ~CSttXDevice();

	long m_nSelect;
	CString m_strSN;
	CString m_strModel;
	CString m_strType;
	CString m_strCategoryID;

//重载函数
public:
	virtual BOOL CopyOwn(CBaseObject* pDest);

	
//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	CString GetSN();
	CString GetModel();
	CString GetType();
	CString GetCategoryID();

	void SetSN(const CString &strValue);
	void SetModel(const CString &strValue);
	void SetType(const CString &strValue);
	void SetCategoryID(const CString &strValue);

	void InitDevice();
};

