#include "QRemoteMeasTable.h"
#include <QHeaderView>
#include <qmath.h>
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../../Module/DataMngr/DvmDevice.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "SttMacroParaEditViewRemoteMeas.h"
#include "../../SttTestBase/SttComplexp.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QDesktopWidget>
#include <QApplication>

extern STT_SystemParas g_oSystemParas;

QRemoteMeasTable::QRemoteMeasTable(CExBaseList *pChVList,CExBaseList *pChIList,tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR,QWidget *parent)
: QScrollTableWidget(parent)
{
	m_nRowHeight = 0;
	m_nHeaderViewHeight = 0;

	m_fAmpMax = 120;
	m_fAmpMin = 0;

	m_pChVDatas = pChVList;
	m_pChIDatas = pChIList;
	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;
	m_ColorList<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181)<<QColor(168,169,171)<<QColor(240,240,240) <<QColor(205,205,205)<<QColor(167,183,181);

	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	m_pComboBoxChannelDelegate = NULL;
	installEventFilter(this);

	InitUI();
}

QRemoteMeasTable::~QRemoteMeasTable()
{
}

void QRemoteMeasTable::InitUI()
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

    //this->horizontalHeader()->setStretchLastSection(true);
	QFont font3 = this->horizontalHeader()->font();
	font3.setPointSize(20);
	this->horizontalHeader()->setFont(font3);

	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void QRemoteMeasTable::InitTable()
{
	setRowCount(11);
	setColumnCount(5);

	CString strName, strValue, strPrimeValue, strSecValue, strErr;
	QStringList headers;
	xlang_GetLangStrByFile(strName, "sName"); //名称
	xlang_GetLangStrByFile(strValue, "sStandardValue");//标准值
	xlang_GetLangStrByFile(strPrimeValue, "IEC_OnceValue");//一次值
	xlang_GetLangStrByFile(strSecValue, "IEC_TwiceValue");//二次值
	xlang_GetLangStrByFile(strErr, "State_Error");//误差

	headers << strName << strValue << strPrimeValue << strSecValue << strErr;

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	int nLabelWidth1 = fontMetrics.width(strName) + 40;
	int nLabelWidth2 = fontMetrics.width(strValue) + 20;
	int nLabelWidth3 = fontMetrics.width(strPrimeValue) + 10;
	int nLabelWidth4 = fontMetrics.width(strSecValue) + 10 ;
	int nLabelWidth5 = fontMetrics.width(strErr) + 10 ;
	this->setColumnWidth(0,nLabelWidth1);
	this->setColumnWidth(1,nLabelWidth2);
	this->setColumnWidth(2,nLabelWidth3);
	this->setColumnWidth(3,nLabelWidth4);
	this->setColumnWidth(4,nLabelWidth5);
	setHorizontalHeaderLabels(headers);
	setIconSize(QSize(20,20));

	for (int row = 0;  row  <  this->rowCount();  row++)
	{
		for (int col  =  0;  col  <  this->columnCount();  col++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			if ((row == 0 && col == 0) || (row == 2 && col == 0)) 
			{
				item->setFlags(item->flags() | Qt::ItemIsEditable); // 设置为可编辑
			}
			else
			{
				item->setFlags(Qt::NoItemFlags);
			}
				item->setTextColor(QColor(0, 0, 0));
			setItem(row,col,item);
			setRowHeight(row,m_nRowHeight);
		}
	}

	m_pComboBoxChannelDelegate = new QComboBoxChannelDelegate(this);
	setItemDelegateForColumn(0, m_pComboBoxChannelDelegate);


	item(0,0)->setText("Ua");
	item(2,0)->setText("Uc");

	connect(m_pComboBoxChannelDelegate,SIGNAL(commitData(QWidget*)),this,SLOT(slot_ComboBoxChannelChanged(QWidget*)),Qt::UniqueConnection);
}

int QRemoteMeasTable::getTableHeight()
{
	return this->height();
}

int QRemoteMeasTable::getTableWidth()
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

void QRemoteMeasTable::UpdateText(const QString &strText)
{
	if (m_pCurrKeyboardItem == NULL)
	{
		return;
	}

	long nRow = m_pCurrKeyboardItem->row();
	long nCol = m_pCurrKeyboardItem->column();
	m_pCurrKeyboardItem->setText(strText);
	slot_OnCellChanged(nRow,nCol);
	emit sig_updataParas();
}

void QRemoteMeasTable::slot_UpdataVamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	
	slot_ActUEqualAmpClicked();
}

void QRemoteMeasTable::slot_UpdataIamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActIqualAmpClicked();
}

void QRemoteMeasTable::slot_UpdataHzamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActHzEqualClicked();
}

void QRemoteMeasTable::slot_UpdataZX(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActPhasePClicked();
}

void QRemoteMeasTable::slot_UpdataFX(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActPhaseNClicked();
}

void QRemoteMeasTable::slot_UpdataLX()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText("0");
	slot_ActPhaseZClicked();
}

void QRemoteMeasTable::slot_ActUEqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void QRemoteMeasTable::slot_ActIqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	float fVal = pItem->text().toFloat();
	Act_setUIAmpValue(pItem,fVal);
}

void QRemoteMeasTable::slot_ActHzEqualClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	float fv = pItem->text().toFloat();
	Act_setHzEqualValue(0,3,fv);
}

void QRemoteMeasTable::slot_ActPhasePClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	int row = pItem->row();
	float fv = pItem->text().toFloat();
	Act_setPrasePValue(row,0,fv);
}

void QRemoteMeasTable::slot_ActPhaseNClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	int row = pItem->row();
	float fv = pItem->text().toFloat();
	Act_setPraseNValue(row,0,fv);
}

void QRemoteMeasTable::slot_ActPhaseZClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem == NULL)
	{
		return;
	}

	int row = pItem->row();
	Act_setPraseZValue(0,3);
}

void QRemoteMeasTable::Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll, long nCol)
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

	for (int i=0;i<rowCount();i++)
	{
		item(i,nCol)->setText(strVal);
	}
}

void QRemoteMeasTable::Act_setHzEqualValue(int nStart,int nEnd,float fv, long nCol)
{
	QString strVal = QString::number(fv,'f',3);

	for (int i=nStart; i<=nEnd; i++)
	{
		int nCount = m_pChVDatas->GetCount()+m_pChIDatas->GetCount();
		if(i>nCount-1)
		{
			break;
		}

		item(i,nCol)->setText(strVal);
	}
}

void QRemoteMeasTable::Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol)
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

void QRemoteMeasTable::Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol)
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

void QRemoteMeasTable::Act_setPraseZValue(int nStart,int nEnd, long nCol)
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

bool QRemoteMeasTable::eventFilter(QObject *obj, QEvent *event)
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

void QRemoteMeasTable::mousePressEvent(QMouseEvent * event)
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

void QRemoteMeasTable::setTableData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	disconnect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)));

	m_pArrUIVOL = pArrUIVOL;
	m_pArrUICUR = pArrUICUR;

	UpdateTable();

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)),Qt::UniqueConnection);
}

void QRemoteMeasTable::slot_OnCellChanged( int row,int col)
{
	if (row  <  0)
	{
		return;
	}
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem*  pItem  =  item(row,  col);

	if (pItem == NULL)
	{
		return;
	}

	QString str = pItem->text();
	float fv;
	QString strText;

	switch (col)
	{
	case 1:
		{
			fv = str.toFloat();
			if (isPosiDigitstr(str))
			{
				str = initMaxAc(str);
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
				if (m_ModuleType == Moudle_U)
				{
					fv = m_pArrUIVOL[row].Harm[1].fAmp;				
				}
				else if (m_ModuleType == Moudle_I)
				{
					fv = m_pArrUICUR[row].Harm[1].fAmp;				
				}
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
		}
		break;
	//case 2:
	//	{
	//		fv = str.toFloat();
	//		if (isPosiDigitstr(str))
	//		{
	//			str = initMaxAc(str);

	//			fv = str.toFloat();
	//			if (fv > m_fAmpMax)
	//			{
	//				fv = m_fAmpMax;
	//			}

	//			if (fv < m_fAmpMin)
	//			{
	//				fv = m_fAmpMin;
	//			}

	//			strText.setNum(fv,'f',3);
	//			pItem->setText(strText);
	//		}
	//		else
	//		{
	//			fv = m_pArrUIVOL[row].Tel.fPrimValue;
	//			strText.setNum(fv,'f',3);
	//			pItem->setText(strText);
	//		}
	//	}
	//	break;
	//case 3:
	//	{
	//		fv = str.toFloat();
	//		if (isPosiDigitstr(str))
	//		{
	//			str = initMaxAc(str);
	//			fv = str.toFloat();

	//			if (fv > m_fAmpMax)
	//			{
	//				fv = m_fAmpMax;
	//			}

	//			if (fv < m_fAmpMin)
	//			{
	//				fv = m_fAmpMin;
	//			}

	//			strText.setNum(fv,'f',3);
	//			pItem->setText(strText);
	//		}
	//		else
	//		{
	//			fv = m_pArrUIVOL[row].Tel.fSecondValue;
	//			strText.setNum(fv,'f',3);
	//			pItem->setText(strText);
	//		}
	//	}
	//	break;
	default:
		break;
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

	if (m_pCurrKeyboardItem != NULL /*&& m_MacroType != MACROTYPE_State*/)//20230112 zhouhj  状态序列也更新参数，只更新矢量图
	{
		long nRow = m_pCurrKeyboardItem->row();
		long nCol = m_pCurrKeyboardItem->column();
		emit sig_ChannelRemoteValueChanged(nRow,nCol, m_pCurrKeyboardItem->text().toFloat());//valueFlag=（1:幅值 2:相位 3:频率）
	}
}

QString QRemoteMeasTable::initMaxAc(QString str)
{
	if (str.toFloat()- m_fAmpMax > 0)
	{
		if(CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,"输入值%f超出范围(%f).",str.toFloat(),m_fAmpMax);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("The input value %f is out of range(%f)."),str.toFloat(),m_fAmpMax);
		}

		return QString("%1").arg(m_fAmpMax);
	}
	else
	{
		return str;
	}
}

void QRemoteMeasTable::slot_OnItemDoubleClicked( QTableWidgetItem *pItem )
{
	if(!(pItem->flags() & Qt::ItemIsEnabled))
	{
		return;
	}

	int nRow = row(pItem);
	int nCol = column(pItem);
	QString strValue = pItem->text();
	
	long nEditType = 4;
	//if (nCol == 1)
	//{
	//	if(m_moudleType == Moudle_U)
	//	{
	//		nEditType = 0;
	//	}
	//	else
	//	{
	//		nEditType = 1;
	//	}
	//}
	//else if (nCol == 2)
	//{
	//	nEditType = 4;
	//}
	//else if (nCol == 3)
	//{
	//	nEditType = 4;//数字键盘
	//}
	//else if (nCol == 4)
	//{
	//	nEditType = 4;
	//}
	//
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::Attach330Channel(this, nEditType);
#endif
		
	m_pCurrKeyboardItem = pItem;
}

void QRemoteMeasTable::CalValueTable(CString strChName,long nChIndex,float fRate1,float fRate2)
{
	CExBaseList *pDataset = (CExBaseList*)g_pRemoteMeas->m_pBtnWidget->m_pSelect_ComboBox->GetCurrSelObject();

	if (pDataset == NULL)
	{
		item(nChIndex,2)->setText("--");
		item(nChIndex,3)->setText("--");
		item(nChIndex,4)->setText("--");
		return;
	}

	strChName.MakeLower();
	CString strChName_Temp;
	CDvmData *pCurrData = NULL,*pFind = NULL;
	POS pos = pDataset->GetHeadPosition();

	while(pos)
	{
		pCurrData = (CDvmData *)pDataset->GetNext(pos);
		strChName_Temp = pCurrData->m_strName;
		strChName_Temp.MakeLower();

		if (strChName_Temp == strChName)
		{
			pFind = pCurrData;
			break;
		}

		strChName_Temp = pCurrData->m_strID;
		strChName_Temp.MakeLower();

		if (strChName_Temp == strChName)
		{
			pFind = pCurrData;
			break;
		}
	}

	if (pFind == NULL)
	{
		item(nChIndex,2)->setText("--");
		item(nChIndex,3)->setText("--");
		item(nChIndex,4)->setText("--");
		return;
	}

	CString strSecondValue = pFind->m_strValue;
	float fSecondValue = CString_To_double(strSecondValue);
	float fPrimeValue;

	if (strChName == /*STT_RemoteMeas_Data_ID_U0*/_T("u0") || strChName == /*STT_RemoteMeas_Data_ID_I0*/_T("i0")) 
	{
		fPrimeValue = fSecondValue*fRate2;
	}
	else
	{
		fPrimeValue = fSecondValue*fRate1;
	}

	item(nChIndex,2)->setText(QString::number(fPrimeValue,'f',0)); //一次值保留整数
	item(nChIndex,3)->setText(QString::number(fSecondValue,'f',3));

	float fErro;
	float fDValue;
	float fAmp = item(nChIndex,1)->text().toFloat();
	if (strChName.contains("u"))//3个电压的误差未计算，一直显示10
	{
		fDValue = fSecondValue-/*m_pArrUIVOL[nChIndex].Harm[1].fAmp*/fAmp; 
		//fErro = fDValue/g_oSystemParas.m_fVNom;
		fErro = fDValue/fAmp;  //基本误差 = (二次值-加量值)/加量值
	}
	else if (strChName.contains("i"))
	{
		fDValue = fSecondValue-/*m_pArrUICUR[nChIndex-4].Harm[1].fAmp*/fAmp;
		//fErro = fDValue/g_oSystemParas.m_fINom;
		fErro = fDValue/fAmp;
	}

	item(nChIndex,4)->setText(QString::number(fErro,'f',3));

	if (strChName == STT_RemoteMeas_Data_ID_Freq)
	{
		fErro = fSecondValue-m_pArrUICUR[0].Harm[1].fFreq;
		item(8,2)->setText(QString::number(fSecondValue,'f',0));//一次值保留整数
		item(8,3)->setText(QString::number(fSecondValue,'f',3));
		item(8,4)->setText(QString::number(fErro,'f',3));
	}

	if (strChName == STT_RemoteMeas_Data_ID_ActivePower)
	{
		double dActiveP1 = SetActive_Power_ByAng(m_pArrUIVOL[0].Harm[1].fAmp,m_pArrUIVOL[0].Harm[1].fAngle,m_pArrUICUR[0].Harm[1].fAmp,m_pArrUICUR[0].Harm[1].fAngle);
		double dActiveP2 = SetActive_Power_ByAng(m_pArrUIVOL[1].Harm[1].fAmp,m_pArrUIVOL[1].Harm[1].fAngle,m_pArrUICUR[1].Harm[1].fAmp,m_pArrUICUR[1].Harm[1].fAngle);
		double dActiveP3 = SetActive_Power_ByAng(m_pArrUIVOL[2].Harm[1].fAmp,m_pArrUIVOL[2].Harm[1].fAngle,m_pArrUICUR[2].Harm[1].fAmp,m_pArrUICUR[2].Harm[1].fAngle);
		double dActiveP = dActiveP1 + dActiveP2 + dActiveP3;

		CString strText;
		strText.Format(_T("%.3f"),dActiveP);
		float fActivePower = CString_To_double(strText);

		fPrimeValue = fSecondValue*fRate1*fRate2;
		fDValue = fSecondValue-fActivePower;
		//fErro = fDValue/(g_oSystemParas.m_fVNom*g_oSystemParas.m_fINom*3);
		fErro = fDValue/fActivePower;

		item(9,1)->setText(strText);
		item(9,2)->setText(QString::number(fPrimeValue,'f',0));//一次值保留整数
		item(9,3)->setText(QString::number(fSecondValue,'f',3));
		item(9,4)->setText(QString::number(fErro,'f',3));
	}

	if (strChName == STT_RemoteMeas_Data_ID_ReactivePower)
	{
		double dReactiveP1 = SetReactive_Power_ByAng(m_pArrUIVOL[0].Harm[1].fAmp,m_pArrUIVOL[0].Harm[1].fAngle,m_pArrUICUR[0].Harm[1].fAmp,m_pArrUICUR[0].Harm[1].fAngle);
		double dReactiveP2 = SetReactive_Power_ByAng(m_pArrUIVOL[1].Harm[1].fAmp,m_pArrUIVOL[1].Harm[1].fAngle,m_pArrUICUR[1].Harm[1].fAmp,m_pArrUICUR[1].Harm[1].fAngle);
		double dReactiveP3 = SetReactive_Power_ByAng(m_pArrUIVOL[2].Harm[1].fAmp,m_pArrUIVOL[2].Harm[1].fAngle,m_pArrUICUR[2].Harm[1].fAmp,m_pArrUICUR[2].Harm[1].fAngle);
		double dReactiveP = dReactiveP1 + dReactiveP2 + dReactiveP3;

		CString strText;
		strText.Format(_T("%.3f"),dReactiveP);
		float fReactivePower = CString_To_double(strText);

		fPrimeValue = fSecondValue*fRate1*fRate2;
		fDValue = fSecondValue-fReactivePower;
		//fErro = fDValue/(g_oSystemParas.m_fVNom*g_oSystemParas.m_fINom*3);
		fErro = fDValue/fReactivePower;


		item(10,1)->setText(strText);
		item(10,2)->setText(QString::number(fPrimeValue,'f',0));//一次值保留整数
		item(10,3)->setText(QString::number(fSecondValue,'f',3));
		item(10,4)->setText(QString::number(fErro,'f',3));
	}
}

void QRemoteMeasTable::UpdateTable()
{
	float fPrimeVol = g_pRemoteMeas->m_pBtnWidget->m_fPrimVolValue;
	float fSecondVol = g_pRemoteMeas->m_pBtnWidget->m_fSecondVolValue;
	float fRateVol = fPrimeVol/fSecondVol;
	float fPrimeVZero = g_pRemoteMeas->m_pBtnWidget->m_fPrimVZeroValue;
	float fSecondVZero = g_pRemoteMeas->m_pBtnWidget->m_fSecondVZeroValue;
	float fRateVZero = fPrimeVZero/fSecondVZero;

	float fPrimeCur = g_pRemoteMeas->m_pBtnWidget->m_fPrimCurValue;
	float fSecondCur = g_pRemoteMeas->m_pBtnWidget->m_fSecondCurValue;
	float fRateCur = fPrimeCur/fSecondCur;
	float fPrimeCZero = g_pRemoteMeas->m_pBtnWidget->m_fPrimCZeroValue;
	float fSecondCZero = g_pRemoteMeas->m_pBtnWidget->m_fSecondCZeroValue;
	float fRateCZero = fPrimeCZero/fSecondCZero;

	//item(0,0)->setText("Ua");
	//item(0,1)->setText(QString::number(m_pArrUIVOL[0].Harm[1].fAmp,'f',3));

	slot_ChannelAmpValueChanged(0,m_pArrUIVOL[0].Harm[1].fAmp);
	CalValueTable(STT_RemoteMeas_Data_ID_Ua,0,fRateVol,fRateVZero);

	item(1,0)->setText("Ub");
	item(1,1)->setText(QString::number(m_pArrUIVOL[1].Harm[1].fAmp,'f',3));
	CalValueTable(STT_RemoteMeas_Data_ID_Ub,1,fRateVol,fRateVZero);

	//item(2,0)->setText("Uc");
	//item(2,1)->setText(QString::number(m_pArrUIVOL[2].Harm[1].fAmp,'f',3));
	slot_ChannelAmpValueChanged(2,m_pArrUIVOL[2].Harm[1].fAmp);
	CalValueTable(STT_RemoteMeas_Data_ID_Uc,2,fRateVol,fRateVZero);

	item(3,0)->setText("U0");
	item(3,1)->setText(QString::number(m_pArrUIVOL[3].Harm[1].fAmp,'f',3));
	CalValueTable(STT_RemoteMeas_Data_ID_U0,3,fRateVol,fRateVZero);

	item(4,0)->setText("Ia");
	item(4,1)->setText(QString::number(m_pArrUICUR[0].Harm[1].fAmp,'f',3));
	CalValueTable(STT_RemoteMeas_Data_ID_Ia,4,fRateCur,fRateCZero);

	item(5,0)->setText("Ib");
	item(5,1)->setText(QString::number(m_pArrUICUR[1].Harm[1].fAmp,'f',3));
	CalValueTable(STT_RemoteMeas_Data_ID_Ib,5,fRateCur,fRateCZero);

	item(6,0)->setText("Ic");
	item(6,1)->setText(QString::number(m_pArrUICUR[2].Harm[1].fAmp,'f',3));
	CalValueTable(STT_RemoteMeas_Data_ID_Ic,6,fRateCur,fRateCZero);

	item(7,0)->setText("I0");
	item(7,1)->setText(QString::number(m_pArrUICUR[3].Harm[1].fAmp,'f',3));
	CalValueTable(STT_RemoteMeas_Data_ID_I0,7,fRateCur,fRateCZero);

	item(8,0)->setText("F");
	item(8,1)->setText(QString::number(m_pArrUICUR[0].Harm[1].fFreq,'f',3));
	CalValueTable(STT_RemoteMeas_Data_ID_Freq,8,1,1);

	item(9,0)->setText("P");
	CalValueTable(STT_RemoteMeas_Data_ID_ActivePower,9,fRateVol,fRateCur);

	item(10,0)->setText("Q");
	CalValueTable(STT_RemoteMeas_Data_ID_ReactivePower,10,fRateVol,fRateCur);

	changeColor();

}

void QRemoteMeasTable::changeColor()
{  
	int Static=0;
	QColor oCurColor;

	for (int i = 0;i < rowCount();i++)  
	{
		if (i/11 <= Static)  
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
		if (i%11 == 10)
		{
			Static++;
		}
	} 
}

void QRemoteMeasTable::UpdateValidTableDatas()
{
	for (int i=0;i<rowCount();i++)
	{
		for (int j=0;j<columnCount();j++)
		{
			slot_OnCellChanged(i,j);
		}
	}
}

void QRemoteMeasTable::slot_ComboBoxChannelChanged( QWidget* editor )
{
	if (editor == NULL)
	{
		return;
	}

	int nRow = currentRow();
	QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
	CString strTemp;
	strTemp = pComboBox->currentText();
	float fAmp;
	if (strTemp == _T("Ua") || strTemp == _T("Uc"))
	{
		fAmp = m_pArrUIVOL[nRow].Harm[1].fAmp;
	}
	else
	{
		fAmp = m_pArrUIVOL[nRow].Harm[1].fAmp * sqrt(3.0f);
	}
	item(nRow,1)->setText(QString::number(fAmp,'f',3));
}

void QRemoteMeasTable::slot_ChannelAmpValueChanged( int nIndex,float fAmpValue )
{
	QAbstractItemModel *model = this->model();
	QModelIndex index = model->index(nIndex, 0);
	QVariant data = model->data(index);
	QString strTemp = data.toString();
	float fAmp;
	if (strTemp == _T("Ua") || strTemp == _T("Uc"))
	{
		fAmp = fAmpValue;
	}
	else
	{
		fAmp = fAmpValue * sqrt(3.0f);
	}
	item(nIndex,1)->setText(QString::number(fAmp,'f',3));
}



QComboBoxChannelDelegate::QComboBoxChannelDelegate(QObject *parent):QItemDelegate (parent)
{
	
}

QComboBoxChannelDelegate ::~QComboBoxChannelDelegate()
{

}

QWidget *QComboBoxChannelDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const  
{
	QVariant variant = index.data();

	QScrollComboBox *pComboBox = new QScrollComboBox(parent);

#ifdef _PSX_QT_LINUX_
	pComboBox->SetIgnoreFirstHidePopup(true);
#endif
	return pComboBox;
}

void QComboBoxChannelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const  
{
	QString strValue = index.model()->data(index, Qt::EditRole).toString();
 	QScrollComboBox *pComboBox = qobject_cast<QScrollComboBox*>(editor);
 	QStringList items;
 	if (index.row() == 0)
 	{
 		items << "Ua" << "Uab";
 	}
 	else if (index.row() == 2)
 	{
 		items << "Uc" << "Ucb";
 	}
 	pComboBox->addItems(items);
	int idx = pComboBox->findText(strValue);
	if (idx >= 0)
	{
		pComboBox->setCurrentIndex(idx);
	}
	if (pComboBox->isHidden())
	{
		pComboBox->showPopup();
	}

	connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(commitAndCloseEditor()));
}

void QComboBoxChannelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const  
{
	QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
	if (!comboBox)
	{
		return;
	}

	model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void QComboBoxChannelDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const 
{
	editor->setGeometry(option.rect);
}


void QComboBoxChannelDelegate::paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const
{  
	if (index.column() == 0 && (index.row() == 0 || index.row() == 2))
	{
		QProxyStyle oProxyStyle;
		QStyleOptionComboBox oStyleOptionComboBox;
		oStyleOptionComboBox.state = option.state | QStyle::State_Enabled | QStyle::State_Active;
		oStyleOptionComboBox.rect = option.rect;
		QPalette oPalette;
		oStyleOptionComboBox.currentText = index.data().toString();

		painter->save();
		painter->setClipRect(option.rect);
		oProxyStyle.drawComplexControl(QStyle::CC_ComboBox, &oStyleOptionComboBox, painter);
		oProxyStyle.drawItemText(painter,option.rect,Qt::AlignCenter,oPalette,true,oStyleOptionComboBox.currentText);
		painter->restore();
	}
	else
	{
		QItemDelegate::paint(painter, option, index);
	}
}

void QComboBoxChannelDelegate::commitAndCloseEditor()
{
	QComboBox* editor = qobject_cast<QComboBox*>(sender());
	if (editor) 
	{
		emit commitData(editor);
		emit closeEditor(editor);
	}
}
