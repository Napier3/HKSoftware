#include "SttReplayParaSetWidget.h"
//#include "../replaytest.h"
#include "SttMacroParaEditViewTransPlay.h" 
//#include "../SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"
#include "../../XLanguage/QT/XLanguageAPI_QT.h"

CSttReplayParaSetWidget::CSttReplayParaSetWidget(CSttModulesComtradeBind *pChMapConfig,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_pSttReplayTriggerWidget =NULL;
	m_pWaveformEditWidget = NULL;
	m_pDigitalModuleWidget = NULL;

	//设置水平表头
//	ui.tableWidgetIns->horizontalHeader()->resizeSection(0,ui.tableWidgetIns->width()/2); //设置表头第1列的宽度
	ui.tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#2a9ee4;}"); //设置表头背景色transparent
	ui.tableWidgetIns->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#2a9ee4;}"); //设置表头背景色transparent
// 	ui.tableWidgetIns->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
// 	//设置垂直表头
// 	ui.tableWidgetIns->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
// 	ui.tableWidgetIns->verticalHeader()->setVisible(false); //设置垂直头不可见

	ui.tableWidget->setFocusPolicy(Qt::NoFocus);
	ui.tableWidgetIns->setFocusPolicy(Qt::NoFocus);
	init(pChMapConfig,parent);
	
	ui.tabWidget->setTabText(ui.tabWidget->indexOf(ui.tab_5), g_sLangTxt_Native_SamplingFrequency);
}

CSttReplayParaSetWidget::~CSttReplayParaSetWidget()
{
	m_oComtradeVolChs_Ref.RemoveAll();
	m_oComtradeCurChs_Ref.RemoveAll();
}

void CSttReplayParaSetWidget::setData(PTMT_PARAS_HEAD pCurr)
{
}

void CSttReplayParaSetWidget::setDvm( CDataGroup *pDvmData )
{
}

void CSttReplayParaSetWidget::startInit()
{
	long nCount = ui.tabWidget->count();
	QWidget *pCurWidhet = NULL;

	for (int nIndex = 0;nIndex<nCount;nIndex++)
	{
		pCurWidhet = ui.tabWidget->widget(nIndex);

		if (pCurWidhet != NULL)
		{
			pCurWidhet->setEnabled(false);
		}
	}
}

void CSttReplayParaSetWidget::stopInit()
{
	long nCount = ui.tabWidget->count();
	QWidget *pCurWidhet = NULL;

	for (int nIndex = 0;nIndex<nCount;nIndex++)
	{
		pCurWidhet = ui.tabWidget->widget(nIndex);

		if (pCurWidhet != NULL)
		{
			pCurWidhet->setEnabled(true);
		}
	}
}

long CSttReplayParaSetWidget::GetTotalChannelNum()
{
	ASSERT(m_pSttModulesComtradeBind != NULL);
	long nNum = 0;

	POS pos = m_pSttModulesComtradeBind->GetHeadPosition();
	CSttModuleComtradeBind *pModule = NULL;

	while(pos != NULL)
	{
		pModule = (CSttModuleComtradeBind *)m_pSttModulesComtradeBind->GetNext(pos);

		if(!pModule->IsBinaryTypeModule())
		{
			nNum += pModule->GetCount();
		}
	}

	return nNum;
}

void CSttReplayParaSetWidget::clearTable()
{
	ui.tableWidget->clear();
	ui.tableWidgetIns->clear();

	//模拟量
	CSttReplayModuleChWidget *pSttReplayModuleChWidget = NULL;
	for (int i=0; i<m_oSttReplayModuleChWidgetList.size(); i++)
	{
		pSttReplayModuleChWidget = m_oSttReplayModuleChWidgetList.at(i);
//		pSttReplayModuleChWidget->dis
		delete pSttReplayModuleChWidget;
	}

	m_oSttReplayModuleChWidgetList.clear();

	if (m_pSttReplayTriggerWidget != NULL)
	{
		delete m_pSttReplayTriggerWidget;
		m_pSttReplayTriggerWidget = NULL;
	}

	if (m_pWaveformEditWidget != NULL)
	{
		delete m_pWaveformEditWidget;
		m_pWaveformEditWidget = NULL;
	}


	//数字量
	if (m_pDigitalModuleWidget != NULL)
	{
		m_pDigitalModuleWidget->clearTab();
		delete m_pDigitalModuleWidget;
		m_pDigitalModuleWidget = NULL;
	}
}

void CSttReplayParaSetWidget::init(CSttModulesComtradeBind *pSttModulesComtradeBind,QWidget *parent)
{
	//20221020 sy 注销
	//SetTabWidget(ui.tabWidget);
	m_pSttModulesComtradeBind = pSttModulesComtradeBind;
	clearTable();

	QStringList header;
	header << g_sLangTxt_Native_SamplingFrequency << g_sLangTxt_Samples;
	ui.tableWidget->setHorizontalHeaderLabels(header);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections  Section
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列自行填充; //设置充满表宽度
#else
    ui.tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//列自行填充; //设置充满表宽度
#endif

    //ui.tableWidget->horizontalHeader()->setFont(QFont("song",16));

	QStringList header1;
	header1<<g_sLangTxt_Name<<g_sLangTxt_Momentaryvalue;
	ui.tableWidgetIns->setHorizontalHeaderLabels(header1);
	ui.tableWidgetIns->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections  Section
    ui.tableWidgetIns->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列自行填充; //设置充满表宽度
#else
    ui.tableWidgetIns->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//列自行填充; //设置充满表宽度
#endif

    ui.tableWidgetIns->setRowCount(GetTotalChannelNum());
    //ui.tableWidgetIns->horizontalHeader()->setFont(QFont("song",16));

	POS pos = m_pSttModulesComtradeBind->GetHeadPosition();
	CSttModuleComtradeBind *pModuleInfo = NULL;
	int nModuleIndex = 0;
	CSttReplayModuleChWidget *pSttReplayModuleChWidget = NULL;
	int nChIndex = 0;
	CString strTabName, strDigitalTabName;;

	while(pos != NULL)
	{
		pModuleInfo = (CSttModuleComtradeBind *)m_pSttModulesComtradeBind->GetNext(pos);

		if(/*!pModuleInfo->IsBinaryTypeModule()*/g_oSystemParas.m_nHasAnalog &&pModuleInfo->IsAnalogTypeModule())
		{
			//增加了模块1 2
			pSttReplayModuleChWidget = new CSttReplayModuleChWidget(nModuleIndex,pModuleInfo,this);
			m_oSttReplayModuleChWidgetList.append(pSttReplayModuleChWidget);
			strTabName = pModuleInfo->m_strName;//(tr("模块%1")).arg(nModuleIndex+1);
			xlang_GetLangStrByFile(g_sLangTxt_Module1,"Module1");
            ui.tabWidget->insertTab(nModuleIndex,pSttReplayModuleChWidget,strTabName);
			nModuleIndex++;

			connect(pSttReplayModuleChWidget,SIGNAL(sig_ModuleChChanged(int,int)),g_pReplayTestMain,SLOT(slot_ModuleChChanged(int,int)));  // slot_ModuleChChanged 用于更新波形图
			connect(pSttReplayModuleChWidget,SIGNAL(sig_ModuleChRangeChanged()),g_pReplayTestMain,SLOT(slot_ModuleChRangeChanged()));  // slot_ModuleChChanged 用于更新波形图

			POS posCh = pModuleInfo->GetHeadPosition();
			CSttModuleChComtradeBind *pCh = NULL;
			QTableWidgetItem *item = NULL;

			while(posCh != NULL)
			{
				pCh = (CSttModuleChComtradeBind *)pModuleInfo->GetNext(posCh);

				item = new QTableWidgetItem();
				item->setTextAlignment(Qt::AlignCenter);
				item->setText(pCh->m_strID);
				ui.tableWidgetIns->setItem(nChIndex, 0, item);

				item = new QTableWidgetItem();
				item->setTextAlignment(Qt::AlignCenter);
				ui.tableWidgetIns->setItem(nChIndex, 1, item);

				nChIndex++;
			}
		}
		else if(pModuleInfo->IsDigitalTypeModule() && g_oSystemParas.m_nHasDigital)
		{
			m_pDigitalModuleWidget = new QSttReplayDigitalModuleWidget(nModuleIndex,pModuleInfo,this);
			strDigitalTabName = pModuleInfo->m_strName;
// 			m_pDigitalModuleWidget->CreatModuleChWidget();
	
			//采样信息
			POS posCh = pModuleInfo->GetHeadPosition();
			CSttModuleChComtradeBind *pCh = NULL;
			QTableWidgetItem *item = NULL;
			while(posCh != NULL)
			{
				pCh = (CSttModuleChComtradeBind *)pModuleInfo->GetNext(posCh);

				item = new QTableWidgetItem();
				item->setTextAlignment(Qt::AlignCenter);
				item->setText(pCh->m_strName);
				ui.tableWidgetIns->setItem(nChIndex, 0, item);

				item = new QTableWidgetItem();
				item->setTextAlignment(Qt::AlignCenter);
				ui.tableWidgetIns->setItem(nChIndex, 1, item);

				nChIndex++;
			}
	}

	}

	if(m_pDigitalModuleWidget)//将数字量添加在模拟量之后
	{
		ui.tabWidget->insertTab(nModuleIndex,m_pDigitalModuleWidget,strDigitalTabName);
		nModuleIndex++;
	}
// 	if(g_pReplayTestMain->isNeedBinaryModule())
// 	{
// 		m_pBinaryOutSetWidget = new CSttReplayBoutModuleChWidget(this,pSttModulesComtradeBind->GetBinaryModule());
// 		ui.tabWidget->insertTab(nModuleIndex++,m_pBinaryOutSetWidget,(_T("开出量设置")));
// 	}

	//增加了触发条件

	m_pSttReplayTriggerWidget = new CSttReplayTriggerWidget(this);
	ui.tabWidget->insertTab(nModuleIndex++,m_pSttReplayTriggerWidget,g_sLangTxt_Manual_OtherParam);

	m_pWaveformEditWidget = new SttReplayWaveformEditWidget(this);
    ui.tabWidget->insertTab(nModuleIndex++, m_pWaveformEditWidget,g_sLangTxt_Replay_WaveformEditing);

	ui.tabWidget->setCurrentIndex(0);

	ui.tabWidget->setFont(*g_pSttGlobalFont);
	UpdateStateView(false);
}

void CSttReplayParaSetWidget::InitModuleChList()
{
	QStringList oUChList,oIChList;
	m_oComtradeVolChs_Ref.RemoveAll();
	m_oComtradeCurChs_Ref.RemoveAll();

	CExBaseList *pAnalogList = g_theBigComtradeTransPlay->GetAnalogs();

	POS pos = pAnalogList->GetHeadPosition();
	CComtradeAnalogData *pAnalogData = NULL;

	while(pos != NULL)
	{
		pAnalogData = (CComtradeAnalogData *)pAnalogList->GetNext(pos);

		if (pAnalogData->IsAnalogUData())
		{
			oUChList.append(pAnalogData->m_strName);
			m_oComtradeVolChs_Ref.AddTail(pAnalogData);
		}
		else
		{
			oIChList.append(pAnalogData->m_strName);
			m_oComtradeCurChs_Ref.AddTail(pAnalogData);
		}
	}

	CSttReplayModuleChWidget *pSttReplayModuleChWidget = NULL;

	if(g_pReplayTestMain->isNeedAnalogModule())
	{
	for (int nIndex=0; nIndex<m_oSttReplayModuleChWidgetList.size(); nIndex++)
	{
		pSttReplayModuleChWidget = m_oSttReplayModuleChWidgetList.at(nIndex);
		pSttReplayModuleChWidget->SetChSelectList(oUChList,oIChList);
	}
	}

	if (g_pReplayTestMain->isNeedDigitalModule() && m_pDigitalModuleWidget)
	{
		m_pDigitalModuleWidget->InitDigitalModuleChList(oUChList,oIChList);
	}

	UpdateStateView(true);
	connect(ui.tabWidget, SIGNAL(currentChanged(QWidget *)), this, SLOT(slot_TabChanged(QWidget *)));
}

void CSttReplayParaSetWidget::InitSttReplayTriggerWidget()
{
	m_pSttReplayTriggerWidget->InitSttReplayTriggerWidget();
}

void CSttReplayParaSetWidget::InitSttReplayWaveEditWidget()
{
	m_pWaveformEditWidget->InitWaveEditWidget();
}

void CSttReplayParaSetWidget::initTabPage()
{
	if (g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_nSamAmount <= 0)
	{
		return;
	}

	ui.tableWidget->clear();
	QStringList header;
	header<<g_sLangTxt_IEC_SamplingRate	<<g_sLangTxt_Samples;
	ui.tableWidget->setHorizontalHeaderLabels(header);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections  Section
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列自行填充; //设置充满表宽度
#else
    ui.tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//列自行填充; //设置充满表宽度
#endif

	ui.tableWidget->setRowCount(g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_nSamAmount);

	QTableWidgetItem *item = NULL;
	for (int i=0; i<g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_nSamAmount; i++)
	{
		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignCenter);
		item->setText(QString::number(g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_pdSamRate[i],'f',4));
		ui.tableWidget->setItem(i, 0, item); 

		item = new QTableWidgetItem();
		item->setTextAlignment(Qt::AlignCenter);
		item->setText(QString::number(g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_pnDataPoints[i],10));
		ui.tableWidget->setItem(i, 1, item); 
	}	
}

void CSttReplayParaSetWidget::UpdateStateView(bool bEnable)
{
	if(g_pReplayTestMain->isNeedAnalogModule())
	{
	for (int i=0; i<m_oSttReplayModuleChWidgetList.size(); i++)
	{
		m_oSttReplayModuleChWidgetList.at(i)->setEnableStateUI(bEnable);
	}
	}

	if(g_pReplayTestMain->isNeedDigitalModule())
	{	
		if(m_pDigitalModuleWidget != NULL)
		{
		m_pDigitalModuleWidget->setEnableStateUI(bEnable);

		}
		
	}


	m_pSttReplayTriggerWidget->setDisabled(!bEnable);
	m_pWaveformEditWidget->setDisabled(!bEnable);
}

//刷新通道瞬时值
void CSttReplayParaSetWidget::UpdateChMomentaryVal()
{
	POS pos = m_pSttModulesComtradeBind->GetHeadPosition();
	CSttModuleComtradeBind *pModuleInfo = NULL;
	int nChIndex = 0;
	CString strValue = _T("");

	while(pos != NULL)
	{
		pModuleInfo = (CSttModuleComtradeBind *)m_pSttModulesComtradeBind->GetNext(pos);
		if((pModuleInfo->IsAnalogTypeModule() && g_oSystemParas.m_nHasAnalog)||
			(pModuleInfo->IsDigitalTypeModule() && g_oSystemParas.m_nHasDigital)||
			(pModuleInfo->IsWeekTypeModule() && g_oSystemParas.m_nHasWeek))
		{
			POS posCh = pModuleInfo->GetHeadPosition();
			CSttModuleChComtradeBind *pCh = NULL;
			CString strValue;

			while(posCh != NULL)
			{
				pCh = (CSttModuleChComtradeBind *)pModuleInfo->GetNext(posCh);

				if (pCh->IsModuleType_U())
				{
					strValue.Format(_T("%.03lf V"),pCh->m_fMomentaryVal);
				} 
				else
				{
					strValue.Format(_T("%.03lf A"),pCh->m_fMomentaryVal);
				}

				ui.tableWidgetIns->item(nChIndex,1)->setText(strValue);
				nChIndex++;
			}
		}

	}
}

void CSttReplayParaSetWidget::UpdateEditData()
{
	for (int i=0; i<m_oSttReplayModuleChWidgetList.size(); i++)
	{
		m_oSttReplayModuleChWidgetList.at(i)->UpdateEditData();
	}

// 	for (int i=0; i<m_oSttReplayWeekModuleChWidgetList.size(); i++)
// 	{
// 		m_oSttReplayWeekModuleChWidgetList.at(i)->UpdateEditData();
// 	}

	m_pSttReplayTriggerWidget->UpdateEditData();

}

void CSttReplayParaSetWidget::slot_OpenRcdFileClicked()
{
	if (g_pReplayTestMain != NULL) 
	{
		g_pReplayTestMain->OpenComtradeFile();
//		UpdateUIMax();
	}
}

void CSttReplayParaSetWidget::slot_TabChanged(QWidget *pCurWidget)
{
	CSttReplayModuleChWidget *pSttReplayModuleChWidget = NULL;
	BOOL bHasFind = FALSE;

	for (int nIndex =0; nIndex<m_oSttReplayModuleChWidgetList.size(); nIndex++)
	{
		pSttReplayModuleChWidget = m_oSttReplayModuleChWidgetList.at(nIndex);

		if (pSttReplayModuleChWidget == pCurWidget)
		{
			bHasFind = TRUE;
			pSttReplayModuleChWidget->UpdatePT_CT_Rates();
			break;
		}
	}

	if (bHasFind)
	{
		pSttReplayModuleChWidget->SetDefaultFocusCtrl();
	}

	if(pCurWidget == m_pWaveformEditWidget)
	{
		InitSttReplayWaveEditWidget();
	}
}

void CSttReplayParaSetWidget::AddTabWidget(QWidget *pCurWidget,const QString &strTitle)
{
    ui.tabWidget->addTab(pCurWidget, strTitle);
}

void CSttReplayParaSetWidget::UpdateUIMax()
{
	CSttReplayModuleChWidget *pSttReplayModuleChWidget = NULL;
	double fUMax,fIMax;

	if(g_pReplayTestMain->isNeedAnalogModule())
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.GetReplayChMaxValue(fUMax,fIMax,REPLAY_MODULE_TYPE_ANALOG);

		for (int nIndex = 0; nIndex < m_oSttReplayModuleChWidgetList.size(); nIndex++)
	{
		pSttReplayModuleChWidget = m_oSttReplayModuleChWidgetList.at(nIndex);
			pSttReplayModuleChWidget->UpdateUIMax(fUMax, fIMax);
		}
	}

	if(g_pReplayTestMain->isNeedDigitalModule())
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.GetReplayChMaxValue(fUMax,fIMax,REPLAY_MODULE_TYPE_DIGITAL);
		m_pDigitalModuleWidget->UpdateUIMax(fUMax,fIMax);//数字模块需要分组更新最大最小电压电流
	}

}

CComtradeAnalogData* CSttReplayParaSetWidget::GetComtradeAnalogU(long nIndex)
{
	return (CComtradeAnalogData*)m_oComtradeVolChs_Ref.GetAtIndex(nIndex);
}

CComtradeAnalogData* CSttReplayParaSetWidget::GetComtradeAnalogI(long nIndex)
{
	return (CComtradeAnalogData*)m_oComtradeCurChs_Ref.GetAtIndex(nIndex);
}

void CSttReplayParaSetWidget::slot_UpdateTwoCursorTimeValues(double dValueA,double dValueB)
{
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("执行更新坐标信号,slot_UpdateTwoCursorTimeValues."));
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.GetReplayBufFixedMomentaryVal(0,dValueA,
		g_theBigComtradeTransPlay->m_oBigComtradeFileRead.m_dInsertFreq);
	UpdateChMomentaryVal();
	CSttReplayModuleChWidget *pSttReplayModuleChWidget = NULL;

	if(g_pReplayTestMain->isNeedAnalogModule())
	{
	for (int nIndex =0; nIndex<m_oSttReplayModuleChWidgetList.size(); nIndex++)
	{
		pSttReplayModuleChWidget = m_oSttReplayModuleChWidgetList.at(nIndex);
		pSttReplayModuleChWidget->UpdateTwoCursorTimeValues(dValueA,dValueB);
	}
	}

	if(g_pReplayTestMain->isNeedDigitalModule())
	{	
		m_pDigitalModuleWidget->UpdateTwoCursorTimeValues(dValueA,dValueB);
	}
}

int CSttReplayParaSetWidget::GetWaveEditType()
{
	if(m_pWaveformEditWidget)
	{
		return m_pWaveformEditWidget->GetWaveEditType();
	}
	return -1;
}

int CSttReplayParaSetWidget::GetInsertNormalType()
{
	if (m_pWaveformEditWidget)
	{
		return m_pWaveformEditWidget->GetInsertNormalType();
	}

	return -1;
}
