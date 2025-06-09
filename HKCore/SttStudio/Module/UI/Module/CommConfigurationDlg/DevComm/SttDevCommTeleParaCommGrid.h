#ifndef SttCDevCommParaCommGrid_H
#define SttCDevCommParaCommGrid_H
#include <QApplication>
#include "../../QExBaseListGridBase/QExBaseListGridBase.h"

#define STTCDEVCOMMPARACOMMGRID_COLS		4 

//其他参数对应的  装置通讯表
class SttCDevCommParaCommGrid : public QExBaseListGridBase
{
public:
	SttCDevCommParaCommGrid (QWidget* pparent);
	virtual ~SttCDevCommParaCommGrid ();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	static void EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	virtual void SelectRow(int nRow);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;
};

#endif // SttCDevCommParaCommGrid 
