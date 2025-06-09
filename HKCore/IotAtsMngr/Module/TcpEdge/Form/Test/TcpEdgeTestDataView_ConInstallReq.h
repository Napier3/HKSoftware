#ifndef TCPEDGETESTDATAVIEW_CONINSTALLREQ_H
#define TCPEDGETESTDATAVIEW_CONINSTALLREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_ConInstallReq.h"

class CTcpEdgeTestDataView_ConInstallReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_ConInstallReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_ConInstallReq();

private:
	Ui::CTcpEdgeTestDataView_ConInstallReq ui;

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();
	virtual void OnOK();

protected slots:
	void slot_editCpuClicked();
	void slot_editMemClicked();
	void slot_editDiskClicked();
	void slot_addPort(bool bChecked);
	void slot_deletePort(bool bChecked);
	void slot_cbPort(int nState);
	void slot_addMount(bool bChecked);
	void slot_deleteMount(bool bChecked);
	void slot_cbMount(int nState);
	void slot_addDev(bool bChecked);
	void slot_deleteDev(bool bChecked);
	void slot_cbDev(int nState);
	void slot_currentIndexChanged(const QString& strText);
};

#endif
