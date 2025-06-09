#ifndef QLOWFREPRESULTASSESSDLG_H
#define QLOWFREPRESULTASSESSDLG_H

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
#include "SttMultiMacroLowFreqParasDefine.h"

class QLowFrepResultAssessDlg : public QDialog
{
	Q_OBJECT

public:
	QLowFrepResultAssessDlg(CDataGroup *m_oLowFrepDataGroup, QWidget *parent = 0);
	virtual ~QLowFrepResultAssessDlg();            

	void InitUI();
	void InitFont();
	void InitConnections();
	void UpdataResultAssess();
	void ComboxModelStyle(QComboBox *pCombox);
	void CbbErrorType(int nIndex, CString strText);
	void SetItemEnable(int nRow, int nCol, BOOL bEnable);


public:
	QStringList m_Headers;
	QTableWidget *m_pResultTableWidget;

	QLabel *m_pLabTripFre;
	QLabel *m_pLabActionTime;
	QLabel *m_pLabDvdtClose;
	QLabel *m_pLabTripILock;
	QLabel *m_pLabTripULock;


	QLabel *m_pLabTripFreNeg;
	QLabel *m_pLabDvdtCloseNeg;
	QLabel *m_pLabTripILockNeg;
	QLabel *m_pLabTripULockNeg;


	QPushButton *m_pBtnOK;
	QPushButton *m_pBtnCancel;
	QVBoxLayout *m_pMainLayout;
	QHBoxLayout *m_pButtonLayout;


	QComboBox *m_pCmbActionTime;
	QComboBox *m_pCmbTripFre;
	QComboBox *m_pCmbDvdtClose;
	QComboBox *m_pCmbTripILock;
	QComboBox *m_pCmbTripULock;


	QTableWidgetItem *m_pItem1;
	QTableWidgetItem *m_pItem2;
	QTableWidgetItem *m_pItem3;
	QTableWidgetItem *m_pItem4;
	QTableWidgetItem *m_pItem5;
	QTableWidgetItem *m_pItem6;
	QTableWidgetItem *m_pItem7;
	QTableWidgetItem *m_pItem8;
	QTableWidgetItem *m_pItem9;
	QTableWidgetItem *m_pItem10;
	QTableWidgetItem *m_pItem11;

	CDataGroup *m_oLowFrepResultAssessDataGroup;
public slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();

	void slot_cellClicked(int row ,int col);
	void slot_cmbErrorChanged(const QString& strText);
};

#endif