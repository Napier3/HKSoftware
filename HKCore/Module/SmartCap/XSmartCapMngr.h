#pragma once

#include "XSttCap_61850.h"

#ifndef _PSX_IDE_QT_
#include "XEthernetCap_61850.h"
#endif

#define WM_VARIABLE_ADD_REMOVE  (WM_USER + 1727)

class CXSmartCapMngr : public CExBaseList
{
private:
	CXSmartCapMngr(void);
	virtual ~CXSmartCapMngr(void);

	static long g_nXSmartCapMngrRef;
	static CXSmartCapMngr* g_pXSmartCapMngr;

#ifndef _PSX_IDE_QT_
	CXEthernetCap_61850 *g_pXEthernetCap_61850;
#endif
	CXSttCap_61850 *g_pSttCap61850;

public:
	static void Create();
	static void Release();
	static CXSttCap_61850* GetSttCap61850_Global();

public:
#ifndef _PSX_IDE_QT_
	CXEthernetCap_61850* CreateEthernetCap_61850(int nNetCardIndex);
#endif
	CXSttCap_61850* GetSttCap_61850()	{	return g_pSttCap61850;	}
	//2022-4-7 lijunqing 创建纯粹的61850分析功能，不需要做报问提取，330报文监视模式
	CXSttCap_61850* CreateSttCap_61850(CSttTestAppCfg *pSttTestAppCfg, CXCapPkgBufferMngrInterface *pSttXCapBufferMngr);

	BOOL IsCapExit();
	BOOL CanClose();
	BOOL IsInCapture();
	BOOL BeginCap(CIecCfgDatasMngr *pIecfgDataMngr, BOOL bClearDevices=TRUE);
	BOOL StopCap();

	void BeginRecord();
	void StopRecord();

	void RecordDevice(CCapDeviceBase *pDevice);
	void InitDvmDevice(CCapDeviceBase *pCapDevice); //根据pCapDevice，初始化设备数据模型
	void InitDvmDevices();
	void IecAnalysis_AddDatasets();	//创建IEC分析相关的数据集  2022-5-8- lijunqing

	CXSmMemBufferMngr* GetCapMemBufferMngr();
	void OnCloseMainFrame();
	CCapDeviceChRecordMngr* GetCapDeviceChRecordMngr();
	void AdjustRecordChRange();
	void ExitInstance();
	void ChangeChRecordState(CCapDeviceChBase *pCh, long nState);
	void ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer);

	void GetCapMemBufMngrIndex(CString &strCurrIndex, CString &strParseIndex, CString &strWriteIndex);
	void SetIecCfgDevice(CIecCfgDevice* pCfgDevice);	//yyj
	CRecordTest* GetRecordTest();

	void GetSttCapParas(CDataGroup *pSttParas, BOOL bUseSmv, BOOL bUseGoose, BOOL bUseFT3);

	//2022-5-2  lijunqing 
	void InitSmartCapCtrl();

public:
	CX61850CapBase *m_pX61850Cap;

};

extern CXSmartCapMngr *g_theXSmartCapMngr;
extern CAutoCriticSection g_oCapDeviceChRecordCriticSection;
