#ifndef STTSYSPARASOTHERSETDIALOG_H
#define STTSYSPARASOTHERSETDIALOG_H

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
#include "../../../../61850/Module/CfgDataMngr/IecCfgSysParas.h"

#define STT_IEC_SYSPARAS_LC_FIBER_NUM                                        1
#define STT_IEC_SYSPARAS_ST_FIBER_NUM                                        2



class QSttIecSysParasOtherSetDialog : public QDialog
{
	Q_OBJECT

public:
	QSttIecSysParasOtherSetDialog(QWidget *parent= NULL);
	~QSttIecSysParasOtherSetDialog();

	virtual void InitData(CIecCfgFiberParas *pFiberParas);
	virtual void SaveData();

private:
	void InitUI();

//	QHBoxLayout *m_pMain_HLayout;
	QVBoxLayout *m_pMain_VLayout;
//	QHBoxLayout *m_pBCode1588HBoxLayout;
	QHBoxLayout *m_pLCFibersHLayout;
	QHBoxLayout *m_pSTFibersHLayout;
	QHBoxLayout *m_pOK_CancelHLayout;

//	QScrollArea *m_pMain_ScrollArea;
//	QWidget *m_pScrollArea_Widget;

//	QGroupBox *m_pBCode1588GroupBox;
	QGroupBox *m_pLCFibersGroupBox;
	QGroupBox *m_pSTFibersGroupBox;
	
	struct SttIecRadioGroup_Struct
	{
		QGroupBox    *pRadioGroupBox;
		QRadioButton *pFirstRadio;
		QRadioButton *pSecondRadio;
		QVBoxLayout *pVBoxLayout;
	};

// 	SttIecRadioGroup_Struct m_oBCodeRadioGroup;
// 	SttIecRadioGroup_Struct m_oIEC1588RadioGroup;
	SttIecRadioGroup_Struct	m_oLCFiberRadioGroup[STT_IEC_SYSPARAS_LC_FIBER_NUM];
	SttIecRadioGroup_Struct m_oSTFiberGroup[STT_IEC_SYSPARAS_ST_FIBER_NUM];

	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	CIecCfgFiberParas *m_pFiberParas;

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
};

#endif // STTSYSPARASOTHERSETDIALOG_H
