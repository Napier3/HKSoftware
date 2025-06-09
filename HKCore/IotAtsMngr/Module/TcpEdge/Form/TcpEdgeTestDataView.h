#ifndef TCPEDGETESTDATAVIEW_H
#define TCPEDGETESTDATAVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include "ui_TcpEdgeTestDataView.h"
#include "../TcpEdgeDevice.h"
#include "../../../../Module/DataMngr/DvmDataset.h"

class CTcpEdgeTestDataView : public QWidget
{
	Q_OBJECT

public:	
	bool m_bIsMngrCh;
	QString m_strFunName;		//测试使用的过程ID
	QString m_strRelFunName;	//从过程ID中可能分化出的其他ID,例如FileGet及其相关ID
	CDvmDataset* m_pProducePkg;
	CDvmDataset m_oTempDataset;
	CTcpEdgeDevice* m_pDevice;

	CTcpEdgeTestDataView(QWidget *parent = 0);
	~CTcpEdgeTestDataView();

	virtual void InitUI(CDvmDataset* pDataset);
	virtual void OnOK();

private:
	Ui::CTcpEdgeTestDataView ui;

	void CopyItemData(CExBaseList* pDest, CExBaseList* pSrc);

protected:
	void EnableBlur(bool bEnabled);
	QPushButton* AddGridButton(QTableWidget* pTable, long nRow, long nCol, const QString& strName);
	void UpdateDataset(const QString& strID);
	void UpdateDatasetGroup(const QString& strID);
	virtual void RecordToDataset();
	void UpdateUI(const QString& strID, QTableWidget* pWidget, QStringList list);

signals:
	void sig_adjustSize();

protected slots:
	void slot_autoConnected(int nState);
};

#endif // TCPEDGETESTHEADERVIEW_H
