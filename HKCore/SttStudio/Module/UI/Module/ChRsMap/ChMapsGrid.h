#ifndef CHMAPSGRID_H
#define CHMAPSGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#define CHMAPS_GRID_COLS		4

class CChMapsGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CChMapsGrid(QWidget* pparent);
	virtual ~CChMapsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;



public:
	//±à¼­´¦Àíº¯Êý
	static void EndEditCell_ChMapsString (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

public slots:
	void slot_clicked( int nRow,int nCol );



};

#endif // CHMAPSGRID_H
