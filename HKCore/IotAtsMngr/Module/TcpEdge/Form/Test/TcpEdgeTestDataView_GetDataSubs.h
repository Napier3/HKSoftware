#ifndef TCPEDGETESTDATAVIEW_GETDATASUBS_H
#define TCPEDGETESTDATAVIEW_GETDATASUBS_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_GetDataSubs.h"

class CTcpEdgeTestDataView_GetDataSubs : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_GetDataSubs(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_GetDataSubs();

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void OnOK();

private:
	Ui::CTcpEdgeTestDataView_GetDataSubs ui;

protected slots:
	void slot_addSub(bool bChecked);
	void slot_deleteSub(bool bChecked);
	void slot_editSub(bool bChecked);
	void slot_cbSubs(int nState);
};

#endif // TCPEDGETESTDATAVIEW_DATASUBS_DATASUBS_H
