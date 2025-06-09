#ifndef _TCPEDGEINFORMATIONDLG_H_
#define _TCPEDGEINFORMATIONDLG_H_

#include <QIcon>
#include "TcpEdgeFormUI.h"

namespace Ui {
	class CTcpEdgeInformationDlg;
}

class CTcpEdgeInformationDlg : public CTcpEdgeFormUI
{
private:
	Ui::CTcpEdgeInformationDlg *ui;

	QIcon m_imgInfo;
	QIcon m_imgWarning;
	QIcon m_imgError;
	QIcon m_imgAbout;

public:
	enum
	{
		INFO,
		WARNING,
		ERR,
		ABOUT,
		PERCENT
	};

	explicit CTcpEdgeInformationDlg(QWidget *parent = NULL);
	~CTcpEdgeInformationDlg();

	int exec(long nModel, const QString& strText);
	void show(const QString& strText);
};

#endif