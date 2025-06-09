#ifndef IECCFGSMV92INCHSGRID_H
#define IECCFGSMV92INCHSGRID_H

#include "IecCfgChsGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92ChIn.h"


#define IECCFGSMV92INCHS_GRID_COLS		5

class CIecCfgSmv92InChsGrid : public CIecCfgChsGridBase
{
	Q_OBJECT

public:
	CIecCfgSmv92InChsGrid(QWidget* pparent);
	virtual ~CIecCfgSmv92InChsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateData_ByDataType(CIecCfg92ChIn *pIecCfgSmv92Ch,int nRow);
	void UpdateDatas_Quality();
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);

public:
	//编辑处理函数
	static void EndEditCell_Smv92ChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

protected:
	QExBaseListCheckBoxDelegate *m_pChSelectDelegate;
	QExBaseListComBoxDelegBase *m_pChAccLevelDelegate;

public slots:

};

#endif // IECCFGSMV92INCHSGRID_H
