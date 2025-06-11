#ifndef STTMACROPARAEDITVIEWFREQOUTPUT_H
#define STTMACROPARAEDITVIEWFREQOUTPUT_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../../SttTest/Common/Distribution/tmt_freqoutput_test.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QGroupBox>
#include "../Controls/SttCheckBox.h"
#include <QTabWidget>
#include "FreqOutPutTable.h"
#include "FreqFileWidget.h"

class QSttMacroParaEditViewFreqOutput: public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewFreqOutput(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewFreqOutput();

public:
	virtual CSttTestResourceBase* CreateTestResource();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual PTMT_PARAS_HEAD GetTestParas(){ return &m_oTmtFreqOutputTest;};
	virtual char* GetMacroID(){ return STT_ORG_MACRO_FreqOutputTest; }
	virtual void UpdateTestResource(BOOL bCreateChMaps);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	void InitUI();
	void InitData();
	void InitConnect();

private:
	tmt_FreqOutputTest m_oTmtFreqOutputTest;
	tmt_FreqOutputParas *m_pFreqOutputParas;
	QFreqOutPutWidget *m_pFreqOutPutTable;//电压电流表格
	QFreqFileWidget *m_pFreqFileWidget;//频率文件
	QTabWidget *m_pTabWidget;
	QRadioButton *m_OutPutTypeBtn[3];//0=电压电流 1=直流信号源 2=转速脉冲信号
	QComboBox *m_pPulseSignalCombox;//脉冲信号
	QSttLineEdit *m_pPulseWidthEdit;//脉冲宽度
	QComboBox *m_pPeakValueCombox;	//峰峰值
	//Idc1,Idc2
	QSttCheckBox *m_pIdc1CheckBox;
	QSttCheckBox *m_pIdc2CheckBox;
	QGroupBox *m_pSpeedPulseGroup;
	QGroupBox *m_pDCSourceGroup;

private slots:
    void slot_OutPutTypeRadioChanged(bool bValue);
	void slot_PulseWidthEditChanged();
	void slot_TabWidgetChangedTabWidget(int nIndex);
	void slot_Idc1CheckStateChanged(int nState);
	void slot_Idc2CheckStateChanged(int nState);
	void slot_PulseSignalCombCurrentIndexChanged(int index);
	void slot_PeakValueCombCurrentIndexChanged(int index);
	void slot_updateParas();


};
extern QSttMacroParaEditViewFreqOutput* g_pFreqOutputTest;
#endif 
