#ifndef TCPEDGETESTDATAVIEW_DATASUBS_H
#define TCPEDGETESTDATAVIEW_DATASUBS_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_DataSubs.h"

class CTcpEdgeTestDataView_DataSubs : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_DataSubs(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_DataSubs();

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void OnOK();

private:
	Ui::CTcpEdgeTestDataView_DataSubs ui;

protected slots:
	void slot_addSub(bool bChecked);
	void slot_deleteSub(bool bChecked);
	void slot_editSub(bool bChecked);
	void slot_cbSubs(int nState);
};

#endif // TCPEDGETESTDATAVIEW_DATASUBS_DATASUBS_H
