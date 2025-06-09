#include "PpSttIotEngineClientWidget.h"
#include "ui_PpSttIotEngineClientWidget.h"

#include "../../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include "../../../../IotProtoServer/Module/SttPxCommCmdDef.h"

#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbWzdAi/GbWzdAiTool.h"
#include "qsttmmsbrcbctrlwidget.h"
#include "qsttzoneindexsetdlg.h"
#include "../../XLangResource_Native.h"
#include "XMessageBox.h"
#include <QProgressDialog>
#include "../../UI/SttTestCntrFrameBase.h"

extern CPpSttIotEngineClientApp *g_theIotEngineApp;
QPpSttIotEngineClientWidget *g_theEngineClientWidget = NULL;

//////////////////////////////////////////////////////////////////////////
//QPpSttIotEngineClientWidget
QPpSttIotEngineClientWidget::QPpSttIotEngineClientWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPpSttIotEngineClientWidget)
{
    m_pPpDeviceClient = NULL;
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowTitleHint;
	this->setWindowFlags(flags);

	m_pCurrSelDvmDataObj = NULL;

    m_pDvmTreeCtrl = new QSttPxEngineDvmTreeCtrl(NULL, this);
	m_pDatasetGrid = new CSttPxEngineDsEditGrid( this);
	m_pDatasetGrid->InitGrid();
	ui->m_wndHorzLayOutArea->addWidget(m_pDvmTreeCtrl, 3);
	ui->m_wndHorzLayOutArea->addWidget(m_pDatasetGrid, 7);

	//ui->m_btnAddDevice->setEnabled(true);
	ui->m_btnAddDevice->hide();
	//ui->m_btnEnumDevice->hide();
	ui->m_btnEnumLDevice->hide();
	ui->m_btnEnumDataset->hide();
	ui->m_btnOpenDvmFile->hide();
	ui->m_btnSaveDvmFile->hide();

	m_pDvmTreeCtrl->AttachOptrInterface(this);
    EnableBtns();
	SetPpIotEngineClientLang();
    m_oArrDelete.SetMaxCount(50);

	m_pDvmDevice = NULL;
	m_bDeviceCreateNew = FALSE;
	m_bDeviceNeedCheckEnas = FALSE;
	m_pCurrWriteDataset = NULL;
	m_bCloseDeviceWhenRelease = FALSE;

	m_lstSttParas.clear();
	m_bIsStarPkgMonitor = FALSE;
}

QPpSttIotEngineClientWidget::~QPpSttIotEngineClientWidget()
{
	if (m_bDeviceCreateNew && m_pDvmDevice != NULL)
	{
		delete m_pDvmDevice;
	}

	if (m_pPpDeviceClient != NULL)
	{
	m_pPpDeviceClient->DisConnectForClose(TRUE);
	delete m_pPpDeviceClient;
	m_pPpDeviceClient = NULL;
	}


    delete ui;
}

void QPpSttIotEngineClientWidget::SetPpIotEngineClientLang()
{
	ui->m_btnConfigDevice->setText(g_sLangTxt_Native_BtnConfigDevice);
	ui->m_btnConnectDevice->setText(g_sLangTxt_Native_BtnConnectDevice);
	ui->m_btnCloseDevice->setText(g_sLangTxt_SOE_Break);
	ui->m_btnEnumDevice->setText(g_sLangTxt_Native_BtnEnumDevice);
	ui->m_btnReadDataset->setText(g_sLangTxt_Native_BtnReadDataset);
	ui->m_btnWriteDataset->setText(g_sLangTxt_Native_BtnWriteDataset);
	ui->m_btnReadZone->setText(g_sLangTxt_Native_BtnReadZone);
	ui->m_btnWriteZone->setText(g_sLangTxt_Native_BtnWriteZone);
	ui->m_btnReset->setText(g_sLangTxt_Native_BtnReset);
	ui->m_btnStartRpt->setText(g_sLangTxt_Native_BtnStartRpt);
	ui->m_btnStopReport->setText(g_sLangTxt_Native_BtnStopReportr);
	ui->m_btnAddDevice->setText(g_sLangTxt_Native_BtnAddDevice);
	ui->m_btnEnumLDevice->setText(g_sLangTxt_Native_BtnEnumLDevice);
	ui->m_btnEnumDataset->setText(g_sLangTxt_Native_BtnEnumDataset);
	ui->m_btnOpenDvmFile->setText(g_sLangTxt_Native_BtnOpenDvmFile);
	ui->m_btnSaveDvmFile->setText(g_sLangTxt_Native_BtnSaveDvmFile);
}

void QPpSttIotEngineClientWidget::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	m_pCurrSelDvmDataObj = pSelObj;
	EnableBtns();
}

BOOL QPpSttIotEngineClientWidget::OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)
{
	if (pSelObj->GetClassID() == DVMCLASSID_CDVMDATASET)
	{
		m_pDatasetGrid->ShowDatas((CExBaseList*)pSelObj);
	}

	return TRUE;
}

void QPpSttIotEngineClientWidget::NewPpSttIotDeviceClient(CPpSttCommConfig *pCommConfig, CDvmDevice *pDvmDevice)
{
	m_bDeviceNeedCheckEnas = TRUE;  //第一次联机时，需要校验远方压板

	if (pDvmDevice == NULL)
	{
		m_pDvmDevice = new CDvmDevice();
		m_bDeviceCreateNew = TRUE;
		CString strDvmFile;
		strDvmFile =_P_GetLibraryPath();
		strDvmFile += pCommConfig->Get_DvmFile();
		m_pDvmDevice->OpenXmlFile(strDvmFile, CDataMngrXmlRWKeys::g_pXmlKeys);
		m_pDvmDevice->m_strID = pCommConfig->Get_DvmFile();
		ShowDvmDevice(m_pDvmDevice);
	}
	else
	{
		m_pDvmDevice = pDvmDevice;
		m_bDeviceCreateNew = FALSE;
	}
}

void QPpSttIotEngineClientWidget::OnCommCommandMsg(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam,LPARAM lParam)
{
    //m_pPpDeviceClient->m_pPpDevice->UnRegisterProcedureWndMsg(m_pPpDeviceClient->m_strProcedureID, (unsigned long)&m_oEngineMsgWnd, WM_COMM_COMMAND);

    if (lParam == engineCommError)
    {
            CLogPrint::LogString(XLOGLEVEL_TRACE, "engineCommError....");
			pIotDevice->FinishRunProcedure();
			m_pCurrWriteDataset = NULL;
			return;
    }
	
	//执行成功，显示相关联的数据集
	if (pIotDevice->m_strProcedureID == CMDID_dvmenum)
	{
		DvmEnumFinish(pIotDevice);
	}
	else
	{
		SaveDatasToLocalDvm(pIotDevice);
	}

	//通信命令执行成功，如果是写数据，则复归状态
	if (m_pCurrWriteDataset != NULL)
	{
		m_pCurrWriteDataset->SetDataChange(0);

		if (m_pCurrWriteDataset == m_pCurrSelDvmDataObj)
		{
			m_pDatasetGrid->UpdateChangeState();
		}
	}

	pIotDevice->FinishRunProcedure();
	m_pCurrWriteDataset = NULL;
}

extern QSttTestCntrFrameBase *g_theTestCntrFrame;

void QPpSttIotEngineClientWidget::OnEngineSystemMessage(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam, LPARAM lParam)
{
    if (pIotDevice == NULL)
    {
        return;
    }

    switch (lParam)
    {
    case engineConnectDeviceFailed:

		if (!m_bCloseDeviceWhenRelease)
		{
			DeleteIotDevice(pIotDevice);
		}

		if (g_theTestCntrFrame != NULL)
		{
			g_theTestCntrFrame->UpdateStatusBar_Btns(_T("DevConnectState"), _T("0"));
		}

        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Connect Device Failed"));
        break;

    case engineConnectDeviceSuccessful:

		if (g_theTestCntrFrame != NULL)
		{
			g_theTestCntrFrame->UpdateStatusBar_Btns(_T("DevConnectState"), _T("1"));
		}

		ReadEnasAfterConnectDevice();
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

void QPpSttIotEngineClientWidget::DvmEnumFinish(CPpSttIotDeviceClient *pIotDevice)
{
	m_pDvmDevice->DeleteAll();
	pIotDevice->GetDvmDevice(m_pDvmDevice);
	pIotDevice->ClearDvmDevice();
	ShowDvmDevice(m_pDvmDevice);

	//更新设备对象
#ifndef not_use_GbWzdAiTool
	g_theGbWzdAiTool->SetDvmDevice(m_pDvmDevice);
#endif
}

void QPpSttIotEngineClientWidget::ShowSoeReport(CPpSttIotDeviceClient *pIotDevice)
{
	CExBaseList oList;
	pIotDevice->AddCurrSoeReports(&oList);

	if (m_pCurrSelDvmDataObj == NULL)
	{
		oList.RemoveAll();
		return;
	}
	
	if (m_pCurrSelDvmDataObj->m_strID != g_strPxDataSetID[DSID_dsReport])
	{
		oList.RemoveAll();
		return;
	}

	m_pDatasetGrid->InsertDatas(&oList);
	oList.RemoveAll();
}

BOOL QPpSttIotEngineClientWidget::GetSoeReprt(CExBaseList *pList)
{
	if (m_pPpDeviceClient == NULL)
	{
		return FALSE;
	}

	long nCurrCount = pList->GetCount();
	m_pPpDeviceClient->AddCurrSoeReports(pList);
	return (pList->GetCount() > nCurrCount);
}

void QPpSttIotEngineClientWidget::ShowPkgSpy(CPpSttIotDeviceClient *pIotDevice)
{
	if (pIotDevice == NULL)
	{
		return;
	}

	if (pIotDevice->m_pPpDevice == NULL)
	{
		return;
	}

	CSttParas *pSttParas = (CSttParas*)pIotDevice->m_pPpDevice->m_oPkgSpyList.Read();

	if (pSttParas == NULL)
	{
		return;
	}

	if(m_bIsStarPkgMonitor)
	{
		CSttParas *pTemp = NULL;
		pTemp = (CSttParas*)pSttParas->Clone();
		if(pTemp)
		{
			m_lstSttParas.append(pTemp);
		}
	}
	

	CString strMsg,strValue;
	long nDir = 0;
	strValue = "";
	pSttParas->GetDataValue("Time",strValue);
	pSttParas->GetDataValue("Dir",nDir);

	if (nDir)
	{
		strMsg.Format("接收时间(%s),原始报文:",strValue.GetString());
	} 
	else
	{
		strMsg.Format("发送时间(%s),原始报文:",strValue.GetString());
	}

	pSttParas->GetDataValue("Pkg",strValue);
	strMsg += strValue;
	//CLogPrint::LogString(XLOGLEVEL_RESULT,strMsg); //chenling20240228 目前通讯时的报文在输出窗口显示，建议将报文放置报文监听界面，可以暂时不解析
	delete pSttParas;
// 	CString strPath;
// 	strPath = _P_GetBinPath();
// 	strPath += "PkgSpy.xml";
// 	pSttParas->SaveXmlFile(strPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

BOOL QPpSttIotEngineClientWidget::ConnectDevice()
{
	// 20240228chenling 闪退,需先判断是否为空
	if(m_pPpDeviceClient == NULL)
	{
		return FALSE;
	}
	emit sig_OnConfigDevice(&m_pPpDeviceClient->m_oCommConfig);
//	slot_OnConfigDevice(&m_pPpDeviceClient->m_oCommConfig);
	m_pPpDeviceClient->CreateDevice(0);
	BOOL nRet =  m_pPpDeviceClient->ConnectDevice();
	//EnableBtns();
	EnableBtns_Connecting_Closeing();
	return nRet;
}

void QPpSttIotEngineClientWidget::OnEngineEventMessage(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam, LPARAM lParam)
{
	if (pIotDevice == NULL)
	{
		return;
	}

	switch (lParam)
	{
	case EngineEvent_ID_DvmEnumFinish:
		DvmEnumFinish(pIotDevice);
		break;

	case EngineEvent_ID_Report:
		ShowSoeReport(pIotDevice);
		break;
	case EngineEvent_ID_PkgSpy://zhouhj  2024.1.23 调试使用
		ShowPkgSpy(pIotDevice);
		break;

	default:
		break;
	}

	EnableBtns();
}

void QPpSttIotEngineClientWidget::SaveDatasToLocalDvm(CPpSttIotDeviceClient *pIoTDevice)
{
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
    m_pDatasetGrid->ShowDatas(pDsLocal);
}

void QPpSttIotEngineClientWidget::SaveDatasToLocalDvm(CDvmDataset *pDataset)
{

}

void QPpSttIotEngineClientWidget::ShowDvmDevice(CDvmDevice *pDevice)
{
	pDevice->GetDataset(g_strPxDataSetID[PX_DSID_dsReport], g_strPxDataSetID[PX_DSID_dsReport]);
	m_pDvmTreeCtrl->ShowBaseList(pDevice);
}

void QPpSttIotEngineClientWidget::UpdateShowDvmDataset(CDvmDataset *pRptDataset)
{
	if (pRptDataset == NULL || m_pDvmDevice == NULL)
	{
		return;
	}

	CDvmDataset *pDsLocal = m_pDvmDevice->FindDatasetByPath(pRptDataset->m_strID);

	if (pDsLocal != NULL)
	{
		m_pDatasetGrid->ShowDatas(pDsLocal);
	}
}

void QPpSttIotEngineClientWidget::UpdateShowDvmDataset(const CString &strDsPath)
{
	if (m_pDvmDevice == NULL)
	{
		return;
	}

	CDvmDataset *pDsLocal = m_pDvmDevice->FindDatasetByPath(strDsPath);

	if (pDsLocal != NULL)
	{
		m_pDatasetGrid->ShowDatas(pDsLocal);
	}
}

void QPpSttIotEngineClientWidget::InitCommConfig(CPpSttCommConfig *pCommConfig)
{
    if (m_pPpDeviceClient == NULL)
    {
        return;
    }

    m_pPpDeviceClient->InitCommConfig(pCommConfig);
}

void QPpSttIotEngineClientWidget::DeleteIotDevice(CPpSttIotDeviceClient *pIotDevice)
{
    g_theIotEngineApp->Remove(pIotDevice);
	pIotDevice->DisConnectForClose(FALSE);
    m_oArrDelete.AddExBaseObject(pIotDevice);
	m_nTimerID = startTimer(1000);
}

void QPpSttIotEngineClientWidget::ReadEnasAfterConnectDevice()
{
	if (m_pDvmDevice == NULL)
	{
		return;
	}

	if (m_pPpDeviceClient == NULL)
	{
		return;
	}

	if (!m_bDeviceNeedCheckEnas)
	{
		return;
	}

	CStringArray oArray;
	m_bDeviceNeedCheckEnas = FALSE;
	ReadEnas_Ena(&oArray, _T("RelayEna"));//先处理保护压板数据集：对应处理远方软压板
	ReadEnas_Ena(&oArray, _T("RelayDin"));//先处理保护遥信数据集：对应处理远方硬压板

	long nCount = oArray.GetCount();
	CString strText;

	while(nCount > 0)
	{
		strText.AppendFormat(oArray.GetAt(nCount -1));
		nCount--;

		if (nCount > 0)
		{
			strText.AppendFormat("、");
		}
	}

	if ( !strText.IsEmpty())
	{
		CString strHead;
		strHead = _T("检测到以下远方压板处于退出状态：\r\n\r\n");
		strText = strHead + strText;
		strText.AppendFormat("。\r\n\r\n");
		strText.AppendFormat(_T("请先手动投入压板后，再进行测试！"));
		CXMessageBox::information(this, "警告", strText);
	}
}

//处理远方软压板：保护压板数据集：RelayEna
//处理远方硬压板，保护遥信数据集：RelayDin
void QPpSttIotEngineClientWidget::ReadEnas_Ena(CStringArray *pEnaArray, const CString &strDsKey)
{
	CExBaseList oListEnas;
	m_pDvmDevice->GetDatasetList(strDsKey, oListEnas);
	CString strText, strTitle, strMsg;

	if (strDsKey == _T("RelayEna"))
	{
		strTitle = _T("正在进行远方软压板校验，请稍后……");
		strMsg = _T("保护压板数据集");
	}
	else 
	{
		strTitle = _T("正在进行远方硬压板校验，请稍后……");
		strMsg = _T("保护遥信数据集");
	}

	if (oListEnas.GetCount() > 0)
	{	
		QProgressDialog oProgress;
		oProgress.setWindowModality(Qt::ApplicationModal);  //对本程序模态
		oProgress.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);  //隐藏右上角的“最大化”、“最小化”、“关闭”按钮
		oProgress.setCancelButtonText(NULL);
		oProgress.setWindowTitle(strTitle);
		oProgress.setRange(0, oListEnas.GetCount());
		oProgress.show();

		POS pos = oListEnas.GetHeadPosition();
		long nIndex = 0;

		while (pos != NULL)
		{
			oProgress.setValue(nIndex+1);
			strText.Format(_T("第%d个 / 共%d个"), nIndex + 1, oListEnas.GetCount());
			strText += strMsg;
			oProgress.setLabelText(strText);

			CDvmDataset *pDataset = (CDvmDataset *)oListEnas.GetNext(pos);
			m_pPpDeviceClient->ReadDataset((CDvmDataset*)pDataset);

			WaitForRunProcedureFinish();
			nIndex++;
		}
	}

	CheckRemoteEnas(&oListEnas, pEnaArray);
	oListEnas.RemoveAll();
}

void QPpSttIotEngineClientWidget::ReadAin(const CString &strDatasetPath)
{
	if (m_pPpDeviceClient == NULL)
	{
		return;
	}

	m_pPpDeviceClient->ReadAin(strDatasetPath);
}

void QPpSttIotEngineClientWidget::ReadSoe(const CString &strDatasetPath)
{
	if (m_pPpDeviceClient == NULL)
	{
		return;
	}

	m_pPpDeviceClient->ReadSoe(strDatasetPath);
}

BOOL QPpSttIotEngineClientWidget::Initialize_Cmd()
{
	if (m_pPpDeviceClient == NULL)
	{
		return FALSE;
	}

	return m_pPpDeviceClient->Initialize_Cmd();
}


BOOL QPpSttIotEngineClientWidget::WiriteEna_Sel(CDvmData *pData,const CString &strDatasetPath)
{
	if (m_pPpDeviceClient == NULL)
	{
		return FALSE;
	}

	return m_pPpDeviceClient->WriteSingleData(pData,strDatasetPath,CMDID_writeenasel);
}

BOOL QPpSttIotEngineClientWidget::WiriteEna_Oper(CDvmData *pData,const CString &strDatasetPath)
{
	if (m_pPpDeviceClient == NULL)
	{
		return FALSE;
	}

	return m_pPpDeviceClient->WriteSingleData(pData,strDatasetPath,CMDID_writeenaoper);
}

BOOL QPpSttIotEngineClientWidget::WiriteEna_Revoke(CDvmData *pData,const CString &strDatasetPath)
{
	if (m_pPpDeviceClient == NULL)
	{
		return FALSE;
	}

	return m_pPpDeviceClient->WriteSingleData(pData,strDatasetPath,CMDID_writeenarevk);
}

void QPpSttIotEngineClientWidget::WaitForRunProcedureFinish()
{
	if (m_pPpDeviceClient == NULL)
	{
		return;
	}

	CTickCount32 oTick;

	while (TRUE)
	{
		if (m_pPpDeviceClient->IsRunProcedureFinished())
		{
			break;
		}

		oTick.DoEvents(5);
	}
}

BOOL QPpSttIotEngineClientWidget::IsRunProcedureFinished()
{
	if (m_pPpDeviceClient == NULL)
	{
		return TRUE;
	}

	return m_pPpDeviceClient->IsRunProcedureFinished();
}

//检查是否有远方压板退出了
void QPpSttIotEngineClientWidget::CheckRemoteEnas(CExBaseList *pDvmDatasets, CStringArray *pArray)
{
	POS pos = pDvmDatasets->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset *)pDvmDatasets->GetNext(pos);
		POS posData = pDataset->GetHeadPosition();

		while (posData != NULL)
		{
			CDvmData *pData = (CDvmData *)pDataset->GetNext(posData);

			if (pData->m_strName.Find(_T("远方")) >= 0)
			{
				if (pData->m_strValue == _T("0"))
				{
					pArray->Add(pData->m_strName);
				}
			}
		}
	}
}

void QPpSttIotEngineClientWidget::CloseDevice_WhenRelease()
{
	if (m_pPpDeviceClient == NULL)
	{
		return;
	}

	if (m_pPpDeviceClient->m_pPpDevice == NULL)
	{
		return;
	}

	if (m_pPpDeviceClient->m_pPpDevice->IsConnectIotServerSucc())
	{
		if (m_pPpDeviceClient->m_pPpDevice->IsConnectSuccessful())
		{
			m_bCloseDeviceWhenRelease = TRUE;
			m_pPpDeviceClient->CloseDevice();
		}
	}
}

BOOL QPpSttIotEngineClientWidget::IsConnectSuccessful()
{
	if (m_pPpDeviceClient == NULL)
	{
		return FALSE;
	}

	if (m_pPpDeviceClient->m_pPpDevice == NULL)
	{
		return FALSE;
	}

	return m_pPpDeviceClient->m_pPpDevice->IsConnectSuccessful();
}

void QPpSttIotEngineClientWidget::AddOutputLog(QWidget*pOutputLog)
{
    ui->m_wndVertOptrLayout->insertWidget(2, pOutputLog);
    ui->m_wndVertOptrLayout->setStretch(1, 7);
    ui->m_wndVertOptrLayout->setStretch(2, 3);
}

void QPpSttIotEngineClientWidget::timerEvent(QTimerEvent *event)
{
     killTimer(m_nTimerID);
	 CPpSttIotDeviceClient *pIotDevice = (CPpSttIotDeviceClient*)m_oArrDelete.ReadCurr(1, TRUE);

     if (pIotDevice == NULL)
     {
         return;
     }

	 pIotDevice->DisConnectForClose(TRUE);
     //delete pIotDevice;
}


/*
// void QPpSttIotEngineClientWidget::slot_OnCommCommandMsg(int wParam,int lParam)
// {
//     OnCommCommandMsg(wParam, lParam);
// }
// 
// void QPpSttIotEngineClientWidget::slot_OnEngineSystemMessage(int wParam, int lParam)
// {
//     OnEngineSystemMessage(wParam, lParam);
// }
*/
void QPpSttIotEngineClientWidget::EnableBtns()
{
    if (m_pPpDeviceClient == NULL)
    {
        ui->m_btnConfigDevice->setEnabled(false);
        ui->m_btnConnectDevice->setEnabled(false);
        ui->m_btnCloseDevice->setEnabled(false);
        ui->m_btnReadDataset->setEnabled(false);
        ui->m_btnWriteDataset->setEnabled(false);
        ui->m_btnReadZone->setEnabled(false);
        ui->m_btnWriteZone->setEnabled(false);
        ui->m_btnReset->setEnabled(false);
        ui->m_btnStartRpt->setEnabled(false);
        ui->m_btnStopReport->setEnabled(false);
        ui->m_btnEnumDevice->setEnabled(false);
        ui->m_btnEnumLDevice->setEnabled(false);
        ui->m_btnEnumDataset->setEnabled(false);
        return;
    }

	BOOL bIsDataset=FALSE, bIsLDevice=FALSE, bIsDevice=FALSE, bHasRpt=FALSE, bDatasetCanWrite=FALSE;
	ui->m_btnOpenDvmFile->setEnabled(true);
	ui->m_btnSaveDvmFile->setEnabled(true);

	if (m_pCurrSelDvmDataObj != NULL)
	{
		UINT nClassID = m_pCurrSelDvmDataObj->GetClassID();
		bIsDataset = ( nClassID == DVMCLASSID_CDVMDATASET);
		bIsLDevice = ( nClassID == DVMCLASSID_CDVMLOGICDEVICE);
		bIsDevice = ( nClassID == DVMCLASSID_CDVMDEVICE);

		if (bIsDataset)
		{
			CDvmBrcb *pDvmBrcb = ((CDvmDataset*)m_pCurrSelDvmDataObj)->m_pDvmBrcb;
			bHasRpt = (pDvmBrcb != NULL) ? (pDvmBrcb->GetCount() > 0) : FALSE;
			bDatasetCanWrite = Px_DatasetCanWrite(m_pCurrSelDvmDataObj->m_strID);
		}
	}

    if (m_pPpDeviceClient->m_pPpDevice == NULL)
	{
        ui->m_btnConfigDevice->setEnabled(true);
		ui->m_btnConnectDevice->setEnabled(true);
		ui->m_btnCloseDevice->setEnabled(false);
        ui->m_btnReadDataset->setEnabled(false);
        ui->m_btnWriteDataset->setEnabled(false);
		ui->m_btnReadZone->setEnabled(false);
		ui->m_btnWriteZone->setEnabled(false);
        ui->m_btnReset->setEnabled(false);
        ui->m_btnStartRpt->setEnabled(false);
        ui->m_btnStopReport->setEnabled(false);
		ui->m_btnEnumDevice->setEnabled(false);
		ui->m_btnEnumLDevice->setEnabled(false);
		ui->m_btnEnumDataset->setEnabled(false);
		return;
	}
	
    if (m_pPpDeviceClient->m_pPpDevice->IsConnectIotServerSucc())
    {
        if (m_pPpDeviceClient->m_pPpDevice->IsConnectSuccessful())
        {
            ui->m_btnConfigDevice->setEnabled(false);
			ui->m_btnConnectDevice->setEnabled(false);
            ui->m_btnCloseDevice->setEnabled(true);
			ui->m_btnReset->setEnabled(true);
			ui->m_btnReadZone->setEnabled(true);
			ui->m_btnWriteZone->setEnabled(true);

			ui->m_btnReadDataset->setEnabled(bIsDataset);
			ui->m_btnWriteDataset->setEnabled(bIsDataset && bDatasetCanWrite);
			ui->m_btnStartRpt->setEnabled(bHasRpt);
			ui->m_btnStopReport->setEnabled(bHasRpt);
			ui->m_btnEnumDevice->setEnabled(bIsDataset | bIsLDevice | bIsDevice);
			ui->m_btnEnumLDevice->setEnabled(bIsDataset | bIsLDevice);
			ui->m_btnEnumDataset->setEnabled(bIsDataset);
        }
        else
        {
            ui->m_btnConfigDevice->setEnabled(true);
			ui->m_btnConnectDevice->setEnabled(true);
			ui->m_btnCloseDevice->setEnabled(false);
			ui->m_btnReset->setEnabled(false);
			ui->m_btnReadZone->setEnabled(false);
			ui->m_btnWriteZone->setEnabled(false);

			ui->m_btnReadDataset->setEnabled(false);
			ui->m_btnWriteDataset->setEnabled(false);
			ui->m_btnStartRpt->setEnabled(false);
			ui->m_btnStopReport->setEnabled(false);
			ui->m_btnEnumDevice->setEnabled(false);
			ui->m_btnEnumLDevice->setEnabled(false);
			ui->m_btnEnumDataset->setEnabled(false);
        }
    }
    else
    {
        ui->m_btnConfigDevice->setEnabled(true);
		ui->m_btnConnectDevice->setEnabled(true);
		ui->m_btnCloseDevice->setEnabled(false);
		ui->m_btnReadDataset->setEnabled(false);
		ui->m_btnWriteDataset->setEnabled(false);
		ui->m_btnReadZone->setEnabled(false);
		ui->m_btnWriteZone->setEnabled(false);
		ui->m_btnReset->setEnabled(false);
		ui->m_btnStartRpt->setEnabled(false);
		ui->m_btnStopReport->setEnabled(false);
		ui->m_btnEnumDevice->setEnabled(false);
		ui->m_btnEnumLDevice->setEnabled(false);
		ui->m_btnEnumDataset->setEnabled(false);
    }
}

//正在连接和断开时，所有按钮不可点
void QPpSttIotEngineClientWidget::EnableBtns_Connecting_Closeing()
{
	ui->m_btnConfigDevice->setEnabled(false);
	ui->m_btnConnectDevice->setEnabled(false);
	ui->m_btnCloseDevice->setEnabled(false);
	ui->m_btnReadDataset->setEnabled(false);
	ui->m_btnWriteDataset->setEnabled(false);
	ui->m_btnReadZone->setEnabled(false);
	ui->m_btnWriteZone->setEnabled(false);
	ui->m_btnReset->setEnabled(false);
	ui->m_btnStartRpt->setEnabled(false);
	ui->m_btnStopReport->setEnabled(false);
	ui->m_btnEnumDevice->setEnabled(false);
	ui->m_btnEnumLDevice->setEnabled(false);
	ui->m_btnEnumDataset->setEnabled(false);
}

#include "CommConfigWidget/PpCommConfigDlg.h"

void QPpSttIotEngineClientWidget::on_m_btnConfigDevice_clicked()
{
   CPpSttCommConfig *pCommConfig = &m_pPpDeviceClient->m_oCommConfig;

   PpCommConfigDlg dlg(pCommConfig);

   if (dlg.exec() != Accepted)
   {
		return;
   }

	on_m_btnConnectDevice_clicked();
}

void QPpSttIotEngineClientWidget::on_m_btnCloseDevice_clicked()
{
    m_pPpDeviceClient->CloseDevice();
	//EnableBtns();
	EnableBtns_Connecting_Closeing();
}

void QPpSttIotEngineClientWidget::on_m_btnConnectDevice_clicked()
{
	emit sig_OnConfigDevice(&m_pPpDeviceClient->m_oCommConfig);
    m_pPpDeviceClient->CreateDevice(0);
    m_pPpDeviceClient->ConnectDevice();
    //EnableBtns();
	EnableBtns_Connecting_Closeing();
}


void QPpSttIotEngineClientWidget::on_m_btnReset_clicked()
{
    m_pPpDeviceClient->Reset();
}

void QPpSttIotEngineClientWidget::on_m_btnEnumDevice_clicked()
{
    m_pPpDeviceClient->EnumDevice((CDvmDevice*)m_pCurrSelDvmDataObj);
}

void QPpSttIotEngineClientWidget::on_m_btnEnumLDevice_clicked()
{
    m_pPpDeviceClient->EnumLDevice((CDvmLogicDevice*)m_pCurrSelDvmDataObj);
}

void QPpSttIotEngineClientWidget::on_m_btnEnumDataset_clicked()
{
    m_pPpDeviceClient->EnumDataset((CDvmDataset*)m_pCurrSelDvmDataObj);
}

void QPpSttIotEngineClientWidget::on_m_btnReadDataset_clicked()
{
    m_pPpDeviceClient->ReadDataset((CDvmDataset*)m_pCurrSelDvmDataObj);
}

void QPpSttIotEngineClientWidget::on_m_btnWriteDataset_clicked()
{
	m_pCurrWriteDataset = (CDvmDataset*)m_pCurrSelDvmDataObj;

	if (!m_pPpDeviceClient->WriteDataset(m_pCurrWriteDataset))
	{
		CString strTitile,strMsg;
		strTitile = "提示";
		strMsg = "写数据失败.";
		CXMessageBox::information(this, strTitile, strMsg);
	}
}

void QPpSttIotEngineClientWidget::on_m_btnReadZone_clicked()
{
    m_pPpDeviceClient->ReadZone();
}

void QPpSttIotEngineClientWidget::on_m_btnWriteZone_clicked()
{
	if (m_pPpDeviceClient == NULL)
	{
		return;
	}

	if (m_pPpDeviceClient->m_pPpDevice == NULL)
	{
		return;
	}

	QSttZoneIndexSetDlg dlg(m_pPpDeviceClient->m_pPpDevice->m_nZoneIndex);
	
	if (dlg.exec() == QDialog::Accepted)
	{
		m_pPpDeviceClient->WriteZone(dlg.m_nZoneIndex);
	}
}

void QPpSttIotEngineClientWidget::on_m_btnStartRpt_clicked()
{
	QSttMmsBrcbCtrlWidget dlg;

	if (dlg.exec() != QDialog::Accepted)
	{
		return;
	}

	m_pPpDeviceClient->StartRpt((CDvmDataset*)m_pCurrSelDvmDataObj, &dlg.m_oBrcbCtrl);
}

void QPpSttIotEngineClientWidget::on_m_btnStopReport_clicked()
{
	m_pPpDeviceClient->StopReport((CDvmDataset*)m_pCurrSelDvmDataObj);
}

void QPpSttIotEngineClientWidget::on_m_btnOpenDvmFile_clicked()
{

}

void QPpSttIotEngineClientWidget::on_m_btnSaveDvmFile_clicked()
{

}

//2023-2-7  lijunqing  下面部分的代码，用于调试功能用
/*
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbWzdAi/GbWzdAiTool.h"
#include "../../UI/Interface/SttHtmlViewApi.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
*/
void QPpSttIotEngineClientWidget::on_m_btnAddDevice_clicked()
{
/*
	CGbWzdAiTool oTool;

	CDataGroup oTestMacroUI_Paras;
	stt_ui_OpenParasFile("Distance_Paras.xml", &oTestMacroUI_Paras);
	CString strAiFile = stt_ui_GetParasFile("Distance_Paras_ai.xml");
	oTool.SetXKeyDB(g_pTheSttTestApp->m_pKeyDB);
	oTool.SetDvmDevice(m_pDvmDevice);
	oTool.DvmFilterByExtendKeys();
	oTool.OpenGbWzdAiFile(strAiFile);
	oTool.SetMacroParasByAI(&oTestMacroUI_Paras);
	stt_ui_SaveParasFile("Distance_Paras_After_Ai.xml", &oTestMacroUI_Paras);
*/

}

QPpSttIotEngineClientWidget* CreateEngineClientWidget()
{
    if (g_theEngineClientWidget != NULL)
    {
        return g_theEngineClientWidget;
    }

    g_theEngineClientWidget = new QPpSttIotEngineClientWidget();
    return g_theEngineClientWidget;
}

void ReleaseEngineClientWidget()
{
    if (g_theEngineClientWidget == NULL)
    {
        return;
    }

    delete g_theEngineClientWidget;
    g_theEngineClientWidget = NULL;
}


