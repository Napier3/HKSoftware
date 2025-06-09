#ifndef TCPEDGETESTDATAVIEW_FILEGET_H
#define TCPEDGETESTDATAVIEW_FILEGET_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_FileGet.h"

class CTcpEdgeTestDataView_FileGet : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_FileGet(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_FileGet();

private:
	Ui::CTcpEdgeTestDataView_FileGet ui;

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();

public slots:
	void slot_clicked(bool bChecked);
};

#endif
