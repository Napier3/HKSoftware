#ifndef SCLCTRLSSMVINGRID_H
#define SCLCTRLSSMVINGRID_H

#include "SclCtrlsGridBase.h"


#define SCLCTRLS_SMVIN_GRID_COLS		12

class CSclCtrlsSmvInGrid : public CSclCtrlsGridBase
{
public:
	CSclCtrlsSmvInGrid(QWidget* pparent);
	virtual ~CSclCtrlsSmvInGrid();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//更新订阅发布配置

public:
	//编辑处理函数

protected:
};

#endif // SCLCTRLSSMVINGRID_H
