#include "powerdiagramwidget.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../SttTestCntrFrameAPI.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/XLanguageResource.h"
#include <math.h>
#include <QPainter>
#include <QPaintEvent>

#define  STT_POWER_VolSetType_LN                0 // 相电压
#define  STT_POWER_VolSetType_LL                1//线电压
#define  STT_POWER_VolSetType_SE                2//电压序分量

#define  STT_POWER_CurSetType_LN                0 // 相电流
#define  STT_POWER_CurSetType_SE                1 // 电流序分量

CString FormatAngleString(float fAngle)
{
	CString strText;
#ifdef _PSX_QT_WINDOWS_
	strText.Format(_T("%.3f"), fAngle);
	strText += QString::fromLocal8Bit("°");
#else
	strText.Format(_T("%.3f°"), fAngle);
#endif // _PSX_QT_WINDOWS_

	return strText;
}

PowerDiagramWidget::PowerDiagramWidget(QWidget *parent) :
    QWidget(parent)
{
	m_AllGroup = 0;
	m_nNeedUGroup = 0;
	m_nNeedIGroup = 0;
	m_nCurrentGroup = 0;
	m_pVOL = NULL;
	m_pCUR = NULL;
	m_pPowerSttTestResource = NULL;
	m_pVolChList = NULL;
	m_pCurChList = NULL;
	setFocusPolicy(Qt::NoFocus);

	for (int nChIndex = 0;nChIndex<3;nChIndex++)
	{
		for (int nPowerIndex = 0;nPowerIndex<4;nPowerIndex++)
		{
			m_fPowerValues[nChIndex][nPowerIndex] = 0.0f;
		}
	}

	InitUI();
	InitLanuage();
	InitComboBoxData();
	SetEnabled_Alignment();
	
	setButtonImage();
	setControlFont();
	setlabNumVolText();
	setlabNumCurText();
	setCombVolText();
	setCombCurText();
	SetComboBoxItemText();

	//m_nTimerID = -1;

	connect(m_pbnNext,SIGNAL(clicked()),this,SLOT(slot_PbnNextClicked()));
	connect(m_pbnPre,SIGNAL(clicked()),this,SLOT(slot_PbnPreClicked()));
	connect(m_combVolSet,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_VolSetChanged(int)));
	connect(m_combCurSet,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_CurSetChanged(int)));

}


PowerDiagramWidget::~PowerDiagramWidget()
{
    //delete ui;
}

void PowerDiagramWidget::InitUI()
{
	VolGridLayout = new QGridLayout();
	VolGridLayout->setContentsMargins(10, 10, 10, 10);
	VolGridLayout->setSpacing(20);

	m_labVolAmplitude = new QLabel(g_sLangTxt_Native_Amplitude);
	m_labVolPhase = new QLabel(g_sLangTxt_Native_Phase);
	m_labVolFrequency = new QLabel(g_sLangTxt_Native_Freq);
    
	m_labVa = new QLabel();
	m_editVa0 = new QSttLineEdit();
	m_editVa1 = new QSttLineEdit();
	m_editVa2 = new QSttLineEdit();	

	m_labVb = new QLabel();
	m_editVb0 = new QSttLineEdit();
	m_editVb1 = new QSttLineEdit();
	m_editVb2 = new QSttLineEdit();

	m_labVc = new QLabel();
	m_editVc0 = new QSttLineEdit();
	m_editVc1 = new QSttLineEdit();
	m_editVc2 = new QSttLineEdit();

	m_labV0 = new QLabel();
	m_editV0 = new QSttLineEdit();
	m_editV1 = new QSttLineEdit();
	m_editV2 = new QSttLineEdit();


	VolGridLayout->addWidget(m_labVolAmplitude, 0, 1, 1, 1);
	VolGridLayout->addWidget(m_labVolPhase, 0, 2, 1, 1);
	VolGridLayout->addWidget(m_labVolFrequency, 0, 3, 1, 1);

	VolGridLayout->addWidget(m_labVa, 1, 0, 1, 1);
	VolGridLayout->addWidget(m_editVa0, 1, 1, 1, 1);
	VolGridLayout->addWidget(m_editVa1, 1, 2, 1, 1);	
	VolGridLayout->addWidget(m_editVa2, 1, 3, 1, 1);

	VolGridLayout->addWidget(m_labVb, 2, 0, 1, 1);
	VolGridLayout->addWidget(m_editVb0, 2, 1, 1, 1);	
	VolGridLayout->addWidget(m_editVb1, 2, 2, 1, 1);	
	VolGridLayout->addWidget(m_editVb2, 2, 3, 1, 1);	

	VolGridLayout->addWidget(m_labVc, 3, 0, 1, 1);
	VolGridLayout->addWidget(m_editVc0, 3, 1, 1, 1);
	VolGridLayout->addWidget(m_editVc1, 3, 2, 1, 1);
	VolGridLayout->addWidget(m_editVc2, 3, 3, 1, 1);

	VolGridLayout->addWidget(m_labV0, 4, 0, 1, 1);
	VolGridLayout->addWidget(m_editV0, 4, 1, 1, 1);
	VolGridLayout->addWidget(m_editV1, 4, 2, 1, 1);	
	VolGridLayout->addWidget(m_editV2, 4, 3, 1, 1);
	
	CurGridLayout = new QGridLayout();
	CurGridLayout->setContentsMargins(10, 10, 10, 10);
	CurGridLayout->setSpacing(20);

	m_labCurAmplitude = new QLabel(g_sLangTxt_Native_Amplitude);
	m_labCurPhase = new QLabel(g_sLangTxt_Native_Phase);
	m_labCurFrequency = new QLabel(g_sLangTxt_Native_Freq);

	m_labIa = new QLabel();
	m_editIa0 = new QSttLineEdit();
	m_editIa1 = new QSttLineEdit();
	m_editIa2 = new QSttLineEdit();

	m_labIb = new QLabel();
	m_editIb0 = new QSttLineEdit();
	m_editIb1 = new QSttLineEdit();
	m_editIb2 = new QSttLineEdit();

	m_labIc = new QLabel();
	m_editIc0 = new QSttLineEdit();;
	m_editIc1 = new QSttLineEdit();
	m_editIc2 = new QSttLineEdit();

	m_labI0 = new QLabel();
	m_editI0 = new QSttLineEdit();
	m_editI1 = new QSttLineEdit();
	m_editI2 = new QSttLineEdit();

	CurGridLayout->addWidget(m_labCurAmplitude, 0, 1, 1, 1);
	CurGridLayout->addWidget(m_labCurPhase, 0, 2, 1, 1);
	CurGridLayout->addWidget(m_labCurFrequency, 0, 3, 1, 1);	

	CurGridLayout->addWidget(m_labIa, 1, 0, 1, 1);
	CurGridLayout->addWidget(m_editIa0, 1, 1, 1, 1);
	CurGridLayout->addWidget(m_editIa1, 1, 2, 1, 1);
	CurGridLayout->addWidget(m_editIa2, 1, 3, 1, 1);

	CurGridLayout->addWidget(m_labIb, 2, 0, 1, 1);
	CurGridLayout->addWidget(m_editIb0, 2, 1, 1, 1);
	CurGridLayout->addWidget(m_editIb1, 2, 2, 1, 1);
	CurGridLayout->addWidget(m_editIb2, 2, 3, 1, 1);

	CurGridLayout->addWidget(m_labIc, 3, 0, 1, 1);
	CurGridLayout->addWidget(m_editIc0, 3, 1, 1, 1);
	CurGridLayout->addWidget(m_editIc1, 3, 2, 1, 1);
	CurGridLayout->addWidget(m_editIc2, 3, 3, 1, 1);

	CurGridLayout->addWidget(m_labI0, 4, 0, 1, 1);
	CurGridLayout->addWidget(m_editI0, 4, 1, 1, 1);
	CurGridLayout->addWidget(m_editI1, 4, 2, 1, 1);
	CurGridLayout->addWidget(m_editI2, 4, 3, 1, 1);	

	m_pHLayoutcur_Vol = new QHBoxLayout();
	m_pHLayoutcur_Vol->addLayout(VolGridLayout);
	m_pHLayoutcur_Vol->addLayout(CurGridLayout);


	horizontalLayout_3 = new QHBoxLayout();

	Powerwidget = new QWidget();
	PowerGridLayout = new QGridLayout();
	PowerGridLayout->setContentsMargins(1, 1, 1, 1);
	PowerGridLayout->setSpacing(20);

	m_lblAPhase = new QLabel(g_sLangTxt_Aphase);
	m_lblBPhase = new QLabel(g_sLangTxt_Bphase);
	m_lblCPhase = new QLabel(g_sLangTxt_Cphase);
	m_lblTotalPower = new QLabel(g_sLangTxt_Native_TotalPow);

	m_lblPowerFactor = new QLabel(g_sLangTxt_Native_PowFactor);
	m_editAPhase0 = new QSttLineEdit();
	m_editBPhase0 = new QSttLineEdit();
	m_editCPhase0 = new QSttLineEdit();
	
	m_lblActivePower = new QLabel(g_sLangTxt_Native_Power);
	m_editAPhase1 = new QSttLineEdit();
	m_editBPhase1 = new QSttLineEdit();
	m_editCPhase1 = new QSttLineEdit();
	m_editTotalPower0 = new QSttLineEdit();
	
	m_lblReactivePower = new QLabel(g_sLangTxt_Native_ReactivePow);
	m_editAPhase2 = new QSttLineEdit();
	m_editBPhase2 = new QSttLineEdit();
	m_editCPhase2 = new QSttLineEdit();
	m_editTotalPower1 = new QSttLineEdit();

	m_lblApparentPower = new QLabel(g_sLangTxt_Native_ApparentPow);
	m_editAPhase3= new QSttLineEdit();
	m_editBPhase3 = new QSttLineEdit();
	m_editCPhase3 = new QSttLineEdit();
	m_editTotalPower2 = new QSttLineEdit();

	//m_editAPhase0->setMinimumSize(QSize(100, 30));
	//m_editBPhase0->setMinimumSize(QSize(100, 30));
	//m_editCPhase0->setMinimumSize(QSize(100, 30));
	//m_editAPhase1->setMinimumSize(QSize(100, 30));
	//m_editBPhase1->setMinimumSize(QSize(100, 30));
	//m_editCPhase1->setMinimumSize(QSize(100, 30));
	//m_editTotalPower0->setMinimumSize(QSize(100, 30));

	//m_editAPhase2->setMinimumSize(QSize(100, 30));
	//m_editBPhase2->setMinimumSize(QSize(100, 30));
	//m_editCPhase2->setMinimumSize(QSize(100, 30));
	//m_editTotalPower1->setMinimumSize(QSize(100, 30));
	//m_editAPhase3->setMinimumSize(QSize(100, 30));
	//m_editBPhase3->setMinimumSize(QSize(100, 30));
	//m_editCPhase3->setMinimumSize(QSize(100, 30));
	//m_editTotalPower2->setMinimumSize(QSize(100, 30));

	PowerGridLayout->addWidget(m_lblAPhase, 0, 1, 1, 1);
	PowerGridLayout->addWidget(m_lblBPhase, 0, 2, 1, 1);
	PowerGridLayout->addWidget(m_lblCPhase, 0, 3, 1, 1);
	PowerGridLayout->addWidget(m_lblTotalPower, 0, 4, 1, 1);
	
	PowerGridLayout->addWidget(m_lblPowerFactor, 1, 0, 1, 1);
	PowerGridLayout->addWidget(m_editAPhase0, 1, 1, 1, 1);
	PowerGridLayout->addWidget(m_editBPhase0, 1, 2, 1, 1);
	PowerGridLayout->addWidget(m_editCPhase0, 1, 3, 1, 1);	

	PowerGridLayout->addWidget(m_lblActivePower, 2, 0, 1, 1);
	PowerGridLayout->addWidget(m_editAPhase1, 2, 1, 1, 1);
	PowerGridLayout->addWidget(m_editBPhase1, 2, 2, 1, 1);
	PowerGridLayout->addWidget(m_editCPhase1, 2, 3, 1, 1);	
	PowerGridLayout->addWidget(m_editTotalPower0, 2, 4, 1, 1);

	PowerGridLayout->addWidget(m_lblReactivePower, 3, 0, 1, 1);
	PowerGridLayout->addWidget(m_editAPhase2, 3, 1, 1, 1);
	PowerGridLayout->addWidget(m_editBPhase2, 3, 2, 1, 1);
	PowerGridLayout->addWidget(m_editCPhase2, 3, 3, 1, 1);
	PowerGridLayout->addWidget(m_editTotalPower1, 3, 4, 1, 1);

	PowerGridLayout->addWidget(m_lblApparentPower, 4, 0, 1, 1);
	PowerGridLayout->addWidget(m_editAPhase3, 4, 1, 1, 1);
	PowerGridLayout->addWidget(m_editBPhase3, 4, 2, 1, 1);
	PowerGridLayout->addWidget(m_editCPhase3, 4, 3, 1, 1);	
	PowerGridLayout->addWidget(m_editTotalPower2, 4, 4, 1, 1);	


	m_labNum = new QLabel();

	m_pBtnHLayout = new QHBoxLayout();
	m_pbnPre = new QPushButton();
	m_pbnNext = new QPushButton();

	m_pBtnHLayout->addWidget(m_pbnPre);
	m_pBtnHLayout->addWidget(m_pbnNext);
	
	verticalLayout_2 = new QVBoxLayout();
	verticalLayout_2->addWidget(m_labNum);
	verticalLayout_2->addStretch();
	verticalLayout_2->addLayout(m_pBtnHLayout);

	gridLayout = new QGridLayout();
	gridLayout->setContentsMargins(1, 1, 1, 1);
	gridLayout->setSpacing(20);


	m_lblVolSet = new QLabel(g_sLangTxt_Gradient_VoltageSet);
	m_combVolSet = new QScrollComboBox();
	m_lblCurSet = new QLabel(g_sLangTxt_Gradient_CurrentSet);
	m_combCurSet = new QScrollComboBox();

	gridLayout->addWidget(m_lblVolSet, 0, 0, 1, 1);
	gridLayout->addWidget(m_combVolSet, 0, 1, 1, 1);
	gridLayout->addWidget(m_lblCurSet, 1, 0, 1, 1);
	gridLayout->addWidget(m_combCurSet, 1, 1, 1, 1);

	m_combVolSet->setMinimumWidth(115);
	m_combCurSet->setMinimumWidth(115);		//20240507 xueyangfan 功率图显示不全

	verticalLayout_3 = new QVBoxLayout();
	verticalLayout_3->addLayout(gridLayout);
	verticalLayout_3->addStretch();
	verticalLayout_3->addLayout(verticalLayout_2);
	
	
	horizontalLayout_3->addLayout(PowerGridLayout);
	horizontalLayout_3->addLayout(verticalLayout_3);
	
	Powerwidget->setLayout(horizontalLayout_3);

	m_pMainVLayout = new QVBoxLayout();
	m_pMainVLayout->addStretch();
	m_pMainVLayout->addLayout(m_pHLayoutcur_Vol);
	m_pMainVLayout->addStretch();
	m_pMainVLayout->addWidget(Powerwidget);
	m_pMainVLayout->addStretch();

	this->setLayout(m_pMainVLayout);


	m_editV0->hide();
	m_editV1->hide();
	m_editV2->hide();
	m_labV0->hide();

	m_editI0->hide();
	m_editI1->hide();
	m_editI2->hide();
	m_labI0->hide();

	// 20230907 suyang 注销

	// 	//20230815  表格增加左间距 lcq
	//  	PowerGridLayout->setContentsMargins(30, 0, 0, 0);
	// 
	// 	m_lblPowerFactor->setMinimumSize(QSize(120, 30));
	// 	m_lblPowerFactor->setMaximumSize(QSize(120, 30));
	// 
	// 	m_lblActivePower->setMinimumSize(QSize(120, 30)); 
	// 	m_lblActivePower->setMaximumSize(QSize(120, 30));
	// 	
	// 	m_lblReactivePower->setMinimumSize(QSize(120, 30));
	// 	m_lblReactivePower->setMaximumSize(QSize(120, 30));
	// 
	// 	m_lblApparentPower->setMinimumSize(QSize(120, 30));
	// 	m_lblApparentPower->setMaximumSize(QSize(120, 30));

}

void PowerDiagramWidget::InitLanuage()
{
	xlang_SetLangStrToWidget_Txt(m_labVolAmplitude,g_sLangTxt_Native_Amplitude,XLang_Ctrls_QLabel);//lcq
	xlang_SetLangStrToWidget_Txt(m_labVolPhase,g_sLangTxt_Native_Phase,XLang_Ctrls_QLabel);//lcq
	xlang_SetLangStrToWidget_Txt(m_labVolFrequency,g_sLangTxt_Native_Freq,XLang_Ctrls_QLabel);//lcq
	xlang_SetLangStrToWidget_Txt(m_labCurAmplitude,g_sLangTxt_Native_Amplitude,XLang_Ctrls_QLabel);//lcq
	xlang_SetLangStrToWidget_Txt(m_labCurPhase,g_sLangTxt_Native_Phase,XLang_Ctrls_QLabel);//lcq
	xlang_SetLangStrToWidget_Txt(m_labCurFrequency,g_sLangTxt_Native_Freq,XLang_Ctrls_QLabel);//lcq

	xlang_SetLangStrToWidget_Txt(m_lblPowerFactor,g_sLangTxt_Native_PowFactor,XLang_Ctrls_QLabel);//lcq 功率因数
	xlang_SetLangStrToWidget_Txt(m_lblActivePower,g_sLangTxt_Native_Power,XLang_Ctrls_QLabel);//lcq 有功功率
	xlang_SetLangStrToWidget_Txt(m_lblReactivePower,g_sLangTxt_Native_ReactivePow,XLang_Ctrls_QLabel);//lcq 无功功率
	xlang_SetLangStrToWidget_Txt(m_lblApparentPower,g_sLangTxt_Native_ApparentPow,XLang_Ctrls_QLabel);//lcq 视在功率

	xlang_SetLangStrToWidget_Txt(m_lblAPhase,g_sLangTxt_Aphase,XLang_Ctrls_QLabel);//lcq 
	xlang_SetLangStrToWidget_Txt(m_lblBPhase,g_sLangTxt_Bphase,XLang_Ctrls_QLabel);//lcq 
	xlang_SetLangStrToWidget_Txt(m_lblCPhase,g_sLangTxt_Cphase,XLang_Ctrls_QLabel);//lcq 
	xlang_SetLangStrToWidget_Txt(m_lblTotalPower,g_sLangTxt_Native_TotalPow,XLang_Ctrls_QLabel);//lcq 

	xlang_SetLangStrToWidget_Txt(m_lblVolSet,g_sLangTxt_Gradient_VoltageSet,XLang_Ctrls_QLabel);//lcq 电压设置
	xlang_SetLangStrToWidget_Txt(m_lblCurSet,g_sLangTxt_Gradient_CurrentSet,XLang_Ctrls_QLabel);//lcq 电流设置

}
void PowerDiagramWidget::InitComboBoxData()
{
	m_combVolSet->addItem(g_sLangTxt_Native_VolSetTypeLN);
	m_combVolSet->addItem(g_sLangTxt_Native_VolSetTypeLL);
	m_combVolSet->addItem(g_sLangTxt_Native_VolSetTypeSE);

	m_combCurSet->addItem(g_sLangTxt_Native_CurSetTypeLN);
	m_combCurSet->addItem(g_sLangTxt_Native_CurSetTypeSE);

}

void PowerDiagramWidget::SetEnabled_Alignment()
{
// 	m_labVolAmplitude->setEnabled(false);
// 	m_labVolFrequency->setEnabled(false);
// 	m_labVolPhase->setEnabled(false);
// 	m_labVa->setEnabled(false);
// 	 m_editVa1->setEnabled(false);
// 	m_editVa0->setEnabled(false);
// 	m_editVa2->setEnabled(false);
// 	m_editVb0->setEnabled(false);
// 	m_editVb1->setEnabled(false);
// 	m_labVb->setEnabled(false);
// 	m_editVb2->setEnabled(false);
// 	m_editVc0->setEnabled(false);
// 	 m_labVc->setEnabled(false);
// 	m_editVc1->setEnabled(false);
// 	m_editVc2->setEnabled(false);
// 	 m_editV0->setEnabled(false);
// 	 m_editV1->setEnabled(false);
// 	m_editV2->setEnabled(false);
// 	m_labV0->setEnabled(false);
// 	m_labCurFrequency->setEnabled(false);
// 	m_editIa0->setEnabled(false);
// 	m_labIa->setEnabled(false);
// 	m_editIa1->setEnabled(false);
// 	m_editIa2->setEnabled(false);
// 	m_labIc->setEnabled(false);
// 	m_editIc2->setEnabled(false);
// 	m_editIb0->setEnabled(false);
// 	m_editIb2->setEnabled(false);
// 	m_editIb1->setEnabled(false);
// 	m_labIb->setEnabled(false);
// 	m_editIc1->setEnabled(false);
// 	m_editIc0->setEnabled(false);
// 	m_editI0->setEnabled(false);
// 	m_editI1->setEnabled(false);
// 	m_editI2->setEnabled(false);
// 	m_labI0->setEnabled(false);
// 	m_lblAPhase->setEnabled(false);
// 	m_lblTotalPower->setEnabled(false);
// 	m_lblBPhase->setEnabled(false);
// 	m_lblCPhase->setEnabled(false);
// 	m_editAPhase0->setEnabled(false);
// 	m_lblPowerFactor->setEnabled(false);
// 	m_editBPhase0->setEnabled(false);
// 	m_editCPhase0->setEnabled(false);
// 	m_editBPhase1->setEnabled(false);
// 	m_editCPhase1->setEnabled(false);
// 	m_editTotalPower0->setEnabled(false);
// 	m_editAPhase1->setEnabled(false);
// 	m_editBPhase2->setEnabled(false);
// 	m_editAPhase2->setEnabled(false);
// 	m_editCPhase2->setEnabled(false);
// 	m_lblReactivePower->setEnabled(false);
// 	m_editAPhase3->setEnabled(false);
// 	m_editTotalPower1->setEnabled(false);
// 	m_lblApparentPower->setEnabled(false);
// 	m_editBPhase3->setEnabled(false);
// 	m_editCPhase3->setEnabled(false);
// 	m_editTotalPower2->setEnabled(false);
// 	m_lblActivePower->setEnabled(false);
// 	m_labNum->setEnabled(false);
// 	m_lblVolSet->setEnabled(false);
// 	m_lblCurSet->setEnabled(false);
// 	m_labCurAmplitude->setEnabled(false);
// 	m_labCurPhase->setEnabled(false);


	m_editVa1->setReadOnly(true);
	m_editVa0->setReadOnly(true);
	m_editVa2->setReadOnly(true);
	m_editVb0->setReadOnly(true);
	m_editVb1->setReadOnly(true);

	m_editVb2->setReadOnly(true);
	m_editVc0->setReadOnly(true);
	m_editVc1->setReadOnly(true);
	m_editVc2->setReadOnly(true);
	m_editV0->setReadOnly(true);
	m_editV1->setReadOnly(true);
	m_editV2->setReadOnly(true);
	
	m_editIa0->setReadOnly(true);

	m_editIa1->setReadOnly(true);
	m_editIa2->setReadOnly(true);
	
	m_editIc2->setReadOnly(true);
	m_editIb0->setReadOnly(true);
	m_editIb2->setReadOnly(true);
	m_editIb1->setReadOnly(true);
	m_editIc1->setReadOnly(true);
	m_editIc0->setReadOnly(true);
	m_editI0->setReadOnly(true);
	m_editI1->setReadOnly(true);
	m_editI2->setReadOnly(true);
	m_editAPhase0->setReadOnly(true);
	m_editBPhase0->setReadOnly(true);
	m_editCPhase0->setReadOnly(true);
	m_editBPhase1->setReadOnly(true);
	m_editCPhase1->setReadOnly(true);
	m_editTotalPower0->setReadOnly(true);
	m_editAPhase1->setReadOnly(true);
	m_editBPhase2->setReadOnly(true);
	m_editAPhase2->setReadOnly(true);
	m_editCPhase2->setReadOnly(true);
	m_editAPhase3->setReadOnly(true);
	m_editTotalPower1->setReadOnly(true);
	m_editBPhase3->setReadOnly(true);
	m_editCPhase3->setReadOnly(true);
	m_editTotalPower2->setReadOnly(true);



	m_labVa->setAlignment(Qt::AlignCenter);
	m_labVolPhase->setAlignment(Qt::AlignCenter);
	m_labVolFrequency->setAlignment(Qt::AlignCenter);
	m_labVolAmplitude->setAlignment(Qt::AlignCenter);
	m_editVa1->setAlignment(Qt::AlignCenter);
	m_editVa0->setAlignment(Qt::AlignCenter);
	m_editVa2->setAlignment(Qt::AlignCenter);
	m_editVb0->setAlignment(Qt::AlignCenter);
	m_editVb1->setAlignment(Qt::AlignCenter);
	m_labVb->setAlignment(Qt::AlignCenter);
	m_editVb2->setAlignment(Qt::AlignCenter);
	m_editVc0->setAlignment(Qt::AlignCenter);
	m_labVc->setAlignment(Qt::AlignCenter);
	m_editVc1->setAlignment(Qt::AlignCenter);
	m_editVc2->setAlignment(Qt::AlignCenter);
	m_editV0->setAlignment(Qt::AlignCenter);
	m_editV1->setAlignment(Qt::AlignCenter);
	m_editV2->setAlignment(Qt::AlignCenter);
	m_labV0->setAlignment(Qt::AlignCenter);
	m_labCurAmplitude->setAlignment(Qt::AlignCenter);
	m_labCurFrequency->setAlignment(Qt::AlignCenter);
	m_labCurPhase->setAlignment(Qt::AlignCenter);
	m_editIa0->setAlignment(Qt::AlignCenter);
	m_labIa->setAlignment(Qt::AlignCenter);
	m_editIa1->setAlignment(Qt::AlignCenter);
	m_editIa2->setAlignment(Qt::AlignCenter);
	m_labIc->setAlignment(Qt::AlignCenter);
	m_editIc2->setAlignment(Qt::AlignCenter);
	m_editIb0->setAlignment(Qt::AlignCenter);
	m_editIb2->setAlignment(Qt::AlignCenter);
	m_editIb1->setAlignment(Qt::AlignCenter);
	m_labIb->setAlignment(Qt::AlignCenter);
	m_editIc1->setAlignment(Qt::AlignCenter);
	m_editIc0->setAlignment(Qt::AlignCenter);
	m_editI0->setAlignment(Qt::AlignCenter);
	m_editI1->setAlignment(Qt::AlignCenter);
	m_editI2->setAlignment(Qt::AlignCenter);
	m_labI0->setAlignment(Qt::AlignCenter);
	m_lblAPhase->setAlignment(Qt::AlignCenter);
	m_lblTotalPower->setAlignment(Qt::AlignCenter);
	m_lblBPhase->setAlignment(Qt::AlignCenter);
	m_lblCPhase->setAlignment(Qt::AlignCenter);
	m_editAPhase0->setAlignment(Qt::AlignCenter);
	m_lblPowerFactor->setAlignment(Qt::AlignCenter);
	m_editBPhase0->setAlignment(Qt::AlignCenter);
	m_editCPhase0->setAlignment(Qt::AlignCenter);
	m_editBPhase1->setAlignment(Qt::AlignCenter);
	m_editCPhase1->setAlignment(Qt::AlignCenter);
	m_editTotalPower0->setAlignment(Qt::AlignCenter);
	m_editAPhase1->setAlignment(Qt::AlignCenter);
	m_editBPhase2->setAlignment(Qt::AlignCenter);
	m_editAPhase2->setAlignment(Qt::AlignCenter);
	m_editCPhase2->setAlignment(Qt::AlignCenter);
	m_lblReactivePower->setAlignment(Qt::AlignCenter);
	m_editAPhase3->setAlignment(Qt::AlignCenter);
	m_editTotalPower1->setAlignment(Qt::AlignCenter);
	m_lblApparentPower->setAlignment(Qt::AlignCenter);
	m_editBPhase3->setAlignment(Qt::AlignCenter);
	m_editCPhase3->setAlignment(Qt::AlignCenter);
	m_editTotalPower2->setAlignment(Qt::AlignCenter);
	m_lblActivePower->setAlignment(Qt::AlignCenter);


}

void PowerDiagramWidget::paintEvent(QPaintEvent *event)
{
	//20230907 suyang 手写界面后不需要设置

// 	QPainter p(this);
// 	QColor color(50, 50, 50, 30);
// 	p.setPen(color); 
// 	p.drawRect(20,30,Volwidget->width()-1, Volwidget->height()-30);
//     p.drawRect(530,30,Curwidget->width()-20, Curwidget->height()-30);
// 	p.drawRect(20,265,Powerwidget->width()-20,Powerwidget->height()+10);
}

void PowerDiagramWidget::SetComboBoxItemText()
{
	//20230907 suyang 手写界面后不需要重新设置语言

// 	m_combVolSet->setItemText(0,g_sLangTxt_Native_VolSetTypeLN);
// 	m_combVolSet->setItemText(1,g_sLangTxt_Native_VolSetTypeLL);
// 	m_combVolSet->setItemText(2,g_sLangTxt_Native_VolSetTypeSE);
// 	
// 	m_combCurSet->setItemText(0,g_sLangTxt_Native_CurSetTypeLN);
// 	m_combCurSet->setItemText(1,g_sLangTxt_Native_CurSetTypeSE);
}

void PowerDiagramWidget::setShowVolCurPhaseEdit()
{
	CString str;
	int i = m_nCurrentGroup * 3;
	if (m_pVolChList->GetCount()==4)
	{
		m_labV0->show();
		m_editV0->show();
		m_editV1->show();
		m_editV2->show();

		if(!stt_Frame_IsTestStarted() && m_pVOL)
		{
			GetPhaseVolValue(&m_pVOL[i+3],m_editV0,m_editV1,m_editV2);
		}
		else
		{		
			CSttMacroChannel* pMacroChVol0 = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+3);
			UpdateVolValue(pMacroChVol0,m_fAttribute0,m_editV0,m_editV1,m_editV2);				
		}	
	}
	else
	{
		m_labV0->hide();
		m_editV0->hide();
		m_editV1->hide();
		m_editV2->hide();
	}

	if (m_pCurChList->GetCount()==4)
	{	
		m_labI0->show();
		m_editI0->show();
		m_editI1->show();
		m_editI2->show();

		if(!stt_Frame_IsTestStarted() && m_pCUR)
		{
			GetPhaseCurValue(&m_pCUR[i+3],m_editI0,m_editI1,m_editI2);
		}
		else
		{
			CSttMacroChannel* pMacroChCur0 = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+3);
			UpdateCurValue(pMacroChCur0,m_fAttribute0,m_editI0,m_editI1,m_editI2);		
		}		
	}

	else
	{
		m_labI0->hide();
		m_editI0->hide();
		m_editI1->hide();
		m_editI2->hide();
	}
}


void PowerDiagramWidget::setControlFont()
{
	m_labVolAmplitude->setFont(*g_pSttGlobalFont);
	m_labVolPhase->setFont(*g_pSttGlobalFont);
	m_labVolFrequency->setFont(*g_pSttGlobalFont);
	m_labVa->setFont(*g_pSttGlobalFont);
	m_labVb->setFont(*g_pSttGlobalFont);
	m_labVc->setFont(*g_pSttGlobalFont);
	m_editVa0->setFont(*g_pSttGlobalFont);
	m_editVa1->setFont(*g_pSttGlobalFont);
	m_editVa2->setFont(*g_pSttGlobalFont);
	m_editVb0->setFont(*g_pSttGlobalFont);
	m_editVb1->setFont(*g_pSttGlobalFont);
	m_editVb2->setFont(*g_pSttGlobalFont);
	m_editVc0->setFont(*g_pSttGlobalFont);
	m_editVc1->setFont(*g_pSttGlobalFont);
	m_editVc2->setFont(*g_pSttGlobalFont);

	m_labCurAmplitude->setFont(*g_pSttGlobalFont);
	m_labCurFrequency->setFont(*g_pSttGlobalFont);
	m_labCurPhase->setFont(*g_pSttGlobalFont);
	m_labIa->setFont(*g_pSttGlobalFont);
	m_labIb->setFont(*g_pSttGlobalFont);
	m_labIc->setFont(*g_pSttGlobalFont);
	m_editIa0->setFont(*g_pSttGlobalFont);
	m_editIa1->setFont(*g_pSttGlobalFont);
	m_editIa2->setFont(*g_pSttGlobalFont);
	m_editIb0->setFont(*g_pSttGlobalFont);
	m_editIb1->setFont(*g_pSttGlobalFont);
	m_editIb2->setFont(*g_pSttGlobalFont);
	m_editIc0->setFont(*g_pSttGlobalFont);
	m_editIc1->setFont(*g_pSttGlobalFont);
	m_editIc2->setFont(*g_pSttGlobalFont);


	m_editAPhase0->setFont(*g_pSttGlobalFont);
	m_editAPhase1->setFont(*g_pSttGlobalFont);
	m_editAPhase2->setFont(*g_pSttGlobalFont);
	m_editAPhase3->setFont(*g_pSttGlobalFont);
	m_editBPhase0->setFont(*g_pSttGlobalFont);
	m_editBPhase1->setFont(*g_pSttGlobalFont);
	m_editBPhase2->setFont(*g_pSttGlobalFont);
	m_editBPhase3->setFont(*g_pSttGlobalFont);
	m_editCPhase0->setFont(*g_pSttGlobalFont);
	m_editCPhase1->setFont(*g_pSttGlobalFont);
	m_editCPhase2->setFont(*g_pSttGlobalFont);
	m_editCPhase3->setFont(*g_pSttGlobalFont);
        m_editTotalPower0->setFont(*g_pSttGlobalFont);
        m_editTotalPower1->setFont(*g_pSttGlobalFont);
        m_editTotalPower2->setFont(*g_pSttGlobalFont);
	m_lblAPhase->setFont(*g_pSttGlobalFont);
	m_lblBPhase->setFont(*g_pSttGlobalFont);
	m_lblCPhase->setFont(*g_pSttGlobalFont);
	m_lblTotalPower->setFont(*g_pSttGlobalFont);
	m_lblPowerFactor->setFont(*g_pSttGlobalFont);
	m_lblActivePower->setFont(*g_pSttGlobalFont);
	m_lblReactivePower->setFont(*g_pSttGlobalFont);
	m_lblApparentPower->setFont(*g_pSttGlobalFont);
	m_labNum->setFont(*g_pSttGlobalFont);

	m_lblVolSet->setFont(*g_pSttGlobalFont);
	m_lblCurSet->setFont(*g_pSttGlobalFont);
	m_combVolSet->setFont(*g_pSttGlobalFont);
	m_combCurSet->setFont(*g_pSttGlobalFont);

	m_editV0->setFont(*g_pSttGlobalFont);
	m_editV1->setFont(*g_pSttGlobalFont);
	m_editV2->setFont(*g_pSttGlobalFont);
	m_labV0->setFont(*g_pSttGlobalFont);

	m_editI0->setFont(*g_pSttGlobalFont);
	m_editI1->setFont(*g_pSttGlobalFont);
	m_editI2->setFont(*g_pSttGlobalFont);
	m_labI0->setFont(*g_pSttGlobalFont);
}
void PowerDiagramWidget::setButtonImage()
{
#ifdef _PSX_QT_WINDOWS_
	QString strPicPath_Next = _P_GetResourcePath();
	strPicPath_Next += "Button-Next.png";
	m_pbnNext->setIcon(QPixmap(strPicPath_Next));

	QString strPicPath_Pre = _P_GetResourcePath();
	strPicPath_Pre += "Button-Previous.png";
	m_pbnPre->setIcon(QPixmap(strPicPath_Pre));
#else
	QString strPicPath_Next = ":/ctrls/images/Button-Next.png";
	m_pbnNext->setIcon(QPixmap(strPicPath_Next));

	QString strPicPath_Pre = ":/ctrls/images/Button-Previous.png";
	m_pbnPre->setIcon(QPixmap(strPicPath_Pre));
#endif
}


void PowerDiagramWidget::setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource)
{
	if (pSttTestResource == NULL)
	{
		return;
	}

	m_pPowerSttTestResource = pSttTestResource;
	m_nNeedUGroup = 0;
	m_nNeedIGroup = 0;
	int nChannelNum = 0;
	int nVChNumOfModule = 0;
	int nIChNUmOfModule = 0;

	nChannelNum = m_pPowerSttTestResource->m_oVolChRsListRef.GetCount();

	if (nChannelNum <= 4)
	{
		m_nNeedUGroup++;
		nVChNumOfModule = nChannelNum;
	}
	else
	{
		if (nChannelNum%3 == 0)
		{
			m_nNeedUGroup = nChannelNum/3;

		}
		else
		{
			m_nNeedUGroup = nChannelNum/3+1;
		}

		nVChNumOfModule = 3;
	}

	nChannelNum = m_pPowerSttTestResource->m_oCurChRsListRef.GetCount();
	if (nChannelNum <= 4)
	{
		m_nNeedIGroup++;
		nIChNUmOfModule = nChannelNum;
	}
	else
	{
		if (nChannelNum%3 == 0)
		{
			m_nNeedIGroup = nChannelNum/3;
		}
		else
		{
			m_nNeedIGroup = nChannelNum/3+1;
		}

		nIChNUmOfModule = 3;
	}

	m_AllGroup = (m_nNeedUGroup >= m_nNeedIGroup)?m_nNeedUGroup:m_nNeedIGroup;

	if(m_AllGroup == 1)
	{
		m_pbnNext->setDisabled(true);
		m_pbnPre->setDisabled(true);
	}
	else
	{
		//2024-8-23 wuxinyi 切换状态数量，按钮使能不对应问题
		if (m_nCurrentGroup == 0)
		{
		m_pbnNext->setDisabled(false);
		m_pbnPre->setDisabled(true);
	}
		else if (m_nCurrentGroup == m_AllGroup -1)
		{
			m_pbnNext->setDisabled(true);
			m_pbnPre->setDisabled(false);
		}
		else
		{
			m_pbnNext->setDisabled(false);
			m_pbnPre->setDisabled(false);
		}
		
	}
}

void PowerDiagramWidget::setData(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList)
{
	m_pVOL = pVOL;
	m_pCUR = pCUR;

	m_pVolChList = pVolChList;
	m_pCurChList = pCurChList;
	
	initData();
}

void PowerDiagramWidget::UpdatePowerValue(tmt_channel* pVOL,tmt_channel* pCUR,double *pPowerValue,QLineEdit *pPowerFactor_Edit,QLineEdit *pActivePower_Edit,QLineEdit *pReActivePower_Edit,QLineEdit *pAppPower_Edit)
{
	CString strText;
	double dCoef = SetFactor_ByAng(pVOL->Harm[1].fAngle,pCUR->Harm[1].fAngle);
	strText.Format(_T("%.3f"),dCoef);
	pPowerFactor_Edit->setText(strText);
	
	double dPA = SetActive_Power_ByAng(pVOL->Harm[1].fAmp,pVOL->Harm[1].fAngle,pCUR->Harm[1].fAmp,pCUR->Harm[1].fAngle);
	strText.Format(_T("%.3fW"),dPA);
	pActivePower_Edit->setText(strText);
	*(pPowerValue+1)=dPA;
 
	double dQA=SetReactive_Power_ByAng(pVOL->Harm[1].fAmp,pVOL->Harm[1].fAngle,pCUR->Harm[1].fAmp,pCUR->Harm[1].fAngle);
	strText.Format(_T("%.3fVar"),dQA);
	pReActivePower_Edit->setText(strText);
	*(pPowerValue+2)=dQA;

	double dSA=SetApparent_Power_ByAng(pVOL->Harm[1].fAmp,pCUR->Harm[1].fAmp);
	strText.Format(_T("%.3fVA"),dSA);
	pAppPower_Edit->setText(strText);
	*(pPowerValue+3)=dSA;
}

void PowerDiagramWidget::updatePowerData()
{
	int i = m_nCurrentGroup*3;
	if(!stt_Frame_IsTestStarted()&& m_pCUR && m_pVOL)
	{
		UpdatePowerValue(&m_pVOL[i],&m_pCUR[i],m_fPowerValues[0],m_editAPhase0,m_editAPhase1,m_editAPhase2,m_editAPhase3);
		UpdatePowerValue(&m_pVOL[i+1],&m_pCUR[i+1],m_fPowerValues[1],m_editBPhase0,m_editBPhase1,m_editBPhase2,m_editBPhase3);	
		UpdatePowerValue(&m_pVOL[i+2],&m_pCUR[i+2],m_fPowerValues[2],m_editCPhase0,m_editCPhase1,m_editCPhase2,m_editCPhase3);
		UpdateTotalPowers();
	}
	else
	{
		getPowerValueTest();
	}
}

void PowerDiagramWidget::UpdateTotalPowers()
{
	double dTotalPower = m_fPowerValues[0][1] + m_fPowerValues[1][1] + m_fPowerValues[2][1];
	CString strText;
	strText.Format(_T("%.3fW"),dTotalPower);
	m_editTotalPower0->setText(strText);

	dTotalPower = m_fPowerValues[0][2] + m_fPowerValues[1][2] + m_fPowerValues[2][2];
	strText.Format(_T("%.3fVar"),dTotalPower);
	m_editTotalPower1->setText(strText);

	dTotalPower = m_fPowerValues[0][3] + m_fPowerValues[1][3] + m_fPowerValues[2][3];
	strText.Format(_T("%.3fVA"),dTotalPower);
	m_editTotalPower2->setText(strText);
}

void PowerDiagramWidget::UpdatePowerValueTest(CSttMacroChannel *pSttVolCh,CSttMacroChannel *pSttCurCh,float *pfAttribute,double *pPowerValue,
									 QLineEdit *pPowerFactor_Edit,QLineEdit *pActivePower_Edit,QLineEdit *pReActivePower_Edit,QLineEdit *pAppPower_Edit)
{
	if (pSttVolCh != NULL)
	{
		pfAttribute[0] = pSttVolCh->m_oRtDataCh.m_fMag;
		pfAttribute[1] = pSttVolCh->m_oRtDataCh.m_fAng;
		pfAttribute[2] = pSttVolCh->m_oRtDataCh.m_fFreq;
	}

	if (pSttCurCh != NULL)
	{
		pfAttribute[3] = pSttCurCh->m_oRtDataCh.m_fMag;
		pfAttribute[4] = pSttCurCh->m_oRtDataCh.m_fAng;
		pfAttribute[5] = pSttCurCh->m_oRtDataCh.m_fFreq;
	}

	CString strText;
	double dCoef = SetFactor_ByAng(pfAttribute[1],pfAttribute[4]);
	strText.Format(_T("%.3f"),dCoef);
	pPowerFactor_Edit->setText(strText);
	
	double dPA = SetActive_Power_ByAng(pfAttribute[0],pfAttribute[1],pfAttribute[3],pfAttribute[4]);
	strText.Format(_T("%.3fW"),dPA);
	pActivePower_Edit->setText(strText);
	*(pPowerValue+1)=dPA;

	double dQA=SetReactive_Power_ByAng(pfAttribute[0],pfAttribute[1],pfAttribute[3],pfAttribute[4]);
	strText.Format(_T("%.3fVar"),dQA);
	pReActivePower_Edit->setText(strText);
	*(pPowerValue+2)=dQA;

	double dSA=SetApparent_Power_ByAng(pfAttribute[0],pfAttribute[3]);
	strText.Format(_T("%.3fVA"),dSA);
	pAppPower_Edit->setText(strText);
	*(pPowerValue+3)=dSA;
}

void PowerDiagramWidget::getPowerValueTest()
{
	int i = m_nCurrentGroup*3;
	CSttMacroChannel* pMacroChVol_A = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
	CSttMacroChannel* pMacroChCur_A = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
	CSttMacroChannel* pMacroChVol_B = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+1);
	CSttMacroChannel* pMacroChCur_B = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+1);
	CSttMacroChannel* pMacroChVol_C = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+2);
	CSttMacroChannel* pMacroChCur_C = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+2);
	
	UpdatePowerValueTest(pMacroChVol_A,pMacroChCur_A,m_fAttributeA,m_fPowerValues[0],m_editAPhase0,
		m_editAPhase1,m_editAPhase2,m_editAPhase3);

	UpdatePowerValueTest(pMacroChVol_B,pMacroChCur_B,m_fAttributeB,m_fPowerValues[1],m_editBPhase0,
		m_editBPhase1,m_editBPhase2,m_editBPhase3);

	UpdatePowerValueTest(pMacroChVol_C,pMacroChCur_C,m_fAttributeC,m_fPowerValues[2],m_editCPhase0,
		m_editCPhase1,m_editCPhase2,m_editCPhase3);
	UpdateTotalPowers();
}


void PowerDiagramWidget::UpdateVolValue(CSttMacroChannel *pSttVolCh,float *pfAttribute, QLineEdit *pAmpVol_Edit,QLineEdit *pAngleVol_Edit,QLineEdit *pFreqVol_Edit)
{
	if (pSttVolCh != NULL)
	{
		pfAttribute[0] = pSttVolCh->m_oRtDataCh.m_fMag;
		pfAttribute[1] = pSttVolCh->m_oRtDataCh.m_fAng;
		pfAttribute[2] = pSttVolCh->m_oRtDataCh.m_fFreq;
	}

	CString strText;
	strText.Format(_T("%.3fV"),pfAttribute[0]);
	pAmpVol_Edit->setText(strText);
	
	strText = FormatAngleString(pfAttribute[1]);
	pAngleVol_Edit->setText(strText);
	
	strText.Format(_T("%.3fHz"),pfAttribute[2]);
	pFreqVol_Edit->setText(strText);

}

void PowerDiagramWidget::UpdateCurValue(CSttMacroChannel *pSttCurCh,float *pfAttribute, QLineEdit *pAmpCur_Edit,QLineEdit *pAngleCur_Edit,QLineEdit *pFreqCur_Edit)
{
	if (pSttCurCh != NULL)
	{
		pfAttribute[3] = pSttCurCh->m_oRtDataCh.m_fMag;
		pfAttribute[4] = pSttCurCh->m_oRtDataCh.m_fAng;
		pfAttribute[5] = pSttCurCh->m_oRtDataCh.m_fFreq;
	}

	CString strText;
	strText.Format(_T("%.3fA"),pfAttribute[3]);
	pAmpCur_Edit->setText(strText);

	strText = FormatAngleString(pfAttribute[4]);
	pAngleCur_Edit->setText(strText);

	strText.Format(_T("%.3fHz"),pfAttribute[5]);
	pFreqCur_Edit->setText(strText);
}

void PowerDiagramWidget::initChannelData()
{
	CString str;
	int i = m_nCurrentGroup * 3;
	if (m_pVOL)
	{
		if(!stt_Frame_IsTestStarted() && m_pVOL)
		{
			GetPhaseVolValue(&m_pVOL[i],m_editVa0,m_editVa1,m_editVc2);
			GetPhaseVolValue(&m_pVOL[i+1],m_editVb0,m_editVb1,m_editVb2);
			GetPhaseVolValue(&m_pVOL[i+2],m_editVc0,m_editVc1,m_editVc2);
		}
		else
		{
			CSttMacroChannel* pMacroChVol_A = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
			CSttMacroChannel* pMacroChVol_B = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+1);
			CSttMacroChannel* pMacroChVol_C = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+2);
			
			UpdateVolValue(pMacroChVol_A,m_fAttributeA,m_editVa0,m_editVa1,m_editVa2);
			UpdateVolValue(pMacroChVol_B,m_fAttributeB,m_editVb0,m_editVb1,m_editVb2);
			UpdateVolValue(pMacroChVol_C,m_fAttributeC,m_editVc0,m_editVc1,m_editVc2);

		}	
	}

	if (m_pCUR)
	{		
		if(!stt_Frame_IsTestStarted() && m_pCUR)
		{
			GetPhaseCurValue(&m_pCUR[i],m_editIa0,m_editIa1,m_editIc2);
			GetPhaseCurValue(&m_pCUR[i+1],m_editIb0,m_editIb1,m_editIb2);
			GetPhaseCurValue(&m_pCUR[i+2],m_editIc0,m_editIc1,m_editIc2);
		}
		else
		{
			CSttMacroChannel* pMacroChCur_A = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
			CSttMacroChannel* pMacroChCur_B = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+1);
			CSttMacroChannel* pMacroChCur_C = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+2);

			UpdateCurValue(pMacroChCur_A,m_fAttributeA,m_editIa0,m_editIa1,m_editIa2);
			UpdateCurValue(pMacroChCur_B,m_fAttributeB,m_editIb0,m_editIb1,m_editIb2);
			UpdateCurValue(pMacroChCur_C,m_fAttributeC,m_editIc0,m_editIc1,m_editIc2);
		}		
	}
}
void PowerDiagramWidget::initData()
{
	if(m_nCurrentGroup >= m_AllGroup)
	{
		m_nCurrentGroup = m_AllGroup - 1;
	}
	setlabNumText(getAllCurGroupStr());
	initData(m_nCurrentGroup);
	updatePowerData();
}

void PowerDiagramWidget::setlabNumText(QString str)
{
	m_labNum->setText(str);  
	update();
}

CString PowerDiagramWidget::getAllCurGroupStr()
{
	CString strAllGroup,strCurGroup,strNum;
	xlang_GetLangStrByFile(strAllGroup, "Native_AllGroup");
	xlang_GetLangStrByFile(strCurGroup, "Native_CurGroup");

	CString strText1,strText2;
	strText1 = _T("  ");
	strText1 += strAllGroup;
	strNum.Format(_T("%d"),m_AllGroup);
	strText1 += strNum;

	strText2 = _T("  ");
	strText2 += strCurGroup;
	strNum.Format(_T("%d"),m_nCurrentGroup + 1);
	strText2 += strNum;

	CString str = strText1;
	str += "\n";
	str += strText2;
	return str;
}


void PowerDiagramWidget::initData(int nCurrentGroup)
{
	if (m_pPowerSttTestResource == NULL)
	{
		return;
	}

    int mapKey = 0;
	//将电压数据分组
	int startpos=0;
	int endpos=0;
	//小于等于4的一组
	if(m_pPowerSttTestResource->m_oVolChRsListRef.GetCount()<=4)
	{
		mapKey++;
		endpos = startpos+m_pPowerSttTestResource->m_oVolChRsListRef.GetCount();
		//initChannelData(startpos, startpos+m_pPowerSttTestResource->m_oVolChRsListRef.GetCount(),mapKey);
	}
	else
	{
		//大于3，每3个一组
		{
			mapKey ++;
			startpos = nCurrentGroup * 3;
			endpos = startpos+3;
			if (endpos>m_pPowerSttTestResource->m_oVolChRsListRef.GetCount())
			{
				endpos = m_pPowerSttTestResource->m_oVolChRsListRef.GetCount();
			}
			//initChannelData(startpos, endpos, mapKey);
		}
	}

    //将电流数据分组
	mapKey = 0;
	startpos = 0;

	if (m_pPowerSttTestResource->m_oCurChRsListRef.GetCount()<=4 )
	{
		mapKey ++;
		endpos =startpos+m_pPowerSttTestResource->m_oCurChRsListRef.GetCount();
		//initChannelData(startpos, startpos+m_pPowerSttTestResource->m_oCurChRsListRef.GetCount(), mapKey);		
	}
	else
	{
		//每3个量一组
		{
			mapKey ++;
			startpos = nCurrentGroup * 3;
			endpos = startpos+3;
			if (endpos>m_pPowerSttTestResource->m_oCurChRsListRef.GetCount())
			{
				endpos = m_pPowerSttTestResource->m_oCurChRsListRef.GetCount();
			}
			//initChannelData(startpos, endpos, mapKey);
		}
	}

 	getGroupVolPhaseEdit();
 	getGroupCurPhaseEdit();
	setShowVolCurPhaseEdit();
}

void PowerDiagramWidget::slot_PbnNextClicked()
{
	m_nCurrentGroup++;
	if (m_nCurrentGroup >= m_AllGroup)
	{
		m_nCurrentGroup = m_AllGroup - 1;
	}

	if (m_nCurrentGroup == 0)
	{
		m_pbnPre->setDisabled(true);
	}
	else
	{
		m_pbnPre->setDisabled(false);
	}

	if (m_nCurrentGroup == m_AllGroup-1)
	{
		m_pbnNext->setDisabled(true);
	}
	else
	{
		m_pbnNext->setDisabled(false);
	}

	setlabNumText(getAllCurGroupStr());
	initData();
	cmbVolCurPhaseText();
	cmbVolSetChanged();
	cmbCurSetChanged();
}

void PowerDiagramWidget::slot_PbnPreClicked()
{
	m_nCurrentGroup--;
	if (m_nCurrentGroup<0)
	{
		m_nCurrentGroup = 0;
	}

	if (m_nCurrentGroup == 0)
	{
		m_pbnPre->setDisabled(true);
	}
	else
	{
		m_pbnPre->setDisabled(false);
	}

	if (m_nCurrentGroup == m_AllGroup-1)
	{
		m_pbnNext->setDisabled(true);
	}
	else
	{
		m_pbnNext->setDisabled(false);
	}
	setlabNumText(getAllCurGroupStr());
	initData();
	cmbVolCurPhaseText();
	cmbVolSetChanged();
	cmbCurSetChanged();
}

void PowerDiagramWidget::slot_cmb_VolSetChanged(int index)
{
	cmbVolSetChanged();
}
void PowerDiagramWidget::slot_cmb_CurSetChanged(int index)
{
	cmbCurSetChanged();
}
//相电压
void PowerDiagramWidget::GetPhaseVolValue(tmt_Channel* pVOL,QLineEdit *pAmpVol_Edit,QLineEdit *pAngleVol_Edit,QLineEdit *pFreqVol_Edit)
{
	CString strText;

	strText.Format(_T("%.3fV"),pVOL->Harm[1].fAmp);
	pAmpVol_Edit->setText(strText);

	strText = FormatAngleString(pVOL->Harm[1].fAngle);
	pAngleVol_Edit->setText(strText);

	strText.Format(_T("%.3fHz"),pVOL->Harm[1].fFreq);
	pFreqVol_Edit->setText(strText);
}

//线电压
void PowerDiagramWidget::GetLineVolValue(tmt_Channel*pA, tmt_Channel*pB,QLineEdit *pAmpVol_Edit,QLineEdit *pAngleVol_Edit)
{
	m_oCompA = m_pPowerComplex->polar(pA->Harm[1].fAmp, pA->Harm[1].fAngle);
	m_oCompB = m_pPowerComplex->polar(pB->Harm[1].fAmp, pB->Harm[1].fAngle);
	Complex result= m_oCompA-m_oCompB;
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pAmpVol_Edit->setText(strText);
	
	double fAngle=result.arg();
	strText = FormatAngleString(fAngle);
	pAngleVol_Edit->setText(strText);

// 	strText.Format(_T("%.3fHz"),pA->Harm[1].fFreq);
// 	pFreq_Edit->setText(strText);
}

void PowerDiagramWidget::cmbVolSetChanged()
{	
	setCombVolText();
	setlabNumVolText();
	cmbVolCurPhaseText();
	int i = m_nCurrentGroup*3;
	CString str;
	if(!stt_Frame_IsTestStarted()  && m_pVOL)
	{
 	
		str.Format(_T("%.3fHz"),m_pVOL[i].Harm[1].fFreq);
		m_editVa2->setText(str);
		str.Format(_T("%.3fHz"),m_pVOL[i+1].Harm[1].fFreq);
		m_editVb2->setText(str);
		str.Format(_T("%.3fHz"),m_pVOL[i+2].Harm[1].fFreq);
		m_editVc2->setText(str);   

		if (m_combVolSet->currentIndex()==STT_POWER_VolSetType_LN)
		{
			GetPhaseVolValue(&m_pVOL[i],m_editVa0,m_editVa1,m_editVa2);
			GetPhaseVolValue(&m_pVOL[i+1],m_editVb0,m_editVb1,m_editVb2);
			GetPhaseVolValue(&m_pVOL[i+2],m_editVc0,m_editVc1,m_editVc2);
			
		}
		else if (m_combVolSet->currentIndex()==STT_POWER_VolSetType_LL)
		{		
			GetLineVolValue(&m_pVOL[i],&m_pVOL[i+1],m_editVa0,m_editVa1);
			GetLineVolValue(&m_pVOL[i+1],&m_pVOL[i+2],m_editVb0,m_editVb1);
			GetLineVolValue(&m_pVOL[i+2],&m_pVOL[i],m_editVc0,m_editVc1);
            
		}
		else if(m_combVolSet->currentIndex()==STT_POWER_VolSetType_SE)
		{			
			GetPositiveSeqValue(&m_pVOL[i],&m_pVOL[i+1],&m_pVOL[i+2],m_editVa0,m_editVa1);
			GetNegativeSeqValue(&m_pVOL[i],&m_pVOL[i+1],&m_pVOL[i+2],m_editVb0,m_editVb1);
			GetZeroSeqValue(&m_pVOL[i],&m_pVOL[i+1],&m_pVOL[i+2],m_editVc0,m_editVc1);
		}
	}
	else
	{
		getVolSetChangedTest();
	}	

	setShowVolCurPhaseEdit();
}

//正序
void PowerDiagramWidget::GetPositiveSeqValue(tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit)
{
	Complex oAlpha = m_pPowerComplex->aoperator(120);
	m_oCompA = m_pPowerComplex->polar(pA->Harm[1].fAmp, pA->Harm[1].fAngle);
	m_oCompB = m_pPowerComplex->polar(pB->Harm[1].fAmp, pB->Harm[1].fAngle);
	m_oCompC = m_pPowerComplex->polar(pC->Harm[1].fAmp, pC->Harm[1].fAngle);
	
	Complex result = (m_oCompA + oAlpha*m_oCompB + oAlpha*oAlpha*m_oCompC)/3.0;	
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pAmp_Edit->setText(strText);

	double fAngle=result.arg();
	strText = FormatAngleString(fAngle);
	pAngle_Edit->setText(strText);

	/*strText.Format(_T("%.3fHz"),pA->Harm[1].fFreq);
	pFreq_Edit->setText(strText);*/
}

//负序
void PowerDiagramWidget::GetNegativeSeqValue(tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit)
{
	Complex oAlpha = m_pPowerComplex->aoperator(120);
	m_oCompA = m_pPowerComplex->polar(pA->Harm[1].fAmp, pA->Harm[1].fAngle);
	m_oCompB = m_pPowerComplex->polar(pB->Harm[1].fAmp, pB->Harm[1].fAngle);
	m_oCompC = m_pPowerComplex->polar(pC->Harm[1].fAmp, pC->Harm[1].fAngle);

	Complex result = (m_oCompA + oAlpha*oAlpha*m_oCompB + oAlpha*m_oCompC)/3.0;
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pAmp_Edit->setText(strText);

	double fAngle=result.arg();
	//strText.Format(_T("%.3f°"),fAngle);
	strText = FormatAngleString(fAngle);
	pAngle_Edit->setText(strText);

// 	strText.Format(_T("%.3fHz"),pA->Harm[1].fFreq);
// 	pFreq_Edit->setText(strText);
}
//零序
void PowerDiagramWidget::GetZeroSeqValue(tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit)
{
	m_oCompA = m_pPowerComplex->polar(pA->Harm[1].fAmp, pA->Harm[1].fAngle);
	m_oCompB = m_pPowerComplex->polar(pB->Harm[1].fAmp, pB->Harm[1].fAngle);
	m_oCompC = m_pPowerComplex->polar(pC->Harm[1].fAmp, pC->Harm[1].fAngle);

	Complex result = (m_oCompA + m_oCompB + m_oCompC)/3.0;
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pAmp_Edit->setText(strText);

	double fAngle=result.arg();    
	strText = FormatAngleString(fAngle);
	pAngle_Edit->setText(strText);
}

void PowerDiagramWidget::UpdateVolPositiveSeqValueTest(CSttMacroChannel *pSttVolChA,CSttMacroChannel *pSttVolChB,CSttMacroChannel *pSttVolChC
													   ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
													   ,QLineEdit *pVolAmp_Edit,QLineEdit *pVolAngle_Edit)

{
	if (pSttVolChA != NULL)
	{
		pfAttributeA[0] = pSttVolChA->m_oRtDataCh.m_fMag;
		pfAttributeA[1] = pSttVolChA->m_oRtDataCh.m_fAng;
		pfAttributeA[2] = pSttVolChA->m_oRtDataCh.m_fFreq;
	}
	if (pSttVolChB != NULL)
	{
		pfAttributeB[0] = pSttVolChB->m_oRtDataCh.m_fMag;
		pfAttributeB[1] = pSttVolChB->m_oRtDataCh.m_fAng;
		pfAttributeB[2] = pSttVolChB->m_oRtDataCh.m_fFreq;
	}
	if (pSttVolChC != NULL)
	{
		pfAttributeC[0] = pSttVolChC->m_oRtDataCh.m_fMag;
		pfAttributeC[1] = pSttVolChC->m_oRtDataCh.m_fAng;
		pfAttributeC[2] = pSttVolChC->m_oRtDataCh.m_fFreq;
	}

	Complex oAlpha = m_pPowerComplex->aoperator(120);
	m_oCompA = m_pPowerComplex->polar(pfAttributeA[0], pfAttributeA[1]);
	m_oCompB = m_pPowerComplex->polar(pfAttributeB[0], pfAttributeB[1]);
	m_oCompC = m_pPowerComplex->polar(pfAttributeC[0], pfAttributeC[1]);

	Complex result = (m_oCompA + oAlpha*m_oCompB + oAlpha*oAlpha*m_oCompC)/3.0;	
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pVolAmp_Edit->setText(strText);

	double fAngle=result.arg();
	strText = FormatAngleString(fAngle);
	pVolAngle_Edit->setText(strText);
}

void PowerDiagramWidget::UpdateVolNegativeSeqValueTest(CSttMacroChannel *pSttVolChA,CSttMacroChannel *pSttVolChB,CSttMacroChannel *pSttVolChC
													   ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
													   ,QLineEdit *pVolAmp_Edit,QLineEdit *pVolAngle_Edit)

{
	if (pSttVolChA != NULL)
	{
		pfAttributeA[0] = pSttVolChA->m_oRtDataCh.m_fMag;
		pfAttributeA[1] = pSttVolChA->m_oRtDataCh.m_fAng;
		pfAttributeA[2] = pSttVolChA->m_oRtDataCh.m_fFreq;
	}
	if (pSttVolChB != NULL)
	{
		pfAttributeB[0] = pSttVolChB->m_oRtDataCh.m_fMag;
		pfAttributeB[1] = pSttVolChB->m_oRtDataCh.m_fAng;
		pfAttributeB[2] = pSttVolChB->m_oRtDataCh.m_fFreq;
	}
	if (pSttVolChC != NULL)
	{
		pfAttributeC[0] = pSttVolChC->m_oRtDataCh.m_fMag;
		pfAttributeC[1] = pSttVolChC->m_oRtDataCh.m_fAng;
		pfAttributeC[2] = pSttVolChC->m_oRtDataCh.m_fFreq;
	}

	Complex oAlpha = m_pPowerComplex->aoperator(120);
	m_oCompA = m_pPowerComplex->polar(pfAttributeA[0], pfAttributeA[1]);
	m_oCompB = m_pPowerComplex->polar(pfAttributeB[0], pfAttributeB[1]);
	m_oCompC = m_pPowerComplex->polar(pfAttributeC[0], pfAttributeC[1]);

	Complex result = (m_oCompA + oAlpha*oAlpha*m_oCompB + oAlpha*m_oCompC)/3.0;
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pVolAmp_Edit->setText(strText);

	double fAngle=result.arg();
	strText = FormatAngleString(fAngle);
	pVolAngle_Edit->setText(strText);
}

void PowerDiagramWidget::UpdateVolZeroSeqValueTest(CSttMacroChannel *pSttVolChA,CSttMacroChannel *pSttVolChB,CSttMacroChannel *pSttVolChC
													   ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
													   ,QLineEdit *pVolAmp_Edit,QLineEdit *pVolAngle_Edit)

{
	if (pSttVolChA != NULL)
	{
		pfAttributeA[0] = pSttVolChA->m_oRtDataCh.m_fMag;
		pfAttributeA[1] = pSttVolChA->m_oRtDataCh.m_fAng;
		pfAttributeA[2] = pSttVolChA->m_oRtDataCh.m_fFreq;
	}
	if (pSttVolChB != NULL)
	{
		pfAttributeB[0] = pSttVolChB->m_oRtDataCh.m_fMag;
		pfAttributeB[1] = pSttVolChB->m_oRtDataCh.m_fAng;
		pfAttributeB[2] = pSttVolChB->m_oRtDataCh.m_fFreq;
	}
	if (pSttVolChC != NULL)
	{
		pfAttributeC[0] = pSttVolChC->m_oRtDataCh.m_fMag;
		pfAttributeC[1] = pSttVolChC->m_oRtDataCh.m_fAng;
		pfAttributeC[2] = pSttVolChC->m_oRtDataCh.m_fFreq;
	}

	Complex oAlpha = m_pPowerComplex->aoperator(120);
	m_oCompA = m_pPowerComplex->polar(pfAttributeA[0], pfAttributeA[1]);
	m_oCompB = m_pPowerComplex->polar(pfAttributeB[0], pfAttributeB[1]);
	m_oCompC = m_pPowerComplex->polar(pfAttributeC[0], pfAttributeC[1]);

	Complex result = (m_oCompA + m_oCompB + m_oCompC)/3.0;
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pVolAmp_Edit->setText(strText);

	double fAngle=result.arg();
	strText = FormatAngleString(fAngle);
	pVolAngle_Edit->setText(strText);
}

void PowerDiagramWidget::UpdateVolLineValueTest(CSttMacroChannel *pSttVolChA,CSttMacroChannel *pSttVolChB
												,float *pfAttributeA,float *pfAttributeB
												,QLineEdit *pVolAmp_Edit,QLineEdit *pVolAngle_Edit)
{
	if (pSttVolChA != NULL)
	{
		pfAttributeA[0] = pSttVolChA->m_oRtDataCh.m_fMag;
		pfAttributeA[1] = pSttVolChA->m_oRtDataCh.m_fAng;
		pfAttributeA[2] = pSttVolChA->m_oRtDataCh.m_fFreq;
	}
	if (pSttVolChB != NULL)
	{
		pfAttributeB[0] = pSttVolChB->m_oRtDataCh.m_fMag;
		pfAttributeB[1] = pSttVolChB->m_oRtDataCh.m_fAng;
		pfAttributeB[2] = pSttVolChB->m_oRtDataCh.m_fFreq;
	}
	

	m_oCompA = m_pPowerComplex->polar(pfAttributeA[0], pfAttributeA[1]);
	m_oCompB = m_pPowerComplex->polar(pfAttributeB[0], pfAttributeB[1]);
	
	Complex result = m_oCompA - m_oCompB;
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pVolAmp_Edit->setText(strText);

	double fAngle=result.arg();
	strText = FormatAngleString(fAngle);
	pVolAngle_Edit->setText(strText);
}

void PowerDiagramWidget::getVolSetChangedTest()
{
	int i = m_nCurrentGroup*3; 	
	CString str;
	CSttMacroChannel* pMacroChVol_A = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
	CSttMacroChannel* pMacroChVol_B = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+1);
	CSttMacroChannel* pMacroChVol_C = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+2);
	
	
	str.Format(_T("%.3fHz"),m_fAttributeA[2]);
	m_editVa2->setText(str);
	str.Format(_T("%.3fHz"),m_fAttributeB[2]);
	m_editVb2->setText(str);
	str.Format(_T("%.3fHz"),m_fAttributeC[2]);
	m_editVc2->setText(str);
	
	if (m_combVolSet->currentIndex()==STT_POWER_VolSetType_LN)
	{
		UpdateVolValue(pMacroChVol_A,m_fAttributeA,m_editVa0,m_editVa1,m_editVa2);
		UpdateVolValue(pMacroChVol_B,m_fAttributeB,m_editVb0,m_editVb1,m_editVb2);
		UpdateVolValue(pMacroChVol_C,m_fAttributeC,m_editVc0,m_editVc1,m_editVc2);
	}
	else if (m_combVolSet->currentIndex()== STT_POWER_VolSetType_LL)
	{
		UpdateVolLineValueTest(pMacroChVol_A,pMacroChVol_B,m_fAttributeA,m_fAttributeB,m_editVa0,m_editVa1);
		UpdateVolLineValueTest(pMacroChVol_B,pMacroChVol_C,m_fAttributeB,m_fAttributeC,m_editVb0,m_editVb1);
		UpdateVolLineValueTest(pMacroChVol_C,pMacroChVol_A,m_fAttributeC,m_fAttributeA,m_editVc0,m_editVc1);
	}
	else if(m_combVolSet->currentIndex()== STT_POWER_VolSetType_SE )
	{
		UpdateVolPositiveSeqValueTest(pMacroChVol_A,pMacroChVol_B,pMacroChVol_C
			                         ,m_fAttributeA,m_fAttributeB,m_fAttributeC
			                         ,m_editVa0,m_editVa1);
		UpdateVolNegativeSeqValueTest(pMacroChVol_A,pMacroChVol_B,pMacroChVol_C
			                         ,m_fAttributeA,m_fAttributeB,m_fAttributeC
			                         ,m_editVb0,m_editVb1);
		UpdateVolZeroSeqValueTest(pMacroChVol_A,pMacroChVol_B,pMacroChVol_C
			                         ,m_fAttributeA,m_fAttributeB,m_fAttributeC
			                         ,m_editVc0,m_editVc1);//2023/10/27 wjs 这零序应该是m_editVc0/1
	}
}

//相电流
void PowerDiagramWidget::GetPhaseCurValue(tmt_Channel* pCUR,QLineEdit *pAmpCur_Edit,QLineEdit *pAngleCur_Edit,QLineEdit *pFreqCur_Edit)
{
	CString strText;
	strText.Format(_T("%.3fA"),pCUR->Harm[1].fAmp);
	pAmpCur_Edit->setText(strText);

	strText = FormatAngleString(pCUR->Harm[1].fAngle);
	pAngleCur_Edit->setText(strText);

	strText.Format(_T("%.3fHz"),pCUR->Harm[1].fFreq);
	pFreqCur_Edit->setText(strText);
}

void PowerDiagramWidget::cmbCurSetChanged()
{
	setCombCurText();
	setlabNumCurText();
	cmbVolCurPhaseText();
	int i = m_nCurrentGroup*3; 	
	CString str;
	if (!stt_Frame_IsTestStarted() && m_pCUR )
	{
		str.Format(_T("%.3fHz"),m_pCUR[i].Harm[1].fFreq);
		m_editIa2->setText(str);
		str.Format(_T("%.3fHz"),m_pCUR[i+1].Harm[1].fFreq);
		m_editIb2->setText(str);
		str.Format(_T("%.3fHz"),m_pCUR[i+2].Harm[1].fFreq);
		m_editIc2->setText(str);

		if (m_combCurSet->currentIndex()==STT_POWER_CurSetType_LN )
		{
			GetPhaseCurValue(&m_pCUR[i],m_editIa0,m_editIa1,m_editIc2);
			GetPhaseCurValue(&m_pCUR[i+1],m_editIb0,m_editIb1,m_editIb2);
			GetPhaseCurValue(&m_pCUR[i+2],m_editIc0,m_editIc1,m_editIc2);
		}
		else if(m_combCurSet->currentIndex()==STT_POWER_CurSetType_SE)
		{	
			GetPositiveSeqValue(&m_pCUR[i],&m_pCUR[i+1],&m_pCUR[i+2],m_editIa0,m_editIa1);
			GetNegativeSeqValue(&m_pCUR[i],&m_pCUR[i+1],&m_pCUR[i+2],m_editIb0,m_editIb1);
			GetZeroSeqValue(&m_pCUR[i],&m_pCUR[i+1],&m_pCUR[i+2],m_editIc0,m_editIc1);
		}		
	}
	else
	{
		getCurSetChangedTest();
	}
}

void PowerDiagramWidget::UpdateCurPositiveSeqValueTest(CSttMacroChannel *pSttCurChA,CSttMacroChannel *pSttCurChB,CSttMacroChannel *pSttCurChC
												,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
												,QLineEdit *pCurAmp_Edit,QLineEdit *pCurAngle_Edit)
												
{
	if (pSttCurChA != NULL)
	{
		pfAttributeA[3] = pSttCurChA->m_oRtDataCh.m_fMag;
		pfAttributeA[4] = pSttCurChA->m_oRtDataCh.m_fAng;
		pfAttributeA[5] = pSttCurChA->m_oRtDataCh.m_fFreq;
	}
	if (pSttCurChB != NULL)
	{
		pfAttributeB[3] = pSttCurChB->m_oRtDataCh.m_fMag;
		pfAttributeB[4] = pSttCurChB->m_oRtDataCh.m_fAng;
		pfAttributeB[5] = pSttCurChB->m_oRtDataCh.m_fFreq;
	}
	if (pSttCurChC != NULL)
	{
		pfAttributeC[3] = pSttCurChC->m_oRtDataCh.m_fMag;
		pfAttributeC[4] = pSttCurChC->m_oRtDataCh.m_fAng;
		pfAttributeC[5] = pSttCurChC->m_oRtDataCh.m_fFreq;
	}

	Complex oAlpha = m_pPowerComplex->aoperator(120);
	m_oCompA = m_pPowerComplex->polar(pfAttributeA[3], pfAttributeA[4]);
	m_oCompB = m_pPowerComplex->polar(pfAttributeB[3], pfAttributeB[4]);
	m_oCompC = m_pPowerComplex->polar(pfAttributeC[3], pfAttributeC[4]);

	Complex result = (m_oCompA + oAlpha*m_oCompB + oAlpha*oAlpha*m_oCompC)/3.0;	
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pCurAmp_Edit->setText(strText);

	double fAngle=result.arg();
	strText = FormatAngleString(fAngle);
	pCurAngle_Edit->setText(strText);
}

void PowerDiagramWidget::UpdateCurNegativeSeqValueTest(CSttMacroChannel *pSttCurChA,CSttMacroChannel *pSttCurChB,CSttMacroChannel *pSttCurChC
								   ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
								   ,QLineEdit *pCurAmp_Edit,QLineEdit *pCurAngle_Edit)
{
	if (pSttCurChA != NULL)
	{
		pfAttributeA[3] = pSttCurChA->m_oRtDataCh.m_fMag;
		pfAttributeA[4] = pSttCurChA->m_oRtDataCh.m_fAng;
		pfAttributeA[5] = pSttCurChA->m_oRtDataCh.m_fFreq;
	}
	if (pSttCurChB != NULL)
	{
		pfAttributeB[3] = pSttCurChB->m_oRtDataCh.m_fMag;
		pfAttributeB[4] = pSttCurChB->m_oRtDataCh.m_fAng;
		pfAttributeB[5] = pSttCurChB->m_oRtDataCh.m_fFreq;
	}
	if (pSttCurChC != NULL)
	{
		pfAttributeC[3] = pSttCurChC->m_oRtDataCh.m_fMag;
		pfAttributeC[4] = pSttCurChC->m_oRtDataCh.m_fAng;
		pfAttributeC[5] = pSttCurChC->m_oRtDataCh.m_fFreq;
	}

	Complex oAlpha = m_pPowerComplex->aoperator(120);
	m_oCompA = m_pPowerComplex->polar(pfAttributeA[3], pfAttributeA[4]);
	m_oCompB = m_pPowerComplex->polar(pfAttributeB[3], pfAttributeB[4]);
	m_oCompC = m_pPowerComplex->polar(pfAttributeC[3], pfAttributeC[4]);

	Complex result = (m_oCompA + oAlpha*oAlpha*m_oCompB + oAlpha*m_oCompC)/3.0;
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pCurAmp_Edit->setText(strText);

	double fAngle=result.arg();
	strText = FormatAngleString(fAngle);
	pCurAngle_Edit->setText(strText);
}

void PowerDiagramWidget::UpdateCurZeroSeqValueTest(CSttMacroChannel *pSttCurChA,CSttMacroChannel *pSttCurChB,CSttMacroChannel *pSttCurChC
												   ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC
												   ,QLineEdit *pCurAmp_Edit,QLineEdit *pCurAngle_Edit)
{
	if (pSttCurChA != NULL)
	{
		pfAttributeA[3] = pSttCurChA->m_oRtDataCh.m_fMag;
		pfAttributeA[4] = pSttCurChA->m_oRtDataCh.m_fAng;
		pfAttributeA[5] = pSttCurChA->m_oRtDataCh.m_fFreq;
	}
	if (pSttCurChB != NULL)
	{
		pfAttributeB[3] = pSttCurChB->m_oRtDataCh.m_fMag;
		pfAttributeB[4] = pSttCurChB->m_oRtDataCh.m_fAng;
		pfAttributeB[5] = pSttCurChB->m_oRtDataCh.m_fFreq;
	}
	if (pSttCurChC != NULL)
	{
		pfAttributeC[3] = pSttCurChC->m_oRtDataCh.m_fMag;
		pfAttributeC[4] = pSttCurChC->m_oRtDataCh.m_fAng;
		pfAttributeC[5] = pSttCurChC->m_oRtDataCh.m_fFreq;
	}

	Complex oAlpha = m_pPowerComplex->aoperator(120);
	m_oCompA = m_pPowerComplex->polar(pfAttributeA[3], pfAttributeA[4]);
	m_oCompB = m_pPowerComplex->polar(pfAttributeB[3], pfAttributeB[4]);
	m_oCompC = m_pPowerComplex->polar(pfAttributeC[3], pfAttributeC[4]);

	Complex result = (m_oCompA + m_oCompB + m_oCompC)/3.0;
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pCurAmp_Edit->setText(strText);

	double fAngle=result.arg();
	strText = FormatAngleString(fAngle);
	pCurAngle_Edit->setText(strText);
}

void PowerDiagramWidget::getCurSetChangedTest()
{
	int i = m_nCurrentGroup*3; 	
	CString str;
	CSttMacroChannel* pMacroChCur_A = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
	CSttMacroChannel* pMacroChCur_B = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+1);
	CSttMacroChannel* pMacroChCur_C = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+2);

	str.Format(_T("%.3fHz"),m_fAttributeA[5]);
	m_editIa2->setText(str);
	str.Format(_T("%.3fHz"),m_fAttributeB[5]);
	m_editIb2->setText(str);
	str.Format(_T("%.3fHz"),m_fAttributeC[5]);
	m_editIc2->setText(str);
	
	if (m_combCurSet->currentIndex()==STT_POWER_CurSetType_LN)
	{
		UpdateCurValue(pMacroChCur_A,m_fAttributeA,m_editIa0,m_editIa1,m_editIa2);
		UpdateCurValue(pMacroChCur_B,m_fAttributeB,m_editIb0,m_editIb1,m_editIb2);
		UpdateCurValue(pMacroChCur_C,m_fAttributeC,m_editIc0,m_editIc1,m_editIc2);
	}
	else if(m_combCurSet->currentIndex()==STT_POWER_CurSetType_SE)
	{
		UpdateCurPositiveSeqValueTest(pMacroChCur_A,pMacroChCur_B,pMacroChCur_C
		                          ,m_fAttributeA,m_fAttributeB,m_fAttributeC
		                          ,m_editIa0,m_editIa1);
		UpdateCurNegativeSeqValueTest(pMacroChCur_A,pMacroChCur_B,pMacroChCur_C
		 ,m_fAttributeA,m_fAttributeB,m_fAttributeC
		 ,m_editIb0,m_editIb1);
		UpdateCurZeroSeqValueTest(pMacroChCur_A,pMacroChCur_B,pMacroChCur_C
		 ,m_fAttributeA,m_fAttributeB,m_fAttributeC
		 ,m_editIc0,m_editIc1);
	}
}

void PowerDiagramWidget::setlabNumVolText()
{
	CString str;	
	str=m_labVa->text();
	m_labVa->setText(str.left((str.length()-1))+QString::number(m_nCurrentGroup+1));
	str=m_labVb->text();
	m_labVb->setText(str.left((str.length()-1))+QString::number(m_nCurrentGroup+1));
	str=m_labVc->text();
	m_labVc->setText(str.left((str.length()-1))+QString::number(m_nCurrentGroup+1));
}

void PowerDiagramWidget::setlabNumCurText()
{
	CString str;
	str=m_labIa->text();
	m_labIa->setText(str.left((str.length()-1))+QString::number(m_nCurrentGroup+1));
	str=m_labIb->text();
	m_labIb->setText(str.left((str.length()-1))+QString::number(m_nCurrentGroup+1));
	str=m_labIc->text();
	m_labIc->setText(str.left((str.length()-1))+QString::number(m_nCurrentGroup+1));
}

void PowerDiagramWidget::setCombVolText()
{
	if (m_combVolSet->currentIndex()==STT_POWER_VolSetType_LL)
	{
		m_labVa->setText("Uab1");
		m_labVb->setText("Ubc1");
		m_labVc->setText("Uca1");
	}
	else if(m_combVolSet->currentIndex()==STT_POWER_VolSetType_SE)
	{
		m_labVa->setText("U1_1");
		m_labVb->setText("U2_1");
		m_labVc->setText("U0_1");
	}
}

void PowerDiagramWidget::setCombCurText()
{
	if(m_combCurSet->currentIndex()== STT_POWER_CurSetType_SE)
	{
		m_labIa->setText("I1_1");
		m_labIb->setText("I2_1");
		m_labIc->setText("I0_1");
	}
}

void PowerDiagramWidget::cmbVolCurPhaseText()
{
	int i = m_nCurrentGroup*3; 	
	if(m_combVolSet->currentIndex()==STT_POWER_VolSetType_LN)
	{	
		CSttMacroChannel *pChannelVolA = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
		CSttMacroChannel *pChannelVolB = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+1);
		CSttMacroChannel *pChannelVolC = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+2);
		

		if(pChannelVolA != NULL)
		{
			m_strChNameA=pChannelVolA->m_strName;
		}

		if (pChannelVolB != NULL)
		{
			m_strChNameB=pChannelVolB->m_strName;
		}

		if (pChannelVolC != NULL)
		{
			m_strChNameC=pChannelVolC->m_strName;
		}

		m_labVa->setText(m_strChNameA);
		m_labVb->setText(m_strChNameB);
		m_labVc->setText(m_strChNameC);	

		if (m_pVolChList->GetCount()==4)
		{
			m_labV0->show();
			CSttMacroChannel *pChannelVol0 = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+3);
			if (pChannelVol0 != NULL)
			{
				m_strChName0=pChannelVol0->m_strName;
			}
			m_labV0->setText(m_strChName0);
		}	
	}

	if(m_combCurSet->currentIndex()==STT_POWER_CurSetType_LN)
	{
		CSttMacroChannel *pChannelCurA = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
		CSttMacroChannel *pChannelCurB = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+1);
		CSttMacroChannel *pChannelCurC = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+2);

		if(pChannelCurA != NULL)
		{
			m_strChNameA=pChannelCurA->m_strName;
		}

		if (pChannelCurB != NULL)
		{
			m_strChNameB=pChannelCurB->m_strName;
		}

		if (pChannelCurC != NULL)
		{
			m_strChNameC=pChannelCurC->m_strName;
		}
		
		m_labIa->setText(m_strChNameA);
		m_labIb->setText(m_strChNameB);
		m_labIc->setText(m_strChNameC);


		if (m_pCurChList->GetCount()==4)
		{
			m_labI0->show();
			CSttMacroChannel *pChannelCur0 = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+3);
			if (pChannelCur0 != NULL)
			{
				m_strChName0=pChannelCur0->m_strName;
			}
			m_labI0->setText(m_strChName0);
		}	
	}
}

void PowerDiagramWidget::getGroupVolPhaseEdit()
{
	int i = m_nCurrentGroup*3;
	CString str;
	if(!stt_Frame_IsTestStarted() && m_pVOL)
	{
		long nVolrChs = getGroupVolPhaseCount();

		if (nVolrChs >= 1)
		{
			str.Format(_T("%.3fV"),m_pVOL[i].Harm[1].fAmp);
			m_editVa0->setText(str);

			str = FormatAngleString(m_pVOL[i].Harm[1].fAngle);
			m_editVa1->setText(str);
			str.Format(_T("%.3fHz"),m_pVOL[i].Harm[1].fFreq);
			m_editVa2->setText(str);
		}
		else
		{//电压和电流的组数有可能不同，会导致当前组的电流通道数为0
			str = "--";
			m_editVa0->setText(str);
			m_editVa1->setText(str);
			m_editVa2->setText(str);
		}

		if (nVolrChs >= 2)
		{
			str.Format(_T("%.3fV"),m_pVOL[i+1].Harm[1].fAmp);
			m_editVb0->setText(str);

			str = FormatAngleString(m_pVOL[i+1].Harm[1].fAngle);
			m_editVb1->setText(str);
			str.Format(_T("%.3fHz"),m_pVOL[i+1].Harm[1].fFreq);
			m_editVb2->setText(str);
		}
		else
		{
			str = "--";
			m_editVb0->setText(str);
			m_editVb1->setText(str);
			m_editVb2->setText(str);
		}

		if (nVolrChs >= 3)
		{
			str.Format(_T("%.3fV"),m_pVOL[i+2].Harm[1].fAmp);
			m_editVc0->setText(str);

			str = FormatAngleString(m_pVOL[i + 2].Harm[1].fAngle);
			m_editVc1->setText(str);
			str.Format(_T("%.3fHz"),m_pVOL[i+2].Harm[1].fFreq);
			m_editVc2->setText(str);
		}
		else
		{
			str = "--";
			m_editVc0->setText(str);
			m_editVc1->setText(str);
			m_editVc2->setText(str);
		}
	}	    	
	else
	{
		getGroupVolPhaseEditTest();
	}
}
void PowerDiagramWidget::getGroupVolPhaseEditTest()
{
	int i = m_nCurrentGroup*3; 
	CString str;
	long nVolrChs = getGroupVolPhaseCount();
	CSttMacroChannel *pChannelVolA = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
	CSttMacroChannel *pChannelVolB = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+1);
	CSttMacroChannel *pChannelVolC = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+2);
	
	if(pChannelVolA != NULL)
	{
		m_fAttributeA[0] = pChannelVolA->m_oRtDataCh.m_fMag;
		m_fAttributeA[1] = pChannelVolA->m_oRtDataCh.m_fAng;
		m_fAttributeA[2] = pChannelVolA->m_oRtDataCh.m_fFreq;
	}

	if (pChannelVolB != NULL)
	{
		m_fAttributeB[0] = pChannelVolB->m_oRtDataCh.m_fMag;
		m_fAttributeB[1] = pChannelVolB->m_oRtDataCh.m_fAng;
		m_fAttributeB[2] = pChannelVolB->m_oRtDataCh.m_fFreq;
	}

	if (pChannelVolC != NULL)
	{
		m_fAttributeC[0]= pChannelVolC->m_oRtDataCh.m_fMag;
		m_fAttributeC[1] = pChannelVolC->m_oRtDataCh.m_fAng;
		m_fAttributeC[2] = pChannelVolC->m_oRtDataCh.m_fFreq;
	}

	if (nVolrChs >= 1)
	{
		str.Format(_T("%.3fV"),m_fAttributeA[0]);
		m_editVa0->setText(str);

		str = FormatAngleString(m_fAttributeA[1]);
		m_editVa1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeA[2]);
		m_editVa2->setText(str);
	}
	else
	{//电压和电流的组数有可能不同，会导致当前组的电流通道数为0
		str = "--";
		m_editVa0->setText(str);
		m_editVa1->setText(str);
		m_editVa2->setText(str);
	}

	if (nVolrChs >= 2)
	{
		str.Format(_T("%.3fV"),m_fAttributeB[0]);
		m_editVb0->setText(str);

		str = FormatAngleString(m_fAttributeB[1]);
		m_editVb1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeB[2]);
		m_editVb2->setText(str);
	}
	else
	{
		str = "--";
		m_editVb0->setText(str);
		m_editVb1->setText(str);
		m_editVb2->setText(str);
	}

	if (nVolrChs >= 3)
	{
		str.Format(_T("%.3fV"),m_fAttributeC[0]);
		m_editVc0->setText(str);

		str = FormatAngleString(m_fAttributeC[1]);
		m_editVb1->setText(str);

		str.Format(_T("%.3fHz"),m_fAttributeC[2]);
		m_editVc2->setText(str);
	}
	else
	{
		str = "--";
		m_editVc0->setText(str);
		m_editVc1->setText(str);
		m_editVc2->setText(str);
	}	
}

long power_GetCurrGroupChs(CExBaseList *pChRsListRef, long nCurrGroupIndex)
{
	int channelNum= pChRsListRef->GetCount();
	int nChGroups = channelNum / 3;

	if (nChGroups * 3 != channelNum)
	{
		nChGroups++;
	}

	if (nChGroups <= nCurrGroupIndex)
	{//当前电压/电流的总组数，小于当前组数
		return 0;
	}

	if (nCurrGroupIndex == nChGroups-1)
	{//当前显示的是最后一组
		return channelNum - nCurrGroupIndex * 3;
	}
	else
	{
		return 3;
	}
}

long PowerDiagramWidget::getGroupVolPhaseCount()
{
	return power_GetCurrGroupChs(&m_pPowerSttTestResource->m_oVolChRsListRef, m_nCurrentGroup);
	/*
	int channelNum=m_pPowerSttTestResource->m_oVolChRsListRef.GetCount();
	int nChGroups = channelNum / 3;

	if (nChGroups * 3 != channelNum)
	{
		nChGroups++;
	}

	if (m_nCurrentGroup == nChGroups-1)
	{//当前显示的是最后一组
		return channelNum - m_nCurrentGroup * 3;
	}
	else
	{
		return 3;
	}
	*/
}


long PowerDiagramWidget::getGroupCurPhaseCount()
{
	return power_GetCurrGroupChs(&m_pPowerSttTestResource->m_oCurChRsListRef, m_nCurrentGroup);
/*
	int channelNum=m_pPowerSttTestResource->m_oCurChRsListRef.GetCount();
	int nChGroups = channelNum / 3;

	if (nChGroups * 3 != channelNum)
	{
		nChGroups++;
	}

	if (m_nCurrentGroup == nChGroups-1)
	{//当前显示的是最后一组
		return channelNum - m_nCurrentGroup * 3;
	}
	else
	{
		return 3;
	}
*/
}

void PowerDiagramWidget::getGroupCurPhaseEdit()
{
	int i = m_nCurrentGroup*3;
	CString str;

	if(!stt_Frame_IsTestStarted() && m_pCUR)
	{
		long nCurrChs = getGroupCurPhaseCount();
		
		if (nCurrChs >= 1)
		{
			str.Format(_T("%.3fA"),m_pCUR[i].Harm[1].fAmp);
			m_editIa0->setText(str);

			str = FormatAngleString(m_pCUR[i].Harm[1].fAngle);
			m_editIa1->setText(str);
			str.Format(_T("%.3fHz"),m_pCUR[i].Harm[1].fFreq);
			m_editIa2->setText(str);
		}
		else
		{//电压和电流的组数有可能不同，会导致当前组的电流通道数为0
			str = "--";
			m_editIa0->setText(str);
			m_editIa1->setText(str);
			m_editIa2->setText(str);
		}

		if (nCurrChs >= 2)
		{
			str.Format(_T("%.3fA"),m_pCUR[i+1].Harm[1].fAmp);
			m_editIb0->setText(str);
// 			str.Format(_T("%.3f°"), m_pCUR[i + 1].Harm[1].fAngle);

			str = FormatAngleString(m_pCUR[i + 1].Harm[1].fAngle);
			m_editIb1->setText(str);
			str.Format(_T("%.3fHz"),m_pCUR[i+1].Harm[1].fFreq);
			m_editIb2->setText(str);
		}
		else
		{
			str = "--";
			m_editIb0->setText(str);
			m_editIb1->setText(str);
			m_editIb2->setText(str);
		}

		if (nCurrChs >= 3)
		{
			str.Format(_T("%.3fA"),m_pCUR[i+2].Harm[1].fAmp);
			m_editIc0->setText(str);
//			str.Format(_T("%.3f°"),m_pCUR[i+2].Harm[1].fAngle);

			str = FormatAngleString(m_pCUR[i + 2].Harm[1].fAngle);
			m_editIc1->setText(str);
			str.Format(_T("%.3fHz"),m_pCUR[i+2].Harm[1].fFreq);
			m_editIc2->setText(str);
		}
		else
		{
			str = "--";
			m_editIc0->setText(str);
			m_editIc1->setText(str);
			m_editIc2->setText(str);
		}
	}
	else
	{
		getGroupCurPhaseEditTest();
	}
}

void PowerDiagramWidget::getGroupCurPhaseEditTest()
{
	int i = m_nCurrentGroup*3;
	CString str;
	long nCurrChs = getGroupCurPhaseCount();
	CSttMacroChannel *pChannelCurA = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
	CSttMacroChannel *pChannelCurB = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+1);
	CSttMacroChannel *pChannelCurC = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+2);

	if(pChannelCurA != NULL)
	{
		m_fAttributeA[3] = pChannelCurA->m_oRtDataCh.m_fMag;
		m_fAttributeA[4] = pChannelCurA->m_oRtDataCh.m_fAng;
		m_fAttributeA[5] = pChannelCurA->m_oRtDataCh.m_fFreq;
	}

	if (pChannelCurB != NULL)
	{
		m_fAttributeB[3] = pChannelCurB->m_oRtDataCh.m_fMag;
		m_fAttributeB[4] = pChannelCurB->m_oRtDataCh.m_fAng;
		m_fAttributeB[5] = pChannelCurB->m_oRtDataCh.m_fFreq;
	}

	if (pChannelCurC != NULL)
	{
		m_fAttributeC[3] = pChannelCurC->m_oRtDataCh.m_fMag;
		m_fAttributeC[4] = pChannelCurC->m_oRtDataCh.m_fAng;
		m_fAttributeC[5] = pChannelCurC->m_oRtDataCh.m_fFreq;
	}

	if (nCurrChs >= 1)
	{
		str.Format(_T("%.3fA"),m_fAttributeA[3]);
		m_editIa0->setText(str);
// 		str.Format(_T("%.3f°"),m_fAttributeA[4]);

		str = FormatAngleString(m_fAttributeA[4]);
		m_editIa1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeA[5]);
		m_editIa2->setText(str);
	}
	else
	{
		str = "--";
		m_editIa0->setText(str);
		m_editIa1->setText(str);
		m_editIa2->setText(str);
	}

	if (nCurrChs >= 2)
	{
		str.Format(_T("%.3fA"),m_fAttributeB[3]);
		m_editIb0->setText(str);
		//str.Format(_T("%.3f°"),m_fAttributeB[4]);

		str = FormatAngleString(m_fAttributeB[4]);
		m_editIb1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeB[5]);
		m_editIb2->setText(str);
	}
	else
	{
		str = "--";
		m_editIb0->setText(str);
		m_editIb1->setText(str);
		m_editIb2->setText(str);
	}

	if (nCurrChs >= 3)
	{
		str.Format(_T("%.3fA"),m_fAttributeC[3]);
		m_editIc0->setText(str);

		str = FormatAngleString(m_fAttributeC[4]);
		m_editIc1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeC[5]);
		m_editIc2->setText(str);
	}
	else
	{
		str = "--";
		m_editIc0->setText(str);
		m_editIc1->setText(str);
		m_editIc2->setText(str);
	}	    	
}

// void PowerDiagramWidget::TimerStart()
// {
// 	m_nTimerID = startTimer(1000);
// }
// 
// void PowerDiagramWidget::TimerStop(bool bUpdate)
// {
// 	killTimer(m_nTimerID);
// 	m_nTimerID = -1;
// }

// void PowerDiagramWidget::timerEvent(QTimerEvent *event)
// {
// 	if(m_nTimerID == event->timerId())
// 	{
// 		getPowerValueTest();
// 		getVolSetChangedTest();
// 		getCurSetChangedTest();
// 		setShowVolCurPhaseEdit();
// 		QWidget::timerEvent( event );
// 	}
// }
