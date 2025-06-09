#ifndef TCPEDGETESTDATAVIEW_GETMESSAGE_H
#define TCPEDGETESTDATAVIEW_GETMESSAGE_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_GetMessage.h"

class CTcpEdgeTestDataView_GetMessage : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_GetMessage(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_GetMessage();

private:
	Ui::CTcpEdgeTestDataView_GetMessage ui;

	virtual void InitUI(CDvmDataset* pDataset);

protected slots:
	void slot_cbStartTimeStateChanged(int nState);
	void slot_cbEndTimeStateChanged(int nState);
};

#endif
