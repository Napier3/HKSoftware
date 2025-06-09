#ifndef IECCFGSMVDATA92GRID_H
#define IECCFGSMVDATA92GRID_H

#include "IecCfgDataGridBase.h"


#define IECCFGSMVDATA92_GRID_COLS		14

class CIecCfgSmvData92Grid : public CIecCfgDataGridBase
{
//	Q_OBJECT

public:
	CIecCfgSmvData92Grid(QWidget* pparent);
	virtual ~CIecCfgSmvData92Grid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	virtual BOOL IsCfgData(CExBaseObject *pIecCfgDataBase);

public:
	//编辑处理函数

protected:
	QIecNumberEditDelegate *m_pSrcMacAddrDelegate;
	CIecSpinBoxDelegate *m_pDelayTimeDelegate;
	QIecNumberEditDelegate *m_pVlanIDDelegate;
	QExBaseListComBoxDelegBase *m_pSynMode_DelegBase;

// public slots:
// 	void slot_doubleClicked(int nRow,int nCol);
};

#endif // IECCFGSMVDATA92GRID_H
