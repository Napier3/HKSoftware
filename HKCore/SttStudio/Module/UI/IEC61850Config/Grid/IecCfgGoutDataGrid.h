#ifndef IECCFGGOUTDATAGRID_H
#define IECCFGGOUTDATAGRID_H

#include "IecCfgDataGridBase.h"


#define IECCFGGOUTDATA_GRID_COLS		16

class CIecCfgGoutDataGrid : public CIecCfgDataGridBase
{
//	Q_OBJECT
public:
	CIecCfgGoutDataGrid(QWidget* pparent);
	virtual ~CIecCfgGoutDataGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	virtual BOOL IsCfgData(CExBaseObject *pIecCfgDataBase);

public:
	//±à¼­´¦Àíº¯Êý

protected:

	QIecNumberEditDelegate *m_pSrcMacAddrDelegate;
	QIecNumberEditDelegate *m_pVlanIDDelegate;
	QExBaseListCheckBoxDelegate *m_pTestCheckDelegate;
	QExBaseListCheckBoxDelegate *m_pNdsComCheckDelegate;
// public slots:
// 	void slot_doubleClicked(int nRow,int nCol);
};

#endif // IECCFGGOUTDATAGRID_H
