#ifndef SCLCTRLSMVOUTCHSGRID_H
#define SCLCTRLSMVOUTCHSGRID_H

#include "SclCtrlChsGridBase.h"

#define SCLCTRLS_SMVOUT_CHS_GRID_COLS		3

class QSclCtrlSmvOutChsGrid : public QSclCtrlChsGridBase
{
public:
	QSclCtrlSmvOutChsGrid(QWidget* pparent);
	virtual ~QSclCtrlSmvOutChsGrid();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//���¶��ķ�������

public:
	//�༭������

protected:
};

#endif // SCLCTRLSMVOUTCHSGRID_H
