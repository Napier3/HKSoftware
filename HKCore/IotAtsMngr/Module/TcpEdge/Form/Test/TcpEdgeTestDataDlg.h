#ifndef TCPEDGETESTDATADLG_H
#define TCPEDGETESTDATADLG_H

#include "ui_TcpEdgeTestDataDlg.h"
#include "../TcpEdgeFormUI.h"

class CTcpEdgeTestDataDlg : public CTcpEdgeFormUI
{
	Q_OBJECT

public:
	QString m_strModelName;
	QString m_strType;
	CTcpEdgeTestDataDlg(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDataDlg();

	int exec(const QString& strTitle, CExBaseList* pData);
	void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();

private:
	Ui::CTcpEdgeTestDataDlg ui;

protected slots:
	void slot_autoConnected(int nState);
};

#endif // TCPEDGETESTSUBDLG_H
