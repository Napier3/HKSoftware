#ifndef QCHOOSEDEVICEWIDGET_H
#define QCHOOSEDEVICEWIDGET_H

#include <QWidget>
#include "ui_QChooseDeviceWidget.h"
#include "QIecDevicesGrid.h"
#include "..\..\61850\Module\SCL\SclIecCfgDatas.h"
#include "..\Module\QExBaseListGridBase\QExBaseListGridBase.h"

class QChooseDeviceWidget : public QWidget, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QChooseDeviceWidget(QWidget *pparent = NULL);
	~QChooseDeviceWidget();

	QIecDevicesGrid *m_pIecDevicesGrid;//×°ÖÃÁÐ±í
	CSclStation *m_pSclStation;
	void SetSCLStation(CSclStation *pSclStation);
	void UpdateIEDGrids();
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

private:
	Ui::QChooseDeviceWidget ui;
	
};

#endif // QCHOOSEDEVICEWIDGET_H
