#include "SttIecRecordMainWidget.h"
#include "ui_SttIecRecordMainWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"

#include "SttIecRecordDetectWidget.h"
#include "SttIecRecordCbWidget.h"
#include "MUTest/SttMUTestRecordCbWidget.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapAnalysisConfig.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../UI/SttTestCntrCmdDefine.h"

QSttIecRecordMainWidget *g_theSttIecRecordMainWidget = NULL;

QSttIecRecordMainWidget::QSttIecRecordMainWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttIecRecordMainWidget)
{
	g_theSttIecRecordMainWidget = this;
	m_bHasInitFinished = false;
	m_pSttIecRecordCbWidget = 0;
	m_pSttIecRecordDetectWidget = 0;
	m_oFont = font;
	m_nPkgDetectType = STT_IEC_DETECT_TYPE_61850_92;
}

void QSttIecRecordMainWidget::InitIecRecordMain()
{
	if (m_bHasInitFinished)
	{
		return;
	}
	
    ui->setupUi(this);

	m_pSttIecRecordCbWidget = NULL;
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	g_oCapAnalysisConfig.Open();

	m_pSttIecRecordDetectWidget = new QSttIecRecordDetectWidget(m_oFont, this);
	m_pSttIecRecordCbWidget = new QSttIecRecordCbWidget(m_oFont, this);
    m_pSttIecRecordDetectWidget->hide();
    m_pSttIecRecordCbWidget->hide();

    ui->verticalLayout->insertWidget(0,m_pSttIecRecordDetectWidget);
    ui->verticalLayout->insertWidget(0,m_pSttIecRecordCbWidget);
    m_pSttIecRecordDetectWidget->show();

	connect(this,SIGNAL(sig_ShowIecDetectWindow()),this,SLOT(on_ShowIecDetectWindow()));
	connect(this,SIGNAL(sig_ShowIecCbWindow()),this,SLOT(on_ShowIecCbWindow()));
	m_bHasInitFinished = true;
}

void QSttIecRecordMainWidget::showEvent(QShowEvent *event)
{
	InitIecRecordMain();
	InitIecRecordCbWidget(m_strFuncID, m_nPkgDetectType);//dingxy 20240920 ��ָ�����⵼�±��������޸�

	QWidget::showEvent(event);
}


QSttIecRecordMainWidget::~QSttIecRecordMainWidget()
{
        delete ui;
		if (m_pSttIecRecordDetectWidget != NULL)
		{
        delete m_pSttIecRecordDetectWidget;
			m_pSttIecRecordDetectWidget = NULL;
		}

		if (m_pSttIecRecordCbWidget != NULL)
		{
			delete m_pSttIecRecordCbWidget;
			m_pSttIecRecordCbWidget = NULL;
		}
}


//////////////////////////////////////////////////////////////////////////
//CSttWndAssistInterface
//���Ҵ��ڣ������� �ҵ����ش���,      ���򷵻�NULL
CSttWndAssistInterface* QSttIecRecordMainWidget::ast_FindWnd(const CString &strWndID)
{

	return NULL;
}

//����ִ�нӿ�
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
	InitIecRecordMain(); //2024-9-10 lijunqing �Ż�ϵͳ����������Ч��
	QSttIecRecordDetectWidget *pDetect = (QSttIecRecordDetectWidget*)m_pSttIecRecordDetectWidget;
//	pDetect->m_bIecCapWriteFile = b;

	pDetect->SetIecCapWriteFile(b);
}

void QSttIecRecordMainWidget::InitIecRecordCbWidget(const CString &strFuncID,long nPkgDetectType)
{
	m_strFuncID = strFuncID;
	m_nPkgDetectType = nPkgDetectType;
	if (!m_bHasInitFinished)
	{
		return;
	}
//#ifndef _PSX_QT_LINUX_//��LINUX�»�ʹ��ԭ�з�ʽ
	if ((strFuncID == STT_ORG_MACRO_MUAccuracyTest)||(strFuncID == STT_ORG_MACRO_MUFirstCycleTest)
		||(strFuncID == STT_ORG_MACRO_MUAccurAutoTest)||(strFuncID == STT_ORG_MACRO_MUAutoTest))
	{
		if (!g_pSttIecRecordCbWidget->IsTabUI_Mode())//�ϲ���Ԫ׼ȷ�ȵȲ���ģʽ��ҪΪTab��ʽ��ʾ
		{
			QDialog *pOldSttIecRecordCbWidget = m_pSttIecRecordCbWidget;
			m_pSttIecRecordCbWidget = new QSttMUTestRecordCbWidget(font(), nPkgDetectType,this);
			m_pSttIecRecordDetectWidget->hide();
			m_pSttIecRecordCbWidget->show();
			ui->verticalLayout->insertWidget(0,m_pSttIecRecordCbWidget);
			//20241226 suyang ��Ϊ��tab��ʽ��ʾ����Ҫ�����������ʾ����
			((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->MuBeginRecord();
			if (pOldSttIecRecordCbWidget != NULL)
			{
				delete pOldSttIecRecordCbWidget;
			}
		}
	}
	else if (g_pSttIecRecordCbWidget->IsTabUI_Mode())//�Ǻϲ���Ԫ׼ȷ�ȵȲ���ģʽ��ҪΪԭ�з�ʽ��ʾ
	{
		QDialog *pOldSttIecRecordCbWidget = m_pSttIecRecordCbWidget;
		m_pSttIecRecordCbWidget = new QSttIecRecordCbWidget(font(), this);
		m_pSttIecRecordCbWidget->hide();
		ui->verticalLayout->insertWidget(0,m_pSttIecRecordCbWidget);

		if (pOldSttIecRecordCbWidget!= NULL)
		{
			delete pOldSttIecRecordCbWidget;
		}
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
		StartDetect();//2024-6-24 wuxinyi �޸���ʱ����ʱ���Ĭ��IEC̽��ҳ��Ĭ�Ͽ�ʼ̽��
	}
	else
	{
		g_pSttIecRecordCbWidget->SetMUTestMode(false);
	}

	((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateDetectType(nPkgDetectType);
}

void QSttIecRecordMainWidget::UpdateIecDetectType(long nPkgDetectType)
{
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
	if (m_pSttIecRecordCbWidget == NULL)
	{
		m_pSttIecRecordDetectWidget->show();
		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateDetectWidget();
		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->StartDetect();
		assist_widget_show("IecRecordDetect", m_pSttIecRecordDetectWidget, true);
		return;
	} 


	if (g_pSttIecRecordCbWidget->IsTabUI_Mode())
	{
		m_pSttIecRecordCbWidget->show();
		m_pSttIecRecordDetectWidget->hide();
		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateDetectWidget();
//		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->StartDetect();//20230630 zhouhj ������̽��,��ˢ�°�ť����̽��

		assist_widget_show("IecRecordCb", m_pSttIecRecordCbWidget, true);
//		assist_widget_show("IecRecordDetect", m_pSttIecRecordDetectWidget, true);
	}
	else
	{
		m_pSttIecRecordCbWidget->hide();
		m_pSttIecRecordDetectWidget->show();
		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateDetectWidget();
		((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->StartDetect();

		assist_widget_show("IecRecordCb", m_pSttIecRecordCbWidget, false);
		assist_widget_show("IecRecordDetect", m_pSttIecRecordDetectWidget, true);
	}
}

void QSttIecRecordMainWidget::on_ShowIecCbWindow()
{
	if (m_pSttIecRecordCbWidget == NULL)
	{
		m_pSttIecRecordCbWidget = new QSttIecRecordCbWidget(font(), this);
		ui->verticalLayout->insertWidget(0,m_pSttIecRecordCbWidget);
	}

	if (m_pSttIecRecordDetectWidget == 0)
	{
		return;
	}

	m_pSttIecRecordDetectWidget->hide();
	m_pSttIecRecordCbWidget->show();
	g_pSttIecRecordCbWidget->ExecIecFunc();

#ifdef STT_MUTest_CBSelect_USE_Assist
	assist_widget_show("IecRecordDetect", m_pSttIecRecordDetectWidget, false);
	assist_widget_show("IecRecordCb", m_pSttIecRecordCbWidget, true);
#endif
}

void QSttIecRecordMainWidget::StartDetect()
{
	InitIecRecordMain(); //2024-9-10 lijunqing �Ż�ϵͳ����������Ч��

	if (m_pSttIecRecordDetectWidget != 0)
	{
	((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->StartDetect();
	}
}

void QSttIecRecordMainWidget::UpdateIecfg()
{
	InitIecRecordMain(); //2024-9-10 lijunqing �Ż�ϵͳ����������Ч��

	if (m_pSttIecRecordDetectWidget != 0)
	{
	((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->UpdateIecfg();
	}
}

void QSttIecRecordMainWidget::ClearAll_StartDetect()//���ȫ��,���¿�ʼ̽��
{
	if (m_pSttIecRecordDetectWidget != 0)
	{
	((QSttIecRecordDetectWidget *)m_pSttIecRecordDetectWidget)->ClearAll_StartDetect();
	}
}

void QSttIecRecordMainWidget::CloseIecCapDetect()
{
	if (m_pSttIecRecordDetectWidget != 0)
	{
		((QSttIecRecordDetectWidget*)m_pSttIecRecordDetectWidget)->CloseIecCapDetect();
	}
}
