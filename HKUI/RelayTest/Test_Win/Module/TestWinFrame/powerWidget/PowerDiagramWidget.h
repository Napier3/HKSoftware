#ifndef POWERDIAGRAMWIDGET_H
#define POWERDIAGRAMWIDGET_H

#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QLabel>
#include "../Module/CommonMethod/Complexp.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

namespace Ui {
	class PowerDiagramWidget;
}

class PowerDiagramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PowerDiagramWidget(QWidget *parent = 0);

	Ui::PowerDiagramWidget *ui;
	~PowerDiagramWidget();
	void InitLanuage();
	void initUI();
	void initSetFont();
	void setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource);
	void setData(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList);
	void initData();
	void initData(int nCurrentGroup);
	void setlabNumText();
	void updateData();
	void updatePowerData();
	void setlabNumVolCurText(int nModuleType);
	void setCombVolCurText(int nModuleType);
	void cmbVolCurPhaseText();
    void getLabVolCurText(QLabel *m_label);
    
	void cmbVolSetChanged();
	void cmbCurSetChanged();
	void getGroupVolPhaseEdit();
	void getGroupCurPhaseEdit();

	long getGroupCurPhaseCount();
	long getGroupVolPhaseCount();

	void TimerStart();
	void TimerStop(bool bUpdate = false);

	void setDCChanged(bool bDCTest);
	virtual void OnRtDataChanged();
	void setDC(bool bDC);
	
	void UpdateTotalPowers();
	void UpdatePowerValue(tmt_channel* pVOL,tmt_channel* pCUR,double *pPowerValue,QLineEdit *pPowerFactor_Edit,QLineEdit *pActivePower_Edit,QLineEdit *pReActivePower_Edit,QLineEdit *pAppPower_Edit);
	void GetPhaseValue(int nModuleType,tmt_Channel* pVOL,tmt_Channel* pCUR,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit,QLineEdit *pFreq_Edit);
	void GetLineValue(tmt_Channel*pA, tmt_Channel*pB,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit);
	void GetSequenceValue(int nModuleType,long nSequenceID,tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit);
	void GetResult(int nModuleType,Complex result,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit);
	void TypeSttVolCurCh(int nModuleType,CSttMacroChannel *pSttVolCurCh,float *pfAttribute);
	void getNameType(CSttMacroChannel *pSttChA,CSttMacroChannel *pSttChB,CSttMacroChannel *pSttChC,QLabel *m_labChNameA,QLabel *m_labChNameB,QLabel *m_labChNameC);

	void getPowerValueTest();
	void getVolSetChangedTest();
	void getCurSetChangedTest();
	void getGroupVolPhaseEditTest();
	void getGroupCurPhaseEditTest();

	void UpdatePowerValueTest(CSttMacroChannel *pSttVolCh,CSttMacroChannel *pSttCurCh,float *pfAttribute,double *pPowerValue,
		QLineEdit *pPowerFactor_Edit,QLineEdit *pActivePower_Edit,QLineEdit *pReActivePower_Edit,QLineEdit *pAppPower_Edit);
	void GetPhaseValueTest(int nModuleType,CSttMacroChannel *pSttVolCurCh,float *pfAttribute, QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit,QLineEdit *pFreq_Edit);
	void GetLineValueTest(CSttMacroChannel *pSttVolChA,CSttMacroChannel *pSttVolChB,float *pfAttributeA,float *pfAttributeB,QLineEdit *pVolAmp_Edit,QLineEdit *pVolAngle_Edit);
	void GetSequenceValueTest(int nModuleType,long nSequenceID,CSttMacroChannel *pSttVolCurChA,CSttMacroChannel *pSttVolCurChB,CSttMacroChannel *pSttVolCurChC
		,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
		,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit);


public slots:
		void slot_PbnNextClicked();
		void slot_PbnPreClicked();
		void slot_cmb_VolSetChanged(int index);
		void slot_cmb_CurSetChanged(int index);

protected:
//	void paintEvent(QPaintEvent *event);
	virtual void timerEvent(QTimerEvent * );

	tmt_channel* m_pVOL;//初始电压
	tmt_channel* m_pCUR;//初始电流

	CExBaseList* m_pVolChList;//全部电压通道资源索引
	CExBaseList* m_pCurChList; //全部电流通道资源索引

	int m_AllGroup;//总数组
	int m_nCurrentGroup; //当前组
	int m_nNeedUGroup;
	int m_nNeedIGroup;

	float m_fAttributeA[6];//0-电压幅值 1-电压相位 2-电压频率 3-电流幅值 4-电流相位 5-电流频率
	float m_fAttributeB[6];
	float m_fAttributeC[6];
	double m_fPowerValues[3][4];//功率相关数值

	QString m_strChNameA,m_strChNameB,m_strChNameC;
	long m_nTimerID;
	CSttTestResourceBase *m_pPowerSttTestResource;
	Complex *m_pPowerComplex;
	Complex m_oCompA,m_oCompB,m_oCompC/*,alpha*/;

	bool m_bDCTest;

};


#endif // POWERDIAGRAMWIDGET_H



