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
	//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//更新订阅发布配置

public:
	//编辑处理函数

protected:
};

#endif // SCLCTRLSMVOUTCHSGRID_H
