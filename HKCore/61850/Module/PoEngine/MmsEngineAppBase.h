// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// PpMmsEngine.h : PpMmsEngine Ӧ�ó������ͷ�ļ�
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
	/* 2012-11-9  ������֪ͨ */
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

	//tagDA���ݲ���
	CString mms_GetDAName(tagDA *pDA);
	CString mms_GetDADataType(tagDA *pDA);
	CString mms_GetDAPath(tagDA *pDA);
	CString mms_GetDAUnit(tagDA *pDA);

public:
	/* 2012-11-22  �������ݲ������� */
	virtual long MMS_DataOpeProc(CFuncParamEx *pFuncParaEx);
	BOOL SendMessage_TestFuncFinished(WPARAM wParam,LPARAM lParam);//zhouhj 20210326 ���Ͳ��Թ��ܽ�����Ϣ

// ����
public:
	int  m_nBrcbType;

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};
