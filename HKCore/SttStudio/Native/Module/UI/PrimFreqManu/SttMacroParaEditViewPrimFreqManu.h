#ifndef SttMacroParaEditViewPrimFreqManual_H
#define SttMacroParaEditViewPrimFreqManual_H

#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "../Manual/SttMacroParaEditViewManualBase.h"
#include "../Module/CommonCtrl_QT/SttDiffCurrCalDlg.h"
#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QGroupBox>
#include "QPrimFreqManualWidget.h"

#include "../Controls/SttCheckBox.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Manual/ManualEstimateDlg.h"
#include "../Controls/SttGroupBox.h"
#include "../Module/SttTest/Common/PrimFreq/tmt_prim_freq_manu_test.h"

#define FILE_PRIMFREQMANUALTEST		"PrimFreqManualTest"
#define POSTFIX_PRIMFREQMANUALTEST    "pfmntxml"

class QSttMacroParaEditViewPrimFreqManual : public QSttMacroParaEditViewManualBase
{
    Q_OBJECT

public:

	tmt_PrimFreqManualTest m_oManualTest;
	QPrimFreqManualWidget *m_pManualTest_UI;
	QBoxLayout* m_pMainLayout;	
public:

public:
    explicit QSttMacroParaEditViewPrimFreqManual(QWidget *parent = 0);
    virtual ~QSttMacroParaEditViewPrimFreqManual();

private:
	void SendUpdateParameter();
	void InitBinaryInBinaryOutUI();
	void InitOtherParasUI();
	void SetManualOtherParasFont();
	void InitStyle();

public:
	//test funciton - need delete

	virtual void InitLanuage();
	virtual void CopyBinaryConfig(BOOL b=TRUE);
	virtual void InitBinStateOnStarting();
	virtual void InitConnect();
	void UinitConnect();
	virtual CSttTestResourceBase* CreateTestResource();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual bool PrepStartTest();//zhouhj 20230704 开始测试前的准备工作

	virtual void ClearResult(PTMT_PARAS_HEAD pHead);
	virtual void OnTestResults(CDataGroup *pResults);
	virtual void UpdateTestResource(BOOL bCreateChMaps);
//	virtual void UpdateRtSyncTime(CDataGroup *pRtSycTime);//20220920 zhouhj 更新对时、守时同步时间

	void UpdateManualParas(bool bUpdateParasData = TRUE);

	virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oManualTest;}
	virtual char* GetMacroID(){ return "ManualTest"; }

    virtual void InitParasView();
    virtual void InitIVView();
	void slot_SwitchStateChanged();

	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	virtual void ShowReport(CDvmValues *pValues);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);

	virtual BOOL SetValues_dsRcdStep6U6I(CDvmDataset *pDsRcdStep6U6I);

	void slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor = FALSE);

	virtual void UpdateAuxDCEdit();//20240613 suyang 新增用于更新L336D 状态序列 通用 辅助直流编辑框 
	virtual CString GetMacroTestResultUnit();

signals:
	void sig_updataParas();

private slots:
    void on_m_btnLock_clicked();
    void on_m_btnAdd_clicked();
    void on_m_btnMinus_clicked();
	void on_m_editIintVal_editingFinished();
	void on_m_editFinishVal_editingFinished();
	void on_m_editTime_editingFinished();
	void on_m_editUdc_editingFinished();
	void on_m_editStep_editingFinished();
	//void on_m_editDelayed_editingFinished();
	void on_m_cbAuto_clicked(int nIndex);
	void on_m_cbbSelect_currentIndexChanged(int index);
	void on_m_cbbChannel_currentIndexChanged(int index);
	void on_m_cbbChangeType_currentIndexChanged(int index);
	void on_m_cbOut1_clicked(int nIndex);
	void on_m_cbOut2_clicked(int nIndex);
	void on_m_cbOut3_clicked(int nIndex);
	void on_m_cbOut4_clicked(int nIndex);


	void on_m_editTimeChanged();
	void on_m_editStepChanged();
	void on_m_editInitValueChanged();
	void on_m_editFinishValueChanged();
	//void on_m_editDelayChanged();
	void slot_currentChangedTabWidget(int nCurrIndex);


    void on_m_btnInBinaryOutSet_clicked();

	void slot_GrpPulse_cliked();
	void slot_GrpDc_cliked();
	void slot_cbb_PulseType(int nIndex);
	void slot_cbb_PeakValue(int nIndex);
	void slot_cbb_DcChangeType(int nIndex);
	void slot_edt_PulseWidth();
	void slot_edt_PulseFreq();
	void slot_edt_DcChangeValue();
	void slot_edt_Dc1();
	void slot_edt_Dc2();
	void slot_btn_Mapping();

protected slots:
	void slot_updateParas();
	void slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);
};

extern QSttMacroParaEditViewPrimFreqManual* g_pPrimFreqManualTest;

#endif // SttMacroParaEditViewPrimFreqManual_H
