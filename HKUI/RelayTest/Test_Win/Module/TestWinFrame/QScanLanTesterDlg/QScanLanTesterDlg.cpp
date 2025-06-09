#include "QScanLanTesterDlg.h"
#include <QDirIterator>
#include <iphlpapi.h>
#include <QTextCursor>
#include <QMessageBox>
#include "../../../../Module/SttCmd/SttParas.h"
#include "../../../../Module/SttGlobalDef.h"
#include "../../../../../Module/System/TickCount32.h"
#include "QModifyIPAddrDlg.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "..\ReportView\XLangResource_PowerTestWin.h"

QScanLanTesterDlg::QScanLanTesterDlg(QWidget *parent,bool bUseScanLan)
	: QDialog(parent)
{
	setWindowIcon (QIcon(":/image/set.png"));
	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(/*tr("扫描局域网测试仪")*/g_sLangTxt_Native_LST);
	m_pSttMulticastClientSocket = NULL;
	m_pScan_PushButton = NULL;
	m_pModifyTesterIP_PushButton = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_nTimerID = -1;
	m_pIpAdapterInfo = NULL;
	m_bScan = FALSE;
	m_strSelNetDesc = _T("");
	m_pCurSelData = NULL;
	m_pLogString_TextEdit = NULL;
	m_hDevInfo = INVALID_HANDLE_VALUE;
	m_strNetCardLocalIP = "";
	m_bUseScanLan = bUseScanLan;
}

QScanLanTesterDlg::~QScanLanTesterDlg()
{
	ReleaseOnClose();
	SetupDiDestroyDeviceInfoList(m_hDevInfo);
}

void QScanLanTesterDlg::initUI()
{
	ReleaseUI();
	resize(600, 400);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

 	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
 	sizePolicy.setHorizontalStretch(30);
 	sizePolicy.setVerticalStretch(30);

	m_pAllVLayout = new QVBoxLayout(this);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pHBoxLayout1 = new QHBoxLayout(this);
	m_pNetCardSel_Label = new QLabel(this);
	m_pNetCardSel_Label->setText(/*tr("网卡选择:")*/g_sLangTxt_Native_NetAdptSelect+":");
	m_pHBoxLayout1->addWidget(m_pNetCardSel_Label);
	m_pNetCardSel_ComboBox = new QComboBox(this);
	m_pNetCardSel_ComboBox->setMinimumWidth(150);
	m_pHBoxLayout1->addWidget(m_pNetCardSel_ComboBox);
	m_pHBoxLayout1->addStretch();
	m_pLocalIP_Label = new QLabel(this);
	m_pLocalIP_Label->setText(/*tr("本地网卡IP:")*/g_sLangTxt_Gradient_LocalNICIP+":");
	m_pHBoxLayout1->addWidget(m_pLocalIP_Label);
	m_pLocalIP_ComboBox =  new QComboBox(this);
	m_pHBoxLayout1->addWidget(m_pLocalIP_ComboBox);
// 	m_pLocalIP_LineEdit = new QLineEdit(this);
// 	m_pLocalIP_LineEdit->setEnabled(false);
// 	m_pHBoxLayout1->addWidget(m_pLocalIP_LineEdit);
	m_pAllVLayout->addLayout(m_pHBoxLayout1);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pScanLanTesterGrid = new CScanLanTesterGrid(this);
	m_pScanLanTesterGrid->InitGrid();
	m_pAllVLayout->addWidget(m_pScanLanTesterGrid);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pLogString_TextEdit = new QTextEdit(this);
	m_pLogString_TextEdit->setStyleSheet("color:red");//文本颜色
	m_pLogString_TextEdit->setReadOnly(true);
	m_pLogString_TextEdit->setFixedHeight(50);
	m_pAllVLayout->addWidget(m_pLogString_TextEdit);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pScan_PushButton = new QPushButton(this);
	m_pScan_PushButton->setText(/*tr("扫描")*/g_sLangTxt_scan);
	m_pScan_PushButton->setIcon (QPixmap( ":/image/clear.png"));

	m_pModifyTesterIP_PushButton = new QPushButton(this);
	m_pModifyTesterIP_PushButton->setText(/*tr("修改测试仪IP")*/g_sLangTxt_Native_ModTesterIP);
	m_pModifyTesterIP_PushButton->setEnabled(false);
//	m_pModifyTesterIP_PushButton->setIcon (QPixmap( ":/image/set.png"));

	m_pServerIP_Label = new QLabel(this);
	m_pServerIP_Label->setText(/*tr("IP地址:")*/g_sLangTxt_Native_IPAddr+":");

	m_pServerIP_LineEdit = new QLineEdit(this);
	
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(/*tr("确定")*/g_sLangTxt_OK);
	m_pOK_PushButton->setIcon (QPixmap( ":/image/check.png"));

	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(/*tr("取消")*/g_sLangTxt_Cancel);
	m_pCancel_PushButton->setIcon (QPixmap( ":/image/Cancel.png"));

	m_pHBoxLayout2 = new QHBoxLayout(this);
	m_pHBoxLayout2->addWidget(m_pScan_PushButton);
	m_pHBoxLayout2->addWidget(m_pModifyTesterIP_PushButton);
	m_pHBoxLayout2->addWidget(m_pServerIP_Label);
	m_pHBoxLayout2->addWidget(m_pServerIP_LineEdit);
	m_pHBoxLayout2->addStretch();
	m_pHBoxLayout2->addWidget(m_pOK_PushButton);
	m_pHBoxLayout2->addSpacing(10);
	m_pHBoxLayout2->addWidget(m_pCancel_PushButton);
	m_pHBoxLayout2->setDirection(QBoxLayout::LeftToRight);
	m_pAllVLayout->addLayout(m_pHBoxLayout2);
	InitDatas();

	if (m_bUseScanLan)
	{
		InitLocalAdapters();
	}

	this->setLayout(m_pAllVLayout);

	connect(m_pScan_PushButton, SIGNAL(clicked()), this, SLOT(slot_ScanClicked()));
 	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
 	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pModifyTesterIP_PushButton, SIGNAL(clicked()), this, SLOT(slot_ModifyTesterIP_Clicked()));
	connect(m_pNetCardSel_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeNetCardSel(int)));
	connect(m_pLocalIP_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeLocalIPAddrSel(int)));
//	InitEnableNetDevices();
}

void QScanLanTesterDlg::ReleaseUI()
{

}

void QScanLanTesterDlg::InitDatas()
{
	m_oSttTestAppCfg.SttOpen(m_oSttTestAppCfg.GetSttCfgFile());
	m_pServerIP_LineEdit->setText(m_oSttTestAppCfg.GetTestAppIP());
	m_pScanLanTesterGrid->AttachDataViewOptrInterface(this);
}

BOOL QScanLanTesterDlg::ConnectMulticastServer()
{
	FreeMulticastSocket();
	m_pSttMulticastClientSocket = new CSttMulticastClientSocket;

	if(!m_pSttMulticastClientSocket->Create(m_oSttTestAppCfg.GetMulticastIP()
		,m_oSttTestAppCfg.GetMulticastPort()
		,m_oSttTestAppCfg.GetLocalIP()
		,m_oSttTestAppCfg.GetMulticastPort()))
	{
		return FALSE;
	}

	return TRUE;
}

CString QScanLanTesterDlg::GetNetCardDesc()
{
	if (m_pIpAdapterInfo == NULL)
	{
		return "";
	}

	PIP_ADAPTER_INFO pIterater = m_pIpAdapterInfo;
	PIP_ADDR_STRING pCurIpAddr;
	CString strLocalIP;

	if (m_strNetCardLocalIP.IsEmpty())
	{
		strLocalIP = m_oSttTestAppCfg.GetLocalIP();
	} 
	else
	{
		strLocalIP = m_strNetCardLocalIP;
	}
	
	while(pIterater)
	{
		pCurIpAddr = &pIterater->IpAddressList;

		while(pCurIpAddr != NULL)
		{
			if (strcmp(pCurIpAddr->IpAddress.String,strLocalIP.GetString())  == 0)
			{
				return pIterater->Description;
			}

			pCurIpAddr = pCurIpAddr->Next;
		}

		pIterater = pIterater->Next;
	}

	AddRecord(/*tr("获取本地IP地址失败,当前值为空.")*/g_sLangTxt_Native_FailToRetrieveNetAddr);
	return "";
}

void QScanLanTesterDlg::slot_ScanClicked()
{
	disconnect(m_pScan_PushButton, SIGNAL(clicked()), this, SLOT(slot_ScanClicked()));
	m_pScan_PushButton->setEnabled(false);

	if(!m_bScan)
	{
		CString strNetCardDesc;
		strNetCardDesc = GetNetCardDesc();
//		EnableNetDevices(strNetCardDesc,DICS_DISABLE);

		if (!ConnectMulticastServer())
		{
//			connect(m_pScan_PushButton, SIGNAL(clicked()), this, SLOT(slot_ScanClicked()));
			AddRecord(/*tr("创建组播链接失败,无法进行扫描,5s后自动重连.")*/g_sLangTxt_automatic);
//			m_pScan_PushButton->setEnabled(true);
			FreeMulticastSocket();

			if (m_nTimerID != -1)
			{
				killTimer(m_nTimerID);
			}

			m_nTimerID = startTimer(5000);
			return;
		}

		m_pModifyTesterIP_PushButton->setEnabled(false);
//		m_pOK_PushButton->setEnabled(false);
		m_oGridDatas.DeleteAll();
		m_pCurSelData = NULL;
		m_pScanLanTesterGrid->ShowDatas(&m_oGridDatas);
		m_pScan_PushButton->setText(/*tr("停止扫描")*/g_sLangTxt_stopscan);
		m_pSttMulticastClientSocket->AttatchSttMulticastMsgViewInterface(this);

		if (m_nTimerID != -1)
		{
			killTimer(m_nTimerID);
		}

		m_nTimerID = startTimer(2000);
		m_bScan = TRUE;
	}
	else
	{
		OnStopScan();
		m_bScan = FALSE;
	}

	m_pScan_PushButton->setEnabled(true);
	connect(m_pScan_PushButton, SIGNAL(clicked()), this, SLOT(slot_ScanClicked()));
}

void QScanLanTesterDlg::InitEnableNetDevices()
{
	m_hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);

	if (INVALID_HANDLE_VALUE == m_hDevInfo)
	{
		AddRecord(/*tr("取得设备信息失败")*/g_sLangTxt_Native_FailToRetDevInfo);
		return;
	}

	SP_DEVINFO_DATA DeviceInfoData = { sizeof(SP_DEVINFO_DATA) };
	LPOLESTR guid;
	QString strDevName;
	wchar_t wszDevName[128];
	char *pszDevName = NULL;
	wchar_t wszInstanceId[128];
	char *pszInstanceId = NULL;
	CString strNetCardDesc;
	strNetCardDesc = GetNetCardDesc();
	m_oDevNetsInfo.m_nNum = 0;

	for (int nDevIndex = 0; SetupDiEnumDeviceInfo(m_hDevInfo, nDevIndex, &m_oDevNetsInfo.m_oDevInforData[m_oDevNetsInfo.m_nNum]); nDevIndex++)
	{
		StringFromCLSID(m_oDevNetsInfo.m_oDevInforData[m_oDevNetsInfo.m_nNum].ClassGuid, &guid);
		SetupDiClassNameFromGuid(&m_oDevNetsInfo.m_oDevInforData[m_oDevNetsInfo.m_nNum].ClassGuid, wszDevName, 128, NULL);
		str_wchar_to_char(&pszDevName,wszDevName);

		TCHAR szDevDesc[MAX_PATH] = { 0 };

		SetupDiGetDeviceRegistryProperty(m_hDevInfo, &m_oDevNetsInfo.m_oDevInforData[m_oDevNetsInfo.m_nNum], SPDRP_FRIENDLYNAME, NULL, (PBYTE)szDevDesc, MAX_PATH - 1, NULL);         
		CString strDevDesc = szDevDesc;

		if (strcmp(pszDevName, "Net") == 0)//需要包含Net
		{
			SetupDiGetDeviceInstanceId(m_hDevInfo, &m_oDevNetsInfo.m_oDevInforData[m_oDevNetsInfo.m_nNum], wszInstanceId, 128, NULL);
			str_wchar_to_char(&pszInstanceId,wszInstanceId);

			if (!strncmp(pszInstanceId, "PCI", 3) || !strncmp(pszInstanceId, "BTH", 3) || !strncmp(pszInstanceId, "ROOT\\VMWARE\\",12) || !strncmp(pszInstanceId, "ROOT\\NET\\",9))
			{
				m_oDevNetsInfo.m_strNetName[m_oDevNetsInfo.m_nNum] = strDevDesc;
				m_oDevNetsInfo.m_oParams[m_oDevNetsInfo.m_nNum].ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
				m_oDevNetsInfo.m_oParams[m_oDevNetsInfo.m_nNum].Scope = DICS_FLAG_CONFIGSPECIFIC;
				m_oDevNetsInfo.m_oParams[m_oDevNetsInfo.m_nNum].StateChange = DICS_DISABLE;

				if (strcmp(strNetCardDesc.GetString(),strDevDesc.GetString()) == 0)
				{
					m_oDevNetsInfo.m_oParams[m_oDevNetsInfo.m_nNum].StateChange = DICS_ENABLE;//当前网卡需要使能
				}

				m_oDevNetsInfo.m_oParams[m_oDevNetsInfo.m_nNum].HwProfile = 0;
				SetupDiSetClassInstallParams(m_hDevInfo, &m_oDevNetsInfo.m_oDevInforData[m_oDevNetsInfo.m_nNum],
					(SP_CLASSINSTALL_HEADER*)&m_oDevNetsInfo.m_oParams[m_oDevNetsInfo.m_nNum], sizeof(SP_PROPCHANGE_PARAMS));
				SetupDiChangeState(m_hDevInfo, &m_oDevNetsInfo.m_oDevInforData[m_oDevNetsInfo.m_nNum]);
				m_oDevNetsInfo.m_nNum++;
			}

			delete pszInstanceId;
		}

		delete pszDevName;
		pszDevName = NULL;
		CoTaskMemFree(guid);
	}

//	SetupDiDestroyDeviceInfoList(m_hDevInfo);
	Sleep(200);
}

void QScanLanTesterDlg::EnableNetDevices(const CString&strExcludeNet,DWORD dwEnable)
{
// 	HDEVINFO hDevInfo = INVALID_HANDLE_VALUE;
// 	hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);

	if (INVALID_HANDLE_VALUE == m_hDevInfo)
	{
		AddRecord(/*tr("取得设备信息失败")*/g_sLangTxt_Native_FailToRetDevInfo);
		return;
	}

	long nSetNum = 0;

	for (int nIndex = 0;nIndex<m_oDevNetsInfo.m_nNum;nIndex++)
	{
		if (m_oDevNetsInfo.m_strNetName[nIndex] == strExcludeNet)
		{
			if (m_oDevNetsInfo.m_oParams[nIndex].StateChange != DICS_ENABLE)
			{
				nSetNum++;
				m_oDevNetsInfo.m_oParams[nIndex].StateChange = DICS_ENABLE;
				SetupDiSetClassInstallParams(m_hDevInfo, &m_oDevNetsInfo.m_oDevInforData[nIndex],
					(SP_CLASSINSTALL_HEADER*)&m_oDevNetsInfo.m_oParams[nIndex], sizeof(SP_PROPCHANGE_PARAMS));
				SetupDiChangeState(m_hDevInfo, &m_oDevNetsInfo.m_oDevInforData[nIndex]);
			}

			continue;
		}

		if (m_oDevNetsInfo.m_oParams[nIndex].StateChange != dwEnable)
		{
			m_oDevNetsInfo.m_oParams[nIndex].StateChange = dwEnable;
			SetupDiSetClassInstallParams(m_hDevInfo, &m_oDevNetsInfo.m_oDevInforData[nIndex],
				(SP_CLASSINSTALL_HEADER*)&m_oDevNetsInfo.m_oParams[nIndex], sizeof(SP_PROPCHANGE_PARAMS));
			SetupDiChangeState(m_hDevInfo, &m_oDevNetsInfo.m_oDevInforData[nIndex]);
			nSetNum++;
		}
	}

	if (nSetNum>0)
	{
//		SetupDiDestroyDeviceInfoList(m_hDevInfo);
	}

	if(dwEnable == DICS_ENABLE)
	{
		Sleep(200);
	}
	else
	{
		Sleep(100);
	}
}

void QScanLanTesterDlg::slot_OKClicked()
{
	CString strSelIP;
	strSelIP = m_pServerIP_LineEdit->text();

	if (!ValidCurrSelIP(strSelIP))
	{
		CString strMsg;
		strMsg = QString(/*tr("测试仪IP地址(%1)与当前网卡IP不在同一网段,是否修改?")*/g_sLangTxt_Native_AddrNotInSameSubnet.arg(strSelIP));
		int nRet = QMessageBox::question(this, /*tr("提示")*/g_sLangTxt_Message,strMsg,/*tr("是")*/g_sLangTxt_State_Yes,/*tr("否")*/g_sLangTxt_State_No);

		if (nRet == 0)
		{
			slot_ModifyTesterIP_Clicked();
			return;
		}
	}

	m_pOK_PushButton->setEnabled(false);

	if (m_nTimerID != -1)
	{
		killTimer(m_nTimerID);
	}

	if (m_pIpAdapterInfo)
	{
		delete []m_pIpAdapterInfo;
		m_pIpAdapterInfo =NULL;
	}

	m_oSttTestAppCfg.SetTestAppIP(m_pServerIP_LineEdit->text());
	QString strSavePath = m_oSttTestAppCfg.GetSttCfgFile();
	m_oSttTestAppCfg.SttSave(strSavePath);


	//20240408 suyang  需要更新一下TestAppConfigSttAtsWin.xml，以防合并单元连接不上
	CSttTestAppCfg oSttTestAppCfg;

	CString strPath,strFile,strAtsFile;

	strPath =  _P_GetInstallPath();//zhouhj 2024.4.22 修改IP地址后,保存到该文件夹下,供自动测试使用
	strAtsFile  = strPath + _T("e-Report/Config/TestAppConfig.xml");

	if (oSttTestAppCfg.SttOpen(strAtsFile))
	{
		CString strTestAppIP = oSttTestAppCfg.GetTestAppIP();

		if (strTestAppIP != m_oSttTestAppCfg.GetTestAppIP())
		{
			oSttTestAppCfg.SetTestAppIP(m_pServerIP_LineEdit->text());
			oSttTestAppCfg.SttSave(strAtsFile);
		}
	}

	emit sig_TesterIP_Changed();
//	ReleaseOnClose();
	close();
}


void QScanLanTesterDlg::slot_CancelClicked()
{
	if (m_pIpAdapterInfo)
	{
		delete []m_pIpAdapterInfo;
		m_pIpAdapterInfo =NULL;
	}

//	ReleaseOnClose();
	close();
}

void QScanLanTesterDlg::ReleaseOnClose()
{
//	if (m_pSttMulticastClientSocket != NULL)
	{
//		EnableNetDevices(_T(""),DICS_ENABLE);
	}

	FreeMulticastSocket();
}

void QScanLanTesterDlg::slot_ModifyTesterIP_Clicked()
{
	if (m_pCurSelData == NULL)
	{
		return;
	}

	if (m_pSttMulticastClientSocket == NULL)
	{
		if (!ConnectMulticastServer())
		{
			return;
		}
	}

	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(m_pCurSelData, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(m_pCurSelData, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);

	CDataGroup *pGroupIP = (CDataGroup *)m_pCurSelData->FindByID(STT_SYS_DATA_ID_DeviceIP);
	CString strIP = m_oSttTestAppCfg.GetTestAppIP();

	if (pGroupIP != NULL)
	{
		stt_GetDataValueByID(pGroupIP, STT_SYS_DATA_ID_IP, strIP);
	}

	QModifyIPAddrDlg oModifyIP_Dlg;
	oModifyIP_Dlg.InitParas(strModel,strSN,strIP);
	connect(&oModifyIP_Dlg, SIGNAL(sig_ModifyTesterIP_OK(QString &,const QString &)), this, SLOT(slot_ModifyTesterIP(QString &,const QString &)));
	oModifyIP_Dlg.exec();
	disconnect(&oModifyIP_Dlg, SIGNAL(sig_ModifyTesterIP_OK(QString &,const QString &)), this, SLOT(slot_ModifyTesterIP(QString &,const QString &)));
}

BOOL HasValidIP(QList<QNetworkAddressEntry> &oIPsList)
{
	if (oIPsList.size() <= 0)
	{
		return FALSE;
	}

	QNetworkAddressEntry oCurIP;
	CString strLocalIP = "";

	for (int nIP_index = 0;nIP_index<oIPsList.size();nIP_index++)
	{
		oCurIP = oIPsList.at(nIP_index);
		strLocalIP = oCurIP.ip().toString();

		if ((strLocalIP.Find(("."))>0)&&(strLocalIP != "127.0.0.1"))
		{
			break;
		}

		strLocalIP = "";
	}

	if (strLocalIP.IsEmpty())
	{
		return FALSE;
	}

	return TRUE;
}

void QScanLanTesterDlg::slot_changeLocalIPAddrSel(int nCurComboxIndex)
{
	CString strLocalIP;
	strLocalIP = m_pLocalIP_ComboBox->currentText();

	if (strLocalIP.Find(".")>0)
	{
		m_oSttTestAppCfg.SetLocalIP(strLocalIP);
	}
}

CString GetValidIP(QNetworkInterface &oCurNetInterface)
{
	QList<QNetworkAddressEntry> oIPsList = oCurNetInterface.addressEntries();
	QNetworkAddressEntry oCurIP;
	CString strTmp;

	for (int nIP_index = 0;nIP_index<oIPsList.size();nIP_index++)
	{
		oCurIP = oIPsList.at(nIP_index);
		strTmp = oCurIP.ip().toString();

		if (strTmp.Find(("."))<=0)
		{
			continue;
		}

		return strTmp;
	}

	return "";
}

BOOL QScanLanTesterDlg::ValidCurrSelIP(const CString &strIP)
{
	long nCurSelCard = m_pNetCardSel_ComboBox->currentIndex();

	if (m_bUseScanLan)
	{
		if (nCurSelCard<0)
		{
			AddRecord(/*tr("当前选择的网卡为空.")*/g_sLangTxt_Native_CurrSelNetAdptEmpty);
			return FALSE;
		}

		if (nCurSelCard>=m_oNetWorkList.size())
		{
			CString strMsg;
			strMsg = QString(/*tr("当前选择的Index(%1),大于等于总的网卡数(%2).")*/g_sLangTxt_networkcards.arg(nCurSelCard).arg(m_oNetWorkList.size()));
			AddRecord(strMsg);
			return FALSE;
		}
	}
	

	long nIndex = strIP.ReverseFind('.');

	if (nIndex == -1)
	{
		CString strMsg;
		strMsg = QString(/*tr("当前选择的IP地址(%1)不合法.")*/g_sLangTxt_validIP.arg(strIP));
		AddRecord(strMsg);
		return FALSE;
	}
	else if (!m_bUseScanLan)
	{
		return TRUE;
	}

	QNetworkInterface oCurNetInterface = m_oNetWorkList.at(nCurSelCard);
	CString strTmp;
	strTmp = strIP.left(nIndex+1);
	QString strCurName = m_pNetCardSel_ComboBox->currentText();

	QList<QNetworkInterface> oAllInterfaces = QNetworkInterface::allInterfaces();
	QNetworkInterface oNetInterface;
	BOOL bFind = FALSE;

	for (int nIndex = 0; nIndex < oAllInterfaces.size(); nIndex++)
	{
		oNetInterface = oAllInterfaces.at(nIndex);

		if (oNetInterface.humanReadableName() == strCurName)
		{
			bFind = TRUE;
			break;
		}
	}

	if (!bFind)
	{
		QString strMsg;
		strMsg = QString(/*tr("当前网卡查找失败(%1).")*/g_sLangTxt_cardlookup.arg(strCurName));
		AddRecord(strMsg);
		return FALSE;
	}

	QList<QNetworkAddressEntry> oIPsList = oNetInterface.addressEntries();
	QNetworkAddressEntry oCurIP;
	CString strLocalIP;
	bFind = FALSE;

	for (int nIP_index = 0;nIP_index<oIPsList.size();nIP_index++)
	{
		oCurIP = oIPsList.at(nIP_index);
		strLocalIP = oCurIP.ip().toString();

		if (strLocalIP.Find(strTmp)==0)
		{
			bFind = TRUE;
			break;
		}
	}

	if (!bFind)
	{
		QString strMsg;
		strMsg = QString(/*tr("测试仪IP地址(%1)与当前网卡IP不在同一网段,请修改.")*/g_sLangTxt_modifyIP.arg(strIP));
		AddRecord(strMsg);
		return FALSE;
	}

	return TRUE;
}

void QScanLanTesterDlg::slot_changeNetCardSel(int nCurComboxIndex)
{
	QNetworkInterface oCurNetInterface;
	CString strLocalIP;
	CString strCurSelNetDesc;

	if (nCurComboxIndex>=m_oNetWorkList.size())
	{
		return;
	}

	oCurNetInterface = m_oNetWorkList.at(nCurComboxIndex);
	m_strNetCardLocalIP = GetValidIP(oCurNetInterface);
	UpdataLocalIP_Combox(oCurNetInterface);
	strCurSelNetDesc = oCurNetInterface.humanReadableName();

	if(m_strSelNetDesc != strCurSelNetDesc)
	{
		slot_ScanClicked();//先停止扫描
		m_strSelNetDesc = strCurSelNetDesc;
		m_oGridDatas.DeleteAll();
		m_pCurSelData = NULL;
		m_pScanLanTesterGrid->ShowDatas(&m_oGridDatas);
		slot_ScanClicked();//再启动扫描
	}
}

void QScanLanTesterDlg::slot_ModifyTesterIP(QString &strIP,const QString &strSubNetMask)
{
	if (m_pCurSelData == NULL)
	{
		return;
	}

	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(m_pCurSelData, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(m_pCurSelData, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);

	//设置后清除列表
	m_pCurSelData = NULL;
	m_oGridDatas.DeleteAll();
	m_pScanLanTesterGrid->ShowDatas(&m_oGridDatas);
	m_pModifyTesterIP_PushButton->setEnabled(false);

	if(m_pSttMulticastClientSocket != NULL)
	{
		m_pSttMulticastClientSocket->Multicast_SetIPV4s(strSN,strModel,strIP,strSubNetMask);
	}
}

void QScanLanTesterDlg::FreeMulticastSocket()
{
	if(m_pSttMulticastClientSocket != NULL)
	{
		m_pSttMulticastClientSocket->CloseSocket();

		delete m_pSttMulticastClientSocket;
		m_pSttMulticastClientSocket = NULL;
	}
}

void QScanLanTesterDlg::OnStopScan()
{
	if(m_nTimerID>=0)
	{
		killTimer(m_nTimerID);
		m_nTimerID = -1;
	}

//	FreeMulticastSocket();
//	EnableNetDevices(_T(""),DICS_ENABLE);
	m_bScan = FALSE;

 	if (m_pScan_PushButton != NULL)
 	{
		m_pScan_PushButton->setText(/*tr("扫描")*/g_sLangTxt_scan);
 	}

//	m_pOK_PushButton->setEnabled(true);
}

void QScanLanTesterDlg::timerEvent( QTimerEvent *event )
{
	if ( event->timerId() == m_nTimerID)
	{
		if (m_pSttMulticastClientSocket!= NULL)
		{
			m_pSttMulticastClientSocket->Multicast_QueryIP();
		}
		else
		{
			if (m_strSelNetDesc == "WLAN")
			{
				QList<QNetworkInterface> oAllInterfaces = QNetworkInterface::allInterfaces();
				QNetworkInterface oCurObj;

				for (int nIndex = 0; nIndex < oAllInterfaces.size(); nIndex++)
				{
					oCurObj = oAllInterfaces.at(nIndex);

					if (oCurObj.humanReadableName() == "WLAN")
					{
						UpdataLocalIP_Combox(oCurObj);
						break;
					}
				}
			}

			slot_ScanClicked();
		}
	}

	QWidget::timerEvent( event );
}

void QScanLanTesterDlg::UpdataLocalIP_Combox(QNetworkInterface &oCurNetInterface)
{
	QList<QNetworkAddressEntry> oIPsList = oCurNetInterface.addressEntries();

	CString strLocalIP;
	QNetworkAddressEntry oCurIP;
	m_pLocalIP_ComboBox->clear();
	QStringList strIP_List;

	for (int nIP_index = 0;nIP_index<oIPsList.size();nIP_index++)
	{
		oCurIP = oIPsList.at(nIP_index);
		strLocalIP = oCurIP.ip().toString();

		if (strLocalIP.Find(("."))<=0)
		{
			continue;
		}

		strIP_List.append(strLocalIP);
	}

	m_pLocalIP_ComboBox->addItems(strIP_List);
	slot_changeLocalIPAddrSel(0);
}

void QScanLanTesterDlg::InitLocalAdapters()
{
	m_pIpAdapterInfo = new IP_ADAPTER_INFO;
	unsigned long ulSize = sizeof(IP_ADAPTER_INFO);

	//获取适配器信息
	int nRet = GetAdaptersInfo(m_pIpAdapterInfo,&ulSize);

	if (ERROR_BUFFER_OVERFLOW == nRet)
	{
		delete []m_pIpAdapterInfo;

		m_pIpAdapterInfo = (PIP_ADAPTER_INFO) new BYTE[ulSize];
		nRet = GetAdaptersInfo(m_pIpAdapterInfo,&ulSize);

		if (ERROR_SUCCESS != nRet)
		{
			if (m_pIpAdapterInfo != NULL)
			{
				delete []m_pIpAdapterInfo;
				m_pIpAdapterInfo = NULL;
			}
		}
	}

	m_oNetWorkList = QNetworkInterface::allInterfaces();
	m_pNetCardSel_ComboBox->clear();
	QNetworkInterface oCurNetInterface;
	BOOL bHasInitLocalIP = FALSE,bValid = FALSE;

	for (int nIndex = 0; nIndex < m_oNetWorkList.size(); nIndex++)
	{
		oCurNetInterface = m_oNetWorkList.at(nIndex);
		bValid = FALSE;

		if (oCurNetInterface.flags().testFlag(QNetworkInterface::IsUp) &&
			oCurNetInterface.flags().testFlag(QNetworkInterface::IsRunning) &&
			oCurNetInterface.flags().testFlag(QNetworkInterface::CanMulticast))
		{
			QList<QNetworkAddressEntry> oIPsList = oCurNetInterface.addressEntries();

			if (HasValidIP(oIPsList))
			{
				if (!bHasInitLocalIP)
				{
					bHasInitLocalIP = TRUE;
					UpdataLocalIP_Combox(oCurNetInterface);
					m_strSelNetDesc = oCurNetInterface.humanReadableName();
//					m_strNetCardID = oCurNetInterface.name();
				}

				bValid = TRUE;
				m_pNetCardSel_ComboBox->insertItem(nIndex,oCurNetInterface.humanReadableName());
			}
		}

		if (!bValid)
		{
			m_oNetWorkList.removeAt(nIndex);
			nIndex--;
		}
	}
}

void QScanLanTesterDlg::OnMulticastReceiveMsg(BYTE *pBuf, long nLen,LPVOID fsockaddr)
{

}

void QScanLanTesterDlg::OnProcessDataMsg(BYTE nCmdType, CSttPpDatasDriver vec)
{
	switch (nCmdType)
	{
	case MULTICAST_CMD_QUERYIPS_ACK:
		{
			Process_Multicast_QueryIP_ACK(vec);
			break;
		}
	case MULTICAST_CMD_QUERYSERVERSTATE_ACK:
		{
			Process_Multicast_QueryServerState_ACK(vec);
			break;
		}
	default:
		break;	
	}
}

void QScanLanTesterDlg::OnStopMulticastMsg()
{
	OnStopScan();
}

BOOL QScanLanTesterDlg::Process_Multicast_QueryIP_ACK(CSttPpDatasDriver vec)
{	
	CString strSN = _T(""),strModel = _T("");
	CString strIP = _T(""),strMask = _T("");

	CSttPpDatas *pDatas = vec.GetDatas();
	pDatas->FindDataByID(STT_PP_DATAID_SN, strSN);
	pDatas->FindDataByID(STT_PP_DATAID_MODEL, strModel);
	pDatas->FindDataByID(STT_PP_DATAID_IP, strIP, strMask);

	POS pos = m_oGridDatas.GetHeadPosition();
	CDataGroup *pFind = NULL;
	CDataGroup *p= NULL;

	while (pos != NULL)
	{
		p = (CDataGroup *)m_oGridDatas.GetNext(pos);

		CString strValue = _T("");
		stt_GetDataValueByID(p, ID_STT_USER_ATTR_SN_TestApp, strValue);
		if (strSN == strValue)
		{
			pFind = p;
			break;
		}
	}

	if (pFind != NULL)
	{
		return TRUE;
	}

	CDataGroup *RecvGroup = new CDataGroup;
	RecvGroup->AddNewData(_T(""),ID_STT_USER_ATTR_SN_TestApp,_T(""),strSN);
	RecvGroup->AddNewData(_T(""),ID_STT_REGISTER_ATTR_Model_TestApp,_T(""),strModel);
	CDataGroup *pNew = RecvGroup->AddNewGroup(STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP);
	pNew->AddNewData(STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, strIP);
	pNew->AddNewData(STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, strMask);

	m_oGridDatas.AddTail(RecvGroup);
	m_pScanLanTesterGrid->ShowDatas(&m_oGridDatas);

	return TRUE;
}

BOOL QScanLanTesterDlg::Process_Multicast_QueryServerState_ACK(CSttPpDatasDriver vec)
{
	CString strSN = _T(""),strModel = _T("");
	long nErrCode = 0;

	CSttPpDatas *pDatas = vec.GetDatas();
	pDatas->FindDataByID(STT_PP_DATAID_SN, strSN);
	pDatas->FindDataByID(STT_PP_DATAID_MODEL, strModel);
	pDatas->FindDataByID(STT_PP_DATAID_RUNSTATE, nErrCode);

	if (nErrCode != 0)
	{
		CString strTmp;
		strTmp = QString(/*tr("查询测试仪【SN=%1】【Model=%2】运行进程失败【ErrCode=%3】。")*/g_sLangTxt_query.arg(strSN).arg(strModel).arg(nErrCode));
		AddRecord(strTmp);
		return FALSE;
	}

	POS pos = pDatas->GetHeadPosition();
	PSTT_PP_DATA p = NULL;
	CString strValue = _T("");
	QString strInfo;
	strInfo = QString(/*tr("查询测试仪【SN=%1】【Model=%2】运行进程结果：")*/g_sLangTxt_running.arg(strSN).arg(strModel));

	while (pos != NULL)
	{
		p = pDatas->GetNext(pos);

		if (p->id != STT_PP_DATAID_PROCESSID)
		{
			continue;
		}

		stt_pp_data_get_string(p, strValue);
		strInfo += QString(tr("【%1】;").arg(strValue));
	}

	AddRecord(strInfo);
//	m_bProgressed = TRUE;
	return TRUE;
}

void QScanLanTesterDlg::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	CDataGroup *pCurrSelTester = (CDataGroup*)m_pScanLanTesterGrid->GetCurrSelData();

	if (pCurrSelTester == NULL)
	{
		return;
	}

	CDataGroup *pGroup = (CDataGroup *)pCurrSelTester->FindByID(STT_SYS_DATA_ID_DeviceIP);

	if (pGroup == NULL)
	{
		return;
	}

	CString strIP;
	stt_GetDataValueByID(pGroup, STT_SYS_DATA_ID_IP, strIP);

	if (strIP.IsEmpty())
	{
		return;
	}

	ValidCurrSelIP(strIP);
	m_pCurSelData = pCurrSelTester;
	m_pServerIP_LineEdit->setText(strIP);
	m_pModifyTesterIP_PushButton->setEnabled(true);
}

void QScanLanTesterDlg::AddRecord(const CString &description )
{
	if (m_pLogString_TextEdit == NULL)
		return;

//	m_pLogString_LineEdit->setTextColor(color);

	QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
	time += "      ";
	time += description;

	m_pLogString_TextEdit->append(time);

	QTextCursor cursor = m_pLogString_TextEdit->textCursor();     
	cursor.movePosition(QTextCursor::End);     
	m_pLogString_TextEdit->setTextCursor(cursor);
}



