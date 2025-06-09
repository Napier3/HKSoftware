#ifndef TCPEDGETESTDEVICEDLG_H
#define TCPEDGETESTDEVICEDLG_H

#include "ui_TcpEdgeTestDeviceDlg.h"
#include "../TcpEdgeFormUI.h"

class CTcpEdgeTestDeviceDlg : public CTcpEdgeFormUI
{
	Q_OBJECT

public:
	CTcpEdgeTestDeviceDlg(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDeviceDlg();

	int exec(const QString& strTitle, CExBaseList* pData);
	void InitUI(CDvmDataset* pDataset, const QString& strType);
	virtual void RecordToDataset();

private:
	Ui::CTcpEdgeTestDeviceDlg ui;

protected slots:
	void slot_addService(bool bChecked);
	void slot_deleteService(bool bChecked);
	void slot_editService(bool bChecked);
	void slot_cbServices(int nState);
	void slot_autoConnected(int nState);
	void slot_btnOK(bool bChecked);
};

#endif // TCPEDGETESTSUBDLG_H
