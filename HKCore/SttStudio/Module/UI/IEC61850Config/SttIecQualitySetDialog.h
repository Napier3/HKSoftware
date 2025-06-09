#ifndef STTIECQUALITYSETDIALOG_H
#define STTIECQUALITYSETDIALOG_H

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
#include <QCheckBox>
#include "../../../../61850/Module/CfgDataMngr/IecCfg92Ch.h"
#include "../Module/CommonCtrl_QT/QNumberCheckBox.h"
#include "../Module/CommonCtrl_QT/QIecLineEdit.h"


class QSttIecQualitySetDialog : public QDialog
{
	Q_OBJECT

public:
	QSttIecQualitySetDialog(CIecCfg92Ch *pIecCfgSmv92Ch,QWidget *parent= NULL);
	~QSttIecQualitySetDialog();

	virtual void SaveData();
	void SetIecQualitySetDialogFont();

private:
	void InitUI();
	void InitDatas();
	void ShowQuality();
	DWORD GetCurrQuality();

	CIecCfg92Ch *m_pIecCfgSmv92Ch;

	QLabel *m_pValid_Label;
	QComboBox *m_pValid_ComBox;
	QLabel *m_pOverFlow_Label;
	QComboBox *m_pOverFlow_ComBox;

	QLabel *m_pOutOfRange_Label;
	QComboBox *m_pOutOfRange_ComBox;
	QLabel *m_pBadRef_Label;
	QComboBox *m_pBadRef_ComBox;

	QLabel *m_pOscilatory_Label;
	QComboBox *m_pOscilatory_ComBox;
	QLabel *m_pFailure_Label;
	QComboBox *m_pFailure_ComBox;

	QLabel *m_pOldData_Label;
	QComboBox *m_pOldData_ComBox;
	QLabel *m_pInconsistent_Label;
	QComboBox *m_pInconsistent_ComBox;

	QLabel *m_pInaccureate_Label;
	QComboBox *m_pInaccureate_ComBox;
	QLabel *m_pSource_Label;
	QComboBox *m_pSource_ComBox;

	QLabel *m_pTest_Label;
	QComboBox *m_pTest_ComBox;
	QLabel *m_pOpb_Label;
	QComboBox *m_pOpb_ComBox;


	QVBoxLayout *m_pMain_VLayout;
	QGridLayout *m_pQualitySetGridLayout;
	QHBoxLayout *m_pOK_CancelHLayout;

	QNumberCheckBox   *m_pModifyAllChs_Check;
	QIecLineEdit   *m_pValue_LineEdit;
	QPushButton *m_pDirectSet_PushButton;
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;


public slots:
	void slot_EditValueClicked();
	void slot_DirectSetClicked();
	void slot_OKClicked();
	void slot_CancelClicked();
};

extern QFont *g_pSttGlobalFont;  

#endif // STTIECQUALITYSETDIALOG_H
