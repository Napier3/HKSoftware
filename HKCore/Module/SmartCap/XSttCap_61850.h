#pragma once

#include "61850Cap/SttCapThread.h"
#include "61850Cap/ProtocolBase/Protocol61850.h"
#include "61850Cap/Record/CapDeviceChRecordMngr.h"

#ifdef _XSmartCap_use_SmDb_
#include "61850Cap/CapSmDbFile/CapFrameDbFile.h"
#include "../Smdb/SmDbWriteThread.h"
#endif

#include "X61850CapBase.h"

#ifdef _XSmartCap_use_SttRcdSocket_
#include "../../SttStudio/Module/SttSocket/TestTerminal/VC/SttClientSocket.h"
#endif

#include "../../SttStudio/Module/Engine/SttClientTestEngine.h"
#include "../../SttStudio/Module/RecordTest/SttRcdSocketBase.h"
#include "../../SttStudio/Module/SttTestAppConfig/SttTestAppCfg.h"

/*
#define XPARA_ID_IEC_CB _T("IEC_CB")
#define XPARA_ID_Type _T("Type")
#define XPARA_ID_Port _T("Port")
#define XPARA_ID_CRC _T("CRC")
#define XPARA_ID_APPID _T("APPID")
#define XPARA_ID_PkgDetect _T("PkgDetect")
*/
#define PARA_DATA_ID_MESTMAC     XPARA_ID_DestMac
#define PARA_DATA_ID_APPID       XPARA_ID_APPID
#define PARA_DATA_ID_Port        XPARA_ID_Port   //光口号" 
#define PARA_DATA_ID_Type        XPARA_ID_Type   //GOOSE 或者  SV

#define IEDTEST_AUTOTEST_DELAY_TIMER  2035
#define IEDTEST_STORM_SOE_TIMER    2036

class CXSttCap_61850 : public CX61850CapBase, public CSttRcdBufferRcvMsg
{
public:
	virtual void OnRcdBufRcv(BYTE *pBuffer, long nLen) ;
	virtual long OnRcdRcvClosed(); ////2022-6-30  lijunqing 

public:
	CXSttCap_61850(CXCapPkgBufferMngrInterface *pSttXCapBufferMngr);
	virtual ~CXSttCap_61850(void);

	virtual void BeginRecord();

	virtual void ExitInstance();
	virtual void CreateCapTrhead();
	virtual BOOL BeginCap(CIecCfgDatasMngr *pIecfgDataMngr, BOOL bClearDevices=TRUE);
	virtual BOOL StopCap();

	virtual BOOL IsCapExit();
	virtual BOOL CanClose();
	virtual BOOL IsInCapture();

	virtual void FreeCapture();

	CXSmMemBufferMngr* GetCapMemBufferMngr()	{	return m_pSttCapThread->GetCapMemBufferMngr();	}

	BOOL ConnectServer(BOOL bEngineConnect=TRUE);
	BOOL ConnectServerEx();
	void DisConnectServer();
	BOOL CreateSttRcdSocket();
	void AttachSttTestAppCfg(CSttTestAppCfg *p)	{	m_pSttTestAppCfg = p;	}
	CXCapPkgBufferMngrInterface* GetSttXCapBufferMngr()	{	return m_pSttXCapBufferMngr;	}

protected:
	CString m_strIP;
	unsigned short m_nPort;

	CSttFrameMemBufferMngr m_oCapBufferMngr61850;   //抓包报文缓冲区
	
	CXCapPkgBufferMngrInterface *m_pSttXCapBufferMngr; //2022-4-6  lijunqing 修改，使用动态创建的对象
	//CSttRcdMemBufferMngr m_oSttRcdMemBufferMngr;

	CSttCapThread *m_pSttCapThread;
	long   m_nCount;//mym 2020-12-12

	CSttTestAppCfg *m_pSttTestAppCfg;

#ifdef _XSmartCap_use_SttRcdSocket_
    CSttClientSocket m_oSttRcdClientSocket;
	CSttRcdSocketBase m_oSttRcdSocketBase;
#endif

public:
	void ReadHexTestFile();
	CSttTestEngineClientData *m_pSttClientTestEngine;
	void FreeClientTestEngine();

	BOOL m_bTestStarted;	//开始测试标记
	BOOL m_bInStateTest;    //是否状态序列输出，用于使能界面按钮；
	BOOL m_bUseSttTestEngineClientData;//20230704 zhouhj 增加用于区分原有SmartTest应用场景和330,在330下由测试仪对应Socket发送测试控制命令

	CProtocol61850 *GetProtocol16850(){		return m_pProtocol61850;	}
	BOOL IsRecordTestCalThreadCreated();	

public:
	BOOL GetStatesOutputCmd(CDvmDataset *pDsStates, CDataGroup &oDataGroup);
	void GetSttRecordParas(CIecCfgDatasMngr *pDatasMngr, CSttParas *pParas, const CString &strIecfgDataID);
	BOOL StateTest(const CString &strDatasetID);
	BOOL DownIecfgData(const CString &strIecfgDataID, const CString &strSwitchFlag);
	BOOL DownIecfgData_SttRecord(const CString &strIecfgDataID);
	BOOL DownIecfgData_Iec61850Config(const CString &strIecfgDataID, const CString &strSwitchFlag);
	BOOL IsIec61850Config(const CString &strIecfgDataID);
	void ReadSoe();               //读SOE
	void Reset();                 //复归
	void LOG_DEBUG_INFOR();
	BOOL IecDetect(long nMode = 0, const CString &strCRC = _T(""));  //SV探测
	BOOL WriteIecRcdStep(const CString &strDatasetID);  //合并单元精度测试
	BOOL MUTimeTest(const CString &strDatasetID);     //时间特性测试
	BOOL IEDTest(const CString &strDatasetID);//智能终端测试
	BOOL GetOutputCmd_302IecRcdStep(CDvmDataset *pDataset, CDataGroup &oDataGroup);
	BOOL GetOutputCmd_IEDTest(CDvmDataset *pDataset, CDataGroup &oDataGroup);
	BOOL GetOutputCmd_IEDTest_Delay(CDvmDataset *pDataset, CDataGroup &oDataGroup);
	BOOL GetOutputCmd_IEDTest_Delay_AutoTest(CDvmDataset *pDataset, CDataGroup &oDataGroup, const CString &strSwitchIndex, const CString &strSwitchState);
	BOOL GetOutputCmd_IEDTest_Delay_ManuTest(CDvmDataset *pDataset, CDataGroup &oDataGroup, const CString &strSwitchIndex, const CString &strSwitchState);
	BOOL GetOutputCmd_IEDTest_SOE(CDvmDataset *pDataset, CDataGroup &oDataGroup);
	BOOL GetOutputCmd_IEDTest_Storm(CDvmDataset *pDataset, CDataGroup &oDataGroup);
	BOOL GetOutputCmd_IEDTest_BinaryEnable(CDvmDataset *pDataset, CDataGroup &oDataGroup);
	long GetBinaryMapCount_IEDTest(CDvmDataset *pDataset);
	void ResetBinaryMap_Data(CDvmData *pData);
	void SetPT_CT_Rates(CIecCfgPrimRatesIn *pPrimRatesIn,BOOL bIsFT3Device);
//	void UpdatePT_CT_Rates(CIecCfgPrimRatesIn *pPrimRatesIn);//更新变比值,及更新全部9-2通道变比值

protected:
	long GetSttRecordParas_SV(CIecCfgDatasSMV *pSmvMngr, CSttParas *pParas, const CString &strIecfgDataID);
	long GetSttRecordParas_GS(CIecCfgGoutDatas *pGoutMngr, CSttParas *pParas, const CString &strIecfgDataID);

};
