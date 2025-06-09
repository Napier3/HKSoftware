#include "powerwidget.h"
#include "../../CommonMethod/commonMethod.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttXTestMngrBaseApp.h"
#include "../ReportView/XLangResource_PowerTestWin.h"
#include"../../XLanguage/QT/XLanguageAPI_QT.h"
PowerWidget::PowerWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	InitLanguage();
	m_uiVOL = NULL;
	m_uiCUR = NULL;
	m_bDC = FALSE;

	m_nRowNum = 0;
	m_AllGroup = 0;
	m_NeedUGroup = 0;
	m_nCurrentGroup = 1;
}

PowerWidget::~PowerWidget()
{
	
}

void PowerWidget::setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource)
{
	if (pSttTestResource == NULL)
	{
		return;
	}

	m_pSttTestResource = pSttTestResource;

	m_NeedUGroup = 0;
	m_NeedIGroup = 0;

	int nChannelNum = m_pSttTestResource->m_oVolChRsListRef.GetCount();
	ASSERT(nChannelNum>=3);

	if (nChannelNum <= 4)
	{
		m_NeedUGroup = 1;
	}
	else
	{
		m_NeedUGroup = nChannelNum/3;
	}

	nChannelNum = m_pSttTestResource->m_oCurChRsListRef.GetCount();
	ASSERT(nChannelNum>=3);

	if (nChannelNum <= 4)
	{
		m_NeedIGroup = 1;
	}
	else
	{
		m_NeedIGroup = nChannelNum/3;
	}

	m_nRowNum = 4;

	m_AllGroup = (m_NeedUGroup >= m_NeedIGroup)?m_NeedIGroup:m_NeedUGroup;

	m_pVolChList = &m_pSttTestResource->m_oVolChRsListRef;
	m_pCurChList = &m_pSttTestResource->m_oCurChRsListRef;
}

void PowerWidget::setData(tmt_channel* pVOL,tmt_channel* pCUR)
{
	m_uiVOL = pVOL;
	m_uiCUR = pCUR;

	InitUI();
}

void PowerWidget::InitUI()
{
	ui.m_table->setStyleSheet(QString::fromUtf8("background-color: rgb(167,183,181);"));
	QHeaderView* pTop = ui.m_table->horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	QHeaderView* pLeft = ui.m_table->verticalHeader();
	pLeft->setDefaultSectionSize(50);
	pLeft->setVisible(false);

	ui.m_table->horizontalHeader()->setStretchLastSection(true); 
	ui.m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_headerList<</*tr("名称")*/g_sLangTxt_Name<</*tr("功率因数")*/g_sLangTxt_Native_PowFactor<</*tr("有功功率")*/g_sLangTxt_Native_ActPower<</*tr("无功功率")*/g_sLangTxt_Native_ReacPower<</*tr("视在功率")*/g_sLangTxt_Native_AppPower;
	ui.m_table->setHorizontalHeaderLabels(m_headerList);
	ui.m_table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(171,167,176);}"); 
	ui.m_table->horizontalHeader()->setFixedHeight(30);
	int temp = ui.m_table->horizontalHeader()->height();

	ui.m_table->setColumnCount(5);
	ui.m_table->setHorizontalHeaderLabels(m_headerList);
	QFontMetrics fontMetrics = QFontMetrics(font());
	int nLabelWidth1 = fontMetrics.width(/*tr("总功率(W)")*/g_sLangTxt_Native_TotalPow+"(W)") + 30;
	int nLabelWidth2 = fontMetrics.width(/*tr("功率因数")*/g_sLangTxt_Native_PowFactor) + 30;
	int nLabelWidth3 = fontMetrics.width(/*tr("有功功率")*/g_sLangTxt_Native_ActPower) + 30;
	int nLabelWidth4 = fontMetrics.width(/*tr("无功功率")*/g_sLangTxt_Native_ReacPower) + 30;
	int nLabelWidth5 = fontMetrics.width(/*tr("视在功率")*/g_sLangTxt_Native_AppPower) + 30;

	ui.m_table->setColumnWidth(0,nLabelWidth1);
	ui.m_table->setColumnWidth(1,nLabelWidth2);
	ui.m_table->setColumnWidth(2,nLabelWidth3);
	ui.m_table->setColumnWidth(3,nLabelWidth4);
	ui.m_table->setColumnWidth(4,nLabelWidth5);

	int nRowHeight = fontMetrics.height() + 5;

	for (int i=0; i< m_nRowNum;i++)
	{
		QTableWidgetItem *item1 = new QTableWidgetItem();
		item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item2 = new QTableWidgetItem();
		item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item3 = new QTableWidgetItem();
		item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item4 = new QTableWidgetItem();
		item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item5 = new QTableWidgetItem();
		item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

		int rowCount = ui.m_table->rowCount();
		ui.m_table->insertRow(rowCount);
		ui.m_table->setRowHeight(rowCount,30);
		ui.m_table->setItem(rowCount, 0, item1);   	
		ui.m_table->setItem(rowCount, 1, item2);  
		ui.m_table->setItem(rowCount, 2, item3); 
		ui.m_table->setItem(rowCount, 3, item4); 
		ui.m_table->setItem(rowCount, 4, item5); 

		ui.m_table->setRowHeight(rowCount,nRowHeight);
	}

	//初始化固定名称
	ui.m_table->item(0,0)->setText(/*tr("A相")*/g_sLangTxt_Aphase);	
	ui.m_table->item(1,0)->setText(/*tr("B相")*/g_sLangTxt_Bphase);	
	ui.m_table->item(2,0)->setText(/*tr("C相")*/g_sLangTxt_Cphase);	
	ui.m_table->item(3,0)->setText(/*tr("总功率(W))")*/g_sLangTxt_Native_TotalPow+"(W)");	

//	ui.m_ButtonNext->setIcon(QPixmap( "./images/Button-Next.png"));
	ui.m_ButtonNext->setStyleSheet("background-color: rgb(255, 255, 255);");

//	ui.m_ButtonPrevious->setIcon(QPixmap( "./images/Button-Previous.png"));
	ui.m_ButtonPrevious->setStyleSheet("background-color: rgb(255, 255, 255);");

	ui.m_labelText->setStyleSheet("background-color: rgb(255, 255, 255);");
	ui.m_labelText->setText(QString(/*tr("总组数: %1")*/g_sLangTxt_Native_AllGroup+" %1").arg(1) + "\n" + QString(/*tr("当前组: %1")*/g_sLangTxt_Native_CurGroup+" %1").arg(1));

	connect(ui.m_ButtonNext, SIGNAL(clicked()), this, SLOT(slot_PbnNextClicked()));
	connect(ui.m_ButtonPrevious, SIGNAL(clicked()), this, SLOT(slot_PbnPreClicked()));
}

void PowerWidget::setDCChanged(bool bDC)
{
	m_bDC = bDC;
	updateData();
}

void PowerWidget::updateData()
{
	if (m_uiVOL == NULL || m_uiCUR == NULL)
	{
		return;
	}

	UpdateGroupText();

	if (g_oSttTestResourceMngr.IsSyncMode())
	{
		int nStart = 0;
		int nEnd = 0;
		CSttMacroChannel *pMacroCh_UA,*pMacroCh_UB,*pMacroCh_UC,*pMacroCh_IA,*pMacroCh_IB,*pMacroCh_IC;
		tmt_Channel channelPara_UA,channelPara_UB,channelPara_UC,channelPara_IA,channelPara_IB,channelPara_IC;

		if (m_nCurrentGroup<=m_AllGroup)
		{
			getGroupPosRange(m_nCurrentGroup,nStart,nEnd);
			if(nEnd-nStart>= 2)
			{
				pMacroCh_UA = (CSttMacroChannel*)m_pVolChList->GetAtIndex(nStart);
				if(pMacroCh_UA==NULL){
					return;
				}
				channelPara_UA.Harm[1].fAmp = pMacroCh_UA->m_oRtDataCh.m_fMag;
				channelPara_UA.Harm[1].fAngle = pMacroCh_UA->m_oRtDataCh.m_fAng;
				channelPara_UA.Harm[1].fFreq = pMacroCh_UA->m_oRtDataCh.m_fFreq;

				pMacroCh_UB = (CSttMacroChannel*)m_pVolChList->GetAtIndex(nStart+1);
				if(pMacroCh_UB==NULL){
					return;
				}
				channelPara_UB.Harm[1].fAmp = pMacroCh_UB->m_oRtDataCh.m_fMag;
				channelPara_UB.Harm[1].fAngle = pMacroCh_UB->m_oRtDataCh.m_fAng;
				channelPara_UB.Harm[1].fFreq = pMacroCh_UB->m_oRtDataCh.m_fFreq;

				pMacroCh_UC = (CSttMacroChannel*)m_pVolChList->GetAtIndex(nStart+2);
				if(pMacroCh_UC==NULL){
					return;
				}
				channelPara_UC.Harm[1].fAmp = pMacroCh_UC->m_oRtDataCh.m_fMag;
				channelPara_UC.Harm[1].fAngle = pMacroCh_UC->m_oRtDataCh.m_fAng;
				channelPara_UC.Harm[1].fFreq = pMacroCh_UC->m_oRtDataCh.m_fFreq;

				pMacroCh_IA = (CSttMacroChannel*)m_pCurChList->GetAtIndex(nStart);
				if(pMacroCh_IA==NULL){
					return;
				}
				channelPara_IA.Harm[1].fAmp = pMacroCh_IA->m_oRtDataCh.m_fMag;
				channelPara_IA.Harm[1].fAngle = pMacroCh_IA->m_oRtDataCh.m_fAng;
				channelPara_IA.Harm[1].fFreq = pMacroCh_IA->m_oRtDataCh.m_fFreq;

				pMacroCh_IB = (CSttMacroChannel*)m_pCurChList->GetAtIndex(nStart+1);
				if(pMacroCh_IB==NULL){
					return;
				}
				channelPara_IB.Harm[1].fAmp = pMacroCh_IB->m_oRtDataCh.m_fMag;
				channelPara_IB.Harm[1].fAngle = pMacroCh_IB->m_oRtDataCh.m_fAng;
				channelPara_IB.Harm[1].fFreq = pMacroCh_IB->m_oRtDataCh.m_fFreq;

				pMacroCh_IC = (CSttMacroChannel*)m_pCurChList->GetAtIndex(nStart+2);
				if(pMacroCh_IC==NULL){
					return;
				}
				channelPara_IC.Harm[1].fAmp = pMacroCh_IC->m_oRtDataCh.m_fMag;
				channelPara_IC.Harm[1].fAngle = pMacroCh_IC->m_oRtDataCh.m_fAng;
				channelPara_IC.Harm[1].fFreq = pMacroCh_IC->m_oRtDataCh.m_fFreq;

				PowerValue power0;

                if (g_theSttXTestMngrBaseApp->m_bViewTestStarted)
				{
					power0 = GetPowerValue( m_bDC, &channelPara_UA, &channelPara_UB, &channelPara_UC, &channelPara_IA, &channelPara_IB, &channelPara_IC);
				}
				else
				{
					power0 = GetPowerValue( m_bDC, &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2], &m_uiCUR[nStart], &m_uiCUR[nStart+1], &m_uiCUR[nStart+2]);
				}

				ui.m_table->item(0,1)->setText(QString("%1").arg(power0.FactorA, 0, 'f', 3));	
				ui.m_table->item(1,1)->setText(QString("%1").arg(power0.FactorB, 0, 'f', 3));	
				ui.m_table->item(2,1)->setText(QString("%1").arg(power0.FactorC, 0, 'f', 3));	
				ui.m_table->item(3,1)->setText("");	

				ui.m_table->item(0,2)->setText(QString("%1").arg(power0.PA, 0, 'f', 3));	
				ui.m_table->item(1,2)->setText(QString("%1").arg(power0.PB, 0, 'f', 3));	
				ui.m_table->item(2,2)->setText(QString("%1").arg(power0.PC, 0, 'f', 3));	
				ui.m_table->item(3,2)->setText(QString("%1").arg(power0.PSum, 0, 'f', 3));

				ui.m_table->item(0,3)->setText(QString("%1").arg(power0.QA, 0, 'f', 3));	
				ui.m_table->item(1,3)->setText(QString("%1").arg(power0.QB, 0, 'f', 3));	
				ui.m_table->item(2,3)->setText(QString("%1").arg(power0.QC, 0, 'f', 3));	
				ui.m_table->item(3,3)->setText(QString("%1").arg(power0.QSum, 0, 'f', 3));

				ui.m_table->item(0,4)->setText(QString("%1").arg(power0.SA, 0, 'f', 3));	
				ui.m_table->item(1,4)->setText(QString("%1").arg(power0.SB, 0, 'f', 3));	
				ui.m_table->item(2,4)->setText(QString("%1").arg(power0.SC, 0, 'f', 3));	
				ui.m_table->item(3,4)->setText(QString("%1").arg(power0.SSum, 0, 'f', 3));
			}
		}
	}
}

void PowerWidget::getGroupPosRange(int nGroup, int& nStart, int& nEnd)
{
	if (m_AllGroup == 0 || nGroup <= 0 || nGroup > m_AllGroup)
	{
		nStart = nEnd = 0;
		return;
	}

	if (nGroup <= m_AllGroup)
	{
		nStart = (nGroup-1)*3;
		nEnd = nStart + 2;
	}
}

void PowerWidget::OnRtDataChanged()
{
	updateData();
}

void PowerWidget::UpdateGroupText()
{
	QString str = QString(/*tr("总组数: %1")*/g_sLangTxt_Native_AllGroup+" %1").arg(m_AllGroup)+ "\n" + QString(/*tr("当前组: %1")*/g_sLangTxt_Native_CurGroup+" %1").arg(m_nCurrentGroup);
	ui.m_labelText->setText(str);
}

void PowerWidget::slot_PbnNextClicked()
{
	QString str;

	m_nCurrentGroup++;
	if (m_nCurrentGroup>m_AllGroup)
	{
		m_nCurrentGroup = m_AllGroup;
	}
	
	updateData();
}

void PowerWidget::slot_PbnPreClicked()
{
	m_nCurrentGroup--;
	if (m_nCurrentGroup<1)
	{
		m_nCurrentGroup = 1;
	}
	
	updateData();
}

void PowerWidget::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui.m_ButtonPrevious,g_sLangTxt_Natve_LastGroup,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui.m_ButtonNext,g_sLangTxt_Natve_NextGroup,XLang_Ctrls_QPushButton);
}
