#include "PpSttIotEngineDebugWidget.h"
#include "ui_PpSttIotEngineDebugWidget.h"

#include <QMessageBox>

#include "../../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"

extern CPpSttIotEngineClientApp *g_theIotEngineApp;


//////////////////////////////////////////////////////////////////////////
//QPpSttIotEngineDebugWidgetWnd
QPpSttIotEngineDebugWidgetWnd::QPpSttIotEngineDebugWidgetWnd()
{
	m_pRefWidget = NULL;
}

QPpSttIotEngineDebugWidgetWnd::~QPpSttIotEngineDebugWidgetWnd()
{

}


//重载函数OnWndMsg，实现消息处理
void QPpSttIotEngineDebugWidgetWnd::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
	m_pRefWidget->OnWndMsg(nMsgID, wParam, lParam);
}

void QPpSttIotEngineDebugWidgetWnd::OnWndTimer(unsigned int nIDEvent) 
{
	m_pRefWidget->OnWndTimer(nIDEvent);
}


//////////////////////////////////////////////////////////////////////////
//QPpSttIotEngineDebugWidget
QPpSttIotEngineDebugWidget::QPpSttIotEngineDebugWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPpSttIotEngineDebugWidget)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint;
	
	this->setWindowFlags(flags);
	m_oEngineMsgWnd.m_pRefWidget = this;
    ui->m_btnPpEngine->setChecked(true);
    on_m_btnPpEngine_clicked();
	EnableBtns();

    CLogPrint::Create(this);

    connect(this,SIGNAL(sig_OnCommCommandMsg(int, int)),this,SLOT(slot_OnCommCommandMsg(int, int)));
    connect(this,SIGNAL(sig_OnEngineSystemMessage(int, int)),this,SLOT(slot_OnEngineSystemMessage(int, int)));
}

QPpSttIotEngineDebugWidget::~QPpSttIotEngineDebugWidget()
{
    CLogPrint::SetLog(NULL);
    CLogPrint::Release();
    m_oEngineMsgWnd.DestroyWindow();
    delete ui;
}

void QPpSttIotEngineDebugWidget::LogString(long nLevel, const CString &strMsg)
{
    ui->m_listLog->addItem(strMsg);
}

void QPpSttIotEngineDebugWidget::LogString(long nLevel, const char *strMsg)
{
    ui->m_listLog->addItem(strMsg);
}


//重载函数OnWndMsg，实现消息处理
void QPpSttIotEngineDebugWidget::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
	switch (nMsgID)
	{
	case WM_ENGINE_SYSTEM_MSG:
		OnEngineSystemMessage(wParam, lParam);
		break;

	case WM_COMM_COMMAND:
		OnCommCommandMsg(wParam, lParam);
		break;

	default:
		break;
	}
}

void QPpSttIotEngineDebugWidget::OnWndTimer(unsigned int nIDEvent) 
{

}

void QPpSttIotEngineDebugWidget::OnCommCommandMsg(WPARAM wParam,LPARAM lParam)
{
    emit sig_OnCommCommandMsg(wParam, lParam);
}

void QPpSttIotEngineDebugWidget::OnEngineSystemMessage(WPARAM wParam, LPARAM lParam)
{
    emit sig_OnEngineSystemMessage(wParam, lParam);
}

void QPpSttIotEngineDebugWidget::ShowDatasetAfterCmd()
{
    CDvmDataset *pDataset = g_theIotEngineApp->GetCurrDataset();

    if (pDataset == NULL)
    {
        return;
    }

    CLogPrint::LogString(XLOGLEVEL_TRACE, g_theIotEngineApp->m_strDatasetPath);
    POS pos = pDataset->GetHeadPosition();
    CDvmData *pData = NULL;

    while (pos != NULL)
    {
        pData = (CDvmData*)pDataset->GetNext(pos);
        CLogPrint::LogString(XLOGLEVEL_TRACE, pData->m_strID);
    }
}

void QPpSttIotEngineDebugWidget::ShowDatasetAfterCmd(CDvmDataset *pDataset)
{
    CLogPrint::LogString(XLOGLEVEL_TRACE, pDataset->m_strID);
    POS pos = pDataset->GetHeadPosition();
    CDvmData *pData = NULL;

    while (pos != NULL)
    {
        pData = (CDvmData*)pDataset->GetNext(pos);
        CLogPrint::LogString(XLOGLEVEL_TRACE, pData->m_strName);
    }
}

void QPpSttIotEngineDebugWidget::slot_OnCommCommandMsg(int wParam,int lParam)
{
    //g_theIotEngineApp->m_pPpDevice->UnRegisterProcedureWndMsg(g_theIotEngineApp->m_strProcedureID, (unsigned long)&m_oEngineMsgWnd, WM_COMM_COMMAND);

    if (lParam == engineCommError)
    {
            CLogPrint::LogString(XLOGLEVEL_TRACE, "engineCommError....");
    }
    else  //lParam == engineCommFinish
    {//执行成功，显示相关联的数据集
        ShowDatasetAfterCmd();
    }
}

void QPpSttIotEngineDebugWidget::slot_OnEngineSystemMessage(int wParam, int lParam)
{
    switch (lParam)
    {
    case engineConnectDeviceFailed:
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Connect Device Failed"));
        g_theIotEngineApp->DisConnectForClose(NULL);
        break;

    case engineConnectDeviceSuccessful:
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Connect Device Successful"));
        break;

    case engineCommError:
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommError"));
        break;

    case engineException:
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Exception"));
        break;

    default:
        break;
    }

    EnableBtns();
}

void QPpSttIotEngineDebugWidget::EnableBtns()
{
    if (g_theIotEngineApp->m_pPpDevice == NULL)
	{
        ui->m_btnCmsEngine->setEnabled(true);
        ui->m_btnMmsEngine->setEnabled(true);
        ui->m_btnPpEngine->setEnabled(true);
		ui->m_btnCreateDevice->setEnabled(true);
		ui->m_btnCloseDevice->setEnabled(false);
		ui->m_btnReadAin->setEnabled(false);
		ui->m_btnWriteEna->setEnabled(false);
        ui->m_btnWriteSetting->setEnabled(false);
        ui->m_btnReadEna->setEnabled(false);
        ui->m_btnReadSetting->setEnabled(false);
		return;
	}

    ui->m_btnCmsEngine->setEnabled(false);
    ui->m_btnMmsEngine->setEnabled(false);
    ui->m_btnPpEngine->setEnabled(false);
	ui->m_btnCreateDevice->setEnabled(false);
	
    if (g_theIotEngineApp->m_pPpDevice->IsConnectIotServerSucc())
    {
        if (g_theIotEngineApp->m_pPpDevice->IsConnectSuccessful())
        {
            ui->m_btnConnectDevice->setEnabled(false);
            ui->m_btnCloseDevice->setEnabled(true);
            ui->m_btnReadAin->setEnabled(true);
            ui->m_btnWriteEna->setEnabled(true);
            ui->m_btnWriteEna->setEnabled(true);
            ui->m_btnReadEna->setEnabled(true);
            ui->m_btnWriteSetting->setEnabled(true);
            ui->m_btnReadSetting->setEnabled(true);
        }
        else
        {
            ui->m_btnConnectDevice->setEnabled(true);
            ui->m_btnCloseDevice->setEnabled(false);
            ui->m_btnReadAin->setEnabled(false);
            ui->m_btnWriteEna->setEnabled(false);
            ui->m_btnWriteEna->setEnabled(false);
            ui->m_btnReadEna->setEnabled(false);
            ui->m_btnWriteSetting->setEnabled(false);
            ui->m_btnReadSetting->setEnabled(false);
        }
    }
    else
    {
        ui->m_btnConnectDevice->setEnabled(true);
        ui->m_btnCloseDevice->setEnabled(false);
        ui->m_btnReadAin->setEnabled(false);
        ui->m_btnWriteEna->setEnabled(false);
        ui->m_btnWriteEna->setEnabled(false);
        ui->m_btnReadEna->setEnabled(false);
        ui->m_btnWriteSetting->setEnabled(false);
        ui->m_btnReadSetting->setEnabled(false);
    }
}

void QPpSttIotEngineDebugWidget::on_m_btnCreateDevice_clicked()
{
    g_theIotEngineApp->Createdevice((PSX_OBJ_ADDR)&m_oEngineMsgWnd);
	EnableBtns();
}

void QPpSttIotEngineDebugWidget::on_m_btnCloseDevice_clicked()
{
    g_theIotEngineApp->CloseDevice();
	EnableBtns();
}

void QPpSttIotEngineDebugWidget::on_m_btnConnectDevice_clicked()
{
    g_theIotEngineApp->ConnectDevice();
    EnableBtns();
}

void QPpSttIotEngineDebugWidget::on_m_btnReadAin_clicked()
{
    g_theIotEngineApp->SendIotCmdFile((PSX_OBJ_ADDR)&m_oEngineMsgWnd, _T("ReadAin"));
}

void QPpSttIotEngineDebugWidget::on_m_btnWriteEna_clicked()
{
    g_theIotEngineApp->SendIotCmdFile((PSX_OBJ_ADDR)&m_oEngineMsgWnd, _T("WriteEna"));
}

void QPpSttIotEngineDebugWidget::on_m_btnReadEna_clicked()
{
    g_theIotEngineApp->SendIotCmdFile((PSX_OBJ_ADDR)&m_oEngineMsgWnd, _T("ReadEna"));
}

void QPpSttIotEngineDebugWidget::on_m_btnWriteSetting_clicked()
{
    g_theIotEngineApp->SendIotCmdFile((PSX_OBJ_ADDR)&m_oEngineMsgWnd, _T("WriteSetting"));
}

void QPpSttIotEngineDebugWidget::on_m_btnPpEngine_clicked()
{
    g_theIotEngineApp->m_strProtoType = _T("PpEngine");
    g_theIotEngineApp->InitCmdFilePath();

	EnableBtns();
}

void QPpSttIotEngineDebugWidget::on_m_btnMmsEngine_clicked()
{
    g_theIotEngineApp->m_strProtoType = _T("MmsEngine");
    g_theIotEngineApp->InitCmdFilePath();

    EnableBtns();
}

void QPpSttIotEngineDebugWidget::on_m_btnCmsEngine_clicked()
{
    g_theIotEngineApp->m_strProtoType = _T("CmsEngine");
    g_theIotEngineApp->InitCmdFilePath();

    EnableBtns();
}


void QPpSttIotEngineDebugWidget::on_m_btnReadSetting_clicked()
{
    g_theIotEngineApp->SendIotCmdFile((PSX_OBJ_ADDR)&m_oEngineMsgWnd, _T("ReadSetting"));
}


void QPpSttIotEngineDebugWidget::on_m_chkSttFormat_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        g_theIotEngineApp->SetSttCmdFormat(_PUGI_XML_TYPE_);
    }
    else
    {
        g_theIotEngineApp->SetSttCmdFormat(_JSON_TYPE_);
    }
}


void QPpSttIotEngineDebugWidget::on_m_btnClose_clicked()
{
    close();
}

QPpSttIotEngineDebugWidget *g_pPpSttIotEngineDebugWidget = NULL;

void Create_PpSttIotEngineDebugWidget()
{
	if (g_pPpSttIotEngineDebugWidget == NULL)
	{
		g_pPpSttIotEngineDebugWidget = new QPpSttIotEngineDebugWidget();
		g_pPpSttIotEngineDebugWidget->show();
	}
}

void Release_PpSttIotEngineDebugWidget()
{
	if (g_pPpSttIotEngineDebugWidget != NULL)
	{
		delete g_pPpSttIotEngineDebugWidget;
		g_pPpSttIotEngineDebugWidget = NULL;
	}
}



