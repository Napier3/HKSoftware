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
//	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow);//���¶��ķ�������

public:
	//�༭������

protected:
};

#endif // SCLCTRLSSMVINGRID_H
