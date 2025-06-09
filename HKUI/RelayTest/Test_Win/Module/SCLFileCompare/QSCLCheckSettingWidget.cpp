#include "QSCLCheckSettingWidget.h"
#include "..\..\API\GlobalConfigApi.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QTableWidgetItem>
#include "..\SclCheckDataMngr\SclCheckObjectsSet.h"
#include "..\SclCheckDataMngr\SclCheckMngrGlobal.h"

QSCLCheckSettingWidget::QSCLCheckSettingWidget(QWidget* pparent)
{
	m_pSchemaSettings = NULL;
	m_pDL860CheckSettings = NULL;
	m_pProModCheckSettings = NULL;
	m_pVirtualLoopCheckSettings = NULL;
	ui.setupUi(this);
	InitUI();
}

QSCLCheckSettingWidget::~QSCLCheckSettingWidget()
{
	delete m_pSchemaSettingGrid;
	m_pSchemaSettingGrid = NULL;
	delete m_pDL860CheckSettingGrid;
	m_pDL860CheckSettingGrid = NULL;
	delete m_pProModCheckSettingGrid;
	m_pProModCheckSettingGrid = NULL;
	delete m_pVirtualLoopCheckSettingGrid;
	m_pVirtualLoopCheckSettingGrid = NULL;

}

void QSCLCheckSettingWidget::InitUI()
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	m_pSchemaSettingGrid = new QSchemaCheckSettingGrid(this);
	m_pDL860CheckSettingGrid = new QMannualCheckSettingGrid(this);
	m_pProModCheckSettingGrid = new QMannualCheckSettingGrid(this);
	m_pVirtualLoopCheckSettingGrid = new QMannualCheckSettingGrid(this);

	CString strTitle = _T("Schema语法检查设置");
	ui.m_pCheckTab->addTab(m_pSchemaSettingGrid,strTitle);
	strTitle = _T("DL/860数据类型检查设置");
	ui.m_pCheckTab->addTab(m_pDL860CheckSettingGrid,strTitle);
	strTitle = _T("工程应用模型规范性检查设置");
	ui.m_pCheckTab->addTab(m_pProModCheckSettingGrid,strTitle);
	strTitle = _T("虚回路相关检查设置");
	ui.m_pCheckTab->addTab(m_pVirtualLoopCheckSettingGrid,strTitle);
	m_pSchemaSettingGrid->InitGrid();
	m_pDL860CheckSettingGrid->InitGrid();
	m_pProModCheckSettingGrid->InitGrid();
	m_pVirtualLoopCheckSettingGrid->InitGrid();
	UpdateGrids();

	CString strPngPath = _P_GetResourcePath();
	strPngPath  += _T("Setting.png");
	this->setWindowIcon(QIcon(strPngPath));

	connect(ui.m_OK_Btn, SIGNAL(clicked()), this, SLOT(slot_m_OK_Btn_Clicked()));
	connect(ui.m_Cancel_Btn, SIGNAL(clicked()), this, SLOT(slot_m_Cancel_Btn_Clicked()));
	connect(m_pDL860CheckSettingGrid, SIGNAL(sig_SelectAll()), this, SLOT(slot_SelectAll()));
	connect(m_pSchemaSettingGrid, SIGNAL(sig_SelectAll()), this, SLOT(slot_SelectAll()));
	connect(m_pProModCheckSettingGrid, SIGNAL(sig_SelectAll()), this, SLOT(slot_SelectAll()));
	connect(m_pVirtualLoopCheckSettingGrid, SIGNAL(sig_SelectAll()), this, SLOT(slot_SelectAll()));
	connect(m_pDL860CheckSettingGrid, SIGNAL(sig_UnSelectAll()), this, SLOT(slot_UnSelectAll()));
	connect(m_pSchemaSettingGrid, SIGNAL(sig_UnSelectAll()), this, SLOT(slot_UnSelectAll()));
	connect(m_pProModCheckSettingGrid, SIGNAL(sig_UnSelectAll()), this, SLOT(slot_UnSelectAll()));
	connect(m_pVirtualLoopCheckSettingGrid, SIGNAL(sig_UnSelectAll()), this, SLOT(slot_UnSelectAll()));
	connect(m_pDL860CheckSettingGrid, SIGNAL(sig_Reverse()), this, SLOT(slot_Reverse()));
	connect(m_pSchemaSettingGrid, SIGNAL(sig_Reverse()), this, SLOT(slot_Reverse()));
	connect(m_pProModCheckSettingGrid, SIGNAL(sig_Reverse()), this, SLOT(slot_Reverse()));
	connect(m_pVirtualLoopCheckSettingGrid, SIGNAL(sig_Reverse()), this, SLOT(slot_Reverse()));

}

void QSCLCheckSettingWidget::GetConfigs()
{
	m_oSclCheckObjects.OpenCheckConfigFile();
	m_pSchemaSettings = (CSchemaChecks*)(m_oSclCheckObjects.FindByClassID(SCLCLASSID_CSCHEMACHECKS));
	m_pDL860CheckSettings = (CDLT860ModelChecks*)(m_oSclCheckObjects.FindByClassID(SCLCLASSID_CDLT860MODELCHECKS));
	m_pProModCheckSettings = (CProjAppModelChecks*)(m_oSclCheckObjects.FindByClassID(SCLCLASSID_CPROJAPPMODELCHECKS));
	m_pVirtualLoopCheckSettings = (CVirLoopChecks*)(m_oSclCheckObjects.FindByClassID(SCLCLASSID_CVIRLOOPCHECKS));
}

void QSCLCheckSettingWidget::SetConfigs()
{
	m_oSclCheckObjects.SaveCheckConfigFile();
	emit sig_UpdateConfigs();
}

void QSCLCheckSettingWidget::slot_m_Cancel_Btn_Clicked()
{
	this->close();
}

void QSCLCheckSettingWidget::slot_m_OK_Btn_Clicked()
{
	SetConfigs();
	this->close();

}

void QSCLCheckSettingWidget::UpdateGrids()
{
	GetConfigs();
 	m_pSchemaSettingGrid->ShowDatas(m_pSchemaSettings);
	m_pDL860CheckSettingGrid->ShowDatas(m_pDL860CheckSettings);
	m_pProModCheckSettingGrid->ShowDatas(m_pProModCheckSettings);
	m_pVirtualLoopCheckSettingGrid->ShowDatas(m_pVirtualLoopCheckSettings);

}

void QSCLCheckSettingWidget::slot_SelectAll()
{
	QWidget* currentTab = ui.m_pCheckTab->currentWidget();
	QString currentTabTitle = ui.m_pCheckTab->tabText(ui.m_pCheckTab->indexOf(currentTab));
	if (currentTabTitle == "Schema语法检查设置")
	{
		if (m_pSchemaSettings != NULL)
		{
			CSchemaCheckObject *pSchemaCheck = NULL;
			POS pos = m_pSchemaSettings->GetHeadPosition();
			while(pos)
			{
				pSchemaCheck = (CSchemaCheckObject*)m_pSchemaSettings->GetNext(pos);
				pSchemaCheck->m_nChoose = 1;
			}
			m_pSchemaSettingGrid->ShowDatas(m_pSchemaSettings);
		}
	}
	else if (currentTabTitle == "DL/860数据类型检查设置")
	{
		if (m_pDL860CheckSettings != NULL)
		{
			CCheckObject *pCheck = NULL;
			POS pos = m_pDL860CheckSettings->GetHeadPosition();
			while(pos)
			{
				pCheck = (CCheckObject*)m_pDL860CheckSettings->GetNext(pos);
				pCheck->m_nChoose = 1;
			}
			m_pDL860CheckSettingGrid->ShowDatas(m_pDL860CheckSettings);
		}

	}
	else if (currentTabTitle == "工程应用模型规范性检查设置")
	{
		if (m_pProModCheckSettings != NULL)
		{
			CCheckObject *pCheck = NULL;
			POS pos = m_pProModCheckSettings->GetHeadPosition();
			while(pos)
			{
				pCheck = (CCheckObject*)m_pProModCheckSettings->GetNext(pos);
				pCheck->m_nChoose = 1;
			}
			m_pProModCheckSettingGrid->ShowDatas(m_pProModCheckSettings);
		}

	}
	else if (currentTabTitle == "虚回路相关检查设置")
	{
		if (m_pVirtualLoopCheckSettings != NULL)
		{
			CCheckObject *pCheck = NULL;
			POS pos = m_pVirtualLoopCheckSettings->GetHeadPosition();
			while(pos)
			{
				pCheck = (CCheckObject*)m_pVirtualLoopCheckSettings->GetNext(pos);
				pCheck->m_nChoose = 1;
			}
			m_pVirtualLoopCheckSettingGrid->ShowDatas(m_pVirtualLoopCheckSettings);
		}

	}
}

void QSCLCheckSettingWidget::slot_UnSelectAll()
{
 	QWidget* currentTab = ui.m_pCheckTab->currentWidget();
	QString currentTabTitle = ui.m_pCheckTab->tabText(ui.m_pCheckTab->indexOf(currentTab));
	if (currentTabTitle == "Schema语法检查设置")
	{
		if (m_pSchemaSettings != NULL)
		{
			CSchemaCheckObject *pSchemaCheck = NULL;
			POS pos = m_pSchemaSettings->GetHeadPosition();
			while(pos)
			{
				pSchemaCheck = (CSchemaCheckObject*)m_pSchemaSettings->GetNext(pos);
				pSchemaCheck->m_nChoose = 0;
			}
			m_pSchemaSettingGrid->ShowDatas(m_pSchemaSettings);
		}
	}
	else if (currentTabTitle == "DL/860数据类型检查设置")
	{
		if (m_pDL860CheckSettings != NULL)
		{
			CCheckObject *pCheck = NULL;
			POS pos = m_pDL860CheckSettings->GetHeadPosition();
			while(pos)
			{
				pCheck = (CCheckObject*)m_pDL860CheckSettings->GetNext(pos);
				pCheck->m_nChoose = 0;
			}
			m_pDL860CheckSettingGrid->ShowDatas(m_pDL860CheckSettings);
		}

	}
	else if (currentTabTitle == "工程应用模型规范性检查设置")
	{
		if (m_pProModCheckSettings != NULL)
		{
			CCheckObject *pCheck = NULL;
			POS pos = m_pProModCheckSettings->GetHeadPosition();
			while(pos)
			{
				pCheck = (CCheckObject*)m_pProModCheckSettings->GetNext(pos);
				pCheck->m_nChoose = 0;
			}
			m_pProModCheckSettingGrid->ShowDatas(m_pProModCheckSettings);
		}

	}
	else if (currentTabTitle == "虚回路相关检查设置")
	{
		if (m_pVirtualLoopCheckSettings != NULL)
		{
			CCheckObject *pCheck = NULL;
			POS pos = m_pVirtualLoopCheckSettings->GetHeadPosition();
			while(pos)
			{
				pCheck = (CCheckObject*)m_pVirtualLoopCheckSettings->GetNext(pos);
				pCheck->m_nChoose = 0;
			}
			m_pVirtualLoopCheckSettingGrid->ShowDatas(m_pVirtualLoopCheckSettings);
		}

	}

}

void QSCLCheckSettingWidget::slot_Reverse()
{
	QWidget* currentTab = ui.m_pCheckTab->currentWidget();
	QString currentTabTitle = ui.m_pCheckTab->tabText(ui.m_pCheckTab->indexOf(currentTab));
	if (currentTabTitle == "Schema语法检查设置")
	{
		if (m_pSchemaSettings != NULL)
		{
			CSchemaCheckObject *pSchemaCheck = NULL;
			POS pos = m_pSchemaSettings->GetHeadPosition();
			while(pos)
			{
				pSchemaCheck = (CSchemaCheckObject*)m_pSchemaSettings->GetNext(pos);
				if (pSchemaCheck->m_nChoose == 0)
				{
					pSchemaCheck->m_nChoose = 1;
				}
				else
				{
					pSchemaCheck->m_nChoose = 0;
				}
				
			}
			m_pSchemaSettingGrid->ShowDatas(m_pSchemaSettings);
		}
	}
	else if (currentTabTitle == "DL/860数据类型检查设置")
	{
		if (m_pDL860CheckSettings != NULL)
		{
			CCheckObject *pCheck = NULL;
			POS pos = m_pDL860CheckSettings->GetHeadPosition();
			while(pos)
			{
				pCheck = (CCheckObject*)m_pDL860CheckSettings->GetNext(pos);
				if(pCheck->m_nChoose == 0)
				{
					pCheck->m_nChoose = 1;
				}
				else
				{
					pCheck->m_nChoose = 0;
				}
				
			}
			m_pDL860CheckSettingGrid->ShowDatas(m_pDL860CheckSettings);
		}

	}
	else if (currentTabTitle == "工程应用模型规范性检查设置")
	{
		if (m_pProModCheckSettings != NULL)
		{
			CCheckObject *pCheck = NULL;
			POS pos = m_pProModCheckSettings->GetHeadPosition();
			while(pos)
			{
				pCheck = (CCheckObject*)m_pProModCheckSettings->GetNext(pos);
				if(pCheck->m_nChoose == 0)
				{
					pCheck->m_nChoose = 1;
				}
				else
				{
					pCheck->m_nChoose = 0;
				}
			}
			m_pProModCheckSettingGrid->ShowDatas(m_pProModCheckSettings);
		}

	}
	else if (currentTabTitle == "虚回路相关检查设置")
	{
		if (m_pVirtualLoopCheckSettings != NULL)
		{
			CCheckObject *pCheck = NULL;
			POS pos = m_pVirtualLoopCheckSettings->GetHeadPosition();
			while(pos)
			{
				pCheck = (CCheckObject*)m_pVirtualLoopCheckSettings->GetNext(pos);
				if(pCheck->m_nChoose == 0)
				{
					pCheck->m_nChoose = 1;
				}
				else
				{
					pCheck->m_nChoose = 0;
				}
			}
			m_pVirtualLoopCheckSettingGrid->ShowDatas(m_pVirtualLoopCheckSettings);
		}

	}

}