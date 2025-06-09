#ifndef QBINARYREVERSECFGWIDGET_H
#define QBINARYREVERSECFGWIDGET_H

#include <QDialog>
#include "ui_QBinReverseCfgWidget.h"
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include "CString_QT.h"
#include <qevent.h>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../SttTest/Common/tmt_system_config.h"

class QBinReverseCfgDialog : public QDialog
{
	Q_OBJECT

public:
	QBinReverseCfgDialog(QWidget *parent = 0);
	~QBinReverseCfgDialog();
	CDataGroup m_oBinCfgParas;
	tmt_BinConfig m_oBinCfg[MAX_BINARYIN_COUNT];
	CString m_strName[MAX_BINARYIN_COUNT];
	void InitBinInfos();
	void SaveBinConfigs();
	void InitUI();
	void GenerareParas();//拼接参数
	void SetParas();//下发参数
	void handleEnterKey();
#ifdef _PSX_QT_LINUX_
    virtual void keyPressEvent(QKeyEvent *event) ;
#else
	virtual void keyPressEvent(QKeyEvent *event)override;
#endif

private:
	Ui::QBinaryReverseCfgWidget ui;
	QCheckBox *m_pCheckBoxBeEmpty[MAX_BINARYIN_COUNT];
	QLabel *m_pTextLabelBin[MAX_BINARYIN_COUNT];
	QLineEdit *m_pEdit[MAX_BINARYIN_COUNT];
	

public slots:
	void On_Btn_OK_clicked();
	void On_Btn_Cancel_clicked();
	void On_BeEmptyChanged();
	void On_ReverseThresholdChanged();
};
extern STT_SystemParas g_oSystemParas;
#endif // QBINARYREVERSECFGWIDGET_H
