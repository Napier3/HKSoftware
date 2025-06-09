#ifndef STTMACROPARAEDITVIEWHARM_H
#define STTMACROPARAEDITVIEWHARM_H

#include <QMainWindow>
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "HarmWidget.h"

#include "../Controls/SttLineEdit.h"
#include "../Controls/SettingCtrls/QSettingLineEdit.h"
#include "../Controls/SettingCtrls/settingselectdlg.h"

#define FILE_HARMTEST		"HarmTest"
#define POSTFIX_HarmTEST    "hrmxml"

class QSttMacroParaEditViewHarm: public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
    QSttMacroParaEditViewHarm(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewHarm();

	virtual void ShowReport(CDvmValues *pValues);
	virtual void SetDatas(CDataGroup *pParas);
	virtual void GetDatas(CDataGroup *pParas);


	tmt_HarmTest m_oTmtHarmTest;
	//tmt_HarmParas* m_pHarmPara;

	QTimer m_oTimerDiBian;
//	int    m_nUpdateDataFlag;
	int    m_nAutoStep;	
	//QTimer m_oTimerWave;

	int m_nCurHarmIndex;

public:
	void initUI();
	void initConnections();
	void UpdateHarmParas();
	void CopyBinaryConfig(BOOL b=TRUE);

	CSttTestResourceBase* CreateTestResource();
	virtual void UpdateTestResource(BOOL bCreateChMaps);

	virtual PTMT_PARAS_HEAD GetTestParas(){ return &m_oTmtHarmTest;};
	virtual char* GetMacroID(){ return "HarmTest"; }
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);

	virtual void OnTestResults(CDataGroup *pResults);

	virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);
	virtual void initTestParas();

	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);

	virtual void UpdateBinBoutExTab();

	virtual void OnViewTestLink(BOOL b=FALSE);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
 	virtual QWidget* GetWaveWidget();


// 	void AddWavePlot();
// 	void SetWavePlotTestResource();
// 	void SetWavePlot();
	void InitArrUIValue();
	void InitBinStateOnStarting();

	void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);

public:
    QHarmWidget *m_pHarmWidget;
    QHBoxLayout *m_pMainLayout;

signals:
	void sig_updataParas();
	void sig_SwitchParaOKClicked();

protected slots:	
	void slot_updateParas();
	void slot_SwitchStateChanged();
	void slot_LockChanged();
	void slot_GooseDataChanged();
	void slot_FT3DataChanged();
//	void slot_RepairDataChanged();

// 	void slot_pbnAddClicked();
// 	void slot_pbnMinusClicked();
	void slot_pbnAutoClicked(bool);

	/*void slot_Timer_Wave();*/
//	void slot_DiBianTimer();

//	void slot_CheckStateChanged();
	void slot_SetToZero();

	void slot_currentChangedTabWidget(int nCurrIndex);
	
};

extern QSttMacroParaEditViewHarm* g_pHarmTest;

#endif // STTMACROPARAEDITVIEWHARM_H
