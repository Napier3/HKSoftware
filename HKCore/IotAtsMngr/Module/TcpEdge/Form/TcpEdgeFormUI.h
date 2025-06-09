#ifndef _TCPEDGEFORMUI_H_
#define _TCPEDGEFORMUI_H_

#include <QDialog>
#include <QMouseEvent>
#include "TcpEdgeUIGlobalDef.h"
#include "../TcpEdgeDevice.h"

class CTcpEdgeFormUI : public QDialog
{
private:
	QPoint m_ptStart;
	bool m_bLButtonDown;
	QWidget* m_pWidget;
	QWidget* m_pTitle;

public:
	CTcpEdgeDevice* m_pDevice;
	CDvmDataset* m_pProducePkg;
	CDvmDatasetGroup m_oTempDataset;

	CTcpEdgeFormUI(QWidget *parent = 0);
	virtual ~CTcpEdgeFormUI();

	void EnableBlur(bool bEnabled);
	void InitFormUI(QWidget* pWidget, QWidget* pTitle);
	QPushButton* AddGridButton(QTableWidget* pTable, long nRow, long nCol, const QString& strName);
	virtual void RecordToDataset();

protected:
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent *event);

protected slots:
	void slot_autoConnected(int nState);
};

#endif