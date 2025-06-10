#include "SttReplayParaSetWidget.h"
//#include "../replaytest.h"
#include "SttMacroParaEditViewTransPlay.h" 
//#include "../SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"
#include "../../XLanguage/QT/XLanguageAPI_QT.h"
#include "SttReplayWeekModuleChWidget.h"

CSttReplayParaSetWidget::CSttReplayParaSetWidget(CSttModulesComtradeBind *pChMapConfig,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_pSttReplayTriggerWidget =NULL;
	m_pWaveformEditWidget = NULL;
	m_pDigitalModuleWidget = NULL;
	m_pBinaryOutSetWidget = NULL;

	//设置水平表头
//	ui.tableWidgetIns->horizontalHeader()->resizeSection(0,ui.tableWidgetIns->width()/2); //设置表头第1列的宽度
	ui.tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#2a9ee4;}"); //设置表头背景色transparent
	ui.tableWidgetIns->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#2a9ee4;}"); //设置表头背景色transparent
// 	ui.tableWidgetIns->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
// 	//设置垂直表头
// 	ui.tableWidgetIns->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
// 	ui.tableWidgetIns->verticalHeader()->setVisible(false); //设置垂直头不可见

	ui.tableWidget->setFocusPolicy(Qt::NoFocus);
	ui.tableWidgetIns->setFocusPolicy(Qt::NoFocus);
	init(pChMapConfig,parent);
	
	ui.tabWidget->setTabText(ui.tabWidget->indexOf(ui.tab_5),g_sLangTxt_IEC_SamplingRate);
}

CSttReplayParaSetWidget::~CSttReplayParaSetWidget()
{
	m_oComtradeVolChs_Ref.RemoveAll();
	m_oComtradeCurChs_Ref.RemoveAll();
	m_oComtradeBinaryChs_Ref.RemoveAll();

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
		delete pSttReplayModuleChWidget;
	}

	m_oSttReplayModuleChWidgetList.clear();

	//弱信号
	for (int i=0; i<m_oSttReplayWeekModuleChWidgetList.size(); i++)
	{
		pSttReplayModuleChWidget = m_oSttReplayWeekModuleChWidgetList.at(i);
		delete pSttReplayModuleChWidget;
	}
	m_oSttReplayWeekModuleChWidgetList.clear();


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

	//开出量扩展
	CSttReplayBoutModuleChWidget* pBoutModuleChWidget = NULL;
	for(int i=0;i<m_oBinaryOutSetExList.size();++i)
	{
		pBoutModuleChWidget = m_oBinaryOutSetExList.at(i);
		delete pBoutModuleChWidget;
	}
	m_oBinaryOutSetExList.clear();

	//主板开出
	if (m_pBinaryOutSetWidget != NULL)
	{
		delete m_pBinaryOutSetWidget;
		m_pBinaryOutSetWidget = NULL;
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
	header<<g_sLangTxt_IEC_SamplingRate<<g_sLangTxt_Samples;
	ui.tableWidget->setHorizontalHeaderLabels(header);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列自行填充; //设置充满表宽度
	ui.tableWidget->horizontalHeader()->setFont(QFont("song",16));

	QStringList header1;
	header1<<g_sLangTxt_Name<<g_sLangTxt_Momentaryvalue;
	ui.tableWidgetIns->setHorizontalHeaderLabels(header1);
	ui.tableWidgetIns->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui.tableWidgetIns->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列自行填充; //设置充满表宽度
	ui.tableWidgetIns->setRowCount(GetTotalChannelNum());
	ui.tableWidgetIns->horizontalHeader()->setFont(QFont("song",16));

	POS pos = m_pSttModulesComtradeBind->GetHeadPosition();
	CSttModuleComtradeBind *pModuleInfo = NULL;
	CSttReplayBoutModuleChWidget* pBoutModuleCWidget = NULL;

	int nModuleIndex = 0;
	CSttReplayModuleChWidget *pSttReplayModuleChWidget = NULL;
	int nChIndex = 0;
	QString strTabName, strDigitalTabName;
	CString strAnalogName = _T("模"),strWeekName = _T("弱");

	while(pos != NULL)
	{
		pModuleInfo = (CSttModuleComtradeBind *)m_pSttModulesComtradeBind->GetNext(pos);

		if(/*!pModuleInfo->IsBinaryTypeModule()*/g_oSystemParas.m_nHasAnalog &&pModuleInfo->IsAnalogTypeModule())
		{
			//增加了模块1 2
			pSttReplayModuleChWidget = new CSttReplayModuleChWidget(nModuleIndex,pModuleInfo,this);
			m_oSttReplayModuleChWidgetList.append(pSttReplayModuleChWidget);
// 			strTabName = pModuleInfo->m_strName;//(tr("模块%1")).arg(nModuleIndex+1);
			//xlang_GetLangStrByFile(g_sLangTxt_Module1,"Module1");
// 			strTabName.Format(_T("模块%d (%s-%s)"), nModuleIndex+1, strAnalogName, pModuleInfo->m_strName);
			strTabName = QString("模块%1 (%2-%3)").arg(nModuleIndex + 1).arg(strAnalogName).arg(g_sLangTxt_State_VoltageandCurrent);

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
		else if(g_oSystemParas.m_nHasWeek &&pModuleInfo->IsWeekTypeModule())
		{
			//增加了模块1 2
			pSttReplayModuleChWidget = new CSttReplayWeekModuleChWidget(nModuleIndex,pModuleInfo,this);
			m_oSttReplayWeekModuleChWidgetList.append(pSttReplayModuleChWidget);
// 			strTabName.Format(_T("模块%d (%s-%s)"), nModuleIndex+1, strWeekName, pModuleInfo->m_strName);
			strTabName = QString("模块%1 (%2-%3)").arg(nModuleIndex + 1).arg(strWeekName).arg(g_sLangTxt_State_VoltageandCurrent);

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
		else if(pModuleInfo->IsBinaryTypeModule())
		{
			pBoutModuleCWidget = new CSttReplayBoutModuleChWidget(this,pModuleInfo);
			m_oBinaryOutSetExList.append(pBoutModuleCWidget);
			strTabName = pModuleInfo->m_strName;//(tr("模块%1")).arg(nModuleIndex+1);
			ui.tabWidget->addTab(pBoutModuleCWidget,strTabName);
		}

	}

	if(m_pDigitalModuleWidget)//将数字量添加在模拟量之后
	{
		ui.tabWidget->insertTab(nModuleIndex,m_pDigitalModuleWidget,strDigitalTabName);
		nModuleIndex++;
	}
	if(g_pReplayTestMain->isNeedBinaryModule())
	{
		m_pBinaryOutSetWidget = new CSttReplayBoutModuleChWidget(this,pSttModulesComtradeBind->GetBinaryModule());
		ui.tabWidget->insertTab(nModuleIndex++,m_pBinaryOutSetWidget,(_T("开出量设置")));
	}

	//增加了触发条件

	m_pSttReplayTriggerWidget = new CSttReplayTriggerWidget(this);
	ui.tabWidget->insertTab(nModuleIndex++,m_pSttReplayTriggerWidget,g_sLangTxt_Manual_OtherParam);

	m_pWaveformEditWidget = new SttReplayWaveformEditWidget(this);
	ui.tabWidget->insertTab(nModuleIndex++, m_pWaveformEditWidget, _T("波形编辑"));

	ui.tabWidget->setCurrentIndex(0);

	m_pPreWidget = m_pSttReplayTriggerWidget;
	if (m_oSttReplayModuleChWidgetList.size() > 0)
	{
		m_pPreWidget = m_oSttReplayModuleChWidgetList.at(0);
	}

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

	if(g_pReplayTestMain->isNeedDigitalModule())
	{
		m_pDigitalModuleWidget->InitDigitalModuleChList(oUChList,oIChList);
	}

	if(g_pReplayTestMain->isNeedWeekModule())
	{
		CSttReplayWeekModuleChWidget *pSttReplayWeekModuleChWidget = NULL;
		for (int nIndex=0; nIndex<m_oSttReplayWeekModuleChWidgetList.size(); nIndex++)
		{
			pSttReplayWeekModuleChWidget = (CSttReplayWeekModuleChWidget *)m_oSttReplayWeekModuleChWidgetList.at(nIndex);
			pSttReplayWeekModuleChWidget->SetWeekEeType();		
			pSttReplayWeekModuleChWidget->SetChSelectList(oUChList,oIChList);
		}
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
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列自行填充; //设置充满表宽度

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
		m_pDigitalModuleWidget->setEnableStateUI(bEnable);
	}

	if(g_pReplayTestMain->isNeedWeekModule())
	{
		for (int i=0; i<m_oSttReplayWeekModuleChWidgetList.size(); i++)
		{
			m_oSttReplayWeekModuleChWidgetList.at(i)->setEnableStateUI(bEnable);
		}
	}

	m_pSttReplayTriggerWidget->setDisabled(!bEnable);
	m_pWaveformEditWidget->setDisabled(!bEnable);

	if(g_pReplayTestMain->isNeedBinaryModule())
	{
		m_pBinaryOutSetWidget->UpdateButtonEnable(bEnable);
	}

	for (int i=0; i<m_oBinaryOutSetExList.size(); i++)
	{
		m_oBinaryOutSetExList.at(i)->UpdateButtonEnable(bEnable);
	}

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

	for (int i=0; i<m_oSttReplayWeekModuleChWidgetList.size(); i++)
	{
		m_oSttReplayWeekModuleChWidgetList.at(i)->UpdateEditData();
	}

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

	for (int nIndex =0; nIndex<m_oSttReplayWeekModuleChWidgetList.size(); nIndex++)
	{
		pSttReplayModuleChWidget = m_oSttReplayWeekModuleChWidgetList.at(nIndex);

		if (pSttReplayModuleChWidget == pCurWidget)
		{
			bHasFind = TRUE;
			pSttReplayModuleChWidget->UpdatePT_CT_Rates();
			break;
		}
	}

	if (m_pSttReplayTriggerWidget == m_pPreWidget)
	{
		m_pSttReplayTriggerWidget->clearFocus();
	}
	else if (m_pWaveformEditWidget == m_pPreWidget)
	{
		m_pWaveformEditWidget->clearFocus();
	}

	if (m_pSttReplayTriggerWidget == pCurWidget)
	{
		m_pSttReplayTriggerWidget->setFocus();
	}
	else if (m_pWaveformEditWidget == pCurWidget)
	{
		m_pWaveformEditWidget->setFocus();
	}

	if (bHasFind)
	{
		pSttReplayModuleChWidget->SetDefaultFocusCtrl();
	}

	if(pCurWidget == m_pWaveformEditWidget)
	{
		InitSttReplayWaveEditWidget();
	}
	m_pPreWidget = pCurWidget;
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

	for (int nIndex =0; nIndex<m_oSttReplayModuleChWidgetList.size(); nIndex++)
	{
		pSttReplayModuleChWidget = m_oSttReplayModuleChWidgetList.at(nIndex);
		pSttReplayModuleChWidget->UpdateUIMax(fUMax,fIMax);
	}
	}

	if(g_pReplayTestMain->isNeedDigitalModule())
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.GetReplayChMaxValue(fUMax,fIMax,REPLAY_MODULE_TYPE_DIGITAL);
		m_pDigitalModuleWidget->UpdateUIMax(fUMax,fIMax);//数字模块需要分组更新最大最小电压电流
	}

	if(g_pReplayTestMain->isNeedWeekModule())
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.GetReplayChMaxValue(fUMax,fIMax,REPLAY_MODULE_TYPE_WEEK);

		for (int nIndex =0; nIndex<m_oSttReplayWeekModuleChWidgetList.size(); nIndex++)
		{
			pSttReplayModuleChWidget = m_oSttReplayWeekModuleChWidgetList.at(nIndex);
			pSttReplayModuleChWidget->UpdateUIMax(fUMax,fIMax);
		}
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

CComtradeBinaryData* CSttReplayParaSetWidget::GetComtradeBinary( long nIndex )
{
	return (CComtradeBinaryData*)m_oComtradeBinaryChs_Ref.GetAtIndex(nIndex);
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

	if(g_pReplayTestMain->isNeedWeekModule())
	{
		for (int nIndex =0; nIndex<m_oSttReplayWeekModuleChWidgetList.size(); nIndex++)
		{
			pSttReplayModuleChWidget = m_oSttReplayWeekModuleChWidgetList.at(nIndex);
			pSttReplayModuleChWidget->UpdateTwoCursorTimeValues(dValueA,dValueB);
		}
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

void CSttReplayParaSetWidget::InitBinaryModuleChList()
{
	disconnect(ui.tabWidget, SIGNAL(currentChanged(QWidget *)), this, SLOT(slot_TabChanged(QWidget *)));
	QStringList oBinaryChList;
	m_oComtradeBinaryChs_Ref.RemoveAll();

	CExBaseList *pBinaryList = g_theBigComtradeTransPlay->GetBinarys();

	if(pBinaryList == NULL)
	{
		return;
	}

	POS pos = pBinaryList->GetHeadPosition();
	CComtradeBinaryData *pBinaryData = NULL;

	while(pos != NULL)
	{
		pBinaryData = (CComtradeBinaryData *)pBinaryList->GetNext(pos);
		oBinaryChList.append(pBinaryData->m_strName);
		m_oComtradeBinaryChs_Ref.AddTail(pBinaryData);
	}

	if(g_pReplayTestMain->isNeedBinaryModule())
	{
		m_pBinaryOutSetWidget->SetChSelectList(oBinaryChList);
	}

	CSttReplayBoutModuleChWidget *pModuleChWidget = NULL;

	for (int nIndex=0; nIndex<m_oBinaryOutSetExList.size(); nIndex++)
	{
		pModuleChWidget = m_oBinaryOutSetExList.at(nIndex);
		pModuleChWidget->SetChSelectList(oBinaryChList);
	}

	UpdateStateView(true);
	connect(ui.tabWidget, SIGNAL(currentChanged(QWidget *)), this, SLOT(slot_TabChanged(QWidget *)));
}

