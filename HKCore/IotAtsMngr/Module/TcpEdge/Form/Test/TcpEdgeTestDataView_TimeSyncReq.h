#ifndef TCPEDGETESTDATAVIEW_TIMESYNCREQ_H
#define TCPEDGETESTDATAVIEW_TIMESYNCREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_TimeSyncReq.h"

class CTcpEdgeTestDataView_TimeSyncReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_TimeSyncReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_TimeSyncReq();

private:
	Ui::CTcpEdgeTestDataView_TimeSyncReq ui;

	virtual void InitUI(CDvmDataset* pDataset);

protected slots:
	void slot_cbTimeStateChanged(int nState);
};

#endif
