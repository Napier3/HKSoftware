#pragma once

#include "..\..\..\61850\Module\SCL\SclIecCfgDatas.h"
#include "..\..\..\Module\GridBase\ExBaseListGrid.h"

#define IDC_GRID_SCLVISUAL_CTRL   21012
#define IDC_GRID_SCLVISUAL_CHN    21013

class CSclVisualGridBase : public CExBaseListGrid
{
public:
	CSclVisualGridBase();
	virtual ~CSclVisualGridBase();

public:
	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual long GetDatasCount();

protected:
	UINT m_nOldSclIecCfgClassID;

};

class CSclVisualCtrlGrid : public CSclVisualGridBase
{
public:
	CSclVisualCtrlGrid();
	virtual ~CSclVisualCtrlGrid();

public:

	long m_nCtrlType;
	CDvmDataset *m_pFirstDvmDataset;
	CExBaseListGridOptrInterface *m_pDataViewOptrInterface2;

	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void UpdateCheck();
public:
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);
	void AttachDataViewOptrForTwo(CExBaseListGridOptrInterface *pInterface1 ,CExBaseListGridOptrInterface *pInterface2 = NULL)	{AttachDataViewOptrInterface(pInterface1);	m_pDataViewOptrInterface2 = pInterface2;	}

	void ShowData_GooseInput(CSclCtrlGsIn *pGsIn,int nRow);
	void ShowData_GooseOutput(CSclCtrlGsOut *pGsOut,int nRow);
	void ShowData_SMVInput(CSclCtrlSmvIn *pSmvIn,int nRow);
	void ShowData_SMVOutput(CSclCtrlSmvOut *pSmvOut,int nRow);
	void ShowData_RptCtrl(CRptCtrl *pRptCtrl,int nRow , CString strName);
	void ShowData_LogCtrl(CLogCtrl *pLogCtrl,int nRow , CString strName);
	void ShowData_DataSet(CDvmDataset *pDvmDataset,int nRow ,CString strName ,CString strDesc);
};

class CSclVisualCtrlChnGrid : public CSclVisualGridBase
{
public:
	CSclVisualCtrlChnGrid();
	virtual ~CSclVisualCtrlChnGrid();
public:
	long m_nCtrlType;
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
public:
	void ShowData_GooseInputChn(CSclChGsIn *pChn,int nRow);
	void ShowData_GooseOutputChn(CSclChGsOut *pChn,int nRow);
	void ShowData_GooseOutputChnRef(CSclChGsOut *pChn, CSclChGsIn *pSclChGsIn ,int nRow);
	void ShowData_SMVInputChn(CSclChSmvIn *pChn,int nRow);
	void ShowData_SMVOutputChn(CSclChSmvOut *pChn,int nRow);
	void ShowData_SMVOutputChnRef(CSclChSmvOut *pChn,CSclChSmvIn *pSclChSmvIn ,int nRow);
	void ShowData_DataSetChn(CDvmData *pChn,int nRow ,CString strName);
};

