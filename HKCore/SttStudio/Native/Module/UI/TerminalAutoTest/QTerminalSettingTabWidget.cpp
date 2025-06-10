#include "QTerminalSettingTabWidget.h"
#include <QVBoxLayout>
#include "../SttTestCntrFrameBase.h"
#include "SttMacroParaEditViewTerminalAutoTest.h"
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"


QTerminalSettingTabWidget::QTerminalSettingTabWidget(QWidget *parent):QDialog(parent)
{		
	CString strText;
	strText = ("设置");
	this->setWindowTitle(strText);
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::X11BypassWindowManagerHint);
	this->resize(1000,750);
	this->setFixedWidth(1000);
	this->setFixedHeight(750);
	m_pTabWidget = NULL;
	m_pIecCfgGoutDataGrid = NULL;
	m_pIecCfgGoutChannelsGrid = NULL;
	m_pIecCfgGinDataGrid = NULL;
	m_pIecCfgGinChannelsGrid = NULL;
	m_pBtnCancle = NULL;
	m_pBtnOK = NULL;
	m_pBtnOtherSet = NULL;

	InitUI();
	InitConnection();
}

QTerminalSettingTabWidget::~QTerminalSettingTabWidget()
{

}

void QTerminalSettingTabWidget::InitConnection()
{
	connect(m_pBtnOK, SIGNAL(clicked()),SLOT(slot_BtnOK()));
	connect(m_pBtnCancle, SIGNAL(clicked()), SLOT(slot_BtnCancle()));	
	connect(m_pTabWidget,SIGNAL(currentChanged(int )),this,SLOT(slot_TabPageChanged(int)));
	connect(m_pIecCfgGoutDataGrid,SIGNAL(sig_UpdateChansdata(CIecCfgChsBase *)),this,SLOT(UpdateGoutChans(CIecCfgChsBase *)));
	connect(m_pIecCfgGinDataGrid,SIGNAL(sig_UpdateChansdata(CIecCfgChsBase *)),this,SLOT(UpdateGinChans(CIecCfgChsBase *)));
}


void QTerminalSettingTabWidget::InitUI()
{
	m_pTabWidget = new QTabWidget(this);
	m_pTabWidget->setFont(*g_pSttGlobalFont);
	m_pIecCfgGoutDataGrid = new QTerminalGoutDataGrid(this);
	m_pIecCfgGoutDataGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIecCfgGoutDataGrid->setFont(*g_pSttGlobalFont);
	m_pIecCfgGoutDataGrid->InitGrid();

	m_pIecCfgGoutChannelsGrid = new QTerminalGoutDataChsGrid(this);
	m_pIecCfgGoutChannelsGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIecCfgGoutChannelsGrid->setFont(*g_pSttGlobalFont);
	m_pIecCfgGoutChannelsGrid->InitGrid();

	m_pIecCfgGinDataGrid = new QTerminalGinDataGrid(this);
	m_pIecCfgGinDataGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIecCfgGinDataGrid->setFont(*g_pSttGlobalFont);
	m_pIecCfgGinDataGrid->InitGrid();

	m_pIecCfgGinChannelsGrid = new QTerminalGinDataChsGrid(this);
	m_pIecCfgGinChannelsGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIecCfgGinChannelsGrid->setFont(*g_pSttGlobalFont);
	m_pIecCfgGinChannelsGrid->InitGrid();

	CString strText;
	m_pBtnOtherSet = new QPushButton(this);
	strText = _T("其他设置");
	m_pBtnOtherSet->setText(strText);
	m_pBtnOtherSet->hide();
	m_pBtnCancle = new QPushButton(this);
	strText = _T("取消");
	m_pBtnCancle->setText(strText);
	m_pBtnCancle->setFont(*g_pSttGlobalFont);
	m_pBtnOK = new QPushButton(this);
	strText = _T("确认");
	m_pBtnOK->setText(strText);
	m_pBtnOK->setFont(*g_pSttGlobalFont);

	QHBoxLayout *pBtnLayout = new QHBoxLayout;
	pBtnLayout->addWidget(m_pBtnOtherSet);
	pBtnLayout->addStretch(5);
	pBtnLayout->addWidget(m_pBtnCancle);
	pBtnLayout->addWidget(m_pBtnOK);
	QWidget *pBtnWidget = new QWidget;
	pBtnWidget->setLayout(pBtnLayout);


	QVBoxLayout *pGinVLayout = new QVBoxLayout;
	pGinVLayout->addWidget(m_pIecCfgGinDataGrid);
	pGinVLayout->addWidget(m_pIecCfgGinChannelsGrid);
	m_pMuGooseGinWidget = new QWidget(this);
	m_pMuGooseGinWidget ->setLayout(pGinVLayout);

	QVBoxLayout *pGoutVLayout = new QVBoxLayout;
	pGoutVLayout->addWidget(m_pIecCfgGoutDataGrid);
	pGoutVLayout->addWidget(m_pIecCfgGoutChannelsGrid);
	m_pMuGooseGoutWidget = new QWidget(this);
	m_pMuGooseGoutWidget->setLayout(pGoutVLayout);

	m_pTabWidget->insertTab(SET_TAB_TYPE_GOOSETOBIN,m_pMuGooseGoutWidget,_T("GOOSE转开入"));
	m_pTabWidget->insertTab(SET_TAB_TYPE_BOUTTOGOOSE,m_pMuGooseGinWidget,_T("开出转GOOSE"));

	
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(m_pTabWidget);
	layout->addWidget(pBtnWidget);
	setLayout(layout);

	slot_TabPageChanged(SET_TAB_TYPE_GOOSETOBIN);
}

void QTerminalSettingTabWidget::slot_TabPageChanged(int nIndex)
{
	if (nIndex == SET_TAB_TYPE_GOOSETOBIN)
	{
		InitBinGooseData();
	}
	else if (nIndex == SET_TAB_TYPE_BOUTTOGOOSE)
	{
		InitBoutGooseData();
	}
}


void QTerminalSettingTabWidget::slot_BtnOK()
{
	accept();	
	//g_oSttTestResourceMngr.SaveDefaultIec61850Config();//保存xml
	g_theTestCntrFrame->slot_IecCfgDataMngrUpdate();//chenling20231207

	SaveGoutMapValue();
	SaveGinMapValue();

	g_TerminalAutoTest->SaveXmlParas();
}


void QTerminalSettingTabWidget::slot_BtnCancle()
{
	reject();
}


void QTerminalSettingTabWidget::InitBinGooseData()
{
	m_pIecCfgGoutDataGrid->m_nFirstIndex = 0;
	m_pIecCfgGoutDataGrid->ShowDatas(g_TerminalAutoTest->m_pIecCfgGoutDatas);
	m_pIecCfgGoutChannelsGrid->ShowDatas(g_TerminalAutoTest->m_pIecCfgGoutChs);
}


void QTerminalSettingTabWidget::InitBoutGooseData()
{
	m_pIecCfgGinDataGrid->m_nFirstIndex = 0;
	m_pIecCfgGinDataGrid->ShowDatas(g_TerminalAutoTest->m_pIecCfgGinDatas);
	m_pIecCfgGinChannelsGrid->ShowDatas(g_TerminalAutoTest->m_pIecCfgGinChs);
}


void QTerminalSettingTabWidget::UpdateGoutChans(CIecCfgChsBase *pIecCfgChs)
{
	m_pIecCfgGoutChannelsGrid->ShowDatas(pIecCfgChs);
}

void QTerminalSettingTabWidget::UpdateGinChans(CIecCfgChsBase *pIecCfgChs)
{
	m_pIecCfgGinChannelsGrid->ShowDatas(pIecCfgChs);
}

void QTerminalSettingTabWidget::SaveXmlParas()
{
// 	SaveGoutMapValue();
// 	SaveGinMapValue();
// 	CString strFile;
// 	strFile = _P_GetDBPath();
// 	strFile += _T("atsgen/TerminalAuto_Paras.xml");
// 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value++;
// 	g_TerminalAutoTest->m_pMUAutoTestDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
// 	CDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value--;
}


void QTerminalSettingTabWidget::SaveGoutMapValue()
{
	CIecCfgGoutChs *pIecCfgGoutChs = g_TerminalAutoTest->m_pGoutMapChs;
	SaveMapValue(pIecCfgGoutChs,_T("bin"),_T("Gout"),_T("SOEGout"));
}

void QTerminalSettingTabWidget::SaveGinMapValue()
{
	CIecCfgGinChs *pIecCfgGinChs = g_TerminalAutoTest->m_pGinMapChs;
	SaveMapValue(pIecCfgGinChs,_T("bout"),_T("Gin"),_T("SOEGin"));
}


void QTerminalSettingTabWidget::SaveMapValue(CIecCfgChsBase *pIecCfgChsBase,CString str1,CString str2,CString srtSOE)
{
	long nIndex = 0,nIndex1 = 0;
	QString strDevID,strDevValue,strAppID,strAppValue,strCheck;
	QString strSoeDevID,strSoeDevValue,strSoeAppID,strSoeAppValue,strSoeCheck;

	CIecCfgDataGooseChBase *pIecCfgCh = NULL;
	POS pos = pIecCfgChsBase->GetHeadPosition();
	while(pos)
	{
		pIecCfgCh = (CIecCfgDataGooseChBase *)pIecCfgChsBase->GetNext(pos);
		
		strDevID = QString("%1_Check%2_Map").arg(str2).arg(nIndex1 + 1);
		strDevValue = "0"; 
		strAppID = QString("%1_Check%2_Value").arg(str2).arg(nIndex1 + 1);
		strAppValue = "0";	
		
		//新增SOE开出Value
		strSoeDevID = QString("%1_Check%2_Map").arg(srtSOE).arg(nIndex1 + 1);
		strSoeDevValue = "0";
		strSoeAppID = QString("%1_Check%2_Value").arg(srtSOE).arg(nIndex1 + 1);
		strSoeAppValue = "0";

		strCheck = QString("%1_Check%2").arg(str2).arg(nIndex1 + 1);
		g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strCheck,strAppValue);//chenling20240228 更新测试点的勾选value

		strSoeCheck = QString("%1_Check%2").arg(srtSOE).arg(nIndex1 + 1);
		g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strSoeCheck,strSoeAppValue);

		g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strAppID,strAppValue);
		g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strDevID,strDevValue);
		g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strSoeDevID,strSoeDevValue);
		g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strSoeAppID,strSoeAppValue);

		if (pIecCfgCh->m_strDevChID.Find(str1) >= 0)
		{
			strDevID = QString("%1_Check%2_Map").arg(str2).arg(nIndex + 1);
			strDevValue = pIecCfgCh->m_strDevChID.right(1);

			strAppID = QString("%1_Check%2_Value").arg(str2).arg(nIndex + 1);
			strAppValue = pIecCfgCh->m_strDevChID.right(1);

			strSoeDevID = QString("%1_Check%2_Map").arg(srtSOE).arg(nIndex + 1);
			strSoeDevValue = pIecCfgCh->m_strDevChID.right(1);
			strSoeAppID = QString("%1_Check%2_Value").arg(srtSOE).arg(nIndex + 1);
			strSoeAppValue = pIecCfgCh->m_strDevChID.right(1);

			strCheck = QString("%1_Check%2").arg(str2).arg(nIndex + 1);
			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strCheck,"1");
 
// 			strSoeCheck = QString("%1_Check%2").arg(srtSOE).arg(nIndex + 1);
// 			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strSoeCheck,"1");

			nIndex ++;

			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strAppID,strAppValue);
			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strDevID,strDevValue);

			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strSoeDevID,strSoeDevValue);
			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strSoeAppID,strSoeAppValue);
		}
// 		else
// 		{
// 			strDevID = QString("%1_Check%2_Map").arg(str2).arg(nIndex1 + 1);
// 			strDevValue = "0";
// 
// 			strAppID = QString("%1_Check%2_Value").arg(str2).arg(nIndex1 + 1);
// 			strAppValue = "0";
// 		}
		nIndex1 ++;
	}
}