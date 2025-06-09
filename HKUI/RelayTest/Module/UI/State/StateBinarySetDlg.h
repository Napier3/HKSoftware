#ifndef _QStateBinarySetDlg_H
#define _QStateBinarySetDlg_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QStringList>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../../Module/SttTest/Common/tmt_state_test.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Controls/SttGroupBox.h"

class QStateBinarySetDlg: public QDialog
{
	Q_OBJECT

public:
	QStateBinarySetDlg(QWidget *parent = 0);
	~QStateBinarySetDlg();

	tmt_StatePara* m_pStatePara;
	void setData(tmt_StatePara* pStatePara);

	void initUI();
	void initConnections();

	void UpdateData();
	void UpdateInput();
	void UpdateOutPut();
	void SetBinaryInEnable(bool bFlag);

	void startInit();
	void stopInit();


	long CalculateBin();//开入量选中计算
	void SetStateParaFont();//设置字体大小

private:
	BOOL *m_pbTmtParaChanged;

public:
	QSttGroupBox* m_pBinBox;//开入量
	QSttGroupBox* m_pBoutBox;//开出量

	//QLabel* m_pTrigerHoldTime;//触发后保持时间:
	QLabel* m_pOutputHoldTime;//保持时间:
	
	//QSttLineEdit* m_pTrigerHoldTimeEdit;
	QSttLineEdit* m_pOutputHoldTimeEdit;

// 	QCheckBox* m_pBin_A;
// 	QCheckBox* m_pBin_B;
// 	QCheckBox* m_pBin_C;
// 	QCheckBox* m_pBin_D;
	QCheckBox* m_pBin_E;
	QCheckBox* m_pBin_F;
	QCheckBox* m_pBin_G;
	QCheckBox* m_pBin_H;
	QCheckBox* m_pBin_I;
	QCheckBox* m_pBin_J;

	QRadioButton* m_pLogicOr;
	QRadioButton* m_pLogicAnd;

	QCheckBox* m_pBout_5;
	QCheckBox* m_pBout_6;
	QCheckBox* m_pBout_7;
	QCheckBox* m_pBout_8;
	QCheckBox* m_pBout_9;
	QCheckBox* m_pBout_10;
	QCheckBox* m_pChk_HoldTime;

	QPushButton *m_pbn_Ok;
	QPushButton *m_pbn_Cancel;

protected slots:
	void slot_OkClicked();
	void slot_CancelClicked();

	//void slot_lne_TrigerHoldTimeChangedKeyBoard();
	void slot_lne_OutPutHoldTimeChangedKeyBoard();

	//void slot_lne_TrigerHoldTimeChanged();
	void slot_lne_OutPutHoldTimeChanged();
	void slot_chb_OutPutHoldTimeStateChanged(int);
};

extern CFont *g_pSttGlobalFont;  

#endif // _QStateBinarySetDlg_H
