#ifndef SCLCTRLGOUTCHSGRID_H
#define SCLCTRLGOUTCHSGRID_H

#include "SclCtrlChsGridBase.h"

#define SCLCTRLS_GOOSEOUT_CHS_GRID_COLS		3

class QSclCtrlGoutChsGrid : public QSclCtrlChsGridBase
{
public:
	QSclCtrlGoutChsGrid(QWidget* pparent);
	virtual ~QSclCtrlGoutChsGrid();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//���¶��ķ�������

public:
	//�༭������

protected:
};

#endif // SCLCTRLGOUTCHSGRID_H
