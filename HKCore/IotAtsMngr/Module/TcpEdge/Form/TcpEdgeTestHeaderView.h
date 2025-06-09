#ifndef TCPEDGETESTHEADERVIEW_H
#define TCPEDGETESTHEADERVIEW_H

#include <QWidget>
#include "ui_TcpEdgeTestHeaderView.h"
#include "../../../../Module/DataMngr/DvmDatasetGroup.h"

class CTcpEdgeTestHeaderView : public QWidget
{
	Q_OBJECT

public:
	CDvmDataset* m_pProducePkg;
	CTcpEdgeTestHeaderView(QWidget *parent = 0);
	~CTcpEdgeTestHeaderView();

	void InitUI(CDvmDataset* pDataset);

private:
	Ui::CTcpEdgeTestHeaderView ui;

protected slots:
	void slot_cbTimeStateChanged(int nState);
	void slot_autoConnected(int nState);
};

#endif // TCPEDGETESTHEADERVIEW_H
