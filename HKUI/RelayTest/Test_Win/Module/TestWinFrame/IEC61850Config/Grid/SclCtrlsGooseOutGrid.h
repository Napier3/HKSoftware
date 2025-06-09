#ifndef SCLCTRLSGOOSEOUTGRID_H
#define SCLCTRLSGOOSEOUTGRID_H

#include "SclCtrlsGridBase.h"

#define SCLCTRLS_GOOSEOUT_GRID_COLS		12

class CSclCtrlsGooseOutGrid : public CSclCtrlsGridBase
{
public:
	CSclCtrlsGooseOutGrid(QWidget* pparent);
	virtual ~CSclCtrlsGooseOutGrid();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//更新订阅发布配置

public:
	//编辑处理函数

protected:
};

#endif // SCLCTRLSGOOSEOUTGRID_H
