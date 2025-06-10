#ifndef STTMACROPARAEDITVIEWFAULT_GRADIENT_H
#define STTMACROPARAEDITVIEWFAULT_GRADIENT_H

#include <QWidget>
#include "ui_SttMacroParaEditViewFaultGradient.h"

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"

#include "../../SttTest/Common/Gradient/tmt_fault_gradient_test.h"

#define FILE_FAULTGRADIENT		"FaultGradientTest"
#define POSTFIX_FAULTGRADIENT    "grtxml"

namespace Ui
{
	class QSttMacroParaEditViewFaultGradient;
}

class QSttMacroParaEditViewFaultGradient : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewFaultGradient(QWidget *parent = 0);
	~QSttMacroParaEditViewFaultGradient();

public:
	//界面初始化 属性 字体 文字等
	void SetUIFont(QWidget* pWidget);
	void SetStyleStateValue(QGroupBox* pGroup,int nState = -1,int nVFlag = -1);
	void InitComboBox();
	void InitUI();
	//内容初始化设置
	void SetParas();
	void InitConnections();
	void SetData(PTMT_PARAS_HEAD pCurr);
	//改变单位 设置
	void SetLableTextUnit(int nFaultIndex,int nChangIndex);
	void SetUnit(int nFaultMode,int nValueType,QString strUnit);
	//获取edit 的数值
	void GetEditFloatValue(QSttLineEdit* pLine,float& fValue);
	//设置变化量改变 从而改变 短路电流/电压 阻抗角变化 
	void SetShortVaVmAngle(int nFaultIndex,int nChangIndex);
	void SetShortVaVmAngleEnable(int nShortVmFlag = 1,int nShortVmTypeFlag = 1,int nShortVaFlag = 1,int nAngleFlag = 1);
	//设置edit 值限制 1 时间  2 电流  3 电压  4 角度 5 HZ
	float SetEditValueControl(float fValue,int nFlag = -1,QSttLineEdit* pLine = NULL);
	//切换单位  界面所有edit重新设置限制值
	void SetAllEditValueControl();
	///////////////////////////////////////////////////
	//FT3 goose 数据更新
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);//如果需要数字输出，初始化goose页面以及更新tab页面
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);

	void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);
	//void UpdateBinBoutExTab();//更新开关量扩展界面 暂时没有
	//goose 界面 添加 删除
	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void EnableGooseParaWidget(bool b);
	bool ExistGooseParaWidget();
	// FT3 界面添加 删除
	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget(); 
	void EnableFT3OutParaWidget(bool b);
	bool ExistFT3OutParaWidget();

signals:


public slots:
	void on_ReturnType_currentIndexChanged(int nIndex);
	//根据故障模式 改变变化量的comombox内容
	void on_FaultMode_currentIndexChanged(int nIndex);
	void on_ChangeValue_currentIndexChanged(int nIndex);
	void on_VMType_currentIndexChanged(int nIndex);
	//开入量和开出 正常 故障
	void on_GrpBin_ButtonClick(QAbstractButton * pCurrBtn);
	void on_GrpOutNormalError_ButtonClick(QAbstractButton * pCurrBtn);
	//逻辑与或
	void on_AndStateChanged(bool);
	//更多开出   整定和结果评定
	void on_MoreOut_ButtonClick();
	void on_Estimate_ButtonClick();
	//edit 变量响应
	void on_EditInit_Finish();            //变化始值
	void on_EditFinish_Finish();		  //变化终值
	void on_EditStep_Finish();			  //变化步长
	void on_EditFaultTime_Finish();		  //故障时间
	void on_EditShortVm_Finish();		  //短路电压
	void on_EditShortVa_Finish();		  //短路电流
	void on_EditAngle_Finish();			  //阻抗角
	void on_EditTimeBeforeChange_Finish();//变化前时间
	void on_EditTimeBeforeFail_Finish();  //故障前时间
	void on_EditFaultBeforeVm_Finish();	  //故障前电压
	void on_EditFaultBeforeVa_Finish();	  //故障前电流
	void on_EditFaultBeforeAngle_Finish();//故障前相角

public:
	virtual void InitLanuage();
	//读取序列化
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	//创建结构体指针，不能直接new
	virtual PTMT_PARAS_HEAD CreateTestParas(const char * pszMacroID);
	//用于返回创建的结构体指针
	virtual PTMT_PARAS_HEAD GetTestParas() { return m_pCurFGTest;}
	virtual char* GetMacroID(){ return STT_ORG_MACRO_FaultGradientTest; }
	//测试和开始和结束 报告
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void ShowReport(CDvmValues *pValues);
	//修改和获取结构体 最新的值 
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	//更新
	virtual void UpdateTestResource(BOOL bCreateChMaps);
	//根据路径获取参数文件  grtxml 测试文件
	virtual CString GetDefaultParaFile(); 
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);


private:
	//参数结构体
	tmt_fault_gradient_test*			 m_pCurFGTest;
	//goose 和FT3 界面
	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;
	//初始化  commbox 列表值
	QStringList							 m_lstGradientType;
	QStringList							 m_lstFaultMode;
	QMap<int,QStringList>				 m_mapChangValue;
	//根据故障模式改变  记录上一次Index值，用于切换变化量的comombox值 
	int									 m_nLastFaultModeIndex;
	QStringList							 m_lstShortVm;
	//开出量 btn数量中间值
	int									 m_nOutNormalError;
	//当前的 edit 限制的类型 根据commbox 选择电压电流决定
	int									 m_nEditControlType;

private:
	Ui::QSttMacroParaEditViewFaultGradient *ui;
};
#endif // STTMACROPARAEDITVIEWFAULT_GRADIENT_H
