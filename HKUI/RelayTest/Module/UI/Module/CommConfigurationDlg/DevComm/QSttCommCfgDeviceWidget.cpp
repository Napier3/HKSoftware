#include "QSttCommCfgDeviceWidget.h"
#include <QMessageBox>
#include "ui_PpSttIotEngineClientWidget.h"
#include "../CommCfg/QSttCommCfgMainDlg.h"
#include "../../CommonMethod/commonMethod.h"
#include "QSttCommCfgDeviceDlg.h"
#include "../../../../../../Module/OSInterface/QT/XMessageBox.h"
/*lijunqing 2024-7-13*/ //#include "../../../RemoteCtrl/SttMacroParaEditViewRemoteCtrl.h"
#include "../../../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../../../SoftKeyboard/SoftKeyBoard.h"
#endif
//extern void Global_SetLinuxDevIP(CString strIP, CString strMask);
//extern CString Global_GetPointTbFilePath();
extern CFont *g_pSttGlobalFont;

QSttCommCfgDeviceWidget::QSttCommCfgDeviceWidget(QWidget *parent)
: QPpSttIotEngineClientWidgetMain(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_pDvmTeleMeasureGrid = NULL;
	m_pDvmTeleParaCommGrid = NULL;
	//mpEditZoneNum = NULL;
	//mpBtnWriteZone = NULL;
	m_bCrtDasetIsTeleMeasure = FALSE;
	m_pRunProcedureReceiveDlg = NULL;
	initUI();
	InitDatas();
}

QSttCommCfgDeviceWidget::~QSttCommCfgDeviceWidget()
{

}

void QSttCommCfgDeviceWidget::initUI()
{
	//ReleaseUI();
	resize(900, 630);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	m_pDvmTeleMeasureGrid = new SttCDevCommTeleMeasureGrid(this);
	m_pDvmTeleMeasureGrid->InitGrid();

	m_pDatasetGrid->hide();

	ui->m_wndHorzLayOutArea->removeWidget(m_pDatasetGrid);
	ui->m_wndHorzLayOutArea->addWidget(m_pDvmTeleMeasureGrid,7);

	ui->m_btnConfigDevice->hide();
	ui->m_btnConnectDevice->hide();
	ui->m_btnCloseDevice->hide();
	ui->m_btnEnumDevice->hide();
	//ui->m_btnReadDataset->hide();
	//ui->m_btnWriteDataset->hide();
	//ui->m_btnReadZone->hide();
	ui->m_btnWriteZone->hide();
	ui->m_btnReset->hide();
	ui->m_btnStartRpt->hide();
	ui->m_btnStopReport->hide();

	ui->m_btnAddDevice->hide();
	ui->m_btnEnumLDevice->hide();
	ui->m_btnEnumDataset->hide();
	ui->m_btnOpenDvmFile->hide();
	ui->m_btnSaveDvmFile->hide();
	//====================================
	// 删除布局中的所有子控件 
	setInnertState();

	//ui->m_gridLayOutOptr=new QGridLayout(this);

//	QSttCommCfgDeviceDlg *pDevComWidet = new QSttCommCfgDeviceDlg(ui, this);
	ui->m_btnWriteDataset->setText(CString("写数据"));

	m_pBtnCmCfg = new QPushButton(this);
	m_pBtnCmCfg->setText(CString("通讯配置"));

	m_pBtnWriteZone = new QPushButton(this);
	m_pBtnWriteZone->setText(CString("修改定值区"));

	m_pLabelZoneNum = new QLabel(this);
	m_pLabelZoneNum->setText(CString("当前区号:"));

	m_pEditZoneNum = new QSttLineEdit(this);
	m_pEditZoneNum->setMaximumWidth(80);
	m_pEditZoneNum->setValidator(new QRegExpValidator(QRegExp("\\d+")));
	m_pEditZoneNum->setText("0");

	ui->m_gridLayOutOptr->addWidget(m_pBtnCmCfg, 0, 1, 1, 1);
	ui->m_gridLayOutOptr->addWidget(ui->m_btnReadDataset, 0, 2, 1, 1);
	ui->m_gridLayOutOptr->addWidget(ui->m_btnWriteDataset, 0, 3, 1, 1);

	ui->m_gridLayOutOptr->addWidget(ui->m_btnReadZone, 0, 4, 1, 1);
	ui->m_gridLayOutOptr->addWidget(m_pLabelZoneNum, 0, 5, 1, 1);
	ui->m_gridLayOutOptr->addWidget(m_pEditZoneNum, 0, 6, 1, 1);
	ui->m_gridLayOutOptr->addWidget(m_pBtnWriteZone, 0, 7, 1, 1);


	//20240320 暂时隐藏,功能未完善
	m_pBtnWriteZone->hide();
	m_pLabelZoneNum->hide();
	m_pEditZoneNum->hide();
	ui->m_btnReadZone->hide();


	connect(m_pBtnCmCfg, SIGNAL(clicked()), this, SLOT(slot_DevCommConfigBtnClicked()));
	connect(m_pBtnWriteZone, SIGNAL(clicked()), this, SLOT(slot_DevCommWriteZoneBtnClicked()));
	connect(this, SIGNAL(sig_FinishRunProcedure(QString)), this, SLOT(slot_FinishRunProcedure(QString)),Qt::QueuedConnection);

	EnableBtns();
	SetDialogFont();
}

void QSttCommCfgDeviceWidget::SetDialogFont()
{
	if (g_pSttGlobalFont == NULL)
	{
		return;
	}
	m_pDvmTreeCtrl->setFont(*g_pSttGlobalFont);
	ui->m_btnReadDataset->setFont(*g_pSttGlobalFont);
	ui->m_btnReadZone->setFont(*g_pSttGlobalFont);
	ui->m_btnWriteDataset->setFont(*g_pSttGlobalFont);

	m_pBtnWriteZone->setFont(*g_pSttGlobalFont);
	m_pEditZoneNum->setFont(*g_pSttGlobalFont);
	m_pBtnCmCfg->setFont(*g_pSttGlobalFont);
	m_pLabelZoneNum->setFont(*g_pSttGlobalFont);

	//mpBtnWriteZone->setFont(*g_pSttGlobalFont);
	//mpEditZoneNum->setFont(*g_pSttGlobalFont);
	//mpBtnCmCfg->setFont(*g_pSttGlobalFont);
	//mpLabelZoneNum->setFont(*g_pSttGlobalFont);

	//mpOK_PushButton->setFont(*g_pSttGlobalFont);
	//mpCancel_PushButton->setFont(*g_pSttGlobalFont);


}


void QSttCommCfgDeviceWidget::SaveDatasToLocalDvm(CPpSttIotDeviceClient *pIoTDevice)
{
	//QPpSttIotEngineClientWidget::SaveDatasToLocalDvm(pIoTDevice);
	
	CDvmDataset *pDataset = pIoTDevice->GetCurrDataset();

	if (pDataset == NULL)
	{
		return;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, pDataset->m_strID);
	CDvmDataset *pDsLocal = NULL;

	if (m_pDvmDevice != NULL)
	{
		pDsLocal = m_pDvmDevice->FindDatasetByPath(pDataset->m_strID);
	}

	if (pDsLocal == NULL)
	{
		return;
	}

	pDsLocal->UpdateDataValue(pDataset);
	pDsLocal->SetDataChange();

	if (m_bCrtDasetIsTeleMeasure)
	{
		if (m_pDvmTeleMeasureGrid != NULL)
		{
			m_pDvmTeleMeasureGrid->ShowDatas(pDsLocal);
		}
	}else
	{
		if (m_pDvmTeleParaCommGrid != NULL)
		{
			m_pDvmTeleParaCommGrid->ShowDatas(pDsLocal);
		}

	}

	//m_pDvmTeleMeasureGrid
}

void QSttCommCfgDeviceWidget::OnCommCommandMsg(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam,LPARAM lParam)
{
	if (lParam == engineCommFinish)
	{
		if (pIotDevice->m_strProcedureID == CMDID_writesetting)
		{
			emit sig_FinishRunProcedure(CMDID_writesetting);
		}
		else if (pIotDevice->m_strProcedureID == CMDID_writeena)
		{
			emit sig_FinishRunProcedure(CMDID_writeena);
		}
		else if (pIotDevice->m_strProcedureID == CMDID_writeenasel)
		{
			emit sig_FinishRunProcedure(CMDID_writeenasel);
		}
		else if (pIotDevice->m_strProcedureID == CMDID_writeenaoper)
		{
			emit sig_FinishRunProcedure(CMDID_writeenaoper);
		}
		else if (pIotDevice->m_strProcedureID == CMDID_writeenarevk)
		{
			emit sig_FinishRunProcedure(CMDID_writeenarevk);
		}
	}

	QPpSttIotEngineClientWidget::OnCommCommandMsg(pIotDevice, wParam, lParam);

	if (m_pPpSttIotEngineClientInterface != NULL)
	{
		m_pPpSttIotEngineClientInterface->OnCommCommandMsg(wParam,lParam);
	}
}

//void QSttCommCfgDeviceWidget::slot_OKClicked()
//{
//	close();
//}
//
//void QSttCommCfgDeviceWidget::slot_CancelClicked()
//{
//	close();
//}
void QSttCommCfgDeviceWidget::EnableBtns()
{
			ui->m_btnConfigDevice->setEnabled(false);
			//ui->m_btnConnectDevice->setEnabled(false);
			//ui->m_btnCloseDevice->setEnabled(true);
			ui->m_btnReadZone->setEnabled(true);
			ui->m_btnWriteZone->setEnabled(true);
// 	ui->m_btnReadDataset->setEnabled(true);
// 	ui->m_btnWriteDataset->setEnabled(true);


	if (m_pCurrSelDvmDataObj == NULL)
	{
		ui->m_btnWriteDataset->setEnabled(false);
		ui->m_btnReadDataset->setEnabled(false);
	}
	else
	{
		ui->m_btnWriteDataset->setEnabled(true);
		ui->m_btnReadDataset->setEnabled(true);
	}
}
//
//void QSttCommCfgDeviceCommDlg::EnableBtns()
//{
//	BOOL bIsDataset = FALSE;
//	BOOL bDatasetCanWrite = FALSE;
//	if (m_pCurrSelDvmDataObj != NULL)
//	{
//		UINT nClassID = m_pCurrSelDvmDataObj->GetClassID();
//		bIsDataset = ( nClassID == DVMCLASSID_CDVMDATASET);
//		if (bIsDataset)
//		{
//			bDatasetCanWrite = Px_DatasetCanWrite(m_pCurrSelDvmDataObj->m_strID);
//		}
//	}
//	//ui->m_btnConfigDevice->setEnabled(true);
//	//ui->m_btnReadDataset->setEnabled(bIsDataset);
//	//ui->m_btnWriteDataset->setEnabled(bIsDataset&&bDatasetCanWrite);
//	//ui->m_btnReadZone->setEnabled(true);
//	//ui->m_btnWriteZone->setEnabled(true);
//
//	if ((m_pPpDeviceClient==NULL) || (m_pPpDeviceClient->m_pPpDevice == NULL))
//	{
//		//ui->m_btnConfigDevice->setEnabled(true);
//		ui->m_btnReadDataset->setEnabled(false);
//		ui->m_btnWriteDataset->setEnabled(false);
//		ui->m_btnReadZone->setEnabled(false);
//		ui->m_btnWriteZone->setEnabled(false);
//		//mpEditZoneNum->setEnabled(false);
//		//mpBtnWriteZone->setEnabled(false);
//		return;
//	}
//	if (m_pPpDeviceClient->m_pPpDevice->IsConnectIotServerSucc())
//	{
//		if (m_pPpDeviceClient->m_pPpDevice->IsConnectSuccessful())
//		{
//			ui->m_btnConfigDevice->setEnabled(false);
//			//ui->m_btnConnectDevice->setEnabled(false);
//			//ui->m_btnCloseDevice->setEnabled(true);
//			ui->m_btnReadZone->setEnabled(true);
//			ui->m_btnWriteZone->setEnabled(true);
//			ui->m_btnReadDataset->setEnabled(bIsDataset);
//			ui->m_btnWriteDataset->setEnabled(bIsDataset && bDatasetCanWrite);
//		//	mpEditZoneNum->setEnabled(true);
//		//	mpBtnWriteZone->setEnabled(true);
//		}
//		else
//		{
//			//ui->m_btnConfigDevice->setEnabled(true);
//			//ui->m_btnConnectDevice->setEnabled(true);
//			ui->m_btnReadZone->setEnabled(false);
//			ui->m_btnWriteZone->setEnabled(false);
//			ui->m_btnReadDataset->setEnabled(false);
//			ui->m_btnWriteDataset->setEnabled(false);
//			//mpEditZoneNum->setEnabled(false);
//			//mpBtnWriteZone->setEnabled(false);
//		}
//	}
//	else
//	{
//		//ui->m_btnConfigDevice->setEnabled(true);
//		//ui->m_btnConnectDevice->setEnabled(true);
//		ui->m_btnReadDataset->setEnabled(false);
//		ui->m_btnWriteDataset->setEnabled(false);
//		ui->m_btnReadZone->setEnabled(false);
//		ui->m_btnWriteZone->setEnabled(false);
//		//mpEditZoneNum->setEnabled(false);
//		//mpBtnWriteZone->setEnabled(false);
//	}
//}

void QSttCommCfgDeviceWidget::EnableBtns_Connecting_Closeing()
{
	//ui->m_btnConfigDevice->setEnabled(true);
	ui->m_btnReadDataset->setEnabled(true);
	ui->m_btnWriteDataset->setEnabled(true);
	ui->m_btnReadZone->setEnabled(true);
	//ui->m_btnWriteZone->setEnabled(true);
}

void QSttCommCfgDeviceWidget::InitDatas()
{
	OpenPpSttCommConfigFile();
}



void QSttCommCfgDeviceWidget::OpenPpSttCommConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");

	CPpSttCommConfig oCommConfig;
	if (! oCommConfig.OpenCommConfigFile(strFile) )
	{
		return;
	}
	CString strPpXmlFile = oCommConfig.Get_PpxmlFile();
	if (strPpXmlFile.IsEmpty())
	{
		QMessageBox oChkBox(QMessageBox::Information, CString("提示"), CString("ppxml-file配置参数空,请首先去通讯配置界面选择"), QMessageBox::Ok);
		//使 MyBox 对话框显示s
		oChkBox.exec();
		return;
	}
	int nPos = strPpXmlFile.ReverseFind('.');
	if (nPos > 0)
	{
		strPpXmlFile=strPpXmlFile.Left(nPos);
	}
	CString strDvmFile = oCommConfig.Get_DvmFile();
	if (strDvmFile.IsEmpty())
	{
		QMessageBox oChkBox(QMessageBox::Information, CString("提示"), CString("dvm-file配置参数空,请首先去通讯配置界面选择"), QMessageBox::Ok);
		//使 MyBox 对话框显示s
		oChkBox.exec();
		return;
	}
	//绝对路径
	CString strPointTbPath = Global_GetPointTbFilePath();
	strDvmFile.replace(strPointTbPath,"",Qt::CaseInsensitive);

	//CString dvmFilePath = strPointTbPath + strPpXmlFile +CString("/")+ strDvmFile;
	CString dvmFilePath = strPointTbPath + strDvmFile;
	CString strPointSubPath = strPointTbPath + strPpXmlFile;
	if (!::IsFileExist(dvmFilePath))
	{
		return; 
	}
	// yuanting 
	//m_pDvmDevice = new CDvmDevice();
	if(m_pDvmDevice == NULL)
	{
	m_pDvmDevice = new CDvmDevice();
	}
	else
	{
		m_pDvmDevice->DeleteAll();
	}

	m_pDvmDevice->OpenXmlFile(dvmFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
	ShowDvmDevice(m_pDvmDevice);
	
	//导入新的点表文件清空表格数据
	m_pDvmTeleMeasureGrid->clearContents();
	m_pDvmTeleMeasureGrid->setRowCount(0);

	SetLinuxDeviceIP(&oCommConfig);
	NewPpSttIotDeviceClient(&oCommConfig, m_pDvmDevice);
}

bool QSttCommCfgDeviceWidget::SetCurrentCommInfo(CPpSttCommConfig &oCommConfig)
{
	CString strPpXmlFile = oCommConfig.Get_PpxmlFile();
	if (strPpXmlFile.IsEmpty())
	{
		QMessageBox oChkBox(QMessageBox::Information, CString("提示"), CString("ppxml-file配置参数空,请首先去通讯配置界面选择"), QMessageBox::Ok);
		oChkBox.exec();
		return false;
	}

	CString strDvmFile = oCommConfig.Get_DvmFile();
	if (strDvmFile.IsEmpty())
	{
		QMessageBox oChkBox(QMessageBox::Information, CString("提示"), CString("dvm-file配置参数空,请首先去通讯配置界面选择"), QMessageBox::Ok);
		oChkBox.exec();
		return false;
	}

	//绝对路径
	CString strPointTbPath = Global_GetPointTbFilePath();
	strDvmFile.replace(strPointTbPath,"",Qt::CaseInsensitive);

	CString dvmFilePath = strPointTbPath + strDvmFile;
	if (!::IsFileExist(dvmFilePath))
	{
		return false; 
	}
	if(m_pDvmDevice == NULL)
	{
		m_pDvmDevice = new CDvmDevice();
	}
	else
	{
		m_pDvmDevice->DeleteAll();
	}

	m_pDvmDevice->OpenXmlFile(dvmFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
	ShowDvmDevice(m_pDvmDevice);
	SetLinuxDeviceIP(&oCommConfig);
	NewPpSttIotDeviceClient(&oCommConfig, m_pDvmDevice);
	return true;
}

bool QSttCommCfgDeviceWidget::CloseCurrentConnect()
{
	if(m_pPpDeviceClient == NULL)
	{
		return false;
	}
	DeleteIotDevice(m_pPpDeviceClient);
	return true;
}

void QSttCommCfgDeviceWidget::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	m_pCurrSelDvmDataObj = pSelObj;
	ShowTelemesureTable(pSelObj);
	EnableBtns();
}

BOOL QSttCommCfgDeviceWidget::OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)
{
	ShowTelemesureTable(pSelObj);
	EnableBtns();

	return TRUE;
}

void QSttCommCfgDeviceWidget::ShowTelemesureTable(CExBaseObject *pSelObj)
{
	m_bCrtDasetIsTeleMeasure = FALSE;
	if (pSelObj->GetClassID() == DVMCLASSID_CDVMDATASET)
	{
		CDvmDataset*pSelDataset = (CDvmDataset*)pSelObj;
		CString strDasetID = pSelDataset->m_strID;
		strDasetID.MakeUpper();	
		int nPos = strDasetID.Find(CString("AIN")); //dsRelayAin 
		//int nPos=pSelDataset->m_strID.Find(CString("dsRelayAin"));
		if (nPos < 0) //非遥测界面
		{
			m_bCrtDasetIsTeleMeasure = FALSE;
			//ui->m_wndHorzLayOutArea->removeWidget(m_pDatasetGrid);
			if (m_pDvmTeleParaCommGrid == NULL)
			{
				m_pDvmTeleParaCommGrid = new SttCDevCommParaCommGrid(this); 
				m_pDvmTeleParaCommGrid->InitGrid();
			}
			if ((m_pDvmTeleMeasureGrid != NULL) && (ui->m_wndHorzLayOutArea->indexOf(m_pDvmTeleMeasureGrid) >= 0))
			{
				int resOther = ui->m_wndHorzLayOutArea->indexOf(m_pDvmTeleMeasureGrid);
				ui->m_wndHorzLayOutArea->removeWidget(m_pDvmTeleMeasureGrid);
			}
			if (ui->m_wndHorzLayOutArea->indexOf(m_pDvmTeleParaCommGrid) < 0)
			{
				ui->m_wndHorzLayOutArea->addWidget(m_pDvmTeleParaCommGrid, 7);
			}	
			m_pDvmTeleParaCommGrid->ShowDatas((CExBaseList*)pSelObj);

			//int testidx=ui->m_wndHorzLayOutArea->indexOf(m_pDvmTeleParaCommGrid);
			//int testaa=testidx;


		}else //遥测dataset页面
		{
			m_bCrtDasetIsTeleMeasure = TRUE;
			//ui->m_wndHorzLayOutArea->removeWidget(m_pDatasetGrid);
			if ((m_pDvmTeleParaCommGrid != NULL) && (ui->m_wndHorzLayOutArea->indexOf(m_pDvmTeleParaCommGrid) >= 0))
			{
				ui->m_wndHorzLayOutArea->removeWidget(m_pDvmTeleParaCommGrid);
			}
			if (ui->m_wndHorzLayOutArea->indexOf(m_pDvmTeleMeasureGrid) < 0)
			{
				ui->m_wndHorzLayOutArea->addWidget(m_pDvmTeleMeasureGrid, 7);
			}
			if (m_pDvmTeleParaCommGrid != NULL)
			{
				delete m_pDvmTeleParaCommGrid;
				m_pDvmTeleParaCommGrid=NULL;
			}
			m_pDvmTeleMeasureGrid->ShowDatas((CExBaseList*)pSelObj);
		}
	}

}

void QSttCommCfgDeviceWidget::setInnertState()
{
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnStartRpt);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnReset);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnReadZone);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnWriteZone);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnReadDataset);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnConnectDevice);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnWriteDataset);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnCloseDevice);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnConfigDevice);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnStopReport);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnAddDevice);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnEnumDevice);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnEnumLDevice);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnEnumDataset);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnOpenDvmFile);
	ui->m_gridLayOutOptr->removeWidget(ui->m_btnSaveDvmFile);

	//m_wndVertOptrLayout->addLayout(m_gridLayOutOptr);
}

void QSttCommCfgDeviceWidget::slot_DevCommConfigBtnClicked()
{
	QSttCommCfgMainDlg oSttCommCfgMainDlg(this);
	oSttCommCfgMainDlg.UpdateConnectStateUI(IsConnectSuccessful());
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oSttCommCfgMainDlg);
	oSttCommCfgMainDlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	oSttCommCfgMainDlg.exec();
#endif

	/*QSttCommCfgMainDlg oSttCommCfgMainDlg;
	oSttCommCfgMainDlg.UpdateConnectStateUI(IsConnectSuccessful());
	oSttCommCfgMainDlg.exec();*/

	OpenPpSttCommConfigFile();
	g_theTestCntrFrame->UpdateDeviceModelRef();//更新设备数据模型关联信息
}

void QSttCommCfgDeviceWidget::slot_DevCommWriteZoneBtnClicked()
{
	long nZoneIndex = (long)m_pEditZoneNum->text().toInt();

	if (m_pPpDeviceClient == NULL)
	{
		return;
	}

	m_pPpDeviceClient->Initialize_Cmd();
//	m_pPpDeviceClient->WriteZone(nZoneIndex);
}

BOOL QSttCommCfgDeviceWidget::IsRemoteCtrlRunProcedure(const QString &strID)
{
	if (strID == CMDID_writeena)
	{
		return TRUE;
	}
	else if (strID == CMDID_writeenasel)
	{
		return TRUE;
	}
	else if (strID == CMDID_writeenaoper)
	{
		return TRUE;
	}
	else if (strID == CMDID_writeenarevk)
	{
		return TRUE;
	}

	return FALSE;
}

void QSttCommCfgDeviceWidget::slot_FinishRunProcedure(QString strID)
{
	CString strMsg,strTitile;
	strTitile = "提示";
	long nHasError = 0;

	if (m_pPpDeviceClient != NULL)
	{
		if (m_pPpDeviceClient->GetRunProcedureRltValue(ATTRID_ERRINFO,nHasError))
		{
			if ((m_pRunProcedureReceiveDlg != NULL)
				&&IsRemoteCtrlRunProcedure(strID))
			{
                /*lijunqing 2024-7-13*/ //((QSttMacroParaEditViewRemoteCtrl*)m_pRunProcedureReceiveDlg)->UpdateExeResult(nHasError);
			}
		}
	}

	if (strID == CMDID_writesetting)
	{
		strMsg = "修改数据成功.";
	}
	else if (strID == CMDID_writeena)
	{
		if (nHasError)
		{
			strMsg = "遥控执行失败.";
		} 
		else
		{
			strMsg = "遥控执行成功.";
		}
	}
	else if (strID == CMDID_writeenasel)
	{
		if (nHasError)
		{
			strMsg = "遥控预置失败.";
		} 
		else
		{
			strMsg = "遥控预置成功.";
		}
	}
	else if (strID == CMDID_writeenaoper)
	{
		if (nHasError)
		{
			strMsg = "遥控执行失败.";
		} 
		else
		{
			strMsg = "遥控执行成功.";
		}
	}
	else if (strID == CMDID_writeenarevk)
	{
		if (nHasError)
		{
			strMsg = "遥控撤销失败.";
		} 
		else
		{
			strMsg = "遥控撤销成功.";
		}
	}	
	else
	{
		return;
	}

	CXMessageBox::information(this, strTitile, strMsg);
}


void QSttCommCfgDeviceWidget::SetLinuxDeviceIP(CPpSttCommConfig *pCommConfig)
{
#ifdef _PSX_QT_LINUX_
	CString strLocalIp;
	CString strSubMask = "255.255.255.0";
	CString strPpXmlFile = pCommConfig->Get_PpxmlFile();
//	QSttCommCfgMainDlg dlg;// = new QSttCommCfgMainDlg();
    CDvmData* pDvmData = Global_OpenPpxmlFile(strPpXmlFile);
	if (pDvmData != NULL)
	{
		CDvmValue *pDvmValueLocalIp = (CDvmValue*)pDvmData->FindByID(CString("local-ip"));
		CDvmValue *pDvmValueLocalPort = (CDvmValue*)pDvmData->FindByID(CString("SubnetMask"));
		if ((pDvmValueLocalIp != NULL) && (pDvmValueLocalPort != NULL))
		{
			strLocalIp = pDvmValueLocalIp->m_strValue;
			strSubMask = pDvmValueLocalPort->m_strValue;
		}
	}
	if (strLocalIp.IsEmpty())
	{
		strLocalIp = pCommConfig->TcpClient_Get_LocalIP();
	}
	Global_SetLinuxDevIP(strLocalIp,  strSubMask);
#endif
}


