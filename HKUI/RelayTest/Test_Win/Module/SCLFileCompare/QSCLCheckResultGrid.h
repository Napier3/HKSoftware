#ifndef QSCLCHECKRESULTGRID_H
#define QSCLCHECKRESULTGRID_H
#include "../TestWinFrame/QExBaseListGridBase/QExBaseListGridBase.h"

#define SCLCHECKRESULTGRID_COLS  8

class QSCLCheckResultGrid: public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSCLCheckResultGrid(QWidget* pparent);
	virtual ~QSCLCheckResultGrid();
	QColor m_oColor;//2024 1-2 zhouyangyong 新增偶数行颜色

	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);//2024 1-2 zhouyangyong 新增换行后刷新颜色

};

#endif