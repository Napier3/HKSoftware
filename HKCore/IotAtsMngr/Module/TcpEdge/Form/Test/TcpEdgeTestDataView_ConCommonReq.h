#ifndef TCPEDGETESTDATAVIEW_CONCOMMONREQ_H
#define TCPEDGETESTDATAVIEW_CONCOMMONREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_ConCommonReq.h"

class CTcpEdgeTestDataView_ConCommonReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_ConCommonReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_ConCommonReq();

private:
	Ui::CTcpEdgeTestDataView_ConCommonReq ui;

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();
};

#endif
