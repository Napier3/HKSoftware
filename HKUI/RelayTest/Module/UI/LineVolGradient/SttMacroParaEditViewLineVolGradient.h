#ifndef STTMACROPARAEDITVIEWLINEVOLGRIDENT_H
#define STTMACROPARAEDITVIEWLINEVOLGRIDENT_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include <QWidget>
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "LineVolGradientGroupWidget.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
#include "ui_SttMacroParaEditViewSequenceGradient.h"
#include "../../SttTest/Common/LineVolt/tmt_linevolt_gradient_test.h"
#include "../Gradient/SttMacroParaEditViewGradient.h"


namespace Ui {
    class QSttMacroParaEditViewSequenceGradient;
}
class QSttMacroParaEditViewLineVolGradient : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
    Ui::QSttMacroParaEditViewSequenceGradient *ui;

	explicit QSttMacroParaEditViewLineVolGradient(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewLineVolGradient();

	tmt_LineVolGradientTestEx* m_pCurTest;
	tmt_LineVolGradientParasEx* m_pCurPara;
	tmt_LineVolGradientResult* m_pCurResult;

	CDataType m_oLineVolGradientChs;
	QStringList m_ChangeTypeList;
	QStringList m_ChangeTypeList2;
	QStringList m_listTestMode2;//两种测试模式选择
	QStringList m_listTestMode3;//三种测试模式选择

	QString  m_strUnit[32];

	QLineVolGradientGroupWidget* m_pGroupWidget;
	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;

private:
	CString m_strVoltage;
	CString m_strCurrent;
	CString m_strFreq;

	CString GetCurChannal(PTMT_PARAS_HEAD pParas);

	void SetLineVoltGradientFont();

public:
	virtual void InitLanuage();

	void InitUI();
	void InitParas();
	void InitConnections();
	void updateLabName();
	void initQList();
	void CopyBinaryConfig(BOOL b=TRUE);
	void InitGradientChannel(LineVolt_type vartype);
	void UpdateLineVolGradientChs();
	void InitUI_AfterGridentSel();
	void UpdateG1G2();
	void EnableRadientType();
	void getYRange(float ftime,float fv,float v1,float v2,float fstart,float fend,float &down,float &up);
	long GetSttLineVolGradientChannelType(long nChannel);
	CSttTestResourceBase* CreateTestResource();
	void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);

	virtual PTMT_PARAS_HEAD GetTestParas() { return m_pCurTest;}
	virtual char* GetMacroID(){ return "LineVolGradientTest"; }

	virtual PTMT_PARAS_HEAD CreateTestParas(const char * pszMacroID);
	virtual PTMT_PARAS_HEAD CreateTestParas(PTMT_PARAS_HEAD pCurr);
	void SetData(PTMT_PARAS_HEAD pCurr);


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

	void UpdateTestResource(BOOL bCreateChMaps);
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	void UpdateBinBoutExTab();//更新开关量扩展界面
	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void EnableGooseParaWidget(bool b);
	bool ExistGooseParaWidget();
	void InitMannualparas();

	void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void UpdateFT3Tab(BOOL bUpdateList = FALSE);
	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget(); 
	void EnableFT3OutParaWidget(bool b);
	bool ExistFT3OutParaWidget();
	void AddUnGradientSettingWidget();
	void RemoveUnGradientSettingWidget();
	void InitStyle();	
	LineVolt_type getLineVoltParaTypeByInt(int iVar);

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

	void on_m_btnManual_clicked();//更多标注量
	void on_m_cbbVar_currentIndexChanged(int index);//变量
	void on_m_cbbVarType_currentIndexChanged(int index);//变量类型(幅值，相位)
	void on_m_cbbType_currentIndexChanged(int index);//类型(动作值，返回系数)
//	void on_m_cbbDirection_currentIndexChanged(int index);//递变方向
	void on_m_cbBefore_clicked(int nState);//脉冲

	void on_m_editInit_clicked();
	void on_m_editFinish_clicked();
	void on_m_editStep_clicked();
	void on_m_editTime_clicked();

	void on_m_editTimeBeforeChange_clicked();
	void on_m_editTimeBeforeFail_clicked();
	void on_m_editCurBeforeChange_clicked();
	void on_m_editfDiffUaIaAngle_clicked();
	void on_m_editTimeBeforeChangeChanged();
	void on_m_editTimeBeforeFailChanged();
	void slot_edit_changed2(QSttLineEdit* pEditLine, long nType);
	void slot_Estimate();
	void slot_SettingValue();

	void on_m_editInitChanged();
	void on_m_editFinishChanged();
	void on_m_editStepChanged();
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
	

	void slot_chb_OutPut1_EStateChanged(int);
	void slot_chb_OutPut2_EStateChanged(int);
	void slot_chb_OutPut3_EStateChanged(int);
	void slot_chb_OutPut4_EStateChanged(int);

};

extern QSttMacroParaEditViewLineVolGradient* g_LineVolGradientMain;
#endif 