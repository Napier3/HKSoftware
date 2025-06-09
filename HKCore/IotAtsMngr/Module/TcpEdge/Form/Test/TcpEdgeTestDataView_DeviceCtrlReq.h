#ifndef TCPEDGETESTDATAVIEW_DEVICECTRLREQ_H
#define TCPEDGETESTDATAVIEW_DEVICECTRLREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_DeviceCtrlReq.h"

class CTcpEdgeTestDataView_DeviceCtrlReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_DeviceCtrlReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_DeviceCtrlReq();

private:
	Ui::CTcpEdgeTestDataView_DeviceCtrlReq ui;

	virtual void InitUI(CDvmDataset* pDataset);

protected slots:
};

#endif
