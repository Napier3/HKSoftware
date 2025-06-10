#pragma once

#include "SttBaseInterface.h"
#include "../../../Module/TestMacro/TestMacro.h"
#include "../../../Module/DataMngr/DvmDataset.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "../SttPkgDispatchInterface.h"

static const CString g_strSttTestClientEngine = _T("SttTestEngine");

enum MtSpyWndShow
{
	TmtSpyShow_Hide = 0,
	TmtSpyShow_Show = 1,
	TmtSpyShow_MinSize = 2,
	TmtSpyShow_MaxSize = 3,
	TmtSpyShow_Close = 4,
	TmtSpyShow_ShowCenter = 5
};

enum MtMessageID
{
	MTMSG_ConnectSuccess=0,
	MTMSG_ConnectFaild=1,
	MTMSG_ConnectConfig=2,
	MTMSG_TestBegin=3,
	MTMSG_TestFinished=4, 
	MTMSG_SearchPointFinished=5, 
	MTMSG_CommError=6,
	MTMSG_Not_Surport=7,
	MTMSG_ManualTestBegin=8,
	MTMSG_ManualTestReturn=9,
	MTMSG_ManualTestStop=10,
	MTMSG_ShowCurItem=11,
	MTMSG_TestOverTime=12,
	MTMSG_AppWarning=13,
	MTMSG_AppError=14,
	MTMSG_TestManualStop=15,   //shaolei  20210526  人工停止消息，例如：急停
	MTMSG_SearchPointReport=16 //shaolei  20220728 特性曲线搜索中间过程消息
};

class CMacroTestInterface : public CSttBaseInterface
{
public:
	CMacroTestInterface()
	{	
		m_pTestMacro = NULL;	
		m_bIsNewCreate = TRUE;
		m_pSttTestApp = NULL;
		m_bTestStarted = FALSE;
	};

	virtual ~CMacroTestInterface(void){};
	CTestMacro *m_pTestMacro;
	CString m_strItemPath;
	CDataGroup m_oFaultParas_Dvm;  //故障参数+扩展故障参数+系统参数
	CDataGroup m_oResults_Dvm;   //结果参数+扩展结果参数
	CSttTestAppCfg *m_pSttTestApp;
	CString m_strTestAppSN;  //测试仪设备SN

public:
	virtual long SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID) = 0;
	virtual CString GetConfig() = 0;
	virtual long SetConfig(const CString & bstrConfig) = 0;
	virtual long Test(const CString & strMacroID, const CString & strParameter) = 0;
	virtual CString GetReport() = 0;
	virtual long StopTest() = 0;
	virtual long CloseDevice() = 0;
	virtual CString GetSearchReport() = 0;
	virtual long FinishTest(long nState) = 0;
	virtual long ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter) = 0;
	virtual unsigned long GetExternMsgRcvWnd() = 0;
	virtual unsigned long GetExternMsgID() = 0;
	virtual unsigned long StopDevice(void) = 0;
    virtual long UpdateParameter(const CString &strMacroID, CDataGroup *pParas)    {    return -1;  }
    virtual long ManualTrigger()    {    return -1;  }

	//add by shaolei
	virtual void SetTestMacro(CTestMacro *pTestMacro){	m_pTestMacro = pTestMacro;	}
	//add by shaolei 2024-3-25
	virtual void SetItemPath(const CString &strItemPath)	{	m_strItemPath = strItemPath;	}

    //2022-2-12  lijunqing  为通信通道制定转发报文的对象指针
    virtual void AddPkgDispatchInterface(CSttPkgDispatchInterface *p){};

	//2023-6-1  lijunqing 
	virtual long Test(const CString & strMacroID, CDataGroup *pParas)	{	return 0;	}
	
	//2023-6-20  lijunqing
	virtual CDataGroup* GetResults()	{	return NULL;	}

public:
	BOOL IsNewCreate()			{	return m_bIsNewCreate;		}
	void ClearNewCreateFlag()	{	m_bIsNewCreate = FALSE;		}

	BOOL m_bTestStarted;

protected:
	BOOL m_bIsNewCreate;
};

class CMacroTestEngineInterface : public CSttBaseInterface
{
public:
	CMacroTestEngineInterface(){};
	virtual ~CMacroTestEngineInterface(void){};

	virtual CMacroTestInterface* CreateMacroTest(const CString &bstrConfig) = 0;
	virtual long ExitEngine() = 0;
	virtual long ExcuteCmd(const CString &strCmdID, const CString &strCmdParameter) = 0;
	virtual long ShowSpyWnd(long nShow) = 0;
	virtual long ConfigEngine() = 0;
	virtual long AttatchLogWnd(unsigned long hWnd) = 0;
};

class CMacroTestCreatorInterface : public CSttBaseInterface
{
public:
	CMacroTestCreatorInterface()
	{
		m_hLogWnd = 0;
	};

	virtual ~CMacroTestCreatorInterface(void){};

	unsigned long m_hLogWnd;
public:
	virtual CMacroTestEngineInterface* CreateMacroTestEngine(const CString &strMacroFile) = 0;
	virtual CMacroTestEngineInterface* GetMacroTestEngine(const CString &strType, const CString &strProgID, const CString &strMacroFile) = 0;
	virtual CMacroTestInterface* GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps) = 0;
	virtual void ReleaseMacroTestEngine() = 0;
	virtual void ReleaseMacroTestEngine(const CString &strProgID) = 0;
	virtual void ShowSpyWnd() = 0;
	virtual void ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara) = 0;
	virtual long ConfigEngine(const CString &strMacroFile, const CString &strIP) = 0;
	virtual long AttatchLogWnd(unsigned long hWnd) = 0;
};

//2021-1-8
inline void mt_GetIP_ConfigString(CDvmDataset *pDataset, const CString &strIP)
{
	pDataset->m_strID = _T("cmm-config");
	pDataset->m_strName = pDataset->m_strID;
	CDvmData *pData = pDataset->AddNewData();
	pData->m_strID = _T("ip-addr");
	pData->m_strName = pData->m_strID;
	pData->m_strValue = strIP;
}

//2021-1-8
inline void mt_GetIP_ConfigString(const CString &strIP, CString &strXml)
{
	CDvmDataset oDataset;
	mt_GetIP_ConfigString(&oDataset, strIP);
	oDataset.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXml);
}
