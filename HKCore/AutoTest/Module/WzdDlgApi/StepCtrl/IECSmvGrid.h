#pragma once
#include "61850/IECCfgSmvDataChsGridBase.h"
#include "61850/IECCfgSmv92DataGrid.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../../61850/Module/IecCfgTool/IecCfgFile.h"

class CIECChMap : public CExBaseObject
{
public:
	CIecCfgGinAppChMap* m_pChMap;
	CIecCfgGinCh* m_pCh;
	CSclIed* m_pIedSel;

	CIECChMap()
	{
		m_pCh = NULL;
		m_pChMap = NULL;
		m_pIedSel = NULL;
	}

	virtual ~CIECChMap() {}
};

class CIECChOutMap : public CExBaseObject
{
public:
	CIecCfgGoutCh* m_pCh;

	CIECChOutMap()
	{
		m_pCh = NULL;
	}

	virtual ~CIECChOutMap() {}
};

class CIECSmvChGrid : public CIECCfgSmvDataChsGridBase
{
public:
	enum tagType
	{
		MODE_SMV,
		MODE_GOOSE_IN,
		MODE_GOOSE_OUT
	};

	tagType m_tagType;
	long m_nErrImgIndex;
	long m_nCorrImgIndex;

	BOOL m_bInitDataTypes;

	//GOOSE
	//CIecCfgGinChs* m_pIecCfgGinChs;		//20230630 huangliang 重写数据类型加载，此处不再使用
	CDataType m_oDataType;
	CExBaseList m_oGsInChsList;

	CDataType m_oGsOutDataType;
	CExBaseList m_oGsOutChsList;

private:
	void ShowData_SMVCh(CExBaseObject *pData, int& nRow);
	void ShowData_GOOSE(CExBaseObject *pData, int& nRow);
	void ShowData_GOOSE_Out(CExBaseObject *pData, int& nRow);

	//void GetGsInChs(CDataType* pDataType);		//20230630 huangliang 重写数据类型加载，此处不再使用
	BOOL ValidateIecCfgDatFiberIndex(CIecCfgGinData *pIecCfgData);
	static void EndEditCell_Fiber (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_GsInChs (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_GsOutChs (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	void Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc = NULL);
	void Show_GsInChs(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc = NULL);
	void Show_GsOutChs(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc = NULL);

public:
	CIECSmvChGrid();
	virtual ~CIECSmvChGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

	void SetGridType(tagType type);
	void ClearDataTypes();
	void ClearOutDataTypes();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow =TRUE);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars =TRUE);
	virtual long GetAppChColIndex() { return 5; }

	//20230630 huangliang 添加数据类型
	void AddDataType(CIecCfgChsBase* pIecCfgGinChs);
	void AddDataTypeForGsOut(CIecCfgChsBase* pIecCfgGoutChs);
};

class CIECSmvGrid : public CIECCfgSmv92DataGrid
{
public:
	CIECSmvGrid();
	virtual ~CIECSmvGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow =TRUE);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars =TRUE);
	void SetGridCh_Smv_Gs(int nRow);
	//void CollectAllSmvCh(CIecCfgFileDevice* pIecCfgFileDevice);
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);
};