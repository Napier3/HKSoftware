#ifndef QSTTSAVECFGDLG_H
#define QSTTSAVECFGDLG_H

#include <QDialog>
#include "ui_QSttSaveCfgDlg.h"

class QSttSaveCfgDlg : public QDialog
{
	Q_OBJECT

public:
	QSttSaveCfgDlg(QString strFilePath, QString strFileName,QWidget *parent = 0);
	~QSttSaveCfgDlg();

	Ui::QSttSaveCfgDlg ui;

	void InitData(QString strFilePath, QString strFileName);


public slots:
	void slot_m_pBtnSelPath();   //Ñ¡ÔñÂ·¾¶
	void slot_m_pBtnOk();
	void slot_m_pBtnCancel();


};

#endif
