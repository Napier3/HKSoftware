#ifndef  QSTTBINRECORDMODULEGRID
#define  QSTTBINRECORDMODULEGRID

#include "../../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "QSttBinRecordChsGrid.h"
#include "../../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceMngr.h"

#define QSTTBINRECORDMODULEGRIDCOL   6

class QSttBinRecordModuleCheckBoxDelegate : public QExBaseListCheckBoxDelegate
{

public:
	QSttBinRecordModuleCheckBoxDelegate(QObject *parent = NULL);
	virtual ~QSttBinRecordModuleCheckBoxDelegate();

	virtual bool editorEvent(QEvent * event,
		QAbstractItemModel * model,
		const QStyleOptionViewItem &/* option*/,
		const QModelIndex & index);

};

class QSttBinRecordModuleGrid :public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttBinRecordModuleGrid(QWidget *parent = NULL);
	virtual ~QSttBinRecordModuleGrid();

	virtual void InitGrid(CCapDeviceMngr *pCapDeviceAll);
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	void ShowChildren(CDataGroup *pDataGroup, int& nRow, BOOL bInsertRow = TRUE);
	static void EndEditCell_CheckChanged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	CCapDeviceMngr *m_pCapDeviceAll;
	QSttBinRecordChsGrid *m_pBinRecordChsGrid;

signals:
	void sig_CheckBoxValue(int nRow, int nState);

public slots:
	void slot_BinRecordModuleGrid(int nRow, int nCol);
	void slot_CellChanged(int nRow, int nCol);

public:
	QExBaseListCheckBoxDelegate *m_pFileSelectDelegate;

};


#endif
