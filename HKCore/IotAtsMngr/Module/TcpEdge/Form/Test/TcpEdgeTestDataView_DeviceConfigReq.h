#ifndef TCPEDGETESTDATAVIEW_DEVICECONFIGREQ_H
#define TCPEDGETESTDATAVIEW_DEVICECONFIGREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_DeviceConfigReq.h"

class CTcpEdgeTestDataView_DeviceConfigReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_DeviceConfigReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_DeviceConfigReq();

private:
	Ui::CTcpEdgeTestDataView_DeviceConfigReq ui;

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();

protected slots:
	void slot_editClicked();
};

#endif
