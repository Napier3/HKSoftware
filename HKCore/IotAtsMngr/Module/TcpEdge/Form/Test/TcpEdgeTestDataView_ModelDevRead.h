#ifndef TCPEDGETESTDATAVIEW_MODELDEVREAD_H
#define TCPEDGETESTDATAVIEW_MODELDEVREAD_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_ModelDevRead.h"

class CTcpEdgeTestDataView_ModelDevRead : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_ModelDevRead(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_ModelDevRead();

private:
	Ui::CTcpEdgeTestDataView_ModelDevRead ui;

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();
	virtual void OnOK();

protected slots:
	void slot_addDevice(bool bChecked);
	void slot_deleteDevice(bool bChecked);
	void slot_cbModels(int nState);
};

#endif
