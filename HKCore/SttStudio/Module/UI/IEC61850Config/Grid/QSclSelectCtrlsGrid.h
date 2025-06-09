#ifndef QSCLSELECTCTRLSGRID_H
#define QSCLSELECTCTRLSGRID_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"


#define SCL_SCLCTRLS__GRID_COLS		4

class QSclSelectCtrlsGrid : public QExBaseListGridBase
{
public:
	QSclSelectCtrlsGrid(QWidget* pparent);
	virtual ~QSclSelectCtrlsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	QExBaseListComBoxDelegBase *m_pChType_DelegBase;
	BOOL m_bRunning;


};


#endif // QSCLSELECTCTRLSGRID_H
