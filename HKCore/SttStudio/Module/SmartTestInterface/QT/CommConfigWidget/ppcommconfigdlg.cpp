#include "ppcommconfigdlg.h"
#include "ui_ppcommconfigdlg.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../Module/API/FileApi.h"





PpCommConfigDlg::PpCommConfigDlg(CPpSttCommConfig *pCommConfig, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PpCommConfigDlg)
{
    m_pCommConfig              =    pCommConfig;
    m_pWidgetSerialMode    =    NULL;
    m_pWidgetCmsMode       =    NULL;
    m_pWidgetMmsMode      =    NULL;
    m_pWidgetTcpServer      =    NULL;
    m_pWidgetTcpClient        =    NULL;
    m_pWidgetUdpServer      =   NULL;
    m_pWidgetUdpClient        =   NULL;

    ui->setupUi(this);
    m_pTabCmmConfig = new QTabWidget(this);
    m_pTabCmmConfig->setTabShape(QTabWidget::Triangular);
    ui->m_vlConfigMain->insertWidget(2, m_pTabCmmConfig);
    ui->m_grpNetConfig->setDisabled(true);

    //根据m_pCommConfig初始化页面
	ShowData();
}

PpCommConfigDlg::~PpCommConfigDlg()
{
    delete ui;
}

void PpCommConfigDlg::ShowData(CPpSttCommConfig *pCommConfig)
{
	m_pCommConfig = pCommConfig;
	ShowData();
}

void PpCommConfigDlg::ShowData()
{
	if (m_pCommConfig->Is_PpEngine_Net())
	{
		ui->m_btnNet->setChecked(true);
		on_m_btnNet_clicked();
		return;
	}
	if (m_pCommConfig->Is_PpEngine_Serial())
	{
		ui->m_btnSerial->setChecked(true);
		on_m_btnSerial_clicked();
		return;
	}

	if (m_pCommConfig->Is_MmsEngine())
	{
		ui->m_btnMms->setChecked(true);
		on_m_btnMms_clicked();
		return;
	}

	if (m_pCommConfig->Is_CmsEngine())
	{
		ui->m_btnCms->setChecked(true);
		on_m_btnCms_clicked();

// 		QCOmmConfigCmsDlg dlg;
// 		dlg.ShowData(pCommConfig);
// 		dlg.exec();
		return;
	}
}

void PpCommConfigDlg::HasChangedData()
{
    if(m_pWidgetSerialMode != NULL)
    {
        m_pWidgetSerialMode->SaveData();
    }
    if(m_pWidgetCmsMode != NULL)
    {
        m_pWidgetCmsMode->SaveData();
    }
    if(m_pWidgetMmsMode != NULL)
    {
        m_pWidgetMmsMode->SaveData();
    }
    if(m_pWidgetTcpServer != NULL)
    {
        m_pWidgetTcpServer->SaveData();
    }
    if(m_pWidgetTcpClient != NULL)
    {
        m_pWidgetTcpClient->SaveData();
    }
    if(m_pWidgetUdpServer != NULL)
    {
        m_pWidgetUdpServer->SaveData();
    }
    if(m_pWidgetUdpClient != NULL)
    {
        m_pWidgetUdpClient->SaveData();
    }
}

void PpCommConfigDlg::DeleteAllCfgWidget()
{
    if (m_pWidgetCmsMode != NULL)
    {
        delete  m_pWidgetCmsMode;
        m_pWidgetCmsMode = NULL;
    }
    if (m_pWidgetSerialMode != NULL)
    {
        delete  m_pWidgetSerialMode;
        m_pWidgetSerialMode = NULL;
    }
    if(m_pWidgetMmsMode != NULL)
    {
        delete m_pWidgetMmsMode;
        m_pWidgetMmsMode = NULL;
    }
}

void PpCommConfigDlg::DeleteNetCfgWidget()
{
    m_pTabCmmConfig->removeTab(0);
    if (m_pWidgetTcpServer != NULL)
    {
        delete  m_pWidgetTcpServer;
        m_pWidgetTcpServer = NULL;
    }
    if (m_pWidgetTcpClient != NULL)
    {
        delete  m_pWidgetTcpClient;
        m_pWidgetTcpClient = NULL;
    }
    if (m_pWidgetUdpServer != NULL)
    {
        delete  m_pWidgetUdpServer;
        m_pWidgetUdpServer = NULL;
    }
    if (m_pWidgetUdpClient != NULL)
    {
        delete  m_pWidgetUdpClient;
        m_pWidgetUdpClient = NULL;
    }
}

void PpCommConfigDlg::ChangedNetModeUnChecked()
{
    ui->m_btnTcpServer->setChecked(false);
    ui->m_btnTcpClient->setChecked(false);
    ui->m_btnUdpServer->setChecked(false);
    ui->m_btnUdpClient->setChecked(false);
}

void PpCommConfigDlg::on_m_btnSerial_clicked()
{
	if (m_pWidgetSerialMode != NULL)
	{
		return;
	}

	//m_pCommConfig->Set_Serial();
    ui->m_grpNetConfig->setDisabled(true);
	ui->m_grpNetConfig->hide();
	DeleteAllCfgWidget();
	DeleteNetCfgWidget();
	ChangedNetModeUnChecked();
	m_pWidgetSerialMode = new QCommConfigSerialMode(m_pTabCmmConfig);
	m_pTabCmmConfig->addTab(m_pWidgetSerialMode, "Serail");


	m_pCommConfig->Set_Serial();
    m_pWidgetSerialMode->ShowData(m_pCommConfig);

	



    
}

void PpCommConfigDlg::on_m_btnCms_clicked()
{
	if (m_pWidgetCmsMode != NULL)
	{
		return;
	}

	//m_pCommConfig->Set_CMS();

    ui->m_grpNetConfig->setDisabled(true);
	ui->m_grpNetConfig->hide();

	DeleteAllCfgWidget();
	DeleteNetCfgWidget();
	ChangedNetModeUnChecked();

	m_pWidgetCmsMode = new QCOmmConfigCmsDlg(m_pTabCmmConfig);
	m_pTabCmmConfig->addTab(m_pWidgetCmsMode, "CMS");
	//m_pWidgetCmsMode->ShowData(m_pCommConfig);


	m_pCommConfig->Set_CMS();
	m_pWidgetCmsMode->ShowData(m_pCommConfig);

	
}

void PpCommConfigDlg::on_m_btnNet_clicked()
{
	if (m_pWidgetCmsMode != NULL || m_pWidgetMmsMode != NULL || m_pWidgetSerialMode != NULL)
	{//如果是MMS、CMS、Serial，则切换，否则返回

	}
	else
	{
		//return;
	}

//	m_pCommConfig->Set_Net();
    ui->m_grpNetConfig->setDisabled(false);
	ui->m_grpNetConfig->show();
	DeleteAllCfgWidget();

	if (m_pCommConfig->Get_TcpClient())
	{
		ui->m_btnTcpClient->setCheckState(Qt::Checked);
		//on_m_btnTcpClient_stateChanged(2);
	}

	if (m_pCommConfig->Get_TcpServer())
	{
		ui->m_btnTcpServer->setCheckState(Qt::Checked);
		//on_m_btnTcpServer_stateChanged(1);
	}

	if (m_pCommConfig->Get_UdpClient())
	{
		ui->m_btnUdpClient->setCheckState(Qt::Checked);
		//on_m_btnUdpClient_stateChanged(1);
	}

	if (m_pCommConfig->Get_UdpServer())
	{
		ui->m_btnUdpServer->setCheckState(Qt::Checked);
		//on_m_btnUdpServer_stateChanged(1);
	}
}

void PpCommConfigDlg::on_m_btnMms_clicked()
{
	if (m_pWidgetMmsMode != NULL)
	{
		return;
	}

	m_pCommConfig->Set_MMS();
	ui->m_grpNetConfig->hide();
	DeleteAllCfgWidget();
	DeleteNetCfgWidget();
	ChangedNetModeUnChecked();
	m_pWidgetMmsMode = new QCommConfigMmsDlg(m_pTabCmmConfig);
	m_pTabCmmConfig->addTab(m_pWidgetMmsMode, "Mms");
	m_pWidgetMmsMode->ShowData(m_pCommConfig);
}

void PpCommConfigDlg::on_m_btnTcpServer_stateChanged(int arg1)
{
    int nIndex = 0;

    if(arg1 == 2)
    {
        m_pWidgetTcpServer = new QCommConfigServerDlg(m_pTabCmmConfig);
        nIndex = m_pTabCmmConfig->addTab(m_pWidgetTcpServer,"TcpServer");
        m_pTabCmmConfig->setCurrentIndex(nIndex);

		m_pCommConfig->Set_Net();
        m_pWidgetTcpServer->ShowData(m_pCommConfig);
	
    }
   else// if (arg1 == 0)
    {
        nIndex = m_pTabCmmConfig->indexOf(m_pWidgetTcpServer);
         m_pTabCmmConfig->removeTab(nIndex);
         delete  m_pWidgetTcpServer;
         m_pWidgetTcpServer = NULL;
    }
}

void PpCommConfigDlg::on_m_btnTcpClient_stateChanged(int arg1)
{
     int nIndex = 0;
    if(arg1 == 2)
    {
        m_pWidgetTcpClient = new QCommCfgTcpClientDlg(m_pTabCmmConfig);
        nIndex = m_pTabCmmConfig->addTab(m_pWidgetTcpClient,"TcpClient");
        m_pTabCmmConfig->setCurrentIndex(nIndex);

		m_pCommConfig->Set_Net();
        m_pWidgetTcpClient->ShowData(m_pCommConfig);

		
    }
    else
    {
        nIndex = m_pTabCmmConfig->indexOf(m_pWidgetTcpClient);
         m_pTabCmmConfig->removeTab(nIndex);
         delete  m_pWidgetTcpClient;
         m_pWidgetTcpClient = NULL;
    }
}

void PpCommConfigDlg::on_m_btnUdpServer_stateChanged(int arg1)
{
    int nIndex = 0;
    if(arg1 == 2)
    {
        m_pWidgetUdpServer = new QCommConfigUdpServer(m_pTabCmmConfig);
        nIndex = m_pTabCmmConfig->addTab(m_pWidgetUdpServer,"UdpServer");
        m_pTabCmmConfig->setCurrentIndex(nIndex);
			
		m_pCommConfig->Set_Net();
        m_pWidgetUdpServer->ShowData(m_pCommConfig);

    }
    else
    {
         nIndex = m_pTabCmmConfig->indexOf(m_pWidgetUdpServer);
         m_pTabCmmConfig->removeTab(nIndex);
         delete  m_pWidgetUdpServer;
         m_pWidgetUdpServer = NULL;
    }
}

void PpCommConfigDlg::on_m_btnUdpClient_stateChanged(int arg1)
{
    int nIndex = 0;
    if(arg1 == 2)
    {
        m_pWidgetUdpClient = new QCommConfigUdpClientDlg(m_pTabCmmConfig);
        nIndex = m_pTabCmmConfig->addTab(m_pWidgetUdpClient,"UdpClient");
        m_pTabCmmConfig->setCurrentIndex(nIndex);

		m_pCommConfig->Set_Net();
        m_pWidgetUdpClient->ShowData(m_pCommConfig);
		
    }
    else
    {
         nIndex = m_pTabCmmConfig->indexOf(m_pWidgetUdpClient);
         m_pTabCmmConfig->removeTab(nIndex);
         delete  m_pWidgetUdpClient;
         m_pWidgetUdpClient = NULL;
    }
}


void PpCommConfigDlg::on_m_btnSave_clicked()
{
	if (ui->m_btnSerial->isChecked())
	{
		m_pCommConfig->Set_Serial();
		if(m_pWidgetSerialMode != NULL)
		{
			m_pWidgetSerialMode->SaveData();
		}
	}
	if (ui->m_btnNet->isChecked())
	{
		m_pCommConfig->Set_Net();

		if (ui->m_btnTcpServer->isChecked())
		{
			if(m_pWidgetTcpServer != NULL)
			{
				m_pWidgetTcpServer->SaveData();
			}
		}
		else if (ui->m_btnTcpClient->isChecked())
		{
			if(m_pWidgetTcpClient != NULL)
			{
				m_pWidgetTcpClient->SaveData();
			}
		}
		else if (ui->m_btnUdpServer->isChecked())
		{
			if(m_pWidgetUdpServer != NULL)
			{
				m_pWidgetUdpServer->SaveData();
			}

		}
		else if (ui->m_btnUdpClient->isChecked())
		{
			if(m_pWidgetUdpClient != NULL)
			{
				m_pWidgetUdpClient->SaveData();
			}
		}
	}
	if (ui->m_btnMms->isChecked()) 
	{
		m_pCommConfig->Set_MMS();
		if(m_pWidgetMmsMode != NULL)
		{
			//m_pWidgetMmsMode->ShowData(m_pCommConfig);
			m_pWidgetMmsMode->SaveData();
		}
	}
	
	if (ui->m_btnCms->isChecked()) 
	{
		m_pCommConfig->Set_CMS();
		if(m_pWidgetCmsMode != NULL)
		{
			m_pWidgetCmsMode->SaveData();
		}
	}

	SaveSttCommConfigFile();
	
    //HasChangedData();

    this->accept();
}

void PpCommConfigDlg::on_m_btnCancel_clicked()
{
    this->close();
}


void PpCommConfigDlg::SaveSttCommConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");
	if (! ::IsFileExist(strFile))
	{
		return;
	}

	m_pCommConfig->SaveCommConfigFile(strFile);

}
