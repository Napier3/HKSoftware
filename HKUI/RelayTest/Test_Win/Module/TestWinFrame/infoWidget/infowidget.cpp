#include "infowidget.h"
#include <QStringList>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDateTime>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

#include "../../Module/SttCmd/SttSysState.h"
#include "../../Module/SttTest/Common/tmt_test_paras_head.h"

InfoWidget::InfoWidget(QWidget *parent)
	: QTableWidget(parent)
{
	m_eDispFlag = Input10;
	for(int i = 0;i<MAX_BINARYIN_COUNT;i++)//20230725 wxy 初始化开入量数组
	{
		m_nBinIn[i] = 0;
	}
	init();
}

InfoWidget::~InfoWidget()
{

}

void InfoWidget::init()
{
	QStringList  HStrList;
	HStrList.push_back(QString(/*tr("序号")*/g_sLangTxt_SerNumber));
	HStrList.push_back(QString(/*tr("时间")*/g_sLangTxt_Time));
	HStrList.push_back(QString(/*tr("动作类型")*/g_sLangTxt_Native_ActType));
	HStrList.push_back(QString(/*tr("开入量")*/g_sLangTxt_Native_Bin));	
	HStrList.push_back(QString(/*tr("动作时间(s)")*/g_sLangTxt_Native_ActionTime));
	HStrList.push_back(QString(/*tr("当前状态号")*/g_sLangTxt_Native_CurTypeIdx));

	QHeaderView* pLeft = verticalHeader();
	pLeft->setDefaultSectionSize(36);
	pLeft->setVisible(false);

	setColumnCount(6);
	setHorizontalHeaderLabels(HStrList);

	QHeaderView* pTop = horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);

	QFontMetrics fontMetrics = QFontMetrics(font());
	int nLabelWidth1 = fontMetrics.width(HStrList[0]) + 30;
	int nLabelWidth2;

	//20240301 suyang 分辨率  2880X1800
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	
	if (rect.height() == 1800)
	{
		nLabelWidth2 = fontMetrics.width(tr("00:00:00:000")) + 150;
	}
	else
	{
		nLabelWidth2 = fontMetrics.width(tr("00:00:00:000")) + 100;//时间列应加宽，时间完整显示chenling20240122
	}

	int nLabelWidth3 = fontMetrics.width(/*tr("开始测试")*/g_sLangTxt_Native_StartTestSy) + 40;
	int nLabelWidth4 = fontMetrics.width(tr("0000000000000000")) + 60;
	int nLabelWidth5 = fontMetrics.width(tr("00:00:00.000000")) + 40;
	int nLabelWidth6 = fontMetrics.width(HStrList[5]) + 30;
	
	setColumnWidth(0,nLabelWidth1);
	setColumnWidth(1,nLabelWidth2);
	setColumnWidth(2,nLabelWidth3);
	setColumnWidth(3,nLabelWidth4);
	setColumnWidth(4,nLabelWidth5);
	setColumnWidth(5,nLabelWidth6);

	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	setRowCount(0);
}

void InfoWidget::clear()
{
	int nRowCount = rowCount();
	for(int i = 0;i < nRowCount;i++)
	{
		removeRow(0);
	}
}

void InfoWidget::setProperty(InPutDispNum eflag)
{
	m_eDispFlag = eflag;
}

void InfoWidget::updateSwitchInfoTable(QList<CEventResult*> list)
{
	int nRowCount = rowCount();
	int n = list.size();
	CEventResult *pResult = NULL;

	for (int i=nRowCount; i< n;i++)
	{
		pResult = list.at(i);
		InsertSwitchInfoTable(pResult,TRUE);
	}

	scrollToBottom();
}

void InfoWidget::InsertSwitchInfoTable(CEventResult* pEventResult,BOOL bUpdateStateIndex)
{
	CString strTime = _T("/");

	if ((pEventResult->m_strEventID != SYS_STATE_EVENT_OnTestStoped)&&(pEventResult->m_strEventID != SYS_STATE_EVENT_OnTestFinished))
	{
		long nIndex = pEventResult->m_strTimeStr.ReverseFind('.');
		if (nIndex < 10)
		{
			strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),pEventResult->m_tmEvent.wYear,pEventResult->m_tmEvent.wMonth ,pEventResult->m_tmEvent.wDay,pEventResult->m_tmEvent.wHour
				,pEventResult->m_tmEvent.wMinute
				,pEventResult->m_tmEvent.wSecond
				,pEventResult->m_tmEvent.wMilliseconds);		
		} 
		else
		{
			strTime = pEventResult->m_strTimeStr.Left(nIndex+4);
		}

	}

	if (pEventResult->m_strEventID == SYS_STATE_EXCEPTION)
	{
//		CLogPrint::LogString(XLOGLEVEL_INFOR,tr("测试异常"));
		return;
	}

	if (pEventResult->m_strEventID == SYS_STATE_UNEXCEPTION)
	{
//		CLogPrint::LogString(XLOGLEVEL_INFOR,tr("解除测试异常"));
		return;
	}
	
	//20230725 wxy 修改开入量内容
	//CString strBinIn = _T("");

	//for (int i=0; i<g_nBinCount/*g_oLocalSysPara.m_nCHBinInNum*/; i++)
	//{
	//	strBinIn.AppendFormat(_T("%d"),pEventResult->m_BinIn[i]);
	//}	

	CString strBinIn = _T("");

	if(pEventResult->m_strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		for (int i=0; i<g_nBinCount; i++)
	{
		strBinIn.AppendFormat(_T("%d"),pEventResult->m_BinIn[i]);
			m_nBinIn[i] = pEventResult->m_BinIn[i];
		}
	}
	else if(pEventResult->m_strEventID == SYS_STATE_REPORT_OnSwichInChanged )
	{
		strBinIn = FindBinInChange(pEventResult->m_BinIn, g_nBinCount);
	}
	else 
	{
		for (int i=0; i<g_nBinCount; i++)
	{
		strBinIn.AppendFormat(_T("%d"),pEventResult->m_BinIn[i]);
	}
	}

	int nRows = rowCount();

	QTableWidgetItem *item = NULL; 

	insertRow(nRows);

	//序号
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(QString("%1").arg(nRows+1));
	setItem(nRows, 0, item); 

	//时间
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(strTime);
	setItem(nRows, 1, item); 

	//事件ID
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(Global_GetEventName(pEventResult->m_strEventID));
	setItem(nRows, 2, item); 

	//开入信息
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item->setText(strBinIn);
	setItem(nRows, 3, item); 

	//动作时间
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (pEventResult->m_strEventID == SYS_STATE_REPORT_OnSwichInChanged)
	{
		long nPrecision = 4;

		if ((pEventResult->m_fActTime>0.000f)&&(pEventResult->m_fActTime<0.0001f))
		{
			nPrecision = 5;
		}

		item->setText(QString::number(pEventResult->m_fActTime,'f',nPrecision));
	}
	else
	{
		item->setText("/");
	}

	setItem(nRows, 4, item); 

	//当前状态号
	item = new QTableWidgetItem();
	item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	if (bUpdateStateIndex)
	{
		item->setText(QString("%1").arg(pEventResult->m_nCurrStateIndex + 1));
	} 
	else
	{
		item->setText(QString("0"));
	}

	setItem(nRows, 5, item); 

	resizeRowsToContents();//20230726 wxy 自适应行高
}

QString InfoWidget::msformatTime(long us) //us
{  
	long ms = us/1000;
	long ss = 1000;  
	long mi = ss * 60;  
	long hh = mi * 60;  
	long dd = hh * 24;  

	long day = ms / dd;  
	long hour = (ms - day * dd) / hh;  
	long minute = (ms - day * dd - hour * hh) / mi;  
	long second = (ms - day * dd - hour * hh - minute * mi) / ss;  
	long milliSecond = ms - day * dd - hour * hh - minute * mi - second * ss;
	long usSecond = us-ms*1000;

	long v = milliSecond*1000+usSecond;

	QString str ;//利用printf的格式输出（0占位方式）,解决了原来显示卡顿的现象
	str = str.sprintf("%02d:%02d:%02d.%03d%03d",hour,minute,second,milliSecond,usSecond);//hour,minute,second,mSecond都是int型变量

	return str;
}

void InfoWidget::ShowBinInResultMsg(CEventResult* pEventResult)
{
	CString strBinInMsg;

	for (int i = 0; i < g_nBinCount; i++)
	{
		if(m_nBinIn[i] != pEventResult->m_BinIn[i])
		{
			if(i == 0)
			{
				strBinInMsg = g_sLangTxt_Manual_InA;
			}
			else if(i == 1)
			{
				strBinInMsg = g_sLangTxt_Manual_InB;
			}
			else if(i == 2)
			{
				strBinInMsg = g_sLangTxt_Manual_InC;
			}
			else if(i == 3)
			{
				strBinInMsg = g_sLangTxt_Manual_InD;
			}
			else if(i == 4)
			{
				strBinInMsg = g_sLangTxt_Manual_InE;
			}
			else if(i == 5)
			{
				strBinInMsg = g_sLangTxt_Manual_InF;
			}
			else if(i == 6)
			{
				strBinInMsg = g_sLangTxt_Manual_InG;
			}
			else if(i == 7)
			{
				strBinInMsg = g_sLangTxt_Manual_InH;
			}

			strBinInMsg += ":  ";

			long nPrecision = 3;

			if ((pEventResult->m_fActTime>0.000f)&&(pEventResult->m_fActTime<0.001f))
			{
				if (pEventResult->m_fActTime<0.0001f)
				{
					nPrecision = 5;
				}
				else
				{
					nPrecision = 4;
				}
			}

			strBinInMsg += QString::number(pEventResult->m_fActTime,'f',nPrecision);//.Format("%.5lf",dValue);
			strBinInMsg += "s";
			//strBinInMsg.AppendFormat(_T("%.3lfs"),pEventResult->m_fActTime);
			CLogPrint::LogString(XLOGLEVEL_RESULT,strBinInMsg);

		}

	}
}


CString InfoWidget::FindBinInChange(long *pnNewArr, int size)
{
	CString strBinIn,strBinInChannel,strMsg,NotChangeBinIn,strBinInMsg;
	int ChangeIndex = 0;
	for (int i = 0; i < size; i++)
	{
		if(m_nBinIn[i] != pnNewArr[i])
		{
			++ChangeIndex;

			if(ChangeIndex >1)
			{
				strBinIn += "\n";
			}

			if(i == 0)
			{
				strBinInMsg = g_sLangTxt_Manual_InA;
			}
			else if(i == 1)
			{
				strBinInMsg = g_sLangTxt_Manual_InB;
			}
			else if(i == 2)
			{
				strBinInMsg = g_sLangTxt_Manual_InC;
			}
			else if(i == 3)
			{
				strBinInMsg = g_sLangTxt_Manual_InD;
			}
			else if(i == 4)
			{
				strBinInMsg = g_sLangTxt_Manual_InE;
			}
			else if(i == 5)
			{
				strBinInMsg = g_sLangTxt_Manual_InF;
			}
			else if(i == 6)
			{
				strBinInMsg = g_sLangTxt_Manual_InG;
			}
			else if(i == 7)
			{
				strBinInMsg = g_sLangTxt_Manual_InH;
			}
			strMsg = "  "+QString::number(m_nBinIn[i]) +"->" + QString::number(pnNewArr[i]);

			//strBinInMsg = _T("开入");
			//strBinInMsg += strBinInChannel;

			strBinInMsg += strMsg;
			strBinIn += strBinInMsg;

		}
		m_nBinIn[i] = pnNewArr[i];
		NotChangeBinIn+= QString::number(pnNewArr[i]);

	}
	if(ChangeIndex == 0)
	{
		strBinIn = NotChangeBinIn;
	}
//	CString CstrBinIn = strBinIn.toStdString().c_str();
	return strBinIn;
}
