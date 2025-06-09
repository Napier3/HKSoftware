#include "QSttVoltageTimeGroupTestItemWidget.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttGlobalDef.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include "../../Module/UI/Module/FAParasSetWidget/QSttFAParasSetDialog.h"
#include <QHeaderView>
#include "QSttMacroParaEditViewVolTimeTypeSec.h"


QSttVoltageTimeGroupTestItemWidget::QSttVoltageTimeGroupTestItemWidget(QWidget *parent) :QWidget(parent)
{
	m_pVolTimeTypeTestItemTableWidget = NULL;
	m_pCheckSelBtn = NULL;
	m_pRemoteMonitorCheckBox = NULL;

	for(int i = 0;i<MAX_BINARYIN_COUNT;i++)//20230725 wxy 初始化开入量数组
	{
		m_nBinIn[i] = 0;
	}
	InitUI();
	InitConnections();
}

QSttVoltageTimeGroupTestItemWidget::~QSttVoltageTimeGroupTestItemWidget()
{

}



void QSttVoltageTimeGroupTestItemWidget::InitUI()
{
	InitTable();
	CString strText;
	m_pCheckSelBtn = new QPushButton;
	strText = /*_T("全选")*/g_sLangTxt_SelAll;
	m_pCheckSelBtn->setText(strText);
	m_pRemoteMonitorCheckBox = new QSttCheckBox;
	strText = QString::fromLocal8Bit("遥信变位监测");
	m_pRemoteMonitorCheckBox->setText(strText);

	m_pCheckSelBtn->setFont(*g_pSttGlobalFont);
	m_pRemoteMonitorCheckBox->setFont(*g_pSttGlobalFont);
	QHBoxLayout *pBtnLayout = new QHBoxLayout;
	pBtnLayout->addWidget(m_pCheckSelBtn);
	pBtnLayout->addStretch(10);
	pBtnLayout->addWidget(m_pRemoteMonitorCheckBox);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pVolTimeTypeTestItemTableWidget);
	pMainLayout->addLayout(pBtnLayout);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);

}


void QSttVoltageTimeGroupTestItemWidget::InitTable()
{
	m_pVolTimeTypeTestItemTableWidget = new QTableWidget;
	m_pVolTimeTypeTestItemTableWidget->setColumnCount(3);
	m_pVolTimeTypeTestItemTableWidget->setFont(*g_pSttGlobalFont);
	m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setClickable(false);
	m_pVolTimeTypeTestItemTableWidget->verticalHeader()->setVisible(false);
	QStringList  HStrList;
	HStrList << g_sLtxt_SICDSelect << g_sLangTxt_Name << g_sLangTxt_Status;
	m_pVolTimeTypeTestItemTableWidget->setHorizontalHeaderLabels(HStrList); 
	m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	m_pVolTimeTypeTestItemTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pVolTimeTypeTestItemTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	m_pVolTimeTypeTestItemTableWidget->setColumnWidth(0,40*g_dUIShowCoef);
	m_pVolTimeTypeTestItemTableWidget->setColumnWidth(1,230*g_dUIShowCoef);
	m_pVolTimeTypeTestItemTableWidget->setColumnWidth(2,50*g_dUIShowCoef);

}

void QSttVoltageTimeGroupTestItemWidget::InitConnections()
{
// 	for (int i = 0; i < m_pSelcetCheckItemList.size(); ++i) 
// 	{
// 		QSttCheckBox *pCheckBox = m_pSelcetCheckItemList.at(i);
// 		connect(pCheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_CheckBoxClicked(bool)));
// 
// 	}
	connect(m_pVolTimeTypeTestItemTableWidget, SIGNAL(cellClicked (int,int)), this, SLOT(slot_TableWidgetClicked(int,int)));
	connect(m_pCheckSelBtn, SIGNAL(clicked()), this, SLOT(slot_CheckSelBtnClicked()));
	connect(m_pRemoteMonitorCheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_RemoteMonitorClicked(bool)));
}


void QSttVoltageTimeGroupTestItemWidget::InitData(CDataGroup *pParas )
{
	QTableWidgetItem *pItem = NULL; 
	CString strID;
	int nCount = pParas->GetChildCount(DTMCLASSID_CDATAGROUP);
	m_pVolTimeTypeTestItemTableWidget->setRowCount(nCount);
	for (int nCurrRowIndex = 0; nCurrRowIndex < nCount;nCurrRowIndex++)
	{
		pItem = new QTableWidgetItem();
		pItem->setTextAlignment(Qt::AlignCenter); 
		strID.Format(_T("TestItem%d"), nCurrRowIndex+1);
		CDataGroup *pTestItemData = (CDataGroup *)pParas->FindByID(strID);
		if (pTestItemData)
		{
			pItem->setText(pTestItemData->m_strName);
		}
		m_pVolTimeTypeTestItemTableWidget->setItem(nCurrRowIndex,1,pItem);
		QSttCheckBox *pCheckBox = new QSttCheckBox(this);
		// 将复选框放入布局
		QWidget *pWidget = new QWidget();
		QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
		pLayout->addWidget(pCheckBox);
		pLayout->setContentsMargins(0, 0, 0, 0);
		pLayout->setAlignment(pCheckBox, Qt::AlignCenter);
		pWidget->setLayout(pLayout);
		m_pVolTimeTypeTestItemTableWidget->setCellWidget(nCurrRowIndex, 0, pWidget);
		m_pSelcetCheckItemList.append(pCheckBox); // 将复选框加入列表

		pItem = new QTableWidgetItem();
		pItem->setTextAlignment(Qt::AlignCenter); 
		m_pVolTimeTypeTestItemTableWidget->setItem(nCurrRowIndex,2,pItem);

		connect(pCheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_CheckBoxClicked(bool)));
	}
}

void QSttVoltageTimeGroupTestItemWidget::slot_CheckSelBtnClicked()
{
	CString strText,strID;
	bool bIsSelectAll = (m_pCheckSelBtn->text() == /*_T("全选"))*/g_sLangTxt_SelAll);
	strText = bIsSelectAll ?  /*_T("清空"):_T("全选")*/ g_sLangTxt_Native_Clear:g_sLangTxt_SelAll;

	for (int row = 0; row < m_pVolTimeTypeTestItemTableWidget->rowCount(); ++row)
	{
		strID.Format(_T("TestItem%d"), row+1);
		CDataGroup *pTestItemData = (CDataGroup *)m_pVolTimeTypeSecDataGroup->FindByID(strID);
		if (pTestItemData)
		{
			CString strValue;
			if (bIsSelectAll)
			{
				strValue = _T("1");
			}
			else
			{
				strValue = _T("0");
			}
			pTestItemData->SetDataValue(_T("isValid"), strValue);
		}

		QWidget *pWidget = m_pVolTimeTypeTestItemTableWidget->cellWidget(row, 0);
		if (pWidget != NULL)
		{
			QList<QWidget*> childWidgets = pWidget->findChildren<QWidget*>();
			foreach (QWidget *pChildWidget, childWidgets)
			{
				QCheckBox *pCheckBox = qobject_cast<QCheckBox*>(pChildWidget);
				if (pCheckBox != NULL)
				{
					pCheckBox->setChecked(bIsSelectAll);
					break;
				}
			}
		}
	}
	m_pCheckSelBtn->setText(strText);
}

void QSttVoltageTimeGroupTestItemWidget::slot_RemoteMonitorClicked( bool checked )
{
	if (checked)
	{
		g_pTheSttTestApp->OpenPpSttCommConfigFile();
	}
	else
	{
		g_pTheSttTestApp->FreeDvmDevice();
	}

	m_pVolTimeTypeSecDataGroup->SetDataValue(_T("YX_Check"),long(checked));
}



void QSttVoltageTimeGroupTestItemWidget::StartInit()
{
	m_pVolTimeTypeTestItemTableWidget->setDisabled(true);
	m_pCheckSelBtn->setDisabled(true);
	m_pRemoteMonitorCheckBox->setDisabled(true);


	ClearResultState();
}

void QSttVoltageTimeGroupTestItemWidget::StopInit()
{
	m_pVolTimeTypeTestItemTableWidget->setDisabled(false);
	m_pCheckSelBtn->setDisabled(false);
	m_pRemoteMonitorCheckBox->setDisabled(false);
}

void QSttVoltageTimeGroupTestItemWidget::UpdateData( CDataGroup *pParas )
{
	m_pVolTimeTypeSecDataGroup = pParas;

	CDvmData* pCurData = (CDvmData*)pParas->FindByID(_T("YX_Check"));
	if (pCurData)
	{
		long nSelect = CString_To_long(pCurData->m_strValue);
		m_pRemoteMonitorCheckBox->setChecked(nSelect);
		slot_RemoteMonitorClicked(nSelect);
	}

	int nCount = pParas->GetChildCount(DTMCLASSID_CDATAGROUP);
	CString strID;
	for (int i = 0; i < nCount;i++)
	{
		strID.Format(_T("TestItem%d"), i+1);
		CDataGroup *pTestItemData = (CDataGroup *)pParas->FindByID(strID);
		if (pTestItemData == NULL)
		{
			continue;
		}

		//默认显示第一个测试项
		if (i == 0)
		{
			g_pVolTimeTypeSecTestMain->m_pFAStateSequenceGroupGrid->ShowDatas(pTestItemData);
		}

// 		QTableWidgetItem *pItem = m_pVolTimeTypeTestItemTableWidget->item(i, 1);
// 		if (pItem)
// 		{
// 			pItem->setText(pTestItemData->m_strName);
// 		}

		if(!m_pSelcetCheckItemList.isEmpty())
		{
			QSttCheckBox *pCheckBox = m_pSelcetCheckItemList.at(i);
			if (pCheckBox)
			{
				long nCheck;
				stt_GetDataValueByID(pTestItemData, _T("isValid"), nCheck);
				pCheckBox->setChecked(nCheck); 
			}
		}
	}
}

void QSttVoltageTimeGroupTestItemWidget::UpdateStateTable()
{
	if (m_pVolTimeTypeTestItemTableWidget == NULL)
	{
		return;
	}
	int nCurrentRow = m_pVolTimeTypeTestItemTableWidget->currentRow();
	int nCurrentColumn = m_pVolTimeTypeTestItemTableWidget->currentColumn();

	slot_TableWidgetClicked(nCurrentRow,nCurrentColumn);
}

void QSttVoltageTimeGroupTestItemWidget::UpdateResultState( CString strID,const CString &strState )
{
	m_strItemID = strID;
	CString strResult;
	strResult = _T("");
	QColor resultColor(Qt::white);
	strID = strID.Right(1);
	long nIndex = CString_To_long(strID);
	
	QTableWidgetItem *pItem = m_pVolTimeTypeTestItemTableWidget->item(nIndex-1, 2);
	if (pItem)
	{
		if (strState == TEST_STATE_DESC_ELIGIBLE)
		{
			strResult = /*_T("合格")*/g_sLangTxt_Qualified;
			 resultColor = QColor(Qt::green); 
		}
		else if(strState == TEST_STATE_DESC_INLEGIBLE)
		{
			strResult = /*_T("不合格")*/g_sLangTxt_Unqualified;
			resultColor = QColor(Qt::red); 
		}
		else if(strState == TEST_STATE_DESC_TESTING)
		{
			strResult = /*_T("测试中")*/g_sLangTxt_Testing;
			resultColor = QColor(Qt::black); 
		}
		pItem->setTextColor(resultColor);
		pItem->setText(strResult);
	}

	//切换右边状态序列视图
	slot_TableWidgetClicked(nIndex-1,1);
}

void QSttVoltageTimeGroupTestItemWidget::ClearResultState()
{
	for (int row = 0; row < m_pVolTimeTypeTestItemTableWidget->rowCount(); ++row)
	{
		QTableWidgetItem *pItem = m_pVolTimeTypeTestItemTableWidget->item(row, 2);
		if (pItem)
		{
			pItem->setText(_T(""));
		}
	}
}

void QSttVoltageTimeGroupTestItemWidget::UpdateEventMsg(CEventResult *pCurrEventResult )
{
	if (m_strItemID.IsEmpty())
	{
		return;
	}

	CString strBinIn = _T("");

	if(pCurrEventResult->m_strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		for (int i=0; i<g_nBinCount; i++)
		{
			m_nBinIn[i] = pCurrEventResult->m_BinIn[i];
		}
	}
	else if(pCurrEventResult->m_strEventID == SYS_STATE_REPORT_OnSwichInChanged )
	{
		strBinIn = FindBinInChange(pCurrEventResult->m_BinIn, g_nBinCount);//返回有动作变位对应的开入
	}
	
	int nCurrStateIndex = pCurrEventResult->m_nCurrStateIndex;
	double dActTime = pCurrEventResult->m_fActTime;

	CString strID,strStateID;
	long nIndex = CString_To_long(m_strItemID.Right(1));
	strID.Format(_T("TestItem%d"), nIndex);
	CDataGroup *pTestItemData = (CDataGroup *)m_pVolTimeTypeSecDataGroup->FindByID(strID);
	if (pTestItemData == NULL)
	{
		return;
	}

	strStateID.Format(_T("state%d"), nCurrStateIndex);
	CDataGroup *pStateData = (CDataGroup *)pTestItemData->FindByID(strStateID);

	if (pStateData == NULL)
	{
		return;
	}

	long nEndMode;
	stt_GetDataValueByID(pStateData, _T("EndMode"), nEndMode);
	if (nEndMode != 0)
	{	//EndMode：0-时间触发 1-合闸 2-分闸

		CString strEndBinIn,strBinInResult;

		if (nEndMode == 1)
		{
			strEndBinIn = g_pVolTimeTypeSecTestMain->m_strEndBinIn[0].Right(1);//合闸
		}
		else if(nEndMode == 2)
		{
			strEndBinIn = g_pVolTimeTypeSecTestMain->m_strEndBinIn[1].Right(1);//分闸	
		}

		strEndBinIn = g_sLangTxt_Native_BinX + strEndBinIn.GetString();
		
// 		bool bFind = false;
// 		char flag='A'; //该模块需要0->1的开入变位
// 		for (int i=0; i<g_nBinCount; i++)
// 		{
// 			if (pCurrEventResult->m_BinIn[i] == 1)
// 			{
// 				strBinInResult.Format(_T("开入%c"), flag);
// 				if (strBinInResult == strEndBinIn)
// 				{
// 					bFind = true;
// 					break;
// 				}
// 			}
// 			flag++;
// 		}
		if(strBinIn == strEndBinIn/* && bFind*/)
		{
			if(dActTime > 0.00001)
			{
				pStateData->SetDataValue(_T("ActTime"), QString::number(dActTime,'f'));
			}
			else
			{
				pStateData->SetDataValue(_T("ActTime"), /*_T("未动作")*/g_sLangTxt_Unact);
			}
		}
		else
		{
			pStateData->SetDataValue(_T("ActTime"), /*_T("未动作")*/g_sLangTxt_Unact);
		}
	}
}

CString QSttVoltageTimeGroupTestItemWidget::FindBinInChange( long *pnNewArr, int size )
{
	CString strBinIn,strBinInMsg;
	for (int i = 0; i < size; i++)
	{
		if(m_nBinIn[i] != pnNewArr[i])
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

			if (m_nBinIn[i] == 0 && pnNewArr[i] == 1)//该模块需要0->1的开入变位
			{
				strBinIn += strBinInMsg;
			}
		}
		m_nBinIn[i] = pnNewArr[i];

	}
	return strBinIn;
}

void QSttVoltageTimeGroupTestItemWidget::slot_TableWidgetClicked(int row,int col)
{
	if (row < 0 || col < 0)
	{
		return;
	}
	disconnect(m_pVolTimeTypeTestItemTableWidget, SIGNAL(cellChanged (int,int)), this, SLOT(slot_TableWidgetClicked(int row,int col)));

	CString strID;
	strID.Format(_T("TestItem%d"), row+1);
	CDataGroup *pTestItemData = (CDataGroup *)m_pVolTimeTypeSecDataGroup->FindByID(strID);
	if (pTestItemData == NULL)
	{
		return;
	}

	g_pVolTimeTypeSecTestMain->m_pFAStateSequenceGroupGrid->ShowDatas(pTestItemData);
	//g_pVolTimeTypeSecTestMain->m_pFATestResultViewGroupGrid->ShowDatas(pTestItemData);
	connect(m_pVolTimeTypeTestItemTableWidget, SIGNAL(cellChanged (int,int)), this, SLOT(slot_TableWidgetClicked(int row,int col)));

}

void QSttVoltageTimeGroupTestItemWidget::slot_CheckBoxClicked(bool checked)
{
	QSttCheckBox* senderCheckBox = qobject_cast<QSttCheckBox*>(sender()); // 获取发送信号的复选框
	if (!senderCheckBox) 
	{
		return;
	}

	QPoint checkBoxPos = senderCheckBox->mapToGlobal(QPoint(0, 0)); // 将控件坐标转换为全局屏幕坐标
	int rowIndex = m_pVolTimeTypeTestItemTableWidget->indexAt(m_pVolTimeTypeTestItemTableWidget->viewport()->mapFromGlobal(checkBoxPos)).row(); // 获取复选框所在的行

	if (rowIndex < 0) 
	{
		return;
	}

	CString strID;

	strID.Format(_T("TestItem%d"), rowIndex+1);
	CDataGroup *pTestItemData = (CDataGroup *)m_pVolTimeTypeSecDataGroup->FindByID(strID);
	CString strValue;
	if (checked)
	{
		strValue = _T("1");
	}
	else
	{
		strValue = _T("0");
	}
	if (pTestItemData)
	{
		pTestItemData->SetDataValue(_T("isValid"), strValue);

	}


	//g_pVolTimeTypeSecTestMain->SaveXml();
}


