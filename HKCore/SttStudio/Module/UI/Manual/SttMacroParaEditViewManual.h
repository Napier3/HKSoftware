#ifndef STTMACROPARAEDITVIEWMANUAL_H
#define STTMACROPARAEDITVIEWMANUAL_H

#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "QSttMUParasWidget.h"
#include "QSttMUTimeTestWidget.h"

//#include "../../Module/SttTest/Common/tmt_state_test.h"

#include "QSttManualBinBoutDlg.h"
#include "../Module/CommonCtrl_QT/SttDiffCurrCalDlg.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QGroupBox>

#include "../Controls/SttCheckBox.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "ManualEstimateDlg.h"
#include "../Controls/SttGroupBox.h"
#include "SttMacroParaEditViewManualBase.h"

namespace Ui {
class QSttMacroParaEditViewManual;
}

#define FILE_MANUTEST		"ManualTest"
#define POSTFIX_MANUTEST    "mntxml"

class QSttMacroParaEditViewManual : public QSttMacroParaEditViewManualBase
{
    Q_OBJECT

public:
    Ui::QSttMacroParaEditViewManual *m_pManualTest_UI;

	//���ֳ�Ա��������QSttMacroParaEditViewManualBase
// 	QManualView_Paras m_oParas;
// 	QManualView_IV m_oIV;
// 	QSttMUParasWidget *m_pSttMUParasWidget;
	QSttMUTimeTestWidget *m_pSttMUTimeTestWidget;

	//tmt_StatePara* m_pStatePara;  //2022-12-30 wjs
//	QDiffCalcDlg* m_pDiffCalcDlg;

	ShortCalcuPara m_ShortCalcuPara; 
	tmt_manual_test m_oManualTest;
// 	tmt_ManualParas *m_pManualParas;
	Stt_DiffCurrCalParas m_oDiffCurrCalParas;

// 	bool m_bIsChanging;//�ж�+��-��ť����ɵĸ����Ƿ��Ѿ����,δ���ʱ����������һ��SetItemPara

	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;
// 	CString m_strCbbChannel;//ͨ��ѡ��

	ExSwitchSet* m_pExBinParaWidget;		//��չ��������
	ExSwitchSet* m_pExBoutParaWidget;		//��չ��������

public:

	QGridLayout *m_pMainVBoxLayout;

	QGridLayout* m_pGridLayoutLeft;
	QSttGroupBox *m_pManualGroupBox;

	QSttCheckBox *m_pHarm_CheckBox;
	QScrollComboBox *m_pHarm_ComboBox;
	QLabel *m_pTestMethod_Label;
	QScrollComboBox *m_pTestMethod_ComboBox;

	QLabel *m_pMeasType_Label;
	QScrollComboBox *m_pMeasType_ComboBox;

	QLabel *m_pBCode_Label;
	QScrollComboBox *m_pBCode_ComboBox;
	QSttGroupBox *m_pOutSetGroupBox;
	QCheckBox *m_pOutCheckBox[10];
	QGridLayout *m_pOutSetGridLayout;

	QSttGroupBox *m_pTestGroupBox;

	QSttCheckBox *m_pSetMUTestRpt_CheckBox;//���úϲ���Ԫ���Ա�����Դ�����ÿ��ʹ��ʱ��
	QSttLineEdit *m_pMUAccuracyTestNum_Edit;
	QLabel *m_pMUTestNumUnit_Label;
	QSttLineEdit *m_pMUTestTime_Edit;
	QLabel *m_pMUTestTimeUnit_Label;

	QPushButton *m_pRefresh_Button;//ˢ��
	
	int m_nBCodeMode,m_nIecFormatMeas; //2023-5-31 suyang ����ϵͳ������ϲ���ԪB�롢���������ж�



public:
    explicit QSttMacroParaEditViewManual(QWidget *parent = 0);
    virtual ~QSttMacroParaEditViewManual();

private:
	void SendUpdateParameter();
	void InitBinaryInBinaryOutUI();
	void InitOtherParasUI();
	void SetManualOtherParasFont();
	void InitStyle();
	void VisibleCtrlsByFuncType();//���ݹ���������ʾ��������

	// 2023-06-1 suyang �ϲ���Ԫ
	void InitMuUI();
	void InitMuComboBoxItem();

	void UpdateMUAccurData();
	void UpdateMURptUI();

	void SetWinMuTestFont_1024_768();//20230724 ����1024 X768 �ֱ���

public:
	//test funciton - need delete

	virtual void InitLanuage();
	virtual void CopyBinaryConfig(BOOL b=TRUE);
	virtual void InitBinStateOnStarting();
	virtual void InitConnect();
	virtual CSttTestResourceBase* CreateTestResource();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual bool PrepStartTest();//zhouhj 20230704 ��ʼ����ǰ��׼������

	virtual void ClearResult(PTMT_PARAS_HEAD pHead);
	virtual void OnTestResults(CDataGroup *pResults);
	virtual void UpdateTestResource(BOOL bCreateChMaps);
//	virtual void UpdateRtSyncTime(CDataGroup *pRtSycTime);//20220920 zhouhj ���¶�ʱ����ʱͬ��ʱ��

	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	virtual void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	virtual void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);

	virtual void UpdateBinBoutExTab();//���¿�������չ����
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

	virtual void UpdateAuxDCEdit();//20240613 suyang �������ڸ���L336D ״̬���� ͨ�� ����ֱ���༭�� 
	virtual BOOL IsUseSecondParaSet();
	virtual void UpdatePrimParaSetUI();//20240918 suyang ���½���һ��/����ֵ��λ��ʾ
	virtual void SetPlotAcDcMaxMinValue();	
	virtual CString GetMacroTestResultUnit();
	virtual void UpdateDCParasByCurrModulePower(BOOL bCurrModulePowerHigh);

	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void EnableGooseParaWidget(bool b);
	bool ExistGooseParaWidget();

	//chenling20230516
	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget(); 
	void EnableFT3OutParaWidget(bool b);
	bool ExistFT3OutParaWidget();

	void UpdateHarmCheckComboxUI(BOOL bClearItems);
	void UpdateDCCheckBoxUI(BOOL bCurrModulePowerHigh = FALSE);

	void AddExBinParaWidget();
	void RemoveExBinParaWidget();
	void AddExBoutParaWidget();
	void RemoveExBoutParaWidget();
	void EnableBinParaWidget(bool b);
	void EnableBoutParaWidget(bool b);
	bool ExistExBinParaWidget();
	bool ExistExBoutParaWidget();
	//2023.10.17 zhouhj ɾ��
//	void UpdateMUTimeAccurRlt_PPS();
//	void UpdateMUTimeAccurRlt_PPS(CDvmDataset *pTimeRltDataset);
	//zhouhj 2023.10.16 �������·���,ɾ���˺���
//	void UpdateMUTimeAccurRlt_NOPPS(CDvmData *pSVDelayData);
//	void EnableSubParaWidget(bool bEnable);

signals:
	void sig_updataParas();
	//2023.10.17 zhouhj ɾ��
//	void sig_UpdateMUTimeAccurRlt_PPS();

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
	void on_m_cbOld_clicked();
	void on_m_cbAuto_clicked();
	void on_m_cbDC_clicked();
	void on_m_cbbSelect_currentIndexChanged(int index);
	void on_m_cbbChannel_currentIndexChanged(int index);
	void on_m_cbbChangeType_currentIndexChanged(int index);
	void on_m_cbOut1_clicked();
	void on_m_cbOut2_clicked();
	void on_m_cbOut3_clicked();
	void on_m_cbOut4_clicked();
	/*void on_m_cbOut5_clicked();
	void on_m_cbOut6_clicked();
	void on_m_cbOut7_clicked();
	void on_m_cbOut8_clicked();
	void on_m_cbOut9_clicked();
	void on_m_cbOut10_clicked();
	void on_m_cbInA_clicked();
	void on_m_cbInB_clicked();
	void on_m_cbInC_clicked();
	void on_m_cbInD_clicked();
	void on_m_cbInE_clicked();
	void on_m_cbInF_clicked();
	void on_m_cbInG_clicked();
	void on_m_cbInH_clicked();
	void on_m_cbInI_clicked();
	void on_m_cbInJ_clicked();
	void on_m_rdAnd_clicked();
	void on_m_rdOr_clicked();*/

	void on_m_editTimeChanged();
	void on_m_editStepChanged();
	void on_m_editInitValueChanged();
	void on_m_editFinishValueChanged();
	//void on_m_editDelayChanged();
	void slot_HarmCheck_stateChanged(int nState);
	void slot_cmbHarm_SelChanged(int nCurrIndex);
	void slot_currentChangedTabWidget(int nCurrIndex);

	void on_m_btnShortCalcu_clicked();

    void on_m_btnInBinaryOutSet_clicked();
//
    void on_m_btnDiffCalc_clicked();
	void slot_Estimate();

	virtual void slot_ShortCalcuOk(ShortCalcuPara &para);

private slots:
	void slot_cbbTestMethod_currentIndexChanged(int index);
	void slot_cbbMeasType_currentIndexChanged(int index);
	void slot_cbbBCode_currentIndexChanged(int index);

	void slot_editTestNumChanged();
	void slot_editTestTimeChanged();
	void slot_editTestNumFinished();
	void slot_editTestTimeFinished();

	void slot_OnTestCheckChanged();
	void slot_RefreshClicked();
	void slot_OnOutCheckChanged();

// 	void slot_UpdateUdcEditEnabled();

protected slots:
	void slot_updateParas();
	void slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);
	void slot_GooseDataChanged();
	//2023.10.17 zhouhj ɾ��
//	void slot_UpdateMUTimeAccurRlt_PPS();
    void slot_FT3DataChanged(); 
	 void slot_BinBoutStateChanged();
};

extern QSttMacroParaEditViewManual* g_pManualTest;

#endif // STTMACROPARAEDITVIEWMANUAL_H
