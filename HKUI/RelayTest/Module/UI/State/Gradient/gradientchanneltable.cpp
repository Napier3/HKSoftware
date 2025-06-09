#include "gradientchanneltable.h"
#include <QFontMetrics>
#include <QScrollBar>
#include <cmath>
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
//#include "../../SttTestCntrFrameBase.h"
#include "../../../../Module/XLangResource_Native.h"
#include <QApplication>

#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

//#define GenHao3	1.7320508 //根号三

GradientChannelTable::GradientChannelTable(int moudleType,int gradientType,int gradientObj,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent)
	: QScrollTableWidget(parent)
{
	m_pChDatas = pChList;

	m_ModuleType = moudleType;
	m_nGradientType = gradientType;
	m_nGradientObj = gradientObj,

	m_pArrUI = pArrUI;

	m_ColorList<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181)<<QColor(168,169,171)<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181);

	m_fAmpMax = 120;
	m_fAmpMin = 0;
	m_pCurrKeyboardItem = NULL;

	m_bRunning = FALSE;
	installEventFilter(this);

	init();
}

GradientChannelTable::~GradientChannelTable()
{

}

void GradientChannelTable::setTableData(tmt_channel *pArrUI)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	disconnect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemClicked(QTableWidgetItem *)));

// 	this->horizontalHeader()->setFont(*g_pSttGlobalFont);
// 	this->setFont(*g_pSttGlobalFont);
	m_pArrUI = pArrUI;
	UpdateTable();

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemClicked(QTableWidgetItem *)),Qt::UniqueConnection);
}

void GradientChannelTable::setItemValue(int row,int col,float fv)
{
	if (row<rowCount()&&col<columnCount())
	{
		if (col>0&&col<columnCount())
		{
			item(row,col)->setText(QString::number(fv,'f',3));
		}
	}
}

float GradientChannelTable::getItemValue(int row,int col)
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

void GradientChannelTable::setAmpMaxMinValue(float fmax,float fmin)
{
	m_fAmpMax = fmax;
	m_fAmpMin = fmin;
}

void GradientChannelTable::setColumnWidthByNum(int col,int width)
{
	setColumnWidth(col,width);
}

void GradientChannelTable::setTableFixWidgt(int width)
{
	this->setFixedWidth(width);
}

int GradientChannelTable::getTableHeight()
{
	return this->height();
}

int GradientChannelTable::getTableWidth()
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

void GradientChannelTable::Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll)
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
			item(i,3)->setText(strVal);
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
			item(i,3)->setText(strVal);
		}
	}
}

void GradientChannelTable::Act_setHzEqualValue(int nStart,int nEnd,float fv)
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

void GradientChannelTable::init()
{
	setFocusPolicy(Qt::NoFocus);
	setContextMenuPolicy (Qt::CustomContextMenu);

	QHeaderView* pLeft = this->verticalHeader();
    QHeaderView* pTopHeaderView = this->horizontalHeader();

    pLeft->setDefaultSectionSize(15);
	pLeft->setVisible(false);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
    pLeft->setSectionsClickable(false);
    pTopHeaderView->setSectionsClickable(false);
#else
    pLeft->setClickable(false);
    pTopHeaderView->setClickable(false);
#endif

	QFont font1 = *g_pSttGlobalFont/*this->horizontalHeader()->font()*/;
//	font1.setBold(true);
	
//	this->horizontalHeader()->setFont(font1);
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
	QFontMetrics fontHeaderViewMe = QFontMetrics(font1);
	m_nHeaderViewHeight = fontHeaderViewMe.height() + 20;
	QFont font2 = *g_pSttGlobalFont/*this->font()*/;
// 	font2.setPointSize(20);
// 	this->setFont(font2);

	QFontMetrics fontRowMe = QFontMetrics(font2);
	m_nRowHeight = fontRowMe.height() + 20;
	
	this->horizontalScrollBar()->setEnabled(true);
	this->verticalScrollBar()->setEnabled(true);

	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	//this->horizontalHeader()->setResizeMode(QHeaderView::Fixed); 
//    this->horizontalHeader()->setResizeMode(QHeaderView::Stretch); 

// 	QFont font3 = this->horizontalHeader()->font();
// 	font3.setPointSize(20);
// 	this->horizontalHeader()->setFont(font3);

//	this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(1,m_pCheckBoxDelegateBase);

	initTable();

// 	this->horizontalHeader()->setFont(*g_pSttGlobalFont);
// 	this->setFont(*g_pSttGlobalFont);
// 	QFont oFont;
// 	oFont.setPixelSize(14);//20230113 zhouhj 同样的设置,电压和电流通道的字体在linux下显示不一样,此处暂时固定标题字体
	horizontalHeader()->setFont(/*oFont*/*g_pSttGlobalFont);
	setFont(*g_pSttGlobalFont);
}

void GradientChannelTable::initTable()
{
	ASSERT(m_pChDatas);

	setColumnCount(5);
	horizontalHeader()->setStretchLastSection(true); //设置充满表宽度

	for (int i = 0; i < this->rowCount(); i++)
	{
		item(i,0)->setText("");
		item(i,1)->setCheckState(Qt::Unchecked);
		item(i,2)->setText("");
		item(i,3)->setText("");
		item(i,4)->setText("");
	}

	setRowCount(m_pChDatas->GetCount());

	QStringList headers;
/*
	if(m_nGradientType == GRADIENT_TYPE_Linear)
	{
		if(m_nGradientObj == GRADIENT_AMP)
		{
			if(m_ModuleType == Moudle_U)
			{
				headers<<tr("通道")<<tr("选择")<<tr("始值")<<tr("终值")<<tr("dv/dt");
			}
			else if(m_ModuleType == Moudle_I)
			{
				headers<<tr("通道")<<tr("选择")<<tr("始值")<<tr("终值")<<tr("di/dt");
			}
		}
		else if(m_nGradientObj == GRADIENT_FRE)
		{
			headers<<tr("通道")<<tr("选择")<<tr("始值")<<tr("终值")<<tr("df/dt");
		}
	}
	else if(m_nGradientType == GRADIENT_TYPE_Step)
	{
		headers<<tr("通道")<<tr("选择")<<tr("始值")<<tr("终值")<<tr("步长");
	}

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	int nLabelWidth1 = fontMetrics.width(tr("通道")) + 10;
	int nLabelWidth2 = fontMetrics.width(tr("选择")) + 10;
	int nLabelWidth3 = fontMetrics.width(tr("-57.735")) + 20;
	int nLabelWidth4 = fontMetrics.width(tr("-57.735")) + 20;
	int nLabelWidth5 = fontMetrics.width(tr("0.001")) + 30 ;
*/
    CString strChannel, strSelect, strBeginVal, strEndVal, strStep,strUnit;
	xlang_GetLangStrByFile(strChannel, "Native_Channel");
	xlang_GetLangStrByFile(strSelect, "sSelect");
	xlang_GetLangStrByFile(strBeginVal, "State_BeginVal");
	xlang_GetLangStrByFile(strEndVal, "State_EndVal");
	xlang_GetLangStrByFile(strStep, "sStep");

	if(m_nGradientObj == GRADIENT_AMP)
	{
		if(m_ModuleType == Moudle_U)
		{
			strUnit = "(V)";
		}
		else if(m_ModuleType == Moudle_I)
		{
			strUnit = "(A)";
		}
	}
	else if(m_nGradientObj == GRADIENT_FRE)
	{
		strUnit = "(Hz)";
	}

	strBeginVal += strUnit;
	strEndVal += strUnit;

	if (m_nGradientType == GRADIENT_TYPE_Step)
	{
		strStep += strUnit;
	}

	if(m_nGradientType == GRADIENT_TYPE_Linear)
	{
		if(m_nGradientObj == GRADIENT_AMP)
		{
			if(m_ModuleType == Moudle_U)
			{
				headers << strChannel << strSelect << strBeginVal << strEndVal <<tr("dv/dt(V/s)");
			}
			else if(m_ModuleType == Moudle_I)
			{
				headers << strChannel << strSelect << strBeginVal << strEndVal <<tr("di/dt(A/s)");
			}
		}
		else if(m_nGradientObj == GRADIENT_FRE)
		{
			headers << strChannel << strSelect << strBeginVal << strEndVal <<tr("df/dt(Hz/s)");
		}
	}
	else if(m_nGradientType == GRADIENT_TYPE_Step)
	{
		headers << strChannel << strSelect << strBeginVal << strEndVal <<strStep;
	}

	setHorizontalHeaderLabels(headers);

	QFontMetrics fontMetrics = QFontMetrics(*g_pSttGlobalFont/*this->font()*/);
	int nLabelWidth1 = fontMetrics.width(strChannel) + 30;
	int nLabelWidth2 = fontMetrics.width(strSelect) + 40;
	int nLabelWidth3 = fontMetrics.width(strBeginVal) + 30;
	int nLabelWidth4 = fontMetrics.width(strEndVal) + 30;
	int nLabelWidth5 = fontMetrics.width(tr("df/dt(Hz/s)")) + 20 ;

	this->setColumnWidth(0,nLabelWidth1);
	this->setColumnWidth(1,nLabelWidth2);
	this->setColumnWidth(2,nLabelWidth3);
	this->setColumnWidth(3,nLabelWidth4);
	this->setColumnWidth(4,nLabelWidth5);


	for (int row=0;row<this->rowCount();row++)
	{
		for (int col=0;col<this->columnCount();col++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

			if (col == 1)
			{
				item->setCheckState(Qt::Unchecked);
				item->setFlags(item->flags() & (~Qt::ItemIsEditable));
			}
			setItem(row,col,item);
			setRowHeight(row,m_nRowHeight);
		}
	}
	
//	int ntableHight = this->horizontalHeader()->height() + ((m_nRowHeight)*this->rowCount());
	//setFixedHeight(ntableHight);
}

void GradientChannelTable::changeTableColor()
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

void GradientChannelTable::EnableGradientCol()
{
	if(m_nGradientType > GRADIENT_TYPE_None)
	{
		setDisabled(false);
		for(int i=0;i<m_pChDatas->GetCount();i++)
		{
			item(i,0)->setFlags(Qt::NoItemFlags);
			item(i,0)->setBackground(item(i,0)->background());
			item(i,0)->setTextColor(QColor(0, 0, 0));

			item(i,2)->setFlags(Qt::NoItemFlags);
			item(i,2)->setBackground(Qt::gray);
			item(i,2)->setTextColor(QColor(0, 0, 0));

			item(i,3)->setFlags(item(i,3)->flags());
			item(i,3)->setBackground(item(i,3)->background());

			item(i,4)->setFlags(item(i,4)->flags());
			item(i,4)->setBackground(item(i,4)->background());
		}
	}
	else
	{
		setDisabled(true);
	}
}

void GradientChannelTable::UpdateTable()
{
	ASSERT(m_pChDatas);
	POS pos = m_pChDatas->GetHeadPosition();
	CExBaseObject *pCh = NULL;
	long nChIndex = 0;

	while(pos)
	{
		pCh = m_pChDatas->GetNext(pos);
		
		item(nChIndex,0)->setText(pCh->m_strName);
		if (m_nGradientType == GRADIENT_TYPE_Linear)
		{
			if(m_nGradientObj == GRADIENT_AMP)
			{
				if(m_pArrUI[nChIndex].Ramp[0].nIndex == -1)
				{
					item(nChIndex,1)->setCheckState(Qt::Unchecked);
				}
				else if (m_pArrUI[nChIndex].Ramp[0].nIndex == 1)
				{
					item(nChIndex,1)->setCheckState(Qt::Checked);
				}
				item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].Harm[1].fAmp,'f',3));
				item(nChIndex,3)->setText(QString::number(m_pArrUI[nChIndex].Ramp[0].fEnd,'f',1));
				item(nChIndex,4)->setText(QString::number(m_pArrUI[nChIndex].Ramp[0].fStep*1000,'f',3));
			}
			else if (m_nGradientObj == GRADIENT_FRE)
			{
				if(m_pArrUI[nChIndex].Ramp[2].nIndex == -1)
				{
					item(nChIndex,1)->setCheckState(Qt::Unchecked);
				}
				else if (m_pArrUI[nChIndex].Ramp[2].nIndex == 1)
				{
					item(nChIndex,1)->setCheckState(Qt::Checked);
				}
				item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].Harm[1].fFreq,'f',3));
				item(nChIndex,3)->setText(QString::number(m_pArrUI[nChIndex].Ramp[2].fEnd,'f',1));
				item(nChIndex,4)->setText(QString::number(m_pArrUI[nChIndex].Ramp[2].fStep*1000,'f',3));
			}
		}
		else if (m_nGradientType == GRADIENT_TYPE_Step)
		{
			if(m_nGradientObj == GRADIENT_AMP)
			{
				if(m_pArrUI[nChIndex].Ramp[0].nIndex == -1)
				{
					item(nChIndex,1)->setCheckState(Qt::Unchecked);
				}
				else if (m_pArrUI[nChIndex].Ramp[0].nIndex == 1)
				{
					item(nChIndex,1)->setCheckState(Qt::Checked);
				}
				item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].Harm[1].fAmp,'f',3));
				item(nChIndex,3)->setText(QString::number(m_pArrUI[nChIndex].Ramp[0].fEnd,'f',1));
				item(nChIndex,4)->setText(QString::number(m_pArrUI[nChIndex].Ramp[0].fStep,'f',3));
			}
			else if (m_nGradientObj == GRADIENT_FRE)
			{
				if(m_pArrUI[nChIndex].Ramp[2].nIndex == -1)
				{
					item(nChIndex,1)->setCheckState(Qt::Unchecked);
				}
				else if (m_pArrUI[nChIndex].Ramp[2].nIndex == 1)
				{
					item(nChIndex,1)->setCheckState(Qt::Checked);
				}
				item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].Harm[1].fFreq,'f',3));
				item(nChIndex,3)->setText(QString::number(m_pArrUI[nChIndex].Ramp[2].fEnd,'f',1));
				item(nChIndex,4)->setText(QString::number(m_pArrUI[nChIndex].Ramp[2].fStep,'f',3));
			}
		}

		nChIndex++;
	}

	EnableGradientCol();
	changeTableColor();
}

void GradientChannelTable::slot_ActUEqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void GradientChannelTable::slot_ActIqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void GradientChannelTable::slot_ActHzEqualClicked()
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

void GradientChannelTable::slot_UpdataVamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);

	slot_ActUEqualAmpClicked();
}

void GradientChannelTable::slot_UpdataIamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);

	slot_ActIqualAmpClicked();
}

void GradientChannelTable::slot_UpdataHzamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);

	slot_ActHzEqualClicked();
}
void GradientChannelTable::UpdateText(const QString &strText)
{
	if (m_pCurrKeyboardItem == NULL)
	{
		return;
	}

	long nRow = m_pCurrKeyboardItem->row();
	long nCol = m_pCurrKeyboardItem->column();
	m_pCurrKeyboardItem->setText(strText);
	slot_OnCellChanged(nRow,nCol);
 	emit sig_ScrollFinished();

// 	emit sig_ChannelValueChanged(m_moudleType,nRow,nCol, m_pCurrKeyboardItem->text().toFloat());//valueFlag=（1:幅值 2:相位 3:频率）
}

void GradientChannelTable::slot_OnItemClicked(QTableWidgetItem *pItem)
{
	if(!(pItem->flags() & Qt::ItemIsEnabled))
	{
		return;
	}

	int nRow = row(pItem);
	int nCol = column(pItem);

	CString strValue = pItem->text();

	long nEditType;
	if (nCol == 3)
	{
		if(m_nGradientObj == GRADIENT_AMP)
		{
			if(m_ModuleType == 0)
			{
				nEditType = 0;
			}
			else if(m_ModuleType == 1)
			{
				nEditType = 1;
			}
		}
		else  if(m_nGradientObj == GRADIENT_FRE)
		{
			nEditType = 3;
		}
	}
	else if (nCol == 4)
	{
		nEditType = 4;
	}
	else 
	{
		return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::Attach330Channel(this, nEditType);
#endif

	m_pCurrKeyboardItem = pItem;
 
// 	slot_OnCellChanged(row(pItem),column(pItem));
}


void GradientChannelTable::slot_OnCellChanged(int row,int col)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);
	QString str = pItem->text();
	float fv;
	QString strText;

	switch (col)
	{
	case 3: 	//终值
		{
			fv = str.toFloat();
			if (isPosiDigitstr(str))
			{
				if(m_nGradientObj == GRADIENT_AMP)
				{
					str = initMaxAc(str);
				}
				else  if(m_nGradientObj == GRADIENT_FRE)
				{
					str = initMaxHz(str);
				}

				fv = str.toFloat();
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
			else
			{
				//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("输入值含有非法字符."));
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_State_IlleInputCharac.GetString()); //输入值含有非法字符.lcq 3.14
				if(m_nGradientObj == GRADIENT_AMP)
				{
					fv = m_pArrUI[row].Ramp[0].fEnd;
				}
				else if(m_nGradientObj == GRADIENT_FRE)
				{
					fv = m_pArrUI[row].Ramp[2].fEnd;
				}

				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
		}
		break;
	case 4:	//步长（滑差）
		{
			fv = str.toFloat();
			if (isPosiDigitstr(str))
			{
				if(m_nGradientObj == GRADIENT_AMP)
				{
					str = initMaxAc(str);
				}
				else  if(m_nGradientObj == GRADIENT_FRE)
				{
					str = initMaxHz(str);
				}

				fv = str.toFloat();
				if (fv > m_fAmpMax)
				{
					fv = m_fAmpMax;
				}

				if (fv < m_fAmpMin)
				{
					fv = m_fAmpMin;
				}

				if (fv < 0.001)
				{
					fv = 0.001;
				}

				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
			else
			{
				if(m_nGradientObj == GRADIENT_AMP)
				{
					fv = m_pArrUI[row].Ramp[0].fStep;
				}
				else  if(m_nGradientObj == GRADIENT_FRE)
				{
					fv = m_pArrUI[row].Ramp[2].fStep;
				}

				if (fv < 0.001)
				{
					fv = 0.001;
				}

				if(m_nGradientType==GRADIENT_TYPE_Linear)
				{
					fv = fv*1000;
				}
				
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
		}
		break;
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	emit sig_ScrollFinished();
}

void GradientChannelTable::InitLinearStepGradient()
{
	POS pos = m_pChDatas->GetHeadPosition();
	CExBaseObject *pCh = NULL;
	long nChIndex = 0;

	while(pos)
	{
		pCh = m_pChDatas->GetNext(pos);

		if (m_nGradientType == GRADIENT_TYPE_Linear)
		{
			if(m_nGradientObj == GRADIENT_AMP)
			{
				m_pArrUI[nChIndex].Ramp[0].fStep *= 1000;
			}
			else if (m_nGradientObj == GRADIENT_FRE)
			{
				m_pArrUI[nChIndex].Ramp[2].fStep *= 1000;
			}
		}
		else if (m_nGradientType == GRADIENT_TYPE_Step)
		{
			if(m_nGradientObj == GRADIENT_AMP)
			{
				m_pArrUI[nChIndex].Ramp[0].fStep /= 1000;
			}
			else if (m_nGradientObj == GRADIENT_FRE)
			{
				m_pArrUI[nChIndex].Ramp[2].fStep /= 1000;
			}
		}

		nChIndex++;
	}
}


void GradientChannelTable::saveTable()
{
	POS pos = m_pChDatas->GetHeadPosition();
	CExBaseObject *pCh = NULL;
	long nChIndex = 0;

	while(pos)
	{
		pCh = m_pChDatas->GetNext(pos);

		if (m_nGradientType == GRADIENT_TYPE_Linear)
		{
			if(m_nGradientObj == GRADIENT_AMP)
			{
				if(item(nChIndex,1)->checkState() >0/*== Qt::Checked*/)
				{
					m_pArrUI[nChIndex].Ramp[0].nIndex = 1;
				}
				else
				{
					m_pArrUI[nChIndex].Ramp[0].nIndex = -1;
				}
				
				QString str = item(nChIndex,3)->text();
				m_pArrUI[nChIndex].Ramp[0].fEnd = str.toFloat();
				
				str = item(nChIndex,4)->text();
				m_pArrUI[nChIndex].Ramp[0].fStep = str.toFloat()/1000;
			}
			else if (m_nGradientObj == GRADIENT_FRE)
			{
				if(item(nChIndex,1)->checkState() >0/* == Qt::Checked*/)
				{
					m_pArrUI[nChIndex].Ramp[2].nIndex = 1;
				}
				else
				{
					m_pArrUI[nChIndex].Ramp[2].nIndex = -1;
				}

				QString str = item(nChIndex,3)->text();
				m_pArrUI[nChIndex].Ramp[2].fEnd = str.toFloat();

				str = item(nChIndex,4)->text();
				m_pArrUI[nChIndex].Ramp[2].fStep = str.toFloat()/1000;
			}
		}
		else if (m_nGradientType == GRADIENT_TYPE_Step)
		{
			if(m_nGradientObj == GRADIENT_AMP)
			{
				if(item(nChIndex,1)->checkState() >0/* == Qt::Checked*/)
				{
					m_pArrUI[nChIndex].Ramp[0].nIndex = 1;
				}
				else
				{
					m_pArrUI[nChIndex].Ramp[0].nIndex = -1;
				}

				QString str = item(nChIndex,3)->text();
				m_pArrUI[nChIndex].Ramp[0].fEnd = str.toFloat();

				str = item(nChIndex,4)->text();
				m_pArrUI[nChIndex].Ramp[0].fStep = str.toFloat();
			}
			else if (m_nGradientObj == GRADIENT_FRE)
			{
				if(item(nChIndex,1)->checkState() >0/* == Qt::Checked*/)
				{
					m_pArrUI[nChIndex].Ramp[2].nIndex = 1;
				}
				else
				{
					m_pArrUI[nChIndex].Ramp[2].nIndex = -1;
				}

				QString str = item(nChIndex,3)->text();
				m_pArrUI[nChIndex].Ramp[2].fEnd = str.toFloat();

				str = item(nChIndex,4)->text();
				m_pArrUI[nChIndex].Ramp[2].fStep = str.toFloat();
			}
		}

		nChIndex++;
	}
}

QString GradientChannelTable::initMaxAc(QString str)
{
	if (str.toFloat()- m_fAmpMax > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_State_EnterTheValueoutofRange.GetString(),str.toFloat(),m_fAmpMax); //输入值%f超出范围(%f lcq
		return QString("%1").arg(m_fAmpMax);
	}
	else
	{
		return str;
	}
}

QString GradientChannelTable::initMaxHz(QString str)
{
	if (str.toFloat()- Global_GetMaxFreq() > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_State_EnterTheValueoutofRange.GetString(),Global_GetMaxFreq());  //输入值%f超出范围(%d) lcq
		return QString("%1").arg(Global_GetMaxFreq());
	}
	else
	{
		return str;
	}
}

//#ifndef _PSX_QT_WINDOWS_
bool GradientChannelTable::eventFilter(QObject *obj, QEvent *event)
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

void GradientChannelTable::mousePressEvent(QMouseEvent * event)
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
