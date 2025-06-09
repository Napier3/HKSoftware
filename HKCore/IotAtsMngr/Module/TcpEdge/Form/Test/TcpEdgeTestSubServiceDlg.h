#ifndef TCPEDGETESTSUBSERVICEDLG_H
#define TCPEDGETESTSUBSERVICEDLG_H

#include "ui_TcpEdgeTestSubServiceDlg.h"
#include "../TcpEdgeFormUI.h"

class CTcpEdgeTestSubServiceDlg : public CTcpEdgeFormUI
{
	Q_OBJECT

public:
	QString m_strModelName;
	CTcpEdgeTestSubServiceDlg(QWidget *parent = 0);
	virtual ~CTcpEdgeTestSubServiceDlg();

	int exec(const QString& strTitle, CExBaseList* pData);
	void InitUI(CDvmDataset* pDataset);
	void HideDataUI();

	virtual void RecordToDataset();

private:
	Ui::CTcpEdgeTestSubServiceDlg ui;

protected slots:
	void slot_addDevice(bool bChecked);
	void slot_deleteDevice(bool bChecked);
	void slot_cbDeviceList(int nState);
	void slot_addData(bool bChecked);
	void slot_deleteData(bool bChecked);
	void slot_editData(bool bChecked);
	void slot_cbDataList(int nState);
	void slot_btnOK(bool bChecked);
	void slot_autoConnected(int nState);
};

#endif // TCPEDGETESTSUBDLG_H
