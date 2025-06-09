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
	//Ĭ������
	QSttCheckableGroupBox *m_pDefaultGroupBox;
	QSttLineEdit *m_pRowLineEdit;//���� 
	QSttLineEdit *m_pHoldTimeLineEdit;//����ʱ��
	QSttLineEdit *m_pFreqLineEdit;//Ƶ��
	QSttLineEdit *m_pDcCurrentLineEdit;//ֱ������

	// Ƶ�ʵݱ�
	QSttCheckableGroupBox *m_pFreqChangeGroupBox;
	QSttLineEdit *m_pStartFreqEdit;//��ֵ 
	QSttLineEdit *m_pEndFreqEdit;//��ֵ 
	QSttLineEdit *m_pStepFreqEdit;//����
	QRadioButton *m_ChangeFreqRadio[2];//0=ʼ�� 1=ʼ��ʼ
	QSttLineEdit *m_pHoldTimeFreqLineEdit;//����ʱ��
	
	// ֱ�������ݱ�
	QSttCheckableGroupBox *m_pCurrentChangeGroupBox;
	QSttLineEdit *m_pStartCurrentEdit;//��ֵ 
	QSttLineEdit *m_pEndCurrentEdit;//��ֵ 
	QSttLineEdit *m_pStepCurrentEdit;//����
	QRadioButton *m_ChangeCurrentRadio[2];//0=ʼ�� 1=ʼ��ʼ
	QSttLineEdit *m_pHoldTimeCurrentLineEdit;//����ʱ��

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
