#ifndef QSTTIECSMVFT3DCOTHERSETDIALOG_H
#define QSTTIECSMVFT3DCOTHERSETDIALOG_H

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

class  QSttIecSMVFT3DCOtherSetDialog : public QDialog
{
	Q_OBJECT

public:

	QSttIecSMVFT3DCOtherSetDialog(QWidget *parent= NULL);
	~QSttIecSMVFT3DCOtherSetDialog();

	virtual void InitData(CIecCfgSmvRates *pSmvRates);
	virtual void SaveData();

private:
	void InitUI();

	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pOK_CancelHLayout;
	QTabWidget *m_pDcAcTabWidget;
	QVBoxLayout *m_pDcVBoxLayout;
	QVBoxLayout *m_pAcVBoxLayout;
	QWidget *m_pDcWidget;
	QWidget *m_pAcWidget;

	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	CIecCfgSmvRates *m_pSmvRates_Extern;
	CIecCfgSmvRates *m_pSmvRates_Inner;


public:
	CIecCfgSMVFT3DCOtherSetGrid *m_pIecCfgSMVFT3DCVolGrid; 
	CIecCfgSMVFT3DCOtherSetGrid *m_pIecCfgSMVFT3DCCurGrid; 
	CIecCfgSMVFT3DCOtherSetGrid *m_pIecCfgSMVFT3ACVolGrid; 
	CIecCfgSMVFT3DCOtherSetGrid *m_pIecCfgSMVFT3AcCurGrid;

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();

};

#endif //QSTTIECSMVFT3DCOTHERSETDIALOG_H
