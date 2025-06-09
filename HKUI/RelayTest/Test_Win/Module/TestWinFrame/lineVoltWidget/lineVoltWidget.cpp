#include "lineVoltWidget.h"
#include "../../CommonMethod/commonMethod.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttXTestMngrBaseApp.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

LineVoltWidget::LineVoltWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	xlang_SetLangStrToWidget_Txt(ui.m_ButtonPrevious,g_sLangTxt_Natve_LastGroup,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui.m_ButtonNext,g_sLangTxt_Natve_NextGroup,XLang_Ctrls_QPushButton);

	m_uiVOL = NULL;
	m_uiCUR = NULL;
	m_bDC = FALSE;

	m_nRowNum = 0;
	m_AllGroup = 0;
	m_nCurrentGroup = 1;
}

LineVoltWidget::~LineVoltWidget()
{

}

void LineVoltWidget::setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource)
{
	if (pSttTestResource == NULL)
	{
		return;
	}

	m_pSttTestResource = pSttTestResource;

	int nChannelNum = m_pSttTestResource->m_oVolChRsListRef.GetCount();

	if(nChannelNum < 3)
	{
		return;
	}

	if (nChannelNum <= 4)
	{
		m_AllGroup = 1;
	}
	else
	{
		m_AllGroup = nChannelNum/3;
	}

	m_nRowNum = 3;

	m_pVolChList = &m_pSttTestResource->m_oVolChRsListRef;
	m_pCurChList = &m_pSttTestResource->m_oCurChRsListRef;
}

void LineVoltWidget::setData(tmt_channel* pVOL,tmt_channel* pCUR)
{
	m_uiVOL = pVOL;
	m_uiCUR = pCUR;

	InitUI();
}

void LineVoltWidget::InitUI()
{
	ui.m_table->setStyleSheet(QString::fromUtf8("background-color: rgb(167,183,181);"));
	QHeaderView* pTop = ui.m_table->horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	QHeaderView* pLeft = ui.m_table->verticalHeader();
	pLeft->setDefaultSectionSize(50);
	pLeft->setVisible(false);

	ui.m_table->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	ui.m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_headerList<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(V)")*/g_sLangTxt_Native_amplitudeV<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase<</*tr("频率(HZ)")*/g_sLangTxt_Native_FreqHz;
	ui.m_table->setHorizontalHeaderLabels(m_headerList);
	ui.m_table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(171,167,176);}"); //设置表头背景色
	ui.m_table->horizontalHeader()->setFixedHeight(30);
	int temp = ui.m_table->horizontalHeader()->height();

	ui.m_table->setColumnCount(4);
	ui.m_table->setHorizontalHeaderLabels(m_headerList);
	QFontMetrics fontMetrics = QFontMetrics(font());
	int nLabelWidth1 = fontMetrics.width(/*tr("名称")*/g_sLangTxt_Name) + 30;
	int nLabelWidth2 = fontMetrics.width(tr("900.000")) + 80;
	int nLabelWidth3 = fontMetrics.width(/*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase) + 40;
	int nLabelWidth4 = fontMetrics.width(/*tr("频率(HZ)")*/g_sLangTxt_Native_FreqHz) + 80;

	ui.m_table->setColumnWidth(0,nLabelWidth1);
	ui.m_table->setColumnWidth(1,nLabelWidth2);
	ui.m_table->setColumnWidth(2,nLabelWidth3);
	ui.m_table->setColumnWidth(3,nLabelWidth4);

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

		int rowCount = ui.m_table->rowCount();
		ui.m_table->insertRow(rowCount);
		ui.m_table->setRowHeight(rowCount,30);
		ui.m_table->setItem(rowCount, 0, item1);   	
		ui.m_table->setItem(rowCount, 1, item2);  
		ui.m_table->setItem(rowCount, 2, item3); 
		ui.m_table->setItem(rowCount, 3, item4);

		ui.m_table->setRowHeight(rowCount,nRowHeight);
	}

//	ui.m_ButtonNext->setIcon(QPixmap( "./images/Button-Next.png"));
	ui.m_ButtonNext->setStyleSheet("background-color: rgb(255, 255, 255);");

//	ui.m_ButtonPrevious->setIcon(QPixmap( "./images/Button-Previous.png"));
	ui.m_ButtonPrevious->setStyleSheet("background-color: rgb(255, 255, 255);");

	ui.m_labelText->setStyleSheet("background-color: rgb(255, 255, 255);");
	ui.m_labelText->setText(QString(/*tr("总组数: %1")*/g_sLangTxt_Native_TotalGroupsParam).arg(1) + "\n" + QString(/*tr("当前组: %1")*/g_sLangTxt_Native_CurrentGroupParam).arg(1));

	connect(ui.m_ButtonNext, SIGNAL(clicked()), this, SLOT(slot_PbnNextClicked()));
	connect(ui.m_ButtonPrevious, SIGNAL(clicked()), this, SLOT(slot_PbnPreClicked()));
}

void LineVoltWidget::setDCChanged(bool bDC)
{
	m_bDC = bDC;
	updateData();
}

void LineVoltWidget::OnRtDataChanged()
{
	updateData();
}

QString LineVoltWidget::GetULineVoltName(CSttMacroChannel*pChannelA, CSttMacroChannel*pChannelB)
{
	QString strULineVoltName;

	if (pChannelA == NULL || pChannelB == NULL)
	{
		strULineVoltName = "";
	}
	else
	{
		QString strTemp1 = pChannelA->m_strName.Mid(1);
		QString strTemp2 = pChannelB->m_strName.Mid(1);

		strULineVoltName = QString("U%1%2").arg(strTemp1).arg(strTemp2);
	}

	return strULineVoltName;
}

void LineVoltWidget::updateData()
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
		CSttMacroChannel* pMacroCh_A = NULL;
		CSttMacroChannel* pMacroCh_B = NULL;
		CSttMacroChannel* pMacroCh_C = NULL;
		tmt_Channel channelPara_A,channelPara_B,channelPara_C;

		if (m_nCurrentGroup<=m_AllGroup)
		{
			getGroupPosRange(m_nCurrentGroup,nStart,nEnd);
			if(nEnd-nStart>= 2)
			{
				pMacroCh_A = (CSttMacroChannel*)m_pVolChList->GetAtIndex(nStart);
				if(pMacroCh_A==NULL){
					return;
				}

				channelPara_A.Harm[1].fAmp = pMacroCh_A->m_oRtDataCh.m_fMag;
				channelPara_A.Harm[1].fAngle = pMacroCh_A->m_oRtDataCh.m_fAng;
				channelPara_A.Harm[1].fFreq = pMacroCh_A->m_oRtDataCh.m_fFreq;

				pMacroCh_B = (CSttMacroChannel*)m_pVolChList->GetAtIndex(nStart+1);
				if(pMacroCh_B==NULL){
					return;
				}

				channelPara_B.Harm[1].fAmp = pMacroCh_B->m_oRtDataCh.m_fMag;
				channelPara_B.Harm[1].fAngle = pMacroCh_B->m_oRtDataCh.m_fAng;
				channelPara_B.Harm[1].fFreq = pMacroCh_B->m_oRtDataCh.m_fFreq;

				pMacroCh_C = (CSttMacroChannel*)m_pVolChList->GetAtIndex(nStart+2);
				if(pMacroCh_C==NULL){
					return;
				}

				channelPara_C.Harm[1].fAmp = pMacroCh_C->m_oRtDataCh.m_fMag;
				channelPara_C.Harm[1].fAngle = pMacroCh_C->m_oRtDataCh.m_fAng;
				channelPara_C.Harm[1].fFreq = pMacroCh_C->m_oRtDataCh.m_fFreq;

				//刷新线电压名称
				ui.m_table->item(0,0)->setText(GetULineVoltName(pMacroCh_A,pMacroCh_B));	
				ui.m_table->item(1,0)->setText(GetULineVoltName(pMacroCh_B,pMacroCh_C));	
				ui.m_table->item(2,0)->setText(GetULineVoltName(pMacroCh_C,pMacroCh_A));	

				if (m_bDC)
				{
					ui.m_table->item(0,2)->setText("0");	
					ui.m_table->item(1,2)->setText("0");	
					ui.m_table->item(2,2)->setText("0");

					ui.m_table->item(0,3)->setText("0");	
					ui.m_table->item(1,3)->setText("0");	
					ui.m_table->item(2,3)->setText("0");
				}
				else
				{
                    if(g_theSttXTestMngrBaseApp->m_bViewTestStarted)
					{
						ui.m_table->item(0,2)->setText(QString("%1").arg(GetASubBAngle( &channelPara_A, &channelPara_B ), 0, 'f', 3));	
						ui.m_table->item(1,2)->setText(QString("%1").arg(GetASubBAngle( &channelPara_B, &channelPara_C ), 0, 'f', 3));	
						ui.m_table->item(2,2)->setText(QString("%1").arg(GetASubBAngle( &channelPara_C, &channelPara_A ), 0, 'f', 3));	

						ui.m_table->item(0,3)->setText(QString("%1").arg(channelPara_A.Harm[1].fFreq, 0, 'f', 3));	
						ui.m_table->item(1,3)->setText(QString("%1").arg(channelPara_B.Harm[1].fFreq, 0, 'f', 3));	
						ui.m_table->item(2,3)->setText(QString("%1").arg(channelPara_C.Harm[1].fFreq, 0, 'f', 3));	
					}
					else
					{
						ui.m_table->item(0,2)->setText(QString("%1").arg(GetASubBAngle( &m_uiVOL[nStart], &m_uiVOL[nStart+1] ), 0, 'f', 3));	
						ui.m_table->item(1,2)->setText(QString("%1").arg(GetASubBAngle( &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ), 0, 'f', 3));	
						ui.m_table->item(2,2)->setText(QString("%1").arg(GetASubBAngle( &m_uiVOL[nStart+2], &m_uiVOL[nStart] ), 0, 'f', 3));	

						ui.m_table->item(0,3)->setText(QString("%1").arg(m_uiVOL[nStart].Harm[1].fFreq, 0, 'f', 3));	
						ui.m_table->item(1,3)->setText(QString("%1").arg(m_uiVOL[nStart+1].Harm[1].fFreq, 0, 'f', 3));	
						ui.m_table->item(2,3)->setText(QString("%1").arg(m_uiVOL[nStart+2].Harm[1].fFreq, 0, 'f', 3));	
					}
				}

                if(g_theSttXTestMngrBaseApp->m_bViewTestStarted)
				{
					ui.m_table->item(0,1)->setText(QString("%1").arg(GetASubBAmp( &channelPara_A, &channelPara_B ), 0, 'f', 3));		//Uab幅值
					ui.m_table->item(1,1)->setText(QString("%1").arg(GetASubBAmp( &channelPara_B, &channelPara_C ), 0, 'f', 3));		//Ubc幅值
					ui.m_table->item(2,1)->setText(QString("%1").arg(GetASubBAmp( &channelPara_C, &channelPara_A ), 0, 'f', 3));		//Uca幅值
				}
				else
				{
					ui.m_table->item(0,1)->setText(QString("%1").arg(GetASubBAmp( &m_uiVOL[nStart], &m_uiVOL[nStart+1] ), 0, 'f', 3));	//Uab幅值
					ui.m_table->item(1,1)->setText(QString("%1").arg(GetASubBAmp( &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ), 0, 'f', 3));//Ubc幅值
					ui.m_table->item(2,1)->setText(QString("%1").arg(GetASubBAmp( &m_uiVOL[nStart+2], &m_uiVOL[nStart] ), 0, 'f', 3));	//Uca幅值
				}
			}
		}
	}
}

void LineVoltWidget::getGroupPosRange(int nGroup, int& nStart, int& nEnd)
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

void LineVoltWidget::UpdateGroupText()
{
	QString str = QString(/*tr("总组数: %1")*/g_sLangTxt_Native_TotalGroupsParam).arg(m_AllGroup)+ "\n" + QString(/*tr("当前组: %1")*/g_sLangTxt_Native_CurrentGroupParam).arg(m_nCurrentGroup);
	ui.m_labelText->setText(str);
}

void LineVoltWidget::slot_PbnNextClicked()
{
	QString str;

	m_nCurrentGroup++;
	if (m_nCurrentGroup>m_AllGroup)
	{
		m_nCurrentGroup = m_AllGroup;
	}
	
	updateData();
}

void LineVoltWidget::slot_PbnPreClicked()
{
	m_nCurrentGroup--;
	if (m_nCurrentGroup<1)
	{
		m_nCurrentGroup = 1;
	}
	
	updateData();
}
