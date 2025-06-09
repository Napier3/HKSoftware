#ifndef TCPEDGETESTDATAVIEW_CTRLCMD_H
#define TCPEDGETESTDATAVIEW_CTRLCMD_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_CtrlCmd.h"

class CTcpEdgeTestDataView_CtrlCmd : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_CtrlCmd(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_CtrlCmd();

private:
	Ui::CTcpEdgeTestDataView_CtrlCmd ui;
	virtual void RecordToDataset();
	virtual void InitUI(CDvmDataset* pDataset);

public slots:
	void slot_currentIndexChanged(const QString& strText);
};

#endif
