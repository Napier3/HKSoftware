#ifndef SttCCommCfgDeviceAttrsGrid_H
#define SttCCommCfgDeviceAttrsGrid_H
#include <QApplication>
#include "../../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../../../Module/DataMngr/DvmData.h"


#define STTCCOMMCFGDEVICEATTR_COLS		2 

class SttCCommCfgDeviceAttrsGrid : public QExBaseListGridBase
{
	Q_OBJECT

public:
	SttCCommCfgDeviceAttrsGrid(QWidget* pparent);
	virtual ~SttCCommCfgDeviceAttrsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void SelectRow(int nRow);

	static void EndEditCell_String(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCellDevAddr_String(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	CString TranslateID(CString strID);
	void RemoveAllRowCellWgtInSerial();
	void InitData(CDvmData* pDataTable);
	void setComboSelIndex(QComboBox* pCombo, CString strNameFind);
	void EmitDevAddrChange(long res);
	void EmitNetTableChange();
	BOOL CheckIPValid(CString ip);
	

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	BOOL m_bRunning;

signals:
	void sig_ChangedDevAddr(long);
	void sig_ChangedNetTable();
	void sig_ChangedSerialTable();

public slots:
	void slot_CbPortNumChanged(const QString& strText);
	void slot_CbBoudRateChanged(const QString& strText);
	void slot_CbByteSizeChanged(const QString& strText);
	void slot_CbStopBitChanged(const QString& strText);
	void slot_CbParityChanged(int index);  
};



#endif // SttCCommCfgDeviceAttrsGrid_H
