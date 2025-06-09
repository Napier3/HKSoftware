#include "infowidget.h"
#include <QStringList>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDateTime>
#include <QDebug>

#include "../../Module/SttCmd/SttSysState.h"
#include "../../Module/SttTestSysGlobalPara.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
//#include "../../SttTestCntrFrameBase.h"
#include "../../../../../Module/XLanguage/XLanguageResource.h"
#include"../../Module/XLangResource_Native.h" 


QInfoWidget::QInfoWidget(QWidget *parent)
	: QScrollTableWidget(parent)
{
	m_eDispFlag = Input10;
	for(int i = 0;i<MAX_BINARYIN_COUNT;i++)//20230725 wxy 初始化开入量数组
	{
		m_nBinIn[i] = 0;
		m_nBinInResult[i] = 0;
	}
	
	m_bHasInitFinished = false;
}

QInfoWidget::~QInfoWidget()
{

}

void QInfoWidget::init()
{
	QStringList  HStrList;
	CString strIndex, strTime, strActType, strBin, strActTime, strCurType;
	xlang_GetLangStrByFile(strIndex, "sSerNumber");
	xlang_GetLangStrByFile(strTime, "sTime");
	xlang_GetLangStrByFile(strActType, "Native_ActType");
	xlang_GetLangStrByFile(strBin, "sInputValue");
	xlang_GetLangStrByFile(strActTime, "Native_ActionTime");
	xlang_GetLangStrByFile(strCurType, "Native_CurTypeIdx");
	HStrList.push_back(strIndex);
	HStrList.push_back(strTime);
	HStrList.push_back(strActType);
	HStrList.push_back(strBin);	
	HStrList.push_back(strActTime);
	HStrList.push_back(strCurType);

	QHeaderView* pLeft = verticalHeader();
	pLeft->setDefaultSectionSize(36);
	pLeft->setVisible(false);

	setColumnCount(6);
	setHorizontalHeaderLabels(HStrList);

	QHeaderView* pTop = horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false); 
// 	font1.setPointSize(16);//2022-10-24 sy 采用g_pSttGlobalFont
// 	pTop->setFont(font1);
// 	
//	setFont(font1);
	pTop->setFont(*g_pSttGlobalFont);
	QFont font1 = pTop->font();

	QFontMetrics fontMetrics = QFontMetrics(font1/*font()*/);
	int nLabelWidth1 = fontMetrics.width(HStrList[0]) + 10;
	int nLabelWidth2 = fontMetrics.width("2021-10-10 00:00:00.000") + 40;
	//int nLabelWidth3 = fontMetrics.width("开始测试") + 30;  
    int nLabelWidth3 = fontMetrics.width(g_sLangTxt_StartTest) + 30; //开始测试 lcq 3.15
	int nLabelWidth4 = fontMetrics.width("0000000000000000") + 30;
	int nLabelWidth5 = fontMetrics.width("00:00:00.000000") + 20;
	int nLabelWidth6 = fontMetrics.width(HStrList[5]) + 20;
	
	setColumnWidth(0,nLabelWidth1);
	setColumnWidth(1,nLabelWidth2);
	setColumnWidth(2,nLabelWidth3);
	setColumnWidth(3,nLabelWidth4);
	setColumnWidth(4,nLabelWidth5);
	setColumnWidth(5,nLabelWidth6);

// 	font1 = this->font();
// 	font1.setPointSize(20); 
	this->setFont(font1);

	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	setRowCount(0);
	setWordWrap(true);
}

void QInfoWidget::clear()
{
	int nRowCount = rowCount();
	for(int i = 0;i < nRowCount;i++)
	{
		removeRow(0);
	}

	m_listEventResult.DeleteAll();
}

void QInfoWidget::setProperty(InPutDispNum eflag)
{
	m_eDispFlag = eflag;
}

void QInfoWidget::updateSwitchInfoTable(QList<CEventResult*> list)
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

void QInfoWidget::InsertSwitchInfoTable(CEventResult* pEventResult,BOOL bUpdateStateIndex)
{
	if (m_bHasInitFinished)
	{
		ShowEventResult(pEventResult, bUpdateStateIndex);
	}
	else
	{
		if(pEventResult->m_strEventID == SYS_STATE_EVENT_OnTestStarted)//20241023 suyang 在开始测试的时候将初始化的值匹配
		{
			for (int i=0; i<g_nBinCount; i++)
			{
				m_nBinInResult[i] = pEventResult->m_BinIn[i];
			}
		}

		CEventResult *pNew = (CEventResult*)pEventResult->Clone();
		m_listEventResult.AddNewChild(pNew);
	}
}

QString QInfoWidget::msformatTime(long us) //us
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

void QInfoWidget::ShowBinInResultMsg(CEventResult* pEventResult)
{
	CString strBinInMsg;

	for (int i = 0; i < g_nBinCount; i++)
	{
		if(m_nBinInResult[i] != pEventResult->m_BinIn[i])
		{
			if (!strBinInMsg.IsEmpty())
			{
				strBinInMsg = _T("");//20241023 suyang 防止多个开入动作，字符串清空 
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

			m_nBinInResult[i] = pEventResult->m_BinIn[i];//20241023 suyang 变位更改，也需要更新m_nBinIn[i]开入量

			strBinInMsg += QString::number(pEventResult->m_fActTime,'f',nPrecision);//.Format("%.5lf",dValue);
			strBinInMsg += "s";
			//strBinInMsg.AppendFormat(_T("%.3lfs"),pEventResult->m_fActTime);
			CLogPrint::LogString(XLOGLEVEL_RESULT,strBinInMsg);

		}

	}
}


CString QInfoWidget::FindBinInChange(long *pnNewArr, int size)
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


//2024-9-10 lijunqing 优化系统程序启动的效率
void QInfoWidget::ShowListEventResult()
{
	long nCount = m_listEventResult.GetCount();
	POS pos = m_listEventResult.GetHeadPosition();
	CEventResult *pEventResult = 0;
	long nIndex = 0;

	while (pos != 0)
	{
		pEventResult = (CEventResult *)m_listEventResult.GetNext(pos);
		ShowEventResult(pEventResult,TRUE);//20241023 suyang 增加显示存储的数据

	}
}

//对应手动时间不需要更新StateIndex，统一将其赋值为
void QInfoWidget::ShowEventResult(CEventResult* pEventResult, BOOL bUpdateStateIndex)
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

			m_nBinInResult[i] = pEventResult->m_BinIn[i];
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

void QInfoWidget::showEvent(QShowEvent *event)
{
	if (!m_bHasInitFinished)
	{
		init();
		ShowListEventResult();
		m_bHasInitFinished = true;
	}

	QScrollTableWidget::showEvent(event);
}

