#pragma once
#include "SclCheckObjectsSet.h"
#include "DataTypeTemplates.h"
#include "../SclCheck/ResultsRec.h"
#include "../../../Module/KeyDb/XKeyDB.h"
#include "../../../Module/KeyDb/XMatchVirTerminal.h"
#include "../../../61850/Module/SCL/SclIecCfgDatas.h"

class CSclVirLoopCheckTool
{
public:
	CSclVirLoopCheckTool(void);
	virtual ~CSclVirLoopCheckTool(void);
	BOOL InitVirTermConfigs(const CString &strSMVVirTermCfg,const CString &strGooseVirTermCfg,const CString &strSGCCFilePath);
	BOOL StartCheck();
	//直接启动检查
	int StartVirCheckNormal(CSclStation *pStdSclStation,CVirLoopChecks *pVirLoopChecks,CResultsRec *pVirLoopResults);
	//从线程启动检查
	int StartVirCheckFromThread(CSclStation *pStdSclStation,CVirLoopChecks *pVirLoopChecks,CResultsRec *pVirLoopResults);
	CWinThread *m_pStartCheckThread;
	BOOL m_BeCheckFinished;
	void FreeStartVirCheckThread();
	static UINT StartVirCheckThread(LPVOID pParam);

protected:
	BOOL BeCheckThisObject(CCheckObject *pCheckObject ,CString &strObjectID);
	BOOL VirLoopCheckIsEmpty(CVirLoopChecks *pVirLoopChecks);
	void CheckSmvOutVirLoop(CSclCtrlSmvOut *pSclCtrlSmvOut ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);
	void CheckSmvInVirLoop(CSclCtrlSmvIn *pSclCtrlSmvIn ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);
	void CheckGsOutVirLoop(CSclCtrlGsOut *pSclCtrlGsOut ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);
	void CheckGsInVirLoop(CSclCtrlGsIn *pSclCtrlGsIn ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);
	void CheckRptCtrlBrcb(CExBaseList *pSclLogicDev ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);
	void CheckLogCtrlLcb(CExBaseList *pSclLogicDev ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);
	void AddCheckResultVirLoop(CString strErrorType ,CString strText  ,CString strErrorPos = "");
	bool CheckMACAddrValidity(CString strMAC ,bool bSMVType);
	void AddStringAvoidRepeat(CString &strDesc ,CString strChild);
	bool IsHex(unsigned char ch);
	long DelTailDigtal(CString *strName);
	bool CheckTailDigital(const CString &strText);
	void FormatString(CString &strText, const char *strFormat, ...);

	CXKeyDB m_oSMVKeyDB;
	CXKeyDB m_oGSKeyDB;
	CSclStation *m_pStdSclStation;
	CResultsRec *m_pVirtualLoopResults;
	CVirLoopChecks *m_pVirLoopChecks;

	std::map<long ,CString > m_mapAppID;
	std::map<CString ,CString > m_mapSMVID;
	std::map<CString ,CString > m_mapGOOSEID;
	CXMatchVirTerminal m_oXMatchVirTerminal;

	CTemplateFile1396 m_oTemplateFile1396;
};
