#ifndef TCPEDGETESTHISSERVICEDLG_H
#define TCPEDGETESTHISSERVICEDLG_H

#include "ui_TcpEdgeTestHisServiceDlg.h"
#include "../TcpEdgeFormUI.h"

class CTcpEdgeTestHisServiceDlg : public CTcpEdgeFormUI
{
	Q_OBJECT

public:
	CTcpEdgeTestHisServiceDlg(QWidget *parent = 0);
	virtual ~CTcpEdgeTestHisServiceDlg();

	int exec(const QString& strTitle, CExBaseList* pData);
	void InitUI(CDvmDataset* pDataset);

private:
	Ui::CTcpEdgeTestHisServiceDlg ui;

protected slots:
	void slot_autoConnected(int nState);
	void slot_btnOK(bool bChecked);
};

#endif // TCPEDGETESTSUBDLG_H
