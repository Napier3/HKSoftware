#ifndef TCPEDGETESTHISDEVICEDLG_H
#define TCPEDGETESTHISDEVICEDLG_H

#include "ui_TcpEdgeTestHisDeviceDlg.h"
#include "../TcpEdgeFormUI.h"

class CTcpEdgeTestHisDeviceDlg : public CTcpEdgeFormUI
{
	Q_OBJECT

public:
	CTcpEdgeTestHisDeviceDlg(QWidget *parent = 0);
	virtual ~CTcpEdgeTestHisDeviceDlg();

	int exec(const QString& strTitle, CExBaseList* pData);
	void InitUI(CDvmDataset* pDataset);
	virtual void RecordToDataset();

private:
	Ui::CTcpEdgeTestHisDeviceDlg ui;

protected slots:
	void slot_autoConnected(int nState);
	void slot_btnOK(bool bChecked);
};

#endif // TCPEDGETESTSUBDLG_H
