#ifndef QSTTMUTIMETESTWIDGET_H
#define QSTTMUTIMETESTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include <QTimer>
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../Module/DataMngr/DvmValues.h"
#include "../Controls/SttGroupBox.h"
class QSttMUTimeTestWidget : public QWidget
{
	Q_OBJECT

public:
	QSttMUTimeTestWidget(BOOL *pbTmtParaChanged,QWidget *parent);
	~QSttMUTimeTestWidget();

	void InitUI();
	void UpdateUI();
	void InitData(tmt_manual_test *pManualTest);
	virtual void ShowReport(CDvmValues *pValues);
	//2023.10.17 zhouhj 删除
//	void UpdateMUTimeAccurRlt_PPS(CDvmDataset *pTimeRltDataset);
	//zhouhj 2023.10.16 更换更新方案,删除此函数
//	void UpdateMUTimeAccurRlt_NOPPS(CDvmData *pSVDelayData);
	void UpdateMUTimeAccurRlt(CDataGroup *pRtSycTime);

	void TestStartInit();
	void TestStopInit();
	void ClearResults();

	void SetWinMuTestFont_1024_768();//20230724 suyang  用于在1024 X 768 分辨率下适用6.4 

private:
	void EnableEditCtrls(BOOL bEnable);
	void ConnectAllSigSlot();
	void DisConnectAllSigSlot();
	void UpdateResultsDesc();
	void SetRightPicLabel(const CString &strPicName);
	CString m_strRightPicName;

	QHBoxLayout *m_pMainHBoxLayout;
	QVBoxLayout *m_pLeftVBoxLayout;

	QVBoxLayout *m_pPPS_SetVBoxLayout;
	QHBoxLayout *m_pPPS_ChildHBoxLayout;
//	QHBoxLayout *m_pDelayComp_ChildHBoxLayout;

	//zhouhj 2023.10.13
// 	QLabel *m_pDelayComp_Label;
// 	QFloatLineEdit *m_pDelayComp_FloatLineEdit;

	QSttGroupBox *m_pPPS_SetGroupBox;
	QRadioButton *m_pRisingEdgeRadio;
	QRadioButton *m_pFallingEdgeRadio;
	QRadioButton *m_pNoPPSEdgeRadio;

	QCheckBox *m_pOutCheckBox[10];
	QGridLayout *m_pOutSetGridLayout;
	QSttGroupBox *m_pOutSetGroupBox;

	QLabel *m_pTimeLong_Label;
	QFloatLineEdit *m_pTimeLong_FloatLineEdit;
	QLabel *m_pCurrError_Label;
	QFloatLineEdit *m_pCurrError_FloatLineEdit;
	QLabel *m_pMaxError_Label;
	QFloatLineEdit *m_pMaxError_FloatLineEdit;
	QLabel *m_pMinError_Label;
	QFloatLineEdit *m_pMinError_FloatLineEdit;
	QGridLayout *m_pTestResultsGridLayout;
	QSttGroupBox *m_pTestResultsGroupBox;

	QLabel *m_pRightPic_Label;
	QLabel *m_pStdSting_Label;

	tmt_manual_test *m_pManualTest;
	tmt_ManualParas *m_pManualParas;
	tmt_MuTimeResult *m_pMuTimeRlt;
	BOOL *m_pbTmtParaChanged;
	QTimer m_oAssistTimer;//助手提示定时器
	QTimer m_oResultUpdateTimer;//测试结果更新定时器

signals:
	void sig_updataParas();

private slots:
	void slot_OnPPSSetRadioChanged(bool bValue);
	void slot_OnOutCheckChanged();
	void slot_OnDelayCompEditChanged();
	void slot_AssistTimer();
	void slot_ResultUpdateTimer();
	
};

extern CFont *g_pSttGlobalFont;  

#endif // QSTTMUTIMETESTWIDGET_H
