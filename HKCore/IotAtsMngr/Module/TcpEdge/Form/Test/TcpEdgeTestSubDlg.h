#ifndef TCPEDGETESTSUBDLG_H
#define TCPEDGETESTSUBDLG_H

#include "ui_TcpEdgeTestSubDlg.h"
#include "../TcpEdgeFormUI.h"

class CTcpEdgeTestSubDlg : public CTcpEdgeFormUI
{
	Q_OBJECT

public:
	CTcpEdgeTestSubDlg(QWidget *parent = 0);
	virtual ~CTcpEdgeTestSubDlg();

	int exec(const QString& strTitle, CExBaseList* pData);
	void InitUI(CDvmDataset* pDataset, const QString& strType);
	virtual void RecordToDataset();

private:
	Ui::CTcpEdgeTestSubDlg ui;

protected slots:
	void slot_addService(bool bChecked);
	void slot_deleteService(bool bChecked);
	void slot_editService(bool bChecked);
	void slot_cbServices(int nState);
	void slot_autoConnected(int nState);
	void slot_btnOK(bool bChecked);
};

#endif // TCPEDGETESTSUBDLG_H
