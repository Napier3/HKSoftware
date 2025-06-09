#include "qnetworkconfigwidget.h"
#include "ui_qnetworkconfigwidget.h"
#include "../../../SttGlobalDef.h"
#include "QModifyIPAddrDlg.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../../61850/Module/XLanguageResourcePp_Mms.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"


#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif


QNetworkConfigWidget::QNetworkConfigWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNetworkConfigWidget)
{
    ui->setupUi(this);

	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint); 

	m_pSttMulticastClientSocket = NULL;
	m_bScan = FALSE;
	m_nTimerID = -1;
	m_bUseScanLan = TRUE;
	m_pIpGrid = NULL;
	m_pCurSelData = NULL;

	m_strSelNetDesc = _T("");

	ui->m_pNetCardSel_Label->setText(g_sLangTxt_NetwCardSel); //网卡选择 lcq
	ui->m_pLocalIP_Label->setText(g_sLangTxt_Gradient_LocalNICIP);//本地网卡IP lcq
	ui->m_pScan_PushButton->setText(g_sLangTxt_scan); //扫描 lcq
	ui->m_pServerIP_Label->setText(g_sLangTxt_Gradient_PrimaryIP);//主IP地址： lcq 
	ui->m_btnModify->setText(g_sLangTxt_Modify); //修改 lcq
	ui->m_btnAdd->setText(g_sLangTxt_Add); //添加 lcq
	ui->m_btnDelete->setText(g_sLangTxt_Delete); //删除 lcq
	ui->m_pCancel_PushButton->setText(g_sLangTxt_Close); //关闭 lcq

#ifdef _PSX_QT_LINUX_


#else

	m_pIpAdapterInfo = NULL;
	m_hDevInfo = INVALID_HANDLE_VALUE;
	m_strNetCardLocalIP = "";

#endif

}

void QNetworkConfigWidget::InitUI()
{
	resize(750,400);
	this->setFixedWidth(750);
	this->setFixedHeight(400);
	//CString strTemp = _T("装置IP地址");
	setWindowTitle(g_sLangTxt_IP);

	m_pIpGrid = new QNetworkIpTable(this);
	ui->m_wndVertLayout->insertWidget(0, m_pIpGrid);
	m_pIpGrid->AttachDataViewOptrInterface(this);
	m_pIpGrid->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	m_pIpGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIpGrid->setFont(*g_pSttGlobalFont);

#ifdef _PSX_QT_LINUX_

	ui->m_pNetCardSel_ComboBox-> hide();
	ui->m_pNetCardSel_Label-> hide();
	ui->m_pLocalIP_Label-> hide();
	ui->m_pLocalIP_ComboBox-> hide();
#endif

	m_oSttTestAppCfg.SttOpen(m_oSttTestAppCfg.GetOldCfgFile());
	ui->m_pServerIP_LineEdit->setText(m_oSttTestAppCfg.GetTestAppIP());

	initConnections();
	InitLocalAdapters();
	SetNetworkConfigWidgetFont();
	EnableButtons();

	
}

QNetworkConfigWidget::~QNetworkConfigWidget()
{
   	FreeMulticastSocket();
	
	delete ui;
}

void QNetworkConfigWidget::initConnections()
{
	connect(ui->m_pScan_PushButton, SIGNAL(clicked()), this, SLOT(slot_ScanClicked()));
	connect(ui->m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(ui->m_pNetCardSel_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeNetCardSel(int)));
	connect(ui->m_pLocalIP_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeLocalIPAddrSel(int)));
	connect(ui->m_btnAdd, SIGNAL(clicked()), this, SLOT(slot_btnAdd_clicked()));
	connect(ui->m_btnDelete, SIGNAL(clicked()), this, SLOT(slot_btnDelete_clicked()));
	connect(ui->m_btnModify, SIGNAL(clicked()), this, SLOT(slot_btnModify_clicked()));
	
}

void QNetworkConfigWidget::slot_btnAdd_clicked()
{
	//若不在这边重新获取表格当前选中数据，需要将m_pCurSelData =NULL开放；
	//如采用OnDataSelChanged（）中的m_pCurSelData，需要将m_pCurSelData = NULL；不然连续添加或者修改会闪退。

	m_pCurSelData = (CDataGroup*)m_pIpGrid->GetCurrSelData();

	if(m_pCurSelData == NULL)
	{
		return;
	}

#ifdef _PSX_QT_LINUX_

#else
	if(m_pSttMulticastClientSocket == NULL)
	{

		if (!ConnectMulticastServer())
		{
			return;
		}

	}
#endif

	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(m_pCurSelData, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(m_pCurSelData, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);

	CDataGroup *pGroupIP = (CDataGroup *)m_pCurSelData->FindByID(STT_SYS_DATA_ID_DeviceIP);
	CString strIP = m_oSttTestAppCfg.GetTestAppIP();

	if (pGroupIP != NULL)
	{
		stt_GetDataValueByID(pGroupIP, STT_SYS_DATA_ID_IP, strIP);
	}

	QModifyIPAddrDlg oModifyIP_Dlg(this);
	oModifyIP_Dlg.setFont(*g_pSttGlobalFont);
	//CString strTemp = _T("增加测试仪辅助IP");
	oModifyIP_Dlg.setWindowTitle(g_sLangTxt_assistantIP);
	oModifyIP_Dlg.InitParas(strModel,strSN,strIP);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oModifyIP_Dlg);
#endif

	connect(&oModifyIP_Dlg, SIGNAL(sig_ModifyTesterIP_OK(QString &,const QString &)), this, SLOT(slot_AddTesterIPAsMask(QString &,const QString &)));
	oModifyIP_Dlg.exec();

#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif

	disconnect(&oModifyIP_Dlg, SIGNAL(sig_ModifyTesterIP_OK(QString &,const QString &)), this, SLOT(slot_AddTesterIPAsMask(QString &,const QString &)));

}

void QNetworkConfigWidget::slot_AddTesterIPAsMask(QString &strIP, const QString &strSubNetMask)
{
	if (m_pCurSelData == NULL)
	{
		return;
	}

	CString strMsg,strTemp,strTip,strUsb;
	//strTip=_T("提示");
	
	if (!IsIPExactness(strIP))
	{
		//strUsb = _T("(%1)不是有效项。请指定一个介于0和255间的值。");

		strMsg = QString(g_sLangTxt_validentry.arg(strIP));
		CXMessageBox::information(this,g_sLangTxt_Message ,strMsg);
		return;
	}

	for (int i = 0 ; i<m_astrIP.GetCount();i++)
	{
		CString strListIP = m_astrIP.GetAt(i);

		if (strListIP == strIP)
		{
			//strTemp = _T("列表已存在IP地址(%1)");
			strMsg = QString(g_sLangTxt_listIP .arg(strIP));
			CXMessageBox::information(this,g_sLangTxt_Message,strMsg);
			return;
		}
	}

	if(	!ValidCurrSelIP(strIP))
	{
		//strTemp = _T("测试仪IP地址(%1)与当前网卡IP不在同一网段,是否添加?");
		strMsg = QString(g_sLangTxt_cardIP.arg(strIP));
		int nRet = QMessageBox::question(this,g_sLangTxt_Message,strMsg,g_sLangTxt_State_Yes,g_sLangTxt_State_No);

		if (nRet == 1)
		{
 			return;
		}
	}
	
	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(m_pCurSelData, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(m_pCurSelData, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);
	m_astrIP.Add(strIP);
	m_astrMask.Add(strSubNetMask);

	m_oGridDatas.DeleteAll();

	for (int i = 0 ; i<m_astrIP.GetCount();i++)
	{
		CDataGroup *RecvGroup = new CDataGroup;
		RecvGroup->AddNewData(_T(""),ID_STT_USER_ATTR_SN_TestApp,_T(""),strSN);
		RecvGroup->AddNewData(_T(""),ID_STT_REGISTER_ATTR_Model_TestApp,_T(""),strModel);
		CDataGroup *pNew = RecvGroup->AddNewGroup(STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP);
		pNew->AddNewData(STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, m_astrIP.GetAt(i));
		pNew->AddNewData(STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, m_astrMask.GetAt(i));

		m_oGridDatas.AddTail(RecvGroup);
	}

	// 	m_pCurSelData = NULL; 
	// 	EnableButtons();
	m_pIpGrid->ShowDatas(&m_oGridDatas);

#ifdef _PSX_QT_LINUX_
	
	CString strPreIP,strPreMask;
	stt_file_get_deviceip(strPreIP,strPreMask);
	//更新错误码
	int nErrCode = 0;

	nErrCode = stt_net_set_deviceip(m_astrIP.GetAt(0),m_astrMask.GetAt(0));//nErrCode=1,设置失败
	stt_net_set_subips(m_astrIP,m_astrMask,1);

	system("sync");
	
	strIP = m_astrIP.GetAt(0);

	if(strPreIP == strIP)
	{
		system("/mnt/setip.sh");
	}
	else
	{
		system("reboot");
	}

#else


	if(m_pSttMulticastClientSocket != NULL)
	{
		m_pSttMulticastClientSocket->Multicast_SetIPV4Array(strSN,strModel,m_astrIP,m_astrMask);
	}
#endif
}



void QNetworkConfigWidget::slot_btnDelete_clicked()
{
	m_pCurSelData =(CDataGroup *) m_pIpGrid->GetCurrSelData();
	
	if (m_pCurSelData == NULL)
	{
		return;
	}

	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(m_pCurSelData, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(m_pCurSelData, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);

	CDataGroup *pGroupIP = (CDataGroup *)m_pCurSelData->FindByID(STT_SYS_DATA_ID_DeviceIP);
	CString strIP;
	if (pGroupIP != NULL)
	{
		stt_GetDataValueByID(pGroupIP, STT_SYS_DATA_ID_IP, strIP);
	}

	for(int i=0;i<m_astrIP.GetCount();i++)
	{
		CString strIPs = m_astrIP.GetAt(i);
		
		if (strIPs == strIP)
		{

// 			if (strIPs == m_astrIP.GetAt(0))
// 			{
// 				return;
// 			}

			m_astrIP.RemoveAt(i);
			m_astrMask.RemoveAt(i);
		}
	}

	int row = m_pIpGrid->currentRow();
	m_pIpGrid->removeRow(row);

#ifdef _PSX_QT_LINUX_

	CString strPreIP,strPreMask;
	stt_file_get_deviceip(strPreIP,strPreMask);
	//更新错误码
	int nErrCode = 0;

	nErrCode = stt_net_set_deviceip(m_astrIP.GetAt(0),m_astrMask.GetAt(0));//nErrCode=1,设置失败
	stt_net_set_subips(m_astrIP,m_astrMask,1);

	system("sync");

	strIP = m_astrIP.GetAt(0);

	if(strPreIP == strIP)
	{
		system("/mnt/setip.sh");
	}
	else
	{
		system("reboot");
	}

#else


	if(m_pSttMulticastClientSocket != NULL)
	{
		m_pSttMulticastClientSocket->Multicast_SetIPV4Array(strSN,strModel,m_astrIP,m_astrMask);
	}
#endif

}

void QNetworkConfigWidget::slot_btnModify_clicked()
{
	m_pCurSelData = (CDataGroup*)m_pIpGrid->GetCurrSelData();//若不在这边获取表格当前选中数据，需要将m_pCurSelData =NULL开放

	if(m_pCurSelData == NULL)
	{
		return;
	}

#ifdef _PSX_QT_LINUX_

#else

	if(m_pSttMulticastClientSocket == NULL)
	{

		if (!ConnectMulticastServer())
		{
			return;
		}
	}

#endif
	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(m_pCurSelData, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(m_pCurSelData, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);

	CDataGroup *pGroupIP = (CDataGroup *)m_pCurSelData->FindByID(STT_SYS_DATA_ID_DeviceIP);
	CString strIP;

	if (pGroupIP != NULL)
	{
		stt_GetDataValueByID(pGroupIP, STT_SYS_DATA_ID_IP, strIP);
	}

	for(int i=0;i<m_astrIP.GetCount();i++)
	{
		CString strIPs = m_astrIP.GetAt(i);
		

		if (strIPs == strIP)
		{

// 			if (strIPs == m_astrIP.GetAt(0))
// 			{
// 				return;
// 			}
			m_astrIP.RemoveAt(i);
			m_astrMask.RemoveAt(i);
		}
	}


	QModifyIPAddrDlg oModifyIP_Dlg(this);
	oModifyIP_Dlg.setFont(*g_pSttGlobalFont);
	oModifyIP_Dlg.InitParas(strModel,strSN,strIP);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oModifyIP_Dlg);
#endif

	connect(&oModifyIP_Dlg, SIGNAL(sig_ModifyTesterIP_OK(QString &,const QString &)), this, SLOT(slot_ModifyTesterIPAsMask(QString &,const QString &)));
	oModifyIP_Dlg.exec();

#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif

	disconnect(&oModifyIP_Dlg, SIGNAL(sig_ModifyTesterIP_OK(QString &,const QString &)), this, SLOT(slot_ModifyTesterIPAsMask(QString &,const QString &)));
}

void QNetworkConfigWidget::slot_ModifyTesterIPAsMask(QString &strIP,const QString &strSubNetMask)
{
	if (m_pCurSelData == NULL)
	{
		return;
	}

	CString strMsg,strTemp,strTip,strUsb;
	//strTip=_T("提示");

	if (!IsIPExactness(strIP))
	{
		//strUsb = _T("(%1)不是有效项。请指定一个介于0和255间的值。");

		strMsg = QString(g_sLangTxt_validentry.arg(strIP));
		CXMessageBox::information(this,g_sLangTxt_Message,strMsg);
		return;
	}
	
	for (int i = 0 ; i<m_astrIP.GetCount();i++)
	{
		CString strListIP = m_astrIP.GetAt(i);

		if (strListIP == strIP)
		{
			//strTemp = _T("列表已存在IP地址(%1)");
			strMsg = QString(g_sLangTxt_listIP.arg(strIP));
			CXMessageBox::information(this,g_sLangTxt_Message,strMsg);
			return;
		}
	}

	if(	!ValidCurrSelIP(strIP))
	{

		//strTemp = _T("测试仪IP地址(%1)与当前网卡IP不在同一网段,是否添加?");
		strMsg = QString(g_sLangTxt_cardIP .arg(strIP));
		int nRet = QMessageBox::question(this,g_sLangTxt_Message,strMsg,g_sLangTxt_State_Yes,g_sLangTxt_State_No);

		if (nRet == 1)
		{
			return;
		}

	}


	m_astrIP.Add(strIP);
	m_astrMask.Add(strSubNetMask);

	CString strSN = _T(""),strModel = _T("");
	stt_GetDataValueByID(m_pCurSelData, ID_STT_USER_ATTR_SN_TestApp, strSN);
	stt_GetDataValueByID(m_pCurSelData, ID_STT_REGISTER_ATTR_Model_TestApp, strModel);
	m_oGridDatas.DeleteAll();

	for(int i=0;i<m_astrIP.GetCount();i++)
	{
		CDataGroup *RecvGroup = new CDataGroup;
		RecvGroup->AddNewData(_T(""),ID_STT_USER_ATTR_SN_TestApp,_T(""),strSN);
		RecvGroup->AddNewData(_T(""),ID_STT_REGISTER_ATTR_Model_TestApp,_T(""),strModel);
		CDataGroup *pNew = RecvGroup->AddNewGroup(STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP);
		pNew->AddNewData(STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, m_astrIP.GetAt(i));
		pNew->AddNewData(STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, m_astrMask.GetAt(i));
		m_oGridDatas.AddTail(RecvGroup);

	}
// 	m_pCurSelData = NULL; //如果采用OnDataSelChanged（）中的m_pCurSelData，需要将m_pCurSelData = NULL；不然连续添加或者修改会闪退。
// 	EnableButtons();
	m_pIpGrid->ShowDatas(&m_oGridDatas);

#ifdef _PSX_QT_LINUX_

	CString strPreIP,strPreMask;
	stt_file_get_deviceip(strPreIP,strPreMask);

	//更新错误码
	int nErrCode = 0;

	nErrCode = stt_net_set_deviceip(m_astrIP.GetAt(0),m_astrMask.GetAt(0));//nErrCode=1,设置失败

	stt_net_set_subips(m_astrIP,m_astrMask,1);

	system("sync");

	strIP = m_astrIP.GetAt(0);

	if(strPreIP == strIP)
	{
		system("/mnt/setip.sh");
	}
	else
	{
		system("reboot");
	}

#else

	if(m_pSttMulticastClientSocket != NULL)
	{
		m_pSttMulticastClientSocket->Multicast_SetIPV4s(strSN,strModel,strIP,strSubNetMask);
	}
#endif

}

BOOL QNetworkConfigWidget::ConnectMulticastServer()
{
	FreeMulticastSocket();
	m_pSttMulticastClientSocket = new CSttMulticastClientSocket;

#ifdef _PSX_QT_LINUX_


#else
	if(!m_pSttMulticastClientSocket->Create(m_oSttTestAppCfg.GetMulticastIP(),m_oSttTestAppCfg.GetMulticastPort(),m_oSttTestAppCfg.GetLocalIP(),m_oSttTestAppCfg.GetMulticastPort()))
	{
		return FALSE;
	}
#endif
	return TRUE;
}

void QNetworkConfigWidget::FreeMulticastSocket()
{
	if(m_pSttMulticastClientSocket != NULL)
	{
		m_pSttMulticastClientSocket->CloseSocket();

		delete m_pSttMulticastClientSocket;
		m_pSttMulticastClientSocket = NULL;
	}
}

void QNetworkConfigWidget::QueryLinuxIP()
{
	m_astrIP.RemoveAll();
	m_astrMask.RemoveAll();
	m_oGridDatas.DeleteAll();

	CString strIP, strMask;
	CString strSN,strModel;
	//需更新上面四个参数

#ifdef _PSX_QT_LINUX_
	QFile fileIp("/mnt/setip.sh");
	if(!fileIp.exists())
	{
		stt_net_get_deviceip(strIP, strMask);

		m_astrIP.Add(strIP);
		m_astrMask.Add(strMask);
	}
	else
	{
		if(fileIp.open(QIODevice::Text|QIODevice::ReadWrite))//|QIODevice::Truncate
		{
			char pszBuf[1024];
			int nfileSize;
			while(!fileIp.atEnd())
			{
				nfileSize = fileIp.readLine(pszBuf,1024);
				if(nfileSize > 0)
				{
					CString strData(pszBuf);
					if(strData.contains("ifconfig") && strData.contains("netmask"))
					{
						QList<QString> oList = strData.split(" ");
						m_astrIP.Add(oList.at(2));
						m_astrMask.Add(oList.at(4));

					}
				}
			}

			fileIp.close();
		}
	}
#endif

	strSN=_T("PSL001");
	strModel=_T("PSL001");
	QFile fileXml(_P_GetConfigPath()+CString("DeviceSystemParas.xml"));
	if(fileXml.exists())
	{
		if(fileXml.open(QIODevice::Text|QIODevice::ReadOnly))
		{
			char pszBuf[1000];
			fileXml.read(pszBuf,1000);
			fileXml.close();

			pszBuf[999]='\0';
			CString strData(pszBuf);
			stt_find_device_info(strData,strSN,strModel);
		}
	}

	long nSendBufLen = 1024;
	BYTE *pSendBuf = new BYTE[nSendBufLen];
	BYTE *pHead = pSendBuf + STT_PKG_HEAD_LEN;
	BYTE *pPos = pHead;

	for(int i = 0;i < m_astrIP.GetCount();i++)
	{
		stt_pp_pkt_pack_ipV4Val(pPos, STT_PP_DATAID_IP, m_astrIP.GetAt(i), m_astrMask.GetAt(i));

		CDataGroup *RecvGroup = new CDataGroup;
		RecvGroup->AddNewData(_T(""),ID_STT_USER_ATTR_SN_TestApp,_T(""),strSN);
		RecvGroup->AddNewData(_T(""),ID_STT_REGISTER_ATTR_Model_TestApp,_T(""),strModel);
		CDataGroup *pNew = RecvGroup->AddNewGroup(STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP);
		pNew->AddNewData(STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, m_astrIP.GetAt(i));
		pNew->AddNewData(STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, m_astrMask.GetAt(i));
		m_oGridDatas.AddTail(RecvGroup);
	}

	ui->m_pServerIP_LineEdit->setText(m_astrIP.GetAt(0));

	m_pIpGrid->ShowDatas(&m_oGridDatas);

	delete pSendBuf;

}


void QNetworkConfigWidget::stt_find_device_info(CString strData,CString &strSN,CString &strModel)
{
	int nPosBegin=strData.Find("\"SN\"");
	nPosBegin=strData.Find(" value",nPosBegin);
	nPosBegin=strData.Find("\"",nPosBegin);
	int nPosEnd=strData.Find("\"",nPosBegin+1);
	strSN = strData.Mid(nPosBegin+1,nPosEnd-nPosBegin-1);

	nPosBegin=strData.Find("\"Model\"");
	nPosBegin=strData.Find(" value=",nPosBegin);
	nPosBegin=strData.Find("\"",nPosBegin);
	nPosEnd=strData.Find("\"",nPosBegin+1);
	strModel = strData.Mid(nPosBegin+1,nPosEnd-nPosBegin-1);
}

void QNetworkConfigWidget::timerEvent( QTimerEvent *event )
{
	if ( event->timerId() == m_nTimerID)
	{
		
		if (m_pSttMulticastClientSocket!= NULL)
		{

#ifdef _PSX_QT_LINUX_
			QueryLinuxIP();

#else
			m_pSttMulticastClientSocket->Multicast_QueryIP();
			
#endif
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


void QNetworkConfigWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{

	CDataGroup *pCurrSelTester = (CDataGroup*)m_pIpGrid->GetCurrSelData();

	if (pCurrSelTester == NULL)
	{
		return;
	}
	
	CDataGroup *pGroup = (CDataGroup *)pCurrSelTester->FindByID(STT_SYS_DATA_ID_DeviceIP);

	if (pGroup == NULL)
	{
		return;
	}


	CString strIP,strMask;
	stt_GetDataValueByID(pGroup, STT_SYS_DATA_ID_IP, strIP);

	if (strIP.IsEmpty())
	{
		return;
	}

	stt_GetDataValueByID(pGroup, STT_SYS_DATA_ID_mask, strMask);

	if (strMask.IsEmpty())
	{
		return;
	}

	m_pCurSelData = pCurrSelTester;
	EnableButtons();
	m_bScan = TRUE;
	slot_ScanClicked();
	//ui->m_pServerIP_LineEdit->setText(strIP);
	
}

void QNetworkConfigWidget::OnMulticastReceiveMsg(BYTE *pBuf, long nLen,LPVOID fsockaddr)
{

}
void QNetworkConfigWidget::OnProcessDataMsg(BYTE nCmdType, CSttPpDatasDriver vec)
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
void QNetworkConfigWidget::OnStopMulticastMsg()
{
	OnStopScan();
}


void QNetworkConfigWidget::OnStopScan()
{
	if(m_nTimerID>=0)
	{
		killTimer(m_nTimerID);
		m_nTimerID = -1;
	}

	m_bScan = FALSE;

	if (ui->m_pScan_PushButton != NULL)
	{
		//CString  strTemp =_T("扫描");
		ui->m_pScan_PushButton->setText(g_sLangTxt_scan);
	}

}

BOOL QNetworkConfigWidget::Process_Multicast_QueryIP_ACK(CSttPpDatasDriver vec)
{	
	m_astrIP.RemoveAll();
	m_astrMask.RemoveAll();
	m_oGridDatas.DeleteAll();


	CString strSN = _T(""),strModel = _T("");
	CString strIP = _T(""),strMask = _T("");
	CString strFirstSN;

	CSttPpDatas *pDatas = vec.GetDatas();
	pDatas->FindDataByID(STT_PP_DATAID_SN, strSN);
	pDatas->FindDataByID(STT_PP_DATAID_MODEL, strModel);

	POS pos2 = pDatas->GetHeadPosition();
	PSTT_PP_DATA p2 = NULL;

	while (pos2 != NULL)
	{
		p2 = pDatas->GetNext(pos2);

		if (p2->id == STT_PP_DATAID_IP)
		{
			stt_pp_data_get_ipVal(p2, strIP, strMask);
			m_astrIP.Add(strIP);
			m_astrMask.Add(strMask);
		
		}
	}


	if (strSN.GetLength() != 0)
	{
		if (strFirstSN == strSN)
		{
			return TRUE;
		}
	}

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

	for(int i = 0;i<m_astrIP.GetCount();i++)
	{
		CDataGroup *RecvGroup = new CDataGroup;
		RecvGroup->AddNewData(_T(""),ID_STT_USER_ATTR_SN_TestApp,_T(""),strSN);
		RecvGroup->AddNewData(_T(""),ID_STT_REGISTER_ATTR_Model_TestApp,_T(""),strModel);
		CDataGroup *pNew = RecvGroup->AddNewGroup(STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP, STT_SYS_DATA_ID_DeviceIP);
		pNew->AddNewData(STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, STT_SYS_DATA_ID_IP, m_astrIP.GetAt(i));
		pNew->AddNewData(STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, STT_SYS_DATA_ID_mask, m_astrMask.GetAt(i));
		
		m_oGridDatas.AddTail(RecvGroup);
	}
	
	ui->m_pServerIP_LineEdit->setText(m_astrIP.GetAt(0));
	m_pIpGrid->ShowDatas(&m_oGridDatas);
	strFirstSN = strSN;


	return TRUE;
}

BOOL QNetworkConfigWidget::Process_Multicast_QueryServerState_ACK(CSttPpDatasDriver vec)
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
		strTmp = QString(g_sLangTxt_query.arg(strSN).arg(strModel).arg(nErrCode));
		CLogPrint::LogString(XLOGLEVEL_INFOR,strTmp);
		//AddRecord(strTmp);
		return FALSE;
	}

	POS pos = pDatas->GetHeadPosition();
	PSTT_PP_DATA p = NULL;
	CString strValue = _T("");
	QString strInfo;
	strInfo = QString(g_sLangTxt_running.arg(strSN).arg(strModel));

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

	CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);

	return TRUE;
}


void QNetworkConfigWidget::InitLocalAdapters()
{

#ifdef _PSX_QT_LINUX_


#else
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

#endif

	m_oNetWorkList = QNetworkInterface::allInterfaces();
	
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
					//oCurNetInterface =m_oNetWorkList.at(2);
					UpdataLocalIP_Combox(oCurNetInterface);
					m_strSelNetDesc = oCurNetInterface.humanReadableName();

				}

				bValid = TRUE;
				ui->m_pNetCardSel_ComboBox->insertItem(nIndex,oCurNetInterface.humanReadableName());
				
			}
		}

		if (!bValid)
		{
			m_oNetWorkList.removeAt(nIndex);
			nIndex--;
		}
	}
}

BOOL QNetworkConfigWidget::HasValidIP(QList<QNetworkAddressEntry> &oIPsList)
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


void QNetworkConfigWidget::EnableButtons()
{
	if (m_pCurSelData == NULL)
	{
		ui->m_pServerIP_LineEdit->setEnabled(FALSE);
		ui->m_btnModify->setEnabled(FALSE);
		ui->m_btnAdd->setEnabled(FALSE);
		ui->m_btnDelete->setEnabled(FALSE);
	}
	else
	{
		ui->m_btnModify->setEnabled(TRUE);
		ui->m_btnDelete->setEnabled(TRUE);
		ui->m_btnAdd->setEnabled(TRUE);
	}

}

void QNetworkConfigWidget::SetNetworkConfigWidgetFont()
{
	ui->m_btnModify->setFont(*g_pSttGlobalFont);
	ui->m_btnDelete->setFont(*g_pSttGlobalFont);
	ui->m_btnAdd->setFont(*g_pSttGlobalFont);
	ui->m_pServerIP_LineEdit->setFont(*g_pSttGlobalFont);
	ui->m_pServerIP_Label->setFont(*g_pSttGlobalFont);
	ui->m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
	ui->m_pScan_PushButton->setFont(*g_pSttGlobalFont);

	ui->m_pNetCardSel_Label->setFont(*g_pSttGlobalFont);
	ui->m_pLocalIP_Label->setFont(*g_pSttGlobalFont);
	ui->m_pNetCardSel_ComboBox->setFont(*g_pSttGlobalFont);
	ui->m_pLocalIP_ComboBox->setFont(*g_pSttGlobalFont);

}

CString QNetworkConfigWidget::GetNetCardDesc()
{

#ifdef _PSX_QT_LINUX_


#else

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

	//AddRecord(tr("获取本地IP地址失败,当前值为空."));
	CLogPrint::LogString(XLOGLEVEL_INFOR,g_sLangTxt_nullIP);

#endif

	return "";
}

void QNetworkConfigWidget::slot_ScanClicked()
{
	disconnect(ui->m_pScan_PushButton, SIGNAL(clicked()), this, SLOT(slot_ScanClicked()));
	ui->m_pScan_PushButton->setEnabled(false);

	if(!m_bScan)
	{
		m_astrIP.RemoveAll();
		m_astrMask.RemoveAll();

		CString strNetCardDesc;
		strNetCardDesc = GetNetCardDesc();

		if (!ConnectMulticastServer())
		{

			CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,/*_T("创建组播链接失败,无法进行扫描,5s后自动重连.")*/g_sLangTxt_automatic.GetString());

			FreeMulticastSocket();

			if (m_nTimerID != -1)
			{
				killTimer(m_nTimerID);
			}

			m_nTimerID = startTimer(5000);
			return;
		}

		m_oGridDatas.DeleteAll();
		m_pCurSelData = NULL;
		EnableButtons();
		m_pIpGrid->ShowDatas(&m_oGridDatas);
		
		//CString strTemp = _T("停止扫描");
		ui->m_pScan_PushButton->setText(g_sLangTxt_stopscan);
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

	
	ui->m_pScan_PushButton->setEnabled(true);
	connect(ui->m_pScan_PushButton, SIGNAL(clicked()), this, SLOT(slot_ScanClicked()));

}

void QNetworkConfigWidget::slot_changeNetCardSel(int nCurComboxIndex)
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
		EnableButtons();
		m_pIpGrid->ShowDatas(&m_oGridDatas);
		slot_ScanClicked();//再启动扫描
	}
}

void QNetworkConfigWidget::UpdataLocalIP_Combox(QNetworkInterface &oCurNetInterface)
{
	QList<QNetworkAddressEntry> oIPsList = oCurNetInterface.addressEntries();

	CString strLocalIP;
	QNetworkAddressEntry oCurIP;
	ui->m_pLocalIP_ComboBox->clear();
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

	ui->m_pLocalIP_ComboBox->addItems(strIP_List);
	slot_changeLocalIPAddrSel(0);
}

BOOL QNetworkConfigWidget::ValidCurrSelIP(const CString &strIP)
{
	long nCurSelCard = ui->m_pNetCardSel_ComboBox->currentIndex();

	if (m_bUseScanLan)
	{
		if (nCurSelCard<0)
		{
			//AddRecord(tr("当前选择的网卡为空."));
			return FALSE;
		}

		if (nCurSelCard>=m_oNetWorkList.size())
		{
			CString strMsg;
			strMsg = QString(g_sLangTxt_networkcards.arg(nCurSelCard).arg(m_oNetWorkList.size()));
			CLogPrint::LogString(XLOGLEVEL_INFOR,strMsg);
			
			return FALSE;
		}
	}


	long nIndex = strIP.ReverseFind('.');

	if (nIndex == -1)
	{
		CString strMsg;
		strMsg = QString(g_sLangTxt_validIP.arg(strIP));
		CLogPrint::LogString(XLOGLEVEL_INFOR,strMsg);

		return FALSE;
	}
	else if (!m_bUseScanLan)
	{
		return TRUE;
	}

	QNetworkInterface oCurNetInterface = m_oNetWorkList.at(nCurSelCard);
	CString strTmp;
	strTmp = strIP.left(nIndex+1);
	QString strCurName = ui->m_pNetCardSel_ComboBox->currentText();

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
		strMsg = QString(g_sLangTxt_cardlookup.arg(strCurName));
		CLogPrint::LogString(XLOGLEVEL_INFOR,strMsg);
		//AddRecord(strMsg);
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
		strMsg = QString(g_sLangTxt_modifyIP.arg(strIP));
		//(strMsg);
		return FALSE;
	}

	return TRUE;
}

CString QNetworkConfigWidget::GetValidIP(QNetworkInterface &oCurNetInterface)
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

void QNetworkConfigWidget::slot_changeLocalIPAddrSel(int nCurComboxIndex)
{
	CString strLocalIP;
	strLocalIP = ui->m_pLocalIP_ComboBox->currentText();

	if (strLocalIP.Find(".")>0)
	{
		m_oSttTestAppCfg.SetLocalIP(strLocalIP);
	}
}

BOOL QNetworkConfigWidget::IsIPExactness(CString strIP)
{
	QRegExp rx2("^(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$");
	if( !rx2.exactMatch(strIP) )
	{
		return FALSE;
	}
	
	return TRUE;
}

void QNetworkConfigWidget::slot_CancelClicked()
{
#ifdef _PSX_QT_LINUX_

#else

	if (m_pIpAdapterInfo)
	{
		delete []m_pIpAdapterInfo;
		m_pIpAdapterInfo =NULL;
	}
#endif

	//	ReleaseOnClose();
	close();
}
