#ifndef STTMACROPARAEDITVIEWSEQUENCEGRIDENT_H
#define STTMACROPARAEDITVIEWSEQUENCEGRIDENT_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include <QWidget>
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
//#include "SequenceGradientGroupWidget.h"
#include "SequenceGradientWidget.h"
//#include "../Gradient/GradientEstimateDlg.h"
#include "SequenceGradientEstimateDlg.h"
#include "../Gradient/GradientSettingValueDlg.h"
#include "../../SttTest/Common/Sequence/tmt_sequence_gradient_test.h"

#define STT_RSLTEXPR_MACROID_COMMON _T("Common")

#define STT_GRADIENT_CHANNEL_TYPE_G1_CURR    0
#define STT_GRADIENT_CHANNEL_TYPE_G1_VOLT    1

#define FILE_GRADIENT		"SequenceGradient"
#define POSTFIX_GRADIENT    "grtxml"

namespace Ui{
class QSttMacroParaEditViewSequenceGradient;
}

class QSttMacroParaEditViewSequenceGradient : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	Ui::QSttMacroParaEditViewSequenceGradient *ui;

	explicit QSttMacroParaEditViewSequenceGradient(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewSequenceGradient();

	tmt_SequenceGradientTestEx *m_pCurTest;
	tmt_GradientParasEx *m_pCurPara;
	tmt_GradientResult *m_pCurResult;

	CDataType m_oSequenceGradientChs;
	QStringList m_ChangeTypeList;
	QStringList m_listTestMode2;//两种测试模式选择
	QStringList m_listTestMode3;//三种测试模式选择
	
	QSequenceGradientWidget* m_pSequenceGradientWidget;
	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;
	//自动化测试用
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

private:
	CString m_strVoltage;
	CString m_strCurrent;
	CString m_strFreq;
	void SetSequenceGradientFont();

public:
	virtual void InitLanuage();
	void InitUI();
	void InitParas();
	void InitConnections();
	void InitStyle();
	void CopyBinaryConfig(BOOL b=TRUE);
	void InitMannualparas();//变化前时间和故障前时间的初始化
	void InitQList();//初始化下拉框链表
	void UpdateSequenceGradientChs();//更新变量值（下拉框）
	void InitSequenceGradientChannel(Sequence_type vartype);//初始化变量值
	void getYRange(float ftime,float fv,float v1,float v2,float fstart,float fend,float &down,float &up);//获取最大值和最小值
	void InitUI_AfterSequenceGridentSel();//根变量类型据变量和变量类型，修改单位
	void EnableRadientType();//根据变量类型，使能递变方向的失能类型
	long GetSttSequenceGradientChannelType(long nChannel);//根据变量获取值类型
	void updateLabName();
	void AddUnSequenceGradientSettingWidget();
	void RemoveUnSequenceGradientSettingWidget();
	void InitEnableButtons();
	

	void SetData(PTMT_PARAS_HEAD pCurr);//后面完善结构体需要修改
	virtual void startInit();//对界面的控件进行失能状态处理
	virtual void stopInit();
	virtual PTMT_PARAS_HEAD CreateTestParas(const char * pszMacroID);//新建测试项，需要用到结构体
	virtual PTMT_PARAS_HEAD CreateTestParas(PTMT_PARAS_HEAD pCurr);//克隆测试项
	void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);//序列化测试参数结构体,后期需要更改
	
	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();//测试开始界面的响应
	virtual void OnViewTestStop();//测试停止界面的响应

	//CSttTestResourceBase* CreateTestResource();直接在构造函数中创建软件资源对象
	void slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor = FALSE);//需要根据ui界面更改
	virtual PTMT_PARAS_HEAD GetTestParas() { return m_pCurTest;}
	virtual char* GetMacroID(){ return STT_ORG_MACRO_SequenceGradientTest; }

	virtual void ShowReport(CDvmValues *pValues);//根据id获取值
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);//需要改结构体数据以及链表中的数据
	
	virtual CString GetDefaultParaFile(); //根据路径获取参数文件
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);//判断文件是否存在
	void UpdateTestResource(BOOL bCreateChMaps);//更新测试

	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);//如果需要数字输出，初始化goose页面以及更新tab页面
	void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void UpdateFT3Tab(BOOL bUpdateList = FALSE);
	void UpdateBinBoutExTab();//更新开关量扩展界面

	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void EnableGooseParaWidget(bool b);
	bool ExistGooseParaWidget();

	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget(); 
	void EnableFT3OutParaWidget(bool b);
	bool ExistFT3OutParaWidget();

signals:
	void sig_Para_ChangeIndexChanged(int);
	void sig_Para_ChangeIsAll();
	void sig_Para_ChangeTypeIndexChanged(int);
	void sig_Para_G1CurrentChanged(float);
	void sig_Para_G1VoltChanged(float);
	void sig_Para_DiffAngleChanged(float);	
	void sig_Para_HzChanged(float);
	void sig_Para_StartChanged(float);
	void sig_Para_EndChanged(float);
	void sig_Para_StepChanged(float);
	void sig_Para_ErrorTimeChanged(float);
	void sig_Para_ReturnTypeIndexChanged(int);
	void sig_YRangeChanged(changed_type type,QString strTitle,float fdown,float fup);

private slots:

 	void on_m_cbbVar_currentIndexChanged(int index);
 	void on_m_cbbVarType_currentIndexChanged(int index);
 	void on_m_cbbType_currentIndexChanged(int index);
 	void on_m_cbbDirection_currentIndexChanged(int index);
 	void on_m_editTimeBeforeChangeChanged();
 	void on_m_editTimeBeforeFailChanged();
 	void slot_edit_changed2(QSttLineEdit* pEditLine, long nType);
	void on_m_cbBefore_clicked(int nState);//脉冲状态相应变化
	void slot_Estimate();
	void slot_SettingValue();



 	//void on_m_editFreqChanged();
 	void on_m_editInitChanged();
 	void on_m_editFinishChanged();
 	void on_m_editStepChanged();
 	void on_m_editTimeChanged();
	void on_m_editInit_clicked();
	void on_m_editFinish_clicked();
	void on_m_editStep_clicked();
	void on_m_editTime_clicked();
	void on_m_editTimeBeforeChange_clicked();
	void on_m_editTimeBeforeFail_clicked();

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

	void on_m_btnManual_clicked();
	

};

extern QSttMacroParaEditViewSequenceGradient* g_SequenceGradientMain;

#endif