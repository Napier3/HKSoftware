#ifndef TCPEDGETESTDATAVIEW_DEVICEUPDATEREQ_H
#define TCPEDGETESTDATAVIEW_DEVICEUPDATEREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_DeviceUpdateReq.h"

class CTcpEdgeTestDataView_DeviceUpdateReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_DeviceUpdateReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_DeviceUpdateReq();

private:
	Ui::CTcpEdgeTestDataView_DeviceUpdateReq ui;

	virtual void InitUI(CDvmDataset* pDataset);

protected slots:
	void slot_cbNameStateChanged(int nState);
	void slot_cbFileStateChanged(int nState);
	void slot_btnNameClicked(bool bChecked);
	void slot_groupFileClicked(bool bChecked);
};

#endif
