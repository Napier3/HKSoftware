#ifndef QLOWVOLADDASSESSDLG_H
#define QLOWVOLADDASSESSDLG_H

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
#include "SttMultiMacroLowVolParasDefine.h"
class QLowVolAssessDlg : public QDialog
{
	Q_OBJECT

public:
	QLowVolAssessDlg(CDataGroup *m_oLowVolDataGroup ,QWidget *parent = 0);
	virtual ~QLowVolAssessDlg();            

	void InitUI();
	void InitFont();
	void InitConnections(); 
	void UpdataResultAssess();
	void ComboxModelStyle(QComboBox *pCombox);
	void CbbErrorType(int nIndex, CString strText);
	void SetItemEnable(int nRow, int nCol, BOOL bEnable);
public:
	QStringList headers;
	QTableWidget *m_pResultTableWidget;
	QTableWidgetItem *item;


	QLabel *m_pLabActionTime;
	QLabel *m_pLabUAct;
	QLabel *m_pLabDvdtClose;
	QLabel *m_pLabTripILock;

	QLabel *m_pLabUActNeg;
	QLabel *m_pLabDvdtCloseNeg;
	QLabel *m_pLabTripILockNeg;

	QPushButton *m_pBtnOK;
	QPushButton *m_pBtnCancel;
	QVBoxLayout *m_pMainLayout;
	QHBoxLayout *m_pButtonLayout;
	QComboBox *m_pCmbActionTime;
	QComboBox *m_pCmbUAct;
	QComboBox *m_pCmbDvdtClose;
	QComboBox *m_pCmbTripILock;

	QTableWidgetItem *m_pItem1;
	QTableWidgetItem *m_pItem2;
	QTableWidgetItem *m_pItem3;
	QTableWidgetItem *m_pItem4;
	QTableWidgetItem *m_pItem5;
	QTableWidgetItem *m_pItem6;
	QTableWidgetItem *m_pItem7;
	QTableWidgetItem *m_pItem8;
	QTableWidgetItem *m_pItem9;

	CDataGroup *m_pLowVolAssessDataGroup;
public slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();

	void slot_cellClicked(int row ,int col);
	void slot_cmbErrorChanged(const QString& strText);
};

#endif