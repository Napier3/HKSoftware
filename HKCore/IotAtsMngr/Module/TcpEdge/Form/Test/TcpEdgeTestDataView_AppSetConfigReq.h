#ifndef TCPEDGETESTDATAVIEW_APPSETCONFIGREQ_H
#define TCPEDGETESTDATAVIEW_APPSETCONFIGREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_AppSetConfigReq.h"

class CTcpEdgeTestDataView_AppSetConfigReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_AppSetConfigReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_AppSetConfigReq();

private:
	Ui::CTcpEdgeTestDataView_AppSetConfigReq ui;

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();

protected slots:
	void slot_editCpuClicked();
	void slot_editMemClicked();
	void slot_currentIndexConChanged(const QString& strText);
	void slot_currentIndexAppChanged(const QString& strText);
};

#endif
