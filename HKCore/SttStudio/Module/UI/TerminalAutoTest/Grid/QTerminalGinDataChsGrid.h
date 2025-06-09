#ifndef QGINDATACHSGRID_H
#define QGINDATACHSGRID_H

#include "../../IEC61850Config/Grid/IecCfgChsGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGinCh.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGinDatas.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGinChs.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGinData.h"
#include "../../IEC61850Config/Grid/IecCfgGinChsGrid.h"

#define GINDATACHS_GRID_COLS		4

class QGinMapComBoxDelegBase : public QIecCfgChsComBoxDelegBase
{	
	Q_OBJECT
public:
	QGinMapComBoxDelegBase(QObject *parent=NULL);
	~QGinMapComBoxDelegBase();

	virtual void setEditorData(QWidget * editor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

class QTerminalGinDataChsGrid : public CIecCfgChsGridBase
{
public:
	QTerminalGinDataChsGrid(QWidget* pparent);
	virtual ~QTerminalGinDataChsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateData_ByDataType(CIecCfgGinCh *pIecCfgGinCh,int nRow);
	void UpdateData_ByChMap(CIecCfgGinCh *pGinCh,int nRow);
	void UpdateData_ByDevCh(CIecCfgGinCh *pGinCh,int nRow);

public:
	static void EndEditCell_GinChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);


};

#endif 
