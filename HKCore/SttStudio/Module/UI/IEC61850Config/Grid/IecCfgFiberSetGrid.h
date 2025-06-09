#ifndef IECCFGFIBERSETGRID_H
#define IECCFGFIBERSETGRID_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgFiberPara.h"

#define IECCFG_FIBERSET_GRID_COLS		2

class CIecCfgFiberSetGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:
	CIecCfgFiberSetGrid(QWidget *parent);
	virtual ~CIecCfgFiberSetGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual CDataType* FindDataType(const CString &strDataType);

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);

	long m_nMaxFiberNum;//最大光口数量
	int m_nLeftWidth;//20240103 gongyiping 光口描述宽度设置
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	CExBaseList m_oFiberSetList;


protected:
	QExBaseListComBoxDelegBase *m_pFiberSel_DelegBase;
	BOOL m_bRunning;

public:
	//编辑处理函数
	static void EndEditCell_FiberSetChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	void UpdateData_ByDataType(CIecCfgFiberPara *pIecCfgFiberPara);
	void UpdateDataFiberType();

public slots:
	void slot_doubleClicked(int nRow,int nCol);
	
};

#endif // IECCFGFIBERSETGRID_H
