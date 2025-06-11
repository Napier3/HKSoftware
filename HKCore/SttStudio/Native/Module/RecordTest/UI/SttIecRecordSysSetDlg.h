#ifndef STTIECRECORDSYSSETDLG_H
#define STTIECRECORDSYSSETDLG_H

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include "../../UI/Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../../../../Module/SmartCap/X61850CapBase.h"
#include "../../UI/IEC61850Config/Grid/IecCfgPrimRateGrid.h"


class QSttIecRecordSysSetDlg : public QDialog
{
	Q_OBJECT

public:
	QSttIecRecordSysSetDlg(QWidget *parent= NULL);
	virtual ~QSttIecRecordSysSetDlg();

	virtual void SaveData();
	void InitData(CCapAnalysisConfig *pCapAnalysisConfig,CIecCfgPrimRatesIn *pIecCfgPrimRatesIn);

private:
	void InitUI();
	CIecCfgPrimRatesIn *m_pIecCfgPrimRatesIn;
	CExBaseList m_oLeftList;
	CExBaseList m_oRightList;

	CCapAnalysisConfig *m_pSttCapAnalysisConfig;
	CIecCfgPrimRateGrid *m_pLeft_PrimRateGrid;
	CIecCfgPrimRateGrid *m_pRight_PrimRateGrid;
	QHBoxLayout *m_pPT_CT_RatesHLayout;
	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pRadioHLayout;
//	QHBoxLayout *m_pOK_CancelHLayout;

	QRadioButton *m_pPrimaryValueRadioBtn;
	QRadioButton *m_pSecondValueRadioBtn;

	QPushButton *m_pOK_PushButton;
//	QPushButton *m_pCancel_PushButton;

public slots:
//	void slot_lne_Clicked();
	void slot_OKClicked();
	void slot_CancelClicked();
};

extern QFont *g_pSttGlobalFont;
#endif // STTIECRECORDSYSSETDLG_H
