#include "InterharmonicsWidget.h"
#include "../SttTestCntrFrameAPI.h"
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
			//20240624 huangliang
			//QTableWidgetItem *item = new QTableWidgetItem;
			QSettingItem *iSettem = new QSettingItem(this);	///创建定值关联控件
			iSettem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

			if(col == 0)
			{
				iSettem->setFlags(iSettem->flags() & ~Qt::ItemIsEditable);
			}

			if (col == 1)
			{
				if(m_MacroType == MACROTYPE_State)
				{
					iSettem->setFlags(Qt::NoItemFlags);
				}
				else if ((m_MacroType == MACROTYPE_Manual)||(m_MacroType == MACROTYPE_ManualHarm)||(m_MacroType == MACROTYPE_ManualSequence)||(m_MacroType == MACROTYPE_ManualLineVol))
				{
					iSettem->setFlags(Qt::NoItemFlags);
				}

				iSettem->setTextColor(QColor(0, 0, 0));
			}
			setItem(row,col,iSettem);
			setRowHeight(row,m_nRowHeight);
		}
	}

	int ntableHight = this->horizontalHeader()->height() + ((m_nRowHeight)*this->rowCount());
	creatTableMenu();

	if (m_pCheckBoxDelegateBase == NULL)
	{
		m_pCheckBoxDelegateBase = new QCheckBoxDelegateBase(this);
		setItemDelegateForColumn(0,m_pCheckBoxDelegateBase);
	}
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
		//20240625 huangliang
		//item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].InterHarm.fAmp,'f',3));
		//item(nChIndex,3)->setText(QString::number(m_pArrUI[nChIndex].InterHarm.fAngle,'f',1));
		//item(nChIndex,4)->setText(QString::number(m_pArrUI[nChIndex].InterHarm.fFreq,'f',3));
		((QSettingItem*)item(nChIndex, 2))->UpdateStructText(CVariantDataAddress(&m_pArrUI[nChIndex].InterHarm.fAmp), 3);
		((QSettingItem*)item(nChIndex, 3))->UpdateStructText(CVariantDataAddress(&m_pArrUI[nChIndex].InterHarm.fAngle), 1);
		((QSettingItem*)item(nChIndex, 4))->UpdateStructText(CVariantDataAddress(&m_pArrUI[nChIndex].InterHarm.fFreq), 3);

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
			float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
			float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
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
}

QInterharmonicsImp::QInterharmonicsImp(QWidget *parent) : QBasicTestParaSetImp(parent)
{

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

	QChannelTable *pVolChTable = NULL,*pCurChTable = NULL;
	pVolChTable = new QInterharmonicsChannelTable(Moudle_U,&m_pParaSetSttTestResource->m_oVolChRsListRef,m_pArrUIVOL,m_pUWidget);
	pCurChTable = new QInterharmonicsChannelTable(Moudle_I,&m_pParaSetSttTestResource->m_oCurChRsListRef,m_pArrUICUR,m_pUWidget);
	pVolChTable->setHarmIndex(NULL/*GetHarmIndex()*/);//间谐波不需要使用HarmIndex
	pCurChTable->setHarmIndex(NULL/*GetHarmIndex()*/);
	pVolChTable->setFont(*g_pSttGlobalFont);
	pVolChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	pCurChTable->setFont(*g_pSttGlobalFont);
	pCurChTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	

	if (pVolChTable)
	{
		pVolChTable->setMacroType(m_MacroType);
		pVolChTable->m_bDC = false;//间谐波始值不是直流
		pVolChTable->initTable();
	}

	if (pCurChTable)
	{
		pCurChTable->setMacroType(m_MacroType);
		pCurChTable->m_bDC = false;//间谐波始值不是直流
		pCurChTable->initTable();
	}

	m_UCHannelTableList.append(pVolChTable);
	m_ICHannelTableList.append(pCurChTable);

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

QInterharmonicsWidget::QInterharmonicsWidget(tmt_harm_paras* pParas, QWidget* pParent) : QBasicTestParaSet(pParent)
{
	m_pParas = NULL;
    setPropertyOfParaSet(P_Common, stt_GetSttTestResource(), pParas->m_uiVOL, pParas->m_uiCUR);
}

QInterharmonicsWidget::~QInterharmonicsWidget()
{

}

void QInterharmonicsWidget::showEvent(QShowEvent *)
{
	if (GetBasicTestParaSetImp() != NULL)
	{
		return;
	}

	SetBasicTestParaSetImp(new QInterharmonicsImp(this));
	setMacroType();
	InitSttInfWidget(GetBasicTestParaSetImp());

	initUI();

	setPropertyOfParaSet();//20230313 zhouhj 改为先初始化界面,再设置最大最小值
	setMaxMinAndEDVal();

	initData();
	DCStateChanged();
}
