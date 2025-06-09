#include "channelpowertable.h"
#include <QFontMetrics>
#include <QScrollBar>
#include <cmath>
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../SttTestSysGlobalPara.h"
#include "../../../Module/API/MathApi.h"
#include "../../../SttSystemConfig/SttSystemConfig.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

//#define GenHao3	1.7320508 //根号三
#include <QDesktopWidget>
#include <QApplication>


QChannelPowerTable::QChannelPowerTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_ChannelPower *pArrPOW,QWidget *parent)
	: QScrollTableWidget(parent)
{
	m_pnHarmIndex = NULL;
	m_pChDatas = pChList;
	m_MacroType = 0;
	m_moudleType = moudleType;
	m_pArrPOW = pArrPOW;
	m_bDC = false;
	m_ColorList<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181)<<QColor(168,169,171)<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181);

	m_fAmpMax = 120;
	m_fAmpMin = 0;
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
	for (int i = 0; i < MAX_VOLTAGE_COUNT; i++)
	{
		m_fMultVolAmp[i] = g_oLocalSysPara.m_fAC_VolMax;
	}
	init();
}

QChannelPowerTable::~QChannelPowerTable()
{

}

void QChannelPowerTable::setTableData(tmt_ChannelPower *pArrPOW)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	disconnect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)));

	m_pArrPOW = pArrPOW;
	UpdateTable();

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)),Qt::UniqueConnection);
}

void QChannelPowerTable::setHarmIndex(int *pnHarmIndex)
{
	m_pnHarmIndex = pnHarmIndex;
}

int QChannelPowerTable::GetHarmIndex()
{
		return 1;
}

void QChannelPowerTable::setProperty(bool bDC)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	disconnect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)));
	m_bDC = bDC;


		setColumnHidden(2, false);
		setColumnHidden(3, false);

		for (int i=0;i<rowCount();i++)
		{
			item(i,2)->setFlags(item(i,1)->flags());
			item(i,2)->setBackground(item(i,1)->background());
            item(i,2)->setText(QString::number(m_pArrPOW[i].m_fQpower,'f',3));
	}
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)),Qt::UniqueConnection);
}

void QChannelPowerTable::setItemValue(int row,int col,float fv)
{
	if (row<rowCount()&&col<columnCount())
	{
		if (col>0&&col<columnCount())
		{
			if (col==2)
			{
				item(row,col)->setText(QString::number(fv,'f',3));
			}
			else
			{
				item(row,col)->setText(QString::number(fv,'f',3));
			}
		}
	}
}

float QChannelPowerTable::getItemValue(int row,int col)
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

void QChannelPowerTable::setVolAmpValue(float fVolAmp[])
{
	for (int i = 0; i < MAX_VOLTAGE_COUNT; i++)
	{
		m_fMultVolAmp[i] = fVolAmp[i];
	}
}

void QChannelPowerTable::setAmpEDValue(float fEDValue)
{
	m_fEDVal = fEDValue;
}

void QChannelPowerTable::setColumnWidthByNum(int col,int width)
{
	setColumnWidth(col,width);
}

void QChannelPowerTable::setTableFixWidgt(int width)
{
	this->setFixedWidth(width);
}

int QChannelPowerTable::getTableHeight()
{
	return this->height();
}

int QChannelPowerTable::getTableWidth()
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

void QChannelPowerTable::init()
{
	setFocusPolicy(Qt::NoFocus);
	setContextMenuPolicy (Qt::CustomContextMenu);

	QHeaderView* pLeft = this->verticalHeader();
	pLeft->setDefaultSectionSize(25);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
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

void QChannelPowerTable::initTable()
{
	ASSERT(m_pChDatas);

	setRowCount(4);//加一行总功率
	setColumnCount(4);//功率界面没有频率

	QStringList headers;

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

		this->setColumnWidth(3,nLabelWidth4);
		//headers << strChannel << strAmplitude << strPhase << strFreq;
		headers << strChannel << /*"有功(W)"*/g_sLangTxt_Power_Active << /*"无功(Var)"*/g_sLangTxt_Power_Reactive << /*"功率因数"*/g_sLangTxt_PowerFactor;
	
	setHorizontalHeaderLabels(headers);
	setIconSize(QSize(20,20));

	for (int row=0;row<this->rowCount();row++)
	{
		for (int col=0;col<this->columnCount();col++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			
			if (col == 0 || col == 3 ||row == 3)//通道、功率因数、总功率不可选中更改
			{
					item->setFlags(Qt::NoItemFlags);
				item->setTextColor(QColor(0, 0, 0));
			}
			setItem(row,col,item);
			setRowHeight(row,m_nRowHeight);
		}
	}
    item(3,0)->setText("S");
	item(3,3)->setText("-");//总功率没有功率因数
	int ntableHight = this->horizontalHeader()->height() + ((m_nRowHeight)*this->rowCount());
	
	//setFixedHeight(ntableHight);
	//creatTableMenu();wangtao 20240612 暂时取消右键弹出提示
}

void QChannelPowerTable::changeTableColor()
{
	ASSERT(m_pChDatas);

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


void QChannelPowerTable::UpdateTable()
{
	ASSERT(m_pChDatas);

	POS pos = m_pChDatas->GetHeadPosition();
	//CExBaseObject *pCh = NULL;
	CSttChResource *pCh = NULL;//20240528 suyang 采用CSttChResource 类根据m_nHasMapType来显示
	long nChIndex = 0;
	QTableWidgetItem *pCurrItem = NULL;
	QTableWidgetItem *pTableWidgetItem = NULL;
	CString strChName;
    int nPowerNameCount = 0;
	while(pos)
	{
		pCh = (CSttChResource *)m_pChDatas->GetNext(pos);

		pTableWidgetItem = item(nChIndex,0);

		if (pTableWidgetItem == NULL)
		{
			break;
		}
		else
		{
			//mod wangtao 20240612 为了不受到通道映射影响，在功率这里直接写死通道名称
			switch(nPowerNameCount)
			{
			    case 0:
				   strChName = "Sa";
				   break;

				case 1:
                   strChName = "Sb";
				   break;

				case 2:
				   strChName = "Sc";
				   break;

				default:
				   break;
			}
            nPowerNameCount++;
		}

		pTableWidgetItem->setText(strChName);
		
		//20240204 suyang 增加合并电流输出时 电流通道判断
		//float fAmp = m_pArrPOW[nChIndex].Harm[GetHarmIndex()].fAmp;
        float fAmp = m_pArrPOW[nChIndex].m_fPpower;

		if (fAmp > m_fAmpMax)
		{
			fAmp= m_fAmpMax;
		}

		if (fAmp < m_fAmpMin)
		{
			fAmp = m_fAmpMin;
		}
		if (m_pArrPOW[nChIndex].m_fPpower != fAmp)
		{
			 m_pArrPOW[nChIndex].m_fPpower = fAmp;
		}
		
		QTableWidgetItem *pTableWidgetItem = item(nChIndex, 0);
		CString str = pTableWidgetItem->text();
		
		item(nChIndex,1)->setText(QString::number(m_pArrPOW[nChIndex].m_fPpower,'f',3));

		item(nChIndex,2)->setText(QString::number(m_pArrPOW[nChIndex].m_fQpower,'f',3));

		item(nChIndex,3)->setText(QString::number(m_pArrPOW[nChIndex].m_fFpower,'f',3));

		pCurrItem = item(nChIndex,0);

		if (pCurrItem == NULL)
		{
			nChIndex++;
			continue;
		}
		nChIndex++;
	}

    item(3,1)->setText(QString::number((m_pArrPOW[0].m_fPpower+m_pArrPOW[1].m_fPpower+m_pArrPOW[2].m_fPpower),'f',3));
    item(3,2)->setText(QString::number((m_pArrPOW[0].m_fQpower+m_pArrPOW[1].m_fQpower+m_pArrPOW[2].m_fQpower),'f',3));

	
	changeTableColor();
}

bool QChannelPowerTable::HasHarmParaset()
{
	return false;
}

void QChannelPowerTable::UpdateText(const QString &strText)
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


void QChannelPowerTable::slot_UpdataVamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActUEqualAmpClicked();
}

void QChannelPowerTable::slot_UpdataIamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActIqualAmpClicked();
}

void QChannelPowerTable::slot_UpdataHzamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActHzEqualClicked();
}

void QChannelPowerTable::slot_UpdataZX(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActPhasePClicked();
}

void QChannelPowerTable::slot_UpdataFX(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActPhaseNClicked();
}

void QChannelPowerTable::slot_UpdataLX()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText("0");
	slot_ActPhaseZClicked();
}

void QChannelPowerTable::slot_OnItemDoubleClicked(QTableWidgetItem *pItem)
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
	
//#ifdef _USE_SoftKeyBoard_
//	QSoftKeyBoard::Attach330Channel(this, nEditType);
//#endif
		
	m_pCurrKeyboardItem = pItem;
}

void QChannelPowerTable::slot_OnCellChanged(int row,int col)
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
	case 1:
		{
			fv = str.toFloat();

			float fMaxSpower = m_fMultVolAmp[row] * g_oLocalSysPara.m_fAC_CurMax; //当前通道电压 * 最大电流

			m_fAmpMax = sqrtf(fMaxSpower * fMaxSpower - m_pArrPOW[row].m_fQpower*m_pArrPOW[row].m_fQpower);
			m_fAmpMin = (-1) * sqrtf(fMaxSpower * fMaxSpower - m_pArrPOW[row].m_fQpower*m_pArrPOW[row].m_fQpower);

			if (fv > m_fAmpMax)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_RESULT, "输入值%f大于最大功率(%f)，会导致电流超过最大值(%f).", fv, m_fAmpMax, g_oLocalSysPara.m_fAC_CurMax);
				fv = m_fAmpMax;
			}

			if (fv < m_fAmpMin)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_RESULT, "输入值%f小于最小功率(%f)，会导致电流超过最大值(%f).", fv, m_fAmpMin, g_oLocalSysPara.m_fAC_CurMax);
				fv = m_fAmpMin;
			}

			strText.setNum(fv,'f',3);
			pItem->setText(strText);
			m_pArrPOW[row].m_fPpower = fv;

			pItem  = this->item(3,col);//有功总功率
			if (pItem)
			{
				strText.setNum((m_pArrPOW[0].m_fPpower+m_pArrPOW[1].m_fPpower+m_pArrPOW[2].m_fPpower),'f',3);
				pItem->setText(strText);
			}
	    }
		break;
	case 2:
		{
			fv = str.toFloat();

			float fMaxSpower = m_fMultVolAmp[row] * g_oLocalSysPara.m_fAC_CurMax; //当前通道电压 * 最大电流

			m_fAmpMax = sqrtf(fMaxSpower * fMaxSpower - m_pArrPOW[row].m_fPpower*m_pArrPOW[row].m_fPpower);
			m_fAmpMin = (-1) * sqrtf(fMaxSpower * fMaxSpower - m_pArrPOW[row].m_fPpower*m_pArrPOW[row].m_fPpower);

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
			m_pArrPOW[row].m_fQpower = fv;

			pItem  = this->item(3,col);//无功总功率
			if (pItem)
			{
				strText.setNum((m_pArrPOW[0].m_fQpower+m_pArrPOW[1].m_fQpower+m_pArrPOW[2].m_fQpower),'f',3);
				pItem->setText(strText);
			}
		}
		break;
	default:
		break;
	}

	if ((m_pArrPOW[row].m_fPpower < 1e-7) &&(m_pArrPOW[row].m_fQpower < 1e-7))
	{
		m_pArrPOW[row].m_fFpower = 1;
	}
	else
	{
		m_pArrPOW[row].m_fFpower =fabs(m_pArrPOW[row].m_fPpower)/sqrtf
			((m_pArrPOW[row].m_fPpower*m_pArrPOW[row].m_fPpower)
			+(m_pArrPOW[row].m_fQpower*m_pArrPOW[row].m_fQpower));
	}

	pItem  = this->item(row,3);
	if (pItem)
	{
        strText.setNum(fabs(m_pArrPOW[row].m_fFpower),'f',3);
        pItem->setText(strText);
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
 
 	if (m_pCurrKeyboardItem != NULL /*&& m_MacroType != MACROTYPE_State*/)//20230112 zhouhj  状态序列也更新参数，只更新矢量图
 	{
 		long nRow = m_pCurrKeyboardItem->row();
 		long nCol = m_pCurrKeyboardItem->column();
 		emit sig_ChannelValueChanged(m_moudleType,nRow,nCol, m_pCurrKeyboardItem->text().toFloat());//valueFlag=（1:幅值 2:相位 3:频率）
 	}
}

void QChannelPowerTable::slot_TableShowMent(QPoint pos)
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
			if ((m_MacroType != MACROTYPE_ManualHarm)&&(m_MacroType != MACROTYPE_ManualSequence)&&(m_MacroType != MACROTYPE_ManualLineVol))
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

void QChannelPowerTable::creatTableMenu()
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

	if ((m_MacroType != MACROTYPE_ManualHarm)&&(m_MacroType != MACROTYPE_ManualHarm))
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

void QChannelPowerTable::Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll, long nCol)
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

void QChannelPowerTable::slot_ActUAmpEDClicked()
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

void QChannelPowerTable::slot_ActPerUAmpEDClicked()
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

void QChannelPowerTable::slot_ActUZeroClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem)
	{
		pItem->setText(QString::number(0,'f',3));
	}
}

void QChannelPowerTable::slot_ActUEqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void QChannelPowerTable::slot_ActIAmp1Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem)
	{
		pItem->setText(QString::number(1,'f',3));
	}
}

void QChannelPowerTable::slot_ActIAmp5Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem)
	{
		pItem->setText(QString::number(5,'f',3));
	}
}

void QChannelPowerTable::slot_ActIAmp0Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem)
	{
		pItem->setText(QString::number(0,'f',3));
	}
}

void QChannelPowerTable::slot_ActIqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void QChannelPowerTable::slot_ActIAmpEDClicked()
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

void QChannelPowerTable::slot_ActPerIAmpEDClicked()
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

void QChannelPowerTable::Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol)
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

void QChannelPowerTable::Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol)
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

void QChannelPowerTable::slot_ActPhasePClicked()
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

void QChannelPowerTable::slot_ActPhaseNClicked()
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

void QChannelPowerTable::Act_setPraseZValue(int nStart,int nEnd, long nCol)
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

void QChannelPowerTable::slot_ActPhaseZClicked()
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
void QChannelPowerTable::slot_ActHz50Clicked()
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

void QChannelPowerTable::slot_ActHz60Clicked()
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

void QChannelPowerTable::Act_setHzEqualValue(int nStart,int nEnd,float fv, long nCol)
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

void QChannelPowerTable::slot_ActHzEqualClicked()
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

QString QChannelPowerTable::initMaxAcV(QString str)
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

QString QChannelPowerTable::initMaxAcV_LineVol(QString str)
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

QString QChannelPowerTable::initMaxAcI(QString str)
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

QString QChannelPowerTable::initMaxHz(QString str)
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

void QChannelPowerTable::UpdateValidTableDatas()
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
bool QChannelPowerTable::eventFilter(QObject *obj, QEvent *event)
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

void QChannelPowerTable::mousePressEvent(QMouseEvent * event)
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
//#endif

QString QChannelPowerTable::initMaxZeroAmp_RemoteMeas( MOUDLEType moudleType,QString str )
{
	float fMaxAmp = 0;
	float fMaxAmp_U = 7.8 / 3;
	float fMaxAmp_I = 4;

	if (moudleType == Moudle_U)
	{
		fMaxAmp = fMaxAmp_U;
	}
	else if (moudleType == Moudle_I)
	{
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

int QChannelPowerTable::getChIndexByChName( const CString & strChName )
{
	QList<QTableWidgetItem *> items = this->findItems(strChName, Qt::MatchContains);

	if (!items.isEmpty()) 
	{
		int row = items.at(0)->row();
		return row;
	}

	return -1;
}
