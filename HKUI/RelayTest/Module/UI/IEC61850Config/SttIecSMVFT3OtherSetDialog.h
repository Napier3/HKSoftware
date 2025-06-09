#ifndef STTIECSMVFT3OTHERSETDIALOG_H
#define STTIECSMVFT3OTHERSETDIALOG_H

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
#include "Grid/IecCfgSMVFT3DCOtherSetGrid.h"


class QSttIecSMVFT3OtherSetDialog : public QDialog
{
	Q_OBJECT

public:
	QSttIecSMVFT3OtherSetDialog(BOOL bIsFT3In,QWidget *parent= NULL);
	~QSttIecSMVFT3OtherSetDialog();

	virtual void InitData(CIecCfgSmvRates *pSmvRates);
	virtual void SaveData();

private:
	void InitUI();

	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pOK_CancelHLayout;

	CIecCfgSMVFT3DCOtherSetGrid *m_pIecCfgSMVFT3VolGrid; 
	CIecCfgSMVFT3DCOtherSetGrid *m_pIecCfgSMVFT3CurGrid;


	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	CIecCfgSmvRates *m_pSmvRates_Extern;
	CIecCfgSmvRates *m_pSmvRates_Inner;
	BOOL m_bIsFT3In;

	public slots:
		void slot_OKClicked();
		void slot_CancelClicked();
};

#endif // STTIECSMVFT3OTHERSETDIALOG_H
