#include "QHarmTable.h"
#include <QHeaderView>
#include <qmath.h>
#include "../Module/CommonMethod/commonMethod.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../Module/XLangResource_Native.h"

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

#define HarmColunmCount      5

//#define GenHao3	1.7320508 //������

float  g_fValueStep = 0;

extern STT_SystemParas g_oSystemParas;

long Global_GetHarmTableMaxRowCount()
{
	long nMaxRowCount = g_oLocalSysPara.m_nMaxHarmCount+1;

	if (g_oSystemParas.m_nHasDigital)//�������������ʱ,��Ҫ��ȥһ��г��
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
    pLeft->setSectionsClickable(false);
	pLeft->setVisible(false);

	QFont font1 = this->horizontalHeader()->font();
	font1.setBold(true);

	this->horizontalHeader()->setFont(font1);
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //���ñ�ͷ����ɫ
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
	//this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
	QTableWidgetItem* pCurrHarmItem = NULL;

	this->clear();

	long nMaxRowCount = Global_GetHarmTableMaxRowCount();
	setRowCount(nMaxRowCount);
	setColumnCount(HarmColunmCount);

	QStringList headers;

	CString strEnable,strChannel, strAmplitude, strPhase, strContent;//ʹ�ܣ�ͨ������ֵ����λ��г��������
	xlang_GetLangStrByFile(strEnable, "Harm_Enable");
	strChannel = m_pChResource->m_strName;
	xlang_GetLangStrByFile(strAmplitude, "Native_Amplitude");
	xlang_GetLangStrByFile(strPhase, "Native_Angle");
	xlang_GetLangStrByFile(strContent, "Harm_Content");

	if (strChannel.Find('U') >= 0)
	{
		strAmplitude += "(V)";
	}
	else
		strAmplitude += "(A)";
	
#ifndef _PSX_QT_LINUX_
	strPhase += QString::fromLocal8Bit("(��)");
#else
	strPhase += "(��)";
#endif
	strContent += "(%)";
	headers << strEnable << strChannel << strAmplitude << strPhase << strContent;

	QFontMetrics fontMetrics = QFontMetrics(this->font());

	this->setColumnWidth(STT_HARM_TABLE_COL_Select,50);
	this->setColumnWidth(STT_HARM_TABLE_COL_Desc,60);
	this->setColumnWidth(STT_HARM_TABLE_COL_Amp,88);
	this->setColumnWidth(STT_HARM_TABLE_COL_Phase,88);
	this->setColumnWidth(STT_HARM_TABLE_COL_HarmRate,140);
	setHorizontalHeaderLabels(headers);
	
	for (int row = 0;  row  <  nMaxRowCount;  row++)
	{
		for (int col  =  0;  col  <  HarmColunmCount;  col++)
		{
			pCurrHarmItem = new QTableWidgetItem;

			if(col == STT_HARM_TABLE_COL_Select)
			{
				pCurrHarmItem->setFlags(pCurrHarmItem->flags() & (~Qt::ItemIsEditable));

				if (m_pArrUI[m_nChIndex].Harm[row].m_bSelect)
				{
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
				// 					setSelect(row  -  1,  true);							//��ʼ������ʼ��ʹ��
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

		item(i, STT_HARM_TABLE_COL_Amp)->setText(QString::number(fValueTemp,  'f',  3));
		item(i, STT_HARM_TABLE_COL_Phase)->setText(QString::number(m_pArrUI[m_nChIndex].Harm[i].fAngle, 'f', 1));
		item(i, STT_HARM_TABLE_COL_HarmRate)->setText(QString::number(m_pArrUI[m_nChIndex].Harm[i].fContent,  'f',  2));
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
	{//����
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
	//emit sig_ChannelValueChanged(m_moudleType,nRow,nCol, m_pCurrKeyboardItem->text().toFloat());//valueFlag=��1:��ֵ 2:��λ 3:Ƶ�ʣ�
}

void QHarmTable::slot_OnCellChanged( int nRow,int nCol)
{
	if (nRow  <  0)
	{
		return;
	}

	QTableWidgetItem*  pItem  =  item(nRow,  nCol);

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
		//ֱ����ʱ��
		if (nRow == STT_HARM_TABLE_ROW_DC/*1*/) //zhouhj 20220816 ��0��Ϊֱ��
		{
			if (bIsU)
			{
				if (fEnterValue  >  g_oLocalSysPara.m_fDC_VolMax)
				{
					pItem->setText(QString::number(g_oLocalSysPara.m_fDC_VolMax,  'f', 2));
					//QString strTemp =  tr("����ĵ�ѹ������Χ") + QString::number(g_oLocalSysPara.m_fDC_VolMax,  'f', 2) + tr("V !");
                    QString strTemp =  g_sLangTxt_State_InVolOutofRange.GetString() + QString::number(g_oLocalSysPara.m_fDC_VolMax,  'f', 2) + tr("V !"); //����ĵ�ѹ������Χ lcq 3.14
					CLogPrint::LogString(XLOGLEVEL_ERROR,strTemp);
					return;
				}
			}
			else
			{
				if (fEnterValue  > g_oLocalSysPara.m_fDC_CurMax)
				{
					pItem->setText(QString::number(g_oLocalSysPara.m_fDC_CurMax,  'f', 2));
					//QString strTemp =  tr("����ĵ���������Χ") + QString::number(g_oLocalSysPara.m_fDC_CurMax,  'f', 2) + tr("A !");
                    QString strTemp =  g_sLangTxt_State_InCurOutofrange.GetString() + QString::number(g_oLocalSysPara.m_fDC_CurMax,  'f', 2) + tr("A !");//����ĵ���������Χlcq 3.14
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
					pItem->setText(QString::number(g_oLocalSysPara.m_fAC_VolMax,  'f', 2));
					//QString strTemp =  tr("����ĵ�ѹ������Χ") + QString::number(g_oLocalSysPara.m_fAC_VolMax,  'f', 2) + tr("V !");
                    QString strTemp =  g_sLangTxt_State_InVolOutofRange.GetString() + QString::number(g_oLocalSysPara.m_fDC_VolMax,  'f', 2) + tr("V !"); //����ĵ�ѹ������Χ lcq 3.14
					CLogPrint::LogString(XLOGLEVEL_ERROR,strTemp);
					return;
				}
			}
			else
			{
				if (fEnterValue  > g_oLocalSysPara.m_fAC_CurMax)
				{
					pItem->setText(QString::number(g_oLocalSysPara.m_fAC_CurMax,  'f', 2));
					//QString strTemp =  tr("����ĵ���������Χ") + QString::number(g_oLocalSysPara.m_fAC_CurMax,  'f', 2) + tr("A !");
                    QString strTemp =  g_sLangTxt_State_InCurOutofrange.GetString() + QString::number(g_oLocalSysPara.m_fDC_CurMax,  'f', 2) + tr("A !");//����ĵ���������Χlcq 3.14
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
			//����õ�ѡ����е��������ڵ���31ʱֱ�ӷ��أ�������
			long nCount = g_oLocalSysPara.m_nMaxHarmCount + 2;

			if(g_oSystemParas.m_nHasDigital)
			{
				nCount--;
			}

			if (GetSelectCount() >= nCount)
			{			
				pItem->setCheckState(Qt::Unchecked);	
				connect(this,   SIGNAL(cellChanged ( int ,  int )),   this,  SLOT(slot_OnCellChanged(int ,  int)));
				//QString str = tr("���ܼ�ֻ��ѡ��30��г����������ѡ��ǰ��г������Ҫȡ����ѡһ�У�");

				//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, 
				//	"�ܼ�ֻ��ѡ��%d��г����������ѡ��ǰ��г������Ҫȡ����ѡһ��.", nCount - 2);
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_Gradient_Intotalcheckarow.GetString(), nCount - 2); //�ܼ�ֻ��ѡ��%d��г����������ѡ��ǰ��г������Ҫȡ����ѡһ��. lcq 3.14
				return;
			}

			setSelect(nRow,  true);
		}
		else
		{
			setSelect(nRow,  false);
		}

		bChanged  =  true;

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
		˵����sig_ChanelValueChanged   sig_WaveValueChanged  �������źŵ�������һ�����ӵ�����ܣ�һ��û�����ӵ�����ܣ�ֻ��������ͼ�Ρ�
******************************************************************************************************************************************************************************************/

		if (bChanged)	
			emit sig_ChIndexChanged(m_nChIndex);
	}

	if(g_oSystemParas.m_nHasAnalog || g_oSystemParas.m_nHasWeek)
	{
		//�ڴ���ģ����������������仯����Ҫ����ȷ��г�������ֵ
// 		if(nRow == STT_HARM_TABLE_ROW_Base && nCol == STT_HARM_TABLE_COL_Amp)//20220817 zhouhj ȥ�����û�����,�޸ĸ���г���ķ�ֵ,����������
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
// 			//�ڴ���ģ������������ֵ���ܴ��ڻ���ֵ
// 			if(m_pArrUI[m_nChIndex].Harm[nRow].fAmp > m_pArrUI[m_nChIndex].Harm[1].fAmp)//20220817 zhouhj ȥ�����÷ǻ�����,����г���ķ�ֵ����������
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

	long nEditType = 4;//���ּ���
	if (nRow == 1)
	{
		if (nCol == 1)//ֻ���ڻ�����(��һ��),��ֵ��,֧�ֵȷ�ֵ
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
			nEditType = 2;//��λ����
		}
		else if (nCol == 3)
		{
			nEditType = 4;//���ּ���
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

		item(nRow,nCol)->setText(QString::number(pChannelHarm->fContent,  'f',  2));
		item(nRow,nCol-2)->setText(QString::number(pChannelHarm->fAmp ,  'f',  3));
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

	if (nRow == 0)//ֱ��
	{
		float fBackAmp = m_pArrUI[m_nChIndex].Harm[0].fAmp;
		m_pArrUI[m_nChIndex].Harm[0].fAmp  =  fYxz;

		bChanged = true;
	}
	else if (nRow == 1)//����
	{
		float fBackAmp = m_pArrUI[m_nChIndex].Harm[1].fAmp;
		m_pArrUI[m_nChIndex].Harm[1].fAmp  =  fYxz;

		QString strTemp;
		for (int i  =  1; i < nMaxRowCount; i++)
		{
			m_pArrUI[m_nChIndex].Harm[i].fContent  =  m_pArrUI[m_nChIndex].Harm[i].fAmp * 100 / m_pArrUI[m_nChIndex].Harm[1].fAmp;

			item(i,  nCol + 2)->setText(QString::number(m_pArrUI[m_nChIndex].Harm[i].fContent,  'f',  2));

		}
		bChanged = true;
	}
	else
	{
		float fBackAmp = m_pArrUI[m_nChIndex].Harm[nRow].fAmp;
		float fBackContain = m_pArrUI[m_nChIndex].Harm[nRow].fContent;

		m_pArrUI[m_nChIndex].Harm[nRow].fAmp = fYxz;
		m_pArrUI[m_nChIndex].Harm[nRow].fContent = fYxz  * 100  / m_pArrUI[m_nChIndex].Harm[1].fAmp;

 		bChanged = true;

		item(nRow, nCol)->setText(QString::number(m_pArrUI[m_nChIndex].Harm[nRow].fAmp,   'f',  3));
		item(nRow, nCol + 2)->setText(QString::number(m_pArrUI[m_nChIndex].Harm[nRow].fContent,  'f',  2));
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

	if (nRow == 0)//ֱ��
	{
		m_pArrUI[m_nChIndex].Harm[0].fAngle  =  fXW;
		bChanged = true;
	}
	else if (nRow == 1)//����
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
				//list.append(tr("ֱ��"));
                list.append(g_sLangTxt_Native_DC); //ֱ�� lcq  3.14
			}
			else if (i == 1)
			{
				//list.append(tr("����")); 
                list.append(g_sLangTxt_Native_Fundamental); //���� lcq  3.14
			}
			else
			{
				//list.append(QString(tr("%1��г��")).arg(i));
                list.append(g_sLangTxt_State_TheOnepercentHarmonic); //%1��г�� lcq  3.14
			}
		}
	}
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
		//����Խ��ָ�
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
				//˫���ɱ༭
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
// //	m_pArrUI[nChIndex].Harm[1].m_bSelect  = true;//����һֱҪ��TRUE��
// }

void QHarmTable::setAllAmpValue(float fAmpValue, QString strText)
{
	//setAllValue_Item(fAmpValue, 1, strText);
}

//ͨ��������
void QHarmTable::setAllContainRateValue(float fContainRateValue, QString strText)
{
	//setAllValue_Item(fContainRateValue,  0, strText);
}

//��λ
void QHarmTable::setAllPhaseValue( float fPhaseValue, QString strText)
{
	//setAllValue_Item(fPhaseValue, 2, strText);
}


//���õ���г����ֵ;
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
			if (pChResource->m_strName == listName[nItem])		// ���ҵ���ͬ���Ƶ�ʱ��
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
			if (pChResource->m_strName == listName[nItem])		// ���ҵ���ͬ���Ƶ�ʱ��
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
		if (pChResource->m_strName == strName)		// ���ҵ���ͬ���Ƶ�ʱ��
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
