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
//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//���¶��ķ�������

public:
	//�༭������

protected:
};

#endif // SCLCTRLSGOOSEOUTGRID_H
