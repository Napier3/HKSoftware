#ifndef TCPEDGETESTDATAVIEW_APPCOMMONREQ_H
#define TCPEDGETESTDATAVIEW_APPCOMMONREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_AppCommonReq.h"

class CTcpEdgeTestDataView_AppCommonReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_AppCommonReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_AppCommonReq();

private:
	Ui::CTcpEdgeTestDataView_AppCommonReq ui;

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();

protected slots:
	void slot_currentIndexChanged(const QString& strText);
};

#endif
