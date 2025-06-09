#ifndef QSTTMUPARASWIDGET_H
#define QSTTMUPARASWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../Controls/SttGroupBox.h"
class QSttMUParasWidget : public QWidget
{
	Q_OBJECT

public:
	QSttMUParasWidget(BOOL *pbTmtParaChanged,QWidget *parent);
	~QSttMUParasWidget();

	void InitUI();
	void UpdateUI();
	void InitData(tmt_ManualParas *pManualParas);

public:
	void ConnectAllSigSlot();
	void DisConnectAllSigSlot();

	QVBoxLayout *m_pMainVBoxLayout;
	QHBoxLayout *m_pFirstHBoxLayout;
	QHBoxLayout *m_pTestMethodHBoxLayout;
	QSttGroupBox *m_pTestMethodGroupBox;
	QRadioButton *m_pInterPolMethodRadio;
	QRadioButton *m_pSynchMethodRadio;

	QHBoxLayout *m_pPPS_SetHBoxLayout;
	QSttGroupBox *m_pPPS_SetGroupBox;
	QRadioButton *m_pRisingEdgeRadio;
	QRadioButton *m_pFallingEdgeRadio;
	QRadioButton *m_pNoPPSEdgeRadio;

	QCheckBox *m_pOutCheckBox[10];
	QHBoxLayout *m_pOutSetHBoxLayout;
	QSttGroupBox *m_pOutSetGroupBox;

	QHBoxLayout *m_pOtherSetHBoxLayout;
	QLabel *m_pUn_Label;
	QFloatLineEdit *m_pUn_FloatLineEdit;
	QLabel *m_pIn_Label;
	QFloatLineEdit *m_pIn_FloatLineEdit;
	QSttGroupBox *m_pOtherSetGroupBox;
	tmt_ManualParas *m_pManualParas;

	BOOL *m_pbTmtParaChanged;

signals:
	void sig_updataParas();

private slots:
	void slot_OnTestMethodRadioChanged(bool bValue);
	void slot_OnPPSSetRadioChanged(bool bValue);
	void slot_OnOutCheckChanged();
	void slot_OnUnEditChanged();
	void slot_OnInEditChanged();
};

extern CFont *g_pSttGlobalFont;

#endif // QSTTMUPARASWIDGET_H
