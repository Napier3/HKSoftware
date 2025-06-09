#include "powerdiagramwidget.h"
#include "ui_powerdiagramwidget.h"
#include "../Module/TestWinFrame/testwinbase.h"
//#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../ReportView/XLangResource_PowerTestWin.h"
#include"../../XLanguage/QT/XLanguageAPI_QT.h"
#include <math.h>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>
#define  STT_POWER_VolSetType_LN                0 // 相电压
#define  STT_POWER_VolSetType_LL                1//线电压
#define  STT_POWER_VolSetType_SE                2//电压序分量

#define  STT_POWER_CurSetType_LN                0 // 相电流
#define  STT_POWER_CurSetType_SE                1 // 电流序分量

#define  STT_POWER_PositiveSequence             1//正序
#define  STT_POWER_NegativeSequence             2//负序
#define  STT_POWER_ZeroSequence                 0//零序

PowerDiagramWidget::PowerDiagramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerDiagramWidget)
{
    ui->setupUi(this);
	InitLanuage();
// 	QSizePolicy spLeft(QSizePolicy::Preferred,QSizePolicy::Preferred);
// 	spLeft.setHorizontalStretch(1);
// 	ui->verticalLayout_6->setSizePolicy(spLeft);
// 	ui->horizontalLayout_3->insertStretch(2, 10);
// 	ui->horizontalLayout_3->insertStretch(1, 20);
	ui->horizontalLayout_3->setStretchFactor(ui->verticalWidget, 10);
	ui->horizontalLayout_3->setStretchFactor(ui->verticalWidget_2, 30);
// 	QVBoxLayout* mainLayout = new QVBoxLayout;
// 	mainLayout->addWidget(ui->widget_2);
// 	setLayout(mainLayout);
	
	m_AllGroup = 0;
	m_nNeedUGroup = 0;
	m_nNeedIGroup = 0;
	m_nCurrentGroup = 0;
	m_pPowerSttTestResource = NULL;
 
	m_bDCTest = FALSE;

	m_pVOL = NULL;
    m_pCUR = NULL; 
	
 	m_pVolChList = NULL;
    m_pCurChList = NULL;
	
 
	for (int nChIndex = 0;nChIndex<3;nChIndex++)
	{
		for (int nPowerIndex = 0;nPowerIndex<4;nPowerIndex++)
		{
			m_fPowerValues[nChIndex][nPowerIndex] = 0.0f;
		}
	}

	initUI();
	initSetFont();

	connect(ui->m_pbnNext_2,SIGNAL(clicked()),this,SLOT(slot_PbnNextClicked()));
	connect(ui->m_pbnPre_2,SIGNAL(clicked()),this,SLOT(slot_PbnPreClicked()));
    connect(ui->m_combVolSet_3,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_VolSetChanged(int)));
	connect(ui->m_combCurSet_3,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_CurSetChanged(int)));
	
	m_nTimerID = -1;
}

PowerDiagramWidget::~PowerDiagramWidget()
{
    delete ui;
}

void PowerDiagramWidget::initUI()
{
	ui->m_labVa->setText("Ua1");
	ui->m_labVb->setText("Ub1");
	ui->m_labVc->setText("Uc1");
	ui->m_labIa->setText("Ia1");
	ui->m_labIb->setText("Ib1");
	ui->m_labIc->setText("Ic1");

	setlabNumVolCurText(Moudle_U);
	setlabNumVolCurText(Moudle_I);
	setCombVolCurText(Moudle_U);
	setCombVolCurText(Moudle_I);

#ifdef STT_USE_Resource_Img_
	ui->m_pbnNext_2->setIcon(QPixmap( ":/images/Button-Next.png"));
	ui->m_pbnPre_2->setIcon(QPixmap( ":/images/Button-Previous.png"));
#else

	ui->m_pbnNext_2->setIcon(QPixmap( "./images/Button-Next.png"));
	ui->m_pbnPre_2->setIcon(QPixmap( "./images/Button-Previous.png"));

#endif

	ui->m_pbnNext_2->setStyleSheet("background-color: white;"); //rgb(83, 92, 91)

	ui->m_pbnPre_2->setStyleSheet("background-color: white;");


	QFontMetrics fontMetrics = QFontMetrics(font());
	QRect recContent_drugName = fontMetrics.boundingRect(/*"总组数: 0"*/g_sLangTxt_Native_AllGroup+"0");
	int nDrugNameWidth = recContent_drugName.width();
	nDrugNameWidth *= 1.2;

	
	ui->m_labNum_2->setFixedSize(nDrugNameWidth,80);
}

void PowerDiagramWidget::initSetFont()
{
	QFont font;
	font.setFamily(/*tr("宋体")*/g_sLangTxt_LetterForm);
	font.setPointSize(9);
	ui->m_labVolAmplitude->setFont(font);
	ui->m_labVolPhase->setFont(font);
	ui->m_labVolFrequency->setFont(font);
	ui->m_labVa->setFont(font);
	ui->m_labVb->setFont(font);
	ui->m_labVc->setFont(font);
	ui->m_editVa0->setFont(font);
	ui->m_editVa1->setFont(font);
	ui->m_editVa2->setFont(font);
	ui->m_editVb0->setFont(font);
	ui->m_editVb1->setFont(font);
	ui->m_editVb2->setFont(font);
	ui->m_editVc0->setFont(font);
	ui->m_editVc1->setFont(font);
	ui->m_editVc2->setFont(font);

	ui->m_labCurAmplitude->setFont(font);
	ui->m_labCurFrequency->setFont(font);
	ui->m_labCurPhase->setFont(font);
	ui->m_labIa->setFont(font);
	ui->m_labIb->setFont(font);
	ui->m_labIc->setFont(font);
	ui->m_editIa0->setFont(font);
	ui->m_editIa1->setFont(font);
	ui->m_editIa2->setFont(font);
	ui->m_editIb0->setFont(font);
	ui->m_editIb1->setFont(font);
	ui->m_editIb2->setFont(font);
	ui->m_editIc0->setFont(font);
	ui->m_editIc1->setFont(font);
	ui->m_editIc2->setFont(font);


	ui->m_editAPhase0->setFont(font);
	ui->m_editAPhase1->setFont(font);
	ui->m_editAPhase2->setFont(font);
	ui->m_editAPhase3->setFont(font);
	ui->m_editBPhase0->setFont(font);
	ui->m_editBPhase1->setFont(font);
	ui->m_editBPhase2->setFont(font);
	ui->m_editBPhase3->setFont(font);
	ui->m_editCPhase0->setFont(font);
	ui->m_editCPhase1->setFont(font);
	ui->m_editCPhase2->setFont(font);
	ui->m_editCPhase3->setFont(font);
	ui->m_editTotalPower0->setFont(font);
	ui->m_editTotalPower1->setFont(font);
	ui->m_editTotalPower2->setFont(font);
	ui->m_lblAPhase->setFont(font);
	ui->m_lblBPhase->setFont(font);
	ui->m_lblCPhase->setFont(font);
	ui->m_lblTotalPower->setFont(font);
	ui->m_lblPowerFactor->setFont(font);
	ui->m_lblActivePower->setFont(font);
	ui->m_lblReactivePower->setFont(font);
	ui->m_lblApparentPower->setFont(font);
	ui->m_labNum_2->setFont(font);

	ui->m_lblVolSet_3->setFont(font);
	ui->m_lblCurSet_3->setFont(font);
	ui->m_combVolSet_3->setFont(font);
	ui->m_combCurSet_3->setFont(font);
}

// void PowerDiagramWidget::paintEvent(QPaintEvent *event)
// {
// 	QPainter p(this);
// 	QColor color(50, 50, 50, 30);
// 	p.setPen(color); 
// 	p.drawRect(10,20,ui->VolCurWidget->width()+20, ui->VolCurWidget->height()+20);
// 	p.drawRect(10,420,ui->PowerWidget->width()-10,ui->PowerWidget->height()-10);
// 	//p.drawRect(650,20,ui->widget->width()-10,ui->widget->height()+40);
// }

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

	nChannelNum = m_pPowerSttTestResource->m_oVolChRsListRef.GetCount();

	if (nChannelNum <= 4)
	{
 		m_nNeedUGroup++;
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
	}
	

	nChannelNum = m_pPowerSttTestResource->m_oCurChRsListRef.GetCount();
	if (nChannelNum <= 4)
	{
		m_nNeedIGroup++;
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
	}

	m_AllGroup = (m_nNeedUGroup >= m_nNeedIGroup)?m_nNeedUGroup:m_nNeedIGroup;

// 	m_pVolChList = &m_pPowerSttTestResource->m_oVolChRsListRef;
// 	m_pCurChList = &m_pPowerSttTestResource->m_oCurChRsListRef;

	if(m_AllGroup == 1)
	{
		ui->m_pbnNext_2->setDisabled(true);
		ui->m_pbnPre_2->setDisabled(true);
	}
	else
	{
		ui->m_pbnNext_2->setDisabled(false);
		ui->m_pbnPre_2->setDisabled(true);
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

void PowerDiagramWidget::UpdateTotalPowers()
{
	double dTotalPower = m_fPowerValues[0][1] + m_fPowerValues[1][1] + m_fPowerValues[2][1];
	CString strText;
	strText.Format(_T("%.3fW"),dTotalPower);
	ui->m_editTotalPower0->setText(strText);

	dTotalPower = m_fPowerValues[0][2] + m_fPowerValues[1][2] + m_fPowerValues[2][2];
	strText.Format(_T("%.3fVar"),dTotalPower);
	ui->m_editTotalPower1->setText(strText);

	dTotalPower = m_fPowerValues[0][3] + m_fPowerValues[1][3] + m_fPowerValues[2][3];
	strText.Format(_T("%.3fVA"),dTotalPower);
	ui->m_editTotalPower2->setText(strText);
}

void PowerDiagramWidget::UpdatePowerValueTest(CSttMacroChannel *pSttVolCh,CSttMacroChannel *pSttCurCh,float *pfAttribute,double *pPowerValue,
									 QLineEdit *pPowerFactor_Edit,QLineEdit *pActivePower_Edit,QLineEdit *pReActivePower_Edit,QLineEdit *pAppPower_Edit)
{
    TypeSttVolCurCh(Moudle_U,pSttVolCh,pfAttribute);
	TypeSttVolCurCh(Moudle_I,pSttCurCh,pfAttribute);

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
	if ((m_pVolChList == NULL)||(m_pCurChList == NULL))
	{
		return;
	}

	int i = m_nCurrentGroup*3;
	CSttMacroChannel* pMacroChVol_A = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
	CSttMacroChannel* pMacroChCur_A = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
	CSttMacroChannel* pMacroChVol_B = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+1);
	CSttMacroChannel* pMacroChCur_B = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+1);
	CSttMacroChannel* pMacroChVol_C = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+2);
	CSttMacroChannel* pMacroChCur_C = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+2);
	
	UpdatePowerValueTest(pMacroChVol_A,pMacroChCur_A,m_fAttributeA,m_fPowerValues[0],ui->m_editAPhase0,
		ui->m_editAPhase1,ui->m_editAPhase2,ui->m_editAPhase3);

	UpdatePowerValueTest(pMacroChVol_B,pMacroChCur_B,m_fAttributeB,m_fPowerValues[1],ui->m_editBPhase0,
		ui->m_editBPhase1,ui->m_editBPhase2,ui->m_editBPhase3);

	UpdatePowerValueTest(pMacroChVol_C,pMacroChCur_C,m_fAttributeC,m_fPowerValues[2],ui->m_editCPhase0,
		ui->m_editCPhase1,ui->m_editCPhase2,ui->m_editCPhase3);
	UpdateTotalPowers();
}

void PowerDiagramWidget::updatePowerData()
{
	int i = m_nCurrentGroup*3;
	if(!g_TestWinBase->m_bViewTestStarted && m_pCUR && m_pVOL)
	{
		UpdatePowerValue(&m_pVOL[i],&m_pCUR[i],m_fPowerValues[0],ui->m_editAPhase0,ui->m_editAPhase1,ui->m_editAPhase2,ui->m_editAPhase3);
		UpdatePowerValue(&m_pVOL[i+1],&m_pCUR[i+1],m_fPowerValues[1],ui->m_editBPhase0,ui->m_editBPhase1,ui->m_editBPhase2,ui->m_editBPhase3);	
		UpdatePowerValue(&m_pVOL[i+2],&m_pCUR[i+2],m_fPowerValues[2],ui->m_editCPhase0,ui->m_editCPhase1,ui->m_editCPhase2,ui->m_editCPhase3);
		UpdateTotalPowers();
	}
	else
	{
		getPowerValueTest();
	}
}


void PowerDiagramWidget::TypeSttVolCurCh(int nModuleType,CSttMacroChannel *pSttVolCurCh,float *pfAttribute)
{
	if (nModuleType==Moudle_U)
	{
		if (pSttVolCurCh != NULL)
		{			
			if (m_bDCTest)
			{
				pSttVolCurCh->m_oRtDataCh.m_fAng = 0;
				pSttVolCurCh->m_oRtDataCh.m_fFreq = 0;
			}
			
			pfAttribute[0] = pSttVolCurCh->m_oRtDataCh.m_fMag;
		    pfAttribute[1] = pSttVolCurCh->m_oRtDataCh.m_fAng;
		    pfAttribute[2] = pSttVolCurCh->m_oRtDataCh.m_fFreq;
				
		}
	}
	else
	{
		if (pSttVolCurCh != NULL)
		{
			if (m_bDCTest)
			{
				pSttVolCurCh->m_oRtDataCh.m_fAng = 0;
				pSttVolCurCh->m_oRtDataCh.m_fFreq = 0;
			}
			pfAttribute[3] = pSttVolCurCh->m_oRtDataCh.m_fMag;
			pfAttribute[4] = pSttVolCurCh->m_oRtDataCh.m_fAng;
			pfAttribute[5] = pSttVolCurCh->m_oRtDataCh.m_fFreq;	
		}
	}
}
void PowerDiagramWidget::updateData()
{
	CString str;
	int i = m_nCurrentGroup * 3;

	if (m_pVOL)
	{
		if (!g_TestWinBase->m_bViewTestStarted && m_pVOL )
		{
			GetPhaseValue(Moudle_U,&m_pVOL[i],NULL,ui->m_editVa0,ui->m_editVa1,ui->m_editVa2);
			GetPhaseValue(Moudle_U,&m_pVOL[i+1],NULL,ui->m_editVb0,ui->m_editVb1,ui->m_editVb2);
			GetPhaseValue(Moudle_U,&m_pVOL[i+2],NULL,ui->m_editVc0,ui->m_editVc1,ui->m_editVc2);		
		}
		else
		{
			CSttMacroChannel* pMacroChVol_A = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
			CSttMacroChannel* pMacroChVol_B = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+1);
			CSttMacroChannel* pMacroChVol_C = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+2);
						
			GetPhaseValueTest(Moudle_U,pMacroChVol_A,m_fAttributeA,ui->m_editVa0,ui->m_editVa1,ui->m_editVa2);
			GetPhaseValueTest(Moudle_U,pMacroChVol_B,m_fAttributeB,ui->m_editVb0,ui->m_editVb1,ui->m_editVb2);
			GetPhaseValueTest(Moudle_U,pMacroChVol_C,m_fAttributeC,ui->m_editVc0,ui->m_editVc1,ui->m_editVc2);
			
			
		}	
	}
	

	if (m_pCUR)
	{
		if(!g_TestWinBase->m_bViewTestStarted && m_pCUR)
		{
			GetPhaseValue(Moudle_I,NULL,&m_pCUR[i],ui->m_editIa0,ui->m_editIa1,ui->m_editIa2);
			GetPhaseValue(Moudle_I,NULL,&m_pCUR[i+1],ui->m_editIb0,ui->m_editIb1,ui->m_editIb2);
			GetPhaseValue(Moudle_I,NULL,&m_pCUR[i+2],ui->m_editIc0,ui->m_editIc1,ui->m_editIc2);	
		}
		else
		{	
			CSttMacroChannel* pMacroChCur_A = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
			CSttMacroChannel* pMacroChCur_B = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+1);
			CSttMacroChannel* pMacroChCur_C = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+2);

			GetPhaseValueTest(Moudle_I,pMacroChCur_A,m_fAttributeA,ui->m_editIa0,ui->m_editIa1,ui->m_editIa2);
			GetPhaseValueTest(Moudle_I,pMacroChCur_B,m_fAttributeB,ui->m_editIb0,ui->m_editIb1,ui->m_editIb2);
			GetPhaseValueTest(Moudle_I,pMacroChCur_C,m_fAttributeC,ui->m_editIc0,ui->m_editIc1,ui->m_editIc2);
		}		
	}
}

void PowerDiagramWidget::initData()
{
	if(m_nCurrentGroup >= m_AllGroup)
	{
		m_nCurrentGroup = m_AllGroup - 1;
	}

	setlabNumText();
	updatePowerData();
	setDC(m_bDCTest);
	initData(m_nCurrentGroup);
	cmbVolSetChanged();
	cmbCurSetChanged();	
}

void PowerDiagramWidget::setlabNumText()
{
	QString str = QString(/*tr("总组数: %1")*/g_sLangTxt_Native_AllGroup+" %1").arg(m_AllGroup)+ "\n" + QString(/*tr("当前组: %1")*/g_sLangTxt_Native_CurGroup+" %1").arg(m_nCurrentGroup+1);
	ui->m_labNum_2->setText(str);
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
		ui->m_pbnPre_2->setDisabled(true);
	}
	else
	{
		ui->m_pbnPre_2->setDisabled(false);
	}

	if (m_nCurrentGroup == m_AllGroup-1)
	{
		ui->m_pbnNext_2->setDisabled(true);
	}
	else
	{
		ui->m_pbnNext_2->setDisabled(false);
	}

	setlabNumText();
	initData();
	cmbVolCurPhaseText();
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
		ui->m_pbnPre_2->setDisabled(true);
	}
	else
	{
		ui->m_pbnPre_2->setDisabled(false);
	}

	if (m_nCurrentGroup == m_AllGroup-1)
	{
		ui->m_pbnNext_2->setDisabled(true);
	}
	else
	{
		ui->m_pbnNext_2->setDisabled(false);
	}

	setlabNumText();
	initData();
	cmbVolCurPhaseText();
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
void PowerDiagramWidget::GetPhaseValue(int nModuleType,tmt_Channel* pVOL,tmt_Channel* pCUR,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit,QLineEdit *pFreq_Edit)
{
	CString strText;
    
	if (nModuleType == Moudle_U)
	{
		strText.Format(_T("%.3fV"),pVOL->Harm[1].fAmp);
		pAmp_Edit->setText(strText);

		strText.Format(_T("%.3f°"),pVOL->Harm[1].fAngle);
		pAngle_Edit->setText(strText);

		strText.Format(_T("%.3fHz"),pVOL->Harm[1].fFreq);
		pFreq_Edit->setText(strText);
	}

	if (nModuleType == Moudle_I)
	{
		strText.Format(_T("%.3fA"),pCUR->Harm[1].fAmp);
		pAmp_Edit->setText(strText);

		strText.Format(_T("%.3f°"),pCUR->Harm[1].fAngle);
		pAngle_Edit->setText(strText);

		strText.Format(_T("%.3fHz"),pCUR->Harm[1].fFreq);
		pFreq_Edit->setText(strText);
	}
}

//线电压
void PowerDiagramWidget::GetLineValue(tmt_Channel*pA, tmt_Channel*pB,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit)
{
	m_oCompA = m_pPowerComplex->polar(pA->Harm[1].fAmp, pA->Harm[1].fAngle);
	m_oCompB = m_pPowerComplex->polar(pB->Harm[1].fAmp, pB->Harm[1].fAngle);
	Complex result= m_oCompA-m_oCompB;
	GetResult(Moudle_U,result,pAmp_Edit,pAngle_Edit);
}

//序分量
void PowerDiagramWidget::GetSequenceValue(int nModuleType,long nSequenceID ,tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit)
{
    Complex oAlpha = m_pPowerComplex->aoperator(120);
	m_oCompA = m_pPowerComplex->polar(pA->Harm[1].fAmp, pA->Harm[1].fAngle);
	m_oCompB = m_pPowerComplex->polar(pB->Harm[1].fAmp, pB->Harm[1].fAngle);
	m_oCompC = m_pPowerComplex->polar(pC->Harm[1].fAmp, pC->Harm[1].fAngle);
    Complex result;

	if (nModuleType ==Moudle_U)
	{
  		if (nSequenceID == STT_POWER_PositiveSequence)//正序
  		{
  			result = (m_oCompA + oAlpha*m_oCompB + oAlpha*oAlpha*m_oCompC)/3.0;	
  			GetResult(Moudle_U,result,pAmp_Edit,pAngle_Edit);
  		}
  		else if (nSequenceID == STT_POWER_NegativeSequence)//负序
  		{
  			result = (m_oCompA + oAlpha*oAlpha*m_oCompB + oAlpha*m_oCompC)/3.0;
  			GetResult(Moudle_U,result,pAmp_Edit,pAngle_Edit);
  		}
  		else if (nSequenceID == STT_POWER_ZeroSequence)//零序
  		{
  			result = (m_oCompA + m_oCompB + m_oCompC)/3.0;
  			GetResult(Moudle_U,result,pAmp_Edit,pAngle_Edit);
  		}
	}

	else
	{
 		if (nSequenceID == STT_POWER_PositiveSequence)
 		{
 			result = (m_oCompA + oAlpha*m_oCompB + oAlpha*oAlpha*m_oCompC)/3.0;	
 			GetResult(Moudle_I,result,pAmp_Edit,pAngle_Edit);
 		}
 		else if (nSequenceID == STT_POWER_NegativeSequence)
 		{
 			result = (m_oCompA + oAlpha*oAlpha*m_oCompB + oAlpha*m_oCompC)/3.0;
 			GetResult(Moudle_I,result,pAmp_Edit,pAngle_Edit);
 		}
 		else if (nSequenceID == STT_POWER_ZeroSequence)
 		{
 			result = (m_oCompA + m_oCompB + m_oCompC)/3.0;
 			GetResult(Moudle_I,result,pAmp_Edit,pAngle_Edit);
 		}
	}
}

void PowerDiagramWidget::cmbVolSetChanged()
{	
    setCombVolCurText(Moudle_U);
	setlabNumVolCurText(Moudle_U);
	cmbVolCurPhaseText();
	int i = m_nCurrentGroup*3;
	CString str;
	if(!g_TestWinBase->m_bViewTestStarted && m_pVOL)
	{
		str.Format(_T("%.3fHz"),m_pVOL[i].Harm[1].fFreq);
		ui->m_editVa2->setText(str);
		str.Format(_T("%.3fHz"),m_pVOL[i+1].Harm[1].fFreq);
		ui->m_editVb2->setText(str);
		str.Format(_T("%.3fHz"),m_pVOL[i+2].Harm[1].fFreq);
		ui->m_editVc2->setText(str); 

		if (ui->m_combVolSet_3->currentIndex()==STT_POWER_VolSetType_LN)
		{
			GetPhaseValue(Moudle_U,&m_pVOL[i],NULL,ui->m_editVa0,ui->m_editVa1,ui->m_editVa2);
			GetPhaseValue(Moudle_U,&m_pVOL[i+1],NULL,ui->m_editVb0,ui->m_editVb1,ui->m_editVb2);
			GetPhaseValue(Moudle_U,&m_pVOL[i+2],NULL,ui->m_editVc0,ui->m_editVc1,ui->m_editVc2);

		}
		else if (ui->m_combVolSet_3->currentIndex()==STT_POWER_VolSetType_LL)
		{		
			GetLineValue(&m_pVOL[i],&m_pVOL[i+1],ui->m_editVa0,ui->m_editVa1);
			GetLineValue(&m_pVOL[i+1],&m_pVOL[i+2],ui->m_editVb0,ui->m_editVb1);
			GetLineValue(&m_pVOL[i+2],&m_pVOL[i],ui->m_editVc0,ui->m_editVc1);

		}
		else if(ui->m_combVolSet_3->currentIndex()==STT_POWER_VolSetType_SE)
		{			
			GetSequenceValue(Moudle_U,STT_POWER_PositiveSequence,&m_pVOL[i],&m_pVOL[i+1],&m_pVOL[i+2],ui->m_editVa0,ui->m_editVa1);
			GetSequenceValue(Moudle_U,STT_POWER_NegativeSequence,&m_pVOL[i],&m_pVOL[i+1],&m_pVOL[i+2],ui->m_editVb0,ui->m_editVb1);
			GetSequenceValue(Moudle_U,STT_POWER_ZeroSequence,&m_pVOL[i],&m_pVOL[i+1],&m_pVOL[i+2],ui->m_editVc0,ui->m_editVc1);
		}
	}
 	else
 	{
 		getVolSetChangedTest();		
 	}	
}

void PowerDiagramWidget::GetPhaseValueTest(int nModuleType,CSttMacroChannel *pSttVolCurCh,float *pfAttribute, QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit,QLineEdit *pFreq_Edit)
{
	CString strText;
	if (nModuleType == Moudle_U)
	{
		TypeSttVolCurCh(Moudle_U,pSttVolCurCh,pfAttribute);
		strText.Format(_T("%.3fV"),pfAttribute[0]);
		pAmp_Edit->setText(strText);
		strText.Format(_T("%.3f°"),pfAttribute[1]);
		pAngle_Edit->setText(strText);
		strText.Format(_T("%.3fHz"),pfAttribute[2]);
		pFreq_Edit->setText(strText);
	}
	else
	{
		TypeSttVolCurCh(Moudle_I,pSttVolCurCh,pfAttribute);
		strText.Format(_T("%.3fA"),pfAttribute[3]);
		pAmp_Edit->setText(strText);
		strText.Format(_T("%.3f°"),pfAttribute[4]);
		pAngle_Edit->setText(strText);
		strText.Format(_T("%.3fHz"),pfAttribute[5]);
		pFreq_Edit->setText(strText);
	}
}

void PowerDiagramWidget::GetResult(int nModuleType,Complex result,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit)
{
	CString strText;
	double fAngle=result.arg();
	strText.Format(_T("%.3f°"),fAngle);
	pAngle_Edit->setText(strText);
	double fAmp=result.norm();
	
	if (nModuleType==Moudle_U)
	{		
		strText.Format(_T("%.3fV"),fAmp);
	}	
	else
	{
		strText.Format(_T("%.3fA"),fAmp);
		
	}
	pAmp_Edit->setText(strText);
}



void PowerDiagramWidget::GetSequenceValueTest(int nModuleType,long nSequenceID,CSttMacroChannel *pSttVolCurChA,CSttMacroChannel *pSttVolCurChB,CSttMacroChannel *pSttVolCurChC ,float *pfAttributeA,float *pfAttributeB,float *pfAttributeC ,QLineEdit *pAmp_Edit,QLineEdit *pAngle_Edit)
{
	Complex oAlpha = m_pPowerComplex->aoperator(120);
	Complex result;
	if (nModuleType == Moudle_U)
	{
		TypeSttVolCurCh(Moudle_U,pSttVolCurChA,pfAttributeA);
		TypeSttVolCurCh(Moudle_U,pSttVolCurChB,pfAttributeB);
		TypeSttVolCurCh(Moudle_U,pSttVolCurChC,pfAttributeC);
			
		m_oCompA = m_pPowerComplex->polar(pfAttributeA[0], pfAttributeA[1]);
		m_oCompB = m_pPowerComplex->polar(pfAttributeB[0], pfAttributeB[1]);
		m_oCompC = m_pPowerComplex->polar(pfAttributeC[0], pfAttributeC[1]);

		if (nSequenceID == STT_POWER_PositiveSequence)
		{
			result = (m_oCompA + oAlpha*m_oCompB + oAlpha*oAlpha*m_oCompC)/3.0;	
			GetResult(Moudle_U,result,pAmp_Edit,pAngle_Edit);
		}
		else if (nSequenceID ==STT_POWER_NegativeSequence)
		{
			result = (m_oCompA + oAlpha*oAlpha*m_oCompB + oAlpha*m_oCompC)/3.0;
			GetResult(Moudle_U,result,pAmp_Edit,pAngle_Edit);
		}
		else if (nSequenceID == STT_POWER_ZeroSequence)
		{
			result = (m_oCompA + m_oCompB + m_oCompC)/3.0;
			GetResult(Moudle_U,result,pAmp_Edit,pAngle_Edit);
		}
	}
	else
	{
		TypeSttVolCurCh(Moudle_I,pSttVolCurChA,pfAttributeA);
		TypeSttVolCurCh(Moudle_I,pSttVolCurChB,pfAttributeB);
		TypeSttVolCurCh(Moudle_I,pSttVolCurChC,pfAttributeC);

		m_oCompA = m_pPowerComplex->polar(pfAttributeA[3], pfAttributeA[4]);
		m_oCompB = m_pPowerComplex->polar(pfAttributeB[3], pfAttributeB[4]);
		m_oCompC = m_pPowerComplex->polar(pfAttributeC[3], pfAttributeC[4]);

		if (nSequenceID == STT_POWER_PositiveSequence)
		{
			result = (m_oCompA + oAlpha*m_oCompB + oAlpha*oAlpha*m_oCompC)/3.0;	
			GetResult(Moudle_I,result,pAmp_Edit,pAngle_Edit);
		}
		else if (nSequenceID ==STT_POWER_NegativeSequence)
		{
			result = (m_oCompA + oAlpha*oAlpha*m_oCompB + oAlpha*m_oCompC)/3.0;
			GetResult(Moudle_I,result,pAmp_Edit,pAngle_Edit);
		}
		else if (nSequenceID ==STT_POWER_ZeroSequence)
		{
			result = (m_oCompA + m_oCompB + m_oCompC)/3.0;
			GetResult(Moudle_I,result,pAmp_Edit,pAngle_Edit);	
		}
	}
}


void PowerDiagramWidget::GetLineValueTest(CSttMacroChannel *pSttVolChA,CSttMacroChannel *pSttVolChB,float *pfAttributeA,float *pfAttributeB,QLineEdit *pVolAmp_Edit,QLineEdit *pVolAngle_Edit)								
{
    TypeSttVolCurCh(Moudle_U,pSttVolChA,pfAttributeA);
	TypeSttVolCurCh(Moudle_U,pSttVolChB,pfAttributeB);
	
	m_oCompA = m_pPowerComplex->polar(pfAttributeA[0], pfAttributeA[1]);
	m_oCompB = m_pPowerComplex->polar(pfAttributeB[0], pfAttributeB[1]);
	
	Complex result = m_oCompA - m_oCompB;
	CString strText;
	double fAmp=result.norm();
	strText.Format(_T("%.3fV"),fAmp);
	pVolAmp_Edit->setText(strText);
	double fAngle=result.arg();
	strText.Format(_T("%.3f°"),fAngle);
	pVolAngle_Edit->setText(strText);
}

void PowerDiagramWidget::getVolSetChangedTest()
{
	if ((m_pVolChList == NULL)||(m_pCurChList == NULL))
	{
		return;
	}

	int i = m_nCurrentGroup*3; 	
	CString str;
	CSttMacroChannel* pMacroChVol_A = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
	CSttMacroChannel* pMacroChVol_B = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+1);
	CSttMacroChannel* pMacroChVol_C = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+2);
	
	str.Format(_T("%.3fHz"),m_fAttributeA[2]);
	ui->m_editVa2->setText(str);
	str.Format(_T("%.3fHz"),m_fAttributeB[2]);
	ui->m_editVb2->setText(str);
	str.Format(_T("%.3fHz"),m_fAttributeC[2]);
	ui->m_editVc2->setText(str);
	
	if (ui->m_combVolSet_3->currentIndex()==STT_POWER_VolSetType_LN)
	{
		GetPhaseValueTest(Moudle_U,pMacroChVol_A,m_fAttributeA,ui->m_editVa0,ui->m_editVa1,ui->m_editVa2);
		GetPhaseValueTest(Moudle_U,pMacroChVol_B,m_fAttributeB,ui->m_editVb0,ui->m_editVb1,ui->m_editVb2);
		GetPhaseValueTest(Moudle_U,pMacroChVol_C,m_fAttributeC,ui->m_editVc0,ui->m_editVc1,ui->m_editVc2);
	}
	else if (ui->m_combVolSet_3->currentIndex()== STT_POWER_VolSetType_LL)
	{
		GetLineValueTest(pMacroChVol_A,pMacroChVol_B,m_fAttributeA,m_fAttributeB,ui->m_editVa0,ui->m_editVa1);
		GetLineValueTest(pMacroChVol_B,pMacroChVol_C,m_fAttributeB,m_fAttributeC,ui->m_editVb0,ui->m_editVb1);
		GetLineValueTest(pMacroChVol_C,pMacroChVol_A,m_fAttributeC,m_fAttributeA,ui->m_editVc0,ui->m_editVc1);
	}
	else if(ui->m_combVolSet_3->currentIndex()== STT_POWER_VolSetType_SE )
	{
		GetSequenceValueTest(Moudle_U,STT_POWER_PositiveSequence,pMacroChVol_A,pMacroChVol_B,pMacroChVol_C
			                ,m_fAttributeA,m_fAttributeB,m_fAttributeC,ui->m_editVa0,ui->m_editVa1);
		GetSequenceValueTest(Moudle_U,STT_POWER_NegativeSequence,pMacroChVol_A,pMacroChVol_B,pMacroChVol_C
			                ,m_fAttributeA,m_fAttributeB,m_fAttributeC,ui->m_editVb0,ui->m_editVb1);	                       
		GetSequenceValueTest(Moudle_U,STT_POWER_ZeroSequence,pMacroChVol_A,pMacroChVol_B,pMacroChVol_C
			                ,m_fAttributeA,m_fAttributeB,m_fAttributeC ,ui->m_editVc0,ui->m_editVc1);
	}
}


void PowerDiagramWidget::cmbCurSetChanged()
{
	setCombVolCurText(Moudle_I);
	setlabNumVolCurText(Moudle_I);
	cmbVolCurPhaseText();
	int i = m_nCurrentGroup*3; 	
	CString str;
	if (!g_TestWinBase->m_bViewTestStarted && m_pCUR)
	{
		str.Format(_T("%.3fHz"),m_pCUR[i].Harm[1].fFreq);
		ui->m_editIa2->setText(str);
		str.Format(_T("%.3fHz"),m_pCUR[i+1].Harm[1].fFreq);
		ui->m_editIb2->setText(str);
		str.Format(_T("%.3fHz"),m_pCUR[i+2].Harm[1].fFreq);
		ui->m_editIc2->setText(str);

		if (ui->m_combCurSet_3->currentIndex()==STT_POWER_CurSetType_LN )
		{
			GetPhaseValue(Moudle_I,NULL,&m_pCUR[i],ui->m_editIa0,ui->m_editIa1,ui->m_editIa2);
			GetPhaseValue(Moudle_I,NULL,&m_pCUR[i+1],ui->m_editIb0,ui->m_editIb1,ui->m_editIb2);
			GetPhaseValue(Moudle_I,NULL,&m_pCUR[i+2],ui->m_editIc0,ui->m_editIc1,ui->m_editIc2);
		}
		else if(ui->m_combCurSet_3->currentIndex()==STT_POWER_CurSetType_SE)
		{	
			GetSequenceValue(Moudle_I,STT_POWER_PositiveSequence,&m_pCUR[i],&m_pCUR[i+1],&m_pCUR[i+2],ui->m_editIa0,ui->m_editIa1);
			GetSequenceValue(Moudle_I,STT_POWER_NegativeSequence,&m_pCUR[i],&m_pCUR[i+1],&m_pCUR[i+2],ui->m_editIb0,ui->m_editIb1);
			GetSequenceValue(Moudle_I,STT_POWER_ZeroSequence,&m_pCUR[i],&m_pCUR[i+1],&m_pCUR[i+2],ui->m_editIc0,ui->m_editIc1);
		}		
	}
	else
	{
 		getCurSetChangedTest(); 
 	}
}


void PowerDiagramWidget::getCurSetChangedTest()
{
	if ((m_pVolChList == NULL)||(m_pCurChList == NULL))
	{
		return;
	}

	int i = m_nCurrentGroup*3; 	
	CString str;
	CSttMacroChannel* pMacroChCur_A = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
	CSttMacroChannel* pMacroChCur_B = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+1);
	CSttMacroChannel* pMacroChCur_C = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+2);

	str.Format(_T("%.3fHz"),m_fAttributeA[5]);
	ui->m_editIa2->setText(str);
	str.Format(_T("%.3fHz"),m_fAttributeB[5]);
	ui->m_editIb2->setText(str);
	str.Format(_T("%.3fHz"),m_fAttributeC[5]);
	ui->m_editIc2->setText(str);
	
	if (ui->m_combCurSet_3->currentIndex()==STT_POWER_CurSetType_LN)
	{
		GetPhaseValueTest(Moudle_I,pMacroChCur_A,m_fAttributeA,ui->m_editIa0,ui->m_editIa1,ui->m_editIa2);
		GetPhaseValueTest(Moudle_I,pMacroChCur_B,m_fAttributeB,ui->m_editIb0,ui->m_editIb1,ui->m_editIb2);
		GetPhaseValueTest(Moudle_I,pMacroChCur_C,m_fAttributeC,ui->m_editIc0,ui->m_editIc1,ui->m_editIc2);
	}
	else if(ui->m_combCurSet_3->currentIndex()==STT_POWER_CurSetType_SE)
	{
		GetSequenceValueTest(Moudle_I,STT_POWER_PositiveSequence,pMacroChCur_A,pMacroChCur_B,pMacroChCur_C
		                 ,m_fAttributeA,m_fAttributeB,m_fAttributeC ,ui->m_editIa0,ui->m_editIa1);                         
	    GetSequenceValueTest(Moudle_I,STT_POWER_NegativeSequence,pMacroChCur_A,pMacroChCur_B,pMacroChCur_C
		                 ,m_fAttributeA,m_fAttributeB,m_fAttributeC ,ui->m_editIb0,ui->m_editIb1);
	    GetSequenceValueTest(Moudle_I,STT_POWER_ZeroSequence,pMacroChCur_A,pMacroChCur_B,pMacroChCur_C
		                 ,m_fAttributeA,m_fAttributeB,m_fAttributeC,ui->m_editIc0,ui->m_editIc1);
	}
}

void PowerDiagramWidget::getLabVolCurText(QLabel *m_label)
{
	CString str;
	str=m_label->text();
	m_label->setText(str.left((str.length()-1))+QString::number(m_nCurrentGroup+1));
}

void PowerDiagramWidget::setlabNumVolCurText(int nModuleType)
{
	if (nModuleType == Moudle_U)
	{
		getLabVolCurText(ui->m_labVa);
		getLabVolCurText(ui->m_labVb);
		getLabVolCurText(ui->m_labVc);
	}
	else
	{
		getLabVolCurText(ui->m_labIa);
		getLabVolCurText(ui->m_labIb);
		getLabVolCurText(ui->m_labIc);
	}		
}
	

void PowerDiagramWidget::setCombVolCurText(int nModuleType)
{
	if (nModuleType==Moudle_U)
	{
		if (ui->m_combVolSet_3->currentIndex()==STT_POWER_VolSetType_LL)
		{
			ui->m_labVa->setText("Uab1");
			ui->m_labVb->setText("Ubc1");
			ui->m_labVc->setText("Uca1");
		}
		else if(ui->m_combVolSet_3->currentIndex()==STT_POWER_VolSetType_SE)
		{
			ui->m_labVa->setText("U1_1");
			ui->m_labVb->setText("U2_1");
			ui->m_labVc->setText("U0_1");
		}
	}
	else
	{
		if(ui->m_combCurSet_3->currentIndex()== STT_POWER_CurSetType_SE)
		{
			ui->m_labIa->setText("I1_1");
			ui->m_labIb->setText("I2_1");
			ui->m_labIc->setText("I0_1");
		}
	}	
}

void PowerDiagramWidget::getNameType(CSttMacroChannel *pSttChA,CSttMacroChannel *pSttChB,CSttMacroChannel *pSttChC,QLabel *m_labChNameA,QLabel *m_labChNameB,QLabel *m_labChNameC)

{
	if(pSttChA != NULL)
	{
		m_strChNameA=pSttChA->m_strName;
	}

	if (pSttChB != NULL)
	{
		m_strChNameB=pSttChB->m_strName;
	}

	if (pSttChC != NULL)
	{
		m_strChNameC=pSttChC->m_strName;
	}

	m_labChNameA->setText(m_strChNameA);
	m_labChNameB->setText(m_strChNameB);
	m_labChNameC->setText(m_strChNameC);	
}

void PowerDiagramWidget::cmbVolCurPhaseText()
{
	int i = m_nCurrentGroup*3; 	
	if(ui->m_combVolSet_3->currentIndex()==STT_POWER_VolSetType_LN)
	{	
		CSttMacroChannel *pChannelVolA = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
		CSttMacroChannel *pChannelVolB = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+1);
		CSttMacroChannel *pChannelVolC = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i+2);
		getNameType(pChannelVolA,pChannelVolB,pChannelVolC,ui->m_labVa,ui->m_labVb,ui->m_labVc);		
	}

	if(ui->m_combCurSet_3->currentIndex()==STT_POWER_CurSetType_LN)
	{
		CSttMacroChannel *pChannelCurA = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
		CSttMacroChannel *pChannelCurB = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+1);
		CSttMacroChannel *pChannelCurC = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i+2);	
		getNameType(pChannelCurA,pChannelCurB,pChannelCurC,ui->m_labIa,ui->m_labIb,ui->m_labIc);
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
}


long PowerDiagramWidget::getGroupCurPhaseCount()
{
	return power_GetCurrGroupChs(&m_pPowerSttTestResource->m_oCurChRsListRef, m_nCurrentGroup);
}

void PowerDiagramWidget::getGroupVolPhaseEdit()
{
	int i = m_nCurrentGroup*3;
	CString str;
	
	if (!g_TestWinBase->m_bViewTestStarted && m_pVOL)
	{

		long nVolrChs = getGroupVolPhaseCount();

		if (nVolrChs >= 1)
		{
			str.Format(_T("%.3fV"),m_pVOL[i].Harm[1].fAmp);
			ui->m_editVa0->setText(str);
			str.Format(_T("%.3f°"),m_pVOL[i].Harm[1].fAngle);
			ui->m_editVa1->setText(str);
			str.Format(_T("%.3fHz"),m_pVOL[i].Harm[1].fFreq);
			ui->m_editVa2->setText(str);
		}
		else
		{//电压和电流的组数有可能不同，会导致当前组的电流通道数为0
			str = "--";
			ui->m_editVa0->setText(str);
			ui->m_editVa1->setText(str);
			ui->m_editVa2->setText(str);
		}

		if (nVolrChs >= 2)
		{
			str.Format(_T("%.3fV"),m_pVOL[i+1].Harm[1].fAmp);
			ui->m_editVb0->setText(str);
			str.Format(_T("%.3f°"),m_pVOL[i+1].Harm[1].fAngle);
			ui->m_editVb1->setText(str);
			str.Format(_T("%.3fHz"),m_pVOL[i+1].Harm[1].fFreq);
			ui->m_editVb2->setText(str);
		}
		else
		{
			str = "--";
			ui->m_editVb0->setText(str);
			ui->m_editVb1->setText(str);
			ui->m_editVb2->setText(str);
		}

		if (nVolrChs >= 3)
		{
			str.Format(_T("%.3fV"),m_pVOL[i+2].Harm[1].fAmp);
			ui->m_editVc0->setText(str);
			str.Format(_T("%.3f°"),m_pVOL[i+2].Harm[1].fAngle);
			ui->m_editVc1->setText(str);
			str.Format(_T("%.3fHz"),m_pVOL[i+2].Harm[1].fFreq);
			ui->m_editVc2->setText(str);
		}
		else
		{
			str = "--";
			ui->m_editVc0->setText(str);
			ui->m_editVc1->setText(str);
			ui->m_editVc2->setText(str);
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


	TypeSttVolCurCh(Moudle_U,pChannelVolA,m_fAttributeA);
	TypeSttVolCurCh(Moudle_U,pChannelVolB,m_fAttributeB);
	TypeSttVolCurCh(Moudle_U,pChannelVolC,m_fAttributeC);

	if (nVolrChs >= 1)
	{
		str.Format(_T("%.3fV"),m_fAttributeA[0]);
		ui->m_editVa0->setText(str);
		str.Format(_T("%.3f°"),m_fAttributeA[1]);
		ui->m_editVa1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeA[2]);
		ui->m_editVa2->setText(str);
	}
	else
	{//电压和电流的组数有可能不同，会导致当前组的电流通道数为0
		str = "--";
		ui->m_editVa0->setText(str);
		ui->m_editVa1->setText(str);
		ui->m_editVa2->setText(str);
	}

	if (nVolrChs >= 2)
	{
		str.Format(_T("%.3fV"),m_fAttributeB[0]);
		ui->m_editVb0->setText(str);
		str.Format(_T("%.3f°"),m_fAttributeB[1]);
		ui->m_editVb1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeB[2]);
		ui->m_editVb2->setText(str);
	}
	else
	{
		str = "--";
		ui->m_editVb0->setText(str);
		ui->m_editVb1->setText(str);
		ui->m_editVb2->setText(str);
	}

	if (nVolrChs >= 3)
	{
		str.Format(_T("%.3fV"),m_fAttributeC[0]);
		ui->m_editVc0->setText(str);
		str.Format(_T("%.3f°"),m_fAttributeC[1]);
		ui->m_editVc1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeC[2]);
		ui->m_editVc2->setText(str);
	}
	else
	{
		str = "--";
		ui->m_editVc0->setText(str);
		ui->m_editVc1->setText(str);
		ui->m_editVc2->setText(str);
	}	    	
}

void PowerDiagramWidget::getGroupCurPhaseEdit()
{
	int i = m_nCurrentGroup*3;
	CString str;
	if (!g_TestWinBase->m_bViewTestStarted && m_pCUR)
	{
		long nCurrChs = getGroupCurPhaseCount();

		if (nCurrChs >= 1)
		{
			str.Format(_T("%.3fA"),m_pCUR[i].Harm[1].fAmp);
			ui->m_editIa0->setText(str);
			str.Format(_T("%.3f°"),m_pCUR[i].Harm[1].fAngle);
			ui->m_editIa1->setText(str);
			str.Format(_T("%.3fHz"),m_pCUR[i].Harm[1].fFreq);
			ui->m_editIa2->setText(str);
		}
		else
		{//电压和电流的组数有可能不同，会导致当前组的电流通道数为0
			str = "--";
			ui->m_editIa0->setText(str);
			ui->m_editIa1->setText(str);
			ui->m_editIa2->setText(str);
		}

		if (nCurrChs >= 2)
		{
			str.Format(_T("%.3fA"),m_pCUR[i+1].Harm[1].fAmp);
			ui->m_editIb0->setText(str);
			str.Format(_T("%.3f°"),m_pCUR[i+1].Harm[1].fAngle);
			ui->m_editIb1->setText(str);
			str.Format(_T("%.3fHz"),m_pCUR[i+1].Harm[1].fFreq);
			ui->m_editIb2->setText(str);
		}
		else
		{
			str = "--";
			ui->m_editIb0->setText(str);
			ui->m_editIb1->setText(str);
			ui->m_editIb2->setText(str);
		}

		if (nCurrChs >= 3)
		{
			str.Format(_T("%.3fA"),m_pCUR[i+2].Harm[1].fAmp);
			ui->m_editIc0->setText(str);
			str.Format(_T("%.3f°"),m_pCUR[i+2].Harm[1].fAngle);
			ui->m_editIc1->setText(str);
			str.Format(_T("%.3fHz"),m_pCUR[i+2].Harm[1].fFreq);
			ui->m_editIc2->setText(str);
		}
		else
		{
			str = "--";
			ui->m_editIc0->setText(str);
			ui->m_editIc1->setText(str);
			ui->m_editIc2->setText(str);
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


	TypeSttVolCurCh(Moudle_I,pChannelCurA,m_fAttributeA);
	TypeSttVolCurCh(Moudle_I,pChannelCurB,m_fAttributeB);
	TypeSttVolCurCh(Moudle_I,pChannelCurC,m_fAttributeC);

	if (nCurrChs >= 1)
	{
		str.Format(_T("%.3fA"),m_fAttributeA[3]);
		ui->m_editIa0->setText(str);
		str.Format(_T("%.3f°"),m_fAttributeA[4]);
		ui->m_editIa1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeA[5]);
		ui->m_editIa2->setText(str);
	}
	else
	{
		str = "--";
		ui->m_editIa0->setText(str);
		ui->m_editIa1->setText(str);
		ui->m_editIa2->setText(str);
	}

	if (nCurrChs >= 2)
	{
		str.Format(_T("%.3fA"),m_fAttributeB[3]);
		ui->m_editIb0->setText(str);
		str.Format(_T("%.3f°"),m_fAttributeB[4]);
		ui->m_editIb1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeB[5]);
		ui->m_editIb2->setText(str);
	}
	else
	{
		str = "--";
		ui->m_editIb0->setText(str);
		ui->m_editIb1->setText(str);
		ui->m_editIb2->setText(str);
	}

	if (nCurrChs >= 3)
	{
		str.Format(_T("%.3fA"),m_fAttributeC[3]);
		ui->m_editIc0->setText(str);
		str.Format(_T("%.3f°"),m_fAttributeC[4]);
		ui->m_editIc1->setText(str);
		str.Format(_T("%.3fHz"),m_fAttributeC[5]);
		ui->m_editIc2->setText(str);
	}
	else
	{
		str = "--";
		ui->m_editIc0->setText(str);
		ui->m_editIc1->setText(str);
		ui->m_editIc2->setText(str);
	}	    	
}

void PowerDiagramWidget::TimerStart()
{
	m_nTimerID = startTimer(1000);
}

void PowerDiagramWidget::TimerStop(bool bUpdate)
{
	killTimer(m_nTimerID);
	m_nTimerID = -1;
}

void PowerDiagramWidget::timerEvent(QTimerEvent *event)
{
	if(m_nTimerID == event->timerId())
	{
		getPowerValueTest();
		getVolSetChangedTest();
		getCurSetChangedTest();
		QWidget::timerEvent( event );
	}
}

void PowerDiagramWidget::setDCChanged(bool bDCTest)
{
	m_bDCTest = bDCTest;
	initData();
}

void PowerDiagramWidget::OnRtDataChanged()
{
	initData();
}

void PowerDiagramWidget::setDC(bool bDC)
{
	if (bDC)
	{
		ui->m_editVa1->setEnabled(false);
		ui->m_editVb1->setEnabled(false);
		ui->m_editVc1->setEnabled(false);
		ui->m_editVa2->setEnabled(false);
		ui->m_editVb2->setEnabled(false);
		ui->m_editVc2->setEnabled(false);

		ui->m_editIa1->setEnabled(false);
		ui->m_editIb1->setEnabled(false);
		ui->m_editIc1->setEnabled(false);
		ui->m_editIa2->setEnabled(false);
		ui->m_editIb2->setEnabled(false);
		ui->m_editIc2->setEnabled(false);
	}	
	else
	{
		ui->m_editVa1->setEnabled(true);
		ui->m_editVb1->setEnabled(true);
		ui->m_editVc1->setEnabled(true);
		ui->m_editVa2->setEnabled(true);
		ui->m_editVb2->setEnabled(true);
		ui->m_editVc2->setEnabled(true);

		ui->m_editIa1->setEnabled(true);
		ui->m_editIb1->setEnabled(true);
		ui->m_editIc1->setEnabled(true);
		ui->m_editIa2->setEnabled(true);
		ui->m_editIb2->setEnabled(true);
		ui->m_editIc2->setEnabled(true);
	}
}

void PowerDiagramWidget::InitLanuage()
{
	xlang_SetLangStrToWidget_Txt(ui->m_labVolAmplitude,g_sLangTxt_Native_Amplitude,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_labVolPhase,g_sLangTxt_Native_Phase,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_labVolFrequency,g_sLangTxt_Native_Freq,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_labCurAmplitude,g_sLangTxt_Native_Amplitude,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_labCurPhase,g_sLangTxt_Native_Phase,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_labCurFrequency,g_sLangTxt_Native_Freq,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblVolSet_3,g_sLangTxt_Gradient_VoltageSet,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblCurSet_3,g_sLangTxt_Gradient_CurrentSet,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblAPhase,g_sLangTxt_Aphase,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblBPhase,g_sLangTxt_Bphase,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblCPhase,g_sLangTxt_Cphase,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblTotalPower,g_sLangTxt_Native_TotalPow,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblPowerFactor,g_sLangTxt_Native_PowFactor,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblActivePower,g_sLangTxt_Native_ActPower,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblReactivePower,g_sLangTxt_Native_ReacPower,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblApparentPower,g_sLangTxt_Native_AppPower,XLang_Ctrls_QLabel);

	ui->m_combVolSet_3->clear();
	ui->m_combVolSet_3->addItem(g_sLangTxt_Native_VolSetTypeLN);
	ui->m_combVolSet_3->addItem(g_sLangTxt_Native_VolSetTypeLL);
	ui->m_combVolSet_3->addItem(g_sLangTxt_Native_SeqComp);

	ui->m_combCurSet_3->clear();
	ui->m_combCurSet_3->addItem(g_sLangTxt_Native_CurSetTypeLN);
	ui->m_combCurSet_3->addItem(g_sLangTxt_Native_SeqComp);
}
