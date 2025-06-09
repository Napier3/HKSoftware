#ifndef IECCFGSMV92CHSGRID_H
#define IECCFGSMV92CHSGRID_H

#include "IecCfgChsGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92Ch.h"


#define IECCFGSMV92CHS_GRID_COLS		5

class CIecCfgSmv92ChsGrid : public CIecCfgChsGridBase
{
	Q_OBJECT

public:
	CIecCfgSmv92ChsGrid(QWidget* pparent);
	virtual ~CIecCfgSmv92ChsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateData_ByDataType(CIecCfg92Ch *pIecCfgSmv92Ch,int nRow);
	void UpdateDatas_Quality();
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);

public:
	//编辑处理函数
	static void EndEditCell_Smv92ChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

protected:
	QIecNumberEditDelegate *m_pChQualityDelegate;

public slots:
	void slot_Quality_doubleClicked(int nRow,int nCol);

};

#endif // IECCFGSMV92CHSGRID_H
