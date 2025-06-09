#ifndef COMMONSWITCHPARADLG_H
#define COMMONSWITCHPARADLG_H

#include <QWidget>
#include <QDialog>
#include <QStringList>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QKeyEvent>
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../SttTestSysGlobalPara.h"
#include "../Module/SttUIDefine.h"

class CommonSwitchParaDlg : public QDialog
{
	Q_OBJECT

public:
	CommonSwitchParaDlg(QWidget *parent = 0);
	~CommonSwitchParaDlg();

public:
	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;
	QCheckBox* m_pChIns[MAX_BINARYIN_COUNT];
	QCheckBox* m_pChOuts[MAX_BINARYOUT_COUNT];
	QCheckBox* m_pChFaultOuts[MAX_BINARYOUT_COUNT];//sf 20210812 add
	QRadioButton* m_pLogicAnd;
	QRadioButton* m_pLogicOr;
	tmt_BinaryConfig m_oTempConfig;

	void initUI();
	void setData(tmt_BinaryConfig *pBinaryCfg,int nInNum=BININ_NUM,int nOutNum=0,int nFaultOutNum = 0);

	void copyConfig(tmt_BinaryConfig*pSrcCfg, tmt_BinaryConfig*pDstCfg);
	bool compareConfig(tmt_BinaryConfig*pSrcCfg, tmt_BinaryConfig*pDstCfg);

	void keyPressEvent(QKeyEvent *event);
signals:
	void sig_SwitchParaOKClicked();

private slots:
	void slot_OkClicked();
	void slot_CancelClicked();
	void slot_radio_AndStateChanged(bool);
	void slot_radio_OrStateChanged(bool);

private:
	void initConnections();
	void initParas();

	tmt_BinaryConfig *m_pBinaryCfg;
	int m_nInNum;
	int m_nOutNum;
	int m_nFaultOutNum;
};

#endif // COMMONSWITCHPARADLG_H
