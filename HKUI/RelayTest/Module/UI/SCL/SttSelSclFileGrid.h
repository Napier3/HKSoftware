#ifndef STTSELSCLFILEGRID_H
#define STTSELSCLFILEGRID_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"


#define STTSELSCLFILE_GRID_COLS		4

class CSttSelSclFileGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:
	CSttSelSclFileGrid(QWidget* pparent);
	virtual ~CSttSelSclFileGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	static void EndEditCell_SclFileSel(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	
	void DelSelectData();
	void UpdateSelectState(int nRow);

public:
	//编辑处理函数
	virtual void DisConnectAll_SigSlot();
	virtual void ConnectAll_SigSlot(); 

protected:
	QExBaseListCheckBoxDelegate *m_pSelectSclFileDelegate;

signals:
	void sig_UpdateSelectState();
public slots:
	void slot_UpdateSelectState();
};

#endif // STTSELSCLFILEGRID_H
