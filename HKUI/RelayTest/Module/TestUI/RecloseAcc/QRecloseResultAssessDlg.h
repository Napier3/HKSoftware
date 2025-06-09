#ifndef QRECLOSERESULTASSESSDLG_H
#define QRECLOSERESULTASSESSDLG_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "../../DataMngr/DataGroup.h"
#include "../../DataMngr/DataMngrGlobal.h"
#include "../../API/GlobalConfigApi.h"
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
class QRecloseResultAssessDlg : public QDialog
{
	Q_OBJECT

public:
	QRecloseResultAssessDlg(CDataGroup *m_oRecloseAccDataGroup ,QWidget *parent = 0);
	virtual ~QRecloseResultAssessDlg();            

	void InitUI();
	void InitFont();
	void InitConnections(); 
	void UpdataResultAssess();
	bool eventFilter(QObject *obj, QEvent *event);

	

public:
	QStringList headers;
	QTableWidget *m_pResultTableWidget;
	QTableWidgetItem *item;


	//QLabel *m_pLabActionTime;
	QLabel *m_pLabTripTime;
	//QLabel *m_pLabAccTime;

	QPushButton *m_pBtnOK;
	QPushButton *m_pBtnCancel;
	QVBoxLayout *m_pMainLayout;
	QHBoxLayout *m_pButtonLayout;
	//QComboBox *m_pCmbActionTime;
    CExBaseListComboBox *m_pCmbTtripTime;
	//QComboBox *m_pCmbAccTime;

	//QTableWidgetItem *m_pItem1;
//	QTableWidgetItem *m_pItem2;
//	QTableWidgetItem *m_pItem3;
	QTableWidgetItem *m_pItem4;
	QTableWidgetItem *m_pItem5;
//	QTableWidgetItem *m_pItem6;
//	QTableWidgetItem *m_pItem7;
//	QTableWidgetItem *m_pItem8;
//	QTableWidgetItem *m_pItem9;

//	QTableWidgetItem *m_pItem10;
	QTableWidgetItem *m_pItem11;
//	QTableWidgetItem *m_pItem12;
	
	CDataGroup *m_pRecloseResultAssessDataGroup;
public slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();

	void slot_cellClicked(int row ,int col);
	void slot_CmbTtripTimeCurrentIndex(int nIndex);
};

#endif
