#include "stateparatab.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
//#include "../SttTestCntrFrameBase.h"
#include "../Controls/SttTabWidget.h"
#include "../../XLangResource_Native.h"


QStateParaTab::QStateParaTab(BOOL *pbTmtParaChanged,QWidget *parent)
	: QWidget(parent)
{
	m_tabWidget = NULL;
	m_pUIParaWidget = NULL;		//电压电流设置
	//m_pStateParaWidget = NULL;	//状态参数设置
	m_pHarmParaWidget = NULL;	//谐波设置
	m_pExBinParaWidget = NULL;	//扩展开入设置
	m_pExBoutParaWidget = NULL;	//扩展开出设置
	m_pGooseParaWidget = NULL;	//GOOSE数据发送
	m_pFT3OutParaWidget=NULL;
	m_pGooseAbnParaWidget = NULL;
	m_pSVParaSet = NULL;

	m_pbTmtParaChanged = pbTmtParaChanged;
	

	m_tabWidget = new QSttTabWidget(this);
	connect(m_tabWidget,SIGNAL(currentChanged(int)),this,SLOT(slot_TabPageChanged(int)));

	initUI();
}

QStateParaTab::~QStateParaTab()
{
}

void QStateParaTab::initUI()
{
	m_pUIParaWidget = new QBasicTestParaSet(this);

	//QStateParaWidget(BOOL *pbTmtParaChanged,QWidget *parent = 0);

	//m_pStateParaWidget = new QStateParaWidget(m_pbTmtParaChanged, this);

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"State_UISet");
	m_tabWidget->addTab(m_pUIParaWidget,strTitle);

	xlang_GetLangStrByFile(strTitle,"State_StateParaSet");
	//m_tabWidget->addTab(m_pStateParaWidget,strTitle);

	AddHarmParaset();  //固定有谐波设置页面

// 	QFont font = m_tabWidget->font();
// 	font.setPointSize(20);
// 	m_tabWidget->setFont(font);

	m_tabWidget->setFont(*g_pSttGlobalFont);

	QVBoxLayout* m_pVBoxLayout = new QVBoxLayout(this);
	m_pVBoxLayout->addWidget(m_tabWidget);
	m_pVBoxLayout->setMargin(0);
	m_pVBoxLayout->setSpacing(0);
	setLayout(m_pVBoxLayout);	
}

void QStateParaTab::AddHarmParaset()
{
	if(m_pHarmParaWidget)
	{
		return;
	}

	m_pHarmParaWidget = new QBasicTestParaSet();
//	m_tabWidget->insertTab(2,m_pHarmParaWidget,tr("谐波设置"));

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Harm_Set");
	m_tabWidget->insertTab(2,m_pHarmParaWidget,strTitle);
}

void QStateParaTab::RemoveHarmParaset()
{
	if(m_pHarmParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_tabWidget->indexOf(m_pHarmParaWidget);
	m_tabWidget->removeTab(nIndex);

	delete m_pHarmParaWidget;
	m_pHarmParaWidget = NULL;
}

void QStateParaTab::AddExBinParaWidget()
{
	if (m_pExBinParaWidget)
	{
		return;
	}

	m_pExBinParaWidget = new ExSwitchSet(ExInput);
	int nInsertPos = 2;

	if (ExistHarmParaset())
	{
		nInsertPos = 3;
	}

//	m_tabWidget->insertTab(nInsertPos,m_pExBinParaWidget,tr("开入设置(扩展)"));

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_ExBinSet");
	m_tabWidget->insertTab(nInsertPos,m_pExBinParaWidget,strTitle);
}

void QStateParaTab::RemoveExBinParaWidget()
{
	if(m_pExBinParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_tabWidget->indexOf(m_pExBinParaWidget);
	m_tabWidget->removeTab(nIndex);

	delete m_pExBinParaWidget;
	m_pExBinParaWidget = NULL;
}

void QStateParaTab::AddExBoutParaWidget()
{
	if (m_pExBoutParaWidget)
	{
		return;
	}

	m_pExBoutParaWidget = new ExSwitchSet(ExOutPut);
	int nInsertPos = 2;

	if (ExistHarmParaset())
	{
		nInsertPos++;
	}

	if (ExistExBinParaWidget())
	{
		nInsertPos++;
	}

//	m_tabWidget->insertTab(nInsertPos,m_pExBoutParaWidget,tr("开出设置(扩展)"));

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_ExBoutSet");
	m_tabWidget->insertTab(nInsertPos,m_pExBoutParaWidget,strTitle);
}

void QStateParaTab::RemoveExBoutParaWidget()
{
	if(m_pExBoutParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_tabWidget->indexOf(m_pExBoutParaWidget);
	m_tabWidget->removeTab(nIndex);

	delete m_pExBoutParaWidget;
	m_pExBoutParaWidget = NULL;
}

void QStateParaTab::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas,FALSE);
	m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
	int nInsertPos = 2;

	if (ExistHarmParaset())
	{
		nInsertPos++;
	}

	if (ExistExBinParaWidget())
	{
		nInsertPos++;
	}

	if (ExistExBoutParaWidget())
	{
		nInsertPos++;
	}

//	m_tabWidget->insertTab(nInsertPos,m_pExBoutParaWidget,tr("开出设置(扩展)"));

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	m_tabWidget->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QStateParaTab::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}

	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV,FALSE);//20240304 suyang 修改为FALSE，状态序列切换状态时会改变使能
	m_pFT3OutParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
	int nInsertPos = 3;

	if (ExistHarmParaset())
	{
		nInsertPos++;
	}

	if (ExistExBinParaWidget())
	{
		nInsertPos++;
	}

	if (ExistExBoutParaWidget())
	{
		nInsertPos++;
	}


	CString strTitle;
	strTitle=/*_T("FT3发布")*/g_sLangTxt_Gradient_ReleasedFTT; //lcq
	m_tabWidget->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QStateParaTab::RemoveFT3OutParaWidget()
{
	if(m_pFT3OutParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_tabWidget->indexOf(m_pFT3OutParaWidget);
	m_tabWidget->removeTab(nIndex);

	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;
}

void QStateParaTab::RemoveGooseParaWidget()
{
	if(m_pGooseParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_tabWidget->indexOf(m_pGooseParaWidget);
	m_tabWidget->removeTab(nIndex);

	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

bool QStateParaTab::ExistHarmParaset()
{
	int nIndex = m_tabWidget->indexOf(m_pHarmParaWidget);
	return (nIndex>=0);
}

bool QStateParaTab::ExistExBinParaWidget()
{
	int nIndex = m_tabWidget->indexOf(m_pExBinParaWidget);
	return (nIndex>=0);
}

bool QStateParaTab::ExistExBoutParaWidget()
{
	int nIndex = m_tabWidget->indexOf(m_pExBoutParaWidget);
	return (nIndex>=0);
}

bool QStateParaTab::ExistGooseParaWidget()
{
	int nIndex = m_tabWidget->indexOf(m_pGooseParaWidget);
	return (nIndex>=0);
}

bool QStateParaTab::ExistFT3OutParaWidget()
{
	int nIndex = m_tabWidget->indexOf(m_pFT3OutParaWidget);
	return (nIndex>=0);
}

void QStateParaTab::EnableBinParaWidget(bool b)
{
	if (ExistExBinParaWidget())
	{
		m_tabWidget->setTabEnabled(m_tabWidget->indexOf(m_pExBinParaWidget),b);
	}
}

void QStateParaTab::EnableBoutParaWidget(bool b)
{
	if (ExistExBoutParaWidget())
	{
		m_tabWidget->setTabEnabled(m_tabWidget->indexOf(m_pExBoutParaWidget),b);
	}
}

void QStateParaTab::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		m_tabWidget->setTabEnabled(m_tabWidget->indexOf(m_pGooseParaWidget),b);
	}
}

void QStateParaTab::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		m_tabWidget->setTabEnabled(m_tabWidget->indexOf(m_pFT3OutParaWidget),b);
	}
}

void QStateParaTab::slot_TabPageChanged(int index)
{
	QString strName = m_tabWidget->tabText(index);
	if (!strName.isEmpty())
	{
		if (strName.contains(/*tr("电压电流")*/g_sLangTxt_State_VoltageandCurrent)) //lcq
		{
			if(m_pUIParaWidget != NULL)
			{
				m_pUIParaWidget->initData();
			}
		}
// 		else if (strName.contains(tr("状态参数")))
// 		{
// 			if(m_pStateParaWidget != NULL)
// 			{
// 				m_pStateParaWidget->UpdateData();
// 			}
// 		}
		else if (strName.contains(/*tr("GOOSE报文参数")*/g_sLangTxt_State_GOOSEmessageparameters)) //lcq
		{
			if(m_pGooseAbnParaWidget != NULL)
			{
				m_pGooseAbnParaWidget->UpdateStateTimeUI();
			}
		}
		else if (strName.contains(/*tr("谐波")*/g_sLangTxt_State_Harmonicwave)) //lcq
		{
			if(m_pHarmParaWidget != NULL)
			{
				m_pHarmParaWidget->initData();
			}
		}
		else if(strName.contains(/*tr("扩展开入")*/g_sLangTxt_Native_BinEx)) //lcq
		{
			if(m_pExBinParaWidget != NULL)
			{
				m_pExBinParaWidget->updateData();
			}
		}
		else if(strName.contains(/*tr("扩展开出")*/g_sLangTxt_Native_BoutEx)) //lcq
		{
			if(m_pExBoutParaWidget != NULL)
			{
				m_pExBoutParaWidget->updateData();
			}
		}
	}	
}

void QStateParaTab::startInit()
{
    if (m_pUIParaWidget != NULL)
    {
		m_pUIParaWidget->startInit(FALSE);
    }

// 	if (m_pStateParaWidget != NULL)
// 	{
// 		m_pStateParaWidget->startInit();
// 	}

	if (m_pSVParaSet != NULL)
	{
		m_pSVParaSet->setDisabled(true);
	}

	if (m_pHarmParaWidget != NULL)
	{
		m_pHarmParaWidget->setEnabled(false);
	}

	EnableSubParaWidget(FALSE);
}

void QStateParaTab::stopInit()
{
	if (m_pUIParaWidget != NULL)
	{
		m_pUIParaWidget->stopInit(TRUE);
	}

// 	if (m_pStateParaWidget != NULL)
// 	{
// 		m_pStateParaWidget->stopInit();
// 	}

	if (m_pSVParaSet != NULL)
	{
		m_pSVParaSet->setDisabled(false);
	}

	if (m_pHarmParaWidget != NULL)
	{
		m_pHarmParaWidget->setEnabled(true);
	}

	EnableSubParaWidget(TRUE);
}

void QStateParaTab::EnableSubParaWidget(bool bEnable)
{
	if (m_pHarmParaWidget != NULL)
	{
		m_pHarmParaWidget->startInit(bEnable);
	}

	if(m_pExBinParaWidget != NULL)
	{
		m_pExBinParaWidget->m_pTable->setDisabled(!bEnable);
		m_pExBinParaWidget->ck_SelectAll->setDisabled(!bEnable);
	}

	if(m_pExBoutParaWidget != NULL)
	{
		m_pExBoutParaWidget->m_pTable->setDisabled(!bEnable);
		m_pExBoutParaWidget->ck_SelectAll->setDisabled(!bEnable);
	}

	if (m_pGooseParaWidget!= NULL)
	{
		if(bEnable)
		{
			m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
			m_pGooseParaWidget->SetGooseDisabled(FALSE);
		}
		else
		{
			m_pGooseParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_NotEditable);
			m_pGooseParaWidget->SetGooseDisabled(TRUE);
		}
	}

	if (m_pFT3OutParaWidget!= NULL)
	{
		if(bEnable)
		{
			m_pFT3OutParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
			m_pFT3OutParaWidget->SetGooseDisabled(FALSE);
		}
		else
		{
			m_pFT3OutParaWidget->SetRunState(STT_UI_RUN_STATE_StateTested_NotEditable);
			m_pFT3OutParaWidget->SetGooseDisabled(TRUE);
		}
	}
}
