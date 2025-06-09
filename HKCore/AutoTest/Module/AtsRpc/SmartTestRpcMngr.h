#ifndef _AtsRpcXmlRpcServer_h__
#define _AtsRpcXmlRpcServer_h__

#include "..\..\..\Module\DataMngr\DvmDataset.h"
#include "..\..\..\Module\FTP\XMiniFtpClient.h"
#include "..\..\..\Module\CriticalSection\SynCriticalSection.h"

#include "SmartTestRpcServer.h"
#include "AtsRpcServerConfig.h"
#include "AtsRpcServerGlobalApi.h"

#include "../TestControl\TestControl.h"
#ifdef GUIDEBOOK_DEV_MODE
#include "..\GbWzdAuto\GbWzdAutoConfig.h"
#endif

class CSmartTestRpcMngr : public CExBaseList
{
private:
	CSmartTestRpcMngr();
	virtual ~CSmartTestRpcMngr();

	static long g_nSmartTestRpcMngrRef;
	static CSmartTestRpcMngr *g_pSmartTestRpcMngr;

public:
	static void Create(const CString &strServerIP, long nServerLocalPort, const CString &strTestID);
	static void Release();

public:
	void InitSmartTestRpcMngr();
	void ExitSmartTestRpcMngr();

	//CAtsRpcTestDefine* GetAtsRpcTestDefine()		{	return &m_oAtsRpcTestDef;	}
	void SetMainTestControl(CTestControlBase *pMainTestControl)	{	m_pMainTestControl = pMainTestControl;	}

//MMSEngine XMLRPC Server
protected:
	CSmartTestRpcXmlRpcServer *m_pAtsRpcServer;
	CWinThread *m_pAtsRpcServerThread;
	//CAtsRpcTestDefine m_oAtsRpcTestDef;
	CTestControlBase *m_pMainTestControl;

	CString m_strServerIP;
	long m_nServerLocalPort;
	CString m_strTestID;
	CString m_strGbrptFile;

	void CreateAtsRpcServer();
	static UINT AtsRpcServer(LPVOID pPara);
	void ExitAtsRpcServer();

//////////////////////////////////////////////////////////////////////////
//外部远程调用的处理
public:
	BOOL IsSmartTestExist(const CString &strTestID);
	BOOL ExitSmartTest();
	void InitSmartTestClient(const CString &strServerIP, long nPort);
	void CreateTest(const CString &strTestID, BYTE *pBuffer, long nLen);
	void BeginTest();
	void StopTest();
	void TestAllInlegibleItems();
	void TestPoint(const CString &strTestID, long nIndex);
	void TestBelow(const CString &strTestID, long nIndex);
	void OpenGbrptFile(CString &strGbrptFile, long nDeviceIndex);
	void CloseTest();
	void ExportRpt();
	void ViewItemRpt(long nDeviceIndex, long nItemIndex);
	void GetAllTestItems(CDvmDataset &oDvmDataset);
	void GetTestItemReport(const CString &strItemPath, CBinarySerialBuffer &oBuffer);
	void GbDevWzdAuto(const CString &strTestID, char *pBuffer, long nLen);
	
#ifdef GUIDEBOOK_DEV_MODE
protected:
	CGbWzdAutoConfig m_oGbWzdAutoConfig;

public:
	CGbWzdAutoConfig* GetGbWzdAutoConfig()	{	return &m_oGbWzdAutoConfig;	}
#endif

//MstmSlnTest XMLRPC Client
private:
	void InitXmlRpcClient(const CString &strServerIP, long nPort);
	void ExitXmlRpcClient();
	XmlRpc::XmlRpcClient *m_pXmlRpcClient;

public:
	void OnSmartTestCreated(CDvmDataset *pDvmTasks);
	void OnTestItemStateChanged(CGbItemBase *pTestItem);
	void OnTestFinished(CTestControlBase *pTestControl, long nType);
	void OnTestError(CTestControlBase *pTestControl);
	void OnTestStoped(CTestControlBase *pTestControl, const CString &strMsg);
	void OnExportRptFinished();
	void OnConnectDeviceFailed();
	void OnGbrptOpened();
	void OnOpenGbrptFailed();


//FTP Client  
public:

protected:
	CXMiniFtpClient m_oXMiniFtpClient;
	CString m_strRcdFileRootPath;

	BOOL InitXMiniFtp();
	void ExitXMiniFtp();
};

extern CSmartTestRpcMngr *g_theSmartTestRpcMngr;

BOOL atsrpc_OpenCmdFile_RPC(const CString &strCmdFile, CWnd *pMainWnd);



#endif // _AtsRpcXmlRpcServer_h__

