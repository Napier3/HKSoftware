#ifndef IECCFGSMVDATA92INGRID_H
#define IECCFGSMVDATA92INGRID_H

#include "IecCfgDataGridBase.h"


#define IECCFGSMVDATA92IN_GRID_COLS		6

class CIecCfgSmvData92InGrid : public CIecCfgDataGridBase
{
public:
	CIecCfgSmvData92InGrid(QWidget* pparent);
	virtual ~CIecCfgSmvData92InGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	virtual BOOL IsCfgData(CExBaseObject *pIecCfgDataBase);

public:
	//编辑处理函数

protected:
	CIecSpinBoxDelegate *m_pDelayTimeDelegate;
	QIecNumberEditDelegate *m_pVlanIDDelegate;
	QExBaseListComBoxDelegBase *m_pSynMode_DelegBase;
};

#endif // IECCFGSMVDATA92INGRID_H
