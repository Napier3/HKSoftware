#ifndef TCPEDGETESTDATAVIEW_APPSETCFGFILEREQ_H
#define TCPEDGETESTDATAVIEW_APPSETCFGFILEREQ_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_AppSetCfgFileReq.h"

class CTcpEdgeTestDataView_AppSetCfgFileReq : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_AppSetCfgFileReq(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_AppSetCfgFileReq();

private:
	Ui::CTcpEdgeTestDataView_AppSetCfgFileReq ui;

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();

protected slots:
	void slot_cbNameStateChanged(int nState);
	void slot_cbFileStateChanged(int nState);
	void slot_btnNameClicked(bool bChecked);
	void slot_currentIndexChanged(const QString& strText);
	void slot_groupFileClicked(bool bChecked);
};

#endif
