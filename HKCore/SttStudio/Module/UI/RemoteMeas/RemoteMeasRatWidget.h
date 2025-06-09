#ifndef REMOTEMEASRATWIDGET_H
#define REMOTEMEASRATWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../Controls/SttLineEdit.h"

#include "../../Module/SttTest/Common/tmt_manu_test.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../../../../Module/BaseClass/QT/ExBaseListComboBox.h"
#include "RemoteMeasParaset.h"


class QRemoteMeasRatWidget : public QWidget
{
	Q_OBJECT

public:
	QRemoteMeasRatWidget(QWidget *parent = 0);
	virtual ~QRemoteMeasRatWidget();
   
	tmt_ManualParas* m_pManualParas;
	CExBaseList m_oAinInterDatasRef;            //间隔数据索引

	void DeleteAinInterDatas();//删除间隔遥测数据

	void setData(tmt_ManualParas* pManualParas);

	void initUI();
	void initBaseData();
	void initInterSelectData();

	void startInit();
	void stopInit(BOOL bHasPasteState);

//	void UpdateStateCombox();
	void SetFont();

	float m_fPrimVolValue;//一次电压
	float m_fSecondVolValue;//二次电压
	float m_fPrimCurValue;//一次电流
	float m_fSecondCurValue;//二次电流
	float m_fPrimVZeroValue;//一次零序电压
	float m_fSecondVZeroValue;//二次零序电压
	float m_fPrimCZeroValue;//一次零序电流
	float m_fSecondCZeroValue;//二次零序电流

public:
	QLabel* m_pSelect;
	CExBaseListComboBox *m_pSelect_ComboBox;
	QLabel* m_pVoltRatio_Label;
	QSttLineEdit *m_pVolt1_LineEdit;
	QLabel* m_pLabel1;
	QSttLineEdit *m_pVolt2_LineEdit;
	QLabel* m_pCurrRatio_Label;
	QSttLineEdit *m_pCurr1_LineEdit;
	QLabel* m_pLabel2;
	QSttLineEdit *m_pCurr2_LineEdit;
	QLabel* m_pZeroVoltRatio_Label;
	QSttLineEdit *m_pZeroVolt1_LineEdit;
	QLabel* m_pLabel3;
	QSttLineEdit *m_pZeroVolt2_LineEdit;
	QLabel* m_pZeroCurrRatio_Label;
	QSttLineEdit *m_pZeroCurr1_LineEdit;
	QLabel* m_pLabel4;
	QSttLineEdit *m_pZeroCurr2_LineEdit;

	RemoteMeasParaSet* m_pUIParaWidget;		
	QVBoxLayout *m_pVLayout; 

public:
	void slot_lne_Volt1Changed();
	void slot_lne_Volt2Changed();
	void slot_lne_Curr1Changed();
	void slot_lne_Curr2Changed();
	void slot_lne_ZeroVolt1Changed();
	void slot_lne_ZeroVolt2Changed();
	void slot_lne_ZeroCurr1Changed();
	void slot_lne_ZeroCurr2Changed();
};
extern QFont *g_pSttGlobalFont;  

#endif // REMOTEMEASRATWIDGET_H
