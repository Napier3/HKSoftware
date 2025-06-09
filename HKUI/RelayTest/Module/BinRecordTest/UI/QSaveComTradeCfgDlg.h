#ifndef QSAVECOMTRADECFGDLG_H
#define QSAVECOMTRADECFGDLG_H

#include <QDialog>
#include "ui_QSaveComTradeCfgDlg.h"
#include "CString_QT.h"

class QSaveComTradeCfgDlg : public QDialog
{
	Q_OBJECT

public:
	QSaveComTradeCfgDlg(QWidget *parent = 0);
	~QSaveComTradeCfgDlg();
	CString m_strFilePath;//文件夹路径
	CString m_strFileName;//文件名称
	CString OpenSelectDirectoryDlg(QWidget *parent, const CString &strTitle, const CString &strFolderPath);
public slots:
	void On_Btn_ChoosePath_clicked();
	void On_Btn_OK_clicked();
	void On_Btn_Cancel_clicked();
	void On_FileTypeChanged();
private:
	Ui::QSaveComTradeCfgDlg ui;
};

#endif // QSAVECOMTRADECFGDLG_H
