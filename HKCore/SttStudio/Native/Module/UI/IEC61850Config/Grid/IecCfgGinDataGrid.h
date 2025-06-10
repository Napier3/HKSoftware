#ifndef IECCFGGINDATAGRID_H
#define IECCFGGINDATAGRID_H

#include "IecCfgDataGridBase.h"


#define IECCFGGINDATA_GRID_COLS		14

class CIecCfgGinDataGrid : public CIecCfgDataGridBase
{
public:

	CIecCfgGinDataGrid(QWidget* pparent);
	virtual ~CIecCfgGinDataGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	virtual BOOL IsCfgData(CExBaseObject *pIecCfgDataBase);
public:
	//±à¼­´¦Àíº¯Êý

protected:
	QExBaseListComBoxDelegBase *m_pTestCheckDelegate;
	QExBaseListCheckBoxDelegate *m_pNdsComCheckDelegate;
	QExBaseListCheckBoxDelegate *m_pNotGocbCheckDelegate;

};

#endif // IECCFGGINDATAGRID_H
