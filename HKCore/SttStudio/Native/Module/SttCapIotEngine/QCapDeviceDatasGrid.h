#ifndef QCAPDEVICEDATASGRID_H
#define QCAPDEVICEDATASGRID_H
#include "..\QExBaseListGridBase\QExBaseListGridBase.h"
#include <QHeaderView>
#include "..\DataMngr\DvmValue.h"
#include "..\DataMngr\DvmData.h"
#define QCAPDEVDATASGRID_COLS  11

class QCapDeviceDatasGrid:public QExBaseListGridBase
{
	Q_OBJECT

public:
	QCapDeviceDatasGrid(QWidget *pparent = NULL);
	virtual ~QCapDeviceDatasGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	void UpdateDatas();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void ShowAttrValue(CDvmData *pData, int nRow, int nCol, CString &strAttrID, long nPrecision);

	void ShowChannelDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	void ShowChannelData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};
#endif
