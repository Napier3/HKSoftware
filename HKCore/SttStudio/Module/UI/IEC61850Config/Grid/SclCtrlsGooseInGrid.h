#ifndef SCLCTRLSGOOSEINGRID_H
#define SCLCTRLSGOOSEINGRID_H

#include "SclCtrlsGridBase.h"

#define SCLCTRLS_GOOSEIN_GRID_COLS		15

class CSclCtrlsGooseInGrid : public CSclCtrlsGridBase
{
public:
	CSclCtrlsGooseInGrid(QWidget* pparent);
	virtual ~CSclCtrlsGooseInGrid();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//更新订阅发布配置

public:
	//编辑处理函数

protected:
};

#endif // SCLCTRLSGOOSEINGRID_H
