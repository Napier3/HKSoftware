#ifndef QSTTMACROPARAEDITVIEWSWING_H
#define QSTTMACROPARAEDITVIEWSWING_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include <QWidget>
#include "SwingTestParasDlg.h"
#include "SwingResultEvalDlg.h"
#include "SwingSysDiagramWidget.h"
#include "SwingImpChartWidget.h"
#include "../../SttTest/Common/Swing/tmt_swing_test.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"

#define PANGLESTART_MIN 0
#define PANGLESTART_MAX 360
#define PANGLEEND_MIN 0
#define PANGLEEND_MAX 360
#define Z1_MIN 0
#define Z1_MAX 999999
#define SWINGCYCLE_MIN 0
#define SWINGCYCLE_MAX 999999
#define ISET1_MIN 0
#define ISET1_MAX 20
#define SWINGCOUNT_MIN 1
#define SWINGCOUNT_MAX 999999
#define FAULTTIME_MIN 0
#define FAULTTIME_MAX 999999
#define EMENRATE_MIN 0
#define EMENRATE_MAX 2
#define AMPLITUDE_MIN 0
#define AMPLITUDE_MAX 999999
#define PHASE_MIN 0
#define PHASE_MAX 360

namespace Ui {
class QSttMacroParaEditViewSwing;
}

class QSttMacroParaEditViewSwing : public CSttMacroParaEditViewOriginal
{
    Q_OBJECT

public:
    explicit QSttMacroParaEditViewSwing(QWidget *parent = 0);
    ~QSttMacroParaEditViewSwing();
    void InitUI();
	void UpdateParas();
	virtual void InitLanuage();
	virtual char* GetMacroID(){ return "SwingTest"; }
	virtual PTMT_PARAS_HEAD GetTestParas() { return m_pCurTest;}
    virtual void SetDatas(CDataGroup *pParas);
    virtual void GetDatas(CDataGroup *pParas);
	virtual void startInit();
	virtual void stopInit();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void ShowReport(CDvmValues *pValues);
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	virtual void UpdateTestResource(BOOL bCreateChMaps);
    virtual QWidget* GetSystemDiagramWidget(){ return m_pSysDiagramWidget; }//获取模块中的系统图窗口指针

public:
    QSwingTestParasDlg *m_pParasDlg;
    QSwingResultEvalDlg *m_pResultEvalDlg;
	QSwingImpChartWidget *m_pImpChart;
    QSwingSysDiagramWidget *m_pSysDiagramWidget;
	CDataGroup *m_pCurrDataGroup;
	QGooseParaWidget* m_pGooseParaWidget;
	tmt_SwingTest *m_pCurTest;

private slots:
    void on_Refault_Check_StateChanged(int state);
    void on_Dzdt_Check_StateChanged(int state);
    void on_Reciprocating_Check_StateChanged(int state);
    void on_m_btnResultEval_clicked();
    void on_m_btnTestParas_clicked();
	void on_DataChanged();
    void on_m_editPAngleStart_editingFinished();
    void on_m_editPAngleEnd_editingFinished();
    void on_m_editSwingCycle_editingFinished();
    void on_m_editSwingCount_editingFinished();
    void on_m_editEmEnRate_editingFinished();
    void on_m_editZ1_editingFinished();
    void on_m_editISet1_editingFinished();
    void on_m_editFaultTime_editingFinished();
    void on_m_editAmplitude_editingFinished();
    void on_m_editPhase_editingFinished();
    void on_m_editDzdt_editingFinished();
    void on_m_cbbK0Mode_currentIndexChanged(int index);
    void on_m_cbbFaultType_currentIndexChanged(int index);
    void on_m_cbbTripPoint_currentIndexChanged(int index);

private:
    Ui::QSttMacroParaEditViewSwing *ui;
};

#endif // QSTTMACROPARAEDITVIEWSWING_H
