#ifndef TCPEDGETESTDATAVIEW_PARAREAD_H
#define TCPEDGETESTDATAVIEW_PARAREAD_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_ParaRead.h"

class CTcpEdgeTestDataView_ParaRead : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_ParaRead(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_ParaRead();

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();
	virtual void OnOK();

private:
	Ui::CTcpEdgeTestDataView_ParaRead ui;

protected slots:
	void slot_addService(bool bChecked);
	void slot_deleteService(bool bChecked);
	void slot_editService(bool bChecked);
	void slot_cbServices(int nState);
};

#endif // TCPEDGETESTDATAVIEW_DATASUBS_DATASUBS_H
