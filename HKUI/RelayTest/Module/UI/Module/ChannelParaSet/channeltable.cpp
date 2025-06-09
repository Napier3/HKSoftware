#include "channeltable.h"
#include <QFontMetrics>
#include <QScrollBar>
#include <cmath>
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../SttTestSysGlobalPara.h"
#include "../../../Module/API/MathApi.h"
#include "../../../Module/System/VariantDataAddress.h"
#include "../../../SttSystemConfig/SttSystemConfig.h"
#include "../../Controls/SettingCtrls/QSettingItem.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

//#define GenHao3	1.7320508 //根号三
#include <QDesktopWidget>
#include <QApplication>


extern bool Stt_Global_IsSetting(QObject *pObject);	

QChannelTable::QChannelTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent)
	: QScrollTableWidget(parent)
{
	m_pnHarmIndex = NULL;
	m_pChDatas = pChList;
	m_MacroType = 0;
	m_moudleType = moudleType;
	m_pArrUI = pArrUI;
	m_bDC = false;
	m_ColorList<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181)<<QColor(168,169,171)<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181);

	m_fAmpMax = 120;
	m_fAmpMin = 0;
	for (int i = 0; i < MAX_VOLTAGE_COUNT; i++)
	{
		m_fMultAmpMax[i] = 120;
		m_fMultAmpMin[i] = 0;
	}
	m_fEDVal = 0;
	m_pCurrKeyboardItem = NULL;

	m_bRunning = FALSE;
	installEventFilter(this);


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

	init();
}

QChannelTable::~QChannelTable()
{

}

void QChannelTable::setTableData(tmt_channel *pArrUI)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	disconnect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)));

	m_pArrUI = pArrUI;
	UpdateTable();

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)),Qt::UniqueConnection);
}

void QChannelTable::setHarmIndex(int *pnHarmIndex)
{
	m_pnHarmIndex = pnHarmIndex;
}

int QChannelTable::GetHarmIndex()
{
	if ((m_MacroType != MACROTYPE_ManualHarm)||(m_pnHarmIndex == NULL))
	{
		return 1;
	}

	if ((*m_pnHarmIndex)>=MAX_HARM_COUNT)
	{
		return 1;
	}

	int nHarmIndex = *m_pnHarmIndex;
	return nHarmIndex;
}

void QChannelTable::setProperty(bool bDC)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	disconnect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)));
	
	bool bTempDc = m_bDC;
	m_bDC = bDC;
	FloatTempChData *pData = NULL;
	

	if ((m_bDC)&&
		((m_MacroType != MACROTYPE_ManualHarm)&&(m_MacroType != MACROTYPE_ManualSequence)
		&& (m_MacroType != MACROTYPE_ManualLineVol) && (m_MacroType != MACROTYPE_ManualPower)))
	{
		setColumnHidden(2, true);
		setColumnHidden(3, true);

		for (int i=0;i<rowCount();i++)
		{
			item(i,2)->setFlags(Qt::NoItemFlags);
			item(i,2)->setBackground(Qt::gray);

			item(i,3)->setFlags(Qt::NoItemFlags);
			item(i,3)->setBackground(Qt::gray);

			m_pArrUI[i].Harm[1].bDC = 1;
		}
	}
	else
	{
		setColumnHidden(2, false);
		setColumnHidden(3, false);

		for (int i=0;i<rowCount();i++)
		{
			if(bDC != bTempDc)
			{
				pData = m_oTempSaveDataMap.value(i);
				m_pArrUI[i].Harm[GetHarmIndex()].fAngle = pData->fAngle;
				m_pArrUI[i].Harm[GetHarmIndex()].fFreq = pData->fHz;
			}

			item(i,2)->setFlags(item(i,1)->flags());
			item(i,2)->setBackground(item(i,1)->background());

			//20240624 huangliang
			//item(i,2)->setText(QString::number(m_pArrUI[i].Harm[GetHarmIndex()].fAngle,'f',1));
			((QSettingItem*)item(i,2))->UpdateStructText(CVariantDataAddress(&m_pArrUI[i].Harm[GetHarmIndex()].fAngle), 1);

			if ((m_MacroType != MACROTYPE_ManualHarm) && (m_MacroType != MACROTYPE_ManualSequence) && (m_MacroType != MACROTYPE_ManualLineVol) && (m_MacroType != MACROTYPE_ManualPower))
			{
				item(i,3)->setFlags(item(i,1)->flags());
				item(i,3)->setBackground(item(i,1)->background());

				//20240624 huangliang
				//item(i,3)->setText(QString::number(m_pArrUI[i].Harm[GetHarmIndex()].fFreq,'f',3));
				((QSettingItem*)item(i,3))->UpdateStructText(CVariantDataAddress(&m_pArrUI[i].Harm[GetHarmIndex()].fFreq), 3);
			}
			
			m_pArrUI[i].Harm[GetHarmIndex()].bDC = 0;
		}
	}
	
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)),Qt::UniqueConnection);
}

void QChannelTable::setItemValue(int row,int col,float fv)
{
	if (row<rowCount()&&col<columnCount())
	{
		if (col>0&&col<columnCount())
		{
			if (col==2)
			{
				item(row,col)->setText(QString::number(fv,'f',1));
			}
			else
			{
				item(row,col)->setText(QString::number(fv,'f',3));
			}
		}
	}
}

float QChannelTable::getItemValue(int row,int col)
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

void QChannelTable::setAmpMaxMinValue(float fmax,float fmin)
{
	m_fAmpMax = fmax;
	m_fAmpMin = fmin;
	UpdateTable();//20240204 suyang 更新最大最小值后 更新通道数据范围大小 
}

void QChannelTable::setMultAmpMaxMinValue(float fmax[], float fmin[])
{
	for (int i = 0; i < MAX_VOLTAGE_COUNT; i++)
	{
		m_fMultAmpMax[i] = fmax[i];
		m_fMultAmpMin[i] = fmin[i];
	}
	UpdateTable();
}

void QChannelTable::setAmpEDValue(float fEDValue)
{
	m_fEDVal = fEDValue;
}

void QChannelTable::setColumnWidthByNum(int col,int width)
{
	setColumnWidth(col,width);
}

void QChannelTable::setTableFixWidgt(int width)
{
	this->setFixedWidth(width);
}

int QChannelTable::getTableHeight()
{
	return this->height();
}

int QChannelTable::getTableWidth()
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

void QChannelTable::init()
{
	setFocusPolicy(Qt::NoFocus);
	setContextMenuPolicy (Qt::CustomContextMenu);

	QHeaderView* pLeft = this->verticalHeader();
	pLeft->setDefaultSectionSize(25);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//
    pLeft->setSectionsClickable(false);
#else
    pLeft->setClickable(false);
#endif
	pLeft->setVisible(false);

	QFont font1 = this->horizontalHeader()->font();
	font1.setBold(true);
	
	this->horizontalHeader()->setFont(font1);
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
	QFontMetrics fontHeaderViewMe = QFontMetrics(font1);
	m_nHeaderViewHeight = fontHeaderViewMe.height() + 20;
	QFont font2 = this->font();
	font2.setPointSize(20);
	this->setFont(font2);
	QFontMetrics fontRowMe = QFontMetrics(font2);
	m_nRowHeight = fontRowMe.height() + 15;
	
	this->horizontalScrollBar()->setEnabled(true);
	this->verticalScrollBar()->setEnabled(true);

	QDesktopWidget *pDeskTop = QApplication::desktop();
	QRect rcScreen = pDeskTop->screenGeometry();
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections  Section
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
    this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    QFont font3 = this->horizontalHeader()->font();
	font3.setPointSize(20);
	this->horizontalHeader()->setFont(font3);

	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void QChannelTable::initTable()
{
	ASSERT(m_pChDatas);

	if ((m_MacroType == MACROTYPE_ManualSequence)||(m_MacroType == MACROTYPE_ManualLineVol))
	{
		long nGroupNum = m_pChDatas->GetCount()/3;
		setRowCount(nGroupNum*3);
	} 
	else
	{
		setRowCount(m_pChDatas->GetCount());
	}
	

	if ((m_MacroType == MACROTYPE_ManualHarm) || (m_MacroType == MACROTYPE_ManualSequence) || (m_MacroType == MACROTYPE_ManualLineVol) || (m_MacroType == MACROTYPE_ManualPower))
	{
		setColumnCount(3);//谐波界面没有频率
	} 
	else
	{
		setColumnCount(4);
	}

	QStringList headers;
/*
	if (m_moudleType==Moudle_U)//U
	{
		headers<<tr("通道")<<tr("幅值(V)")<<tr("相位(°)")<<tr("频率(Hz)");
	}
	else
	{
		headers<<tr("通道")<<tr("幅值(A)")<<tr("相位(°)")<<tr("频率(Hz)");
	}
	
	QFontMetrics fontMetrics = QFontMetrics(this->font());
	int nLabelWidth1 = fontMetrics.width(tr("通道")) + 40;
	int nLabelWidth2 = fontMetrics.width(tr("-57.735")) + 20;
	int nLabelWidth3 = fontMetrics.width(tr("相位(°))")) + 10;
	int nLabelWidth4 = fontMetrics.width(tr("频率(Hz)")) + 10 ;
*/
	CString strChannel, strAmplitude, strPhase, strFreq;
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
	int nLabelWidth1 = fontMetrics.width(strChannel) + 40;
	int nLabelWidth2 = fontMetrics.width(tr("-57.735")) + 20;
	int nLabelWidth3 = fontMetrics.width(strPhase) + 10;
	int nLabelWidth4 = fontMetrics.width(strFreq) + 10 ;

	this->setColumnWidth(0,nLabelWidth1);
	this->setColumnWidth(1,nLabelWidth2);
	this->setColumnWidth(2,nLabelWidth3);

	if ((m_MacroType == MACROTYPE_ManualHarm) || (m_MacroType == MACROTYPE_ManualSequence) || (m_MacroType == MACROTYPE_ManualLineVol) || (m_MacroType == MACROTYPE_ManualPower))
	{
		headers << strChannel << strAmplitude << strPhase;
	}	
	else
	{
		this->setColumnWidth(3,nLabelWidth4);
		headers << strChannel << strAmplitude << strPhase << strFreq;
	}
	
	setHorizontalHeaderLabels(headers);
	setIconSize(QSize(20,20));

	for (int row=0;row<this->rowCount();row++)
	{
		for (int col=0;col<this->columnCount();col++)
		{
			//20240624 huangliang
			//QTableWidgetItem *iSettem = new QTableWidgetItem;
			QSettingItem *iSettem = new QSettingItem(this);	///创建定值关联控件
			iSettem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			
			if (col == 0)
			{
				if((m_MacroType == MACROTYPE_State)||(m_MacroType == MACROTYPE_RemoteMeas))
				{
//					item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
					iSettem->setFlags(Qt::NoItemFlags);
				}
				else if ((m_MacroType == MACROTYPE_Manual) || (m_MacroType == MACROTYPE_ManualHarm) || (m_MacroType == MACROTYPE_ManualSequence) || (m_MacroType == MACROTYPE_ManualLineVol) || (m_MacroType == MACROTYPE_ManualPower))
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
	
	//setFixedHeight(ntableHight);
	creatTableMenu();
}

void QChannelTable::changeTableColor()
{
	ASSERT(m_pChDatas);

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

void QChannelTable::changeTableColor_LineVol()
{
	ASSERT(m_pChDatas);

	switch (m_pChDatas->GetCount())
	{
	case 2:
	case 3:
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
	case 4:
		{
			int Static=0;

			for (int i = 0;i < rowCount();i++)  
			{
				if (i/2 <= Static)  
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

				if (i%2 == 1)
				{
					Static++;
				}
			} 
		}
		break;
	case 8:
		{
			int Static=0;

			for (int i = 0;i < rowCount();i++)  
			{
				if (i/2 <= Static)  
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

				if (i%2 == 1)
				{
					Static++;
				}
			} 
		}
		break;
	case 16:
	default:
		{
			int Static=0;
			QColor oCurColor;

			for (int i = 0;i < rowCount();i++)  
			{
				if (i/2 <= Static)  
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
				if (i%2 == 1)
				{
					Static++;
				}
			} 
		}
		break;
	}
}

void QChannelTable::changeTableColor_RemoteMeas()
{
	int Static=0;
	QColor oCurColor;

	for (int i = 0;i < rowCount();i++)  
	{
		if (i/4 <= Static)  
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
		if (i%4 == 3)
		{
			Static++;
		}
	} 
}

CString GetSequenceChName(const CString &strID,long nChIndex)
{
	CString strSequenceChName;
	strSequenceChName = strID.Left(1);
	long nGroupIndex = nChIndex/3 + 1;

	if (nChIndex%3 == 0)
	{
		strSequenceChName.AppendFormat(_T("%ld-1"),nGroupIndex);
	} 
	else if (nChIndex%3 == 1)
	{
		strSequenceChName.AppendFormat(_T("%ld-2"),nGroupIndex);
	} 
	else if (nChIndex%3 == 2)
	{
		strSequenceChName.AppendFormat(_T("%ld-0"),nGroupIndex);
	} 

	return strSequenceChName;
}

CString Global_GetLineVolChName(const CString &strID,long nChIndex) //线电压的通道
{
	CString strVoltageChName;
	strVoltageChName = strID.Left(1);  
	long nGroupIndex = nChIndex/3 + 1;
	long nGroupVIndex = nChIndex/2 + 1;
	if (strVoltageChName.contains("U"))
	{
		if (nChIndex%2 == 0)
		{
			strVoltageChName.AppendFormat(_T("ab%ld"),nGroupVIndex);
		} 
		else if (nChIndex%2 == 1)
		{
			strVoltageChName.AppendFormat(_T("%ld-0"),nGroupVIndex);	//U1-0
			strVoltageChName = "3"+strVoltageChName;							//	3U1-0
		} 
	}
	else
	{
		if (nChIndex%3 == 0)
		{
			strVoltageChName.AppendFormat(_T("a%ld"),nGroupIndex);
		} 
		else if (nChIndex%3 == 1)
		{
			strVoltageChName.AppendFormat(_T("b%ld"),nGroupIndex);
		} 
		else if (nChIndex%3 == 2)
		{
			strVoltageChName.AppendFormat(_T("c%ld"),nGroupIndex);
		} 
	}

	return strVoltageChName;
}

void QChannelTable::UpdateTable()
{
	ASSERT(m_pChDatas);
	POS pos = m_pChDatas->GetHeadPosition();
	//CExBaseObject *pCh = NULL;
	CSttChResource *pCh = NULL;//20240528 suyang 采用CSttChResource 类根据m_nHasMapType来显示
	long nChIndex = 0;
	QTableWidgetItem *pCurrItem = NULL;
	QTableWidgetItem *pTableWidgetItem = NULL;
	CString strChName;

	if(!m_bDC)
	{
		m_oTempSaveDataMap.clear();
	}

	while(pos)
	{
		pCh = (CSttChResource *)m_pChDatas->GetNext(pos);

		pTableWidgetItem = item(nChIndex,0);

		if (pTableWidgetItem == NULL)
		{
			break;
		}
		else if (m_MacroType == MACROTYPE_ManualSequence)
		{
			strChName = GetSequenceChName(pCh->m_strID,nChIndex);
		}
		else if (m_MacroType == MACROTYPE_ManualLineVol)
		{
			strChName = Global_GetLineVolChName(pCh->m_strID,nChIndex);
		}
		else
		{
			strChName = pCh->m_strName;
		}

		pTableWidgetItem->setText(strChName);
		
		//20240204 suyang 增加合并电流输出时 电流通道判断
		float fAmp = m_pArrUI[nChIndex].Harm[GetHarmIndex()].fAmp;

		if (m_MacroType == MACROTYPE_ManualPower)
		{
			m_fAmpMax = m_fMultAmpMax[nChIndex];
			m_fAmpMin = m_fMultAmpMin[nChIndex];
		}

		if (fAmp > m_fAmpMax)
		{
			fAmp = m_fAmpMax;
		}

		if (fAmp < m_fAmpMin)
		{
			if (m_MacroType == MACROTYPE_ManualPower)
			{
				if (pCh->m_strName != "U0")//add wangtao 20241018 功率U0不判断最小电压
				{
					fAmp = m_fAmpMin;
				//TODO wangtao 20240829 缺少多语言，具体文字内容待讨论
				CLogPrint::LogFormatString(XLOGLEVEL_RESULT, "输入值%f小于最小电压(%f)，会导致电流超过最大值(%f).", fAmp, m_fAmpMin, g_oLocalSysPara.m_fAC_CurMax);
			}

			}
			else
			{
			fAmp = m_fAmpMin;
		}
		}
		if (m_pArrUI[nChIndex].Harm[GetHarmIndex()].fAmp != fAmp)
		{
			 m_pArrUI[nChIndex].Harm[GetHarmIndex()].fAmp = fAmp;
		}
		
		QTableWidgetItem *pTableWidgetItem = item(nChIndex, 0);
		CString str = pTableWidgetItem->text();
		if ((m_MacroType == MACROTYPE_RemoteMeas || m_MacroType == MACROTYPE_State || m_MacroType == MACROTYPE_Manual) && (g_oSystemParas.m_nHasWeek))
		{
			float fMaxValue = 0;
			if (str == _T("U0"))
			{
				fMaxValue  =  8.3;
			}
			else if (str == _T("I0"))
			{
				fMaxValue  =  4.2;
			}
			else if (str != _T("U0"))
			{
				fMaxValue = 4.2;
			}
			else if (str != _T("I0"))
			{
				fMaxValue = 21;
			}
			if (m_pArrUI[nChIndex].Harm[GetHarmIndex()].fAmp > fMaxValue)
			{
				m_pArrUI[nChIndex].Harm[GetHarmIndex()].fAmp = fMaxValue;
			}
		}

		if(!m_bDC)
		{
			FloatTempChData *ptempData = new FloatTempChData;
			ptempData->fAngle = m_pArrUI[nChIndex].Harm[GetHarmIndex()].fAngle;
			ptempData->fHz = m_pArrUI[nChIndex].Harm[GetHarmIndex()].fFreq;
			m_oTempSaveDataMap.insert(nChIndex,ptempData);
		}
		
		//20240624 huangliang
		//item(nChIndex,1)->setText(QString::number(m_pArrUI[nChIndex].Harm[GetHarmIndex()].fAmp,'f',3));
		((QSettingItem*)item(nChIndex,1))->UpdateStructText(CVariantDataAddress(&m_pArrUI[nChIndex].Harm[GetHarmIndex()].fAmp), 3);

		//item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].Harm[GetHarmIndex()].fAngle,'f',1));
		((QSettingItem*)item(nChIndex,2))->UpdateStructText(CVariantDataAddress(&m_pArrUI[nChIndex].Harm[GetHarmIndex()].fAngle), 1);

		if ((m_MacroType != MACROTYPE_ManualHarm) && (m_MacroType != MACROTYPE_ManualSequence) && (m_MacroType != MACROTYPE_ManualLineVol) && (m_MacroType != MACROTYPE_ManualPower))
		{
			//item(nChIndex,3)->setText(QString::number(m_pArrUI[nChIndex].Harm[GetHarmIndex()].fFreq,'f',3));
			((QSettingItem*)item(nChIndex,3))->UpdateStructText(CVariantDataAddress(&m_pArrUI[nChIndex].Harm[GetHarmIndex()].fFreq), 3);

		}

		pCurrItem = item(nChIndex,0);

		if (pCurrItem == NULL)
		{
			nChIndex++;
			continue;
		}

		//2024-8-1 wuxinyi 国际版程序状态序列和通用实验模块需要显示通道类型
#ifdef _PSX_QT_WINDOWS_
 		if(m_MacroType == MACROTYPE_State || m_MacroType == MACROTYPE_Manual)
#else
		if(m_MacroType == MACROTYPE_State)
#endif
		{
#ifdef _PSX_QT_WINDOWS_

			if (xlang_IsCurrXLanguageChinese())
			{
			if (m_pArrUI[nChIndex].Ramp[0].nIndex == 1 || m_pArrUI[nChIndex].Ramp[1].nIndex == 1 || m_pArrUI[nChIndex].Ramp[2].nIndex == 1)
			{
				pCurrItem->setIcon(QPixmap("./images/gradual.png"));
			}
			else
			{
// 				if (g_oSystemParas.m_nHasAnalog && !g_oSystemParas.m_nHasDigital)
// 				{
// 					pCurrItem->setIcon(QPixmap("./images/analog.png"));
// 				}
// 				else if (!g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 				{
// 					pCurrItem->setIcon(QPixmap("./images/digital.png"));
// 				}
// 				else if (g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 				{
// 					pCurrItem->setIcon(QPixmap("./images/mix.png"));
// 				}

				if (pCh->m_nHasMapType == 1)
				{
						item(nChIndex, 0)->setIcon(QPixmap("./images/analog.png"));
				}
				else if (pCh->m_nHasMapType == 2)
				{
						item(nChIndex, 0)->setIcon(QPixmap("./images/digital.png"));
				}
				else if (pCh->m_nHasMapType == 4)
				{
						item(nChIndex, 0)->setIcon(QPixmap("./images/mix.png"));
				}
			}
			}
			else
			{
				if (m_pArrUI[nChIndex].Ramp[0].nIndex == 1 || m_pArrUI[nChIndex].Ramp[1].nIndex == 1 || m_pArrUI[nChIndex].Ramp[2].nIndex == 1)
				{
					pCurrItem->setIcon(QPixmap("./images/gradual.png"));
				}
				else
				{
					if (pCh->m_nHasMapType == 1)
					{
						item(nChIndex, 0)->setIcon(QPixmap("./images/A.png"));
				}
				else if (pCh->m_nHasMapType == 2)
				{
						item(nChIndex, 0)->setIcon(QPixmap("./images/D.png"));
				}
				else if (pCh->m_nHasMapType == 4)
				{
						item(nChIndex, 0)->setIcon(QPixmap("./images/A+D.png"));
					}
				}


			}
#else
				if(xlang_IsCurrXLanguageChinese())
				{
				if (m_pArrUI[nChIndex].Ramp[0].nIndex == 1 || m_pArrUI[nChIndex].Ramp[1].nIndex == 1 || m_pArrUI[nChIndex].Ramp[2].nIndex == 1)
				{
					item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/gradual.png"));
				}
				else
				{
// 						if (g_oSystemParas.m_nHasAnalog && !g_oSystemParas.m_nHasDigital)
// 						{
// 							item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/analog.png"));
// 						}
// 						else if (!g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 						{
// 							item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/digital.png"));
// 						}
// 						else if (g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 						{
// 							item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/mix.png"));
// 						}

						if (pCh->m_nHasMapType == 1)
					{
						item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/analog.png"));
					}
						else if (pCh->m_nHasMapType == 2)
					{
						item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/digital.png"));
					}
						else if (pCh->m_nHasMapType == 4)
					{
						item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/mix.png"));
					}

				}
				}
				else
				{
					if (m_pArrUI[nChIndex].Ramp[0].nIndex == 1 || m_pArrUI[nChIndex].Ramp[1].nIndex == 1 || m_pArrUI[nChIndex].Ramp[2].nIndex == 1)
					{
						item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/gradual.png"));
					}
					else
					{
// 						if (g_oSystemParas.m_nHasAnalog && !g_oSystemParas.m_nHasDigital)
// 						{
// 							item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/A.png"));
// 						}
// 						else if (!g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 						{
// 							item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/D.png"));
// 						}
// 						else if (g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 						{
// 							item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/A+D.png"));
// 						}

						if (pCh->m_nHasMapType == 1)
						{
							item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/A.png"));
						}
						else if (pCh->m_nHasMapType == 2)
						{
							item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/D.png"));
						}
						else if (pCh->m_nHasMapType == 4)
						{
							item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/A+D.png"));
						}
					}
				}

				
#endif
		}

		nChIndex++;
	}

	changeTableColor();
	if((m_MacroType == MACROTYPE_ManualLineVol)&&(nChIndex != 0))//20230821 gyp 线电压的电压个数为两个一组，电流为三个一组
	{	
		QTableWidget *pTableWidget =(nChIndex,3,this);
		long nGroupIndex = nChIndex/3;
		long nGroupVIndex = nChIndex/2;
		long Index=(nGroupVIndex-nGroupIndex)*2;	
		
		if (m_pChDatas->GetCount() > 0)//20240606 suyang 当通道为0时会导致崩溃
		{
			if (m_pChDatas->GetCount()==4)
			{
				changeTableColor_LineVol();//20230821 gyp 线电压的颜色为两个为一组	

				if (nChIndex==3)
				{
					pTableWidget->removeRow(nChIndex-1);	
				}	
			}
			else if (pCh->m_strID.contains(tr("U")))
			{		
				changeTableColor_LineVol();//20230821 gyp 线电压的颜色为两个为一组	
				while(Index>=0)
				{
					pTableWidget->removeRow(nChIndex);
					Index--;
					nChIndex--;
					if (nChIndex==11||nChIndex==3)//防止误删除电压的行数
					{
						break;
					}
				}				
			}

		}
				
	}	
	if(m_MacroType == MACROTYPE_RemoteMeas)
	{
		changeTableColor_RemoteMeas();
		QTableWidget *pTableWidget =(nChIndex,3,this);
		while(nChIndex>=4)
		{
			pTableWidget->removeRow(nChIndex);
			nChIndex--;
		}
	}
}

bool QChannelTable::HasHarmParaset()
{
	if (m_MacroType == MACROTYPE_ManualSequence)
		return false;

	if (m_MacroType == MACROTYPE_ManualLineVol)
		return false;

	if (m_MacroType == MACROTYPE_ManualPower)
		return false;

	if (m_MacroType == MACROTYPE_ManualHarm)
		return true;

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

void QChannelTable::UpdateText(const QString &strText)
{
	if (m_pCurrKeyboardItem == NULL)
	{
		return;
	}

	long nRow = m_pCurrKeyboardItem->row();
	long nCol = m_pCurrKeyboardItem->column();
	 m_pCurrKeyboardItem->setText(strText);
	 slot_OnCellChanged(nRow,nCol);
	 emit sig_ChannelValueChanged(m_moudleType,nRow,nCol, m_pCurrKeyboardItem->text().toFloat());//valueFlag=（1:幅值 2:相位 3:频率）
}

bool QChannelTable::IsBaseHarmAddValid(int row,int col,float fv)
{
	ASSERT(!m_bDCTest);
	ASSERT( row>=0 && row<=rowCount()-1 && col==1);

	bool bRet = true;

	float fTotal = fv*fv; 

	if ((m_MacroType == MACROTYPE_ManualHarm)||(m_MacroType == MACROTYPE_ManualSequence)||(m_MacroType == MACROTYPE_ManualLineVol))
	{
		fTotal += m_pArrUI[row].Harm[1].fAmp*m_pArrUI[row].Harm[1].fAmp;
	}
	else
	{
		for(int i=2;i<MAX_HARM_COUNT;i++)
		{
			if (m_pArrUI[row].Harm[i].m_bSelect)
			{
				fTotal += m_pArrUI[row].Harm[i].fAmp*m_pArrUI[row].Harm[i].fAmp;
			}
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

void QChannelTable::slot_UpdataVamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActUEqualAmpClicked();
}

void QChannelTable::slot_UpdataIamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActIqualAmpClicked();
}

void QChannelTable::slot_UpdataHzamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActHzEqualClicked();
}

void QChannelTable::slot_UpdataZX(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActPhasePClicked();
}

void QChannelTable::slot_UpdataFX(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActPhaseNClicked();
}

void QChannelTable::slot_UpdataLX()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText("0");
	slot_ActPhaseZClicked();
}

void QChannelTable::slot_OnItemDoubleClicked(QTableWidgetItem *pItem)
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

	if (nCol == 1)
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
	else if (nCol == 2)
	{
		nEditType = 2;
	}
	else if (nCol == 3)
	{
		nEditType = 3;
	}
	
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::Attach330Channel(this, nEditType);
#endif
		
	m_pCurrKeyboardItem = pItem;
}

void QChannelTable::slot_OnCellChanged(int row,int col)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);
	QString str = pItem->text();
	QString strInfo;
	float fv;
	QString strText;
	bool bChg = false;

	FloatTempChData *pTempChData = m_oTempSaveDataMap.value(row);

	if (m_MacroType == MACROTYPE_ManualPower)
	{
		m_fAmpMax = m_fMultAmpMax[row];
		m_fAmpMin = m_fMultAmpMin[row];
	}

	switch (col)
	{
	case 1:
		{
			fv = str.toFloat();

			if ((m_bDC) && ((m_MacroType != MACROTYPE_ManualHarm) && (m_MacroType != MACROTYPE_ManualSequence) && (m_MacroType != MACROTYPE_ManualLineVol) && (m_MacroType != MACROTYPE_ManualPower)))
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
				
					if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
					{
						CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("输入值%f(%d,%d)超出范围(%f)."),fv,row,col,m_fAmpMax);
					}
					else
					{
						CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("The input value %f(%d,%d)is out of range(%f)."),fv,row,col,m_fAmpMax);
					}
				}
				else if (fv<m_fAmpMin)
				{
					fv = m_fAmpMin;

					if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
					{
						CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("输入值%f(%d,%d)超出范围(%f)."),fv,row,col,m_fAmpMin);
					}
					else
					{
						CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("The input value %f(%d,%d)is out of range(%f)."),fv,row,col,m_fAmpMin);
					}
				}
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
			else
			{	
				if (isPosiDigitstr(str))
				{	
					QTableWidgetItem  *pTableWidgetItem  = this->item(row,col-1);
					QString strText = pTableWidgetItem->text();
					if (m_MacroType ==MACROTYPE_ManualLineVol&&m_moudleType == Moudle_U)//线电压的电压为最大值的√3
					{
						str = initMaxAcV_LineVol(str);
						fv = str.toFloat();
					}
					else if ((m_MacroType == MACROTYPE_RemoteMeas || m_MacroType == MACROTYPE_Manual || m_MacroType == MACROTYPE_State)&& (g_oSystemParas.m_nHasWeek))//UO/I0限制处理 弱信号，UO 0-7.8/3，I0 0-4
					{
						str = initMaxAmp_RemoteMeas(m_moudleType,str,strText);
						fv = str.toFloat();
					}
					else 
					{
					str = initMaxAcV(str);
					fv = str.toFloat();
					}
			
					//判断是否有谐波设置，再调用下面的函数判断
					if(HasHarmParaset() && !IsBaseHarmAddValid(row,col,fv))
					{
						if (m_moudleType == Moudle_U)
						{
							if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
							{
								CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("基波设置值%f(%d,%d)与谐波的叠加超出范围(%fV)."),fv,row,col,g_oLocalSysPara.m_fAC_VolMax);
							}
							else
							{
								CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("The Superposition of fundamental wave value %f(%d,%d)and Harmonic settin value(%fV)is out of range."),fv,row,col,g_oLocalSysPara.m_fAC_VolMax);
							}
						}
						else
						{
							if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
							{
								CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("基波设置值%f(%d,%d)与谐波的叠加超出范围(%fA)."),fv,row,col,g_oLocalSysPara.m_fAC_CurMax);
							}
							else
							{
								CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("The Superposition of fundamental wave value %f(%d,%d)and Harmonic settin value(%fA)is out of range."),fv,row,col,g_oLocalSysPara.m_fAC_CurMax);
							}
						}

						fv = m_pArrUI[row].Harm[GetHarmIndex()].fAmp;
					}

					pItem->setText(QString::number(fv,'f',3));
				}
				else
				{
					if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
					{
						CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("输入值含有非法字符."));
					}
					else
					{
						CLogPrint::LogString(XLOGLEVEL_RESULT,_T("The input value contains illegal characters."));
					}
	
					fv = m_pArrUI[row].Harm[GetHarmIndex()].fAmp;

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

			if(m_pArrUI[row].Harm[GetHarmIndex()].fAmp != fv)
			{
				m_pArrUI[row].Harm[GetHarmIndex()].fAmp = fv;
				bChg = true;
			}
		}
		break;
	case 2:
		{
//			QMessageBox::information(NULL,"标题",str, QMessageBox::Yes, QMessageBox::Yes);
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

			if ((m_bDC) && (m_MacroType != MACROTYPE_ManualHarm) && (m_MacroType != MACROTYPE_ManualSequence) && (m_MacroType != MACROTYPE_ManualLineVol) && (m_MacroType != MACROTYPE_ManualPower))//zhouhj 20211031 在直流的模式下,相位固定为0
			{
				strText.setNum((float)0,'f',1);
				pItem->setText(strText);

				if(m_pArrUI[row].Harm[1].fAngle != 0)
				{
					m_pArrUI[row].Harm[1].fAngle = 0;
					bChg = true;
				}
			}
			else
			{
				strText.setNum(fv,'f',1);
				pItem->setText(strText);
				pTempChData->fAngle = fv;

				if(m_pArrUI[row].Harm[GetHarmIndex()].fAngle != fv)
				{
					m_pArrUI[row].Harm[GetHarmIndex()].fAngle = fv;
					bChg = true;
				}
			}
		}
		break;
	case 3:
		{
			  if ((m_MacroType == MACROTYPE_ManualHarm) || (m_MacroType == MACROTYPE_ManualSequence) || (m_MacroType == MACROTYPE_ManualLineVol) || (m_MacroType == MACROTYPE_ManualPower))
			{
				break;
			}

			if (isPosiDigitstr(str))
			{
				str = initMaxHz(str);
				fv = str.toFloat();

				//2024-8-1 wuxinyi 由于上面判断类型已经break，无需再判断故此注释
				//修改通用试验 选择直流时频率需变为0
				if ((m_bDC) && /*(m_MacroType != MACROTYPE_ManualHarm) && (m_MacroType != MACROTYPE_ManualSequence) && ((m_MacroType == MACROTYPE_ManualLineVol) ||*/ (m_MacroType == MACROTYPE_Manual)/*)*/)
				{
					fv = 0;
				}
				else
				{
					if (fv < 1 && m_MacroType == MACROTYPE_State)  // 20240507 xueyangfan 限制状态序列最小频率为1Hz
					{
						fv = 1;
					}
					else if(fv < 0.001)
					{
						fv = 0;
					}
				}
				
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
			else
			{
				fv = m_pArrUI[row].Harm[GetHarmIndex()].fFreq;
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}

			if(m_pArrUI[row].Harm[GetHarmIndex()].fFreq != fv)
			{
				m_pArrUI[row].Harm[GetHarmIndex()].fFreq = fv;
				pTempChData->fHz = fv;
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

void QChannelTable::slot_TableShowMent(QPoint pos)
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
			  if ((m_MacroType != MACROTYPE_ManualHarm) && (m_MacroType != MACROTYPE_ManualSequence) && (m_MacroType != MACROTYPE_ManualLineVol) && (m_MacroType != MACROTYPE_ManualPower))
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

void QChannelTable::creatTableMenu()
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

			xlang_SetLangStrToAction(m_ActUEqualAmp,"Native_EqualAmp");
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
			m_ActUAmpED = new QAction(tr("额定相电压"),this);
			m_ActUZero = new QAction(tr("零"),this);
			m_ActUEqualAmp = new QAction(tr("等幅值"),this);

			xlang_SetLangStrToAction(m_ActUAmpED,"Native_EDPhaseV");
			xlang_SetLangStrToAction(m_ActUZero,"Native_Zero");
			xlang_SetLangStrToAction(m_ActUEqualAmp,"Native_EqualAmp");

			connect (m_ActUAmpED,SIGNAL(triggered()),this,SLOT(slot_ActUAmpEDClicked())); 
			connect (m_ActUZero,SIGNAL(triggered()),this,SLOT(slot_ActUZeroClicked()));
			connect (m_ActUEqualAmp,SIGNAL(triggered()),this,SLOT(slot_ActUEqualAmpClicked())); 
			m_MenuAmp->addAction(m_ActUAmpED); 
			m_MenuAmp->addAction(m_ActUZero);
			m_MenuAmp->addAction(m_ActUEqualAmp);

			QAction* pActUAmpED20 = new QAction(tr("20%额定相电压"),this);
			QAction* pActUAmpED40 = new QAction(tr("40%额定相电压"),this);
			QAction* pActUAmpED60 = new QAction(tr("60%额定相电压"),this);
			QAction* pActUAmpED80 = new QAction(tr("80%额定相电压"),this);
			QAction* pActUAmpED120 = new QAction(tr("120%额定相电压"),this);
			CString strEDPhaseV;
			xlang_GetLangStrByFile(strEDPhaseV, "Native_EDPhaseV");
			pActUAmpED20->setText("20%" + strEDPhaseV);
			pActUAmpED40->setText("40%" + strEDPhaseV);
			pActUAmpED60->setText("60%" + strEDPhaseV);
			pActUAmpED80->setText("80%" + strEDPhaseV);
			pActUAmpED120->setText("120%" + strEDPhaseV);
			connect (pActUAmpED20,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
			connect (pActUAmpED40,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
			connect (pActUAmpED60,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
			connect (pActUAmpED80,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
			connect (pActUAmpED120,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
			m_MenuAmp->addAction(pActUAmpED20); 
			m_MenuAmp->addAction(pActUAmpED40); 
			m_MenuAmp->addAction(pActUAmpED60); 
			m_MenuAmp->addAction(pActUAmpED80); 
			m_MenuAmp->addAction(pActUAmpED120); 
		}
		
	}
	else//电流模块
	{
		if (g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
		{
			m_ActIqualAmp = new QAction(tr("等幅值"),this);
			m_ActIAmpED = new QAction(tr("额定电流"),this);
			m_pActIAmpED1 = new QAction(tr("1%额定电流"),this);
			m_pActIAmpED5 = new QAction(tr("5%额定电流"),this);
			m_pActIAmpED20 = new QAction(tr("20%额定电流"),this);
			m_pActIAmpED100 = new QAction(tr("100%额定电流"),this);
			m_pActIAmpED120 = new QAction(tr("120%额定电流"),this);

			xlang_SetLangStrToAction(m_ActIqualAmp,"Native_EqualAmp");
			xlang_SetLangStrToAction(m_ActIAmpED,"Native_EDCurrent");

			CString strEDPhaseA;
			xlang_GetLangStrByFile(strEDPhaseA, "Native_EDCurrent");
	
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
			m_ActIAmp0 = new QAction(tr("零"),this);
			m_ActIqualAmp = new QAction(tr("等幅值"),this);
			m_ActIAmpED = new QAction(tr("额定电流"),this);

			xlang_SetLangStrToAction(m_ActIAmp0,"Native_Zero");
			xlang_SetLangStrToAction(m_ActIqualAmp,"Native_EqualAmp");
			xlang_SetLangStrToAction(m_ActIAmpED,"Native_EDCurrent");

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

			QAction* pActIAmpED20 = new QAction(tr("20%额定电流"),this);
			QAction* pActIAmpED40 = new QAction(tr("40%额定电流"),this);
			QAction* pActIAmpED60 = new QAction(tr("60%额定电流"),this);
			QAction* pActIAmpED80 = new QAction(tr("80%额定电流"),this);
			QAction* pActIAmpED120 = new QAction(tr("120%额定电流"),this);
			CString strEDPhaseA;
			xlang_GetLangStrByFile(strEDPhaseA, "Native_EDCurrent");
			pActIAmpED20->setText("20%" + strEDPhaseA);
			pActIAmpED40->setText("40%" + strEDPhaseA);
			pActIAmpED60->setText("60%" + strEDPhaseA);
			pActIAmpED80->setText("80%" + strEDPhaseA);
			pActIAmpED120->setText("120%" + strEDPhaseA);
			connect (pActIAmpED20,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
			connect (pActIAmpED40,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
			connect (pActIAmpED60,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
			connect (pActIAmpED80,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
			connect (pActIAmpED120,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
			m_MenuAmp->addAction(pActIAmpED20); 
			m_MenuAmp->addAction(pActIAmpED40); 
			m_MenuAmp->addAction(pActIAmpED60); 
		        m_MenuAmp->addAction(pActIAmpED80); 
		        m_MenuAmp->addAction(pActIAmpED120); 
	   }
	
	}
	if (m_MacroType !=MACROTYPE_ManualLineVol)
	{
	QAction *m_ActUPhaseP = new QAction(tr("正序"),this);
	QAction *m_ActUPhaseN = new QAction(tr("负序"),this);
	QAction *m_ActUPhaseZ = new QAction(tr("零序"),this);

	xlang_SetLangStrToAction(m_ActUPhaseP,"Native_PositiveSeq");
	xlang_SetLangStrToAction(m_ActUPhaseN,"Native_NegativeSeq");
	xlang_SetLangStrToAction(m_ActUPhaseZ,"Native_ZeroSeq");

	connect (m_ActUPhaseP,SIGNAL(triggered()),this,SLOT(slot_ActPhasePClicked())); 
	connect (m_ActUPhaseN,SIGNAL(triggered()),this,SLOT(slot_ActPhaseNClicked()));
	connect (m_ActUPhaseZ,SIGNAL(triggered()),this,SLOT(slot_ActPhaseZClicked())); 
	m_MenuPhase->addAction(m_ActUPhaseP);
	m_MenuPhase->addAction(m_ActUPhaseN); 
	m_MenuPhase->addAction(m_ActUPhaseZ); 
	}

	if ((m_MacroType != MACROTYPE_ManualHarm) && (m_MacroType != MACROTYPE_ManualHarm) && (m_MacroType != MACROTYPE_ManualPower))
	{
		QAction *m_ActIHz50 = new QAction(tr("50Hz"),this);
		QAction *m_ActIHz60 = new QAction(tr("60Hz"),this);
		QAction *m_ActIHzEqual = new QAction(tr("等频率"),this);
		xlang_SetLangStrToAction(m_ActIHzEqual,"Native_EqualFreq");

		connect (m_ActIHz50,SIGNAL(triggered()),this,SLOT(slot_ActHz50Clicked())); 
		connect (m_ActIHz60,SIGNAL(triggered()),this,SLOT(slot_ActHz60Clicked()));
		connect (m_ActIHzEqual,SIGNAL(triggered()),this,SLOT(slot_ActHzEqualClicked()));
		m_MenuFre->addAction(m_ActIHz50);
		m_MenuFre->addAction(m_ActIHz60); 
		m_MenuFre->addAction(m_ActIHzEqual); 
	}

	connect(this, SIGNAL(customContextMenuRequested ( const QPoint & )), this, SLOT(slot_TableShowMent(QPoint)));
}

void QChannelTable::Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll, long nCol)
{
	if (pItem == NULL)
	{
		return;
	}
	//2024-8-19 wuxinyi 修改偶发修改参数不下发
	m_pCurrKeyboardItem = pItem;

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
			item(i,nCol)->setText(strVal);
		}
	}
	else if(m_MacroType == MACROTYPE_ManualLineVol && m_moudleType==Moudle_U)
	{
		int row = pItem->row();
		int imin = (int(row/2))*2;
		int imax = (int(row/2))*2 +1;
		if (imax>=rowCount())
		{
			imax = rowCount()-1;
		}
		for (int i=imin; i<=imax;i++)
		{
			item(i,nCol)->setText(strVal);
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
			item(i,nCol)->setText(strVal);
		}
	}
}

void QChannelTable::slot_ActUAmpEDClicked()
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
	Act_setUIAmpValue(pItem,m_fEDVal / SQRT3,FALSE);
	}
}

void QChannelTable::slot_ActPerUAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	float fEDVal;
	if (g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)
	{	
		int nRow = currentRow();
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
		fEDVal = m_fEDVal / SQRT3;
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

void QChannelTable::slot_ActUZeroClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem)
	{
		pItem->setText(QString::number(0,'f',3));
	}
}

void QChannelTable::slot_ActUEqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void QChannelTable::slot_ActIAmp1Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem)
	{
		pItem->setText(QString::number(1,'f',3));
	}
}

void QChannelTable::slot_ActIAmp5Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem)
	{
		pItem->setText(QString::number(5,'f',3));
	}
}

void QChannelTable::slot_ActIAmp0Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem)
	{
		pItem->setText(QString::number(0,'f',3));
	}
}

void QChannelTable::slot_ActIqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void QChannelTable::slot_ActIAmpEDClicked()
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

void QChannelTable::slot_ActPerIAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	float fEDVal ;
	int nRow = currentRow();
	//2024-8-21 wuxinyi 仅限PDU100第四条通道使用零序电流额定值
	if ((nRow == 3) && (g_oSttSystemConfig.GetDevModel().Find(_T("PDU100")) >= 0)) //代表零序
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

void QChannelTable::Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol)
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
			item(nOffset+1,nCol)->setText(QString::number(fVal1,'f',1));
			item(nOffset+2,nCol)->setText(QString::number(fVal2,'f',1));
		}
		else if ((nOffset+1)<nMaxCount)
		{
			item(nOffset+1,nCol)->setText(QString::number(fVal1,'f',1));
		}
		
		break;
	case 1:
		fVal1 = fv+120;
		fVal2 = fv+240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		item(nOffset,nCol)->setText(QString::number(fVal1,'f',1));

		if ((nOffset+2)<nMaxCount)
		{
			item(nOffset+2,nCol)->setText(QString::number(fVal2,'f',1));
		}

		break;
	case 2:
		fVal1 = fv-120;
		fVal2 = fv-240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		item(nOffset,nCol)->setText(QString::number(fVal1,'f',1));
		item(nOffset+1,nCol)->setText(QString::number(fVal2,'f',1));
		break;
	default:
		break;
	}
}

void QChannelTable::Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol)
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
			item(nOffset+1,nCol)->setText(QString::number(fVal1,'f',1));
			item(nOffset+2,nCol)->setText(QString::number(fVal2,'f',1));
		}
		else if ((nOffset+1)<nMaxCount)
		{
			item(nOffset+1,nCol)->setText(QString::number(fVal1,'f',1));
		}

		break;
	case 1:
		fVal1 = fv-120;
		fVal2 = fv-240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		item(nOffset,nCol)->setText(QString::number(fVal1,'f',1));

		if ((nOffset+2)<nMaxCount)
		{
			item(nOffset+2,nCol)->setText(QString::number(fVal2,'f',1));
		}

		break;
	case 2:
		fVal1 = fv+120;
		fVal2 = fv+240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		item(nOffset,nCol)->setText(QString::number(fVal1,'f',1));
		item(nOffset+1,nCol)->setText(QString::number(fVal2,'f',1));
		break;
	default:
		break;
	}
}

void QChannelTable::slot_ActPhasePClicked()
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
		else
		{
			int imin = (int(row/3))*3;
			Act_setPrasePValue(row%3,imin,fv);
		}
	}
	else				//电流模块
	{
		int imin = (int(row/3))*3;
		Act_setPrasePValue(row%3,imin,fv);
	}
}

void QChannelTable::slot_ActPhaseNClicked()
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
		else
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

void QChannelTable::Act_setPraseZValue(int nStart,int nEnd, long nCol)
{
	QString strVal = QString::number(0,'f',1);
	long nMaxCount = rowCount();

	if (nEnd>=nMaxCount)
	{
		nEnd = (nMaxCount-1);
	}

	for (int i=nStart; i<=nEnd; i++)
	{
		item(i,nCol)->setText(strVal);
	}
}

void QChannelTable::slot_ActPhaseZClicked()
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
		else
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
void QChannelTable::slot_ActHz50Clicked()
{
	if (!m_bDC)
	{
		QTableWidgetItem *pItem = this->currentItem();
		if (pItem)
		{
			pItem->setText(QString::number(50,'f',3));
		}
	}
}

void QChannelTable::slot_ActHz60Clicked()
{
	if (!m_bDC)
	{
		QTableWidgetItem *pItem = this->currentItem();
		if (pItem)
		{
			pItem->setText(QString::number(60,'f',3));
		}
	}	
}

void QChannelTable::Act_setHzEqualValue(int nStart,int nEnd,float fv, long nCol)
{
	QString strVal = QString::number(fv,'f',3);

	for (int i=nStart; i<=nEnd; i++)
	{
		if(i>m_pChDatas->GetCount()-1)
		{
			break;
		}

		item(i,nCol)->setText(strVal);
	}
}

void QChannelTable::slot_ActHzEqualClicked()
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

QString QChannelTable::initMaxAcV(QString str)
{
	if (str.toFloat()- m_fAmpMax > 0)
	{
		if(CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
			//20240123 suyang  把 XLOGLEVEL_ERROR改为XLOGLEVEL_RESULT
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,"输入值%f超出范围(%f).",str.toFloat(),m_fAmpMax);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("The input value %f is out of range(%f)."),str.toFloat(),m_fAmpMax);
		}

		return QString("%1").arg(m_fAmpMax);
	}
	else
	{
		return str;
	}
}

QString QChannelTable::initMaxAcV_LineVol(QString str)
{
	if (str.toFloat()- m_fAmpMax*SQRT3 > 0)
	{
		if(CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,"输入值%f超出范围(%f).",str.toFloat(),m_fAmpMax*SQRT3);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("The input value %f is out of range(%f)."),str.toFloat(),m_fAmpMax*SQRT3);
		}

		return QString("%1").arg(m_fAmpMax*SQRT3);
	}	
	else
	{
		return str;
	}
}

QString QChannelTable::initMaxAcI(QString str)
{
	if (str.toFloat()- m_fAmpMax > 0)
	{
		if(CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("输入值%f超出范围(%f)."),str.toFloat(),m_fAmpMax);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("The input value %f is out of range(%f)."),str.toFloat(),m_fAmpMax);
		}

		return QString("%1").arg(m_fAmpMax);
	}
	else
	{
		return str;
	}
}

QString QChannelTable::initMaxHz(QString str)
{
	g_oLocalSysPara.m_fAC_VolMax;
	if (str.toFloat()- Global_GetMaxFreq() > 0)
	{
		if(CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
//			int nMaxHz = MAXHZ;
//			CString strInfo = CString("输入值") + str + CString("超出范围(") + QString::number(nMaxHz, 'd') + ")";
//			CLogPrint::LogString(XLOGLEVEL_ERROR,strInfo);
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("输入值%f超出范围(%d)."),str.toFloat(),Global_GetMaxFreq());
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("The input value %f is out of range(%d)."),str.toFloat(),Global_GetMaxFreq());
		}

		return QString("%1").arg(Global_GetMaxFreq());
	}
	else
	{
		return str;
	}
}

void QChannelTable::UpdateValidTableDatas()
{
	for (int i=0;i<rowCount();i++)
	{
		for (int j=0;j<columnCount();j++)
		{
			slot_OnCellChanged(i,j);
		}
	}
}

//#ifndef _PSX_QT_WINDOWS_
bool QChannelTable::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}

	return QScrollTableWidget::eventFilter(obj,event);

}

void QChannelTable::mousePressEvent(QMouseEvent * event)
{
	//2024-8-10 wuxinyi 右键出现菜单栏
#ifdef  _PSX_QT_WINDOWS_
	if (event->button() == Qt::RightButton)
	{
		QModelIndex index = indexAt(event->pos());

		if (index.isValid()) {
			// 设置单元格为当前选择项，确保右键点击时单元格获得焦点
			setCurrentCell(index.row(), index.column());

		}

		QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonRelease, event->pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
		QApplication::postEvent(this, pEvent);
		return;
	}

#endif //  _PSX_QT_WINDOWS_

	//2024-9-29 wuxinyi 单元格添加定值关联之后设置不可编辑
	QModelIndex index = indexAt(event->pos());
	int row = index.row();
	int column = index.column();
	QTableWidgetItem *pItem = item(row, column);

	if (pItem)
	{	
		if (IsAttachSettingItem(pItem))
		{
			// 使单元格不可编辑
			pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable); // 移除可编辑标志
		}
		else
		{
			pItem->setFlags(pItem->flags() | Qt::ItemIsEditable); // 添加可编辑标志
		}
	}


	if (m_bRunning)
	{
		QScrollTableWidget::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QScrollTableWidget::mousePressEvent(event);
}

BOOL QChannelTable::IsAttachSettingItem(QTableWidgetItem *pObject)
{
	QSettingItem* pItem = dynamic_cast<QSettingItem*>(pObject);

	if (pItem == NULL)
		return FALSE;

	if (pItem->inherits(STT_SETTING_ITEM_ClassID/*"QGV_HLITEM"*/))
	{
		if (((QSettingItem*)pItem)->IsSetting())
		{
			return TRUE;
		}
	}
	return FALSE;

}

//#endif

QString QChannelTable::initMaxAmp_RemoteMeas( MOUDLEType moudleType,QString str ,QString strCellText)
{
	//零序电压8.3,零序电流4.2
	float fMaxAmp = 0;
	float fMaxAmp_U = 8.3; 
	float fMaxAmp_I = 4.2;

	if (moudleType == Moudle_U)
	{
		if (strCellText == _T("U0"))
		{
			fMaxAmp_U = 8.3;
		}
		else
		{
			fMaxAmp_U = 4.2;
		}

		fMaxAmp = fMaxAmp_U;
	}
	else if (moudleType == Moudle_I)
	{
		if (strCellText == _T("I0"))
		{
			fMaxAmp_I = 4.2;
		}
		else
		{
			fMaxAmp_I = 21;
		}
		fMaxAmp = fMaxAmp_I;
	}

	if (str.toFloat()- fMaxAmp> 0)
	{
		if(CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,"输入值%f超出范围(%f).",str.toFloat(),fMaxAmp);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("The input value %f is out of range(%f)."),str.toFloat(),fMaxAmp);
		}

		return QString("%1").arg(fMaxAmp);
	}	
	else
	{
		return str;
	}
}

int QChannelTable::getChIndexByChName( const CString & strChName )
{
	QList<QTableWidgetItem *> items = this->findItems(strChName, Qt::MatchContains);

	if (!items.isEmpty()) 
	{
		int row = items.at(0)->row();
		return row;
	}

	return -1;
}
