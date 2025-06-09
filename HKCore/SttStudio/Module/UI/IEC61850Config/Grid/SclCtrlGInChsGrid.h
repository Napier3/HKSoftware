#ifndef SCLCTRLGINCHSGRID_H
#define SCLCTRLGINCHSGRID_H

#include "SclCtrlChsGridBase.h"

#define SCLCTRLS_GOOSEIN_CHS_GRID_COLS		6


class QSclCtrlGInChsGrid : public QSclCtrlChsGridBase
{
public:
	QSclCtrlGInChsGrid(QWidget* pparent);
	virtual ~QSclCtrlGInChsGrid();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//���¶��ķ�������


protected:
};

#endif // SCLCTRLGINCHSGRID_H
