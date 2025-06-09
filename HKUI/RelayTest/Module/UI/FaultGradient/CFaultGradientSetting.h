#ifndef CFAULTGRADIENTSETTING_H
#define CFAULTGRADIENTSETTING_H

#include <QDialog>
#include "ui_CFaultGradientSetting.h"
#include "../../SttTest/Common/Gradient/tmt_fault_gradient_test.h"

namespace Ui {
	class CFaultGradientSetting;
}


class CFaultGradientSetting : public QDialog
{
	Q_OBJECT

public:
	CFaultGradientSetting(tmt_fault_gradient_test *pFGParas, QWidget *parent = 0);
	~CFaultGradientSetting();


	void InitLanguage();
	void SetUIFont(QWidget* pWidget);
	void SetStyleValue(QGroupBox* pGroup,int nVFlag = -1);
public slots:
	void on_GrpOutNormal_ButtonClick(QAbstractButton * pCurrBtn);
	void on_GrpOutError_ButtonClick(QAbstractButton * pCurrBtn);
	void on_OkButtonClick();
	void on_CancelButtonClick();

public:
	tmt_BinaryOut m_binOutTemp[2][MAX_BINARYOUT_COUNT];
private:
	tmt_fault_gradient_test*	 m_pFGParas;
	
private:
	Ui::CFaultGradientSetting*  ui;
};

#endif // CFAULTGRADIENTSETTING_H
