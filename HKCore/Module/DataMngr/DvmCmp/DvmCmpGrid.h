#pragma once

#include "DvmCmpTool.h"
#include "..\..\GridBase\ExBaseListGrid.h"


#define DVMCMPOBJ_COL_INDEX       0
#define DVMCMPOBJ_COL_NAME        1
#define DVMCMPOBJ_COL_ID          2
#define DVMCMPOBJ_COL_DATATYPE    3
#define DVMCMPOBJ_COL_MINOCC      4
#define DVMCMPOBJ_COL_MAXOCC      5
#define DVMCMPOBJ_COL_STEP        6

#define DVMCMPOBJ_COLS            7

#define WM_DVMCMPGRIDSTAND_SELDEST	(WM_USER+929)
#define WM_DVMCMPGRIDDEST_SELSTAND	(WM_USER+930)
#define WM_DVMCMPGRIDSTAND_POPDEST	(WM_USER+931)
#define WM_DVMCMPGRIDDEST_POPSTAND	(WM_USER+932)

class CDvmCmpGridBase : public CExBaseListGrid
{
public:
	CDvmCmpGridBase();
	virtual ~CDvmCmpGridBase();

	CDvmCmpTool *m_pDvmCmpTool;

	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pExDataList);
	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);

	virtual void InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);

	void AttatchDvmCmpRef(CDvmCmpGridBase *pRef)	{	m_pDvmCmpRef = pRef;	}
	virtual void UpdateDvmCmbObj(CExBaseObject *pDvmCmpObj)	{	};

protected:
	virtual void InitGridTitle();

	CDvmCmpGridBase *m_pDvmCmpRef;

	virtual void AfterOnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void AfterOnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	static long g_nDvmCmpGridOptrRefCount;

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowDataValues(CExBaseObject *pData, int& nRow);
	virtual void ShowDataValue(CExBaseObject *pData, int& nRow);

	virtual BOOL PostDvmCmpSelMsg(UINT nMsg, const CCellID &idCell);
};

class CDvmCmpGridStand : public CDvmCmpGridBase
{
public:
	CDvmCmpGridStand();
	virtual ~CDvmCmpGridStand();

protected:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowDataValue(CExBaseObject *pData, int& nRow);

	virtual BOOL OnCellRButtonUp(const CCellID &idCell);
	virtual void UpdateDvmCmbObj(CExBaseObject *pDvmCmpObj);
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);

};


class CDvmCmpGridDest : public CDvmCmpGridBase
{
public:
	CDvmCmpGridDest();
	virtual ~CDvmCmpGridDest();

protected:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowDataValue(CExBaseObject *pData, int& nRow);

	virtual BOOL OnCellRButtonUp(const CCellID &idCell);
	virtual void UpdateDvmCmbObj(CExBaseObject *pDvmCmpObj);
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);

};

