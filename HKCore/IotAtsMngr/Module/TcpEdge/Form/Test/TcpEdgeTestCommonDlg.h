#ifndef TCPEDGETESTCOMMONDLG_H
#define TCPEDGETESTCOMMONDLG_H

#include "ui_TcpEdgeTestCommonDlg.h"
#include "../TcpEdgeFormUI.h"

class CTcpEdgeTestCommonDlg : public CTcpEdgeFormUI
{
	Q_OBJECT

public:
	CTcpEdgeTestCommonDlg(QWidget *parent = 0);
	virtual ~CTcpEdgeTestCommonDlg();

	int exec(const QString& strTitle, CExBaseList* pData);
	void InitUI(CDvmDataset* pDataset);

	QString GetCpus();
	QString GetCpuLmt();
	QString GetMemory();
	QString GetMemLmt();
	QString GetDisk();
	QString GetDiskLmt();
	QString GetTemLow();
	QString GetTemHigh();

private:
	Ui::CTcpEdgeTestCommonDlg ui;

protected slots:
	void slot_autoConnected(int nState);
};

#endif // TCPEDGETESTSUBDLG_H
