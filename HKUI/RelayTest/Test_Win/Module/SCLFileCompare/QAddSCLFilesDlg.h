#ifndef QADDSCLFILESDLG_H
#define QADDSCLFILESDLG_H
#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <CString_QT.h>
#include <QDialog>
#include "ui_QAddSCLFilesDlg.h"

class QAddSCLFilesDlg:public QDialog
{
	Q_OBJECT

public:
	Ui::QAddSCLFilesFrame ui;
	QAddSCLFilesDlg(QWidget* pparent = NULL,CString strStandardFilePath = "", CString strBeTestedFilePath = "");
	virtual ~QAddSCLFilesDlg();
	void InitUI();
	void InitFilePaths(CString strStandardFilePath, CString strBeTestedFilePath);
	void InitConnects();
	void DeliverPath();
	void EnabledBtns();

	CString m_strStandardFilePath;
	CString m_strBeTestedFilePath;

	QPushButton *m_InportStandardFileBtn;
	QPushButton *m_InportBeTestedFileBtn;
	QPushButton *m_ClearBtn;
	QTableView *m_pAddSCLFileTable;
	
public slots:
	void slot_m_InportStandardFileBtn_Clicked();
	void slot_m_InportBeTestedFileBtn_Clicked();
	void slot_m_ClearBtn_Clicked();
	void slot_m_OK_clicked();
	void slot_m_Cancel_clicked();


signals:
	void sig_m_OK_clicked(CString strStandardFilePath, CString strBeTestedFilePath);

};


#endif
