#include "SttIecRecordMainWidget.h"
#include "ui_SttIecRecordMainWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"

#include "SttIecRecordDetectWidget.h"
#include "SttIecRecordCbWidget.h"
//#include "MUTest/SttMUTestRecordCbWidget.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapAnalysisConfig.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../UI/SttTestCntrCmdDefine.h"

QSttIecRecordMainWidget *g_theSttIecRecordMainWidget = NULL;

QSttIecRecordMainWidget::QSttIecRecordMainWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttIecRecordMainWidget)
{
	g_theSttIecRecordMainWidget = this;
    ui->setupUi(this);

    //m_pSttIecRecordCbWidget = NULL;
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	g_oCapAnalysisConfig.Open();

    m_pSttIecRecordDetectWidget = new QSttIecRecordDetectWidget(font, this);
    //m_pSttIecRecordCbWidget = new QSttIecRecordCbWidget(font, this);
    m_pSttIecRecordDetectWidget->hide();
   // m_pSttIecRecordCbWidget->hide();

    ui->verticalLayout->insertWidget(0,m_pSttIecRecordDetectWidget);
    //ui->verticalLayout->insertWidget(0,m_pSttIecRecordCbWidget);
    m_pSttIecRecordDetectWidget->show();

	connect(this,SIGNAL(sig_ShowIecDetectWindow()),this,SLOT(on_ShowIecDetectWindow()));
	connect(this,SIGNAL(sig_ShowIecCbWindow()),this,SLOT(on_ShowIecCbWindow()));
}

QSttIecRecordMainWidget::~QSttIecRecordMainWidget()
{
        delete ui;
        delete m_pSttIecRecordDetectWidget;

//		if (m_pSttIecRecordCbWidget != NULL)
//		{
//			delete m_pSttIecRecordCbWidget;
//			m_pSttIecRecordCbWidget = NULL;
//		}
}


//////////////////////////////////////////////////////////////////////////
//CSttWndAssistInterface
//查找窗口，保留用 找到返回窗口,      否则返回NULL
CSttWndAssistInterface* QSttIecRecordMainWidget::ast_FindWnd(const CString &strWndID)
{

	return NULL;
}

//功能执行接口
bool QSttIecRecordMainWidget::ast_ExecCmd(const CString &strCmdID,const CString &strParas)
{

	return false;
}

bool QSttIecRecordMainWidget::ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID)
{

	return false;
}

bool QSttIecRecordMainWidget::ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile)
{

	return false;
}

//////////////////////////////////////////////////////////////////////////
void QSttIecRecordMainWidget::SetIecCapWriteFile(bool b)
{
	QSttIecRecordDetectWidget *pDetect = (QSttIecRecordDetectWidget*)m_pSttIecRecordDetectWidget;
//	pDetect->m_bIecCapWriteFile = b;

	pDetect->SetIecCapWriteFile(b);
}

void QSttIecRecordMainWidget::InitIecRecordCbWidget(const CString &strFuncID,long nPkgDetectType)
{
//#ifndef _PSX_QT_LINUX_//在LINUX下还使用原有方式
	if ((strFuncID == STT_ORG_MACRO_MUAccuracyTest)||(strFuncID == STT_ORG_MACRO_MUFirstCycleTest)
		||(strFuncID == STT_ORG_MACRO_MUAccurAutoTest)||(strFuncID == STT_ORG_MACRO_MUAutoTest))
	{
//		if (!g_pSttIecRecordCbWidget->IsTabUI_Mode())//合并单元准确度等测试模式需要为Tab方式显示
//		{
//			QDialog *pOldSttIecRecordCbWidget = m_pSttIecRecordCbWidget;
//			m_pSttIecRecordCbWidget = new QSttMUTestRecordCbWidget(font(), nPkgDetectType,this);
//			m_pSttIecRecordDetectWidget->hide();
//			m_pSttIecRecordCbWidget->show();
//			ui->verticalLayout->insertWidget(0,m_pSttIecRecordCbWidget);

//			if (pOldSttIecRecordCbWidget != NULL)
//			{
//				delete pOldSttIecRecordCbWidget;
//			}
//		}
	}
	else if (g_pSttIecRecordCbWidget->IsTabUI_Mode())//非合并单元准确度等测试模式需要为原有方式显示
	{
//		QDialog *pOldSttIecRecordCbWidget = m_pSttIecRecordCbWidget;
//		m_pSttIecRecordCbWidget = new QSttIecRecordCbWidget(font(), this);
//		m_pSttIecRecordCbWidget->hide();
//		ui->verticalLayout->insertWidget(0,m_pSttIecRecordCbWidget);

//		if (pOldSttIecRecordCbWidget!= NULL)
//		{
//			delete pOldSttIecRecordCbWidget;
//		}
	}
//#endif

	if ((strFuncID == STT_ORG_MACRO_MUAccuracyTest)||(strFuncID == STT_ORG_MACRO_MUFirstCycleTest)
		||(strFuncID == STT_ORG_MACRO_MUAccurAutoTest)||(strFuncID == STT_ORG_MACRO_MUAutoTest))
	{
		g_pSttIecRecordCbWidget->SetMUTestMode(true);
	}
	else if ((strFuncID == STT_ORG_MACRO_MUTimingAccurTest)||(strFuncID == STT_ORG_MACRO_MUPunctAccurTest))
	{
		g_pSttIecRecordCbWidget->SetMUTestMode(true);
	}
	else
	{
		g_pSttIecRecordCbWidget->SetMUTestMode(false);
	}

	((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateDetectType(nPkgDetectType);
}


void QSttIecRecordMainWidget::ShowIecDetectWindow()
{
	emit sig_ShowIecDetectWindow();
}

void QSttIecRecordMainWidget::ShowIecCbWindow()
{
	emit sig_ShowIecCbWindow();
}

void QSttIecRecordMainWidget::UpdateCapDevice(CCapDeviceBase *pCapDevice)
{
// 	if (m_pSttIecRecordCbWidget->isVisible())
// 	{
// 		((QSttIecRecordCbWidget*)m_pSttIecRecordCbWidget)->UpdateCapDevice(pCapDevice);
// 	}
}

void QSttIecRecordMainWidget::on_ShowIecDetectWindow()
{
//	if (m_pSttIecRecordCbWidget == NULL)
//	{
//		m_pSttIecRecordDetectWidget->show();
//		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateDetectWidget();
//		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->StartDetect();
//		assist_widget_show("IecRecordDetect", m_pSttIecRecordDetectWidget, true);
//		return;
//	}


//	if (g_pSttIecRecordCbWidget->IsTabUI_Mode())
//	{
//		m_pSttIecRecordCbWidget->show();
//		m_pSttIecRecordDetectWidget->hide();
//		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateDetectWidget();
////		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->StartDetect();//20230630 zhouhj 不主动探测,由刷新按钮启动探测

//		assist_widget_show("IecRecordCb", m_pSttIecRecordCbWidget, true);
////		assist_widget_show("IecRecordDetect", m_pSttIecRecordDetectWidget, true);
//	}
//	else
//	{
//		m_pSttIecRecordCbWidget->hide();
//		m_pSttIecRecordDetectWidget->show();
//		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateDetectWidget();
//		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->StartDetect();

//		assist_widget_show("IecRecordCb", m_pSttIecRecordCbWidget, false);
//		assist_widget_show("IecRecordDetect", m_pSttIecRecordDetectWidget, true);
//	}
}

void QSttIecRecordMainWidget::on_ShowIecCbWindow()
{
//	if (m_pSttIecRecordCbWidget == NULL)
//	{
//		m_pSttIecRecordCbWidget = new QSttIecRecordCbWidget(font(), this);
//		ui->verticalLayout->insertWidget(0,m_pSttIecRecordCbWidget);
//	}

//	m_pSttIecRecordDetectWidget->hide();
//	m_pSttIecRecordCbWidget->show();
//	g_pSttIecRecordCbWidget->ExecIecFunc();

//#ifdef STT_MUTest_CBSelect_USE_Assist
//	assist_widget_show("IecRecordDetect", m_pSttIecRecordDetectWidget, false);
//	assist_widget_show("IecRecordCb", m_pSttIecRecordCbWidget, true);
//#endif
}

void QSttIecRecordMainWidget::StartDetect()
{
	((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->StartDetect();
}

void QSttIecRecordMainWidget::UpdateIecfg()
{
	((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateIecfg();
}

void QSttIecRecordMainWidget::ClearAll_StartDetect()//清空全部,重新开始探测
{
	((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->ClearAll_StartDetect();
}

void QSttIecRecordMainWidget::UpdateIecDetectType(long nPkgDetectType)
{
	((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateDetectType(nPkgDetectType);
}

void QSttIecRecordMainWidget::CloseIecCapDetect()
{
//	if (!m_pSttIecRecordCbWidget->isVisible())//如果不在报文监视界面,则报文探测界面已打开
	{
		((QSttIecRecordDetectWidget*)m_pSttIecRecordDetectWidget)->CloseIecCapDetect();
	}
}
