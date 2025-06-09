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

//extern void Global_SetLinuxDevIP(CString strIP, CString strMask);
extern CFont *g_pSttGlobalFont;


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

	QStringList astrIP, astrMask;

#ifdef _PSX_QT_LINUX_
	int nErrCode = stt_net_get_ip(astrIP, astrMask);
	if (!astrIP.contains(strIP))
	{
		astrIP.append(strIP);
		astrMask.append(strMask);
		int nBeginIndex = astrIP.size();
		stt_net_set_ip(astrIP, astrMask, nBeginIndex);
	}

#endif

}

//解析规约模板文件
CDvmData* Global_OpenPpxmlFile(CString srFilePath)
{
	CDvmData *pDataRes = NULL;

	CXmlRWDocBase* pXmlDocPtr = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);

	if (pXmlDocPtr == NULL)
	{
		return NULL;
	}
	try
	{
		if ( !xml_OpenFile(pXmlDocPtr, srFilePath) )
		{
			delete pXmlDocPtr;
			pXmlDocPtr = NULL;
			return NULL;
		}
	}
	catch (...)
	{
		delete pXmlDocPtr;
		pXmlDocPtr = NULL;
		return NULL;
	}
	CXmlRWNodeBase*  pXmlRootptr = pXmlDocPtr->GetDocNode();
	if (pXmlRootptr == NULL)
	{
		return NULL;
	}
	CXmlRWNodeBase* oNodeRoot = pXmlRootptr->GetChildNode(CString("pp-template"));
	if (oNodeRoot == NULL)
	{
		return NULL;
	}
	CXmlRWNodeBase* oNodeComCfg = oNodeRoot->GetChildNode(CString("comm-config"));
	if (oNodeComCfg == NULL)
	{
		return NULL;
	}
	CXmlRWNodeBase* oNodeNet = oNodeComCfg->GetChildNode(CString("net"));
	CXmlRWNodeBase* oNodeSerial = oNodeComCfg->GetChildNode(CString("serial"));
	if (oNodeNet != NULL)
	{
		CXmlRWNodeBase* oNodeTcpClient = oNodeNet->GetChildNode(CString("tcp-client"));
		if ( oNodeTcpClient != NULL )
		{
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
		}
	}else if (oNodeSerial != NULL) 
	{
		//<serial port_number="2" baud-rate="9600" byte-size="8" stop-bit="1" parity="0">
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
	}
	return pDataRes;
}


QSttCommCfgMainDlg::QSttCommCfgMainDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setWindowTitle(CString("通讯配置"));
	m_pPpxmlFileData = NULL;
	m_pProproTemplate_ComboBox = NULL;
	m_pPointFile_ComboBox = NULL;
	m_pConnect_PushButton = NULL;
	m_pDevAddrDvmDevice = NULL;
	m_bNetTableSave = FALSE;
	m_bSerialTableSave = FALSE;
	m_nConnectStateIndex = 0;
	m_bIsSaveFlag = false;
	initUI();
}

QSttCommCfgMainDlg::~QSttCommCfgMainDlg()
{

}

//Dialog初始化UI
void QSttCommCfgMainDlg::initUI()
{
	//ReleaseUI();
	resize(800, 630);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

  	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  	sizePolicy.setHorizontalStretch(30);
  	sizePolicy.setVerticalStretch(30);
	m_pCommCfgDevcieAttrsGrid = new SttCCommCfgDeviceAttrsGrid(this);
	m_pCommCfgDevcieAttrsGrid->InitGrid();
	
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
	pAllVLayout->addWidget(m_pCommCfgDevcieAttrsGrid);
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

	connect(m_pCommCfgDevcieAttrsGrid, SIGNAL(sig_ChangedDevAddr(long)), this, SLOT(slot_ChangedDevAddr(long)));
	connect(m_pCommCfgDevcieAttrsGrid, SIGNAL(sig_ChangedNetTable()), this, SLOT(slot_ChangedNetTable()));
	connect(m_pCommCfgDevcieAttrsGrid, SIGNAL(sig_ChangedSerialTable()), this, SLOT(slot_ChangedSerialTable()));

	SetDialogFont();
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
	if(m_nConnectStateIndex == 2)
	{
		QSttCommCfgDeviceWidget *pPpSttIotEngineClientWidgetMain = NULL;
		//断开连接
		if(g_theTestCntrFrame->m_pEngineClientWidget != NULL)
		{
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
		m_nConnectStateIndex = 2;
	} 
	else
	{
		strMsg = "连接";
		m_nConnectStateIndex = 0;
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
		m_nConnectStateIndex = 0;
		UpdateConnectStateUI(0);
		break;

	case engineConnectDeviceSuccessful:
		m_nConnectStateIndex++;

		if (m_nConnectStateIndex == 2)//忽略第一次连接成功状态
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
	if(m_nConnectStateIndex == 2)
	{
		//断开连接
		if(g_theTestCntrFrame->m_pEngineClientWidget != NULL)
		{
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
			}
		}
		return;
	}
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
		nRet = pPpSttIotEngineClientWidgetMain->ConnectDevice();
		if (nRet< 0)//此命令,需要等待实际的返回结果
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
	QSttCommCfgDeviceWidget *pPpSttIotEngineClientWidgetMain = NULL;
	if(m_nConnectStateIndex == 2)
	{
		//断开连接
		if(g_theTestCntrFrame->m_pEngineClientWidget != NULL)
		{
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
		return;
	}

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
	
	if (m_pPpxmlFileData == NULL)
	{
		return false;
	}
	CString strLocalIp,strSubnet;
	CDvmValue *pVlSubnet = (CDvmValue*)m_pPpxmlFileData->FindByID("SubnetMask");
	if (pVlSubnet != NULL)
	{
		strSubnet = pVlSubnet->m_strValue;
	}
	CDvmValue *pVlLocIp = (CDvmValue*)m_pPpxmlFileData->FindByID("local-ip");
	if (pVlLocIp != NULL)
	{
		strLocalIp = pVlLocIp->m_strValue;
	}
	Global_SetLinuxDevIP(strLocalIp,strSubnet);
	SaveTcpclientDataToCfgXml();
	return true;
}

//确定按钮槽函数
void QSttCommCfgMainDlg::slot_OKClicked()
{
/*	QString pCrtProtTxt = m_pProproTemplate_ComboBox->currentText();
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
	}
	if (m_bNetTableSave)
	{
		SaveNetTableProtolFile(m_strProproTemplatePath);
	}

	if (m_pPpxmlFileData == NULL)
	{
		return;
	}
	CString strLocalIp,strSubnet;
	CDvmValue *pVlSubnet = (CDvmValue*)m_pPpxmlFileData->FindByID("SubnetMask");
	if (pVlSubnet != NULL)
	{
		strSubnet = pVlSubnet->m_strValue;
	}
	//pGridCrt->ModifyTestDeviceIP(pCell->text(), strSubnet);
	CDvmValue *pVlLocIp = (CDvmValue*)m_pPpxmlFileData->FindByID("local-ip");
	if (pVlLocIp != NULL)
	{
		strLocalIp = pVlLocIp->m_strValue;
		//pGridCrt->ModifyTestDeviceIP(strIp,pCell->text());
	}
	Global_SetLinuxDevIP(strLocalIp,strSubnet);

	//SttCCommCfgDeviceAttrsGrid::ModifyTestDeviceIP(strLocalIp,strSubnet);
	//m_pCommCfgDevcieAttrsGrid->ModifyTestDeviceIP(strLocalIp,strSubnet);
	SaveTcpclientDataToCfgXml();
	*/

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
	CString strProtPath = Global_GetProtolTemplPath();
	CString strFile  = strProtPath + upStrPpXmlFile + CString(".ppxml");
	CDvmData *pDvmData = Global_OpenPpxmlFile(strFile);
	if (pDvmData == NULL)
	{
		return;
	}
	m_pPpxmlFileData = pDvmData;
	m_strProproTemplatePath = strFile;

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
			CDvmValue* pDvmVlTable = (CDvmValue*)m_pPpxmlFileData->FindByID(CString("DeviceAddr"));
			pDvmVlTable->m_strValue = pDataAttr->m_strValue;
		}

	}

	m_pCommCfgDevcieAttrsGrid->ShowDatas(pDvmData);
	/////////////////////////////////////////
	BOOL bIsSerial = FALSE;
	if (pDvmData != NULL)
	{
		int nPos = pDvmData->m_strID.Find(CString("serials"));
		if (nPos >= 0)
		{
			bIsSerial = TRUE;
		}
	}
	if (bIsSerial)
	{
		m_pCommCfgDevcieAttrsGrid->InitData(pDvmData);
	}
	else
	{
		m_pCommCfgDevcieAttrsGrid->RemoveAllRowCellWgtInSerial();
	}
	//////////////////////////////////////////////
	m_pCommCfgDevcieAttrsGrid->ShowDatas(pDvmData);
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
	CString strPpXmlFile = oCommConfig.Get_PpxmlFile();
	//绝对路径：
	CString strTemplPath = Global_GetProtolTemplPath();
	strPpXmlFile.replace(strTemplPath,"",Qt::CaseInsensitive);

	CString strDvmFile = oCommConfig.Get_DvmFile();
	//绝对路径
	CString strPointFilePath = Global_GetPointTbFilePath();
	strDvmFile.replace(strPointFilePath,"",Qt::CaseInsensitive);

	if (iModType == CFMDLG_COMBO_TYPE_PPXMLFILE)
	{
		upStrPpXmlFile = strPpXmlFile;
		upStrDvmFile = strPpXmlFile;
	}
	else if (iModType == CFMDLG_COMBO_TYPE_DVMFILE)
	{
		upStrPpXmlFile = strDvmFile;
		upStrDvmFile = strDvmFile;
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
	CString strPpXmlFile = oCommConfig.Get_PpxmlFile();
	CString strDvmFile = oCommConfig.Get_DvmFile();

	if (iModType == CFMDLG_COMBO_TYPE_PPXMLFILE)
	{
		//绝对路径：
		CString strTemplPath = Global_GetProtolTemplPath();
		upStrPpXmlFile = strTemplPath + upStrPpXmlFile;
		
		oCommConfig.Set_PpXmlFile(upStrPpXmlFile);
		oCommConfig.SaveCommConfigFile(strFile);
	}
	else if (iModType == CFMDLG_COMBO_TYPE_DVMFILE)
	{
		//绝对路径：
		CString strPointFilePath = Global_GetPointTbFilePath();
		upStrDvmFile = strPointFilePath  + upStrDvmFile;;
		
		oCommConfig.Set_DvmFile(upStrDvmFile);
		oCommConfig.SaveCommConfigFile(strFile);
	}

}

//保存规约文件串口内容
void QSttCommCfgMainDlg::SaveSerialTableProtolFile(CString strPpXmlFile)
{
	if (m_pPpxmlFileData == NULL)
	{
		return;
	}

	CDvmValue *pSerialValPortNum = (CDvmValue*)m_pPpxmlFileData->FindByID(CString("port_number"));
	CString valuePortNo = pSerialValPortNum->m_strValue;
	CDvmValue *pSerialValBaudRate = (CDvmValue*)m_pPpxmlFileData->FindByID(CString("baud-rate"));
	CString valueBaudRate = pSerialValBaudRate->m_strValue;
	CDvmValue *pSerialValByteSize = (CDvmValue*)m_pPpxmlFileData->FindByID(CString("byte-size"));
	CString valueByteSize = pSerialValByteSize->m_strValue;
	CDvmValue *pSerialValStopBit = (CDvmValue*)m_pPpxmlFileData->FindByID(CString("stop-bit"));
	CString valueStopBit = pSerialValStopBit->m_strValue;
	CDvmValue *pSerialValParity = (CDvmValue*)m_pPpxmlFileData->FindByID(CString("parity"));
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

}

//保存规约文件网口内容
void QSttCommCfgMainDlg::SaveNetTableProtolFile(CString strPpXmlFile)
{
	if (m_pPpxmlFileData == NULL)
	{
		return;
	}
	CDvmValue *pDvmValueLocalIp = (CDvmValue*)m_pPpxmlFileData->FindByID(CString("local-ip"));
	if (pDvmValueLocalIp == NULL)
	{
		return;
	}
	CString valueLocalIp = pDvmValueLocalIp->m_strValue;
	CDvmValue *pDvmValueLocalPort = (CDvmValue*)m_pPpxmlFileData->FindByID(CString("local-port"));
	CString valueLocalPort = pDvmValueLocalPort->m_strValue;
	CDvmValue *pDvmValueRemoteIp= (CDvmValue*)m_pPpxmlFileData->FindByID(CString("remote-ip"));
	CString valueRemoteIp = pDvmValueRemoteIp->m_strValue;
	CDvmValue *pDvmValueRemotePort= (CDvmValue*)m_pPpxmlFileData->FindByID(CString("remote-port"));
	CString valueRemotePort = pDvmValueRemotePort->m_strValue;

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
	//CXmlRWNodeBase* oNodeSerial = oNodeComCfg->GetChildNode(CString("serial"));
	if (oNodeNet != NULL)
	{
		CXmlRWNodeBase* oNodeTcpClient = oNodeNet->GetChildNode(CString("tcp-client"));
		if ( oNodeTcpClient != NULL )
		{
			oNodeTcpClient->xml_SetAttributeValue(L"local-ip", valueLocalIp);
			oNodeTcpClient->xml_SetAttributeValue(L"local-port", valueLocalPort);
			CString valueClientIp;
			//oNodeTcpClient->xml_SetAttributeValue(L"client-ip", valueClientIp);
			oNodeTcpClient->xml_SetAttributeValue(L"remote-ip", valueRemoteIp);
			oNodeTcpClient->xml_SetAttributeValue(L"remote-port", valueRemotePort);
			
		}
	}

	pXmlDocPtr->SaveXml(strPpXmlFile);

}

//保存规约文件网口的TcpClient数据
void QSttCommCfgMainDlg::SaveTcpclientDataToCfgXml()
{
	CDvmValue *pDvmValueLocalIp = (CDvmValue*)m_pPpxmlFileData->FindByID(CString("local-ip"));
	if (pDvmValueLocalIp == NULL)
	{
		return;
	}
	CString valueLocalIp = pDvmValueLocalIp->m_strValue;
	CDvmValue *pDvmValueLocalPort = (CDvmValue*)m_pPpxmlFileData->FindByID(CString("local-port"));
	CString valueLocalPort = pDvmValueLocalPort->m_strValue;
	CDvmValue *pDvmValueRemoteIp= (CDvmValue*)m_pPpxmlFileData->FindByID(CString("remote-ip"));
	CString valueRemoteIp = pDvmValueRemoteIp->m_strValue;
	CDvmValue *pDvmValueRemotePort= (CDvmValue*)m_pPpxmlFileData->FindByID(CString("remote-port"));
	CString valueRemotePort = pDvmValueRemotePort->m_strValue;

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");

	CPpSttCommConfig oCommConfig;
	if (!oCommConfig.OpenCommConfigFile(strFile) )
	{
		return;
	}
	CDvmData* pDvmData = oCommConfig.Get_TcpClient();
	if (pDvmData == NULL)
	{
		oCommConfig.Set_TcpClient();
	}
	oCommConfig.TcpClient_Set_RemotePort(valueRemotePort.toInt());
	oCommConfig.TcpClient_Set_RemoteIP(valueRemoteIp);
	oCommConfig.TcpClient_Set_LocalIP(valueLocalIp);
	oCommConfig.TcpClient_Set_LocalPort(valueLocalPort.toInt());

	oCommConfig.SaveCommConfigFile(strFile);

}
