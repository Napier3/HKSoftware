#ifndef SCLCTRLSSMVOUTGRID_H
#define SCLCTRLSSMVOUTGRID_H

#include "SclCtrlsGridBase.h"

#define SCLCTRLS_SMVOUT_GRID_COLS		13

class CSclCtrlsSmvOutGrid : public CSclCtrlsGridBase
{
public:
	CSclCtrlsSmvOutGrid(QWidget* pparent);
	virtual ~CSclCtrlsSmvOutGrid();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//更新订阅发布配置

public:
	//编辑处理函数

protected:
};

#endif // SCLCTRLSSMVOUTGRID_H
