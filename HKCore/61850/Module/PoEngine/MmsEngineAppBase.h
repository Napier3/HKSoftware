// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// PpMmsEngine.h : PpMmsEngine 应用程序的主头文件
//
#pragma once

#include "../MmsApi.h"
#include "../MmsConfig/MmsKeyConfig.h"
#include "../XLanguageResourcePp_Mms.h"
#include "../../../Module/XLanguage/XLangWndAdjust.h"
#include "MmsRcdFiles/MmsDevices.h"

#define WND_UPDATE_DATA		123456

//////////////////////////////////////////////////////////////////////////
#define SectionDefault		100000000

#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"


class CMmsEngineAppBase : public CMmsApi
{
private:
	static CMmsEngineAppBase *g_pMmsEngine;
	static long g_nMmsEngineRef;

public:
	static CMmsEngineAppBase* Create();
	static void Release();
	static CMmsEngineAppBase* GetMmsEngine();

public:
	CMmsEngineAppBase();
	virtual void ExitMmsApi();

	CMmsKeyConfig m_oMmsKeyConfig;

	ST_RET enter_u_mvl_rpt_CriticSection();
	ST_RET free_u_mvl_rpt_CriticSection();


	void AddErrorString(const CString &strMsg);
	void GetErrorString(CString &strMsg);

	BOOL SaveAllMmsDevicesRcdFiles();
	void GetRcdDirAndFileFromMmsFileSysObj(CRcdDir *pRcdDir,const MMS_ADDR_VECTOR &oMmsAddrVector);
	BOOL ReadAllMmsDevicesRcdFilesFromFile();
	void GetMmsFileSysObjFromDir(XMMS_FILE_SYS_OBJ *pMmsFileSysObj,CRcdDir *pRcdDir);

public:
	/* 2012-11-9  报告结果通知 */
	virtual ST_VOID mmsi_RecvRptData();

	CString GetStringFromValue(CString str, tagValue data);

	void InitMmsGlobalPath();

/*	void Read(ST_INT nDataType, ST_INT nDeviceIndex, ST_INT nLDIndex = 0)
	{
//		m_oFuncParamEx[nDeviceIndex].set_hNotifyWnd(m_pMainWnd->m_hWnd);
		m_oFuncParamEx[nDeviceIndex].set_DevIndex(nDeviceIndex);
		m_oFuncParamEx[nDeviceIndex].set_LDvIndex(nLDIndex);
		m_oFuncParamEx[nDeviceIndex].set_DSID(nDataType);
		m_oFuncParamEx[nDeviceIndex].set_FuncID(FuncID_Read);

		mmsi_FunctionCall(nDeviceIndex,NULL);
	}

	void EnumLD(ST_INT nDeviceIndex)
	{
//		m_oFuncParamEx[nDeviceIndex].set_hNotifyWnd(m_pMainWnd->m_hWnd);
		m_oFuncParamEx[nDeviceIndex].set_DevIndex(nDeviceIndex);
		m_oFuncParamEx[nDeviceIndex].set_FuncID(FuncID_EnumLD);

		mmsi_FunctionCall(nDeviceIndex,NULL);
	}
*/
public:
	void OnImportDevModelFile(const CString &strModelFilePath,long nDevIndex);

	//tagDA数据操作
	CString mms_GetDAName(tagDA *pDA);
	CString mms_GetDADataType(tagDA *pDA);
	CString mms_GetDAPath(tagDA *pDA);
	CString mms_GetDAUnit(tagDA *pDA);

public:
	/* 2012-11-22  基本数据操作过程 */
	virtual long MMS_DataOpeProc(CFuncParamEx *pFuncParaEx);
	BOOL SendMessage_TestFuncFinished(WPARAM wParam,LPARAM lParam);//zhouhj 20210326 发送测试功能结束消息

// 属性
public:
	int  m_nBrcbType;

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};
