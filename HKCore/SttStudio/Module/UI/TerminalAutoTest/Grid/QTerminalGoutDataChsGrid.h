#ifndef QGOUTDATACHSGRID_H
#define QGOUTDATACHSGRID_H
#include "../../IEC61850Config/Grid/IecCfgChsGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGoutCh.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGoutDatas.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGoutChs.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGoutData.h"

#define GOUTDATACHS_GRID_COLS		4
class QGoutMapComBoxDelegBase : public QIecCfgChsComBoxDelegBase
{
public:
	QGoutMapComBoxDelegBase(QObject *parent=NULL);
	~QGoutMapComBoxDelegBase();

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

class QTerminalGoutDataChsGrid : public CIecCfgChsGridBase
{
public:
	QTerminalGoutDataChsGrid(QWidget* parent);
	virtual ~QTerminalGoutDataChsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateData_ByDataType(CIecCfgGoutCh *pIecCfgGoutCh,int nRow);
	void UpdateData_ByChMap(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateData_ByDevCh(CIecCfgGoutCh *pGoutCh,int nRow);

public:
	//±à¼­´¦Àíº¯Êý
	static void EndEditCell_GoutChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

};

#endif 