#ifndef STTMACROPARAEDITVIEWIMPEDANCEMANU_H
#define STTMACROPARAEDITVIEWIMPEDANCEMANU_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "ImpedanceManuWidget.h"
#include "../Manual/QSttManualBinBoutDlg.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
class QSttMacroParaEditViewImpedanceManu : public CSttMacroParaEditViewOriginal
{
    Q_OBJECT

public:
	QImpedanceManuWidget *m_pImpedanceManuWidget;

	tmt_ManualImpedTest m_oManualImpedTest;
	tmt_ManualImpedParas *m_pManualImpedParas;

	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

	bool m_bIsChanging;//判断+和-按钮所造成的更改是否已经完成,未完成时不允许发送下一次SetItemPara
	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;

public:
    explicit QSttMacroParaEditViewImpedanceManu(QWidget *parent = 0);
    virtual ~QSttMacroParaEditViewImpedanceManu();

	virtual void InitBinaryInBinaryOutUI();//20240913 huangliang 改为虚函数

private:
	void InitUI();
	void SendUpdateParameter();
	//void InitBinaryInBinaryOutUI();	//20240913 huangliang 改为虚函数
	void InitOtherParasUI();
	void SetManualOtherParasFont();
	void InitStyle();

public:
	virtual void InitLanuage();
	void CopyBinaryConfig(BOOL b=TRUE);
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
	void CalPhaseValues();

	virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oManualImpedTest;}
	virtual char* GetMacroID(){ return STT_ORG_MACRO_ImpedManualTest; }

    void InitParasView();
    void InitIVView();
	void slot_SwitchStateChanged();

	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	virtual void ShowReport(CDvmValues *pValues);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);

	//void slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor = FALSE);

	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void EnableGooseParaWidget(bool b);
	bool ExistGooseParaWidget();

	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget(); 
	void EnableFT3OutParaWidget(bool b);
	bool ExistFT3OutParaWidget();
	
signals:
	void sig_updataParas();


protected slots:
	void slot_Edit_Changed();
	void slot_Lock_PushButton_clicked();
	void slot_PushButton_clicked();
	void slot_BinarySetPushButton_clicked();
	void slot_updateParas();
	void slot_GooseDataChanged();
	void slot_FT3DataChanged();
	void slot_EstimatePushButton_clicked();

	void slot_CmbErrorTypeIndexChanged(int);
	void slot_CmbCalModeIndexChanged(int);
	void slot_CmbCacuTypeIndexChanged(int);
	void slot_CmbFirstModeIndexChanged(int);  //变量选择1
	void slot_CmbSecondModeIndexChanged(int);//变量选择2
	void slot_CmbChangeTypeIndexChanged(int);
	void slot_RadioZPhiAndRX_StateChanged();
	void slot_Chb_AutoStateChanged(int);//自动递变
	void slot_Chb_MutationStateChanged(int);//突变量启动

	void slot_ck_Out1StateChanged();
	void slot_ck_Out2StateChanged();
	void slot_ck_Out3StateChanged();
	void slot_ck_Out4StateChanged();
};

extern QSttMacroParaEditViewImpedanceManu* g_pImpedanceManuTest;

#endif // STTMACROPARAEDITVIEWIMPEDANCEMANU_H
