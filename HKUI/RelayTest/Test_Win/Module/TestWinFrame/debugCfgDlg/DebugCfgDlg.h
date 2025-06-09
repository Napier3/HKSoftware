#ifndef _DebugCfgDlg_H_
#define _DebugCfgDlg_H_

#include <QWidget>
#include <QDialog>
#include <QCheckBox>
#include <QPushButton>
#include <QKeyEvent>

class CDebugCfgDlg : public QDialog
{
	Q_OBJECT

public:
	CDebugCfgDlg(QWidget *pParent = 0);
	~CDebugCfgDlg();

private:
	QCheckBox *m_chb_saveFile;
	QCheckBox *m_chb_printLog;

	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;

	void initUI();
	void initConnections();
	void initData();

private slots:
	void slot_OKClicked();
	void slot_CancelClicked();

public:
	long m_nValue;
	void setData(long nValue);
};

#endif