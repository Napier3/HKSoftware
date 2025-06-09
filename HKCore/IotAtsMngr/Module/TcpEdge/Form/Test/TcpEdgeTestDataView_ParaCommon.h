#ifndef TCPEDGETESTDATAVIEW_PARACOMMON_H
#define TCPEDGETESTDATAVIEW_PARACOMMON_H

#include "../TcpEdgeTestDataView.h"
#include "ui_TcpEdgeTestDataView_ParaCommon.h"

class CTcpEdgeTestDataView_ParaCommon : public CTcpEdgeTestDataView
{
	Q_OBJECT

public:
	CTcpEdgeTestDataView_ParaCommon(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataView_ParaCommon();

private:
	Ui::CTcpEdgeTestDataView_ParaCommon ui;

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();
	virtual void OnOK();

protected slots:
	void slot_addParaList(bool bChecked);
	void slot_deleteParaList(bool bChecked);
	void slot_cbParaList(int nState);
	void slot_cbbParaList(const QString& strText);
};

#endif
