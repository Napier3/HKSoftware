#ifndef QFreqNewFileDialog_H
#define QFreqNewFileDialog_H

#include <QDialog>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include "../Controls/SttLineEdit.h"
#include "../Controls/SttCheckableGroupBox.h"
#include "../../SttTest/Common/Distribution/tmt_freqoutput_test.h"

class QFreqNewFileDialog : public QDialog
{
	Q_OBJECT

public:
	QFreqNewFileDialog(tmt_FreqOutputParas *pFreqOutputParas,QWidget* parent = NULL);
	~QFreqNewFileDialog();

public:
	void InitUI();
	void InitConnect();
	void InitData();

private:
	//默认设置
	QSttCheckableGroupBox *m_pDefaultGroupBox;
	QSttLineEdit *m_pRowLineEdit;//行数 
	QSttLineEdit *m_pHoldTimeLineEdit;//持续时间
	QSttLineEdit *m_pFreqLineEdit;//频率
	QSttLineEdit *m_pDcCurrentLineEdit;//直流电流

	// 频率递变
	QSttCheckableGroupBox *m_pFreqChangeGroupBox;
	QSttLineEdit *m_pStartFreqEdit;//起值 
	QSttLineEdit *m_pEndFreqEdit;//终值 
	QSttLineEdit *m_pStepFreqEdit;//步长
	QRadioButton *m_ChangeFreqRadio[2];//0=始终 1=始终始
	QSttLineEdit *m_pHoldTimeFreqLineEdit;//持续时间
	
	// 直流电流递变
	QSttCheckableGroupBox *m_pCurrentChangeGroupBox;
	QSttLineEdit *m_pStartCurrentEdit;//起值 
	QSttLineEdit *m_pEndCurrentEdit;//终值 
	QSttLineEdit *m_pStepCurrentEdit;//步长
	QRadioButton *m_ChangeCurrentRadio[2];//0=始终 1=始终始
	QSttLineEdit *m_pHoldTimeCurrentLineEdit;//持续时间

	tmt_FreqOutputParas *m_pFreqOutputParas;
	tmt_FreqOutputNewFile *m_FreqOutputNewFile;

signals:
	void sig_UpdateTable();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_GroupBoxtoggled(bool bValue);
	void slot_RowEditFinished();
	void slot_LineEditFinished();
	void slot_RadioChanged(bool bValue);

};
#endif
