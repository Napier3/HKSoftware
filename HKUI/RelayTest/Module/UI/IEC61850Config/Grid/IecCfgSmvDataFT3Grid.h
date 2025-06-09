#ifndef IECCFGSMVDATAFT3GRID_H
#define IECCFGSMVDATAFT3GRID_H

#include "IecCfgDataGridBase.h"


#define IECCFGSMVDATAFT3_GRID_COLS		6


class CIecCfgSmvDataFT3Grid : public CIecCfgDataGridBase
{
	Q_OBJECT

public:
	CIecCfgSmvDataFT3Grid(QWidget* pparent);
	virtual ~CIecCfgSmvDataFT3Grid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	virtual BOOL IsCfgData(CExBaseObject *pIecCfgDataBase);
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);
	virtual void slot_FiberSelUpdate(CIecCfgDataBase *pIecCfgDataBase,int nRow);


public:
	//编辑处理函数

private:
	int m_nSelFiberNum;//已选择通道数量

protected:
	CIecSpinBoxDelegate *m_pDelayTimeDelegate;
	QExBaseListComBoxDelegBase *m_pSynMode_DelegBase;
	QExBaseListComBoxDelegBase *m_pByteNum_DelegBase;
	QFiberSelectedComBoxDelegBase *m_pFiberSelected_DelegBase;


	// public slots:
	// 	void slot_doubleClicked(int nRow,int nCol);
};

#endif // IECCFGSMVDATA92GRID_H
