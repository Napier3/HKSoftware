#ifndef SCLCTRLSMVINCHSGRID_H
#define SCLCTRLSMVINCHSGRID_H

#include "SclCtrlChsGridBase.h"


#define SCLCTRLS_SMVIN_CHS_GRID_COLS		5

class QSclCtrlSmvInChsGrid : public QSclCtrlChsGridBase
{
public:
	QSclCtrlSmvInChsGrid(QWidget* pparent);
	virtual ~QSclCtrlSmvInChsGrid();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//更新订阅发布配置

public:
	//编辑处理函数

protected:
};

#endif // SCLCTRLSMVINCHSGRID_H
