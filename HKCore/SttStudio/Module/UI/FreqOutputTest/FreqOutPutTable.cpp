#include "FreqOutPutTable.h"
#include "../SttTestCntrFrameBase.h"

#ifdef _USE_SoftKeyBoard_
#include"../SoftKeyboard/SoftKeyBoard.h"
#endif

QFreqOutPutTable::QFreqOutPutTable(MOUDLEType moudleType, CExBaseList *pChList,
														 tmt_FreqOutputChannel *pArrUI, QWidget *parent) 
: QChannelTable(moudleType, pChList, pArrUI, parent)
{
	m_pCheckBoxDelegateBase = NULL;
	m_pArrUI = pArrUI;
}

QFreqOutPutTable::~QFreqOutPutTable()
{

}

void QFreqOutPutTable::initTable()
{
	setRowCount(m_pChDatas->GetCount());
	setColumnCount(4);

	QStringList headers;
	CString strSelect, strChannel, strAmplitude, strPhase;
	xlang_GetLangStrByFile(strSelect, "sSelect");
	xlang_GetLangStrByFile(strChannel, "Native_Channel");
	xlang_GetLangStrByFile(strAmplitude, "Native_Amplitude");
	xlang_GetLangStrByFile(strPhase, "Native_Angle");

#ifndef _PSX_QT_LINUX_
	strPhase += QString::fromLocal8Bit("(°)");
#else
	strPhase += "(°)";
#endif


	if (m_moudleType == Moudle_U)//U
	{
		strAmplitude += "(V)";
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

	this->setColumnWidth(1,nLabelWidth2);
	this->setColumnWidth(2,nLabelWidth3);
	this->setColumnWidth(3,nLabelWidth4);

	headers << strSelect << strChannel << strAmplitude << strPhase ;

	setHorizontalHeaderLabels(headers);
	setIconSize(QSize(20,20));

	for (int row = 0;row < this->rowCount();row++)
	{
		for (int col = 0;col < this-> columnCount();col++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

			if(col == 0)
			{
				item->setFlags(item->flags() & ~Qt::ItemIsEditable);
			}

			if (col == 1)
			{
				item->setFlags(Qt::NoItemFlags);

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


void QFreqOutPutTable::UpdateTable()
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

		if (nSelState != m_pArrUI[nChIndex].m_nSelect)
		{
			if(m_pArrUI[nChIndex].m_nSelect == false)
			{
				item(nChIndex,0)->setCheckState(Qt::Unchecked);
			}
			else
			{
				item(nChIndex,0)->setCheckState(Qt::Checked);
			}
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
		
		if (strChName.Find('U') >= 0)
		{
			fMaxValue = g_oLocalSysPara.m_fAC_VolMax;
		}
		else
		{
			fMaxValue = g_oLocalSysPara.m_fAC_CurMax;
		}
		if (m_pArrUI[nChIndex].m_fAmp > fMaxValue)
		{
			m_pArrUI[nChIndex].m_fAmp = fMaxValue;
		}


		item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].m_fAmp,'f',3));
		item(nChIndex,3)->setText(QString::number(m_pArrUI[nChIndex].m_fAngle,'f',1));

		nChIndex++;
	}

	changeTableColor();
}

void QFreqOutPutTable::Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll, long nCol)
{
	QChannelTable::Act_setUIAmpValue(pItem, fVal, bAll, 2);
}

void QFreqOutPutTable::Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol)
{
	QChannelTable::Act_setPrasePValue(nSwitch, nOffset, fv, 3);
}

void QFreqOutPutTable::Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol)
{
	QChannelTable::Act_setPraseNValue(nSwitch, nOffset, fv, 3);
}

void QFreqOutPutTable::Act_setPraseZValue(int nStart,int nEnd, long nCol)
{
	QChannelTable::Act_setPraseZValue(nStart, nEnd, 3);
}

void QFreqOutPutTable::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QScrollTableWidget::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QScrollTableWidget::mousePressEvent(event);
}


void QFreqOutPutTable::slot_OnCellChanged( int row,int col )
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);
	QString str = pItem->text();
	QString strInfo;
	float fv;
	QString strText;
	bool bChg = false;

	switch (col)
	{
	case 0:
		{
			bool bSelect = pItem->checkState() != Qt::Unchecked;
			if(m_pArrUI[row].m_nSelect != bSelect)
			{
				m_pArrUI[row].m_nSelect = bSelect;
				bChg = true;
			}
		}
		break;
	case 2:
		{
			QTableWidgetItem  *pNameWidgetItem  = this->item(row,1);
			CString strChName = pNameWidgetItem->text();

			float fAcVMax = 0,fAcIMax = 0;

			if (m_moudleType == Moudle_U)
			{
				fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
			}
			else
			{
				fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
			}

			fv = str.toFloat();
			if (isPosiDigitstr(str))
			{
		
				if (m_moudleType == Moudle_U)
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
					else if (fv <m_fAmpMin)
					{
						fv = m_fAmpMin;
					}
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

				fv = m_pArrUI[row].m_fAmp;

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

			if(m_pArrUI[row].m_fAmp != fv)
			{
				m_pArrUI[row].m_fAmp = fv;
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

			if(m_pArrUI[row].m_fAngle != 0)
			{
				m_pArrUI[row].m_fAngle = 0;
				bChg = true;
			}
		}
		break;
	default:
		break;
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

	if (m_pCurrKeyboardItem != NULL)
	{
		long nRow = m_pCurrKeyboardItem->row();
		long nCol = m_pCurrKeyboardItem->column();
		emit sig_ChannelValueChanged(m_moudleType,nRow,nCol, m_pCurrKeyboardItem->text().toFloat());//valueFlag=（1:幅值 2:相位 3:频率）
	}
}

void QFreqOutPutTable::slot_TableShowMent(QPoint pos)
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

void QFreqOutPutTable::slot_OnItemDoubleClicked(QTableWidgetItem *pItem)
{
	if(!(pItem->flags() & Qt::ItemIsEnabled))
	{
		return;
	}

	int nRow = row(pItem);
	int nCol = column(pItem);

	CString strValue = pItem->text();

	long nEditType;
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

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::Attach330Channel(this, nEditType);
#endif

	m_pCurrKeyboardItem = pItem;

}

QFreqOutPutWidget::QFreqOutPutWidget(QWidget *parent)
	 : QParaSetBase(parent)
{
	m_pArrUICUR = NULL;
	m_pParaSetSttTestResource = NULL;
	m_MacroType = -1;
	m_bDC = true;
	InitUI();
}

QFreqOutPutWidget::~QFreqOutPutWidget()
{
	Release();
	delete m_pUGridLayout;
	delete m_pIGridLayout;
	delete m_pUWidget;
	delete m_pIWidget;
	delete m_pUScrollArea;
	delete m_pIScrollArea;
}

void QFreqOutPutWidget::Release()
{
	for (int i = 0; i< m_UCHannelTableList.size(); i++)
	{
		QChannelTable *p = m_UCHannelTableList.at(i);
		delete p;
		p = NULL;
	}
	m_UCHannelTableList.clear();

	for (int i = 0; i< m_ICHannelTableList.size(); i++)
	{
		QChannelTable *p = m_ICHannelTableList.at(i);
		delete p;
		p = NULL;
	}
	m_ICHannelTableList.clear();
}
void QFreqOutPutWidget::InitUI()
{
	m_pIScrollArea = new QScrollArea(this);
	m_pIWidget = new QWidget(m_pIScrollArea);
	m_pIScrollArea->setWidget(m_pIWidget);
	m_pIGridLayout = new QGridLayout(m_pIWidget);
	m_pIGridLayout->setMargin(0);
	m_pIWidget->setLayout(m_pIGridLayout);
	m_pIScrollArea->setWidgetResizable(true);


	m_pUScrollArea = new QScrollArea(this);
	m_pUWidget = new QWidget(m_pUScrollArea);
	m_pUScrollArea->setWidget(m_pUWidget);
	m_pUGridLayout = new QGridLayout(m_pUWidget);
	m_pUGridLayout->setMargin(0);
	m_pUWidget->setLayout(m_pUGridLayout);
	m_pUScrollArea->setWidgetResizable(true);

	CString strText;
	m_pUIGroupBox = new QGroupBox;
	strText = _T("电压电流");
	m_pUIGroupBox->setTitle(strText);
	m_pUIGroupBox->setFont(*g_pSttGlobalFont);
	QHBoxLayout *pGroupBoxLayout = new QHBoxLayout;
	pGroupBoxLayout->addWidget(m_pUScrollArea);
	pGroupBoxLayout->addWidget(m_pIScrollArea);
	m_pUIGroupBox->setLayout(pGroupBoxLayout);
	QHBoxLayout *pMainHBoxLayout = new QHBoxLayout(this);
	pMainHBoxLayout->addWidget(m_pUIGroupBox);
	this->setLayout(pMainHBoxLayout);  
}

void QFreqOutPutWidget::initUI(CSttTestResourceBase *pSttTestResource)
{
	Release();

	if (pSttTestResource != NULL)
	{
		m_pParaSetSttTestResource = pSttTestResource;
	}

	if (m_pParaSetSttTestResource == NULL)
	{
		return;
	}

	

	QFreqOutPutTable *pCurChTable = NULL;
	pCurChTable = new QFreqOutPutTable(Moudle_I,&m_pParaSetSttTestResource->m_oCurChRsListRef,m_pArrUICUR,m_pIWidget);
	pCurChTable->setFont(*g_pSttGlobalFont);
	pCurChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);

	if (pCurChTable)
	{
		pCurChTable->setMacroType(m_MacroType);
		pCurChTable->m_bDC = m_bDC;
		pCurChTable->initTable();
	}
	m_ICHannelTableList.append(pCurChTable);

	QFreqOutPutTable *pVolChTable = NULL;
	pVolChTable = new QFreqOutPutTable(Moudle_U,&m_pParaSetSttTestResource->m_oVolChRsListRef,m_pArrUIVOL,m_pUWidget);
	pVolChTable->setFont(*g_pSttGlobalFont);
	pVolChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);

	if (pVolChTable)
	{
		pVolChTable->setMacroType(m_MacroType);
		pVolChTable->m_bDC = m_bDC;
		pVolChTable->initTable();
	}
	m_UCHannelTableList.append(pVolChTable);

	int nIWidgetHeight = 0;
	int nIWidgetWidth = 0;
	for (int i = 0; i<m_ICHannelTableList.size();i++)
	{
		nIWidgetWidth = m_ICHannelTableList[i]->getTableWidth();
		nIWidgetHeight += m_ICHannelTableList[i]->getTableHeight();
		m_pIGridLayout->addWidget(m_ICHannelTableList.at(i),i,0,1,1);
		connect(m_ICHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
	}
	
	m_pIWidget->setMinimumHeight(nIWidgetHeight);	


	int nUWidgetHeight = 0;	
	int nUWidgetWidth = 0;
	for (int i = 0; i < m_UCHannelTableList.size(); i++)
	{
		nUWidgetWidth = m_UCHannelTableList[i]->getTableWidth();
		nUWidgetHeight += m_UCHannelTableList[i]->getTableHeight();
		m_pUGridLayout->addWidget(m_UCHannelTableList.at(i),i,0,1,1);
		connect(m_UCHannelTableList[i],SIGNAL(sig_ChannelValueChanged(MOUDLEType,int,int,float)),this,SLOT(slot_ChannelValueChanged(MOUDLEType,/*int,*/int,int,float)));
	}
	m_pUWidget->setMinimumHeight(nUWidgetHeight);	

}

void QFreqOutPutWidget::initData()
{
	if ((m_pParaSetSttTestResource == NULL)||(m_pArrUICUR == NULL))
	{
		return;
	}

	if (m_ICHannelTableList.size()>=1)
	{
		m_ICHannelTableList[0]->setTableData(m_pArrUICUR,true);
	}

	if (m_UCHannelTableList.size()>=1)
	{
		m_UCHannelTableList[0]->setTableData(m_pArrUIVOL, true);
	}
}

void QFreqOutPutWidget::UpdateValidTableDatas()
{
	int nIndex = 0;
	QChannelTable *pCurrChTable = NULL;

	for (nIndex = 0; nIndex< m_UCHannelTableList.size(); nIndex++)
	{
		pCurrChTable = m_UCHannelTableList.at(nIndex);
		pCurrChTable->UpdateValidTableDatas();
	}
	for (nIndex = 0; nIndex< m_ICHannelTableList.size(); nIndex++)
	{
		pCurrChTable = m_ICHannelTableList.at(nIndex);
		pCurrChTable->UpdateValidTableDatas();
	}
}

void QFreqOutPutWidget::setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
											,tmt_FreqOutputChannel *pArrUIVOL,tmt_FreqOutputChannel *pArrUICUR,bool bDC)
{
	ASSERT(pSttTestResource);
	ASSERT( pArrUICUR != NULL);

	m_type = type;
	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;

	m_pParaSetSttTestResource = pSttTestResource;
	m_bDC = bDC;

	initUI(pSttTestResource);
	initData();
}

void QFreqOutPutWidget::setData(tmt_FreqOutputChannel *pArrUIVOL,tmt_FreqOutputChannel *pArrUICUR)
{
	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;

}

void QFreqOutPutWidget::setMaxMinAndEDVal(bool bCanUpdateTable)
{
	setUAmpMaxMinValue(bCanUpdateTable);
	setIAmpMaxMinValue(bCanUpdateTable);

	setUAmpEDValue(g_oSystemParas.m_fVNom);
	setIAmpEDValue(g_oSystemParas.m_fINom);
}


void QFreqOutPutWidget::setIAmpMaxMinValue(bool bCanUpdateTable)
{
	int num = 0;
	num = m_ICHannelTableList.size();
	for (int i =0; i<num; i++)
	{
		m_ICHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_CurMax,0,bCanUpdateTable);
	}
}

void QFreqOutPutWidget::setUAmpMaxMinValue(bool bCanUpdateTable)
{
	int num = 0;
	num = m_UCHannelTableList.size();
	for (int i=0; i<num; i++)
	{
		m_UCHannelTableList[i]->setAmpMaxMinValue(g_oLocalSysPara.m_fAC_VolMax,0, bCanUpdateTable);
	}
}

void QFreqOutPutWidget::setIAmpEDValue(float fIEDVal)
{
	int num = 0;
	num = m_ICHannelTableList.size();

	for (int i =0; i<num; i++)
	{
		m_ICHannelTableList[i]->setAmpEDValue(fIEDVal);
	}
}

void QFreqOutPutWidget::setUAmpEDValue(float fUEDVal)
{
	int num = 0;
	num = m_UCHannelTableList.size();

	for (int i =0; i<num; i++)
	{
		m_UCHannelTableList[i]->setAmpEDValue(fUEDVal);
	}
}

void QFreqOutPutWidget::startInit(bool bEnable)
{
	setDisabled(!bEnable);
}

void QFreqOutPutWidget::stopInit(bool bEnable)
{
	setDisabled(!bEnable);
}



void QFreqOutPutWidget::UpdateTables()
{
	int i = 0;
	for (i = 0; i< m_UCHannelTableList.size(); i++)
	{
		QChannelTable *p = m_UCHannelTableList.at(i);
		p->UpdateTable();
	}

	for (i = 0; i< m_ICHannelTableList.size(); i++)
	{
		QChannelTable *p = m_ICHannelTableList.at(i);
		p->UpdateTable();
	}
}


// void QFreqOutPutWidget::slot_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float datavalue)
// {
// 	initData();
// 	emit sig_updataParas(channelNum,valueFlag,datavalue);
// }

