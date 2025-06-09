#ifndef TCPEDGETESTDATAVIEW_DATAREAD_H
#define TCPEDGETESTDATAVIEW_DATAREAD_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_DataRead.h"

class CTcpEdgeTestDataView_DataRead : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_DataRead(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_DataRead();

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void OnOK();

private:
	Ui::CTcpEdgeTestDataView_DataRead ui;

protected slots:
	void slot_addDevice(bool bChecked);
	void slot_deleteDevice(bool bChecked);
	void slot_editDevice(bool bChecked);
	void slot_cbDevices(int nState);
};

#endif // TCPEDGETESTDATAVIEW_DATASUBS_DATASUBS_H
