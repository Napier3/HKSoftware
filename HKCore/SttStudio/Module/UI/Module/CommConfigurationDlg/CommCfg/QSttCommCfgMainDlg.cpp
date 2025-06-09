#include "QSttCommCfgMainDlg.h"
#include <QDirIterator>
#include <QMessageBox>
#include "../../../../../../Module/xml/PugiXML/pugixml.hpp"
#include "../../Module/XLangResource_Native.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../../SmartTestInterface/PpSttCommConfig.h"
#include "../../../Module/API/FileApi.h"
#include "../../../../../../Module/DataMngr/DvmDevice.h"
#include "../DevComm/QSttCommCfgDeviceWidget.h"
#include "../../../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../SttTestCntrFrameBase.h"

#ifdef _PSX_QT_LINUX_
#include "./../../Module/API/NetworkInterface.h"
#endif

#ifdef _PSX_QT_WINDOWS_
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;
#endif

//extern void Global_SetLinuxDevIP(CString strIP, CString strMask);
extern QFont *g_pSttGlobalFont;
extern bool g_bHasTcpClient = false;
extern bool g_hHsTcpServer = false;
extern bool g_hHsUdpClient = false;
extern bool g_hHsUdpServer = false;
extern bool g_hHsSerial = false;
//获取规约模板文件保存全路径
CString  Global_GetProtolTemplPath()
{
	CString strInstallPath = _P_GetInstallPath();
	CString strProtolPath = strInstallPath + CString("e-Protocol/Template/");
	QDir dir(strProtolPath);
	if (!dir.exists())
	{
		QMessageBox oChkBox(QMessageBox::Information, CString("提示"), CString("路径不存在:") + strProtolPath, QMessageBox::Ok);
		//使 MyBox 对话框显示s
		oChkBox.exec();
	}
	return strProtolPath;
}

//获取点表文件保存全路径
CString Global_GetPointTbFilePath()
{
	CString strInstallPath = _P_GetInstallPath();
	CString strPointTbFilePath = strInstallPath + CString("e-Protocol/Library/");
	QDir dir(strPointTbFilePath);
	if (!dir.exists())
	{
		QMessageBox oChkBox(QMessageBox::Information, CString("提示"), CString("路径不存在:") + strPointTbFilePath, QMessageBox::Ok);
		//使 MyBox 对话框显示s
		oChkBox.exec();
	}
	return strPointTbFilePath;
}

//设置Linux装置IP地址
void Global_SetLinuxDevIP(CString strIP, CString strMask)
{
	if (strIP.IsEmpty() || strMask.IsEmpty())
	{
		return;
	}

#ifdef _PSX_QT_LINUX_
#ifndef _PSX_OS_CENTOS_
	QStringList astrIP, astrMask;
	int nErrCode = stt_net_get_ip(astrIP, astrMask);
	if (!astrIP.contains(strIP))
	{
		astrIP.append(strIP);
		astrMask.append(strMask);
		int nBeginIndex = astrIP.size();
		stt_net_set_ip(astrIP, astrMask, nBeginIndex);
	}
#endif
#endif

}

//解析规约模板文件
CExBaseList * Global_OpenPpxmlFile(CString srFilePath)
{
	CExBaseList* pDataList = new CExBaseList();
	CDvmData *pDataRes = NULL;

	CXmlRWDocBase* pXmlDocPtr = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

	if (pXmlDocPtr == NULL)
	{
		return pDataList;
	}
	try
	{
		if ( !xml_OpenFile(pXmlDocPtr, srFilePath) )
		{
			delete pXmlDocPtr;
			pXmlDocPtr = NULL;
			return pDataList;
		}
	}
	catch (...)
	{
		delete pXmlDocPtr;
		pXmlDocPtr = NULL;
		return pDataList;
	}
	CXmlRWNodeBase*  pXmlRootptr = pXmlDocPtr->GetDocNode();
	if (pXmlRootptr == NULL)
	{
		return pDataList;
	}
	CXmlRWNodeBase* oNodeRoot = pXmlRootptr->GetChildNode(CString("pp-template"));
	if (oNodeRoot == NULL)
	{
		return pDataList;
	}
	CXmlRWNodeBase* oNodeComCfg = oNodeRoot->GetChildNode(CString("comm-config"));
	if (oNodeComCfg == NULL)
	{
		return pDataList;
	}
	CXmlRWNodeBase* oNodeNet = oNodeComCfg->GetChildNode(CString("net"));
	CXmlRWNodeBase* oNodeSerial = oNodeComCfg->GetChildNode(CString("serial"));
	if (oNodeNet != NULL)//tcp-client
	{
		//<tcp-client local-ip="172.21.0.100" local-port="0" client-ip="" remote-ip="192.168.10.57" remote-port="102">
		CXmlRWNodeBase* oNodeTcpClient = oNodeNet->GetChildNode(CString("tcp-client"));
		if ( oNodeTcpClient != NULL )
		{
			g_bHasTcpClient = true; 
			pDataRes = new CDvmData;
			pDataRes->m_strID = CString("tcp-client");
			pDataRes->AddValue(CString("DeviceAddr"),CString(""));
			CString valueLocalIp;
			oNodeTcpClient->xml_GetAttibuteValue(L"local-ip", valueLocalIp);
			pDataRes->AddValue(CString("local-ip"),valueLocalIp);
			CString valueLocalPort;
			oNodeTcpClient->xml_GetAttibuteValue(L"local-port", valueLocalPort);
			pDataRes->AddValue(CString("local-port"),valueLocalPort);
			CString valueClientIp;
			oNodeTcpClient->xml_GetAttibuteValue(L"client-ip", valueClientIp);
			pDataRes->AddValue(CString("SubnetMask"),CString("255.255.255.0"));
			CString valueRemoteIp;
			oNodeTcpClient->xml_GetAttibuteValue(L"remote-ip", valueRemoteIp);
			pDataRes->AddValue(CString("remote-ip"),valueRemoteIp);
			CString valueRemotePort;
			oNodeTcpClient->xml_GetAttibuteValue(L"remote-port", valueRemotePort);
			pDataRes->AddValue(CString("remote-port"),valueRemotePort);
			pDataList->AddNewChild(pDataRes);
		}

		CXmlRWNodeBase* oNodeUdpClient = oNodeNet->GetChildNode(CString("udp-client"));
		if (oNodeUdpClient != NULL )
		{
			g_hHsUdpClient = true; 
			pDataRes = new CDvmData;
			pDataRes->m_strID = CString("udp-client");
			CString valueLocalIp;
			oNodeUdpClient->xml_GetAttibuteValue(L"local-ip", valueLocalIp);
			pDataRes->AddValue(CString("local-ip"),valueLocalIp);
			CString valueLocalPort;
			oNodeUdpClient->xml_GetAttibuteValue(L"local-port", valueLocalPort);
			pDataRes->AddValue(CString("local-port"),valueLocalPort);
			CString valueClientIp;
			oNodeUdpClient->xml_GetAttibuteValue(L"client-ip", valueClientIp);
			pDataRes->AddValue(CString("SubnetMask"),CString("255.255.255.0"));
			CString valueRemoteIp;
			oNodeUdpClient->xml_GetAttibuteValue(L"remote-ip", valueRemoteIp);
			pDataRes->AddValue(CString("remote-ip"),valueRemoteIp);
			CString valueRemotePort;
			oNodeUdpClient->xml_GetAttibuteValue(L"remote-port", valueRemotePort);
			pDataRes->AddValue(CString("remote-port"),valueRemotePort);
			CString strMulticastIP;
			oNodeUdpClient->xml_GetAttibuteValue(L"multicast-ip", strMulticastIP);
			pDataRes->AddValue(CString("multicast-ip"),strMulticastIP);
			CString strUseBroadcast;
			oNodeUdpClient->xml_GetAttibuteValue(L"use-broadcast", strUseBroadcast);
			pDataRes->AddValue(CString("use-broadcast"),strUseBroadcast);
			pDataList->AddNewChild(pDataRes);
		}

		// 解析 TCP Server
		CXmlRWNodeBase* oNodeTcpServer = oNodeNet->GetChildNode(CString("tcp-server"));
		if (oNodeTcpServer) 
		{
			g_hHsTcpServer = true;
			pDataRes = new CDvmData;
			pDataRes->m_strID = CString("tcp-server");
			CString valueLocalIp, valueLocalPort;
			oNodeTcpServer->xml_GetAttibuteValue(L"local-ip", valueLocalIp);
			oNodeTcpServer->xml_GetAttibuteValue(L"local-port", valueLocalPort);
			pDataRes->AddValue(CString("local-ip"), valueLocalIp);
			pDataRes->AddValue(CString("local-port"), valueLocalPort);
			pDataList->AddNewChild(pDataRes);
		}

	
		CXmlRWNodeBase* oNodeUdpServer = oNodeNet->GetChildNode(CString("udp-server"));
		if (oNodeUdpServer != NULL )
		{
			g_hHsUdpServer = true; 
			pDataRes = new CDvmData;
			pDataRes->m_strID = CString("udp-server");
			CString valueLocalIp, valueLocalPort,strMulticastIP,strUseBroadcast;
			oNodeUdpServer->xml_GetAttibuteValue(L"local-ip", valueLocalIp);
			oNodeUdpServer->xml_GetAttibuteValue(L"local-port", valueLocalPort);
			oNodeUdpServer->xml_GetAttibuteValue(L"multicast-ip", strMulticastIP);
			oNodeUdpServer->xml_GetAttibuteValue(L"use-broadcast", strUseBroadcast);
			pDataRes->AddValue(CString("local-ip"), valueLocalIp);
			pDataRes->AddValue(CString("local-port"), valueLocalPort);
			pDataRes->AddValue(CString("multicast-ip"),strMulticastIP);
			pDataRes->AddValue(CString("use-broadcast"),strUseBroadcast);
			pDataList->AddNewChild(pDataRes);
		}

	}
	else if (oNodeSerial != NULL) 
	{
		//<serial port_number="2" baud-rate="9600" byte-size="8" stop-bit="1" parity="0">
		g_hHsSerial = true;
		pDataRes = new CDvmData;
		pDataRes->m_strID = CString("serials");
		pDataRes->AddValue(CString("DeviceAddr"),CString(""));
		CString valuePortNo;
		oNodeSerial->xml_GetAttibuteValue(L"port_number", valuePortNo);
		pDataRes->AddValue(CString("port_number"),valuePortNo);
		CString valueBaudRate;
		oNodeSerial->xml_GetAttibuteValue(L"baud-rate", valueBaudRate);
		pDataRes->AddValue(CString("baud-rate"),valueBaudRate);
		CString valueByteSize;
		oNodeSerial->xml_GetAttibuteValue(L"byte-size", valueByteSize);
		pDataRes->AddValue(CString("byte-size"),valueByteSize);
		CString valueStopBit;
		oNodeSerial->xml_GetAttibuteValue(L"stop-bit", valueStopBit);
		pDataRes->AddValue(CString("stop-bit"),valueStopBit);
		CString valueParity;
		oNodeSerial->xml_GetAttibuteValue(L"parity", valueParity);
		pDataRes->AddValue(CString("parity"),valueParity);
		pDataList->AddNewChild(pDataRes);

	}

	delete pXmlDocPtr;
	pXmlDocPtr = NULL;
	return pDataList;
}


QSttCommCfgMainDlg::QSttCommCfgMainDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setWindowTitle(CString("通讯配置"));
	m_pProproTemplate_ComboBox = NULL;
	m_pPointFile_ComboBox = NULL;
	m_pConnect_PushButton = NULL;
	m_pDevAddrDvmDevice = NULL;
	m_bNetTableSave = FALSE;
	m_bSerialTableSave = FALSE;
//	m_nConnectStateIndex = 0;
	m_bIsSaveFlag = false;
	m_pTabWidget = NULL;
	m_pUdpClientDevcieGrid = NULL;
	m_pTcpClientDevcieGrid = NULL;
	m_pTcpServerDevcieGrid = NULL;   
	m_pUdpServerDevcieGrid = NULL;  
	m_pSerialDevcieGrid = NULL; 
	initUI();
}

QSttCommCfgMainDlg::~QSttCommCfgMainDlg()
{
 	if(m_pTcpClientDevcieGrid != NULL)
 	{
 		delete m_pTcpClientDevcieGrid;
 		m_pTcpClientDevcieGrid = NULL;
 	}

	if(m_pUdpClientDevcieGrid != NULL)
	{
		delete m_pUdpClientDevcieGrid;
		m_pUdpClientDevcieGrid = NULL;
	}
	if(m_pTcpServerDevcieGrid != NULL)
	{
		delete m_pTcpServerDevcieGrid;
		m_pTcpServerDevcieGrid = NULL;
	}
	if(m_pTcpServerDevcieGrid != NULL)
	{
		delete m_pTcpServerDevcieGrid;
		m_pTcpServerDevcieGrid = NULL;
	}
	if(m_pSerialDevcieGrid != NULL)
	{
		delete m_pSerialDevcieGrid;
		m_pSerialDevcieGrid = NULL;
	}
 
 	if (m_pDevAddrDvmDevice != NULL)
 	{
 		delete m_pDevAddrDvmDevice;
 		m_pDevAddrDvmDevice = NULL;
 	}
 
	m_pPpxmlFileData->DeleteAll();

 	if (m_pLabelProtolType != NULL)
 	{
 		delete m_pLabelProtolType;
 		m_pLabelProtolType = NULL;
 	}
 
 	if (m_pLabelPointXmlType != NULL)
 	{
 		delete m_pLabelPointXmlType;
 		m_pLabelPointXmlType = NULL;
 	}
 
 	if (m_pProproTemplate_ComboBox != NULL)
 	{
 		delete m_pProproTemplate_ComboBox;
 		m_pProproTemplate_ComboBox = NULL;
 	}
 
 	if (m_pPointFile_ComboBox != NULL)
 	{
 		delete m_pPointFile_ComboBox;
 		m_pPointFile_ComboBox = NULL;
 	}
 
 	if (m_pConnect_PushButton != NULL)
 	{
 		delete m_pConnect_PushButton;
 		m_pConnect_PushButton = NULL;
 	}
 
 	if (m_pOK_PushButton != NULL)
 	{
 		delete m_pOK_PushButton;
 		m_pOK_PushButton = NULL;
 	}
 
 	if (m_pCancel_PushButton != NULL)
 	{
 		delete m_pCancel_PushButton;
 		m_pCancel_PushButton = NULL;
 	}

	if (layout())
	{
		QLayoutItem *item;
		while ((item = layout()->takeAt(0)) != NULL) 
		{ 
			if (QWidget *widget = item->widget())
			{
				delete widget;  
			}
			delete item;  
		}
		delete layout();  
		setLayout(NULL);
	}

}

//Dialog初始化UI
void QSttCommCfgMainDlg::initUI()
{
	//ReleaseUI();
	resize(800, 630);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	m_pTabWidget = new QTabWidget(this);

  	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  	sizePolicy.setHorizontalStretch(30);
  	sizePolicy.setVerticalStretch(30);

	QFont font1;
	font1.setPointSize(15);

	QVBoxLayout *pAllVLayout = new QVBoxLayout(this);
	QHBoxLayout *pTop_HLayout = new QHBoxLayout(this);
	pTop_HLayout->setAlignment(Qt::AlignTop);
	QVBoxLayout *pTopLeft_VLayout = new QVBoxLayout(this);
	QHBoxLayout *pFirstProtol_HLayout = new QHBoxLayout(this);
	m_pLabelProtolType = new QLabel(this);
	m_pLabelProtolType->setText(CString("规约类型:"));
	m_pProproTemplate_ComboBox = new QScrollComboBox(this);
// 	m_pProproTemplate_ComboBox->setMinimumSize(QSize(0, 0));
// 	m_pProproTemplate_ComboBox->setMaximumSize(QSize(16777215, 16777215));
	m_pProproTemplate_ComboBox->setFont(font1);

	pFirstProtol_HLayout->addWidget(m_pLabelProtolType);
	pFirstProtol_HLayout->addWidget(m_pProproTemplate_ComboBox);
	pFirstProtol_HLayout->addStretch();
	pTopLeft_VLayout->addLayout(pFirstProtol_HLayout);
	QHBoxLayout *pMidPoint_HLayout = new QHBoxLayout(this);
	m_pLabelPointXmlType = new QLabel(this);
	m_pLabelPointXmlType->setText(CString("点表类型:"));
	m_pPointFile_ComboBox = new QScrollComboBox(this);
// 	m_pPointFile_ComboBox->setMinimumSize(QSize(0, 0));
// 	m_pPointFile_ComboBox->setMaximumSize(QSize(16777215, 16777215));
	m_pPointFile_ComboBox->setFont(font1);

	pMidPoint_HLayout->addWidget(m_pLabelPointXmlType);
	pMidPoint_HLayout->addWidget(m_pPointFile_ComboBox);
	pMidPoint_HLayout->addStretch();
	pTopLeft_VLayout->addLayout(pMidPoint_HLayout);
	pTop_HLayout->addLayout(pTopLeft_VLayout);
	m_pConnect_PushButton = new QPushButton(this);
	m_pConnect_PushButton->setText(CString("连接"));
//	pTop_HLayout->addSpacing();
	pTop_HLayout->addWidget(m_pConnect_PushButton);
	pAllVLayout->addLayout(pTop_HLayout);
	pAllVLayout->addWidget(m_pTabWidget);
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(g_sLangTxt_OK);
	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(g_sLangTxt_Cancel);
	QHBoxLayout *m_pOkCancel_HBoxLayout = new QHBoxLayout(this);
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->addWidget(m_pOK_PushButton);
	m_pOkCancel_HBoxLayout->addSpacing(10);
	m_pOkCancel_HBoxLayout->addWidget(m_pCancel_PushButton);
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);
	pAllVLayout->addLayout(m_pOkCancel_HBoxLayout);
	this->setLayout(pAllVLayout);

	m_pConnect_PushButton->setFixedHeight(60);
	m_pProproTemplate_ComboBox->setFixedWidth_All(600,600);
	m_pPointFile_ComboBox->setFixedWidth_All(600,600);

	//m_pProproTemplate_ComboBox->SetCoboboxVertScrollWidth(700,50);
	//m_pPointFile_ComboBox->SetCoboboxVertScrollWidth(700,50);

	InitDatas();

	connect(m_pProproTemplate_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ProtolTempateComboChanged(int)));
	connect(m_pPointFile_ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_PointFileComboChanged(int)));
	connect(m_pConnect_PushButton, SIGNAL(clicked()), this, SLOT(slot_ConnectClicked()));
 	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
 	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));

	if (m_pTcpClientDevcieGrid)
	{
		connect(m_pTcpClientDevcieGrid, SIGNAL(sig_ChangedDevAddr(long)), this, SLOT(slot_ChangedDevAddr(long)));
		connect(m_pTcpClientDevcieGrid, SIGNAL(sig_ChangedNetTable()), this, SLOT(slot_ChangedNetTable()));
	}

	if (m_pUdpClientDevcieGrid)
	{
		connect(m_pUdpClientDevcieGrid, SIGNAL(sig_ChangedDevAddr(long)), this, SLOT(slot_ChangedDevAddr(long)));
		connect(m_pUdpClientDevcieGrid, SIGNAL(sig_ChangedNetTable()), this, SLOT(slot_ChangedNetTable()));
	}

	if (m_pTcpServerDevcieGrid)
	{
		connect(m_pTcpServerDevcieGrid, SIGNAL(sig_ChangedDevAddr(long)), this, SLOT(slot_ChangedDevAddr(long)));
		connect(m_pTcpServerDevcieGrid, SIGNAL(sig_ChangedNetTable()), this, SLOT(slot_ChangedNetTable()));
	}

	if (m_pUdpServerDevcieGrid)
	{
		connect(m_pUdpServerDevcieGrid, SIGNAL(sig_ChangedDevAddr(long)), this, SLOT(slot_ChangedDevAddr(long)));
		connect(m_pUdpServerDevcieGrid, SIGNAL(sig_ChangedNetTable()), this, SLOT(slot_ChangedNetTable()));
	}

	if (m_pSerialDevcieGrid)
	{
		connect(m_pSerialDevcieGrid, SIGNAL(sig_ChangedSerialTable()), this, SLOT(slot_ChangedSerialTable()));
	}

	SetDialogFont();

}


void QSttCommCfgMainDlg::AddTab()
{
	if (g_bHasTcpClient)
	{
		if (m_pTcpClientDevcieGrid == NULL)
		{
			m_pTcpClientDevcieGrid = new SttCCommCfgDeviceAttrsGrid(this);
			m_pTcpClientDevcieGrid->InitGrid();
			m_pTcpClientWidget = new QWidget();
			QVBoxLayout* pTcpClientLayout = new QVBoxLayout(m_pTcpClientWidget);
			pTcpClientLayout->addWidget(m_pTcpClientDevcieGrid);
			m_pTabWidget->addTab(m_pTcpClientWidget, _T("Tcp客户端"));
		}
		else
		{
			int index = m_pTabWidget->indexOf(m_pTcpClientWidget);
			if (index == -1)  
			{
				m_pTabWidget->addTab(m_pTcpClientWidget, _T("Tcp客户端"));
			}
		}
	}
	else
	{
		if (m_pTcpClientWidget)
		{
			int index = m_pTabWidget->indexOf(m_pTcpClientWidget);
			if (index != -1)
			{
				m_pTabWidget->removeTab(index);
			}
		}
	}

	if (g_hHsUdpClient)
	{
		if (m_pUdpClientDevcieGrid == NULL)
		{
			m_pUdpClientDevcieGrid = new SttCCommCfgDeviceAttrsGrid(this);
			m_pUdpClientDevcieGrid->InitGrid();
			m_pUdpClientWidget = new QWidget();
			QVBoxLayout* pUdpClientLayout = new QVBoxLayout(m_pUdpClientWidget);
			pUdpClientLayout->addWidget(m_pUdpClientDevcieGrid);
			m_pTabWidget->addTab(m_pUdpClientWidget, _T("Udp客户端"));
		}
		else
		{
			int index = m_pTabWidget->indexOf(m_pUdpClientWidget);
			if (index == -1)  
			{
				m_pTabWidget->addTab(m_pUdpClientWidget, _T("Udp客户端"));
			}
		}
	}
	else
	{
		if (m_pUdpClientWidget)
		{
			int index = m_pTabWidget->indexOf(m_pUdpClientWidget);
			if (index != -1)
			{
				m_pTabWidget->removeTab(index);
			}
		}
	}

	if (g_hHsTcpServer)
	{
		if (m_pTcpServerDevcieGrid == NULL)
		{
			m_pTcpServerDevcieGrid = new SttCCommCfgDeviceAttrsGrid(this);
			m_pTcpServerDevcieGrid->InitGrid();
			m_pTcpServerWidget = new QWidget();
			QVBoxLayout* pTcpServerLayout = new QVBoxLayout(m_pTcpServerWidget);
			pTcpServerLayout->addWidget(m_pTcpServerDevcieGrid);
			m_pTabWidget->addTab(m_pTcpServerWidget, _T("Tcp服务端"));
		}
		else
		{
			int index = m_pTabWidget->indexOf(m_pTcpServerWidget);
			if (index == -1)  
			{
				m_pTabWidget->addTab(m_pTcpServerWidget, _T("Tcp服务端"));
			}
		}
	}
	else
	{
		if (m_pTcpServerWidget)
		{
			int index = m_pTabWidget->indexOf(m_pTcpServerWidget);
			if (index != -1)
			{
				m_pTabWidget->removeTab(index);
			}
		}
	}


	if (g_hHsUdpServer)
	{
		if (m_pUdpServerDevcieGrid == NULL)
		{
			m_pUdpServerDevcieGrid = new SttCCommCfgDeviceAttrsGrid(this);
			m_pUdpServerDevcieGrid->InitGrid();
			QWidget* pUdpServerTab = new QWidget();
			QVBoxLayout* pUdpServerLayout = new QVBoxLayout(pUdpServerTab);
			pUdpServerLayout->addWidget(m_pUdpServerDevcieGrid);
			m_pTabWidget->addTab(pUdpServerTab, _T("Udp服务端"));
		}
		else
		{
			int index = m_pTabWidget->indexOf(m_pUdppServerWidget);
			if (index == -1)  
			{
				m_pTabWidget->addTab(m_pUdppServerWidget, _T("Udp服务端"));
			}
		}
	}
	else
	{
		if (m_pUdppServerWidget)
		{
			int index = m_pTabWidget->indexOf(m_pUdppServerWidget);
			if (index != -1)
			{
				m_pTabWidget->removeTab(index);
			}
		}
	}


	if (g_hHsSerial)
	{
		if (m_pSerialDevcieGrid == NULL)
		{
			m_pSerialDevcieGrid = new SttCCommCfgDeviceAttrsGrid(this);
			m_pSerialDevcieGrid->InitGrid();
			m_pSerialWidget = new QWidget();
			QVBoxLayout* pSerialLayout = new QVBoxLayout(m_pSerialWidget);
			pSerialLayout->addWidget(m_pSerialDevcieGrid);
			m_pTabWidget->addTab(m_pSerialWidget, _T("串口"));
		}
		else
		{
			int index = m_pTabWidget->indexOf(m_pSerialWidget);
			if (index == -1)  
			{
				m_pTabWidget->addTab(m_pSerialWidget, _T("Udp客户端"));
			}
		}
	}
	else
	{
		if (m_pSerialWidget)
		{
			int index = m_pTabWidget->indexOf(m_pSerialWidget);
			if (index != -1)
			{
				m_pTabWidget->removeTab(index);
			}
		}
	}
}

//设置通讯配置字体
void QSttCommCfgMainDlg::SetDialogFont()
{
	if (g_pSttGlobalFont == NULL)
	{
		return;
	}
	m_pLabelProtolType->setFont(*g_pSttGlobalFont);
	m_pLabelPointXmlType->setFont(*g_pSttGlobalFont);
	m_pConnect_PushButton->setFont(*g_pSttGlobalFont);
	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
	m_pProproTemplate_ComboBox->setFont(*g_pSttGlobalFont);
	m_pPointFile_ComboBox->setFont(*g_pSttGlobalFont);
	m_pTabWidget->setFont(*g_pSttGlobalFont);
}

//设置通讯配置DialogCombo选中项
void QSttCommCfgMainDlg::SetComboItemIndex(int iComboType)
{
	if (iComboType == CFMDLG_COMBO_TYPE_PPXMLFILE)
	{
		CString strCfgPpxml;
		OpenPpSttCommConfigFile(iComboType, strCfgPpxml, strCfgPpxml);
		int nPosPpxml = strCfgPpxml.ReverseFind('.');
		if (nPosPpxml >= 0)
		{
			strCfgPpxml = strCfgPpxml.Left(nPosPpxml);
		}
		if (!strCfgPpxml.IsEmpty())
		{
			for (int i=0; i<m_pProproTemplate_ComboBox->count(); i++)
			{
				if (strCfgPpxml == m_pProproTemplate_ComboBox->itemText(i))
				{
					m_pProproTemplate_ComboBox->setCurrentIndex(i);

				}
			}
		}
	}
	else if (iComboType ==  CFMDLG_COMBO_TYPE_DVMFILE)
	{

		CString strCfgDvmFile;
		OpenPpSttCommConfigFile(iComboType, strCfgDvmFile, strCfgDvmFile);
		int nPosDvmFile = strCfgDvmFile.ReverseFind('.');
		if (nPosDvmFile >= 0)
		{
			strCfgDvmFile = strCfgDvmFile.Left(nPosDvmFile);
			int nPosSplash = strCfgDvmFile.ReverseFind('/');
			if (nPosSplash > 0)
			{
				strCfgDvmFile = strCfgDvmFile.Right(strCfgDvmFile.GetLength()-1-nPosSplash);
			}
		}
		if (!strCfgDvmFile.IsEmpty())
		{
			for (int i=0; i<m_pPointFile_ComboBox->count(); i++)
			{
				if (strCfgDvmFile == m_pPointFile_ComboBox->itemText(i))
				{
					m_pPointFile_ComboBox->setCurrentIndex(i);

				}
			}
		}

	}

}

//通讯配置Dialog初始化数据
void QSttCommCfgMainDlg::InitDatas()
{
	CString strProtPath = Global_GetProtolTemplPath();
	CString strPointTbPath = Global_GetPointTbFilePath();
	QStringList* pListProTols = ScanDataDir(strProtPath, CString("ppxml"));
	m_pProproTemplate_ComboBox->addItems(*pListProTols);
	SetComboItemIndex(1);
	//	m_pProproTemplate_ComboBox->setCurrentIndex(0);
	CString strPointSubPath = strPointTbPath + m_pProproTemplate_ComboBox->currentText();
	QStringList* pListPointTbs = ScanDataDir(strPointSubPath, CString("xml"));
	m_pPointFile_ComboBox->clear();
	m_pPointFile_ComboBox->addItems(*pListPointTbs);
	SetComboItemIndex(2);
	//	m_pPointFile_ComboBox->setCurrentIndex(0);
	QString pCrtProtTxt = m_pProproTemplate_ComboBox->currentText();
	if (!pCrtProtTxt.isEmpty())
	{
		ParseProtolTmplXmlFile(pCrtProtTxt);
	}
	
}

//扫描文件路径获取点表-规约文件
QStringList* QSttCommCfgMainDlg::ScanDataDir(CString strScanPath, CString argFileSuffix) 
{
	QStringList *pAllFilesList = new QStringList;
	QDir dirProtoDir(strScanPath);
	if (!dirProtoDir.exists())
	{
		return pAllFilesList; 
	}
	dirProtoDir.setFilter(QDir::Files | QDir::NoSymLinks);
	QFileInfoList oSubFilesList = dirProtoDir.entryInfoList();
	int iSubFilesListCnt = oSubFilesList.count();
	if (iSubFilesListCnt <= 0)
	{
		return pAllFilesList; 
	}
	for (int i=0; i<iSubFilesListCnt; i++)
	{
		QFileInfo oFileInfo = oSubFilesList.at(i);
		QString strSuffix = oFileInfo.suffix();	
		if(QString::compare(strSuffix, argFileSuffix, Qt::CaseInsensitive) == 0)
		//if(QString::compare(suffix, QString("ppxml"), Qt::CaseInsensitive) == 0)
		{
			//QString absolute_file_path = file_info.absoluteFilePath();
			QString fileNameold = oFileInfo.fileName();
			CString fileName = (CString)fileNameold;
			char ch = '.';
			int nPos = fileName.ReverseFind(ch);
			if (nPos >= 0)
			{
				fileName=fileName.Left(nPos);
			}
			pAllFilesList->append(fileName);
		}
	}

	return pAllFilesList;

}

//规约模板选择ComboBox的槽函数
void QSttCommCfgMainDlg::slot_ProtolTempateComboChanged(int index)
{
	//切换规约文件 如果在连接状态 先断开现有连接 新的规约文件是未连接状态
	//如果断开失败 暂时不允许切换
	//zhouhj 2024.8.10 不能用m_nConnectStateIndex = 2标记是否已连接
	if(g_theTestCntrFrame->m_pEngineClientWidget != NULL)
	{
		if(g_theTestCntrFrame->m_pEngineClientWidget->IsConnectSuccessful()/*m_nConnectStateIndex == 2*/)
		{
			QSttCommCfgDeviceWidget *pPpSttIotEngineClientWidgetMain = NULL;
			//断开连接
			pPpSttIotEngineClientWidgetMain =  (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
			pPpSttIotEngineClientWidgetMain->m_pPpSttIotEngineClientInterface = this;
			if(pPpSttIotEngineClientWidgetMain->CloseCurrentConnect())
			{
				UpdateConnectStateUI(0);
			}
			else
			{
				CString strMsgText;
				strMsgText = _T("断开当前连接失败,请重新断开.");
				CXMessageBox::information(this, /*tr("提示")*/g_sLangTxt_Message, /*tr("断开当前连接失败,请重新断开")*/strMsgText);
				return;
			}
		}
	}
	

	m_bIsSaveFlag = true;

	QString pCrtProtTxt = m_pProproTemplate_ComboBox->currentText();
	if (pCrtProtTxt.isEmpty())
	{
		return;
	}
	CString strCrtProtTxt = pCrtProtTxt;
	CString strPointTbPath = Global_GetPointTbFilePath();
	CString strPointSubPath = strPointTbPath + strCrtProtTxt;
	QStringList* pListPointTbs = ScanDataDir(strPointSubPath, CString("xml"));
	m_pPointFile_ComboBox->clear();
	m_pPointFile_ComboBox->addItems(*pListPointTbs);
	m_pPointFile_ComboBox->setCurrentIndex(0);
	CString ppXmlAllPath = strCrtProtTxt+CString(".ppxml");
	//OpenPpSttCommConfigFile(1, ppXmlAllPath, ppXmlAllPath);
	ParseProtolTmplXmlFile(strCrtProtTxt);
}

//通讯回调Command函数
void QSttCommCfgMainDlg::OnCommCommandMsg(WPARAM wParam,LPARAM lParam)
{

}

//更新连接按钮文本
void QSttCommCfgMainDlg::UpdateConnectStateUI(long nHasConnected)
{
	CString strMsg;

	if (nHasConnected)
	{
		//strMsg = "已连接";
		strMsg = "断开";
//		m_nConnectStateIndex = 2;
	} 
	else
	{
		strMsg = "连接";
//		m_nConnectStateIndex = 0;
	}

	m_pConnect_PushButton->setText(strMsg);
}

//通讯回调Engine函数
void QSttCommCfgMainDlg::OnEngineSystemMessage(WPARAM wParam, LPARAM lParam)
{
	CString strTitile,strMsg;
	strTitile = "提示";

	switch (lParam)
	{
	case engineConnectDeviceFailed:
		strMsg = "连接失败.";
		CXMessageBox::information(this, strTitile, strMsg);
//		m_nConnectStateIndex = 0;
		UpdateConnectStateUI(0);
		break;

	case engineConnectDeviceSuccessful:
//		m_nConnectStateIndex++;

//		if (m_nConnectStateIndex == 2)//忽略第一次连接成功状态
		{
			strMsg = "连接成功.";
			CXMessageBox::information(this, strTitile, strMsg);
			UpdateConnectStateUI(1);		
		}

		break;

	case engineCommError:
		break;

	case engineException:
		break;

	default:
		break;
	}
}

//点表文件选择ComboBox的槽函数
void QSttCommCfgMainDlg::slot_PointFileComboChanged(int index)
{
	QString pCrtPintTbTxt = m_pPointFile_ComboBox->currentText();
	if (pCrtPintTbTxt.isEmpty())
	{
		//CString strEmpty="";
		//OpenPpSttCommConfigFile(2, strEmpty, strEmpty); 
		return;
	}
	m_bIsSaveFlag = true;

	CString strCrtPointTxt = pCrtPintTbTxt + CString(".xml");
	//OpenPpSttCommConfigFile(2, strCrtPointTxt, strCrtPointTxt);

	ParseProtolTmplXmlFile(m_pProproTemplate_ComboBox->currentText());
}

void QSttCommCfgMainDlg::slot_ConnectClicked()
{
	QSttCommCfgDeviceWidget *pPpSttIotEngineClientWidgetMain = NULL;
	//断开连接
	if(g_theTestCntrFrame->m_pEngineClientWidget != NULL)
	{
		if (g_theTestCntrFrame->m_pEngineClientWidget->IsConnectSuccessful())
		{
			QSttCommCfgDeviceWidget *pPpSttIotEngineClientWidgetMain = NULL;
			pPpSttIotEngineClientWidgetMain =  (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
			pPpSttIotEngineClientWidgetMain->m_pPpSttIotEngineClientInterface = this;

			if(pPpSttIotEngineClientWidgetMain->CloseCurrentConnect())
			{
				UpdateConnectStateUI(0);
			}
			else
			{
				CString strMsgText;
				strMsgText = _T("断开当前连接失败,请重新断开.");
				CXMessageBox::information(this, /*tr("提示")*/strMsgText, /*tr("断开当前连接失败,请重新断开")*/strMsgText);
			}

			return;
		}
	}


// 	if(m_nConnectStateIndex == 2)
// 	{
// 		//断开连接
// 		if(g_theTestCntrFrame->m_pEngineClientWidget != NULL)
// 		{
// 			pPpSttIotEngineClientWidgetMain =  (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
// 			pPpSttIotEngineClientWidgetMain->m_pPpSttIotEngineClientInterface = this;
// 			if(pPpSttIotEngineClientWidgetMain->CloseCurrentConnect())
// 			{
// 				UpdateConnectStateUI(0);
// }
// 			else
// 			{
// 				CString strMsgText;
// 				strMsgText = _T("断开当前连接失败,请重新断开.");
// 				CXMessageBox::information(this, /*tr("提示")*/g_sLangTxt_Message, /*tr("断开当前连接失败,请重新断开")*/strMsgText);
// 			}
// 		}
// 		return;
// 	}
	//连接
	//g_theTestCntrFrame->CreateEngineClientWidget();
	//QPpSttIotEngineClientWidgetMain *pPpSttIotEngineClientWidgetMain =  (QPpSttIotEngineClientWidgetMain*)g_theTestCntrFrame->m_pEngineClientWidget;
	//pPpSttIotEngineClientWidgetMain->m_pPpSttIotEngineClientInterface = this;
	//m_nConnectStateIndex = 0;
	//long nRet = pPpSttIotEngineClientWidgetMain->ConnectDevice();

	BOOL bHasConnect = FALSE;

	// 根据修改 修改连接的条件  使用最新的条件连接
	if(g_theTestCntrFrame->m_pEngineClientWidget == NULL)
	{
		bHasConnect = g_theTestCntrFrame->CreateEngineClientWidget();
	}

	long nRet = 0;
	pPpSttIotEngineClientWidgetMain =  (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
	pPpSttIotEngineClientWidgetMain->m_pPpSttIotEngineClientInterface = this;


	if(m_bIsSaveFlag)
	{
		 if(!SaveAll())
		 {
			 return;
		 }
		 m_bIsSaveFlag = false;
	}

	if (!bHasConnect)//zhouhj  2024.2.1 如果在CreateEngineClientWidget接口中进行了连接操作,此处不能再重复连接
	{
		pPpSttIotEngineClientWidgetMain->OpenPpSttCommConfigFile();
	//	nRet = pPpSttIotEngineClientWidgetMain->ConnectDevice();//在OpenPpSttCommConfigFile中已经进行了连接操作

		if (!pPpSttIotEngineClientWidgetMain->IsConnectSuccessful()/*nRet< 0*/)//此命令,需要等待实际的返回结果
		{
			UpdateConnectStateUI(0);
		}
	}
}

//串口类型表格的槽函数
void QSttCommCfgMainDlg::slot_ChangedSerialTable()
{
	m_bSerialTableSave = TRUE;
	m_bNetTableSave = FALSE;
	////SaveSerialTableProtolFile(m_strProproTemplatePath);

	m_bIsSaveFlag = true;

	//close();
}

//网络类型表格的槽函数
void QSttCommCfgMainDlg::slot_ChangedNetTable()
{
	m_bSerialTableSave = FALSE;
	m_bNetTableSave = TRUE;

	m_bIsSaveFlag = true;
	
	//修改IP或者端口后，现在的连接应该断开
	if(g_theTestCntrFrame->m_pEngineClientWidget != NULL)
	{
		if (g_theTestCntrFrame->m_pEngineClientWidget->IsConnectSuccessful())
		{
			QSttCommCfgDeviceWidget *pPpSttIotEngineClientWidgetMain = NULL;
			pPpSttIotEngineClientWidgetMain =  (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
			pPpSttIotEngineClientWidgetMain->m_pPpSttIotEngineClientInterface = this;
			if(pPpSttIotEngineClientWidgetMain->CloseCurrentConnect())
			{
				UpdateConnectStateUI(0);
			}
			else
			{
				CString strMsgText;
				strMsgText = _T("断开当前连接失败,请重新断开.");
				CXMessageBox::information(this, /*tr("提示")*/strMsgText, /*tr("断开当前连接失败,请重新断开")*/strMsgText);
			}
		}
	}
// 	QSttCommCfgDeviceWidget *pPpSttIotEngineClientWidgetMain = NULL;
// 
// 	if(m_nConnectStateIndex == 2)//zhouhj 2024.8.10 不能用m_nConnectStateIndex = 2标记是否已连接
// 	{
// 		//断开连接
// 		if(g_theTestCntrFrame->m_pEngineClientWidget != NULL)
// 		{
// 			pPpSttIotEngineClientWidgetMain =  (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
// 			pPpSttIotEngineClientWidgetMain->m_pPpSttIotEngineClientInterface = this;
// 			if(pPpSttIotEngineClientWidgetMain->CloseCurrentConnect())
// 			{
// 				UpdateConnectStateUI(0);
// 			}
// 			else
// 			{
// 				CString strMsgText;
// 				strMsgText = _T("断开当前连接失败,请重新断开.");
// 				CXMessageBox::information(this, /*tr("提示")*/strMsgText, /*tr("断开当前连接失败,请重新断开")*/strMsgText);
// 			}
// 		}
// 		return;
//	}

}

//首地址修改的槽函数
void QSttCommCfgMainDlg::slot_ChangedDevAddr(long lRes)
{
	if (m_pDevAddrDvmDevice != NULL)
	{
		CString strDevAddr;
		strDevAddr.Format("%ld",lRes);
		m_pDevAddrDvmDevice->SetDeviceAttribute(CString("DeviceAddr"), strDevAddr);
		m_pDevAddrDvmDevice->SaveXmlFile(m_strDevAddrPintPath, CDataMngrXmlRWKeys::g_pXmlKeys);

		m_bIsSaveFlag = true;
	}
	
}

bool QSttCommCfgMainDlg::SaveAll()
{
	QString pCrtProtTxt = m_pProproTemplate_ComboBox->currentText();
	if (!pCrtProtTxt.isEmpty())
	{
		CString ppXmlAllPath = pCrtProtTxt+CString(".ppxml");
		SavePpSttCommConfigFile(CFMDLG_COMBO_TYPE_PPXMLFILE, ppXmlAllPath, ppXmlAllPath);
	}
	QString pCrtPintTbTxt = m_pPointFile_ComboBox->currentText();
	if (!pCrtPintTbTxt.isEmpty())
	{
		CString strCrtPointTxt = pCrtPintTbTxt+CString(".xml");
		if (!pCrtProtTxt.isEmpty())
		{
			strCrtPointTxt = pCrtProtTxt + "/" + strCrtPointTxt;
		}
		SavePpSttCommConfigFile(CFMDLG_COMBO_TYPE_DVMFILE, strCrtPointTxt, strCrtPointTxt);
	}

	if (m_bSerialTableSave)
	{
		SaveSerialTableProtolFile(m_strProproTemplatePath);
		m_bSerialTableSave = false;
	}
	if (m_bNetTableSave)
	{
		SaveNetTableProtolFile(m_strProproTemplatePath);
		m_bNetTableSave = false;
	}
	
	if (m_pPpxmlFileData->GetCount() == 0)
	{
		return false;
	}
	CString strLocalIp,strSubnet;
	CDvmData *pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("tcp-client"));
	if(pDvmData)
	{
		CDvmValue *pVlSubnet = (CDvmValue*)pDvmData->FindByID("SubnetMask");
		if (pVlSubnet != NULL)
		{
			strSubnet = pVlSubnet->m_strValue;
		}
		CDvmValue *pVlLocIp = (CDvmValue*)pDvmData->FindByID("local-ip");
		if (pVlLocIp != NULL)
		{
			strLocalIp = pVlLocIp->m_strValue;
		}
		Global_SetLinuxDevIP(strLocalIp,strSubnet);
	}
	
	//udp-client
	CDvmValue *pDvmValueLocalIp = NULL;
	CString strSubMask = "255.255.255.0";
	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("udp-client"));
	if (pDvmData != NULL)
	{
		pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		if (pDvmValueLocalIp)
		{
			strLocalIp = pDvmValueLocalIp->m_strValue;
		}
		Global_SetLinuxDevIP(strLocalIp,  strSubMask);
	}
	

	//udp-server
	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("udp-server"));
	if (pDvmData != NULL)
	{
		pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		if (pDvmValueLocalIp)
		{
			strLocalIp = pDvmValueLocalIp->m_strValue;
			Global_SetLinuxDevIP(strLocalIp,  strSubMask);

		}
	}

	//tcp-server
	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("tcp-server"));
	if (pDvmData != NULL)
	{
		pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		if (pDvmValueLocalIp)
		{
			strLocalIp = pDvmValueLocalIp->m_strValue;
			Global_SetLinuxDevIP(strLocalIp,  strSubMask);
		}
	}


	SaveTcpclientDataToCfgXml();
	return true;
}



//确定按钮槽函数
void QSttCommCfgMainDlg::slot_OKClicked()
{
	//yuanting 2024-01-31
	if(!SaveAll())
	{
		return;
	}

	QPpSttIotEngineClientWidgetMain *pPpSttIotEngineClientWidgetMain = (QPpSttIotEngineClientWidgetMain*)g_theTestCntrFrame->m_pEngineClientWidget;
	if (pPpSttIotEngineClientWidgetMain != NULL)
	{
		pPpSttIotEngineClientWidgetMain->m_pPpSttIotEngineClientInterface = NULL;
	}

#ifdef _PSX_QT_WINDOWS_
	//chneling 20241212点确认需更新通讯参数,Ats_ConfigDevice告知自动测试
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");
	CPpSttCommConfig oCommConfig;
	if (oCommConfig.OpenCommConfigFile(strFile))
	{
		//chenling 20241212更新SmartGenWzd.wzdxml里的参数,为了兼容7.0新建测试
		g_theGbSmartGenWzd->m_strPpFile = oCommConfig.Get_PpxmlFile();
		g_theGbSmartGenWzd->m_strDvmFile = oCommConfig.Get_DvmFile();
		g_theGbSmartGenWzd->m_strLocalIP = oCommConfig.TcpClient_Get_LocalIP();
		g_theGbSmartGenWzd->m_strDevIP = oCommConfig.TcpClient_Get_RemoteIP();
		CString strPort = oCommConfig.TcpClient_Get_RemotePort();
		g_theGbSmartGenWzd->m_nDevPort= CString_To_long(strPort);
		g_theGbSmartGenWzd->SaveSmartGenWzdFile();

		if (g_pTheSttTestApp->m_pTestCtrlCntr != NULL)
		{
// 			CString strInstallPath = _P_GetInstallPath();
// 			CString strPpXmlFile,strDvmFile;
// 			strDvmFile = strInstallPath + oCommConfig.Get_DvmFile();
// 			strPpXmlFile = strInstallPath + oCommConfig.Get_PpxmlFile();
// 			oCommConfig.Set_DvmFile(strDvmFile);
// 			oCommConfig.Set_PpXmlFile(strPpXmlFile);
			g_pTheSttTestApp->m_pTestCtrlCntr->Ats_ConfigDevice(&oCommConfig);
		}
	}

#endif	
	close();

}

//取消按钮槽函数
void QSttCommCfgMainDlg::slot_CancelClicked()
{
	QPpSttIotEngineClientWidgetMain *pPpSttIotEngineClientWidgetMain = (QPpSttIotEngineClientWidgetMain*)g_theTestCntrFrame->m_pEngineClientWidget;
	if (pPpSttIotEngineClientWidgetMain != NULL)
	{
		pPpSttIotEngineClientWidgetMain->m_pPpSttIotEngineClientInterface = NULL;
	}

	close();
}

//解析规约文件Xml内容
void QSttCommCfgMainDlg::ParseProtolTmplXmlFile(CString upStrPpXmlFile)
{
	g_bHasTcpClient = false;
	g_hHsTcpServer = false;
	g_hHsUdpClient = false;
	g_hHsUdpServer = false;
	g_hHsSerial = false;

	CString strProtPath = Global_GetProtolTemplPath();
	CString strFile  = strProtPath + upStrPpXmlFile + CString(".ppxml");
	CExBaseList* pPpxmlFileData = Global_OpenPpxmlFile(strFile);
	if (pPpxmlFileData->GetCount() == 0)
	{
		return;
	}
	m_pPpxmlFileData = pPpxmlFileData;
	m_strProproTemplatePath = strFile;


	AddTab();

	CDvmData* pDvmData = NULL;

	//------DeviceAddr 点表文件中解析该值
	CString strPointTbPath = Global_GetPointTbFilePath();
	CString strPointFullPath = strPointTbPath + upStrPpXmlFile + CString("/") + m_pPointFile_ComboBox->currentText() + CString(".xml");
	if (::IsFileExist(strPointFullPath))
	{
		m_pDevAddrDvmDevice = new CDvmDevice;
		m_strDevAddrPintPath = strPointFullPath;
		m_pDevAddrDvmDevice->OpenXmlFile(strPointFullPath, CDataMngrXmlRWKeys::g_pXmlKeys);
		CDvmData* pDataAttr = (CDvmData*)m_pDevAddrDvmDevice->GetAttr(CString("DeviceAddr"));
		CString strDeviceAddrFind;
		if (pDataAttr != NULL)
		{
			if (g_bHasTcpClient)
			{
				pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("tcp-client"));
				if(pDvmData)
				{
					m_pTcpClientDevcieGrid->ShowDatas(pDvmData);
				}
			}

			if (g_hHsUdpClient)
			{
				pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("udp-client"));
				if(pDvmData)
				{
					m_pUdpClientDevcieGrid->ShowDatas(pDvmData);
				}
			}

			if (g_hHsTcpServer)
			{
				pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("tcp-server"));
				if(pDvmData)
				{
					m_pTcpServerDevcieGrid->ShowDatas(pDvmData);
				}
			}

			if (g_hHsUdpServer)
			{
				pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("udp-server"));
				if(pDvmData)
				{
					m_pUdpServerDevcieGrid->ShowDatas(pDvmData);
				}
			}

			if(g_hHsSerial)
			{
				pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("serials"));
				m_pSerialDevcieGrid->InitData(pDvmData);
			}
		}
	}
}

//解析TestCtrlCommConfig.xml配置文件
void QSttCommCfgMainDlg::OpenPpSttCommConfigFile(int iModType, CString& upStrPpXmlFile, CString& upStrDvmFile)
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");

	CPpSttCommConfig oCommConfig;
	if (!oCommConfig.OpenCommConfigFile(strFile) )
	{
		return;
	}
	//CString strPpXmlFile = oCommConfig.Get_PpxmlFile();

// 	CString strInstallPath = _P_GetInstallPath();
// 	CString strFilePath;
// 	strFilePath = _T("e-Protocol/Template/");
// 	strPpXmlFile = strInstallPath + strFilePath + strPpXmlFile;
// 	//绝对路径：
// 	CString strTemplPath = Global_GetProtolTemplPath();
// 	strPpXmlFile.replace(strTemplPath,"",Qt::CaseInsensitive);
// 
// 	CString strDvmFile = oCommConfig.Get_DvmFile();
// 	strFilePath = _T("e-Protocol/Library/");
// 	strDvmFile = strInstallPath + strFilePath+ strDvmFile;
// 	//绝对路径
// 	CString strPointFilePath = Global_GetPointTbFilePath();
// 	strDvmFile.replace(strPointFilePath,"",Qt::CaseInsensitive);

	if (iModType == CFMDLG_COMBO_TYPE_PPXMLFILE)
	{
		upStrPpXmlFile = oCommConfig.Get_PpxmlFile();
		/*upStrDvmFile = oCommConfig.Get_DvmFile();*/
	}
	else if (iModType == CFMDLG_COMBO_TYPE_DVMFILE)
	{
		//upStrPpXmlFile = oCommConfig.Get_PpxmlFile();
		upStrDvmFile = oCommConfig.Get_DvmFile();
	}

}

//保存TestCtrlCommConfig.xml配置文件
void QSttCommCfgMainDlg::SavePpSttCommConfigFile(int iModType, CString& upStrPpXmlFile, CString& upStrDvmFile)
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");

	CPpSttCommConfig oCommConfig;
	if (!oCommConfig.OpenCommConfigFile(strFile) )
	{
		return;
	}
// 	CString strPpXmlFile = oCommConfig.Get_PpxmlFile();
// 	CString strDvmFile = oCommConfig.Get_DvmFile();

	//改成相对路径
	//CString strFilePath = _P_GetInstallPath();

	if (iModType == CFMDLG_COMBO_TYPE_PPXMLFILE)
	{
		//绝对路径：
// 		CString strTemplPath = Global_GetProtolTemplPath();
// 		upStrPpXmlFile = strTemplPath + upStrPpXmlFile;
// 		
// 		strFilePath = upStrPpXmlFile.Mid(strFilePath.GetLength());
		oCommConfig.Set_PpXmlFile(upStrPpXmlFile);
		oCommConfig.SaveCommConfigFile(strFile);
	}
	else if (iModType == CFMDLG_COMBO_TYPE_DVMFILE)
	{
		//绝对路径：
// 		CString strPointFilePath = Global_GetPointTbFilePath();
// 		upStrDvmFile = strPointFilePath  + upStrDvmFile;;
// 		
// 		strFilePath = upStrDvmFile.Mid(strFilePath.GetLength());

		oCommConfig.Set_DvmFile(upStrDvmFile);
		oCommConfig.SaveCommConfigFile(strFile);
	}

}

//保存规约文件串口内容
void QSttCommCfgMainDlg::SaveSerialTableProtolFile(CString strPpXmlFile)
{
	if (m_pPpxmlFileData->GetCount() == 0)
	{
		return;
	}
	CDvmData *pDvmData = NULL;
	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("serial"));
	if (pDvmData)
	{
		return;
	}

	CDvmValue *pSerialValPortNum = (CDvmValue*)pDvmData->FindByID(CString("port_number"));
	CString valuePortNo = pSerialValPortNum->m_strValue;
	CDvmValue *pSerialValBaudRate = (CDvmValue*)pDvmData->FindByID(CString("baud-rate"));
	CString valueBaudRate = pSerialValBaudRate->m_strValue;
	CDvmValue *pSerialValByteSize = (CDvmValue*)pDvmData->FindByID(CString("byte-size"));
	CString valueByteSize = pSerialValByteSize->m_strValue;
	CDvmValue *pSerialValStopBit = (CDvmValue*)pDvmData->FindByID(CString("stop-bit"));
	CString valueStopBit = pSerialValStopBit->m_strValue;
	CDvmValue *pSerialValParity = (CDvmValue*)pDvmData->FindByID(CString("parity"));
	CString valueParity = pSerialValParity->m_strValue;

	CXmlRWDocBase* pXmlDocPtr = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	if (pXmlDocPtr == NULL)
	{
		return;
	}
	try
	{
		if ( !xml_OpenFile(pXmlDocPtr, strPpXmlFile) )
		{
			delete pXmlDocPtr;
			pXmlDocPtr = NULL;
			return;
		}
	}
	catch (...)
	{
		delete pXmlDocPtr;
		pXmlDocPtr = NULL;
		return;
	}
	CXmlRWNodeBase*  pXmlRootptr = pXmlDocPtr->GetDocNode();
	if (pXmlRootptr == NULL)
	{
		return;
	}
	CXmlRWNodeBase* oNodeRoot = pXmlRootptr->GetChildNode(CString("pp-template"));
	if (oNodeRoot == NULL)
	{
		return;
	}
	CXmlRWNodeBase* oNodeComCfg = oNodeRoot->GetChildNode(CString("comm-config"));
	if (oNodeComCfg == NULL)
	{
		return;
	}
	//CXmlRWNodeBase* oNodeNet = oNodeComCfg->GetChildNode(CString("net"));
	CXmlRWNodeBase* oNodeSerial = oNodeComCfg->GetChildNode(CString("serial"));
	if (oNodeSerial != NULL) 
	{
		//<serial port_number="2" baud-rate="9600" byte-size="8" stop-bit="1" parity="0">
		//CString valuePortNo;
		oNodeSerial->xml_SetAttributeValue(L"port_number", valuePortNo);

		//CString valueBaudRate;
		oNodeSerial->xml_SetAttributeValue(L"baud-rate", valueBaudRate);

		//CString valueByteSize;
		oNodeSerial->xml_SetAttributeValue(L"byte-size", valueByteSize);

		//CString valueStopBit;
		oNodeSerial->xml_SetAttributeValue(L"stop-bit", valueStopBit);

		//CString valueParity;
		oNodeSerial->xml_SetAttributeValue(L"parity", valueParity);

	}

	pXmlDocPtr->SaveXml(strPpXmlFile);

	delete pXmlDocPtr;
	pXmlDocPtr = NULL;
}

//保存规约文件网口内容
void QSttCommCfgMainDlg::SaveNetTableProtolFile(CString strPpXmlFile)
{
	if (m_pPpxmlFileData->GetCount() == 0)
	{
		return;
	}
	
	CXmlRWDocBase* pXmlDocPtr = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);//CXmlRWFactory::CreateXmlRWDoc(_PUGI_XML_TYPE_);
 	if (pXmlDocPtr == NULL)
 	{
 		//return NULL;
 	}
 	try
 	{
 		if ( !xml_OpenFile(pXmlDocPtr, strPpXmlFile) )//调用XML2Interface.h中的全局函数，加载资源，入口返回给oDoc；
 		{
 			delete pXmlDocPtr;
 			pXmlDocPtr = NULL;
 			//return NULL;
 		}
 	}
 	catch (...)
 	{
 		delete pXmlDocPtr;
 		pXmlDocPtr = NULL;
 		//return NULL;
 	}
 	CXmlRWNodeBase*  pXmlRootptr = pXmlDocPtr->GetDocNode();
 	if (pXmlRootptr == NULL)
 	{
 		//return NULL;
 	}
 	CXmlRWNodeBase* oNodeRoot = pXmlRootptr->GetChildNode(CString("pp-template"));
 	if (oNodeRoot == NULL)
 	{
 		//return NULL;
 	}
 	CXmlRWNodeBase* oNodeComCfg = oNodeRoot->GetChildNode(CString("comm-config"));
 	if (oNodeComCfg == NULL)
 	{
 		//return NULL;
 	}
 	CXmlRWNodeBase* oNodeNet = oNodeComCfg->GetChildNode(CString("net"));

	CDvmData *pDvmData = NULL;
	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("tcp-client"));
	if (pDvmData)
	{
		CDvmValue *pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
 		if (pDvmValueLocalIp == NULL)
 		{
 			return;
 		}
 		CString valueLocalIp = pDvmValueLocalIp->m_strValue;
 		CDvmValue *pDvmValueLocalPort = (CDvmValue*)pDvmData->FindByID(CString("local-port"));
 		CString valueLocalPort = pDvmValueLocalPort->m_strValue;
 		CDvmValue *pDvmValueRemoteIp= (CDvmValue*)pDvmData->FindByID(CString("remote-ip"));
 		CString valueRemoteIp = pDvmValueRemoteIp->m_strValue;
 		CDvmValue *pDvmValueRemotePort= (CDvmValue*)pDvmData->FindByID(CString("remote-port"));
 		CString valueRemotePort = pDvmValueRemotePort->m_strValue;
	 
	 	
 		if (oNodeNet != NULL)
 		{
 			CXmlRWNodeBase* oNodeTcpClient = oNodeNet->GetChildNode(CString("tcp-client"));
 			if ( oNodeTcpClient != NULL )
 			{
 				oNodeTcpClient->xml_SetAttributeValue(L"local-ip", valueLocalIp);
 				oNodeTcpClient->xml_SetAttributeValue(L"local-port", valueLocalPort);
 				CString valueClientIp;
 				oNodeTcpClient->xml_SetAttributeValue(L"remote-ip", valueRemoteIp);
 				oNodeTcpClient->xml_SetAttributeValue(L"remote-port", valueRemotePort);	
 			}
 		}
	}

	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("udp-client"));
	if (pDvmData)
	{
		CDvmValue *pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		CDvmValue *pDvmValueLocalPort = (CDvmValue*)pDvmData->FindByID(CString("local-port"));
		CDvmValue *pDvmValueRemoteIp= (CDvmValue*)pDvmData->FindByID(CString("remote-ip"));
		CDvmValue *pDvmValueRemotePort= (CDvmValue*)pDvmData->FindByID(CString("remote-port"));
		CDvmValue *pDvmValuebroadcast= (CDvmValue*)pDvmData->FindByID(CString("use-broadcast"));
		CDvmValue *pDvmValuemulticastip= (CDvmValue*)pDvmData->FindByID(CString("multicast-ip"));


		if (oNodeNet != NULL)
		{
			CXmlRWNodeBase* oNodeUdpClient = oNodeNet->GetChildNode(CString("udp-client"));
			if ( oNodeUdpClient != NULL )
			{
				oNodeUdpClient->xml_SetAttributeValue(L"local-ip", pDvmValueLocalIp->m_strValue);
				oNodeUdpClient->xml_SetAttributeValue(L"local-port", pDvmValueLocalPort->m_strValue);
				oNodeUdpClient->xml_SetAttributeValue(L"remote-ip", pDvmValueRemoteIp->m_strValue);
				oNodeUdpClient->xml_SetAttributeValue(L"remote-port", pDvmValueRemotePort->m_strValue);	
				oNodeUdpClient->xml_SetAttributeValue(L"use-broadcast", pDvmValuebroadcast->m_strValue);
				oNodeUdpClient->xml_SetAttributeValue(L"multicast-ip", pDvmValuemulticastip->m_strValue);	
			}
		}
	}


	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("tcp-server"));
	if (pDvmData)
	{
		CDvmValue *pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		CDvmValue *pDvmValueLocalPort = (CDvmValue*)pDvmData->FindByID(CString("local-port"));

		if (oNodeNet != NULL)
		{
			CXmlRWNodeBase* oNodeTcpServer = oNodeNet->GetChildNode(CString("tcp-server"));
			if ( oNodeTcpServer != NULL )
			{
				oNodeTcpServer->xml_SetAttributeValue(L"local-ip", pDvmValueLocalIp->m_strValue);
				oNodeTcpServer->xml_SetAttributeValue(L"local-port", pDvmValueLocalPort->m_strValue);
			}
		}
	}

	//udp-server
	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("udp-server"));
	if (pDvmData)
	{
		CDvmValue *pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		CDvmValue *pDvmValueLocalPort = (CDvmValue*)pDvmData->FindByID(CString("local-port"));
		CDvmValue *pDvmValuebroadcast= (CDvmValue*)pDvmData->FindByID(CString("use-broadcast"));
		CDvmValue *pDvmValuemulticastip= (CDvmValue*)pDvmData->FindByID(CString("multicast-ip"));
		if (oNodeNet != NULL)
		{
			CXmlRWNodeBase* oNodeUdpServer = oNodeNet->GetChildNode(CString("udp-server"));
			if ( oNodeUdpServer != NULL )
			{
				oNodeUdpServer->xml_SetAttributeValue(L"local-ip", pDvmValueLocalIp->m_strValue);
				oNodeUdpServer->xml_SetAttributeValue(L"local-port", pDvmValueLocalPort->m_strValue);
				oNodeUdpServer->xml_SetAttributeValue(L"use-broadcast", pDvmValuebroadcast->m_strValue);
				oNodeUdpServer->xml_SetAttributeValue(L"multicast-ip", pDvmValuemulticastip->m_strValue);	
			}
		}
	}

 	pXmlDocPtr->SaveXml(strPpXmlFile);
 	delete pXmlDocPtr;
 	pXmlDocPtr = NULL;
}

//保存规约文件网口的TcpClient数据
void QSttCommCfgMainDlg::SaveTcpclientDataToCfgXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");

	CPpSttCommConfig oCommConfig;
	if (!oCommConfig.OpenCommConfigFile(strFile) )
	{
		return;
	}
	CDataGroup* pDataGroup = (CDataGroup*)oCommConfig.FindByID(_T("comm-config"));
	pDataGroup->DeleteAll();

	CDvmData *pDvmData = NULL;
	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("tcp-client"));
	if (pDvmData)
	{
		CDvmValue *pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		CDvmValue *pDvmValueLocalPort = (CDvmValue*)pDvmData->FindByID(CString("local-port"));
		CDvmValue *pDvmValueRemoteIp= (CDvmValue*)pDvmData->FindByID(CString("remote-ip"));
		CDvmValue *pDvmValueRemotePort= (CDvmValue*)pDvmData->FindByID(CString("remote-port"));
		
		CDvmData* pTcpClientDvm = oCommConfig.Get_TcpClient();
		if (pTcpClientDvm == NULL)
		{
			oCommConfig.Add_TcpClient();
		}
		oCommConfig.TcpClient_Set_RemotePort(pDvmValueRemotePort->m_strValue.toInt());
		oCommConfig.TcpClient_Set_RemoteIP(pDvmValueRemoteIp->m_strValue);
		oCommConfig.TcpClient_Set_LocalIP(pDvmValueLocalIp->m_strValue);
		oCommConfig.TcpClient_Set_LocalPort(pDvmValueLocalPort->m_strValue.toInt());
	}

	
	
	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("udp-client"));
	if (pDvmData)
	{
		CDvmValue *pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		CDvmValue *pDvmValueLocalPort = (CDvmValue*)pDvmData->FindByID(CString("local-port"));
		CDvmValue *pDvmValueRemoteIp= (CDvmValue*)pDvmData->FindByID(CString("remote-ip"));
		CDvmValue *pDvmValueRemotePort= (CDvmValue*)pDvmData->FindByID(CString("remote-port"));
		CDvmValue *pDvmValueUseBroadcast= (CDvmValue*)pDvmData->FindByID(CString("use-broadcast"));
		CDvmValue *pDvmValueMulticastIp= (CDvmValue*)pDvmData->FindByID(CString("multicast-ip"));

		CDvmData* pUdpClientDvm = oCommConfig.Get_UdpClient();
		if (pUdpClientDvm == NULL)
		{
			oCommConfig.Add_UdpClient();
		}
		oCommConfig.UdpClient_Set_RemotePort(pDvmValueRemotePort->m_strValue.toInt());
		oCommConfig.UdpClient_Set_RemoteIP(pDvmValueRemoteIp->m_strValue);
		oCommConfig.UdpClient_Set_LocalIP(pDvmValueLocalIp->m_strValue);
		oCommConfig.UdpClient_Set_LocalPort(pDvmValueLocalPort->m_strValue.toInt());
		oCommConfig.UdpClient_Set_MuticastIP(pDvmValueMulticastIp->m_strValue);
		oCommConfig.UdpClient_Set_Broadcast(pDvmValueUseBroadcast->m_strValue.toInt());
	}


	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("tcp-server"));
	if (pDvmData)
	{
		CDvmValue *pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		CDvmValue *pDvmValueLocalPort = (CDvmValue*)pDvmData->FindByID(CString("local-port"));

		CDvmData* pTcpServerDvm = oCommConfig.Get_TcpServer();
		if (pTcpServerDvm == NULL)
		{
			oCommConfig.Add_TcpServer();
		}
		oCommConfig.TcpServer_Set_LocalIP(pDvmValueLocalIp->m_strValue);
		oCommConfig.TcpServer_Set_LocalPort(pDvmValueLocalPort->m_strValue.toInt());
	}

	pDvmData = (CDvmData*)m_pPpxmlFileData->FindByID(CString("udp-server"));
	if (pDvmData)
	{
		CDvmValue *pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		CDvmValue *pDvmValueLocalPort = (CDvmValue*)pDvmData->FindByID(CString("local-port"));
		CDvmValue *pDvmValueUseBroadcast= (CDvmValue*)pDvmData->FindByID(CString("use-broadcast"));
		CDvmValue *pDvmValueMulticastIp= (CDvmValue*)pDvmData->FindByID(CString("multicast-ip"));

		CDvmData* pTcpServerDvm = oCommConfig.Get_UdpServer();
		if (pTcpServerDvm == NULL)
		{
			oCommConfig.Add_UdpServer();
		}
		oCommConfig.UdpServer_Set_LocalIP(pDvmValueLocalIp->m_strValue);
		oCommConfig.UdpServer_Set_LocalPort(pDvmValueLocalPort->m_strValue.toInt());
		oCommConfig.UdpServer_Set_MuticastIP(pDvmValueMulticastIp->m_strValue);
		oCommConfig.UdpServer_Set_Broadcast(pDvmValueUseBroadcast->m_strValue.toInt());
	}

	oCommConfig.SaveCommConfigFile(strFile);

}
