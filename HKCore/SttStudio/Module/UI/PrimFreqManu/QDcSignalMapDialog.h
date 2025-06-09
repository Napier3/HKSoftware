#ifndef QDcSignalMapDialog_H
#define QDcSignalMapDialog_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "../../SttTest/Common/PrimFreq/tmt_prim_freq_manu_test.h"
#include "../Controls/SttGroupBox.h"
#include <QLabel>
#include <QVBoxLayout>
#include "../Controls/SttLineEdit.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

class QDcSignalMapDialog : public QDialog
{
	Q_OBJECT
private:
	tmt_PrimFreqManualParas m_oInterParas;
	tmt_prim_freq_manual_paras *m_pExternalParas;  // 外部参数

	QSttGroupBox *m_pHzGrp;
	QSttGroupBox *m_pPulseGrp;
	QSttLineEdit *m_pMinHzEdt;
	QSttLineEdit *m_pMaxHzEdt;
	QSttLineEdit *m_pMinPulseEdt;
	QSttLineEdit *m_pMaxPulseEdt;

	QSttLineEdit* m_pArryRangeEdit[4];
	QLabel* m_pArryRangeMap[2];
	QLabel* m_pArryLbUnit[4];
	QLabel* m_pArryLbDcUnit[4];

	QVBoxLayout *m_pVMainLayout;
	QHBoxLayout *m_phLayout[2];
	QGridLayout *m_pGridLayout[2];


public:
	QDcSignalMapDialog(tmt_PrimFreqManualParas* pParas, QWidget* parent = NULL);
	 ~QDcSignalMapDialog();

public:
	void InitUI();
	void InitData();
	void InitConnect();

	int m_nParaSetSecondValue;

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	
	void slot_MinHzEdtFinished();
	void slot_MaxHzEdtFinished();
	void slot_MinPulseEdtFinished();
	void slot_MaxPulseEdtFinished();

};

#endif


