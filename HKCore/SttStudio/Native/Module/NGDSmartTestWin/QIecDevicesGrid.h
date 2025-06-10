#pragma once
#include "..\Module\QExBaseListGridBase\QExBaseListGridBase.h"
#include "..\..\61850\Module\SCL\SclIecCfgDatas.h"
#define  QIECDEVICESGRID_COL	5

class QIecDevicesGrid:public QExBaseListGridBase
{
public:
	QIecDevicesGrid(QWidget* pparent = NULL);
	virtual ~QIecDevicesGrid(void);


	CSclIed *m_pSelectIed;//当前选择的IED
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	static void EndEditCell_SelectIED(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	void UpdateSelectState(int nRow);
	CSclIed *GetSelectIED() {return m_pSelectIed;};

};
