#ifndef STTMACROPARAEDITVIEWGRIDENT_H
#define STTMACROPARAEDITVIEWGRIDENT_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include <QWidget>
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "GradientGroupWidget.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"

#include "../Controls/SttLineEdit.h"
#include "../Controls/SettingCtrls/QSettingLineEdit.h"
#include "../Controls/SettingCtrls/settingselectdlg.h"

#define STT_RSLTEXPR_MACROID_COMMON _T("Common")

#define STT_GRADIENT_CHANNEL_TYPE_G1_CURR    0
#define STT_GRADIENT_CHANNEL_TYPE_G2_CURR    1
#define STT_GRADIENT_CHANNEL_TYPE_G1_VOLT    2
#define STT_GRADIENT_CHANNEL_TYPE_G2_VOLT    3
#define STT_GRADIENT_CHANNEL_TYPE_ALL_CURR   4
#define STT_GRADIENT_CHANNEL_TYPE_ALL_VOLT   5
#define STT_GRADIENT_CHANNEL_TYPE_ALL_FREQ   6

#define FILE_GRADIENT		"Gradient"
#define POSTFIX_GRADIENT    "grtxml"

namespace Ui {
class QSttMacroParaEditViewGradient;
}

class QSttMacroParaEditViewGradient : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	Ui::QSttMacroParaEditViewGradient *ui;

	explicit QSttMacroParaEditViewGradient(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewGradient();
	//tmt_GradientParasEx *m_pGradientParas;

	tmt_GradientTestEx* m_pCurTest;
	tmt_GradientParasEx* m_pCurPara;
	tmt_GradientResult* m_pCurResult;

	CDataType m_oGradientChs;
	QStringList m_ChangeTypeList;
	QStringList m_ChangeTypeList2;
	QStringList m_listTestMode2;//两种测试模式选择
	QStringList m_listTestMode3;//三种测试模式选择

	QString  m_strUnit[32];

	QGradientGroupWidget* m_pGroupWidget;
	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;

private:
	CString m_strVoltage;
	CString m_strCurrent;
	CString m_strFreq;

	CDataTypeValue *m_pDataTypeValue1;
	CDataTypeValue *m_pDataTypeValue2;

	CString GetCurChannal(PTMT_PARAS_HEAD pParas);

	void SetGradientFont();
	void SetDefaultFaultValue(long nChIndex);

public:
	virtual void InitLanuage();

	void InitUI();
	void InitParas();
	void InitConnections();
	void updateLabName();
	void initQList();
	void CopyBinaryConfig(BOOL b=TRUE);
	void InitGradientChannel(para_type vartype ,int GradientcbbVar = 1);
	void UpdateGradientChs();
    void UpdateGradientChs2();
	void InitUI_AfterGridentSel();
	void InitUI_AfterGridentSel2();
	void UpdateG1G2();
	void EnableRadientType();
	void getYRange(float ftime,float fv,float v1,float v2,float fstart,float fend,float &down,float &up);
	long GetSttGradientChannelType(long nChannel);
	CSttTestResourceBase* CreateTestResource();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);

	virtual PTMT_PARAS_HEAD GetTestParas() { return m_pCurTest;}
	virtual char* GetMacroID(){ return "GradientTest"; }

	virtual PTMT_PARAS_HEAD CreateTestParas(const char * pszMacroID);
	virtual PTMT_PARAS_HEAD CreateTestParas(PTMT_PARAS_HEAD pCurr);
	void SetData(PTMT_PARAS_HEAD pCurr);

	//void UpdateResult(float fTripValue, float fReturnValue, float fReturnCoef);

	virtual void ShowReport(CDvmValues *pValues);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);

	virtual void startInit();
	virtual void stopInit();
	void InitEnableButtons();

	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);

	void slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor = FALSE);

	virtual void UpdateTestResource(BOOL bCreateChMaps);
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);
	virtual void UpdateBinBoutExTab();//更新开关量扩展界面

	void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void EnableGooseParaWidget(bool b);
	bool ExistGooseParaWidget();
	void InitMannualparas();

	void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget(); 
	void EnableFT3OutParaWidget(bool b);
	bool ExistFT3OutParaWidget();
	
//	void EnableSubParaWidget(bool bEnable);  //20220815 zhouhj 未用到,注释掉
	void AddUnGradientSettingWidget();
    void RemoveUnGradientSettingWidget();
	void InitStyle();	

	virtual void InitBinaryInBinaryOutUI();//add wangtao 20241010 新增虚函数 初始化开入开出名称和使能

signals:
	void sig_Para_ChangeIndexChanged(int);
	void sig_Para_ChangeIsAll();
	void sig_Para_ChangeTypeIndexChanged(int);
	void sig_Para_G1CurrentChanged(float);
	void sig_Para_G2CurrentChanged(float);
	void sig_Para_G1VoltChanged(float);
	void sig_Para_G2VoltChanged(float);
	void sig_Para_DiffAngleChanged(float);	
	void sig_Para_HzChanged(float);
	void sig_Para_StartChanged(float);
	void sig_Para_EndChanged(float);
	void sig_Para_StepChanged(float);
	void sig_Para_ErrorTimeChanged(float);
	void sig_Para_ReturnTypeIndexChanged(int);
	void sig_YRangeChanged(changed_type type,QString strTitle,float fdown,float fup);

private slots:
	
	void on_m_btnManual_clicked();
	void on_m_cbbVar_currentIndexChanged(int index);
    void on_m_cbbVar2_currentIndexChanged(int index);
	void on_m_cbbVarType_currentIndexChanged(int index);
	void on_m_cbbVarType2_currentIndexChanged(int index);
	void on_m_cbbType_currentIndexChanged(int index);
	void on_m_cbbDirection_currentIndexChanged(int index);
//	void on_m_cbGroup_clicked(int nState);
	void on_m_cbBefore_clicked(int nState);

// 	void on_m_editVarA1_clicked();
// 	void on_m_editVarA2_clicked();
// 	void on_m_editVarV1_clicked();
// 	void on_m_editVarV2_clicked();
//	void on_m_editfDiffIAngle_clicked();
	void on_m_editFreq_clicked();
	void on_m_editInit_clicked();
	void on_m_editFinish_clicked();
	void on_m_editStep_clicked();
	void on_m_editTime_clicked();

	void on_m_editTimeBeforeChange_clicked();
	void on_m_editTimeBeforeFail_clicked();
	void on_m_editCurBeforeChange_clicked();
	void on_m_editfDiffUaIaAngle_clicked();
	//void slot_ck_BinaryInStateChanged(int );
	void on_m_editTimeBeforeChangeChanged();
	void on_m_editTimeBeforeFailChanged();
	void on_m_editCurBeforeChangeChanged();
	void on_m_editfDiffUaIaAngleChanged();
	void slot_edit_changed2(QSttLineEdit* pEditLine, long nType);
	void slot_Estimate();
	void slot_SettingValue();

// 	void on_m_editVarA1Changed();
// 	void on_m_editVarA2Changed();
// 	void on_m_editVarV1Changed();
// 	void on_m_editVarV2Changed();
// 	void on_m_editfDiffIAngleChanged();
	void on_m_editFreqChanged();
	void on_m_editInitChanged();
	void on_m_editFinishChanged();
	void on_m_editStepChanged();
	void on_m_editInit2Changed();
    void on_m_editFinish2Changed();
	void on_m_editStep2Changed();
	void on_m_editTimeChanged();

	void slot_chb_InPutA_StateChanged(int);
	void slot_chb_InPutB_StateChanged(int);
	void slot_chb_InPutC_StateChanged(int);
	void slot_chb_InPutD_StateChanged(int);
	void slot_chb_InPutE_StateChanged(int);
	void slot_chb_InPutF_StateChanged(int);
	void slot_chb_InPutG_StateChanged(int);
	void slot_chb_InPutH_StateChanged(int);
	void slot_chb_InPutI_StateChanged(int);
	void slot_chb_InPutJ_StateChanged(int);

	void slot_radio_AndStateChanged(bool);
	void slot_radio_OrStateChanged(bool);

	void slot_chb_OutPut1StateChanged(int);
	void slot_chb_OutPut2StateChanged(int);
	void slot_chb_OutPut3StateChanged(int);
	void slot_chb_OutPut4StateChanged(int);
    void slot_chb_OutPut5StateChanged(int);
    void slot_chb_OutPut6StateChanged(int);
    void slot_chb_OutPut7StateChanged(int);
    void slot_chb_OutPut8StateChanged(int);
// 	void slot_chb_OutPut9StateChanged(int);
// 	void slot_chb_OutPut10StateChanged(int);

	void slot_chb_OutPut1_EStateChanged(int);
	void slot_chb_OutPut2_EStateChanged(int);
	void slot_chb_OutPut3_EStateChanged(int);
	void slot_chb_OutPut4_EStateChanged(int);
    void slot_chb_OutPut5_EStateChanged(int);
    void slot_chb_OutPut6_EStateChanged(int);
    void slot_chb_OutPut7_EStateChanged(int);
    void slot_chb_OutPut8_EStateChanged(int);
// 	void slot_chb_OutPut9_EStateChanged(int);
// 	void slot_chb_OutPut10_EStateChanged(int);
};

extern QSttMacroParaEditViewGradient* g_GradientMain;

#endif // STTMACROPARAEDITVIEWGRIDENT_H
