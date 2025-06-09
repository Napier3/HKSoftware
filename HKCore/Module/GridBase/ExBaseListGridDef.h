#pragma once

#include "../gridctrl/gridctrl.h"
#include "../BaseClass/ExBaseList.h"
#include "../DataMngr/DataTypes.h"
#include "../BaseClass/ExBaseOptrInterface.h"

class CExBaseListGridOptrInterface
{
public:
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol) = 0;
	virtual BOOL OnEditCellLBDblClk(CXGridCtrlBase *pGridCtrl, int nRow, int nCol, UINT nChar)	{	return FALSE;	}
	virtual void OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)				{	}

};

//定义关联的数据类型nVt
#define VCD_LONG				0
#define VCD_DOUBLE			1
#define VCD_STRING			2
#define VCD_DWORD			3
#define VCD_FLOAT				4
#define VCD_STRCMPBLKS	5
#define VCD_WSTRING			6
#define VCD_SYSTEMTIME	7

#define VCD_TIME_FORMAT_SHORT           1
#define VCD_TIME_FORMAT_SHORT_CHN    2
#define VCD_TIME_FORMAT_LONG             3
#define VCD_TIME_FORMAT_LONG_CHN      4

#define EXBASEGRID_ROWHEIGHT 20

#define CMB_EXBASELIST_ADD_EMPTY    0X80F080F0

inline void exgrid_cmb_set_add_empty(CExBaseList *pExBaseList)
{
#ifndef exbase_not_use_m_dwReserved
	pExBaseList->m_dwReserved = CMB_EXBASELIST_ADD_EMPTY;
#else
	pExBaseList->m_dwItemData = CMB_EXBASELIST_ADD_EMPTY;
#endif
}

inline BOOL is_exgrid_cmb_set_add_empty(CExBaseList *pExBaseList)
{
#ifndef exbase_not_use_m_dwReserved
	return (pExBaseList->m_dwReserved == CMB_EXBASELIST_ADD_EMPTY);
#else
	return (pExBaseList->m_dwItemData == CMB_EXBASELIST_ADD_EMPTY);
#endif
}

inline UINT exgrid_get_vcd_type(LONG nVt)
{
	return LOWORD(nVt);
}

inline UINT exgrid_get_vcd_format(LONG nVt)
{
	return HIWORD(nVt);
}

inline void exgrid_set_vcd_vt(LONG &nVt, LONG nType, LONG nFormat=0)
{
	nVt = MAKELONG(nType, nFormat);
}

typedef struct _ExBaseCellData
{
	LONG nVt;//关联的数据类型

	union
	{
		DWORD *pdwValue;
		long *pnValue;
		double *pdValue;
		float *pfValue;
		CString *pString;
		wchar_t *pWString;
		CStringCmpBlocks *pStrCmpBlks;
		SYSTEMTIME *ptmTime;
	};

	CExBaseObject *pObj;
	CExBaseList *pExBaseList;
	GRID_CELL_EDIT_FUNC *pFunc;

	static _ExBaseCellData* CreateNew(long *pnValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		exgrid_set_vcd_vt(pNew->nVt, VCD_LONG);
		pNew->pnValue = pnValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(DWORD *pdwValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		exgrid_set_vcd_vt(pNew->nVt, VCD_DWORD);
		pNew->pdwValue = pdwValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(double *pdValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		exgrid_set_vcd_vt(pNew->nVt, VCD_DOUBLE);
		pNew->pdValue = pdValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(float *pfValue, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		exgrid_set_vcd_vt(pNew->nVt, VCD_FLOAT);
		pNew->pfValue = pfValue;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}

	static _ExBaseCellData* CreateNew(CString *pStr, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		exgrid_set_vcd_vt(pNew->nVt, VCD_STRING);
		pNew->pString = pStr;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}
	static _ExBaseCellData* CreateNew(wchar_t *pStr, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		exgrid_set_vcd_vt(pNew->nVt, VCD_WSTRING);
		pNew->pWString = pStr;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}
	static _ExBaseCellData* CreateNew(CStringCmpBlocks *pStrCmpBlks, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		exgrid_set_vcd_vt(pNew->nVt, VCD_STRCMPBLKS);
		pNew->pStrCmpBlks = pStrCmpBlks;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}
	static _ExBaseCellData* CreateNew(SYSTEMTIME *ptmTime, UINT nTimeFormat, CExBaseObject *pObj=NULL, CExBaseList *pExBaseList=NULL, GRID_CELL_EDIT_FUNC pFunc=NULL)
	{
		PEXBASECELLDATA pNew = new _ExBaseCellData;
		memset(pNew, 0, sizeof(_ExBaseCellData));
		exgrid_set_vcd_vt(pNew->nVt, VCD_SYSTEMTIME);
		pNew->ptmTime = ptmTime;
		pNew->pObj = pObj;
		pNew->pExBaseList = pExBaseList;
		pNew->pFunc = pFunc;
		return pNew;
	}
}*PEXBASECELLDATA,EXBASECELLDATA;

#define EXBASEGRID_COL_ID_INDEX   0
