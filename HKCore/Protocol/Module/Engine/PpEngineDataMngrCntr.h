#pragma once
#include "../../../module/baseclass/exbaselist.h"
#include "../../../Module/MessageMngr/MsgSendRegister.h"

#include "DeviceModel/DevcieModel.h"
//#include "DeviceModel/DeviceModelDefine.h"
#include "CmmChannel/DeviceCmmChannel.h"
#include "CmmChannel/DeviceCmmChannel.h"
#include "PpTemplate.h"
#include "PpRecordMngr.h"

#include "EngineXvm.h"
#include "../../../Module/System/StringTokenizer.h"

#ifdef _PP_DEV_MODE_
#include "../../../Module/XVM/TSyntax.h"
#endif

#include "../PxiEngine/PxiEngineGlobal.h"

class CPpEngineData : public CExBaseObject
{
private:
	CPpEngineData(){}

public:
	BOOL BuildScript(const char *pszScript, long nBufferLen);
	BOOL BuildScript();
	BOOL BuildScript(CExBaseList *pPpList);
	long CompileScript(CPpScript *pScript, const CString &strVariables=_T(""));
	long RunScript(CPpScript *pScript/*, const CString &strVariables=L"", CBbVariables *pVariables=NULL*/);

	CPpScript* GetPpScript(){return m_pPpScript;}
	BOOL InitTrigerScriptRun(CPpPackageDetail *pPkgDetail);
	BOOL InitTrigerScriptTimerRun();
	BOOL RunTrigerScript_Timer();
	BOOL SerializeTrigerScript(long &nScriptIndex);
	BOOL CanRunWPackageOnReceive();

#ifndef _PP_DEV_MODE_
	CExBaseList* GetListTrigerScriptRun()	{	return &m_listTrigerScriptRun;	}
	CExBaseList* GetListTrigerScriptTimerRun()	{	return &m_listTrigerScriptTimerRun;	}
#endif

protected:
	CPpScript *m_pPpScript;
	char m_pScriptBuffer[65536];
	//char m_pszFuncName[MAX_PATH];

	CEngineXvm *m_pEngineXvm;

#ifndef _PP_DEV_MODE_
	CExBaseList m_listTrigers;
	CExBaseList m_listTrigerScriptRun;
	CExBaseList m_listTrigerScriptTimerRun;
#else
	
#endif
// #ifdef _LUA_IN_DEVBASEAPP_
// 
// #else
// 	void *m_pLua;
// 	CPpScript *m_pPpScript;
// 	char m_pScriptBuffer[65536];
// 
// 	BOOL InitLua();
// 	void CloseLua();
// 	void BindFuncToLua();
// 
// 	//脚本执行
// 	long CompileScript(CPpScript *pScript, const CString &strVariables=L"");
// 
// 	CPpScript* GetPpScript(){return m_pPpScript;}
// 
// 	void GetLuaReturn();
// 	void GetLuaGolbalVariables(CBbVariables *pVariables);
// 	
// public:
// 	long RunScript(CPpScript *pScript, const CString &strVariables=L"", CBbVariables *pVariables=NULL);
// 
// #endif

public:
	CPpEngineData(const CString &strPpTemplateFile, const CString &strPpDeviceFile);
	virtual ~CPpEngineData();
	BOOL IsEngineDataValid();
	BOOL LoadEngineFile(const CString &strPpTemplateFile, const CString &strPpDeviceFile);
	BOOL IsConnectSuccessful();
	BOOL IsConnecting();

	BOOL LoadDeviceFile(const CString &strDeviceFile);
	BOOL GetFileAbsPath(CString &strFile,const CString &strModuleFolder);//zhouhj 2025.2.22 获取文件的绝对路径

    //2020-5-19  lijunqing
    BOOL InitCmmConfig(CDataGroup *pGroup);
public:
    CString m_strDeviceID;  //2020-11-24 lijunqing
	CString m_strPpTemplateFile;
	CString m_strPpDeviceFile;
	CExBaseObject *m_pEngineDeviceBase;  //装置通讯对象

	//模型/模板
	CDevcieModel *m_pDevcieModel;
	CPpDvmDevice *m_pPpDeviceRef;         //设备点表数据管理对象，为m_pDevcieModel成员
	CDeviceCmmConfig *m_pDeviceCmmConfigRef;  //设备通讯配置对象，为m_pDevcieModel成员
	CString m_strNomVarsScript;  //额定值的变量脚本,用于计算点表的数据值

	CPpTemplate *m_pTemplate;  //规约模板对象
	CPpRecordMngr *m_pPpRecordMngr;         //录波规约帧管理对象
	CWinThread *m_pEngineThread;

	CMessageMngr m_oMessageMngr;
	CMsgSendRegister m_oSystemMsgSendRegister;
    CPxiDeviceCommCmdMessage *m_pPxiDeviceCommCmdMessage; //2020-5-22 lijunqing
	CDeviceCmmChannel *m_pDeviceCmmChannelRef;

	CPoDeviceProcedureInterface *m_pPoDeviceProcedureInterface;
	CTreeCtrl *m_pRefTreeCtrl;

	//RCD File Path
	CString m_strRcdFilePath;

public:
	virtual UINT GetClassID() {  return PPCLASSID_PPENGINEDATA;    };
	CMsgSendRegister* Register(ULONG nMsgType, ULONG nHWndOrThreadID, ULONG nMessageID, LPARAM lParam, WPARAM wParam, ULONG nItemData)
	{
		return m_oMessageMngr.Register(nMsgType, nHWndOrThreadID, nMessageID, lParam, wParam, nItemData);
	}
	CMsgSendRegister* Find(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
	{
		return m_oMessageMngr.Find(pMsgRegister, dwMask);
	}
	void UnRegister(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
	{
		m_oMessageMngr.UnRegister(pMsgRegister, dwMask);
	}
	void Register(PMSGSENDREGISTER pMsgRegister, DWORD dwMask)
	{
		m_oMessageMngr.Register(pMsgRegister, dwMask);
	}

	void OnProcedureEnd(const CString &strProcedureID, long wPara=0, long lPara=0);
	void OnDeviceConnectFinish(BOOL bConnectSuccessful);
	void OnDeviceDisConnectFinish(BOOL bConnectSuccessful);

	BOOL IsThreadExit();
	BOOL ExitEngineThread();

	LONG RecordPackage(const CString &strPkgID)
	{
		return m_pPpRecordMngr->RecordPackage(strPkgID);
	}
	LONG UnRecordPackage(const CString &strPkgID)
	{
		return m_pPpRecordMngr->UnRecordPackage(strPkgID);
	}
	LONG RecordProcedure(const CString &strProcedureID)
	{
		return m_pPpRecordMngr->RecordProcedure(strProcedureID);
	}
	LONG UnRecordProcedure(const CString &strProcedureID)
	{
		return m_pPpRecordMngr->UnRecordProcedure(strProcedureID);
	}

	void InitNomVarsScript();
	void RunReset();

private:
	void RunReset(CDvmDevice *pDvmDevice);
	void CreateDeviceListNodes();

	static const CString g_strNomVariableUn;
	static const CString g_strNomVariableIn;
	static const CString g_strNomVarKeyID_UNom;
	static const CString g_strNomVarKeyID_INom;

	void CreateDeviceFileForDebug();
	void ValidateDeviceModel();

private:
	CTickCount32  m_oSendTick;   //发送报文计时
	CTickCount32  m_oRecvTick;   //发送报文计时

public:
	long GetSendTickLong();
	long GetRecvTickLong();
	void ResetSendTick();
	void ResetRecvTick();

public:
	CStringTokenizer m_oStringTokenizer;

	long PPS_InitStrTok(char *pszString, char *pControl);
	long PPS_StrTokCount();
	const char* PPS_StrTokIndex(long nIndex);
	const char* PPS_StrTokNext();

};

class CPpEngineDataMngrCntr :	public CExBaseList
{
public:
	CPpEngineDataMngrCntr(void);
	virtual ~CPpEngineDataMngrCntr(void);

public:
	CPpEngineData* Create(const CString &strPpTemplateFile, const CString &strDeviceFile);
	CPpEngineData* Find(CPpDvmDevice *pDevice);
	CPpEngineData* Find2(CDvmDevice *pDevice);
	CPpEngineData* Find(CPpTemplate *pTemplate);
	CPpEngineData* Find(CDeviceCmmConfig *pCmmConfig);

	//添加节点
	void InsertNodeToTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);

	//批量修改
	void BatchEditData(CDvmDataset *pSrcDataset);
	void BatchEditData(CDvmData *pSrcData, const CString &strDatasetID);
	void ConnectDeviceAll();
	BOOL IsAllDeviceConnectFinished();
	void WaitAllDeviceConnectFinished();
	BOOL IsAllDeviceEngineThreadExit();
	void WaitExitAllEngineThread();
	void ExitAllEngineThread();

protected:
	void BatchEditData(CDvmDataset *pDestDataset, CDvmDataset *pSrcDataset);
	void BatchEditData(CDvmDataset *pDestDataset, CDvmData *pSrcData);
	void BatchEditData(CPpEngineData *pEngineData, CDvmDataset *pSrcDataset);
	void BatchEditData(CPpEngineData *pEngineData, const CString &strDatasetID, CDvmData *pSrcData);

};


void PPS_LogScriptPath(CPpScript *pScript);
