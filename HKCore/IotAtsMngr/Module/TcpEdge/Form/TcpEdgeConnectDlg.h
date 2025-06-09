#ifndef _TCPEDGECONNECTDLG_H_
#define _TCPEDGECONNECTDLG_H_

#include "TcpEdgeFormUI.h"

namespace Ui {
	class CTcpEdgeConnectDlg;
}

class CTcpEdgeConnectDlg : public CTcpEdgeFormUI
{
private:
	Ui::CTcpEdgeConnectDlg *ui;

public:
	explicit CTcpEdgeConnectDlg(QWidget *parent = NULL);
	~CTcpEdgeConnectDlg();

	void InitIP(QStringList strIPs);
	QString GetLocalIP();
	QString GetIP();
	long GetMngrPort();
	long GetDataPort();
	bool IsSign();
	bool IsZilb();
};

#endif