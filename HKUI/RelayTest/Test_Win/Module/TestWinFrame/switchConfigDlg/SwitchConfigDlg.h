#ifndef _SwitchConfigDlg_H_
#define _SwitchConfigDlg_H_

#include <QWidget>
#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QKeyEvent>
#include "../../../../../SttStudio/Module/SttTest/Common/tmt_common_def.h"

class CSwitchConfigDlg : public QDialog
{
	Q_OBJECT

public:
	CSwitchConfigDlg(tmt_BinaryConfig *pBinaryCfg,int nBinInNum,int nBinOutNum,QWidget *pParent = 0);
	~CSwitchConfigDlg();

private:
	QGroupBox *m_pBinInGroup;
	QGroupBox *m_pBinOutGroup;
	QList<QCheckBox *> m_BinInCheckList;
	QList<QCheckBox *> m_BinOutCheckList;
	QRadioButton *m_pRadioLogicAnd;
	QRadioButton *m_pRadioLogicOr;
	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;

private:
	void initUI();
	void keyPressEvent(QKeyEvent *event);

signals:
	void sig_SwitchCfgOK(tmt_BinaryConfig *pBinaryConfig);

private slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_RadioLogicAndClicked();
	void slot_RadioLogicOrClicked();

public:
	tmt_BinaryConfig *m_pBinaryConfig;
	int m_nBinInNum;
	int m_nBinOutNum;
};


#endif