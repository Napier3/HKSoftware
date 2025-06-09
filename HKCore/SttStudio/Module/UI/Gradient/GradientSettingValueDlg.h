#ifndef GRADIENTSETTINGVALUEDLG_H
#define GRADIENTSETTINGVALUEDLG_H

#include "../../SttTest/Common/tmt_gradient_test.h"
#include <QDialog>
#include <QLineEdit>

class GradientSettingValueDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_GradientParasEx* m_pParas;
	QLineEdit* m_pUActEdit;
	QLineEdit* m_pIActEdit;
	QLineEdit* m_pMaxAngleSetEdit;
	QLineEdit* m_pRetCoefSetEdit;
	QLineEdit* m_pHzSetEdit;
	QLineEdit* m_pAngleFSetEdit;
	QLineEdit* m_pAngleSSetEdit;
	QLineEdit* m_pAngleSetEdit;

public:
	GradientSettingValueDlg(tmt_GradientParasEx* pParas, QWidget* parent = NULL);
	virtual ~GradientSettingValueDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};

#endif