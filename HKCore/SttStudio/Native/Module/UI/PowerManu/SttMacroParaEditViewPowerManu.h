#ifndef STTMACROPARAEDITVIEWPOWERMANU_H
#define STTMACROPARAEDITVIEWPOWERMANU_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "PowerManualWidget.h"
#include "ManualView_PV.h"
#include "../Manual/QSttManualBinBoutDlg.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
class QSttMacroParaEditViewPowerManu : public CSttMacroParaEditViewOriginal
{
    Q_OBJECT

public:
	QPowerManualWidget *m_pPowerManualWidget;
	QManualView_PV m_oPV;

	tmt_PowerManuTest m_oManualTest;
	tmt_PowerManuParas *m_pManualParas;

	bool m_bIsChanging;//判断+和-按钮所造成的更改是否已经完成,未完成时不允许发送下一次SetItemPara
	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;

	int m_nManuHarmIndex;

	//tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    //tmt_channel_power m_uiPOW[MAX_VOLTAGE_COUNT];

public:
    explicit QSttMacroParaEditViewPowerManu(QWidget *parent = 0);
    virtual ~QSttMacroParaEditViewPowerManu();

private:
	void InitUI();
	void SendUpdateParameter();
	void InitBinaryInBinaryOutUI();
	void InitOtherParasUI();
	void SetManualOtherParasFont();
	void InitStyle();

public:
	virtual void InitLanuage();
	void CopyBinaryConfig(BOOL b=TRUE);
	void InitBinStateOnStarting();
	virtual void InitConnect();
	virtual CSttTestResourceBase* CreateTestResource();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);

	virtual void ClearResult(PTMT_PARAS_HEAD pHead);
	virtual void OnTestResults(CDataGroup *pResults);
	virtual void UpdateTestResource(BOOL bCreateChMaps);

	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	virtual void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	virtual void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);
	virtual void UpdateBinBoutExTab();//更新开关量扩展界面
	virtual void UpdateManualParas();

	virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oManualTest;}
	virtual char* GetMacroID(){ return STT_ORG_MACRO_PowerManuTest; }

    void InitParasView();
    void InitPVView();
	void slot_SwitchStateChanged();

	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	virtual void ShowReport(CDvmValues *pValues);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);

	void slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor = FALSE);

	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void EnableGooseParaWidget(bool b);
	bool ExistGooseParaWidget();

	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget(); 
	void EnableFT3OutParaWidget(bool b);
	bool ExistFT3OutParaWidget();

	void CalPhaseValues();
	
signals:
	void sig_updataParas();


protected slots:
	void slot_Lock_PushButton_clicked();
	void slot_Add_PushButton_clicked();
	void slot_Minus_PushButton_clicked();
	void slot_StartValue_LineEdit_editingFinished();
	void slot_EndValue_LineEdit_editingFinished();
	void slot_StepTime_LineEdit_editingFinished();
	void slot_StepValue_LineEdit_editingFinished();	
	//void slot_Freq_LineEdit_editingFinished();	
	
	void slot_Auto_CheckBox_clicked();
	void slot_ChGradientTypeComboBox_currentIndexChanged(int index);
	void slot_ChSelectComboBox_currentIndexChanged(int index);
	void slot_ChangedTypeComboBox_currentIndexChanged(int index);
	void slot_Bout_CheckBox1_clicked();
	void slot_Bout_CheckBox2_clicked();
	void slot_Bout_CheckBox3_clicked();
	void slot_Bout_CheckBox4_clicked();
	void slot_StepTime_LineEdit_Changed();
	void slot_StepValue_LineEdit_Changed();
	//void slot_Freq_LineEdit_Changed();
	void slot_StartValue_LineEdit_Changed();
	void slot_EndValue_LineEdit_Changed();
	void slot_BinarySetPushButton_clicked();
	void slot_updateParas();
	void slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);
	void slot_GooseDataChanged();
	void slot_FT3DataChanged();
	void slot_EstimatePushButton_clicked();
};

extern QSttMacroParaEditViewPowerManu* g_pPowerManuTest;

#endif // STTMACROPARAEDITVIEWPOWERMANU_H
