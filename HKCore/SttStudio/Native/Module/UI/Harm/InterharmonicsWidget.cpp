#include "InterharmonicsWidget.h"
#include "../SttTestCntrFrameBase.h"
#include <QGridLayout>
#ifdef _USE_SoftKeyBoard_
#include"../SoftKeyboard/SoftKeyBoard.h"
#endif

QInterharmonicsChannelTable::QInterharmonicsChannelTable(MOUDLEType moudleType, CExBaseList *pChList,
														 tmt_channel *pArrUI, QWidget *parent) 
														 : QChannelTable(moudleType, pChList, pArrUI, parent)
{
	m_pCheckBoxDelegateBase = NULL;
}

QInterharmonicsChannelTable::~QInterharmonicsChannelTable()
{

}

void QInterharmonicsChannelTable::initTable()
{
// 	setFocusPolicy(Qt::NoFocus);
// 	setFocus(Qt::NoFocusReason);
	setRowCount(m_pChDatas->GetCount());
	setColumnCount(5);

	QStringList headers;
	CString strSelect, strChannel, strAmplitude, strPhase, strFreq;
	xlang_GetLangStrByFile(strSelect, "Harm_Enable");
	xlang_GetLangStrByFile(strChannel, "Native_Channel");
	xlang_GetLangStrByFile(strAmplitude, "Native_Amplitude");
	xlang_GetLangStrByFile(strPhase, "Native_Angle");
	xlang_GetLangStrByFile(strFreq, "Native_Freq");

#ifndef _PSX_QT_LINUX_
	strPhase += QString::fromLocal8Bit("(°)");
#else
	strPhase += "(°)";
#endif
	strFreq += "(Hz)";

	if (m_moudleType==Moudle_U)//U
	{
		if (m_nParaSetSecondValue == V_Primary)
		{	
			strAmplitude += "(kV)";
		}
		else
		{
		strAmplitude += "(V)";
	}
		
	}
	else
	{
		strAmplitude += "(A)";
	}

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	int nLabelWidth1 = fontMetrics.width(strSelect) + 40;
	int nLabelWidth2 = fontMetrics.width(strChannel) + 40;
	int nLabelWidth3 = fontMetrics.width(tr("-57.735")) + 20;
	int nLabelWidth4 = fontMetrics.width(strPhase) + 10;
	int nLabelWidth5 = fontMetrics.width(strFreq) + 10 ;

	this->setColumnWidth(1,nLabelWidth2);
	this->setColumnWidth(2,nLabelWidth3);
	this->setColumnWidth(3,nLabelWidth4);

	headers << strSelect << strChannel << strAmplitude << strPhase << strFreq;

	setHorizontalHeaderLabels(headers);
	setIconSize(QSize(20,20));

	for (int row=0;row<this->rowCount();row++)
	{
		for (int col=0;col<this->columnCount();col++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

			if(col == 0)
			{
				item->setFlags(item->flags() & ~Qt::ItemIsEditable);
			}

			if (col == 1)
			{
				if(m_MacroType == MACROTYPE_State)
				{
					item->setFlags(Qt::NoItemFlags);
				}
				else if ((m_MacroType == MACROTYPE_Manual)||(m_MacroType == MACROTYPE_ManualHarm)||(m_MacroType == MACROTYPE_ManualSequence)||(m_MacroType == MACROTYPE_ManualLineVol))
				{
					item->setFlags(Qt::NoItemFlags);
				}

				item->setTextColor(QColor(0, 0, 0));
			}
			setItem(row,col,item);
			setRowHeight(row,m_nRowHeight);
		}
	}

	int ntableHight = this->horizontalHeader()->height() + ((m_nRowHeight)*this->rowCount());
	creatTableMenu();

	if (m_pCheckBoxDelegateBase == NULL)
	{
	m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
		setItemDelegateForColumn(0,m_pCheckBoxDelegateBase);
	}
}

void QInterharmonicsChannelTable::SetParaSetSecondValue(int nParaSetSecondValue)
{
	m_nParaSetSecondValue = nParaSetSecondValue;
	QStringList headers;
	CString strSelect, strChannel, strAmplitude, strPhase, strFreq;
	xlang_GetLangStrByFile(strSelect, "Harm_Enable");
	xlang_GetLangStrByFile(strChannel, "Native_Channel");
	xlang_GetLangStrByFile(strAmplitude, "Native_Amplitude");
	xlang_GetLangStrByFile(strPhase, "Native_Angle");
	xlang_GetLangStrByFile(strFreq, "Native_Freq");

#ifndef _PSX_QT_LINUX_
	strPhase += QString::fromLocal8Bit("(°)");
#else
	strPhase += "(°)";
#endif
	strFreq += "(Hz)";

	if (m_moudleType==Moudle_U)//U
	{
		if (m_nParaSetSecondValue == V_Primary)
		{	
			strAmplitude += "(kV)";
		}
		else
		{
			strAmplitude += "(V)";
		}

	}
	else
	{
		strAmplitude += "(A)";
	}


	headers << strSelect << strChannel << strAmplitude << strPhase << strFreq;

	setHorizontalHeaderLabels(headers);
}

void QInterharmonicsChannelTable::UpdateTable()
{
	ASSERT(m_pChDatas);
	POS pos = m_pChDatas->GetHeadPosition();
	CExBaseObject *pCh = NULL;
	long nChIndex = 0;
	QTableWidgetItem *pTableWidgetItem = NULL;
	CString strChName;
	int nSelState = 0;

	while(pos)
	{
		pCh = m_pChDatas->GetNext(pos);
		nSelState = (item(nChIndex,0)->checkState() == Qt::Checked);

		if (nSelState != m_pArrUI[nChIndex].InterHarm.m_bSelect)
		{
			if(m_pArrUI[nChIndex].InterHarm.m_bSelect == false)
			{
				item(nChIndex,0)->setCheckState(Qt::Unchecked);
			}
			else
			{
				item(nChIndex,0)->setCheckState(Qt::Checked);
			}

//			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("(nChIndex=%ld)m_bSelect=%d"),nChIndex,(int)m_pArrUI[nChIndex].InterHarm.m_bSelect);
		}

		pTableWidgetItem = item(nChIndex,1);

		if (pTableWidgetItem == NULL)
		{
			break;
		}
		else
		{
			strChName = pCh->m_strName;
		}

		pTableWidgetItem->setText(strChName);
		float fMaxValue;
		if (g_oSystemParas.m_nHasWeek)//弱信号限制
		{
			if (strChName.Find("U") >= 0 && strChName != _T("U0"))
			{
#ifdef _PSX_OS_CENTOS_
				fMaxValue = 10.000;

#else
				fMaxValue = 4.200;
#endif
			}
			else if (strChName == _T("U0"))
			{
				fMaxValue = 8.300;
			}
			else if (strChName.Find("I") >= 0 && strChName != _T("I0"))
			{
				fMaxValue = 21.000;
			}
			else if (strChName == _T("I0"))
			{
				fMaxValue = 4.200;
			}
		}
		else 
		{
			if (strChName.Find('U') >= 0)
			{
				fMaxValue = g_oLocalSysPara.m_fAC_VolMax;
			}
			else
			{
				fMaxValue = g_oLocalSysPara.m_fAC_VolMax;
			}
		}
		if (m_pArrUI[nChIndex].InterHarm.fAmp > fMaxValue)
		{
			m_pArrUI[nChIndex].InterHarm.fAmp = fMaxValue;
		}


		item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].InterHarm.fAmp,'f',3));
		item(nChIndex,3)->setText(QString::number(m_pArrUI[nChIndex].InterHarm.fAngle,'f',1));
		item(nChIndex,4)->setText(QString::number(m_pArrUI[nChIndex].InterHarm.fFreq,'f',3));

		nChIndex++;
	}

	changeTableColor();
}

void QInterharmonicsChannelTable::Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll, long nCol)
{
	QChannelTable::Act_setUIAmpValue(pItem, fVal, bAll, 2);
}

void QInterharmonicsChannelTable::Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol)
{
	QChannelTable::Act_setPrasePValue(nSwitch, nOffset, fv, 3);
}

void QInterharmonicsChannelTable::Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol)
{
	QChannelTable::Act_setPraseNValue(nSwitch, nOffset, fv, 3);
}

void QInterharmonicsChannelTable::Act_setPraseZValue(int nStart,int nEnd, long nCol)
{
	QChannelTable::Act_setPraseZValue(nStart, nEnd, 3);
}

void QInterharmonicsChannelTable::Act_setHzEqualValue(int nStart,int nEnd,float fv, long nCol)
{
	QChannelTable::Act_setHzEqualValue(nStart, nEnd, fv, 4);
}


void QInterharmonicsChannelTable::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QScrollTableWidget::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QScrollTableWidget::mousePressEvent(event);
//	QScrollTableWidget::mousePressEvent(event);
}


void QInterharmonicsChannelTable::slot_TableShowMent(QPoint pos)
{
	//获得鼠标点击的x，y坐标点 
	int x = pos.x(); 
	int y = pos.y(); 
	QModelIndex index = this->indexAt(QPoint(x,y)); 
	int col = index.column();//获得QTableWidget列表点击的行数 

	switch(col)
	{
	case 2:
		{
			m_MenuAmp->move(cursor().pos()); 
			m_MenuAmp->show(); 
		}
		break;
	case 3:
		{
			int row = index.row();
			ASSERT(m_pChDatas);

			if((m_pChDatas->GetCount() != 4) || (row != 3))
			{
				m_MenuPhase->move(cursor().pos()); 
				m_MenuPhase->show(); 
			}	
		}
		break;
	case 4:
		{
			if ((m_MacroType != MACROTYPE_ManualHarm)&&(m_MacroType != MACROTYPE_ManualSequence)&&(m_MacroType !=MACROTYPE_ManualLineVol))
			{
				m_MenuFre->move(cursor().pos()); 
				m_MenuFre->show(); 
			}
		}
		break;
	default:
		break;
	}
}

void QInterharmonicsChannelTable::slot_OnItemDoubleClicked(QTableWidgetItem *pItem)
{
	//yzj 2022-3-21 判断Enable状态的列的点击响应
	if(!(pItem->flags() & Qt::ItemIsEnabled))
	{
		return;
	}

	int nRow = row(pItem);
	int nCol = column(pItem);
	QString strValue = pItem->text();

	long nEditType = 0;

	if (nCol == 2)
	{
		if(m_moudleType == Moudle_U)
		{
			nEditType = 0;
		}
		else
		{
			nEditType = 1;
		}
	}
	else if (nCol == 3)
	{
		nEditType = 2;
	}
	else if (nCol == 4)
	{
		nEditType = 3;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::Attach330Channel(this, nEditType);
#endif

	m_pCurrKeyboardItem = pItem;
}

void QInterharmonicsChannelTable::slot_OnCellChanged(int row,int col)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);
	QString str = pItem->text();
	QString strInfo;
	float fv;
	QString strText;
	bool bChg = false;
// 	if ((row == 0)&&(col == 0))
// 	{
// 		if (pItem->checkState() != Qt::Unchecked)
// 		{
// 			pItem->setCheckState(Qt::Checked);
// 		} 
// 		else
// 		{
// 			pItem->setCheckState(Qt::Unchecked);
// 		}
// 	}

	switch (col)
	{
	case 0:
		{
			bool bSelect = pItem->checkState() != Qt::Unchecked;
			if(m_pArrUI[row].InterHarm.m_bSelect != bSelect)
			{
				m_pArrUI[row].InterHarm.m_bSelect = bSelect;
				bChg = true;
			}
		}
		break;
	case 2:
		{
			QTableWidgetItem  *pNameWidgetItem  = this->item(row,1);
			CString strChName = pNameWidgetItem->text();

			float fAcVMax = 0,fAcIMax = 0;

			if (g_oSystemParas.m_nHasWeek)//弱信号限制
			{
				if (m_moudleType==Moudle_U)
				{
					if (strChName.Find("U") >= 0 && strChName != _T("U0"))
					{
#ifdef _PSX_OS_CENTOS_
						fAcVMax = 10.000;

#else
						fAcVMax = 4.200;
#endif
				}
				else
				{
						fAcVMax = 8.300;
					}
				}
				else
				{
					if (strChName.Find("I") >= 0 && strChName != _T("I0"))
					{
						fAcIMax = 21.000;
					}
					else
					{
						fAcIMax = 4.200;
					}
				}
			}
			else
			{
				if (m_moudleType==Moudle_U)
				{
					fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
				}
				else
				{
					fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
				}
			}
			fv = str.toFloat();
			if (isPosiDigitstr(str))
			{
			/*	str = initMaxAcV(str);
				fv = str.toFloat();*/
				if (m_moudleType==Moudle_U)
				{
					if (fabs(fv) > fAcVMax)
					{
						fv = fAcVMax;
					}
					else if (fv<m_fAmpMin)
					{
						fv = m_fAmpMin;
					}
				}
				else
				{
					if (fabs(fv) > fAcIMax)
					{	
						fv = fAcIMax;
					}
					else if (fv<m_fAmpMin)
					{
						fv = m_fAmpMin;
					}
				}		
				strText.setNum(fv,'f',3);
				pItem->setText(strText);

				//判断是否有谐波设置，再调用下面的函数判断
				if(HasHarmParaset() && !IsBaseHarmAddValid(row,col,fv))
				{
					if (m_moudleType == Moudle_U)
					{
						if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("基波设置值%f(%d,%d)与谐波的叠加超出范围(%fV)."),fv,row,col,g_oLocalSysPara.m_fAC_VolMax);
						}
						else
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("The Superposition of fundamental wave value %f(%d,%d)and Harmonic settin value(%fV)is out of range."),fv,row,col,g_oLocalSysPara.m_fAC_VolMax);
						}
					}
					else
					{
						if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("基波设置值%f(%d,%d)与谐波的叠加超出范围(%fA)."),fv,row,col,g_oLocalSysPara.m_fAC_CurMax);
						}
						else
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("The Superposition of fundamental wave value %f(%d,%d)and Harmonic settin value(%fA)is out of range."),fv,row,col,g_oLocalSysPara.m_fAC_CurMax);
						}
					}

					fv = m_pArrUI[row].InterHarm.fAmp;
				}

				pItem->setText(QString::number(fv,'f',3));
			}
			else
			{
				if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
				{
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("输入值含有非法字符."));
				}
				else
				{
					CLogPrint::LogString(XLOGLEVEL_ERROR,_T("The input value contains illegal characters."));
				}

				fv = m_pArrUI[row].InterHarm.fAmp;

				if (fv > m_fAmpMax)
				{
					fv = m_fAmpMax;
				}

				if (fv < m_fAmpMin)
				{
					fv = m_fAmpMin;
				}

				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}

			if(m_pArrUI[row].InterHarm.fAmp != fv)
			{
				m_pArrUI[row].InterHarm.fAmp = fv;
				m_pArrUI[row].InterHarm.fContent = fv * 100 / m_pArrUI[row].Harm[1].fAmp;
				bChg = true;
			}
		}
		break;
	case 3:
		{
			fv = str.toFloat();
			if (fv<=9999 && fv>=-9999)
			{
			float f1 = fv - (int)fv;
			int f2 = ((int)fv)%360;
			fv = f1+f2;
			}
			else
			{
				fv=0;
			}		
			int temp = (int)(fv*10)%10;
			if (temp == 9 ||temp == -9)
			{
				fv = (int)fv+temp*0.1;
			}

			strText.setNum(fv,'f',1);
			pItem->setText(strText);

			if(m_pArrUI[row].InterHarm.fAngle != fv)
			{
				m_pArrUI[row].InterHarm.fAngle = fv;
				bChg = true;
			}
		}
		break;
	case 4:
		{
			if (isPosiDigitstr(str))
			{
				str = initMaxHz(str);
				fv = str.toFloat();

				if ((m_bDC)&&(m_MacroType != MACROTYPE_ManualHarm)&&(m_MacroType != MACROTYPE_ManualSequence)&&(m_MacroType != MACROTYPE_ManualLineVol))
				{
					fv = 0;
				}
				else
				{
					if (fv < 0.001)
					{
						fv = 0;
					}
				}

				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
			else
			{
				fv = m_pArrUI[row].InterHarm.fFreq;
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}

			if(m_pArrUI[row].InterHarm.fFreq != fv)
			{
				m_pArrUI[row].InterHarm.fFreq = fv;
				bChg = true;
			}
		}
		break;
	default:
		break;
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

	if (m_pCurrKeyboardItem != NULL /*&& m_MacroType != MACROTYPE_State*/)//20230112 zhouhj  状态序列也更新参数，只更新矢量图
	{
		long nRow = m_pCurrKeyboardItem->row();
		long nCol = m_pCurrKeyboardItem->column();
		emit sig_ChannelValueChanged(m_moudleType,nRow,nCol, m_pCurrKeyboardItem->text().toFloat());//valueFlag=（1:幅值 2:相位 3:频率）
	}
	emit sig_updataInterharmonicsChannelParas();
}

QInterharmonicsImp::QInterharmonicsImp(QWidget *parent) : QBasicTestParaSetImp(parent)
{
		m_pVolChTable = NULL;
		m_pCurChTable = NULL;
}

QInterharmonicsImp::~QInterharmonicsImp()
{

}

void QInterharmonicsImp::initUI(CSttTestResourceBase *pSttTestResource)
{
	QParaSetBase::initUI(pSttTestResource);

	if (m_pParaSetSttTestResource == NULL)
	{
		return;
	};

	m_pVolChTable = new QInterharmonicsChannelTable(Moudle_U,&m_pParaSetSttTestResource->m_oVolChRsListRef,m_pArrUIVOL,m_pUWidget);
	m_pCurChTable = new QInterharmonicsChannelTable(Moudle_I,&m_pParaSetSttTestResource->m_oCurChRsListRef,m_pArrUICUR,m_pUWidget);
	m_pVolChTable->setHarmIndex(NULL/*GetHarmIndex()*/);//间谐波不需要使用HarmIndex
	m_pCurChTable->setHarmIndex(NULL/*GetHarmIndex()*/);
	m_pVolChTable->setFont(*g_pSttGlobalFont);
	m_pVolChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pCurChTable->setFont(*g_pSttGlobalFont);
	m_pCurChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	

	if (m_pVolChTable)
	{
		m_pVolChTable->setMacroType(m_MacroType);
		m_pVolChTable->m_bDC = false;//间谐波始值不是直流
		m_pVolChTable->m_nParaSetSecondValue = m_nParaSetSecondValue;
		m_pVolChTable->initTable();
	}

	if (m_pCurChTable)
	{
		m_pCurChTable->setMacroType(m_MacroType);
		m_pCurChTable->m_bDC = false;//间谐波始值不是直流
		m_pCurChTable->initTable();
	}

	m_UCHannelTableList.append(m_pVolChTable);
	m_ICHannelTableList.append(m_pCurChTable);

	for (int i = 0; i<m_UCHannelTableList.size();i++)
	{
		connect(m_UCHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
	}
	for (int i = 0; i<m_ICHannelTableList.size();i++)
	{
		connect(m_ICHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
	}

	int nUWidgetHeight = 0;	
	int nUWidgetWidth = 0;
	for (int i = 0; i < m_UCHannelTableList.size(); i++)
	{
		nUWidgetWidth = m_UCHannelTableList[i]->getTableWidth();
		nUWidgetHeight += m_UCHannelTableList[i]->getTableHeight();
		m_pUVGridLayout->addWidget(m_UCHannelTableList.at(i),i,0,1,1);
	}

	m_pUWidget->setMinimumHeight(nUWidgetHeight);
	m_pUVGridLayout->setMargin(0);
	m_pUVGridLayout->setSpacing(0);
	m_pUWidget->setLayout(m_pUVGridLayout);

	int nIWidgetHeight = 0;
	int nIWidgetWidth = 0;
	for (int i = 0; i < m_ICHannelTableList.size(); i++)
	{
		nIWidgetWidth = m_ICHannelTableList[i]->getTableWidth();
		nIWidgetHeight += m_ICHannelTableList[i]->getTableHeight();
		m_pIVGridLayout->addWidget(m_ICHannelTableList.at(i),i,0,1,1);
	}

	m_pIWidget->setMinimumHeight(nIWidgetHeight);
	m_pIVGridLayout->setMargin(0);
	m_pIVGridLayout->setSpacing(0);
	m_pIWidget->setLayout(m_pIVGridLayout);

	m_pUScrollArea->setWidgetResizable(true);
	m_pUScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pUScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	if(m_UCHannelTableList.size() > 1)
	{
		m_pUVGridLayout->setRowStretch(m_UCHannelTableList.size(),1);
		m_pUScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);	
	}

	m_pIScrollArea->setWidgetResizable(true);
	m_pIScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pIScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	if(m_ICHannelTableList.size() > 1)
	{
		m_pIVGridLayout->setRowStretch(m_ICHannelTableList.size(),1);
		m_pIScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	}

	m_pMainGridLayout->addWidget(m_pUScrollArea,0,0);
	m_pMainGridLayout->addWidget(m_pIScrollArea,0,1);
}

void QInterharmonicsImp::SetParaSetSecondValue(int nParaSetSecondValue)
{
	m_nParaSetSecondValue = nParaSetSecondValue;

	if (m_UCHannelTableList.size() > 0)
	{
		QInterharmonicsChannelTable *pInterharmonicsChannelTable = NULL;

		for (int i = 0; i<m_UCHannelTableList.size();i++)
		{
			pInterharmonicsChannelTable = (QInterharmonicsChannelTable *)m_UCHannelTableList.at(i);	
			pInterharmonicsChannelTable->SetParaSetSecondValue(m_nParaSetSecondValue);

		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QInterharmonicsWidget::QInterharmonicsWidget(tmt_harm_paras* pParas, QWidget* pParent) : QBasicTestParaSet(pParent)
{
	m_pInterharmonicsImp = NULL;

	m_pParas = pParas;
	setPropertyOfParaSet(P_Common, g_theTestCntrFrame->GetSttTestResource(), m_pParas->m_uiVOL, m_pParas->m_uiCUR);
}

QInterharmonicsWidget::~QInterharmonicsWidget()
{

}

void QInterharmonicsWidget::SetParaSetSecondValue(int nParaSetSecondValue)
{
	m_nParaSetSecondValue = nParaSetSecondValue;
	if (m_pInterharmonicsImp != NULL)
	{
		m_pInterharmonicsImp->SetParaSetSecondValue(m_nParaSetSecondValue);
	}
}

void QInterharmonicsWidget::showEvent(QShowEvent *)
{
	if (GetBasicTestParaSetImp() != NULL)
	{
		return;
	}
	m_pInterharmonicsImp = new QInterharmonicsImp(this);
	SetBasicTestParaSetImp(m_pInterharmonicsImp);
	setMacroType();
	InitSttInfWidget(GetBasicTestParaSetImp());

	initUI();

	setPropertyOfParaSet();//20230313 zhouhj 改为先初始化界面,再设置最大最小值
	setMaxMinAndEDVal();

	m_pInterharmonicsImp->SetParaSetSecondValue(m_nParaSetSecondValue);
	initData(true);
	DCStateChanged();

	if (m_pInterharmonicsImp->m_pCurChTable)
	{
		//20250120 suyang 增加更新测试过程中修改参数不更新参数下发
		connect(m_pInterharmonicsImp->m_pCurChTable,SIGNAL(sig_updataInterharmonicsChannelParas()), this, SLOT(slot_updataParas()),Qt::UniqueConnection);
	}

	if (m_pInterharmonicsImp->m_pVolChTable)
	{
		//20250120 suyang 增加更新测试过程中修改参数不更新参数下发
		 connect(m_pInterharmonicsImp->m_pVolChTable,SIGNAL(sig_updataInterharmonicsChannelParas()), this, SLOT(slot_updataParas()),Qt::UniqueConnection);
	}
}

void QInterharmonicsWidget::slot_updataParas()
{
	emit sig_updataParas();
}

void QInterharmonicsWidget::UpdataTableData()
{
	setPropertyOfParaSet(P_Common, g_theTestCntrFrame->GetSttTestResource(), m_pParas->m_uiVOL, m_pParas->m_uiCUR);
	if (m_pInterharmonicsImp)
	{
		m_pInterharmonicsImp->m_pCurChTable->UpdateTable();
		m_pInterharmonicsImp->m_pVolChTable->UpdateTable();
	}
	

}
