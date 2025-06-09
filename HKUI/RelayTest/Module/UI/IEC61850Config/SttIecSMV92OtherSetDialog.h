#ifndef STTIECSMV92OTHERSETDIALOG_H
#define STTIECSMV92OTHERSETDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include "../../../../61850/Module/CfgDataMngr/IecCfgSmvRates.h"
#include "Grid/IecCfgSmvRateGrid.h"



class QSttIecSMV92OtherSetDialog : public QDialog
{
	Q_OBJECT

public:
	QSttIecSMV92OtherSetDialog(QWidget *parent= NULL);
	~QSttIecSMV92OtherSetDialog();

	virtual void InitData(CIecCfgSmvRates *pSmvRates);
	virtual void SaveData();

private:
	void InitUI();

	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pOK_CancelHLayout;

	CIecCfgSmvRateGrid *m_pSmvRateGrid;
	

	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	CIecCfgSmvRates *m_pSmvRates_Extern;
	CIecCfgSmvRates *m_pSmvRates_Inner;

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
};

#endif // STTIECSMV92OTHERSETDIALOG_H
