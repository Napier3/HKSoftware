#ifndef TCPEDGETESTDATAVIEW_STATUSREQ_H
#define TCPEDGETESTDATAVIEW_STATUSREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_StatusReq.h"

class CTcpEdgeTestDataView_StatusReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_StatusReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_StatusReq();

private:
	Ui::CTcpEdgeTestDataView_StatusReq ui;

	virtual void InitUI(CDvmDataset* pDataset);

protected slots:

};

#endif
