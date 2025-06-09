#ifndef TCPEDGETESTDEVSERVICEDLG_H
#define TCPEDGETESTDEVSERVICEDLG_H

#include "ui_TcpEdgeTestDevServiceDlg.h"
#include "../TcpEdgeFormUI.h"

class CTcpEdgeTestDevServiceDlg : public CTcpEdgeFormUI
{
	Q_OBJECT

public:
	bool m_bHasParameter;
	QString m_strDeviceId;
	CTcpEdgeTestDevServiceDlg(QWidget *parent = 0);
	virtual ~CTcpEdgeTestDevServiceDlg();

	int exec(const QString& strTitle, CExBaseList* pData);
	void InitUI(CDvmDataset* pDataset);

private:
	Ui::CTcpEdgeTestDevServiceDlg ui;

protected slots:
	void slot_addData(bool bChecked);
	void slot_deleteData(bool bChecked);
	void slot_cbDataList(int nState);
	void slot_btnOK(bool bChecked);
	void slot_autoConnected(int nState);
	void slot_currentIndexChanged(const QString& strText);
};

#endif // TCPEDGETESTSUBDLG_H
