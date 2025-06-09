#pragma once

#include "..\..\..\Module\BaseClass\ExBaseListListCtrl.h"
#include "..\..\..\Module\DataMngr\DvmDatasetGroup.h"
#include "..\..\..\Module\DataMngr\DvmLogs.h"

//////////////////////////////////////////////////////////////////////////
//CDvmDsRptListCtrl
class CDvmDsRptListCtrl :	public CExBaseListListCtrl
{
public:
	CDvmDsRptListCtrl(void);
	virtual ~CDvmDsRptListCtrl(void);

public:
	void InitListHeader();
	void ShowDvmDataset(CDvmDataset *pDvmDataset);
	
protected:
	void ShowDvmData(long &nRow, CDvmData *pData, long nDataIndex);
	void ShowDvmDatasetGroup(long &nRow, CDvmDatasetGroup *pData, long &nDataIndex);  //shaolei 20211017
	BOOL CanShowDvmValue(CDvmValue *pValue);
	void ShowDvmDataValues(long &nRow, CExBaseList *pValues, long nLevel);
	void GetValueTitle2(CExBaseObject *pParent, CDvmValue *pValue, CString &strValTitle);
	CString GetValueTitle(CDvmData *pData, CDvmValue *pValue);

};

//////////////////////////////////////////////////////////////////////////
//CValuesRptListCtrl
class CValuesRptListCtrl :	public CExBaseListListCtrl
{
public:
	CValuesRptListCtrl(void);
	virtual ~CValuesRptListCtrl(void);

public:
	void InitListHeader();
	void ShowValues(CValues *pValues, BOOL bIsItemMacroTest);
	void UpdateParasName(CTestMacro *pCurrMacro);
	void UpdateParasName(CExBaseList *pDatasRef, CExBaseList *pDatasRef2);

protected:
	CTestMacro *m_pCurrMacro;
	CShortData* FindMacroPara(CValue *pValue);
	CExBaseObject* FindPara(CValue *pValue, CExBaseList *pDatasRef, CExBaseList *pDatasRef2);

};


//////////////////////////////////////////////////////////////////////////
//CValuesRptListCtrl
class CLogsRptListCtrl :	public CExBaseListListCtrl
{
public:
	CLogsRptListCtrl(void);
	virtual ~CLogsRptListCtrl(void);

public:
	void InitListHeader();
	void ShowLogs(CDvmLogs *pLogs);

};

