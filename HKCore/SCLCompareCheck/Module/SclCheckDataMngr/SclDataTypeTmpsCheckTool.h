#pragma once
#include "SclCheckObjectsSet.h"
#include "SclDataTemplates.h"
#include "DataTypeTemplates.h"
#include "../SclCheck/ResultsRec.h"

class CSclDataTypeTmpsCheckTool
{
public:
	CSclDataTypeTmpsCheckTool(void);
	virtual ~CSclDataTypeTmpsCheckTool(void);

	BOOL OpenConfigs(const CString &strSGCCFilePath,const CString &strTmpsFilePath);
	BOOL StartCheck();
	CWinThread *m_pStartCheckThread;
	BOOL m_BeCheckFinished;
	CString m_strSclFilePath;
	//直接启动检查
	int Start1396CheckNormal(CString &strSclFilePath,CDLT860ModelChecks *pDLT860ModelChecks,CResultsRec *pDL860Results);
	//从线程启动检查
	int Start1396CheckFromThread(CString &strSclFilePath,CDLT860ModelChecks *pDLT860ModelChecks,CResultsRec *pDL860Results);
	void FreeStartCheckThread();
	static UINT StartCheckThread(LPVOID pParam);

protected:
	void StartTemplateCheck1396(CDLT860ModelChecks *pDLT860ModelChecks);
	void StartTemplatesCompare(CDLT860ModelChecks *pDLT860ModelChecks);
	void CheckLNodeTypeOfGDW1396(CLNodeType *pObjDataType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks);
	void CheckDOTypeOfGDW1396(CDOType *pObjDOType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks);
	void CheckDATypeOfGDW1396(CDAType *pObjDAType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks);
	void CheckEnumTypeOfGDW1396(CEnumType *pObjEnumType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks);

	bool DataTypeCompareWithTemplates(CExBaseList *pTmpDataType , CExBaseList *pObjDataType );

	BOOL HasSelectChecks(BOOL bIsTemplateCheck);//参数1标记是否为模板检测,否则为模板比较
	void AddCheckResultDLT860Tmps(CString strErrorType ,CString strText ,CString strErrorPos = "");
	BOOL BeCheckThisObject(CCheckObject *pCheckObject ,CString &strObjectID);
	bool CheckTailDigital(const CString &strText);
	long DelTailDigtal(CString &strName);
	POS checkDO_withRepeat(CLNodeType *pObjDataType , POS pos ,bool bDigtalTail ,CDLT860ModelChecks *pDLT860ModelChecks);

	CDLT860ModelChecks *m_pDLT860ModelChecks;
	CSCLTemplates m_oSCLTestObjectFile;
	CSCLTemplates m_oStdDataTypeTemplates;//标准模板库文件
	CTemplateFile1396 m_oTemplateFile1396;
	CResultsRec *m_pDL860Results;

};
