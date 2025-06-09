#include "channeltable.h"
#include <QFontMetrics>
#include <QScrollBar>
#include <cmath>
#include "../../../../Module/SttSystemConfig/SttSystemConfig.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"


#define GenHao3	1.7320508 //根号三

CHannelTable::CHannelTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent)
	: QTableWidget(parent)
{
	m_bUsekeyPressEventExec = false;
	m_bSendUpdateParas = true;
	m_pChDatas = pChList;
//	m_nNameNum = 0;
	m_dispmode = 0;
	m_tableIndex = 0;
	m_MacroType = 0;
	m_moudleType = moudleType;
//	m_moudleID = 0;
//	m_moudleChannelNum = pChList->GetCount();
	m_pArrUI = pArrUI;
	m_bDCTest = false;
	m_ColorList<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181)<<QColor(168,169,171)<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181);

	m_ColumnNum = 4;
	m_fAmpMax = 120;
	m_fAmpMin = 0;
	m_fEDVal = 0;
	m_dispmode = V_Secondary;
	
	m_pActUAmpED2 = NULL; 
	m_pActUAmpED5 = NULL;
	m_pActUAmpED20 = NULL;
	m_pActUAmpED120 = NULL;
	m_pActUAmpED190 = NULL;
	m_pActIAmpED1 = NULL;
	m_pActIAmpED5 = NULL;
	m_pActIAmpED20 = NULL;
	m_pActIAmpED100 = NULL;
	m_pActIAmpED120 = NULL;

	CSttDevConfig *pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	if (pSttDevConfig->m_nDoubleClickEdit == 0)
	{
		setEditTriggers(QAbstractItemView::AllEditTriggers);
	}

	init();
}

CHannelTable::~CHannelTable()
{

}

void CHannelTable::setHeaderOfTable(QStringList strheader)
{
	QString str = strheader.at(1);
	if (str.contains(tr("A")))
	{
		m_ActIAmp1->setText(tr("1A"));
		m_ActIAmp5->setText(tr("5A"));
	}
	
	if (str.contains(tr("V")))
	{
		if (str.contains(tr("KV")))
		{
			m_dispmode = V_Primary;
		}
		else
		{
			m_dispmode = V_Secondary;
		}
	}

	setHorizontalHeaderLabels(strheader);
}

void CHannelTable::setTableData(tmt_channel *pArrUI)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	m_pArrUI = pArrUI;
	UpdateTable();

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void CHannelTable::setProperty(bool bDCTest)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	bool bTempDc = m_bDCTest;
	m_bDCTest = bDCTest;
	FloatTempChData *pData = NULL;

	if (m_bDCTest)
	{
		setColumnHidden(2, true);
		setColumnHidden(3, true);

		for (int i=0;i<rowCount();i++)
		{
			item(i,2)->setFlags(Qt::NoItemFlags);
			item(i,2)->setBackground(Qt::gray);
//			item(i,2)->setText(QString::number(0,'f',1));
//			m_pArrUI[i].Harm[1].fAngle = 0;				//相位=0

			if (m_ColumnNum >3)
			{
				item(i,3)->setFlags(Qt::NoItemFlags);
				item(i,3)->setBackground(Qt::gray);
//				item(i,3)->setText(QString::number(0,'f',3));
//				m_pArrUI[i].Harm[1].fFreq = 0;			//频率=0
			}

			m_pArrUI[i].Harm[1].bDC = 1;
		}
	}
	else
	{
		setColumnHidden(2, false);
		setColumnHidden(3, false);

		for (int i=0;i<rowCount();i++)
		{		
			if(bDCTest != bTempDc)
		{
				pData = m_oTempSaveDataMap.value(i);
				m_pArrUI[i].Harm[1].fAngle = pData->fAngle;
				m_pArrUI[i].Harm[1].fFreq = pData->fHz;
			}

			item(i,2)->setFlags(item(i,1)->flags());
			item(i,2)->setBackground(item(i,1)->background());
			if (m_ColumnNum > 3)
			{
				item(i,3)->setFlags(item(i,1)->flags());
				item(i,3)->setBackground(item(i,1)->background());
				item(i,3)->setText(QString::number(m_pArrUI[i].Harm[1].fFreq,'f',3));
			}

			item(i,2)->setText(QString::number(m_pArrUI[i].Harm[1].fAngle,'f',2));//zhouhj相位精度改为2位  20220901

			m_pArrUI[i].Harm[1].bDC = 0;


		}
	}
	
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void CHannelTable::setItemValue(int row,int col,float fv)
{
	if (row<rowCount()&&col<columnCount())
	{
		if (col>0&&col<columnCount())
		{
			QString strTmp;

			if (col==2)
			{
				strTmp = QString::number(fv,'f',2);
				item(row,col)->setText(strTmp);//zhouhj相位精度改为2位  20220901
			}
			else
			{
				strTmp = QString::number(fv,'f',3);
				item(row,col)->setText(strTmp);
			}
		}
	}
}

float CHannelTable::getItemValue(int row,int col)
{
	float fv;
	if (row<rowCount()&&col<columnCount())
	{
		if (col>0&&col<columnCount())
		{
			fv = item(row,col)->text().toFloat(); 
		}
	}
	return fv;
}

void CHannelTable::setAmpMaxMinValue(float fmax,float fmin)
{
	m_fAmpMax = fmax;
	m_fAmpMin = fmin;
}

void CHannelTable::setAmpEDValue(float fEDValue)
{
	m_fEDVal = fEDValue;
}


void CHannelTable::setColumnNum(int num)
{
	m_ColumnNum = num;
	initTable();
}

void CHannelTable::setColumnWidthByNum(int col,int width)
{
	setColumnWidth(col,width);
}

void CHannelTable::setTableFixWidgt(int width)
{
	this->setFixedWidth(width);
}

int CHannelTable::getTableHeight()
{
	return this->height();
}

int CHannelTable::getTableWidth()
{
	int nwidth = 0;
	int nrowheight = 0;
	for (int col = 0; col < this->columnCount(); col++)
	{
		nrowheight = this->columnWidth(col);
		nwidth += nrowheight;
	}

	return nwidth;
}

void CHannelTable::init()
{
	setFocusPolicy(Qt::NoFocus);
	setContextMenuPolicy (Qt::CustomContextMenu);

	QHeaderView* pLeft = this->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setClickable(false);
	pLeft->setVisible(false);

	QFont font1 = this->horizontalHeader()->font();
	font1.setBold(true);
	
	this->horizontalHeader()->setFont(font1);
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
	QFontMetrics fontHeaderViewMe = QFontMetrics(font1);
	m_nHeaderViewHeight = fontHeaderViewMe.height() + 20;
	QFont font2 = this->font();
	font2.setPointSize(9);
	this->setFont(font2);
	QFontMetrics fontRowMe = QFontMetrics(font2);
	m_nRowHeight = fontRowMe.height() + 15;
	
	this->horizontalScrollBar()->setEnabled(true);
	this->verticalScrollBar()->setEnabled(false);

	QDesktopWidget *pDeskTop = QApplication::desktop();
	QRect rcScreen = pDeskTop->screenGeometry();
// 	if(rcScreen.width()<=1024 || rcScreen.height()<=768) //20220511 在1024*768时,4通道时显示不出来故注释掉
// 	{
// 		this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//         this->horizontalHeader()->setStretchLastSection(true);
// 	}
// 	else
	{
		this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        this->horizontalHeader()->setResizeMode(QHeaderView::Stretch); 
	}

	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void CHannelTable::initTable()
{
	setColumnCount(m_ColumnNum);
	ASSERT(m_pChDatas);
	if ((m_MacroType == MACROTYPE_Sequence))// dingxiaoya 20231102 序分量表格行数更新
	{
		long nGroupNum = m_pChDatas->GetCount() / 3;
		setRowCount(nGroupNum * 3);
	}
	else
	{
	setRowCount(m_pChDatas->GetCount());
	}

	QStringList headers;
	if (m_moudleType==Moudle_U)//U
	{
		if (m_ColumnNum == 3)
		{
			headers<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(V)")*/g_sLangTxt_Native_amplitudeV<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase;
		}
		else
		{
			headers<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(V)")*/g_sLangTxt_Native_amplitudeV<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase<</*tr("频率(Hz)")*/g_sLangTxt_Native_FreqHz;
		}
	}
	else
	{
		if (m_ColumnNum == 3)
		{
			headers<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(A)")*/g_sLangTxt_Native_amplitudeA<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase;
		}
		else
		{
			headers<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(A)")*/g_sLangTxt_Native_amplitudeA<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase<</*tr("频率(Hz)")*/g_sLangTxt_Native_FreqHz;
		}
	}
	
	QFontMetrics fontMetrics = QFontMetrics(this->font());
	int nLabelWidth1 = fontMetrics.width(/*tr("通道")*/g_sLangTxt_Native_Channel) + 40;
	int nLabelWidth2 = fontMetrics.width(tr("-57.735")) + 20;
	int nLabelWidth3 = fontMetrics.width(/*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase) + 10;
	
	this->setColumnWidth(0,nLabelWidth1);
	this->setColumnWidth(1,nLabelWidth2);
	this->setColumnWidth(2,nLabelWidth3);
	if (m_ColumnNum > 3)
	{
		int nLabelWidth4 = fontMetrics.width(/*tr("频率(Hz)")*/g_sLangTxt_Native_FreqHz) + 20 ;
		this->setColumnWidth(3,nLabelWidth4);
	}
	setHorizontalHeaderLabels(headers);
	setIconSize(QSize(20,20));

	for (int row=0;row<this->rowCount();row++)
	{
		for (int col=0;col<this->columnCount();col++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			
			if (col == 0)
			{
				if((m_MacroType == MACROTYPE_State)||(m_MacroType == MACROTYPE_Manual))
				{
					item->setFlags(Qt::NoItemFlags);
					item->setTextColor(QColor(0, 0, 0));
				}
			}
			setItem(row,col,item);
			setRowHeight(row,m_nRowHeight);
		}
	}
	
	int ntableHight = this->horizontalHeader()->height() + ((m_nRowHeight)*this->rowCount());
	
	setFixedHeight(ntableHight);
	creatTableMenu();
}

void CHannelTable::changeTableColor()
{
	ASSERT(m_pChDatas);

//	if (m_moudleType==Moudle_U)//电压  zhouhj 20210828  经比较电流与电压通道的代码完全相同,无需分成两份
	{
		switch (m_pChDatas->GetCount())
		{
		case 3:
		case 4:
			{
				for (int i=0;i<rowCount();i++)
				{
					for (int j = 0;j<columnCount();j++)
					{
						QTableWidgetItem *item = this->item(i,j);
						if (item)
						{
							const QColor color = QColor(240,240,240);
							item->setBackgroundColor(color);
						}
					}
				}
			}
			break;
		case 6:
			{
				int Static=0;

				for (int i = 0;i < rowCount();i++)  
				{
					if (i/3 <= Static)  
					{  
						for (int j = 0;j < columnCount();j++)  
						{  
							QTableWidgetItem *item = this->item(i,j);  
							if (item)  
							{  
								item->setBackgroundColor(m_ColorList.at(Static));  
							}  
						}  
					}  

					if (i%3 == 2)
					{
						Static++;
					}
				} 
			}
			break;
		case 12:
			{
				int Static=0;

				for (int i = 0;i < rowCount();i++)  
				{
					if (i/3 <= Static)  
					{  
						for (int j = 0;j < columnCount();j++)  
						{  
							QTableWidgetItem *item = this->item(i,j);  
							if (item)  
							{  
								item->setBackgroundColor(m_ColorList.at(Static));  
							}  
						}  
					} 

					if (i%3 == 2)
					{
						Static++;
					}
				} 
			}
			break;
		case 18:
		default:
			{
				int Static=0;
				QColor oCurColor;

				for (int i = 0;i < rowCount();i++)  
				{
					if (i/3 <= Static)  
					{  
						for (int j = 0;j < columnCount();j++)  
						{  
							QTableWidgetItem *item = this->item(i,j);  

							if (item)  
							{  
								if (Static<m_ColorList.size())//zhouhj 20210828 必须保证当前取的数据,不能大于容器中的总数量
								{
									oCurColor = m_ColorList.at(Static);
								} 
								
								item->setBackgroundColor(oCurColor);  
							}  
						}  
					}  
					if (i%3 == 2)
					{
						Static++;
					}
				} 
			}
			break;
		}
	}
// 	else
// 	{
// 		switch (m_pChDatas->GetCount())
// 		{
// 		case 3:
// 		case 4:
// 			{
// 				for (int i=0;i<rowCount();i++)
// 				{
// 					for (int j = 0;j<columnCount();j++)
// 					{
// 						QTableWidgetItem *item = this->item(i,j);
// 						if (item)
// 						{
// 							const QColor color = QColor(240,240,240);
// 							item->setBackgroundColor(color);
// 						}
// 					}
// 				}
// 			}
// 			break;
// 		case 6:
// 			{
// 				int Static=0;
// 				for (int i = 0;i < rowCount();i++)  
// 				{
// 					if (i/3 <= Static)  
// 					{  
// 						for (int j = 0;j < columnCount();j++)  
// 						{  
// 							QTableWidgetItem *item = this->item(i,j);  
// 							if (item)  
// 							{  
// 								item->setBackgroundColor(m_ColorList.at(Static));  
// 							}  
// 						}  
// 					}  
// 					if (i%3 == 2)
// 					{
// 						Static++;
// 					}
// 				} 
// 			}
// 			break;
// 		case 12:
// 			{
// 				int Static=0;
// 				for (int i = 0;i < rowCount();i++)  
// 				{
// 					if (i/3 <= Static)  
// 					{  
// 						for (int j = 0;j < columnCount();j++)  
// 						{  
// 							QTableWidgetItem *item = this->item(i,j);  
// 							if (item)  
// 							{  
// 								item->setBackgroundColor(m_ColorList.at(Static));  
// 							}  
// 						}  
// 					}  
// 					if (i%3 == 2)
// 					{
// 						Static++;
// 					}
// 				} 
// 			}
// 			break;
// 		case 18:
// 			{
// 				int Static=0;
// 
// 				for (int i = 0;i < rowCount();i++)  
// 				{
// 					if (i/3 <= Static)  
// 					{  
// 						for (int j = 0;j < columnCount();j++)  
// 						{  
// 							QTableWidgetItem *item = this->item(i,j);  
// 
// 							if (item)  
// 							{  
// 								item->setBackgroundColor(m_ColorList.at(Static));  
// 							}  
// 						}  
// 					}  
// 					if (i%3 == 2)
// 					{
// 						Static++;
// 					}
// 				} 
// 			}
// 			break;
// 		default:
// 			break;
// 		}
// 	}
}

void CHannelTable::UpdateTable()
{
	ASSERT(m_pChDatas);
	POS pos = m_pChDatas->GetHeadPosition();
	//CExBaseObject *pCh = NULL;
	CSttChResource *pCh = NULL;
	long nChIndex = 0;
	QTableWidgetItem *pTableWidgetItem = NULL;
	m_oTempSaveDataMap.clear();

	while(pos)
	{
		pCh = (CSttChResource *)m_pChDatas->GetNext(pos);
		
		pTableWidgetItem = item(nChIndex,0);

		if (pTableWidgetItem == NULL)
		{
			break;
		}

		item(nChIndex,0)->setText(pCh->m_strName);
		item(nChIndex,1)->setText(QString::number(m_pArrUI[nChIndex].Harm[1].fAmp,'f',3));
		item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].Harm[1].fAngle,'f',2));//zhouhj相位精度改为2位  20220901

		if (m_ColumnNum > 3)
		{
			item(nChIndex,3)->setText(QString::number(m_pArrUI[nChIndex].Harm[1].fFreq,'f',3));
		}
		FloatTempChData *ptempData = new FloatTempChData;
		ptempData->fAngle = m_pArrUI[nChIndex].Harm[1].fAngle;
		ptempData->fHz = m_pArrUI[nChIndex].Harm[1].fFreq;
		m_oTempSaveDataMap.insert(nChIndex,ptempData);

		if((m_MacroType == MACROTYPE_State)|| (m_MacroType == MACROTYPE_Manual))
		{
			if (m_pArrUI[nChIndex].Ramp[0].nIndex == 1 || m_pArrUI[nChIndex].Ramp[1].nIndex == 1 || m_pArrUI[nChIndex].Ramp[2].nIndex == 1)
			{
				item(nChIndex,0)->setIcon(QPixmap("./images/gradual.png"));
			}
			else
			{
// 				if (g_oSystemParas.m_nHasAnalog && !g_oSystemParas.m_nHasDigital)
// 				{
// 					item(nChIndex,0)->setIcon(QPixmap("./images/analog.png"));
// 				}
// 				else if (!g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 				{
// 					item(nChIndex,0)->setIcon(QPixmap("./images/digital.png"));
// 				}
// 				else if (g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 				{
// 					item(nChIndex,0)->setIcon(QPixmap("./images/mix.png"));
// 				}


				if (pCh->m_nHasMapType == 1)
				{
					item(nChIndex,0)->setIcon(QPixmap("./images/analog.png"));
				}
				else if (pCh->m_nHasMapType == 2)
				{
					item(nChIndex,0)->setIcon(QPixmap("./images/digital.png"));
				}
				else if (pCh->m_nHasMapType == 4)
				{
					item(nChIndex,0)->setIcon(QPixmap("./images/mix.png"));
				}
			}
		}

		nChIndex++;
	}

	changeTableColor();
}

bool CHannelTable::HasHarmParaset()
{
	tmt_channel* pChannel = NULL;
	int i=0;

	if (m_moudleType == Moudle_U)
	{
		for (i=0;i<MAX_VOLTAGE_COUNT;i++)
		{
			pChannel = &m_pArrUI[i];
			for (int nIndex=2;nIndex<MAX_HARM_COUNT;nIndex++)
			{
				if (pChannel->Harm[nIndex].m_bSelect)
				{
					return true;
				}
			}
		}
	}
	else
	{
		for (i=0;i<MAX_CURRENT_COUNT;i++)
		{
			pChannel = &m_pArrUI[i];
			for (int nIndex=2;nIndex<MAX_HARM_COUNT;nIndex++)
			{
				if (pChannel->Harm[nIndex].m_bSelect)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool CHannelTable::IsBaseHarmAddValid(int row,int col,float fv)
{
	ASSERT(!m_bDCTest);
	ASSERT( row>=0 && row<=rowCount()-1 && col==1);

	bool bRet = true;

	float fTotal = fv*fv; 
	for(int i=2;i<MAX_HARM_COUNT;i++)
	{
		if (m_pArrUI[row].Harm[i].m_bSelect)
		{
			fTotal += m_pArrUI[row].Harm[i].fAmp*m_pArrUI[row].Harm[i].fAmp;
		}
	}

	fTotal = sqrt(fTotal);

	if(m_moudleType == Moudle_U && fTotal > g_oLocalSysPara.m_fAC_VolMax)
	{
		bRet = false;
	}
	else if(m_moudleType == Moudle_I && fTotal > g_oLocalSysPara.m_fAC_CurMax)
	{
		bRet = false;
	}

	return bRet;
}

void CHannelTable::slot_OnCellChanged(int row,int col)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);
	QString str = pItem->text();
	QString strInfo;
	float fv;
	QString strText;
	bool bChg = false;

	float fTempAngle = 0.0f,fTempHz = 0.0f;
	FloatTempChData *pTempChData = m_oTempSaveDataMap.value(row);

	switch (col)
	{
	case 1:
		{
			fv = str.toFloat();
			if (m_bDCTest)
			{
				if (fabs(fv) > m_fAmpMax)
				{
					if (fv > 0)
					{
						fv = m_fAmpMax;
					}
					else
					{
						fv = -m_fAmpMax;
					}
				
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f(%d,%d)超出范围(%f).")*/g_sLangTxt_Native_input_overrange.GetString(),fv,row,col,m_fAmpMax);
				}
				else if (fv<m_fAmpMin)
				{
					fv = m_fAmpMin;
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f(%d,%d)超出范围(%f).")*/g_sLangTxt_Native_input_overrange.GetString(),fv,row,col,m_fAmpMin);
				}
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
			else
			{	
				if (isPosiDigitstr(str))
				{
					str = initMaxAcV(str);
					fv = str.toFloat();

					//判断是否有谐波设置，再调用下面的函数判断
					if(HasHarmParaset() && !IsBaseHarmAddValid(row,col,fv))
					{
						if (m_moudleType == Moudle_U)
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("基波设置值%f(%d,%d)与谐波的叠加超出范围(%fV).")*/g_sLangTxt_Native_flowoverV.GetString(),fv,row,col,g_oLocalSysPara.m_fAC_VolMax);
						}
						else
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("基波设置值%f(%d,%d)与谐波的叠加超出范围(%fA).")*/g_sLangTxt_Native_flowoverA.GetString(),fv,row,col,g_oLocalSysPara.m_fAC_CurMax);
						}

						fv = m_pArrUI[row].Harm[1].fAmp;
					}
					pItem->setText(QString::number(fv,'f',3));
				}
				else
				{
					CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("输入值含有非法字符.")*/g_sLangTxt_State_IlleInputCharac.GetString());

					fv = m_pArrUI[row].Harm[1].fAmp;
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
			}

			if(m_pArrUI[row].Harm[1].fAmp != fv)
			{
				m_pArrUI[row].Harm[1].fAmp = fv;
				bChg = true;
			}
		}
		break;
	case 2:
		{
			fv = str.toFloat();
			float f1 = fv - (int)fv;
			int f2 = ((int)fv)%360;
			fv = f1+f2;
// 			int temp = (int)(fv*10)%10;
// 
// 			if (temp == 9 ||temp == -9)
// 			{
// 				fv = (int)fv+temp*0.1;
// 			}

			if (m_bDCTest)//zhouhj 20211031 在直流的模式下,相位固定为0
			{
				CString strText = pItem->text();
				pTempChData->fAngle = strText.toFloat();

				fv = 0;
			}

			strText.setNum(fv,'f',2); //zhouhj相位精度改为2位  20220901
			pItem->setText(strText);

			if(m_pArrUI[row].Harm[1].fAngle != fv)
			{
				m_pArrUI[row].Harm[1].fAngle = fv;
				bChg = true;
			}
		}
		break;
	case 3:
		{
			if ((m_MacroType == MACROTYPE_Manual))			//只输出模拟量状态下最大频率根据谐波次数决定  20240327 xueyangfan
			{
				fv = str.toFloat();
				if(g_oSystemParas.m_nHasAnalog && (!g_oSystemParas.m_nHasDigital) && (!g_oSystemParas.m_nHasWeek))
				{
					if (fv > g_oLocalSysPara.m_nMaxHarmCount * 50)
					{
						fv = g_oLocalSysPara.m_nMaxHarmCount * 50;
						CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f超出范围(%d).")*/g_sLangTxt_State_EnterTheValueoutofRange.GetString(),str.toFloat(),(long)fv);
						strText.setNum(fv,'f',3);
						pItem->setText(strText);
						break;
					}
				}
			}

			if (isPosiDigitstr(str))
			{
				str = initMaxHz(str);
				fv = str.toFloat();

				if (m_bDCTest)
				{
					CString strText = pItem->text();
					pTempChData->fHz = strText.toFloat();
//					if (fv < 0)  //zhouhj 20211031 在直流的模式下,频率固定为0
					{
						fv = 0;
					}
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
				fv = m_pArrUI[row].Harm[1].fFreq;
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}

			if(m_pArrUI[row].Harm[1].fFreq != fv)
			{
				m_pArrUI[row].Harm[1].fFreq = fv;
				bChg = true;
			}
		}
		break;
	default:
		break;
	}
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	//connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::QueuedConnection);   //20240424 xueyangfan 修改开始测试后迅速修改电压电流值闪退问题

	if (col > 0 && bChg && m_bSendUpdateParas)
	{
		emit sig_ChannelValueChanged(m_moudleType,row,col,fv);//valueFlag=（1:幅值 2:相位 3:频率）
	}
}

void CHannelTable::slot_TableShowMent(QPoint pos)
{
	//获得鼠标点击的x，y坐标点 
	int x = pos.x(); 
	int y = pos.y(); 
	QModelIndex index = this->indexAt(QPoint(x,y)); 
	int col = index.column();//获得QTableWidget列表点击的行数 

	switch(col)
	{
	case 1:
		{
			m_MenuAmp->move(cursor().pos()); 
			m_MenuAmp->show(); 

			if (g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
			{
				CString strEDPhase;
				int nRow = index.row();
				if (nRow == 3 && m_moudleType==Moudle_U)
				{
					strEDPhase = _T("额定零序电压");
					m_ActUAmpED->setText(strEDPhase);
					m_pActUAmpED2->setText("2%" + strEDPhase);
					m_pActUAmpED5->setText("5%" + strEDPhase);
					m_pActUAmpED20->setText("20%" + strEDPhase);	
					m_pActUAmpED120->setText("120%" + strEDPhase);
					m_pActUAmpED190->setText("190%" + strEDPhase);
				}
				else if(nRow != 3 && m_moudleType==Moudle_U)
				{
					strEDPhase = _T("额定电压");
					m_ActUAmpED->setText(strEDPhase);
					m_pActUAmpED2->setText("2%" + strEDPhase);
					m_pActUAmpED5->setText("5%" + strEDPhase);
					m_pActUAmpED20->setText("20%" + strEDPhase);	
					m_pActUAmpED120->setText("120%" + strEDPhase);
					m_pActUAmpED190->setText("190%" + strEDPhase);
				}
				else if (nRow == 3 && m_moudleType == Moudle_I)
				{
					strEDPhase = _T("额定零序电流");
					m_ActIAmpED->setText(strEDPhase);
					m_pActIAmpED1->setText("1%" + strEDPhase);
					m_pActIAmpED5->setText("5%" + strEDPhase);
					m_pActIAmpED20->setText("20%" + strEDPhase);	
					m_pActIAmpED100->setText("100%" + strEDPhase);
					m_pActIAmpED120->setText("120%" + strEDPhase);
				}
				else if (nRow != 3 && m_moudleType == Moudle_I)
				{
					strEDPhase = _T("额定电流");
					m_ActIAmpED->setText(strEDPhase);
					m_pActIAmpED1->setText("1%" + strEDPhase);
					m_pActIAmpED5->setText("5%" + strEDPhase);
					m_pActIAmpED20->setText("20%" + strEDPhase);	
					m_pActIAmpED100->setText("100%" + strEDPhase);
					m_pActIAmpED120->setText("120%" + strEDPhase);
				}
			}
		}
		break;
	case 2:
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
	case 3:
		{
			m_MenuFre->move(cursor().pos()); 
			m_MenuFre->show(); 
		}
		break;
	default:
		break;
	}
}

void CHannelTable::creatTableMenu()
{
	m_MenuAmp = new QMenu(this);
	m_MenuPhase = new QMenu(this);
	m_MenuFre = new QMenu(this);
	QString str;

	if (m_moudleType==Moudle_U)//电压模块
	{
		if (g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
		{
			m_ActUEqualAmp = new QAction(tr("等幅值"),this);
			m_ActUAmpED = new QAction(tr("额定电压"),this);
			m_pActUAmpED2 = new QAction(tr("2%额定电压"),this);
			m_pActUAmpED5 = new QAction(tr("5%额定电压"),this);
			m_pActUAmpED20 = new QAction(tr("20%额定电压"),this);
			m_pActUAmpED120 = new QAction(tr("120%额定电压"),this);
			m_pActUAmpED190 = new QAction(tr("190%额定电压"),this);

			CString strEDPhaseV;
			strEDPhaseV = _T("额定电压");
			m_ActUAmpED->setText(strEDPhaseV);
			m_pActUAmpED2->setText("2%" + strEDPhaseV);
			m_pActUAmpED5->setText("5%" + strEDPhaseV);
			m_pActUAmpED20->setText("20%" + strEDPhaseV);	
			m_pActUAmpED120->setText("120%" + strEDPhaseV);
			m_pActUAmpED190->setText("190%" + strEDPhaseV);

			m_MenuAmp->addAction(m_ActUEqualAmp);
			m_MenuAmp->addAction(m_ActUAmpED); 
			m_MenuAmp->addAction(m_pActUAmpED2); 
			m_MenuAmp->addAction(m_pActUAmpED5); 
			m_MenuAmp->addAction(m_pActUAmpED20); 
			m_MenuAmp->addAction(m_pActUAmpED120); 
			m_MenuAmp->addAction(m_pActUAmpED190); 

			connect (m_ActUEqualAmp,SIGNAL(triggered()),this,SLOT(slot_ActUEqualAmpClicked())); 
			connect (m_ActUAmpED,SIGNAL(triggered()),this,SLOT(slot_ActUAmpEDClicked())); 
			connect (m_pActUAmpED2,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
			connect (m_pActUAmpED5,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
			connect (m_pActUAmpED20,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
			connect (m_pActUAmpED120,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
			connect (m_pActUAmpED190,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
		}
		else
		{
		m_ActUAmpED = new QAction(/*tr("额定相电压")*/g_sLangTxt_Native_EDPhaseV,this);
		m_ActUZero = new QAction(/*tr("零")*/g_sLangTxt_Native_Zero,this);
		m_ActUEqualAmp = new QAction(/*tr("等幅值")*/g_sLangTxt_Native_EqualAmp,this);
		connect (m_ActUAmpED,SIGNAL(triggered()),this,SLOT(slot_ActUAmpEDClicked())); 
		connect (m_ActUZero,SIGNAL(triggered()),this,SLOT(slot_ActUZeroClicked()));
		connect (m_ActUEqualAmp,SIGNAL(triggered()),this,SLOT(slot_ActUEqualAmpClicked())); 
		m_MenuAmp->addAction(m_ActUAmpED); 
		m_MenuAmp->addAction(m_ActUZero);
		m_MenuAmp->addAction(m_ActUEqualAmp);
	}
	}
	else//电流模块
	{
		if (g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
		{
			m_ActIqualAmp = new QAction(tr("等幅值"),this);
			m_ActIAmpED = new QAction(/*tr("额定电流")*/g_sLangTxt_Native_EDCurrent,this);
			m_pActIAmpED1 = new QAction(tr("1%额定电流"),this);
			m_pActIAmpED5 = new QAction(tr("5%额定电流"),this);
			m_pActIAmpED20 = new QAction(tr("20%额定电流"),this);
			m_pActIAmpED100 = new QAction(tr("100%额定电流"),this);
			m_pActIAmpED120 = new QAction(tr("120%额定电流"),this);

			CString strEDPhaseA;
			strEDPhaseA = _T("额定电流");
			m_pActIAmpED1->setText("1%" + strEDPhaseA);
			m_pActIAmpED5->setText("5%" + strEDPhaseA);
			m_pActIAmpED20->setText("20%" + strEDPhaseA);	
			m_pActIAmpED100->setText("100%" + strEDPhaseA);
			m_pActIAmpED120->setText("120%" + strEDPhaseA);

			m_MenuAmp->addAction(m_ActIqualAmp);
			m_MenuAmp->addAction(m_ActIAmpED);
			m_MenuAmp->addAction(m_pActIAmpED1); 
			m_MenuAmp->addAction(m_pActIAmpED5); 
			m_MenuAmp->addAction(m_pActIAmpED20); 
			m_MenuAmp->addAction(m_pActIAmpED100); 
			m_MenuAmp->addAction(m_pActIAmpED120); 

			connect (m_ActIqualAmp,SIGNAL(triggered()),this,SLOT(slot_ActIqualAmpClicked())); 
			connect (m_ActIAmpED,SIGNAL(triggered()),this,SLOT(slot_ActIAmpEDClicked())); 
			connect (m_pActIAmpED1,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
			connect (m_pActIAmpED5,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
			connect (m_pActIAmpED20,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
			connect (m_pActIAmpED100,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
			connect (m_pActIAmpED120,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
		}
		else
		{
			m_ActIAmp1 = new QAction(tr("1A"),this);
			m_ActIAmp5 = new QAction(tr("5A"),this);
			m_ActIAmp0 = new QAction(/*tr("零")*/g_sLangTxt_Native_Zero,this);
			m_ActIqualAmp = new QAction(/*tr("等幅值")*/g_sLangTxt_Native_EqualAmp,this);
			m_ActIAmpED = new QAction(/*tr("额定电流")*/g_sLangTxt_Native_EDCurrent,this);

			connect (m_ActIAmp1,SIGNAL(triggered()),this,SLOT(slot_ActIAmp1Clicked())); 
			connect (m_ActIAmp5,SIGNAL(triggered()),this,SLOT(slot_ActIAmp5Clicked()));
			connect (m_ActIAmp0,SIGNAL(triggered()),this,SLOT(slot_ActIAmp0Clicked())); 
			connect (m_ActIqualAmp,SIGNAL(triggered()),this,SLOT(slot_ActIqualAmpClicked())); 
			connect (m_ActIAmpED,SIGNAL(triggered()),this,SLOT(slot_ActIAmpEDClicked())); 

			m_MenuAmp->addAction(m_ActIAmp1);
			m_MenuAmp->addAction(m_ActIAmp5); 
			m_MenuAmp->addAction(m_ActIAmp0); 
			m_MenuAmp->addAction(m_ActIqualAmp); 
			m_MenuAmp->addAction(m_ActIAmpED);
		}
	}

	QAction *m_ActUPhaseP = new QAction(/*tr("正序")*/g_sLangTxt_Native_PositiveSeq,this);
	QAction *m_ActUPhaseN = new QAction(/*tr("负序")*/g_sLangTxt_Native_NegativeSeq,this);
	QAction *m_ActUPhaseZ = new QAction(/*tr("零序")*/g_sLangTxt_Native_ZeroSeq,this);
	connect (m_ActUPhaseP,SIGNAL(triggered()),this,SLOT(slot_ActPhasePClicked())); 
	connect (m_ActUPhaseN,SIGNAL(triggered()),this,SLOT(slot_ActPhaseNClicked()));
	connect (m_ActUPhaseZ,SIGNAL(triggered()),this,SLOT(slot_ActPhaseZClicked())); 
	m_MenuPhase->addAction(m_ActUPhaseP);
	m_MenuPhase->addAction(m_ActUPhaseN); 
	m_MenuPhase->addAction(m_ActUPhaseZ); 

	QAction *m_ActIHz50 = new QAction(tr("50Hz"),this);
	QAction *m_ActIHz60 = new QAction(tr("60Hz"),this);
	QAction *m_ActIHzEqual = new QAction(/*tr("等频率")*/g_sLangTxt_Native_EqualFreq,this);
	QAction *m_ActIHzEqualAll = new QAction(/*tr("等全部频率")*/g_sLangTxt_Native_all_frequencies,this);

	connect (m_ActIHz50,SIGNAL(triggered()),this,SLOT(slot_ActHz50Clicked())); 
	connect (m_ActIHz60,SIGNAL(triggered()),this,SLOT(slot_ActHz60Clicked()));
	connect (m_ActIHzEqual,SIGNAL(triggered()),this,SLOT(slot_ActHzEqualClicked()));
	connect (m_ActIHzEqualAll,SIGNAL(triggered()),this,SLOT(slot_ActHzEqualAllClicked()));

	m_MenuFre->addAction(m_ActIHz50);
	m_MenuFre->addAction(m_ActIHz60); 
	m_MenuFre->addAction(m_ActIHzEqual); 
	m_MenuFre->addAction(m_ActIHzEqualAll); 

	connect(this, SIGNAL(customContextMenuRequested ( const QPoint & )), this, SLOT(slot_TableShowMent(QPoint)));
}

void CHannelTable::Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll)
{
	if (pItem == NULL)
	{
		return;
	}

	QString strVal = QString::number(fVal,'f',3);

	if (!bAll)
	{
		pItem->setText(strVal);
		return;
	}

	ASSERT(m_pChDatas);

	if (m_pChDatas->GetCount()==4)
	{
		for (int i=0;i<rowCount();i++)
		{
			item(i,1)->setText(strVal);
		}
	}
	else
	{
		int row = pItem->row();
		int imin = (int(row/3))*3;
		int imax = (int(row/3))*3 +2;
		if (imax>=rowCount())
		{
			imax = rowCount()-1;
		}
		for (int i=imin; i<=imax;i++)
		{
			item(i,1)->setText(strVal);
		}
	}
}

void CHannelTable::slot_ActUAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	if (g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
	{	
		int nRow = currentRow();
		if (nRow == 3)
		{
			Act_setUIAmpValue(pItem,g_oSystemParas.m_fU0_Std,FALSE);
		}
		else
		{
			Act_setUIAmpValue(pItem,m_fEDVal,FALSE);
		}
	}
	else
	{
		Act_setUIAmpValue(pItem,m_fEDVal / GenHao3,FALSE);
	}
}

void CHannelTable::slot_ActUZeroClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem)
	{
		pItem->setText(QString::number(0,'f',3));
	}
}

void CHannelTable::slot_ActUEqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void CHannelTable::slot_ActIAmp1Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem)
	{
		pItem->setText(QString::number(1,'f',3));
	}
}

void CHannelTable::slot_ActIAmp5Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem)
	{
		pItem->setText(QString::number(5,'f',3));
	}
}

void CHannelTable::slot_ActIAmp0Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem)
	{
		pItem->setText(QString::number(0,'f',3));
	}
}

void CHannelTable::slot_ActIqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void CHannelTable::slot_ActPerUAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	float fEDVal;
	int nRow = currentRow();
	if (g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
	{
		if (nRow == 3) //代表零序
		{
			fEDVal = g_oSystemParas.m_fU0_Std ;
		}
		else
		{
			fEDVal = m_fEDVal ;
		}
	}
	else
	{
		fEDVal = m_fEDVal / GenHao3;
	}

	QAction* pAction = (QAction*)sender();
	if(pAction->text().indexOf("120%") != -1)
	{
		fEDVal *= 1.2;
	}
	else if (pAction->text().indexOf("80%") != -1)
	{
		fEDVal *= 0.8;
	}
	else if (pAction->text().indexOf("60%") != -1)
	{
		fEDVal *= 0.6;
	}
	else if (pAction->text().indexOf("40%") != -1)
	{
		fEDVal *= 0.4;
	}
	else if (pAction->text().indexOf("20%") != -1)
	{
		fEDVal *= 0.2;
	}
	else if (pAction->text().indexOf("2%") != -1)
	{
		fEDVal *= 0.02;
	}
	else if (pAction->text().indexOf("5%") != -1)
	{
		fEDVal *= 0.05;
	}
	else if (pAction->text().indexOf("190%") != -1)
	{
		fEDVal *= 1.9;
	}

	Act_setUIAmpValue(pItem,fEDVal,FALSE);
}

void CHannelTable::slot_ActPerIAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	float fEDVal ;
	int nRow = currentRow();
	if (nRow == 3) //代表零序
	{
		fEDVal = g_oSystemParas.m_fI0_Std;
	}
	else
	{
		fEDVal = m_fEDVal;
	}

	QAction* pAction = (QAction*)sender();
	if(pAction->text().indexOf("120%") != -1)
	{
		fEDVal *= 1.2;
	}
	else if (pAction->text().indexOf("80%") != -1)
	{
		fEDVal *= 0.8;
	}
	else if (pAction->text().indexOf("60%") != -1)
	{
		fEDVal *= 0.6;
	}
	else if (pAction->text().indexOf("40%") != -1)
	{
		fEDVal *= 0.4;
	}
	else if (pAction->text().indexOf("20%") != -1)
	{
		fEDVal *= 0.2;
	}
	else if (pAction->text().indexOf("1%") != -1)
	{
		fEDVal *= 0.01;
	}
	else if (pAction->text().indexOf("5%") != -1)
	{
		fEDVal *= 0.05;
	}
	else if (pAction->text().indexOf("100%") != -1)
	{
		fEDVal *= 1;
	}

	Act_setUIAmpValue(pItem,fEDVal,FALSE);
}

void CHannelTable::slot_ActIAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	if (g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
	{	
		int nRow = currentRow();
		if (nRow == 3)
		{
			Act_setUIAmpValue(pItem,g_oSystemParas.m_fI0_Std,FALSE);
		}
		else
		{
	Act_setUIAmpValue(pItem,m_fEDVal,FALSE);
		}
	}
	else
	{
		Act_setUIAmpValue(pItem,m_fEDVal,FALSE);
	}
}

void CHannelTable::Act_setPrasePValue(int nSwitch,int nOffset,float fv)
{
	float fVal1 = 0,fVal2 = 0;
	long nMaxCount = rowCount();

	switch(nSwitch)
	{
	case 0:
		fVal1 = fv-120;
		fVal2 = fv+120;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);

		if ((nOffset+2)<nMaxCount)
		{
			item(nOffset+1,2)->setText(QString::number(fVal1,'f',2));//zhouhj相位精度改为2位  20220901
			item(nOffset+2,2)->setText(QString::number(fVal2,'f',2));//zhouhj相位精度改为2位  20220901
		}
		else if ((nOffset+1)<nMaxCount)
		{
			item(nOffset+1,2)->setText(QString::number(fVal1,'f',2));//zhouhj相位精度改为2位  20220901
		}
		
		break;
	case 1:
		fVal1 = fv+120;
		fVal2 = fv+240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		item(nOffset,2)->setText(QString::number(fVal1,'f',2));//zhouhj相位精度改为2位  20220901

		if ((nOffset+2)<nMaxCount)
		{
			item(nOffset+2,2)->setText(QString::number(fVal2,'f',2));//zhouhj相位精度改为2位  20220901
		}

		break;
	case 2:
		fVal1 = fv-120;
		fVal2 = fv-240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		item(nOffset,2)->setText(QString::number(fVal1,'f',2));//zhouhj相位精度改为2位  20220901
		item(nOffset+1,2)->setText(QString::number(fVal2,'f',2));//zhouhj相位精度改为2位  20220901
		break;
	default:
		break;
	}
}

void CHannelTable::Act_setPraseNValue(int nSwitch,int nOffset,float fv)
{
	float fVal1 = 0,fVal2 = 0;
	long nMaxCount = rowCount();

	switch(nSwitch)
	{
	case 0:
		fVal1 = fv+120;
		fVal2 = fv-120;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);

		if ((nOffset+2)<nMaxCount)
		{
			item(nOffset+1,2)->setText(QString::number(fVal1,'f',2));//zhouhj相位精度改为2位  20220901
			item(nOffset+2,2)->setText(QString::number(fVal2,'f',2));//zhouhj相位精度改为2位  20220901
		}
		else if ((nOffset+1)<nMaxCount)
		{
			item(nOffset+1,2)->setText(QString::number(fVal1,'f',2));//zhouhj相位精度改为2位  20220901
		}

		break;
	case 1:
		fVal1 = fv-120;
		fVal2 = fv-240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		item(nOffset,2)->setText(QString::number(fVal1,'f',2));//zhouhj相位精度改为2位  20220901

		if ((nOffset+2)<nMaxCount)
		{
			item(nOffset+2,2)->setText(QString::number(fVal2,'f',2));//zhouhj相位精度改为2位  20220901
		}

		break;
	case 2:
		fVal1 = fv+120;
		fVal2 = fv+240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		item(nOffset,2)->setText(QString::number(fVal1,'f',2));//zhouhj相位精度改为2位  20220901
		item(nOffset+1,2)->setText(QString::number(fVal2,'f',2));//zhouhj相位精度改为2位  20220901
		break;
	default:
		break;
	}
}

void CHannelTable::slot_ActPhasePClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	int row = pItem->row();
	float fv = pItem->text().toFloat();
	ASSERT(m_pChDatas);

	if (m_moudleType==Moudle_U)	//电压模块
	{
		if (m_pChDatas->GetCount()==4)
		{
			Act_setPrasePValue(row,0,fv);
		}
		else/* if ((m_pChDatas->GetCount() % 3) == 0)*///zhouhj 20210624  需要考虑不为3的整数倍的情况
		{
			int imin = (int(row/3))*3;
			Act_setPrasePValue(row%3,imin,fv);
		}
	}
	else						//电流模块
	{
		int imin = (int(row/3))*3;
		Act_setPrasePValue(row%3,imin,fv);
	}
}

void CHannelTable::slot_ActPhaseNClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	int row = pItem->row();
	float fv = pItem->text().toFloat();
	ASSERT(m_pChDatas);
	
	if (m_moudleType==Moudle_U)
	{
		if (m_pChDatas->GetCount()==4)
		{
			Act_setPraseNValue(row,0,fv);
		}
		else /*if ((m_pChDatas->GetCount() % 3) == 0)*/
		{
			int imin = (int(row/3))*3;
			Act_setPraseNValue(row%3,imin,fv);
		}
	}
	else
	{
		int imin = (int(row/3))*3;
		Act_setPraseNValue(row%3,imin,fv);
	}
}

void CHannelTable::Act_setPraseZValue(int nStart,int nEnd)
{
	QString strVal = QString::number(0,'f',2);//zhouhj相位精度改为2位  20220901
	long nMaxCount = rowCount();

	if (nEnd>=nMaxCount)
	{
		nEnd = (nMaxCount-1);
	}

	for (int i=nStart; i<=nEnd; i++)
	{
		item(i,2)->setText(strVal);
	}
}

void CHannelTable::slot_ActPhaseZClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	int row = pItem->row();
	ASSERT(m_pChDatas);

	if (m_moudleType==Moudle_U)//电压模块
	{
		if (m_pChDatas->GetCount()==4)
		{
			Act_setPraseZValue(0,3);
		}
		else/* if ((m_pChDatas->GetCount() % 3) == 0)*/
		{
			int imin = (int(row/3))*3;
			Act_setPraseZValue(imin,imin+2);
		}
	}
	else
	{
		int imin = (int(row/3))*3;
		Act_setPraseZValue(imin,imin+2);
	}
}
void CHannelTable::slot_ActHz50Clicked()
{
	if (m_bDCTest==false)
	{
		QTableWidgetItem *pItem = this->currentItem();
		if (pItem)
		{
			pItem->setText(QString::number(50,'f',3));
		}
	}
}

void CHannelTable::slot_ActHz60Clicked()
{
	if (m_bDCTest==false)
	{
		QTableWidgetItem *pItem = this->currentItem();
		if (pItem)
		{
			pItem->setText(QString::number(60,'f',3));
		}
	}	
}

void CHannelTable::Act_setHzEqualValue(int nStart,int nEnd,float fv)
{
	QString strVal = QString::number(fv,'f',3);

	for (int i=nStart; i<=nEnd; i++)
	{
		if(i>m_pChDatas->GetCount()-1)
		{
			break;
		}

		item(i,3)->setText(strVal);
	}
}

void CHannelTable::slot_ActHzEqualClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	ASSERT(m_pChDatas);
	int row = pItem->row();
	float fv = pItem->text().toFloat();

	if (m_pChDatas->GetCount()==4)
	{
		Act_setHzEqualValue(0,3,fv);
	}
	else
	{
		int imin = (int(row/3))*3;
		int imax = imin +2;
		Act_setHzEqualValue(imin,imax,fv);
	}
}

void CHannelTable::slot_ActHzEqualAllClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	ASSERT(m_pChDatas);
	int row = pItem->row();
	float fv = pItem->text().toFloat();
	if (m_pChDatas->GetCount()==4)
	{
		Act_setHzEqualValue(0,3,fv);
	}
	else
	{
		int imin = 0;
		int imax = m_pChDatas->GetCount();
		Act_setHzEqualValue(imin,imax,fv);
	}
}

QString CHannelTable::initMaxAcV(QString str)
{
	if (str.toFloat()- m_fAmpMax > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f超出范围(%f).")*/g_sLangTxt_Native_InputOutOfRange.GetString(),str.toFloat(),m_fAmpMax);
		return QString("%1").arg(m_fAmpMax);
	}
	else
	{
		return str;
	}
}

QString CHannelTable::initMaxAcI(QString str)
{
	if (str.toFloat()- m_fAmpMax > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f超出范围(%f).")*/g_sLangTxt_Native_InputOutOfRange.GetString(),str.toFloat(),m_fAmpMax);
		return QString("%1").arg(m_fAmpMax);
	}
	else
	{
		return str;
	}
}

QString CHannelTable::initMaxHz(QString str)
{
	if (str.toFloat()- MAXHZ > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("输入值%f超出范围(%d).")*/g_sLangTxt_State_EnterTheValueoutofRange.GetString(),str.toFloat(),MAXHZ);
		return QString("%1").arg(MAXHZ);
	}
	else
	{
		return str;
	}
}

void CHannelTable::UpdateValidTableDatas()
{
	for (int i=0;i<rowCount();i++)
	{
		for (int j=0;j<columnCount();j++)
		{
			slot_OnCellChanged(i,j);
		}
	}
}

void CHannelTable::keyPressEvent(QKeyEvent *event)
{
	if (!m_bUsekeyPressEventExec)//不执行转发时
	{
		QTableWidget::keyPressEvent(event);
		return;
	}

	int nKeyValue = event->key();

	if ((nKeyValue == Qt::Key_F2)||(nKeyValue == Qt::Key_Escape)||(nKeyValue == Qt::Key_Left)||(nKeyValue == Qt::Key_Right)
		||(nKeyValue == Qt::Key_Up)||(nKeyValue == Qt::Key_Down))
	{
		emit sig_keyPressEventExec(nKeyValue);
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("CHannelTable::keyPressEvent,Key_F2"));
//		QTableWidget::keyPressEvent(event);
	}
	else
	{
		QTableWidget::keyPressEvent(event);
	}
}


void CHannelTable::mousePressEvent(QMouseEvent *ev)
{
	if (ev->button() == Qt::RightButton)
	{
		QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,ev->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
		QApplication::postEvent(this,pEvent);
	}

	QTableWidget::mousePressEvent( ev );
}

void CHannelTable::mouseReleaseEvent(QMouseEvent *ev)
{
	QList<QLineEdit*> oList = findChildren<QLineEdit*>();
	for (int i = 0; i < oList.size(); i++)
	{
		oList[i]->setContextMenuPolicy(Qt::NoContextMenu);
		oList[i]->installEventFilter(this);
	}

	QTableWidget::mouseReleaseEvent( ev );
}
