#ifndef STTMACROPARAEDITVIEWREMOTEMEAS_H
#define STTMACROPARAEDITVIEWREMOTEMEAS_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "RemoteMeasWidget.h"
//#include "RemoteMeasParaTable.h"
#include "RemoteMeasRatWidget.h"
#include "../Manual/QSttManualBinBoutDlg.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
class QSttMacroParaEditViewRemoteMeas : public CSttMacroParaEditViewOriginal
{
    Q_OBJECT

public:
	explicit QSttMacroParaEditViewRemoteMeas(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewRemoteMeas();

	QBoxLayout* m_pMainLayout;	
	QRemoteMeasWidget *m_pRemoteMeasWidget;
	//QRemoteMeasParaTable m_oIV;
	QRemoteMeasRatWidget* m_pBtnWidget;

	tmt_ManualTest m_oManualTest;
	tmt_ManualParas *m_pManualParas;

	bool m_bIsChanging;//判断+和-按钮所造成的更改是否已经完成,未完成时不允许发送下一次SetItemPara
	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;

	//int m_nManuHarmIndex;

	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

	QTimer m_oRemoteMeasTimer;
	long m_nReadCount;//读取的次数
//	CString m_strAinDatasetPath;//遥测数据集路径

private:
	void InitUI();
	void SendUpdateParameter();
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

	virtual void UpdateBinBoutExTab();//更新开关量扩展界面
	virtual void UpdateManualParas();

	virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oManualTest;}
	virtual char* GetMacroID(){ return STT_MACRO_ID_ManualTest; }

	virtual void UpdateDeviceModelRef();

    void InitParasView();
    void InitIVView();
	void slot_SwitchStateChanged();

	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	virtual void ShowReport(CDvmValues *pValues);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);

	void slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor = FALSE);

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

	virtual void slot_SelectIndexChanged(int nIndex);
	void slot_Volt1Value_LineEdit_editingFinished();
	void slot_Volt2Value_LineEdit_editingFinished();
	void slot_Curr1Value_LineEdit_editingFinished();
	void slot_Curr2Value_LineEdit_editingFinished();	
	void slot_ZeroVolt1Value_LineEdit_editingFinished();
	void slot_ZeroVolt2Value_LineEdit_editingFinished();
	void slot_ZeroCurr1Value_LineEdit_editingFinished();
	void slot_ZeroCurr2Value_LineEdit_editingFinished();	

	void slot_Auto_CheckBox_clicked();
	void slot_ChGradientTypeComboBox_currentIndexChanged(int index);
	void slot_ChSelectComboBox_currentIndexChanged(int index);
	void slot_ChangedTypeComboBox_currentIndexChanged(int index);
	void slot_StepTime_LineEdit_Changed();
	void slot_StepValue_LineEdit_Changed();
	void slot_StartValue_LineEdit_Changed();
	void slot_EndValue_LineEdit_Changed();

	void slot_Volt1Value_LineEdit_Changed();
	void slot_Volt2Value_LineEdit_Changed();
	void slot_Curr1Value_LineEdit_Changed();
	void slot_Curr2Value_LineEdit_Changed();	
	void slot_ZeroVolt1Value_LineEdit_Changed();
	void slot_ZeroVolt2Value_LineEdit_Changed();
	void slot_ZeroCurr1Value_LineEdit_Changed();
	void slot_ZeroCurr2Value_LineEdit_Changed();

	void slot_updateParas();
	void slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);
	void slot_GooseDataChanged();
	void slot_FT3DataChanged();
	void slot_Timer();

};

extern QSttMacroParaEditViewRemoteMeas* g_pRemoteMeas;

#endif // STTMACROPARAEDITVIEWREMOTEMEAS_H
