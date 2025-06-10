#ifndef STTMACROPARAEDITVIEWINTELLIGENTTERMINAL_H
#define STTMACROPARAEDITVIEWINTELLIGENTTERMINAL_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/SttIntelGoutToBinParaWidget.h"
#include "../Module/GooseParaWidget/SttIntelBoutToGinParaWidget.h"
#include "IntellTerminalWidget.h"
#include "../Manual/ManualView_IV.h"
#include "../Manual/QSttManualBinBoutDlg.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"

class QSttMacroParaEditViewIntelligentTerminal : public CSttMacroParaEditViewOriginal
{
    Q_OBJECT

public:
	QIntellTerminalWidget *m_pIntellTerminalWidget;

	tmt_ManualTest m_oIntellTerminalTest;
	tmt_ManualParas *m_pIntellTerminalParas;

	QSttIntelBoutToGinParaWidget* m_pSttIntelBoutToGinParaWidget;//开入转开出
	QSttIntelGoutToBinParaWidget* m_pSttIntelGoutToBinParaWidget;//开出转开入
	QFT3OutParaWidget* m_pFT3OutParaWidget;

	int m_nRowIndex;
	int m_nTestIndex;
	
	CString m_strInitBinIn;
	CString	m_strEndBinIn;
	int	m_nGooseOutType[PARAS_RSLT_COUNT][PARAS_RSLT_EXPR_LEN];	
	int	m_nGooseInType[PARAS_RSLT_COUNT][PARAS_RSLT_EXPR_LEN];	
	float m_fGooseInTime[PARAS_RSLT_COUNT][PARAS_RSLT_EXPR_LEN];
	float m_fGooseOutTime[PARAS_RSLT_COUNT][PARAS_RSLT_EXPR_LEN];
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

public:
    explicit QSttMacroParaEditViewIntelligentTerminal(QWidget *parent = 0);
    virtual ~QSttMacroParaEditViewIntelligentTerminal();

private:
	void InitUI();
	void SendUpdateParameter();
	void InitBinaryInBinaryOutUI();
	void InitOtherParasUI();
	void SetManualOtherParasFont();
	void InitStyle();
	void init();

public:

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
	virtual void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas,CIecCfgGinDatas* pCfgGinDatas);
	virtual void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);
	virtual void UpdateBinBoutExTab();//更新开关量扩展界面
	virtual void UpdateManualParas();

	virtual void UpdateEventMsg(CEventResult *pCurrEventResult);

	int GetGooseSignal(CString strID);//根据m_strDefaultValue获取信号代表值
	void UpGoutData(int nTestIndex,int nindex);//根据记录的行数获取发布信号代表值
	void UpGinData(int nTestIndex,int nindex);//根据记录的行数获取接收信号代表值
	CIecCfgGoutData* GetGoutData( int nindex );
	CIecCfgGinData* GetGinData( int nindex );

	virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oIntellTerminalTest;}
	virtual char* GetMacroID(){ return "BinaryManuTest"; }

    void InitParasView();
    void InitIVView();
	void slot_SwitchStateChanged();
	
	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	void startInit(BOOL bEnableState,int nGooseParasUI_State);
	void stopInit(BOOL bEnableState,int nGooseParasUI_State);

	virtual void ShowReport(CDvmValues *pValues);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);

	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas,CIecCfgGinDatas* pCfgGinDatas );
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

	void slot_BinarySetPushButton_clicked();
	void slot_setBinOut(int nbout ,bool bStateChanged);
	void slot_updateParas();
	void slot_GooseDataChanged();
	void slot_FT3DataChanged();
	void slot_GoutRowIndex(int nRowIndex);
	void slot_RevertData();
	void slot_GinRowIndex(int nRowIndex,float fActTime);

	void slot_TabPageChanged( int nindex );//发布和订阅页面
	void slot_Tab_cellClicked(int nindex );//G1.G2...页面
	void slot_UpdateEventMsgTime(CEventResult *pEventInfo);
	
};

extern QSttMacroParaEditViewIntelligentTerminal* g_pIntelligentTest;

#endif // STTMACROPARAEDITVIEWINTELLIGENTTERMINAL_H
