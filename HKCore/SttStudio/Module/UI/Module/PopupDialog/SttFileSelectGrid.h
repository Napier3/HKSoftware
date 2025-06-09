#ifndef STTFILESELECTGRID_H
#define STTFILESELECTGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#define STTFILESELECT_GRID_COLS		2

class CSttFileSelectGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CSttFileSelectGrid(QWidget* pparent);
	virtual ~CSttFileSelectGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);


public:
	//±à¼­´¦Àíº¯Êý
	static void EndEditCell_SelectFile(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

protected:
	QExBaseListCheckBoxDelegate *m_pFileSelectDelegate;

public:
	
signals:
	void sig_UpdateCheckState(int nRow);

public slots:
	void slot_clicked( int nRow,int nCol );
	void slot_UpdateCheckState(int nRow);
	virtual void slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
};

#endif // CHMAPSGRID_H
