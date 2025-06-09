#include "seqWidget.h"
#include "../../CommonMethod/commonMethod.h"
#include "../../../../Module/SttTest/Common/tmt_system_config.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttXTestMngrBaseApp.h"
#include "../ReportView/XLangResource_PowerTestWin.h"
#include "../../XLanguage/QT/XLanguageAPI_QT.h"

SeqWidget::SeqWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_uiVOL = NULL;
	m_uiCUR = NULL;
	m_bDC = FALSE;

	m_nRowNum = 0;
	m_AllGroup = 0;
	m_NeedUGroup = 0;
	m_NeedIGroup = 0;
	m_nCurrentGroup = 1;
}

SeqWidget::~SeqWidget()
{

}

void SeqWidget::setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource)
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

	m_nRowNum = 6;  //3个电压+3个电流

	m_AllGroup = (m_NeedUGroup >= m_NeedIGroup)?m_NeedIGroup:m_NeedUGroup;

	m_pVolChList = &m_pSttTestResource->m_oVolChRsListRef;
	m_pCurChList = &m_pSttTestResource->m_oCurChRsListRef;
}

void SeqWidget::setData(tmt_channel* pVOL,tmt_channel* pCUR)
{
	m_uiVOL = pVOL;
	m_uiCUR = pCUR;

	InitUI();
}

void SeqWidget::InitUI()
{
	ui.m_table->setStyleSheet(QString::fromUtf8("background-color: rgb(167,183,181);"));
	QHeaderView* pTop = ui.m_table->horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	QHeaderView* pLeft = ui.m_table->verticalHeader();
	pLeft->setDefaultSectionSize(50);
	pLeft->setVisible(false);

	ui.m_table->horizontalHeader()->setStretchLastSection(false); 
	ui.m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_headerList<</*tr("序分量")*/g_sLangTxt_sequence<</*tr("幅值(V)")*/(g_sLangTxt_Native_Amplitude+"(V)")<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase;
	ui.m_table->setHorizontalHeaderLabels(m_headerList);
	ui.m_table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(171,167,176);}");
	ui.m_table->horizontalHeader()->setFixedHeight(30);
	int temp = ui.m_table->horizontalHeader()->height();

	ui.m_table->setColumnCount(3);
	ui.m_table->setHorizontalHeaderLabels(m_headerList);
	QFontMetrics fontMetrics = QFontMetrics(font());
	int nLabelWidth1 = fontMetrics.width(/*tr("序分量")*/g_sLangTxt_sequence) + 30;
	int nLabelWidth2 = fontMetrics.width(/*tr("幅值(V)")*/(g_sLangTxt_Native_Amplitude+"(V)")) + 80;
	int nLabelWidth3 = fontMetrics.width(/*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase) + 80;

	ui.m_table->setColumnWidth(0,nLabelWidth1);
	ui.m_table->setColumnWidth(1,nLabelWidth2);
	ui.m_table->setColumnWidth(2,nLabelWidth3);

	int nRowHeight = fontMetrics.height()+5;

	for (int i=0; i< m_nRowNum;i++)
	{
		QTableWidgetItem *item1 = new QTableWidgetItem();
		item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item2 = new QTableWidgetItem();
		item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item3 = new QTableWidgetItem();
		item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

		int rowCount = ui.m_table->rowCount();
		ui.m_table->insertRow(rowCount);
		ui.m_table->setRowHeight(rowCount,30);
		ui.m_table->setItem(rowCount, 0, item1);   	
		ui.m_table->setItem(rowCount, 1, item2);  
		ui.m_table->setItem(rowCount, 2, item3); 

		ui.m_table->setRowHeight(rowCount,nRowHeight);
	}

	//电压/电流序分量名
	ui.m_table->item(0,0)->setText(tr("U0"));
	ui.m_table->item(1,0)->setText(tr("U1"));
	ui.m_table->item(2,0)->setText(tr("U2"));
	ui.m_table->item(3,0)->setText(tr("I0"));
	ui.m_table->item(4,0)->setText(tr("I1"));
	ui.m_table->item(5,0)->setText(tr("I2"));

//	ui.m_ButtonNext->setIcon(QIcon( "./images/Button-Next.png"));
	ui.m_ButtonNext->setStyleSheet("background-color: rgb(255, 255, 255);");

//	ui.m_ButtonPrevious->setIcon(QIcon( "./images/Button-Previous.png"));
	ui.m_ButtonPrevious->setStyleSheet("background-color: rgb(255, 255, 255);");

	ui.m_labelText->setStyleSheet("background-color: rgb(255, 255, 255);");
	ui.m_labelText->setText(QString(/*tr("总组数: %1")*/g_sLangTxt_Native_AllGroup+" %1").arg(1) + "\n" + QString(/*tr("当前组: %1")*/g_sLangTxt_Native_CurGroup+" %1").arg(1));

//	ui.m_labelPromot->setStyleSheet("background-color: rgb(83, 92, 91);");
//	ui.m_labelPromot->setText(QString(tr("←:上一组")) + "\n" + QString(tr("→:下一组")));

	connect(ui.m_ButtonNext, SIGNAL(clicked()), this, SLOT(slot_PbnNextClicked()));
	connect(ui.m_ButtonPrevious, SIGNAL(clicked()), this, SLOT(slot_PbnPreClicked()));
}

void SeqWidget::setDCChanged(bool bDC)
{
	m_bDC = bDC;
	updateData();
}

void SeqWidget::updateData()
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

		//更新电压序分量
		if (m_nCurrentGroup<=m_AllGroup)
		{
			getGroupPosRange(Moudle_U,m_nCurrentGroup,nStart,nEnd);
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

 				if (m_bDC)
 				{
                    if(g_theSttXTestMngrBaseApp->m_bViewTestStarted)
					{
						ui.m_table->item(0,1)->setText(QString("%1").arg( GetZeroSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));
						ui.m_table->item(1,1)->setText(QString("%1").arg( GetPositiveSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));
						ui.m_table->item(2,1)->setText(QString("%1").arg( GetNegativeSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));	
					}
					else
					{
						ui.m_table->item(0,1)->setText(QString("%1").arg( GetZeroSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).amp, 0, 'f', 3));
						ui.m_table->item(1,1)->setText(QString("%1").arg( GetPositiveSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).amp, 0, 'f', 3));
						ui.m_table->item(2,1)->setText(QString("%1").arg( GetNegativeSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).amp, 0, 'f', 3));	
					}

					ui.m_table->item(0,2)->setText("0");
					ui.m_table->item(1,2)->setText("0");
					ui.m_table->item(2,2)->setText("0");
				}
				else
 				{
                    if(g_theSttXTestMngrBaseApp->m_bViewTestStarted)
					{
						ui.m_table->item(0,1)->setText(QString("%1").arg( GetZeroSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));
						ui.m_table->item(1,1)->setText(QString("%1").arg( GetPositiveSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));
						ui.m_table->item(2,1)->setText(QString("%1").arg( GetNegativeSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));	
						ui.m_table->item(0,2)->setText(QString("%1").arg( GetZeroSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).phase, 0, 'f', 3));
						ui.m_table->item(1,2)->setText(QString("%1").arg( GetPositiveSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).phase, 0, 'f', 3));
						ui.m_table->item(2,2)->setText(QString("%1").arg( GetNegativeSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).phase, 0, 'f', 3));
					}
					else
					{
						ui.m_table->item(0,1)->setText(QString("%1").arg( GetZeroSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).amp, 0, 'f', 3));
						ui.m_table->item(1,1)->setText(QString("%1").arg( GetPositiveSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).amp, 0, 'f', 3));
						ui.m_table->item(2,1)->setText(QString("%1").arg( GetNegativeSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).amp, 0, 'f', 3));	
						ui.m_table->item(0,2)->setText(QString("%1").arg( GetZeroSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).phase, 0, 'f', 3));
						ui.m_table->item(1,2)->setText(QString("%1").arg( GetPositiveSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).phase, 0, 'f', 3));
						ui.m_table->item(2,2)->setText(QString("%1").arg( GetNegativeSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).phase, 0, 'f', 3));				
					}
				}
			}
			
			//更新电流序分量
			if(m_nCurrentGroup<=m_AllGroup)
			{
				getGroupPosRange(Moudle_I,m_nCurrentGroup,nStart,nEnd);
				if(nEnd-nStart>= 2)
				{
					pMacroCh_A = (CSttMacroChannel*)m_pCurChList->GetAtIndex(nStart);
					if(pMacroCh_A==NULL){
						return;
					}

					channelPara_A.Harm[1].fAmp = pMacroCh_A->m_oRtDataCh.m_fMag;
					channelPara_A.Harm[1].fAngle = pMacroCh_A->m_oRtDataCh.m_fAng;
					channelPara_A.Harm[1].fFreq = pMacroCh_A->m_oRtDataCh.m_fFreq;

					pMacroCh_B = (CSttMacroChannel*)m_pCurChList->GetAtIndex(nStart+1);
					if(pMacroCh_B==NULL){
						return;
					}

					channelPara_B.Harm[1].fAmp = pMacroCh_B->m_oRtDataCh.m_fMag;
					channelPara_B.Harm[1].fAngle = pMacroCh_B->m_oRtDataCh.m_fAng;
					channelPara_B.Harm[1].fFreq = pMacroCh_B->m_oRtDataCh.m_fFreq;

					pMacroCh_C = (CSttMacroChannel*)m_pCurChList->GetAtIndex(nStart+2);
					if(pMacroCh_C==NULL){
						return;
					}

					channelPara_C.Harm[1].fAmp = pMacroCh_C->m_oRtDataCh.m_fMag;
					channelPara_C.Harm[1].fAngle = pMacroCh_C->m_oRtDataCh.m_fAng;
					channelPara_C.Harm[1].fFreq = pMacroCh_C->m_oRtDataCh.m_fFreq;

					if (m_bDC)
					{
                        if(g_theSttXTestMngrBaseApp->m_bViewTestStarted)
						{
							ui.m_table->item(3,1)->setText(QString("%1").arg( GetZeroSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));
							ui.m_table->item(4,1)->setText(QString("%1").arg( GetPositiveSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));
							ui.m_table->item(5,1)->setText(QString("%1").arg( GetNegativeSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));	
						}
						else
						{
							ui.m_table->item(3,1)->setText(QString("%1").arg( GetZeroSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).amp, 0, 'f', 3));
							ui.m_table->item(4,1)->setText(QString("%1").arg( GetPositiveSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).amp, 0, 'f', 3));
							ui.m_table->item(5,1)->setText(QString("%1").arg( GetNegativeSeqValue( &m_uiVOL[nStart], &m_uiVOL[nStart+1], &m_uiVOL[nStart+2] ).amp, 0, 'f', 3));	
						}

						ui.m_table->item(3,2)->setText("0");
						ui.m_table->item(4,2)->setText("0");
						ui.m_table->item(5,2)->setText("0");
					}
					else
					{
                        if(g_theSttXTestMngrBaseApp->m_bViewTestStarted)
						{
							ui.m_table->item(3,1)->setText(QString("%1").arg( GetZeroSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));
							ui.m_table->item(4,1)->setText(QString("%1").arg( GetPositiveSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));
							ui.m_table->item(5,1)->setText(QString("%1").arg( GetNegativeSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).amp, 0, 'f', 3));
							ui.m_table->item(3,2)->setText(QString("%1").arg( GetZeroSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).phase, 0, 'f', 3));
							ui.m_table->item(4,2)->setText(QString("%1").arg( GetPositiveSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).phase, 0, 'f', 3));
							ui.m_table->item(5,2)->setText(QString("%1").arg( GetNegativeSeqValue( &channelPara_A, &channelPara_B, &channelPara_C ).phase, 0, 'f', 3));
						}
						else
						{
							ui.m_table->item(3,1)->setText(QString("%1").arg( GetZeroSeqValue( &m_uiCUR[nStart], &m_uiCUR[nStart+1], &m_uiCUR[nStart+2] ).amp, 0, 'f', 3));
							ui.m_table->item(4,1)->setText(QString("%1").arg( GetPositiveSeqValue( &m_uiCUR[nStart], &m_uiCUR[nStart+1], &m_uiCUR[nStart+2] ).amp, 0, 'f', 3));
							ui.m_table->item(5,1)->setText(QString("%1").arg( GetNegativeSeqValue( &m_uiCUR[nStart], &m_uiCUR[nStart+1], &m_uiCUR[nStart+2] ).amp, 0, 'f', 3));
							ui.m_table->item(3,2)->setText(QString("%1").arg( GetZeroSeqValue( &m_uiCUR[nStart], &m_uiCUR[nStart+1], &m_uiCUR[nStart+2] ).phase, 0, 'f', 3));
							ui.m_table->item(4,2)->setText(QString("%1").arg( GetPositiveSeqValue( &m_uiCUR[nStart], &m_uiCUR[nStart+1], &m_uiCUR[nStart+2] ).phase, 0, 'f', 3));
							ui.m_table->item(5,2)->setText(QString("%1").arg( GetNegativeSeqValue( &m_uiCUR[nStart], &m_uiCUR[nStart+1], &m_uiCUR[nStart+2] ).phase, 0, 'f', 3));
						}
					}
				}
			}
 		}
	}
}

void SeqWidget::getGroupPosRange(int nModuleType, int nGroup, int& nStart, int& nEnd)
{
	if (nModuleType == Moudle_U)
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
	else
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
}

void SeqWidget::OnRtDataChanged()
{
	updateData();
}

void SeqWidget::UpdateGroupText()
{
	QString str = QString(/*tr("总组数: %1")*/g_sLangTxt_Native_AllGroup+" %1").arg(m_AllGroup)+ "\n" + QString(/*tr("当前组: %1")*/g_sLangTxt_Native_CurGroup+" %1").arg(m_nCurrentGroup);
	ui.m_labelText->setText(str);
}

void SeqWidget::slot_PbnNextClicked()
{
	QString str;

	m_nCurrentGroup++;
	if (m_nCurrentGroup>m_AllGroup)
	{
		m_nCurrentGroup = m_AllGroup;
	}

	updateData();
}

void SeqWidget::slot_PbnPreClicked()
{
	m_nCurrentGroup--;
	if (m_nCurrentGroup<1)
	{
		m_nCurrentGroup = 1;
	}

	updateData();
}

void SeqWidget::languageProcessing()
{
	xlang_SetLangStrToWidget_Txt(ui.m_ButtonPrevious,g_sLangTxt_Natve_LastGroup,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui.m_ButtonNext,g_sLangTxt_Natve_NextGroup,XLang_Ctrls_QPushButton);
}
