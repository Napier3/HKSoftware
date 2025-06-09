#ifndef BINBOUTMAPSGRID_H
#define BINBOUTMAPSGRID_H


#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"

#define BINBOUTMAPS_GRID_COLS		2

#define BINBOUT_MAPS_TYPE_BIN			0
#define BINBOUT_MAPS_TYPE_BOUT			1

class CBinBoutMapsGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CBinBoutMapsGrid(QWidget* pparent, int iType);
	virtual ~CBinBoutMapsGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;

	CDataType m_oDataType;		//下拉框中数据

public:
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc = NULL);

	//编辑处理函数
	static void EndEditCell_ChMapsString (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

protected:
	QExBaseListEditComBoxDelegBase *m_pDataTypeDelegBase;

public slots:
	void slot_clicked( int nRow,int nCol );
};

#endif // BINBOUTMAPSGRID_H
