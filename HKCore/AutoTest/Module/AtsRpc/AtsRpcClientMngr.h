#ifndef _AtsRpcXmlRpcServer_h__
#define _AtsRpcXmlRpcServer_h__

#include "..\..\..\Module\DataMngr\DvmDataset.h"
#include "..\..\..\Module\FTP\XMiniFtpClient.h"
#include "..\..\..\Module\CriticalSection\SynCriticalSection.h"
#include "..\..\..\AutoTest\Module\GbWzdAuto\GbWzdAutoConfig.h"

#include "AtsRpcClientSvr.h"
#include "AtsRpcServerConfig.h"
#include "AtsRpcServerGlobalApi.h"

#define WM_AtsRpcClient_CREATETEST  (WM_USER+1444)
#define WM_AtsRpcClient_TEST              (WM_USER+1445)

class CAtsRpcClient;

class CAtsRpcClientInterface
{
public:
	virtual void OnItemStateChanged(const CString &strTestID, int nDeviceIndex, int nItemIndex, const CString &strID, const CString &strState) = 0;
	virtual void OnTestFinished(const CString &strTestID, long nDeviceIndex, long nType) = 0;
	virtual void OnTestStoped(const CString &strTestID, long nDeviceIndex, const CString &strMsg) = 0;
	virtual void OnTestAppError() = 0;
	virtual void OnEngineError() = 0;
	virtual void SmartTestCreated(const CString &strTestID, char *pBuffer, long nLen, char *pBufferRpts, long nLenRpts) = 0;
	virtual void OnExportRptFinished(const CString &strTestID) = 0;
	virtual void OnConnectDeviceFailed(const CString &strTestID) = 0;
	virtual void OnGbrptOpenFailed(const CString &strTestID) = 0;
};

class CAtsRpcClientMngr : public CExBaseList
{
public:
	CAtsRpcClientMngr();
	virtual ~CAtsRpcClientMngr();

	void InitAtsRpcClientMngr();
	void ExitAtsRpcClientMngr();

	CAtsRpcTestDefine* GetAtsRpcTestDefine()		{	return &m_oAtsRpcTestDef;	}
	void AttachAtsRpcClientInterface(CAtsRpcClientInterface *pInterface)		{	m_pAtsRpcClientInterface = pInterface;	}

	virtual void OnItemStateChanged(const CString &strTestID, int nDeviceIndex, int nItemIndex, const CString &strID, const CString &strState)	{	m_pAtsRpcClientInterface->OnItemStateChanged(strTestID, nDeviceIndex, nItemIndex, strID, strState);	}
	virtual void OnTestFinished(const CString &strTestID, long nDeviceIndex, long nType)	{	m_pAtsRpcClientInterface->OnTestFinished(strTestID, nDeviceIndex, nType);	}
	virtual void OnTestStoped(const CString &strTestID, long nDeviceIndex, const CString &strMsg)  {		m_pAtsRpcClientInterface->OnTestStoped(strTestID, nDeviceIndex, strMsg);		}
	virtual void OnTestAppError()	{	m_pAtsRpcClientInterface->OnTestAppError();	}
	virtual void OnEngineError()	{	m_pAtsRpcClientInterface->OnEngineError();	}
	virtual void SmartTestCreated(const CString &strTestID, char *pBuffer, long nLen, char *pBufferRpts, long nLenRpts)	{	m_pAtsRpcClientInterface->SmartTestCreated(strTestID, pBuffer, nLen, pBufferRpts, nLenRpts);	}
	virtual void OnExportRptFinished(const CString &strTestID)	{	m_pAtsRpcClientInterface->OnExportRptFinished(strTestID);	}
	virtual void OnConnectDeviceFailed(const CString &strTestID)	{	m_pAtsRpcClientInterface->OnConnectDeviceFailed(strTestID);	}
	virtual void OnGbrptOpenFailed(const CString &strTestID)   {	m_pAtsRpcClientInterface->OnGbrptOpenFailed(strTestID);  }

//MMSEngine XMLRPC Server
protected:
	CAtsRpcClientXmlRpcServer *m_pAtsRpcServer;
	CWinThread *m_pAtsRpcServerThread;
	CAtsRpcTestDefine m_oAtsRpcTestDef;
	CAtsRpcClientInterface *m_pAtsRpcClientInterface;

	void CreateAtsRpcServer();
	static UINT AtsRpcServer(LPVOID pPara);
	void ExitAtsRpcServer();

public:
	CAtsRpcClient* AddNewAtsRpcClient(const CString &strIP, short nPort);
};


class CAtsRpcClient : public CExBaseList
{
public:
	CAtsRpcClient();
	virtual ~CAtsRpcClient();

	CAtsRpcTestDefine* GetAtsRpcTestDefine()		{	return m_pAtsRpcTestDef;	}

protected:
	CAtsRpcTestDefine *m_pAtsRpcTestDef;
	CString m_strServerIP;

//////////////////////////////////////////////////////////////////////////
//外部远程调用的处理
public:
	void InitSmartTestClient();
	BOOL IsSmartTestExist(const CString &strTestID);
	BOOL ExitSmartTest();
	void CreateTest(const CString &strTestID, CAtsRpcTestDefine *pAtsRpcTestDefine);
	void BeginTest(const CString &strTestID);
	void StopTest(const CString &strTestID);
	void TestAllInlegibleItems(const CString &strTestID);
	void TestPoint(const CString &strTestID, long nIndex);
	void TestBelow(const CString &strTestID, long nIndex);
	void OpenGbrptFile(const CString &strGbrptFilePath, long nDeviceIndex);    //打开测试记录，nDeviceIndex为装置编号 -1=测两台
	void CloseTest(const CString &strTestID);
	void ExportRpt(const CString &strTestID);
	void ViewItemRpt(long nDeviceIndex, long nItemIndex);
	//void GetAllTestItems(CDvmDataset *pDvmDataset);
	void GetTestItemReport(const CString &strItemPath, CBinarySerialBuffer &oBuffer);

	void GbDevWzdAuto(CGbWzdAutoConfig *pGbWzdAutoConfig);

	void InitXmlRpcClient(const CString &strIP, short nPort);
//MstmSlnTest XMLRPC Client
private:
	void ExitXmlRpcClient();
	XmlRpc::XmlRpcClient *m_pXmlRpcClient;
};

extern CAtsRpcClientMngr *g_theAtsRpcClientMngr;

#endif // _AtsRpcXmlRpcServer_h__

