#ifndef SttMacroParaEditViewSoe_H
#define SttMacroParaEditViewSoe_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
#include "../Manual/ManualView_IV.h"
#include "../Manual/QSttManualBinBoutDlg.h"
#include "../SttTestCntrCmdDefine.h"


#include "../../SttTest/Common/tmt_soe_test.h"

#include "SttMacroParaEditViewSoeWidget.h"

class QSttMacroParaEditViewSoe : public CSttMacroParaEditViewOriginal
{
    Q_OBJECT

public:

	QManualView_IV m_oIV;

 	bool m_bIsChanging;//判断+和-按钮所造成的更改是否已经完成,未完成时不允许发送下一次SetItemPara
	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;

	QSttMacroParaEditViewSoeWidget *m_pSoeWidget;
	tmt_SoeTest     m_oSoeTest;
	tmt_SoeParas    *m_pSoeParas;


public:
    explicit QSttMacroParaEditViewSoe(QWidget *parent = 0);
    virtual ~QSttMacroParaEditViewSoe();


	void InitUI();
	void SendUpdateParameter();
	void InitOtherParasUI();//其他字体设置
	void SetManualOtherParasFont();
	void InitStyle();//设置样式

	void InitGirdData();

public:
	/*virtual void InitLanuage();*///语言设置

	void InitBinStateOnStarting();//没有任何代码
	virtual void InitConnect();
	virtual CSttTestResourceBase* CreateTestResource();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);

	virtual void ClearResult(PTMT_PARAS_HEAD pHead);
	virtual void OnTestResults(CDataGroup *pResults);
	virtual void UpdateTestResource(BOOL bCreateChMaps);

	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	virtual void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	virtual void UpdateBinBoutExTab();//更新开关量扩展界面
	virtual void UpdateSoeParas();

	virtual void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);

	virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oSoeTest;}
	virtual char* GetMacroID(){ return /*STT_ORG_MACRO_SequenceManuTest*/STT_ORG_MACRO_SoeTest; }

    void InitParasView();

	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	virtual void ShowReport(CDvmValues *pValues);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);

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

	void slot_lne_PulseWidthChanged();
	void slot_lne_SOEChanged();
	void slot_lne_DeflectioChanged();

	void slot_lne_PulseWidthChangedKeyBoard();
	void slot_lne_SOEChangedKeyBoard();
	void slot_lne_DeflectioChangedKeyBoard();

	void slot_SelectAll_PushButton_Clicked();
	void slot_CancelAll_PushButton_Clicked();

	void slot_InitialAl_PushButton_Clicked();
	void slot_InitialDivideAll_PushButton_Clicked();

	void slot_lneH_GPSTimeChanged();
	void slot_lneM_GPSTimeChanged();
	void slot_lneS_GPSTimeChanged();

	void slot_lneH_GPSTimeChangedKeyBoard();
	void slot_lneM_GPSTimeChangedKeyBoard();
	void slot_lneS_GPSTimeChangedKeyBoard();
	void slot_TrigerCondition_cmb_Changed(int index);


  	void slot_GooseDataChanged();
	void slot_updateParas();
	void slot_FT3DataChanged(); 

};

extern QSttMacroParaEditViewSoe* g_pSoeTest;

#endif // SttMacroParaEditViewSoe_H
