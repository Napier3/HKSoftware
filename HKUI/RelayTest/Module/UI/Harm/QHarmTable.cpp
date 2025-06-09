#include "QHarmTable.h"
#include <QHeaderView>
#include <qmath.h>
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../Module/XLangResource_Native.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

#define HarmColunmCount      5

#include <QDesktopWidget>
#include <QApplication>

//#define GenHao3	1.7320508 //根号三

float  g_fValueStep = 0;

extern STT_SystemParas g_oSystemParas;

long Global_GetHarmTableMaxRowCount()
{
	long nMaxRowCount = g_oLocalSysPara.m_nMaxHarmCount+1;

	if (g_oSystemParas.m_nHasDigital)//包含数字量输出时,需要减去一次谐波
	{
		nMaxRowCount--;
	}

	if (nMaxRowCount>HARMNUMBER)
	{
		nMaxRowCount = HARMNUMBER;
	}

	return nMaxRowCount;
}

QHarmTable::QHarmTable(QWidget *parent)
: QScrollTableWidget(parent)
{
	m_nRowHeight = 0;
	m_nHeaderViewHeight = 0;

	m_pArrUI = NULL;
	m_pChResource = NULL;
	m_nChIndex = 0;

	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	installEventFilter(this);

	InitUI();
}

QHarmTable::~QHarmTable()
{
}

void QHarmTable::InitUI()
{
	setFocusPolicy(Qt::NoFocus);
	setContextMenuPolicy (Qt::CustomContextMenu);

	QHeaderView* pLeft = this->verticalHeader();
	pLeft->setDefaultSectionSize(25);
    pLeft->setVisible(false);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
    pLeft->setSectionsClickable(false);
#else
    pLeft->setClickable(false);
#endif

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

	QDesktopWidget *pDeskTop = QApplication::desktop();
	QRect rcScreen = pDeskTop->screenGeometry();
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	//this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	this->horizontalHeader()->setStretchLastSection(true);
	QFont font3 = this->horizontalHeader()->font();
	font3.setPointSize(20);
	this->horizontalHeader()->setFont(font3);

	m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pCheckBoxDelegateBase);
}


void QHarmTable::SetData( CSttChResource *pChResource,tmt_channel *pArrUI )
{
	if (pChResource == NULL)
	{
		return;
	}

	m_pChResource = pChResource;
	
	m_nChIndex = m_pChResource->GetChIndex_FromZero();

	m_pArrUI = pArrUI;
	
	InitTable();
}

void QHarmTable::InitTable()
{
	ASSERT(m_pChResource);
	QSettingItem* pCurrHarmItem = NULL;	//20240624 huangliang

	this->clear();

	long nMaxRowCount = Global_GetHarmTableMaxRowCount();
	setRowCount(nMaxRowCount);
	setColumnCount(HarmColunmCount);

// 	QStringList headers;
// 
// 	CString strEnable,strChannel, strAmplitude, strPhase, strContent;//使能，通道，幅值，相位，谐波含有率
// 	xlang_GetLangStrByFile(strEnable, "Harm_Enable");
// 	strChannel = m_pChResource->m_strName;
// 	xlang_GetLangStrByFile(strAmplitude, "Native_Amplitude");
// 	xlang_GetLangStrByFile(strPhase, "Native_Angle");
// 	xlang_GetLangStrByFile(strContent, "Harm_Content");
// 
// 	CString strUnit;
// 	if (strChannel.Find('U') >= 0)
// 	{
// 		strUnit += "(V)";
// 	}
// 	else
// 		strUnit += "(A)";
// 	
// 	strAmplitude += strUnit;
// #ifndef _PSX_QT_LINUX_
// 	strPhase += QString::fromLocal8Bit("(°)");	
// 	
// 	//新增表头有效值
	UpdateHeaderView();
// 	float fValue = UpdateCacuParaOneChanel();
// 	CString strZ = QString::number(fValue, 'f', 3);
// 	CString strValdValue = g_sLangTxt_Native_ValdValue.GetString();
// 
// 	strChannel += _T("\n");
// 	strChannel += strValdValue;
// 	strChannel += _T(":");
// 	strChannel += strZ;
// 	strChannel += strUnit;
// 
// 	QDesktopWidget* desktopWidget = QApplication::desktop();
// 	QRect rect = desktopWidget->screenGeometry();
// 	float fWidth = rect.width();
// 
// 	if(fWidth >= 2280)
// 	{
// 		this->setColumnWidth(STT_HARM_TABLE_COL_Select, 50);
// 		this->setColumnWidth(STT_HARM_TABLE_COL_Desc, 120);
// 		this->setColumnWidth(STT_HARM_TABLE_COL_Amp, 88);
// 		this->setColumnWidth(STT_HARM_TABLE_COL_Phase, 88);
// 		this->setColumnWidth(STT_HARM_TABLE_COL_HarmRate, 120);
// 	}
// 	else
// 	{
// 		this->setColumnWidth(STT_HARM_TABLE_COL_Select, 50);
// 		this->setColumnWidth(STT_HARM_TABLE_COL_Desc, 120);
// 		this->setColumnWidth(STT_HARM_TABLE_COL_Amp, 60);
// 		this->setColumnWidth(STT_HARM_TABLE_COL_Phase, 60);
// 		this->setColumnWidth(STT_HARM_TABLE_COL_HarmRate, 100);
// 	}

// #else
// 	strPhase += "(°)";
// 
// 	this->setColumnWidth(STT_HARM_TABLE_COL_Select, 50);
// 	this->setColumnWidth(STT_HARM_TABLE_COL_Desc, 60);
// 	this->setColumnWidth(STT_HARM_TABLE_COL_Amp, 88);
// 	this->setColumnWidth(STT_HARM_TABLE_COL_Phase, 88);
// 	this->setColumnWidth(STT_HARM_TABLE_COL_HarmRate, 140);
// #endif
// 	strContent += "(%)";
// 
// 	headers << strEnable << strChannel << strAmplitude << strPhase << strContent;

	QFontMetrics fontMetrics = QFontMetrics(this->font());

// 	this->setColumnWidth(STT_HARM_TABLE_COL_Select,50);
// 	this->setColumnWidth(STT_HARM_TABLE_COL_Desc,60);
// 	this->setColumnWidth(STT_HARM_TABLE_COL_Amp,88);
// 	this->setColumnWidth(STT_HARM_TABLE_COL_Phase,88);
// 	this->setColumnWidth(STT_HARM_TABLE_COL_HarmRate,140);
/*	setHorizontalHeaderLabels(headers);*/

	int nSelCount = 0;//勾选总谐波数
	
	for (int row = 0;  row  <  nMaxRowCount;  row++)
	{
		for (int col  =  0;  col  <  HarmColunmCount;  col++)
		{
			pCurrHarmItem = new QSettingItem(this);//QTableWidgetItem;	//20240624 huangliang

			if(col == STT_HARM_TABLE_COL_Select)
			{
				pCurrHarmItem->setFlags(pCurrHarmItem->flags() & (~Qt::ItemIsEditable));

				if (nSelCount > 30)//2024-9-5 wuxinyi 目前只支持30次谐波
				{
					m_pArrUI[m_nChIndex].Harm[row].m_bSelect = FALSE;
				}

				if (m_pArrUI[m_nChIndex].Harm[row].m_bSelect)
				{
					nSelCount++;
					pCurrHarmItem->setCheckState(Qt::Checked);
				} 
				else
				{
					pCurrHarmItem->setCheckState(Qt::Unchecked);
				}
				// 				if (row == STT_HARM_TABLE_ROW_DC)
				// 				{
				// 					pCurrHarmItem->setCheckState(Qt::Checked);
				// 				}
				// 				else if (row == STT_HARM_TABLE_ROW_Base)
				// 				{
				// 					pCurrHarmItem->setCheckState(Qt::Checked);
				// 					pCurrHarmItem->setFlags(Qt::NoItemFlags);
				// 					setSelect(row  -  1,  true);							//初始化基波始终使能
				// 				}
				// 				else
				// 				{
				// 					if (m_pArrUI[m_nChIndex].Harm[row - 1].m_bSelect  && row <= 30)
				// 					{
				// 						pCurrHarmItem->setCheckState(Qt::Checked);
				// 					}
				// 					else
				// 					{
				// 						pCurrHarmItem->setCheckState(Qt::Unchecked);
				// 					}
				// 				}
			}
			else if(col == STT_HARM_TABLE_COL_Desc)
			{
				pCurrHarmItem->setTextColor(QColor(0, 0, 0));
				pCurrHarmItem->setFlags(Qt::NoItemFlags);

				if (row == STT_HARM_TABLE_ROW_DC)
				{
					CString str;
					xlang_GetLangStrByFile(str, "Native_DC");
					pCurrHarmItem->setText(str);
				}
				else if (row == STT_HARM_TABLE_ROW_Base)
				{
					CString str;
					xlang_GetLangStrByFile(str, "Native_Fundamental");
					pCurrHarmItem->setText(str);
				}
				else
				{
					CString strHarmCount;
					xlang_GetLangStrByFile(strHarmCount, "Harm_Times");

					CString strHarm;
					if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
					{
						strHarm.Format("%d",row);
						strHarm += strHarmCount;
					}
					else
					{
						strHarm.Format("%d",row);
						strHarm = strHarmCount + strHarm;
						//strHarm = QString("Harm %1").arg(row);
					}

					pCurrHarmItem->setText(strHarm);
				}
			}

			pCurrHarmItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			this->setItem(row,   col,  pCurrHarmItem);
		}
	}

	getSelectHarmStringList(m_HarmStringList);
	changeColor();
	updataTableData();
}

void QHarmTable::changeColor()
{  
	for (int i = 2;i < this->rowCount();i++)  
	{  
		if (i % 2 == 0)  
		{  
			for (int j = 0;j < this->columnCount();j++)  
			{  
				QTableWidgetItem *item = this->item(i,  j);  
				if (item)  
				{  
					const QColor color = QColor(240,240,240);  
					item->setBackgroundColor(color);  
				}  
			}  
		}  
	} 
}

void QHarmTable::updataTableData(long  nHarmIndex)
{
	disconnect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,  int)));
	disconnect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)));
	long nMaxRowCount = Global_GetHarmTableMaxRowCount();

	for(int i  =  0;  i  <  nMaxRowCount; i++)
	{
		if ((nHarmIndex != i)&&(nHarmIndex>=0))
		{
			continue;
		}

		QString strValue;
		float fValueTemp = m_pArrUI[m_nChIndex].Harm[i].fAmp;

		if (g_oSystemParas.m_nHasAnalog == 1)
		{
			if (m_pArrUI[m_nChIndex].Harm[i].fAmp >= 1200)	
			{
				fValueTemp = 130;	
				m_pArrUI[m_nChIndex].Harm[i].fAmp = 130;
			}
		}

		if (m_pChResource->m_strName.Find('U') >= 0)
		{
			if (m_pArrUI[m_nChIndex].Harm[i].fAmp > g_oLocalSysPara.m_fAC_VolMax)	
			{
				fValueTemp = g_oLocalSysPara.m_fAC_VolMax;	
				m_pArrUI[m_nChIndex].Harm[i].fAmp = g_oLocalSysPara.m_fAC_VolMax;
			}
		}
		else if (m_pArrUI[m_nChIndex].Harm[i].fAmp > g_oLocalSysPara.m_fAC_CurMax)	
		{
			fValueTemp = g_oLocalSysPara.m_fAC_CurMax;	
			m_pArrUI[m_nChIndex].Harm[i].fAmp = g_oLocalSysPara.m_fAC_CurMax;
		}

		//20240626 huangliang
		//item(i, STT_HARM_TABLE_COL_Amp)->setText(QString::number(fValueTemp,  'f',  3));
		//item(i, STT_HARM_TABLE_COL_Phase)->setText(QString::number(m_pArrUI[m_nChIndex].Harm[i].fAngle, 'f', 1));
		//item(i, STT_HARM_TABLE_COL_HarmRate)->setText(QString::number(m_pArrUI[m_nChIndex].Harm[i].fContent,  'f',  2));
		((QSettingItem*)item(i, STT_HARM_TABLE_COL_Amp))->UpdateStructText(CVariantDataAddress(&m_pArrUI[m_nChIndex].Harm[i].fAmp), 3);
		((QSettingItem*)item(i, STT_HARM_TABLE_COL_Phase))->UpdateStructText(CVariantDataAddress(&m_pArrUI[m_nChIndex].Harm[i].fAngle), 1);
		((QSettingItem*)item(i, STT_HARM_TABLE_COL_HarmRate))->UpdateStructText(CVariantDataAddress(&m_pArrUI[m_nChIndex].Harm[i].fContent), 2);
	}

	item(STT_HARM_TABLE_ROW_Base, STT_HARM_TABLE_COL_HarmRate)->setText(QString::number(100, 'f', 1));
	item(STT_HARM_TABLE_ROW_DC, STT_HARM_TABLE_COL_HarmRate)->setFlags(Qt::NoItemFlags);
// 	item(MAX_HARM_COUNT_UI, 2 )->setText(QString::number(0,  'f',  3));
// 	item(MAX_HARM_COUNT_UI, 3 )->setText(QString::number(0, 'f', 1));
// 	item(MAX_HARM_COUNT_UI, 4 )->setText(QString::number(0,  'f',  2));
// 	item(MAX_HARM_COUNT_UI + 1, 2 )->setText(QString::number(0,  'f',  3));
// 	item(MAX_HARM_COUNT_UI + 1, 3 )->setText(QString::number(0, 'f', 1));
// 	item(MAX_HARM_COUNT_UI + 1, 4 )->setText(QString::number(0,  'f',  2));
	
	connect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));
	connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemDoubleClicked(QTableWidgetItem *)),Qt::UniqueConnection);
}
void QHarmTable::setSelect(int nHarmIndex, bool bSel)
{
	m_pArrUI[m_nChIndex].Harm[nHarmIndex].m_bSelect = bSel;
}

void QHarmTable::scrollPosToItem(int nHarmIndex)
{
	int num = nHarmIndex;
	if (num == 0)
	{//基波
		scrollToTop();
	}
	else
	{
		if (num < 10)
		{
			num = 5;
		}
		else if (num > 43)
		{
			num = 45;
		}
		else
		{
			num = num+3;
		}

		scrollToItem(item(num,0));
	}
}

void QHarmTable::UpdateText(const QString &strText)
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
	//emit sig_ChannelValueChanged(m_moudleType,nRow,nCol, m_pCurrKeyboardItem->text().toFloat());//valueFlag=（1:幅值 2:相位 3:频率）
}

void QHarmTable::slot_OnCellChanged( int nRow,int nCol)
{
	if (nRow  <  0)
	{
		return;
	}

	//20240624 huangliang 
	//QTableWidgetItem*  pItem  =  item(nRow,  nCol);
	QSettingItem*  pItem  =  (QSettingItem*)item(nRow,  nCol);

	if (pItem == NULL)
	{
		return;
	}

	bool bIsU = false;
	if (m_pChResource->m_strName.Find('U') >= 0)
	{
		bIsU = true;
	}

	QString strEnterValue = pItem->text();
	float  fEnterValue = strEnterValue.toFloat();

	if (nCol == STT_HARM_TABLE_COL_Amp)
	{
		//直流的时候；
		if (nRow == STT_HARM_TABLE_ROW_DC/*1*/) //zhouhj 20220816 第0行为直流
		{
			if (bIsU)
			{
				if (fEnterValue  >  g_oLocalSysPara.m_fDC_VolMax)
				{
					//20240624 huangliang
					//pItem->setText(QString::number(g_oLocalSysPara.m_fDC_VolMax,  'f', 2));
					pItem->UpdateStructText(CVariantDataAddress(&g_oLocalSysPara.m_fDC_VolMax), 2);
					//QString strTemp =  tr("输入的电压超出范围") + QString::number(g_oLocalSysPara.m_fDC_VolMax,  'f', 2) + tr("V !");
#ifdef _PSX_QT_WINDOWS_
					CString strTemp = g_sLangTxt_State_InVolOutofRange.GetString();
					strTemp.AppendFormat("%.3f", g_oLocalSysPara.m_fDC_VolMax);
					strTemp += _T("V");
#else
                    QString strTemp =  g_sLangTxt_State_InVolOutofRange.GetString() + QString::number(g_oLocalSysPara.m_fDC_VolMax,  'f', 2) + tr("V !"); //输入的电压超出范围 lcq 3.14
#endif // _PSX_QT_WINDOWS_
					CLogPrint::LogString(XLOGLEVEL_ERROR,strTemp);
					return;
				}
			}
			else
			{
				if (fEnterValue  > g_oLocalSysPara.m_fDC_CurMax)
				{
					//20240624 huangliang
					//pItem->setText(QString::number(g_oLocalSysPara.m_fDC_CurMax,  'f', 2));
					pItem->UpdateStructText(CVariantDataAddress(&g_oLocalSysPara.m_fDC_CurMax), 2);
					//QString strTemp =  tr("输入的电流超出范围") + QString::number(g_oLocalSysPara.m_fDC_CurMax,  'f', 2) + tr("A !");
#ifdef _PSX_QT_WINDOWS_
					CString strTemp = g_sLangTxt_State_InCurOutofrange.GetString();
					strTemp.AppendFormat("%.3f", g_oLocalSysPara.m_fDC_CurMax);
					strTemp += _T("A");
#else
                    QString strTemp =  g_sLangTxt_State_InCurOutofrange.GetString() + QString::number(g_oLocalSysPara.m_fDC_CurMax,  'f', 2) + tr("A !");//输入的电流超出范围lcq 3.14
#endif // _PSX_QT_WINDOWS_
					CLogPrint::LogString(XLOGLEVEL_ERROR,strTemp);
					return;
				}
			}
		}
		else
		{
			if (bIsU)
			{

				if (fEnterValue  >  g_oLocalSysPara.m_fAC_VolMax)
				{
					//20240624 huangliang
					//pItem->setText(QString::number(g_oLocalSysPara.m_fAC_VolMax,  'f', 2));
					pItem->UpdateStructText(CVariantDataAddress(&g_oLocalSysPara.m_fAC_VolMax), 2);
					//QString strTemp =  tr("输入的电压超出范围") + QString::number(g_oLocalSysPara.m_fAC_VolMax,  'f', 2) + tr("V !");
#ifdef _PSX_QT_WINDOWS_
					CString strTemp = g_sLangTxt_State_InVolOutofRange.GetString();
					strTemp.AppendFormat("%.3f",g_oLocalSysPara.m_fDC_VolMax);
					strTemp += _T("V");
#else
                    QString strTemp =  g_sLangTxt_State_InVolOutofRange.GetString() + QString::number(g_oLocalSysPara.m_fDC_VolMax,  'f', 2) + tr("V !"); //输入的电压超出范围 lcq 3.14
#endif // _PSX_QT_WINDOWS_
					CLogPrint::LogString(XLOGLEVEL_ERROR,strTemp);
					return;
				}
			}
			else
			{
				if (fEnterValue  > g_oLocalSysPara.m_fAC_CurMax)
				{
					//20240624 huangliang
					//pItem->setText(QString::number(g_oLocalSysPara.m_fAC_CurMax,  'f', 2));
					pItem->UpdateStructText(CVariantDataAddress(&g_oLocalSysPara.m_fAC_CurMax), 2);
					//QString strTemp =  tr("输入的电流超出范围") + QString::number(g_oLocalSysPara.m_fAC_CurMax,  'f', 2) + tr("A !");
#ifdef _PSX_QT_WINDOWS_
					CString strTemp = g_sLangTxt_State_InCurOutofrange.GetString();
					strTemp.AppendFormat("%.3f",g_oLocalSysPara.m_fDC_CurMax);
					strTemp += _T("A");
#else
                    QString strTemp =  g_sLangTxt_State_InCurOutofrange.GetString() + QString::number(g_oLocalSysPara.m_fDC_CurMax,  'f', 2) + tr("A !");//输入的电流超出范围lcq 3.14
#endif // _PSX_QT_WINDOWS_
					CLogPrint::LogString(XLOGLEVEL_ERROR,strTemp);
					return;
				}
			}
		}
	}
	
	bool bChanged  = false;
	disconnect(this, SIGNAL(cellChanged ( int ,  int )),    this, SLOT(slot_OnCellChanged(int ,  int)));

	if (nCol == STT_HARM_TABLE_COL_Select)
	{
		getSelectHarmStringList(m_HarmStringList);

		if (pItem->checkState() != Qt::Unchecked)
		{
			//当获得的选择的行的数量大于等于31时直接返回，不能择
			long nCount = g_oLocalSysPara.m_nMaxHarmCount + 2;

			if(g_oSystemParas.m_nHasDigital)
			{
				nCount--;
			}

//			if (GetSelectCount() >= nCount)
//			{			
//				pItem->setCheckState(Qt::Unchecked);	
//				connect(this,   SIGNAL(cellChanged ( int ,  int )),   this,  SLOT(slot_OnCellChanged(int ,  int)));
				//QString str = tr("你总计只能选择30次谐波，假如想选择当前次谐波，需要取消勾选一行！");

				//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, 
				//	"总计只能选择%d次谐波，假如想选择当前次谐波，需要取消勾选一行.", nCount - 2);
//                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_Gradient_Intotalcheckarow.GetString(), nCount - 2); //总计只能选择%d次谐波，假如想选择当前次谐波，需要取消勾选一行. lcq 3.14
//				return;
//			}

			if (GetHarmSelCount() > 30)//2024-9-5 wuxinyi 目前只支持30次谐波
			{			
				pItem->setCheckState(Qt::Unchecked);	
				connect(this,   SIGNAL(cellChanged ( int ,  int )),   this,  SLOT(slot_OnCellChanged(int ,  int)));

				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_Gradient_Intotalcheckarow.GetString(), 30/*nCount - 2*/);

				return;
			}

			setSelect(nRow,  true);
		}
		else
		{
			setSelect(nRow,  false);
		}

		bChanged  =  true;
		UpdateHeaderView();

// 		if (m_nChangeFlag==0)
// 		{
// 			emit sig_CheckStateChanged();
// 		}
		emit sig_ChanelValueChanged();	
	}
	else if (nCol > STT_HARM_TABLE_COL_Desc)
	{
		switch(nCol)
		{
		case STT_HARM_TABLE_COL_Amp:
			bChanged = AmplitudeCellChanged(nRow,  nCol);
			break;
		case STT_HARM_TABLE_COL_Phase:
			bChanged = PhaseCellChanged(nRow,  nCol);
			break;
		case STT_HARM_TABLE_COL_HarmRate:
			bChanged = ContainRateCellChanged(nRow,  nCol);
			break;
		default:
			break;
		}

//		if (m_nChangeFlag == 0)
			emit sig_ChanelValueChanged();		

		emit sig_WaveValueChanged();   

/******************************************************************************************************************************************************************************************
		说明：sig_ChanelValueChanged   sig_WaveValueChanged  这两个信号的区别是一个连接到主框架，一个没有连接到主框架，只用来更新图形。
******************************************************************************************************************************************************************************************/

		//2024-8-6 wuxinyi 在判断谐波通道勾选时也需更新谐波图，故挪至判断之外
// 		if (bChanged)	
// 			emit sig_ChIndexChanged(m_nChIndex);
	}

	if (bChanged)
			emit sig_ChIndexChanged(m_nChIndex);

	if(g_oSystemParas.m_nHasAnalog || g_oSystemParas.m_nHasWeek)
	{
		//在存在模拟的情况下如果基波变化，需要重新确定谐波的最大值
// 		if(nRow == STT_HARM_TABLE_ROW_Base && nCol == STT_HARM_TABLE_COL_Amp)//20220817 zhouhj 去除设置基波后,修改各次谐波的幅值,不超过基波
// 		{
// 			for (int i = 2; i < MAX_HARM_COUNT; i++)
// 			{
// 				if(m_pArrUI[m_nChIndex].Harm[i].fAmp > m_pArrUI[m_nChIndex].Harm[1].fAmp)
// 				{
// 					m_pArrUI[m_nChIndex].Harm[i].fAmp = m_pArrUI[m_nChIndex].Harm[1].fAmp;
// 					QTableWidgetItem* pItem  = item(i,  nCol);
// 					pItem->setText(QString::number(m_pArrUI[m_nChIndex].Harm[i].fAmp));
// 				}	
// 			}
// 		}
// 		else
// 		{
// 			//在存在模拟的情况下输入值不能大于基波值
// 			if(m_pArrUI[m_nChIndex].Harm[nRow].fAmp > m_pArrUI[m_nChIndex].Harm[1].fAmp)//20220817 zhouhj 去除设置非基波后,各次谐波的幅值不超过基波
// 			{
// 				m_pArrUI[m_nChIndex].Harm[nRow].fAmp = m_pArrUI[m_nChIndex].Harm[1].fAmp;
// 				QTableWidgetItem* pItem  = item(nRow,  nCol);
// 				pItem->setText(QString::number(m_pArrUI[m_nChIndex].Harm[nRow].fAmp));
// 			}
// 		}
	}

	connect(this,   SIGNAL(cellChanged ( int ,  int )),   this,  SLOT(slot_OnCellChanged(int ,  int)));

	emit sig_updataParas();
}

void QHarmTable::slot_UpdataVamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	MenuFunc_EqualAmp(pItem,strValue);
	
	//slot_ActUEqualAmpClicked();
}

void QHarmTable::MenuFunc_EqualAmp(QTableWidgetItem *pItem,const QString &strValue)
{
	if ((m_pArrUI == NULL)||(m_nChIndex >= MAX_VOLTAGE_COUNT))
	{
		return;
	}

	long nFirstChIndex = m_nChIndex/3;
	nFirstChIndex *= 3;
	double dCurrValue = strValue.toDouble();
	m_pArrUI[nFirstChIndex].Harm[1].fAmp = dCurrValue;
	m_pArrUI[nFirstChIndex+1].Harm[1].fAmp = dCurrValue;
	m_pArrUI[nFirstChIndex+2].Harm[1].fAmp = dCurrValue;
}

void QHarmTable::MenuFunc_PositiveSequence(QTableWidgetItem *pItem,const QString &strValue)
{
	if ((m_pArrUI == NULL)||(m_nChIndex >= MAX_VOLTAGE_COUNT))
	{
		return;
	}

	long nFirstChIndex = m_nChIndex/3;
	nFirstChIndex *= 3;
	long nCurrRemainder = m_nChIndex%3;
	float fCurrValue = strValue.toFloat();

	if (nCurrRemainder == 1)
	{
		fCurrValue += 120;
		LimitAngle360(fCurrValue);
	}
	else if (nCurrRemainder == 2)
	{
		fCurrValue -= 120;
		LimitAngle360(fCurrValue);
	}
	m_pArrUI[nFirstChIndex].Harm[1].fAngle = fCurrValue;
	fCurrValue -= 120;
	LimitAngle360(fCurrValue);
	m_pArrUI[nFirstChIndex+1].Harm[1].fAngle = fCurrValue;
	fCurrValue -= 120;
	LimitAngle360(fCurrValue);
	m_pArrUI[nFirstChIndex+2].Harm[1].fAngle = fCurrValue;
}

void QHarmTable::MenuFunc_NegativeSequence(QTableWidgetItem *pItem,const QString &strValue)
{
	if ((m_pArrUI == NULL)||(m_nChIndex >= MAX_VOLTAGE_COUNT))
	{
		return;
	}

	long nFirstChIndex = m_nChIndex/3;
	nFirstChIndex *= 3;
	long nCurrRemainder = m_nChIndex%3;
	float fCurrValue = strValue.toFloat();

	if (nCurrRemainder == 1)
	{
		fCurrValue -= 120;
		LimitAngle360(fCurrValue);
	}
	else if (nCurrRemainder == 2)
	{
		fCurrValue += 120;
		LimitAngle360(fCurrValue);
	}
	m_pArrUI[nFirstChIndex].Harm[1].fAngle = fCurrValue;
	fCurrValue += 120;
	LimitAngle360(fCurrValue);
	m_pArrUI[nFirstChIndex+1].Harm[1].fAngle = fCurrValue;
	fCurrValue += 120;
	LimitAngle360(fCurrValue);
	m_pArrUI[nFirstChIndex+2].Harm[1].fAngle = fCurrValue;
}

void QHarmTable::MenuFunc_ZeroSequence(QTableWidgetItem *pItem)
{
	if ((m_pArrUI == NULL)||(m_nChIndex >= MAX_VOLTAGE_COUNT))
	{
		return;
	}

	long nFirstChIndex = m_nChIndex/3;
	nFirstChIndex *= 3;
	m_pArrUI[nFirstChIndex].Harm[1].fAngle = 0.0f;
	m_pArrUI[nFirstChIndex+1].Harm[1].fAngle = 0.0f;
	m_pArrUI[nFirstChIndex+2].Harm[1].fAngle = 0.0f;
}

void QHarmTable::slot_UpdataIamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	MenuFunc_EqualAmp(pItem,strValue);
	//slot_ActIqualAmpClicked();
}

void QHarmTable::slot_UpdataHzamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	//slot_ActHzEqualClicked();
}

void QHarmTable::slot_UpdataZX(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	MenuFunc_PositiveSequence(pItem,strValue);
	//slot_ActPhasePClicked();
}

void QHarmTable::slot_UpdataFX(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	MenuFunc_NegativeSequence(pItem,strValue);
	//slot_ActPhaseNClicked();
}

void QHarmTable::slot_UpdataLX()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText("0");
	MenuFunc_ZeroSequence(pItem);
	//slot_ActPhaseZClicked();
}

void QHarmTable::slot_OnItemDoubleClicked( QTableWidgetItem *pItem )
{
	int nRow = row(pItem);
	int nCol = column(pItem) - 1;

	if ( nCol == -1)
	{
		return;
	}

	if(!nCol)
	{
		return;
	}

	CString strValue = pItem->text();

	long nEditType = 4;//数字键盘
	if (nRow == 1)
	{
		if (nCol == 1)//只有在基波行(第一行),幅值列,支持等幅值
		{
			if(m_pChResource->m_strName.Find('U') >= 0)
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
			nEditType = 2;//相位键盘
		}
		else if (nCol == 3)
		{
			nEditType = 4;//数字键盘
		}
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::Attach330Channel(this, nEditType);
#endif
	
	m_pCurrKeyboardItem = pItem;
}

long QHarmTable::GetSelectCount()
{
	long nCount = 0;
	
	QTableWidgetItem* pItem  = NULL;
	long nMaxRowCount = Global_GetHarmTableMaxRowCount();

	for(int nRow = 0; nRow < nMaxRowCount;nRow++)
	{
		pItem  = item(nRow,  0);

		if (pItem->checkState() != Qt::Unchecked)
		{
			nCount++;
		}
	}

	return nCount;
}

long QHarmTable::GetHarmSelCount()
{
	long nCount = 0;

	QTableWidgetItem* pItem = NULL;
	long nMaxRowCount = Global_GetHarmTableMaxRowCount();

	for (int nRow = 1; nRow < nMaxRowCount; nRow++)
	{
		pItem = item(nRow, 0);

		if (pItem->checkState() != Qt::Unchecked)
		{
			nCount++;
		}
	}

	return nCount;

}

void QHarmTable::Disconnect()
{
	disconnect(this,  SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,  int)));
}
bool QHarmTable::ContainRateCellChanged( int nRow,int nCol )
{
	if (nRow <  0)
	{
		return false;
	}

	bool bChanged  =  false;

	QTableWidgetItem* pItem  =  this->item(nRow,   nCol);

	if (pItem == NULL)
	{
		return false;
	}

	disconnect(this,  SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,  int)));

	tmt_ChannelHarm *pChannelHarm = &m_pArrUI[m_nChIndex].Harm[nRow];

	if(nRow == 0)
	{
		//pChannelHarm->fContent = 100;
		//item(nRow,   nCol)->setText("100");
	}
	else if(nRow == 1)
	{
		pChannelHarm->fContent = 100;
		item(nRow,   nCol)->setText("100");
	}
	else
	{
		QString str =  pItem->text();
		float fhyl   = pItem->text().toFloat();
		if (fhyl >= 100)
		{
			fhyl = 100;
		}
		if (str == "" || fhyl <= EPSINON)
		{
			fhyl = 0;
			item(nRow,  nCol)->setText(QString::number(0,  'f',  2));
		}

		float fBackContain  =  pChannelHarm->fContent;
		float fBackValue   =  pChannelHarm->fAmp;

		pChannelHarm->fContent   =  fhyl;
		pChannelHarm->fAmp   =   fhyl  *  0.01  * m_pArrUI[m_nChIndex].Harm[1].fAmp;

		bChanged = true;
		UpdateHeaderView();

		//20240624 huangliang
		//item(nRow,nCol)->setText(QString::number(pChannelHarm->fContent,  'f',  2));
		//item(nRow,nCol-2)->setText(QString::number(pChannelHarm->fAmp ,  'f',  3));
		((QSettingItem*)item(nRow,nCol))->UpdateStructText(CVariantDataAddress(&pChannelHarm->fContent), 2);
		((QSettingItem*)item(nRow,nCol-2))->UpdateStructText(CVariantDataAddress(&pChannelHarm->fAmp), 3);
	}
	connect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));

	return bChanged;
}	

bool QHarmTable::AmplitudeCellChanged( int nRow,  int nCol )
{
	if (nRow <  0)
	{
		return false;
	}

	QTableWidgetItem* pItem  = item(nRow,  nCol);
	if (pItem == NULL)
	{
		return false;
	}

	disconnect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));

	bool bChanged = false;
	QString str =  pItem->text();
	float fYxz = pItem->text().toFloat();
	long nMaxRowCount = Global_GetHarmTableMaxRowCount();

	if ((str == "" || fYxz <= EPSINON)  && nRow != 1 )
	{
		fYxz = 0;
		item(nRow,nCol)->setText(QString::number(0,   'f',  3));
	}

	if (nRow == 0)//直流
	{
		float fBackAmp = m_pArrUI[m_nChIndex].Harm[0].fAmp;
		m_pArrUI[m_nChIndex].Harm[0].fAmp  =  fYxz;

		bChanged = true;
	}
	else if (nRow == 1)//基波
	{
		float fBackAmp = m_pArrUI[m_nChIndex].Harm[1].fAmp;
		m_pArrUI[m_nChIndex].Harm[1].fAmp  =  fYxz;

		QString strTemp;
		for (int i  =  1; i < nMaxRowCount; i++)
		{
			m_pArrUI[m_nChIndex].Harm[i].fContent  =  m_pArrUI[m_nChIndex].Harm[i].fAmp * 100 / m_pArrUI[m_nChIndex].Harm[1].fAmp;

			//20240624 huangliang
			//item(i,  nCol + 2)->setText(QString::number(m_pArrUI[m_nChIndex].Harm[i].fContent,  'f',  2));
			((QSettingItem*)item(i,  nCol + 2))->UpdateStructText(CVariantDataAddress(&m_pArrUI[m_nChIndex].Harm[i].fContent), 2);

		}
		bChanged = true;
		UpdateHeaderView();
	}
	else
	{
		float fBackAmp = m_pArrUI[m_nChIndex].Harm[nRow].fAmp;
		float fBackContain = m_pArrUI[m_nChIndex].Harm[nRow].fContent;

		m_pArrUI[m_nChIndex].Harm[nRow].fAmp = fYxz;
		m_pArrUI[m_nChIndex].Harm[nRow].fContent = fYxz  * 100  / m_pArrUI[m_nChIndex].Harm[1].fAmp;

 		bChanged = true;
		UpdateHeaderView();

		//20240624 huangliang
		//item(nRow, nCol)->setText(QString::number(m_pArrUI[m_nChIndex].Harm[nRow].fAmp,   'f',  3));
		//item(nRow, nCol + 2)->setText(QString::number(m_pArrUI[m_nChIndex].Harm[nRow].fContent,  'f',  2));
		((QSettingItem*)item(nRow,nCol))->UpdateStructText(CVariantDataAddress(&m_pArrUI[m_nChIndex].Harm[nRow].fAmp), 3);
		((QSettingItem*)item(nRow,nCol + 2))->UpdateStructText(CVariantDataAddress(&m_pArrUI[m_nChIndex].Harm[nRow].fContent), 2);
	}

	connect(this, SIGNAL(cellChanged ( int , int )),  this, SLOT(slot_OnCellChanged(int ,int)));

	return bChanged;
}


bool QHarmTable::PhaseCellChanged( int nRow,int nCol )
{
	if (nRow  <  0)
	{
		return false;
	}
	QTableWidgetItem* pItem  = item(nRow,  nCol);
	if (pItem == NULL)
	{
		return false;
	}

	disconnect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));

	bool bChanged = false;
	QString str =  pItem->text();
	float fXW = pItem->text().toFloat();
	LimitAngle360(fXW);

	if (nRow == 0)//直流
	{
		m_pArrUI[m_nChIndex].Harm[0].fAngle  =  fXW;
		bChanged = true;
	}
	else if (nRow == 1)//基波
	{
		m_pArrUI[m_nChIndex].Harm[1].fAngle  =  fXW;
		bChanged = true;
	}
	else
	{
		m_pArrUI[m_nChIndex].Harm[nRow].fAngle    =   fXW;
		bChanged = true;
	}

	item(nRow,  nCol)->setText(QString::number(fXW, 'f', 1));
	connect(this, SIGNAL(cellChanged ( int , int )),  this, SLOT(slot_OnCellChanged(int ,int)));

	return bChanged;
}


bool QHarmTable::addClicked(int harmNum,float fv )
{
	disconnect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));
	
	bool bChanged = false;

	int col = 2;

	float fValue = item(harmNum,col)->text().toFloat();
	fValue = fValue+fv;

	item(harmNum,col)->setText(QString::number(fValue,'f',3));
	bChanged = AmplitudeCellChanged(harmNum,col); 

	connect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));

	return bChanged;
}

bool QHarmTable::delClicked(int harmNum,float fv )
{
	disconnect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));
	
	bool bChanged = false;
	int col = 2;

	float fValue = item(harmNum,col)->text().toFloat();
	float fNewV = fValue - fv;
	if (fNewV < 0 )
	{
		fNewV = 0;
	}

	item(harmNum,col)->setText(QString::number(fNewV,'f',3));
	bChanged = AmplitudeCellChanged(harmNum,col); 

	connect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));

	return bChanged;
}

void QHarmTable::setZero( int index )
{
	disconnect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));

	int col = 2;

	for (int i  =  2;  i  <  this->rowCount();  i++)
	{
		item(i,  col)->setText(QString::number(0,  'f',  3));
		AmplitudeCellChanged(i,  col); 
	}		

	connect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int,  int)));

//	if (m_nChangeFlag == 0)
		emit sig_ChanelValueChanged();
}


void QHarmTable::getSelectHarmStringList( QStringList & list )
{
	list.clear();
	QTableWidgetItem* pItem  = NULL;
	long nCheckValue = 0;


	for (int i  =  0;  i  <  this->rowCount(); i++)
	{
		pItem = item(i,  0);
		nCheckValue = pItem->checkState();
		if (nCheckValue != Qt::Unchecked)
		{
			if (i == 0)
			{
				//list.append(tr("直流"));
                list.append(g_sLangTxt_Native_DC); //直流 lcq  3.14
			}
			else if (i == 1)
			{
				//list.append(tr("基波")); 
                list.append(g_sLangTxt_Native_Fundamental); //基波 lcq  3.14
			}
			else
			{
				//list.append(QString(tr("%1次谐波")).arg(i));
                list.append(g_sLangTxt_State_TheOnepercentHarmonic); //%1次谐波 lcq  3.14
			}
		}
	}
}

bool QHarmTable::UpdateCacuParaOneChanel(CSttChResource *pChResource, long nGroupChIndex)
{
	long nAllChIndex = pChResource->GetChIndex_FromZero();
	//总有效值
	float m_fTotal = 0; //限制
	float fTotal = 0;

	long nMaxHarmNum = g_oLocalSysPara.m_nMaxHarmCount;

	if (nMaxHarmNum > MAX_HARM_COUNT)
	{
		nMaxHarmNum = MAX_HARM_COUNT;
		g_oLocalSysPara.m_nMaxHarmCount = MAX_HARM_COUNT;
	}


	for (int i = 0; i < nMaxHarmNum; i++)
	{
		if (m_pArrUI[nAllChIndex].Harm[i].m_bSelect)
		{
			m_fTotal += m_pArrUI[nAllChIndex].Harm[i].fAmp;
			fTotal += m_pArrUI[nAllChIndex].Harm[i].fAmp * m_pArrUI[nAllChIndex].Harm[i].fAmp;
		}
	}
	m_fTotal += m_pArrUI[nAllChIndex].Harm[0].fAmp;
	fTotal = sqrt(fTotal);
	fTotal += m_pArrUI[nAllChIndex].Harm[0].fAmp;

	CString strInfo;

	QString strZ = QString::number(fTotal, 'f', 3);

	return true;

}

float QHarmTable::UpdateCacuParaOneChanel()
{
	long nAllChIndex = m_pChResource->GetChIndex_FromZero();
	//总有效值
	float m_fTotal = 0; //限制
	float fTotal = 0;

	long nMaxHarmNum = g_oLocalSysPara.m_nMaxHarmCount;

	if (nMaxHarmNum > MAX_HARM_COUNT)
	{
		nMaxHarmNum = MAX_HARM_COUNT;
		g_oLocalSysPara.m_nMaxHarmCount = MAX_HARM_COUNT;
	}


	for (int i = 0; i < nMaxHarmNum; i++)
	{
		if (m_pArrUI[nAllChIndex].Harm[i].m_bSelect)
		{
			m_fTotal += m_pArrUI[nAllChIndex].Harm[i].fAmp;
			fTotal += m_pArrUI[nAllChIndex].Harm[i].fAmp * m_pArrUI[nAllChIndex].Harm[i].fAmp;
		}
	}
	m_fTotal += m_pArrUI[nAllChIndex].Harm[0].fAmp;
	fTotal = sqrt(fTotal);
	fTotal += m_pArrUI[nAllChIndex].Harm[0].fAmp;

	return fTotal;
}

void QHarmTable::UpdateHeaderView()
{
	QStringList headers;

	CString strEnable, strChannel, strAmplitude, strPhase, strContent;//使能，通道，幅值，相位，谐波含有率
	xlang_GetLangStrByFile(strEnable, "Harm_Enable");
	strChannel = m_pChResource->m_strName;
	xlang_GetLangStrByFile(strAmplitude, "Native_Amplitude");
	xlang_GetLangStrByFile(strPhase, "Native_Angle");
	xlang_GetLangStrByFile(strContent, "Harm_Content");

	CString strUnit;
	if (strChannel.Find('U') >= 0)
	{
		strUnit += "(V)";
	}
	else
		strUnit += "(A)";

	strAmplitude += strUnit;
#ifndef _PSX_QT_LINUX_
	strPhase += QString::fromLocal8Bit("(°)");

	float fValue = UpdateCacuParaOneChanel();
	if (abs(fValue > 0.00001))
	{
		CString strZ = QString::number(fValue, 'f', 3);
		CString strValdValue = g_sLangTxt_Native_ValdValue.GetString();

		strChannel += _T("\n");
		strChannel += strValdValue;
		strChannel += _T(":");
		strChannel += strZ;
		strChannel += strUnit;

		QDesktopWidget* desktopWidget = QApplication::desktop();
		QRect rect = desktopWidget->screenGeometry();
		float fWidth = rect.width();

		if (fWidth >= 2240)
		{
			this->setColumnWidth(STT_HARM_TABLE_COL_Select, 50);
			this->setColumnWidth(STT_HARM_TABLE_COL_Desc, 140);
			this->setColumnWidth(STT_HARM_TABLE_COL_Amp, 80);
			this->setColumnWidth(STT_HARM_TABLE_COL_Phase, 80);
			this->setColumnWidth(STT_HARM_TABLE_COL_HarmRate, 130);
		}
		else
		{
			this->setColumnWidth(STT_HARM_TABLE_COL_Select, 50);
			this->setColumnWidth(STT_HARM_TABLE_COL_Desc, 120);
			this->setColumnWidth(STT_HARM_TABLE_COL_Amp, 60);
			this->setColumnWidth(STT_HARM_TABLE_COL_Phase, 60);
			this->setColumnWidth(STT_HARM_TABLE_COL_HarmRate, 100);
		}
	}
#else
	strPhase += "(°)";

	this->setColumnWidth(STT_HARM_TABLE_COL_Select, 50);
	this->setColumnWidth(STT_HARM_TABLE_COL_Desc, 60);
	this->setColumnWidth(STT_HARM_TABLE_COL_Amp, 88);
	this->setColumnWidth(STT_HARM_TABLE_COL_Phase, 88);
	this->setColumnWidth(STT_HARM_TABLE_COL_HarmRate, 140);
#endif
	strContent += "(%)";

	headers << strEnable << strChannel << strAmplitude << strPhase << strContent;

	setHorizontalHeaderLabels(headers);
}

/*
bool QHarmTable::SetAllSelected(bool bSel)
{
	disconnect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));

	bool bChange   =   true;
	int nChs   = m_oGroupResourceRef.GetCount();
	long nHeadChIndex   =  m_oGroupResourceRef.GetHeadChIndex_FromZero();
	tmt_Channel *pbackPara = new tmt_Channel[nChs];
	memcpy(pbackPara,  &m_pArrUI[nHeadChIndex],   sizeof(tmt_Channel)*nChs);

	for (int i  =  3; i <  this->rowCount();i++)
	{
		if (bSel)
		{
			item(i,0)->setCheckState(Qt::Checked);
		}
		else
		{
			item(i,0)->setCheckState(Qt::Unchecked);
		}

		setSelect(i-1,bSel);	
	}

	getSelectHarmStringList(m_HarmStringList);
	//emit sig_CheckAllClicekd();
	bChange = UpdateCacuPara();

	if (!bChange)
	{
		//计算越界恢复
		memcpy(&m_pArrUI[nHeadChIndex],pbackPara,sizeof(tmt_Channel)*nChs);

		for (int i=3;i<this->rowCount();i++)
		{
			if (m_pArrUI[0].Harm[i-1].m_bSelect)
			{
				item(i,0)->setCheckState(Qt::Checked);
			}
			else
			{
				item(i,0)->setCheckState(Qt::Unchecked);
			}
		}
	}

	delete pbackPara;
	connect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));
	return bChange;
}
*/
void QHarmTable::CheckedListUnEdited(bool b)
{
	disconnect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));

	QTableWidgetItem* pItem = NULL;
	for (int i = 0;i<this->rowCount();i++)
	{
		for (int j=0; j<this->columnCount(); j++)
		{
			pItem  =  item(i,j);
			if (pItem == NULL)
			{
				return;
			}

			if (b)
			{
				pItem->setFlags(Qt::NoItemFlags);
			}
			else
			{
				//双击可编辑
				pItem->setFlags((Qt::ItemFlags)63);
			//	pItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
			}
		}
	}
	connect(this, SIGNAL(cellChanged ( int , int )), this, SLOT(slot_OnCellChanged(int ,int)));
}

// void QHarmTable::setArrUIValue(bool bValue)
// {
// 	long nChIndex = 0;
// 
// 	nChIndex = m_pChResource->GetChIndex_FromZero();
// 	long nMaxRowCount = Global_GetHarmTableMaxRowCount();
// 
// 	for (int nHarmIndex = 0;  nHarmIndex <= nMaxRowCount;  nHarmIndex++)//32
// 		m_pArrUI[nChIndex].Harm[nHarmIndex].m_bSelect  =  bValue;
// 
// //	m_pArrUI[nChIndex].Harm[1].m_bSelect  = true;//基波一直要置TRUE；
// }

void QHarmTable::setAllAmpValue(float fAmpValue, QString strText)
{
	//setAllValue_Item(fAmpValue, 1, strText);
}

//通道含有率
void QHarmTable::setAllContainRateValue(float fContainRateValue, QString strText)
{
	//setAllValue_Item(fContainRateValue,  0, strText);
}

//相位
void QHarmTable::setAllPhaseValue( float fPhaseValue, QString strText)
{
	//setAllValue_Item(fPhaseValue, 2, strText);
}


//设置单个谐波的值;
/*void QHarmTable::setSingleHarmValue_Add(int nIndex,  int nHarmIndex,  float fStepValue )
{
	long    nGroupChIndex   =   0,     nAllChIndex   =   0;
	QTableWidgetItem *pItem = NULL;

	QStringList listName = g_strText.split(",");

	int  nItem = 0;
	for (nItem = 0;  nItem < listName.size(); nItem++)
	{
		long		nIndexTemp   =   0;
		POS   pos   =  m_oGroupResourceRef.GetHeadPosition();
		CSttChResource *  pChResource = NULL;

		while(pos)
		{
			pChResource   =   (CSttChResource *)m_oGroupResourceRef.GetNext(pos);
			if (pChResource->m_strName == listName[nItem])		// 查找到相同名称的时候；
			{
				for(int i   =  1;   i  <  MAX_HARM_COUNT_UI + 1;  i++)
				{
					if ((nHarmIndex  +  1)  ==  i)
					{
						pItem = item(i  + 1 ,  3  +  nIndexTemp  *  3);
						QString strValue  =  pItem->text();
						g_fValueStep = strValue.toFloat()  +  fStepValue;

						//QString strTemp = QString::number(strValue.toFloat() + fStepValue,  'f', 3);
						//strTemp.remove(QRegExp("^(0+)"));

						pItem->setText(QString::number(strValue.toFloat() + fStepValue,  'f', 3));

						//pItem->setText(QString::number(strValue.toFloat()  +  fStepValue,  'f', 3));
						break;
					}
				}

				break;
			}
			nIndexTemp++;
		}
	}
}


void QHarmTable::setSingleHarmValue_Del(int nIndex,  int nHarmIndex,  float fStepValue )
{
	long    nGroupChIndex   =   0,     nAllChIndex   =   0;
	QTableWidgetItem *pItem = NULL;
	QStringList listName = g_strText.split(",");

	int  nItem = 0;
	for (nItem = 0;  nItem < listName.size(); nItem++)
	{
		CString	strTmp;
		long		nIndexTemp   =   0;
		POS   pos   =  m_oGroupResourceRef.GetHeadPosition();
		CSttChResource *  pChResource = NULL;

		while(pos)
		{
			pChResource   =   (CSttChResource *)m_oGroupResourceRef.GetNext(pos);
			if (pChResource->m_strName == listName[nItem])		// 查找到相同名称的时候；
			{
				for(int i   =  1;   i  <  MAX_HARM_COUNT_UI + 1;  i++)
				{
					if ((nHarmIndex  +  1)  ==  i)
					{
						pItem = item(i  + 1 ,  3  +  nIndexTemp  *  3);
						QString strValue  =  pItem->text();
						//QString strTemp = QString::number(strValue.toFloat() - fStepValue,  'f', 3);
						//strTemp.remove(QRegExp("^(0+)"));
						pItem->setText(QString::number(strValue.toFloat() - fStepValue,  'f', 3));
						//pItem->setText(QString::number(strValue.toFloat() - fStepValue,  'f', 3));
						break;
					}
				}

				break;
			}
			nIndexTemp++;
		}
	}
}


void QHarmTable::set_single_Value(float fValue, QString strName, int nIndexFlag )
{
	CString	strTmp;
	long		nIndexTemp   =   0;
	POS   pos   =  m_oGroupResourceRef.GetHeadPosition();
	CSttChResource *  pChResource = NULL;
	QTableWidgetItem *pItem = NULL;

	while(pos)
	{
		pChResource   =   (CSttChResource *)m_oGroupResourceRef.GetNext(pos);
		if (pChResource->m_strName == strName)		// 查找到相同名称的时候；
		{
			for(int i   =  2;   i  <  MAX_HARM_COUNT_UI ;  i++)
			{
				pItem = item(i  +  2,  nIndexFlag + 2 + nIndexTemp * 3);
				//QString strTemp = QString::number(fValue, 'f', 3 );
				//strTemp.remove(QRegExp("^(0+)"))
				pItem->setText(QString::number(fValue, 'f', 3 ));
			}

			break;
		}
		nIndexTemp++;
	}
}

void QHarmTable::setAllValue_Item(float fValue,  int nIndexFlag, QString strText)
{
	QStringList listName = strText.split(",");
	int  nItem = 0;
	for (nItem = 0;  nItem < listName.size(); nItem++)
		set_single_Value(  fValue,  listName[nItem] , nIndexFlag);
}
*/

bool QHarmTable::eventFilter(QObject *obj, QEvent *event)
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

void QHarmTable::mousePressEvent(QMouseEvent * event)
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
