#ifndef TCPEDGETESTDATAVIEW_APPINSTALLREQ_H
#define TCPEDGETESTDATAVIEW_APPINSTALLREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_AppInstallReq.h"

class CTcpEdgeTestDataView_AppInstallReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_AppInstallReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_AppInstallReq();

private:
	Ui::CTcpEdgeTestDataView_AppInstallReq ui;

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();

protected slots:
	void slot_editCpuClicked();
	void slot_editMemClicked();
	void slot_cbNameStateChanged(int nState);
	void slot_cbFileStateChanged(int nState);
	void slot_btnNameClicked(bool bChecked);
	void slot_groupFileClicked(bool bChecked);
};

#endif
