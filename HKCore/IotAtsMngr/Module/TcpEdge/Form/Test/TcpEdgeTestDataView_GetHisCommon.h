#ifndef TCPEDGETESTDATAVIEW_GETHISCOMMON_H
#define TCPEDGETESTDATAVIEW_GETHISCOMMON_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_GetHisCommon.h"

class CTcpEdgeTestDataView_GetHisCommon : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_GetHisCommon(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_GetHisCommon();

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void OnOK();

private:
	Ui::CTcpEdgeTestDataView_GetHisCommon ui;

protected slots:
	void slot_addDevice(bool bChecked);
	void slot_deleteDevice(bool bChecked);
	void slot_editDevice(bool bChecked);
	void slot_cbDevices(int nState);
};

#endif // TCPEDGETESTDATAVIEW_DATASUBS_DATASUBS_H
