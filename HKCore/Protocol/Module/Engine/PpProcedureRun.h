#pragma once
#include "PpProcedure.h"
#include "PpDataInterface.h"
#include "PpPackageSendMngr.h"
#include "ProtoPkgProcessInterface.h"


class CPpProcedureRun :	public CExBaseObject
{
private:
	CPpProcedureRun(){}

public:
	CPpProcedureRun(CPpProcedure *pProcedure, CExBaseList *pInterface, CWinThread *pEngineThread, BOOL bIsInitProcedure, CProtoPkgProcessInterface *pProtoPkgPrcss);
	virtual ~CPpProcedureRun(void);

	CPpProcedure *m_pProcedure;
	CExBaseList *m_pInterface;
	CProtoPkgProcessInterface *m_pProtoPkgPrcss;  //2023-01-27  lijunqing

private:
	CPpNode *m_pCurrNode;

	CPpPackageSendMngr *m_pPkgSendMngr;  //报文帧发送管理对象
	CExBaseList *m_pListReceivePackage;             //解析出来的帧对象
	CWinThread *m_pEngineThread;
	DWORD m_dwBeginTickCount;

	CString m_strSndOptr_GlobalVar;
	long m_nSndOptr_Optr;
	long m_nSndOptr_Value;
	BOOL m_bIsInitProcedure;

	BOOL CanRunWPackage();

public:
	void InitRunWPackageScpt();
	void ResetPriorityCounter()		{	m_nPriorityCounter = 0;	}
	void IncreasePriorityCounter()	{	m_nPriorityCounter++;	}
	BOOL CanRun()			{	return (m_nPriorityCounter >= m_pProcedure->m_nPriority);	}
	BOOL Run();
	BOOL IsProcedureExit()			{	return m_bProcedureExit;	};
	void    ExitProcedure()			{	m_bProcedureExit = TRUE;	}; 
	CPpNode* GetCurrNode()		{		return m_pCurrNode;		}
	void CopyDataInterfaceToPackage();
	BOOL IsExclusive()	{	return (m_pProcedure->m_nExclusive > 0);	}
	BOOL IsInitProcedure()	{	return m_bIsInitProcedure;	}

private:
	long m_nPriorityCounter;     //过程优先级计数器
	BOOL m_bProcedureExit;

	void RunNode();
	void RunNodePkg(const CString &strPackageID, BOOL bRunInitScript, BOOL bRunEndScript);
	void ProcessNode();
	CPpNode* ProcessNodeProcess();
	CPpNode* ProcessNodeJumps();
	CPpNode* ProcessNodeTimers();

	void RunWPackage(CPpPackage *pPackage, BOOL bRunInitScript, BOOL bRunEndScript);

	void SetCurrNode(CPpNode *pNode);
//	void DeleteUsedPackages();
	void OnProcedureExit();
	void OnProcedureStart();

};

BOOL Pp_CanRunWPackage(CExBaseObject *pPpObj);

