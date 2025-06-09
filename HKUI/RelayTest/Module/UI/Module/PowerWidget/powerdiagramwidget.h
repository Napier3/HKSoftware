#ifndef POWERDIAGRAMWIDGET_H
#define POWERDIAGRAMWIDGET_H

#include <QWidget>
#include <complex>
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../Module/SttTestBase/SttComplexp.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>

#include "../ScrollCtrl/ScrollComboBox.h"
#include "../../Controls/SttLineEdit.h"


class PowerDiagramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PowerDiagramWidget(QWidget *parent = 0);

    ~PowerDiagramWidget();

	void setControlFont();
	void setButtonImage();
    void setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource);
	void setData(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList);
	void initData();
	void initData(int nCurrentGroup);
	//void updateData();
	void setlabNumText(QString str);
	CString getAllCurGroupStr();
	void initChannelData();
	void updatePowerData();
	void setlabNumVolText();
	void setlabNumCurText();
	void setCombVolText();
	void setCombCurText();
	void cmbVolCurPhaseText();

	void cmbVolSetChanged();
	void cmbCurSetChanged();
	void getGroupVolPhaseEdit();
	void getGroupCurPhaseEdit();
	
	void getPowerValueTest();
	void getVolSetChangedTest();
	void getCurSetChangedTest();
	void getGroupVolPhaseEditTest();
	void getGroupCurPhaseEditTest();
	
	long getGroupCurPhaseCount();
	long getGroupVolPhaseCount();
	
	//void TimerStart();
	//void TimerStop(bool bUpdate = false);

	void SetComboBoxItemText();
	void setShowVolCurPhaseEdit();//显示U0/I0cl20230720

	void InitUI();
	void InitComboBoxData();
	void SetEnabled_Alignment();
	void InitLanuage();

public:

	QVBoxLayout *m_pMainVLayout;
	QHBoxLayout *m_pHLayoutcur_Vol;

	QGridLayout *VolGridLayout;
	QLabel *m_labVolAmplitude;
	QLabel *m_labVolFrequency;
	QLabel *m_labVolPhase;
	QLabel *m_labVa;
	QSttLineEdit *m_editVa1;
	QSttLineEdit *m_editVa0;
	QSttLineEdit *m_editVa2;
	QSttLineEdit *m_editVb0;
	QSttLineEdit *m_editVb1;
	QLabel *m_labVb;
	QSttLineEdit *m_editVb2;
	QSttLineEdit *m_editVc0;
	QLabel *m_labVc;
	QSttLineEdit *m_editVc1;
	QSttLineEdit *m_editVc2;
	QSttLineEdit *m_editV0;
	QSttLineEdit *m_editV1;
	QSttLineEdit *m_editV2;
	QLabel *m_labV0;

	QGridLayout *CurGridLayout;
	QLabel *m_labCurAmplitude;
	QLabel *m_labCurFrequency;
	QSttLineEdit *m_editIa0;
	QLabel *m_labIa;
	QLabel *m_labCurPhase;
	QSttLineEdit *m_editIa1;
	QSttLineEdit *m_editIa2;
	QLabel *m_labIc;
	QSttLineEdit *m_editIc2;
	QSttLineEdit *m_editIb0;
	QSttLineEdit *m_editIb2;
	QSttLineEdit *m_editIb1;
	QLabel *m_labIb;
	QSttLineEdit *m_editIc1;
	QSttLineEdit *m_editIc0;
	QSttLineEdit *m_editI0;
	QSttLineEdit *m_editI1;
	QSttLineEdit *m_editI2;
	QLabel *m_labI0;
	QHBoxLayout *horizontalLayout_3;
	QWidget *Powerwidget;
 
	QGridLayout *PowerGridLayout;
	QLabel *m_lblAPhase;
	QLabel *m_lblTotalPower;
	QLabel *m_lblBPhase;
	QLabel *m_lblCPhase;
	QSttLineEdit *m_editAPhase0;
	QLabel *m_lblPowerFactor;
	QSttLineEdit *m_editBPhase0;
	QSttLineEdit *m_editCPhase0;
	QSttLineEdit *m_editBPhase1;
	QSttLineEdit *m_editCPhase1;
	QSttLineEdit *m_editTotalPower0;
	QSttLineEdit *m_editAPhase1;
	QSttLineEdit *m_editBPhase2;
	QSttLineEdit *m_editAPhase2;
	QSttLineEdit *m_editCPhase2;
	QLabel *m_lblReactivePower;
	QSttLineEdit *m_editAPhase3;
	QSttLineEdit *m_editTotalPower1;
	QLabel *m_lblApparentPower;
	QSttLineEdit *m_editBPhase3;
	QSttLineEdit *m_editCPhase3;
	QSttLineEdit *m_editTotalPower2;
	QLabel *m_lblActivePower;

	QVBoxLayout *verticalLayout_3;

	QVBoxLayout *verticalLayout_2;
	QLabel *m_labNum;
	
	QHBoxLayout *m_pBtnHLayout;
	QPushButton *m_pbnPre;
	QPushButton *m_pbnNext;
	QGridLayout *gridLayout;
	QLabel *m_lblVolSet;
	QScrollComboBox *m_combVolSet;
	QLabel *m_lblCurSet;
	QScrollComboBox *m_combCurSet;

public slots:
	void slot_PbnNextClicked();
	void slot_PbnPreClicked();
	void slot_cmb_VolSetChanged(int index);
	void slot_cmb_CurSetChanged(int index);

protected:
	void paintEvent(QPaintEvent *event);
	//virtual void timerEvent(QTimerEvent * );

	void UpdateTotalPowers();
	void UpdatePowerValue(tmt_channel* pVOL,tmt_channel* pCUR,double *pPowerValue,QLineEdit *pPowerFactor_Edit,QLineEdit *pActivePower_Edit,QLineEdit *pReActivePower_Edit,QLineEdit *pAppPower_Edit);
	void GetPhaseVolValue(tmt_channel* pVOL,QLineEdit *pAmpVol_Edit,QLineEdit *pAngleVol_Edit,QLineEdit *pFreqVol_Edit);
	void GetPhaseCurValue(tmt_Channel* pCUR,QLineEdit *pAmpCur_Edit,QLineEdit *pAngleCur_Edit,QLineEdit *pFreqCur_Edit);
	void GetLineVolValue(tmt_Channel*pA, tmt_Channel*pB,QLineEdit *pAmpVol_Edit,QLineEdit *pAngleVol_Edit);
	void GetPositiveSeqValue(tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit);
	void GetNegativeSeqValue(tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit);
	void GetZeroSeqValue(tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC,QLineEdit *pAmp_Edit,QLineEdit *pAnglel_Edit);
	
  
	void UpdatePowerValueTest(CSttMacroChannel *pSttVolCh,CSttMacroChannel *pSttCurCh,float *pfAttribute,double *pPowerValue,
		QLineEdit *pPowerFactor_Edit,QLineEdit *pActivePower_Edit,QLineEdit *pReActivePower_Edit,QLineEdit *pAppPower_Edit);
	void UpdateVolValue(CSttMacroChannel *pSttVolCh,float *pfAttribute, QLineEdit *pAmpVol_Edit,QLineEdit *pAngleVol_Edit,QLineEdit *pFreqVol_Edit);
	void UpdateCurValue(CSttMacroChannel *pSttCurCh,float *pfAttribute, QLineEdit *pAmpCur_Edit,QLineEdit *pAngleCur_Edit,QLineEdit *pFreqCur_Edit);
	void UpdateVolPositiveSeqValueTest(CSttMacroChannel *pSttVolChA,CSttMacroChannel *pSttVolChB,CSttMacroChannel *pSttVolChC
		                              ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
		                              ,QLineEdit *pVolAmp_Edit,QLineEdit *pVolAngle_Edit);
	void UpdateVolNegativeSeqValueTest(CSttMacroChannel *pSttVolChA,CSttMacroChannel *pSttVolChB,CSttMacroChannel *pSttVolChC
		                               ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
		                               ,QLineEdit *pVolAmp_Edit,QLineEdit *pVolAngle_Edit);
	void UpdateVolZeroSeqValueTest(CSttMacroChannel *pSttVolChA,CSttMacroChannel *pSttVolChB,CSttMacroChannel *pSttVolChC
		                               ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
		                               ,QLineEdit *pVolAmp_Edit,QLineEdit *pVolAngle_Edit);
	void UpdateVolLineValueTest(CSttMacroChannel *pSttVolChA,CSttMacroChannel *pSttVolChB
		                       ,float *pfAttributeA,float *pfAttributeB
		                       ,QLineEdit *pVolAmp_Edit,QLineEdit *pVolAngle_Edit);

	void UpdateCurPositiveSeqValueTest(CSttMacroChannel *pSttCurChA,CSttMacroChannel *pSttCurChB,CSttMacroChannel *pSttCurChC
		                              ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
		                              ,QLineEdit *pCurAmp_Edit,QLineEdit *pCurAngle_Edit);
	void UpdateCurNegativeSeqValueTest(CSttMacroChannel *pSttCurChA,CSttMacroChannel *pSttCurChB,CSttMacroChannel *pSttCurChC
		                              ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
		                              ,QLineEdit *pCurAmp_Edit,QLineEdit *pCurAngle_Edit);
	void UpdateCurZeroSeqValueTest(CSttMacroChannel *pSttCurChA,CSttMacroChannel *pSttCurChB,CSttMacroChannel *pSttCurChC
		                          ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
		                          ,QLineEdit *pCurAmp_Edit,QLineEdit *pCurAngle_Edit);


	
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
	float m_fAttribute0[6];
	double m_fPowerValues[3][4];//功率相关数值

	QString m_strChNameA,m_strChNameB,m_strChNameC,m_strChName0;
	//long m_nTimerID;
	CSttTestResourceBase *m_pPowerSttTestResource;
	Complex *m_pPowerComplex;
	Complex m_oCompA,m_oCompB,m_oCompC/*,alpha*/;
};


#endif // POWERDIAGRAMWIDGET_H


