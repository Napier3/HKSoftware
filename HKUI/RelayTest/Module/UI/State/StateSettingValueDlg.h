#ifndef STATESETTINGVALUEDLG_H
#define STATESETTINGVALUEDLG_H

#include "../../SttTest/Common/tmt_state_test.h"
#include <QDialog>
#include <QLineEdit>

class StateSettingValueDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_StateParas* m_pParas;
	QLineEdit* m_pEdit;

public:
	StateSettingValueDlg(tmt_StateParas* pParas, QWidget* parent = NULL);
	virtual ~StateSettingValueDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};

#endif