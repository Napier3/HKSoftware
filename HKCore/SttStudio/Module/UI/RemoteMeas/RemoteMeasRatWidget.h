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
	CExBaseList m_oAinInterDatasRef;            //�����������

	void DeleteAinInterDatas();//ɾ�����ң������

	void setData(tmt_ManualParas* pManualParas);

	void initUI();
	void initBaseData();
	void initInterSelectData();

	void startInit();
	void stopInit(BOOL bHasPasteState);

//	void UpdateStateCombox();
	void SetFont();

	float m_fPrimVolValue;//һ�ε�ѹ
	float m_fSecondVolValue;//���ε�ѹ
	float m_fPrimCurValue;//һ�ε���
	float m_fSecondCurValue;//���ε���
	float m_fPrimVZeroValue;//һ�������ѹ
	float m_fSecondVZeroValue;//���������ѹ
	float m_fPrimCZeroValue;//һ���������
	float m_fSecondCZeroValue;//�����������

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
