#include "SttIecRecordWriteFileWidget.h"
//#include "ui_SttIecRecordWriteFileWidget.h"
#include "../../../../Module/SmartCap/XSmartCapFileWrite.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDevice6044.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
//#include "../../Module/UI/SttTestCntrFrameBase.h"
#include "SttIecCbGrid.h"
#include "../../UI/Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../UI/Module/PopupDialog/SttPopupSaveAsDialog.h"
#include "../UI/SttIecRecordMainWidget.h"
#include "../UI/SttIecRecordDetectWidget.h"
#include <QHeaderView>
#include <QMessageBox>
#include "MUTest/SttIecRecordCbInterface.h"
#include "../../UI/Module/PopupDialog/SttFileMngrTool.h"
#include "../../XLangResource_Native.h"
#include <QFileDialog>

#ifdef _USE_SoftKeyBoard_	
#include "../../UI/SoftKeyboard/SoftKeyBoard.h"
#endif

extern QSttIecRecordMainWidget *g_theSttIecRecordMainWidget;
extern QSttIecRecordDetectWidget *g_pSttIecRecordDetectWidget;

#define RECORDWRITEGRID_COLS			5

#define RECORDWRITEGRID_TYPE			0
#define RECORDWRITEGRID_APPID			1
#define RECORDWRITEGRID_NAME			2
#define RECORDWRITEGRID_FIBER			3
#define RECORDWRITEGRID_TOTALPACKETS	4


QSttIecRecordWriteFileGrid::QSttIecRecordWriteFileGrid( QWidget* parent )
:QExBaseListGridBase(parent)
{
	QExBaseListGridBase::InitGrid();
	InitGridTitle();
}

QSttIecRecordWriteFileGrid::~QSttIecRecordWriteFileGrid()
{
}

void QSttIecRecordWriteFileGrid::InitGrid()
{
	QExBaseListGridBase::InitGrid();
	// 	QIecNumberEditDelegate *pAppIDDelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
	// 	setItemDelegateForColumn(RECORDWRITEGRID_APPID,pAppIDDelegate);

}

void QSttIecRecordWriteFileGrid::InitGridTitle()
{
	CString astrGridTitle[4];
	//	= {"类型","APPID",_T("描述"),"光口","报文总数KB"};
	xlang_GetLangStrByFile(astrGridTitle[0],_T("Native_Type"));
	astrGridTitle[1] = "AppID";
	xlang_GetLangStrByFile(astrGridTitle[2],_T("State_Description"));
	xlang_GetLangStrByFile(astrGridTitle[3],_T("IEC_FI"));
	// 	astrGridTitle[4] = "报文总数KB";

#ifdef _PSX_QT_LINUX_
	// 	int iGridWidth[RECORDWRITEGRID_COLS]={80, 100, 450, 130, 200};//暂时隐藏报文总数列
	int iGridWidth[4]={100, 100, 450, 130};
#else
	// 	int iGridWidth[RECORDWRITEGRID_COLS]={80, 100, 450, 130, 200};
	int iGridWidth[4]={100, 100, 450, 130};

#endif
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 4);
}

void QSttIecRecordWriteFileGrid::ShowData( CExBaseObject *pData, int& nRow, BOOL bInsertRow/*=TRUE*/ )
{
	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)pData;

	CString strDesc;
	strDesc = pCapDevice->GetCtrlDesc();

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	PSTT_AT02_PKT_HEAD_STC_MNGR pHeadStcMngr = pXCapPkgBufferMngr->GetPkgHeadStcMngr();

	Show_61850Type(pData, nRow, RECORDWRITEGRID_TYPE, pCapDevice->m_nType);

	if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE6044)
	{
		CCapDevice6044 *pCapDevice6044 = (CCapDevice6044 *)pCapDevice;
		strDesc.Format(_T("SampleRate=%ldHz,BaudRate=%lf"),pCapDevice6044->m_nSmpRate,pCapDevice6044->m_dBaudRate);
		Show_StaticString(pData, nRow, RECORDWRITEGRID_APPID, _T("--"));
		Show_StaticString(pData, nRow, RECORDWRITEGRID_NAME, strDesc);
	} 
	else
	{
		Show_Hex(pData, nRow, RECORDWRITEGRID_APPID, &pCapDevice->m_dwAppID, 2, FALSE);
		Show_StaticString(pData, nRow, RECORDWRITEGRID_NAME, strDesc);
	}

	Show_Fiber(pData, nRow, RECORDWRITEGRID_FIBER, pCapDevice->m_nFiberIndex);

	// 	if(nRow <= pHeadStcMngr->nCount)
	// 	{
	// 		Show_TotalPackets(pData, nRow,RECORDWRITEGRID_TOTALPACKETS, &pHeadStcMngr->oHeadStc[nRow]);
	// 	}

	nRow++;
}

void QSttIecRecordWriteFileGrid::Show_61850Type(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nType)
{
	CString strType = ep_Get61850ProtocolType(nType);
	Show_StaticString(pStData, nRow, nCol, strType);
}

void QSttIecRecordWriteFileGrid::Show_Fiber(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nFiberIndex)
{
	CString strFiber;
	strFiber.Format(/*_T("光口%d")*/g_sLangTxt_Gradient_POpticalPort.GetString()/*g_sLangTxt_Gradient_POpticalPort.GetString()*/,nFiberIndex+1); //lcq
	Show_StaticString(pStData, nRow, nCol, strFiber);
}


void QSttIecRecordWriteFileGrid::Show_FileSize( CExBaseObject *pStData, const int& nRow, const int& nCol)
{
	long nLen = CXSmartCapFileWrite::GetWriteLen();
	nLen = nLen / 1024;
	long nM = nLen / 1024;
	long nK = nLen - nM * 1024;
	CString strSize;
	strSize.Format(_T("%d,%d K"), nM, nK);

	Show_StaticString(pStData,nRow,nCol,strSize);
}

void QSttIecRecordWriteFileGrid::Show_TotalPackets(CExBaseObject *pStData, const int& nRow, const int& nCol, PSTT_AT02_PKT_HEAD_STC pHeadStc )
{
	CString strTotalPackets = QString::number(pHeadStc->nPkgCount);
	Show_StaticString(pStData,nRow,nCol,strTotalPackets);
}

////////////////////////////////////////////////////////////////////////////////////////////////////


QSttIecRecordWriteFileWidget::QSttIecRecordWriteFileWidget(QWidget *parent) :
	QDialog(parent)//,
//	ui(new Ui::QSttIecRecordWriteFileWidget)
{
//     ui->setupUi(this);
    m_pIecRcdFuncWidget = this;

	m_bIsStartRecord= FALSE;

	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	m_pRecordWriteFileGrid = new QSttIecRecordWriteFileGrid(this);
	m_pRecordWriteFileGrid->setFont(*g_pSttGlobalFont);
	m_pRecordWriteFileGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pRecordWriteFileGrid->InitGrid();

//	m_nRecordtime = 0;
	m_mainLayout = new QHBoxLayout();
	this->setLayout(m_mainLayout);
	m_mainLayout->addWidget(m_pRecordWriteFileGrid);
// 	ui->gridLayout_2->addWidget(m_pRecordWriteFileGrid);


	CXSmartCapFileWrite::Create();

	m_oWriteFileTickCount.Enter();
//	double timeRate = 1;/*1s刷新一次录波时间*/
//	m_oTimerRcdtimer.start(1000 * timeRate);
//	connect(&m_oTimerRcdtimer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
}

QSttIecRecordWriteFileWidget::~QSttIecRecordWriteFileWidget()
{
//    delete ui;
}

void QSttIecRecordWriteFileWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_oWriteFileTickCount.Enter();
}

void IecRcdFunc_WriteFile_Show(QLineEdit *pEditAppID, QLineEdit *pEditPkgCount, QLineEdit *pEditPkgErr, QLineEdit *pEditMaxTime,PSTT_AT02_PKT_HEAD_STC pHeadStc)
{
	CString strText;
	strText.Format(_T("%X"), pHeadStc->appid);
	pEditAppID->setText(strText);

	pEditPkgCount->setText(QString::number(pHeadStc->nPkgCount));
	pEditPkgErr->setText(QString::number(pHeadStc->nSmpCntError));
	pEditMaxTime->setText(QString::number(pHeadStc->nMaxTimeDiff));
}

void QSttIecRecordWriteFileWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{

#ifdef _XSmartCap_use_SttRcdSocket_

	if (!CSttRcdSocketBase::IsWriteAt02dRcdFileWrite())
	{
		return;
	}

	long nLen = CSttRcdSocketBase::m_n64RecvTotalSize;
#else
	long nLen = CXSmartCapFileWrite::GetWriteLen();
#endif
// 	//接受到报文长度大于0，开启计时录波文件定时器
// 	if(nLen > 0)
// 	{	
// 		if(!m_oTimerRcdtimer.isActive())
// 		{
// 			double timeRate = 1;/*1s刷新一次录波时间*/
// 			m_oTimerRcdtimer.start(1000 * timeRate);
// 		}
// 	}

	//2023/11/24 wangjunsheng 当点击停止录波后不更新录播时间和文件大小
	if(m_bIsStartRecord == TRUE)
	{
		return;
	}

	long nTime = m_oWriteFileTickCount.GetTickCountLong(FALSE);
	g_pSttIecRecordCbWidget->UpdateWriteFileTimeAndFileSize(nTime,nLen);

//	emit sig_SendFileSize(nM,nK);

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	PSTT_AT02_PKT_HEAD_STC_MNGR pHeadStcMngr = pXCapPkgBufferMngr->GetPkgHeadStcMngr();

}

void QSttIecRecordWriteFileWidget::Release()
{
	if(m_pRecordWriteFileGrid != NULL)
	{
		delete m_pRecordWriteFileGrid;
		m_pRecordWriteFileGrid = NULL;
	}
//	m_oTimerRcdtimer.stop();
	if(!CXSmartCapFileWrite::HasRelease())
	{
		CXSmartCapFileWrite::Release();
	}

	delete this;
}

// void QSttIecRecordWriteFileWidget::timerUpdate( )
// {
// 	emit sig_SendRecordTime(++m_nRecordtime);
// }

void QSttIecRecordWriteFileWidget::SetSelectedCbs( CExBaseList *pSelectedCbs )
{
	ASSERT(pSelectedCbs);

 	m_pRecordWriteFileGrid->ShowDatas(pSelectedCbs);
}

void QSttIecRecordWriteFileWidget::StartRecord()
{
	//CXSmartCapFileWrite::Release();
	CXSmartCapFileWrite::Create();
	m_oWriteFileTickCount.Enter();
	m_bIsStartRecord = FALSE;
}

void QSttIecRecordWriteFileWidget::Config()
{
	if(m_bIsStartRecord == TRUE)
	{
		StartRecord();
		return;
	}


	CString strWriteFilePath,strPcapFilePath,strMsgText,strTmp;
#ifdef _XSmartCap_use_SttRcdSocket_
	strWriteFilePath = CSttRcdSocketBase::m_strWriteFilePath;
	CString strAt02DFilePath;
	strAt02DFilePath = ChangeFilePostfix(strWriteFilePath,_T("at02d"));
	stt_rcd_unzip_file(strWriteFilePath.GetString(),strAt02DFilePath.GetString());
	X_DeleteFile(strWriteFilePath);
	strWriteFilePath = strAt02DFilePath;
#else
	strWriteFilePath = CXSmartCapFileWrite::GetWriteFilePath();
#endif

	strTmp = ChangeFilePostfix(strWriteFilePath,_T("pcap"));
	strPcapFilePath = GetFileNameFromFilePath(strTmp);

	if (strPcapFilePath.IsEmpty())
	{
		strMsgText = /*_T("当前写文件路径为空.")*/g_sLangTxt_Native_CurrWrtFileEmpty.GetString();
		CLogPrint::LogString(XLOGLEVEL_ASSIST,strMsgText);
		return;
	}

	strTmp = g_oFileMngrTool.GetFolderPath_STD(STT_FILE_MNGR_PcapFile);
	strTmp += _T("/");
	strTmp.Replace(_T("//"),_T("/"));

	//2024-6-22 wuxinyi 当Pcap文件夹不存在时，创建文件夹
	if(!IsFileExist(strTmp))
	{
		CreateAllDirectories(strPcapFilePath);
	}

#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;
	astrPostfix<<"pcap";
	QSttPopupSaveAsDialog oSavedlg(strTmp, astrPostfix,strPcapFilePath, this);
	oSavedlg.InitUI();
	oSavedlg.InitTitle(/*_T("文件保存为")*/g_sLangTxt_Native_SaveAs);
//	CString strFilePathName = CXSmartCapFileWrite::GetPcapFilePath();

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oSavedlg,Keyboard::CHINESE);

	if (oSavedlg.exec() != QDialog::Accepted)
	{
		QSoftKeyBoard::ReAttachObj();
		return;
	}

	QSoftKeyBoard::ReAttachObj();
#else
	if (oSavedlg.exec() != QDialog::Accepted)
	{
		return;
	}

#endif
	strPcapFilePath = oSavedlg.GetFilePath();
#else

	strPcapFilePath = QFileDialog::getSaveFileName(0, QObject::tr("Pcap文件另存为"),
		strTmp,"pcap(*.pcap)"); //lcq

	if (strPcapFilePath.IsEmpty())
	{
		return;
	}

	strPcapFilePath = ChangeFilePostfix(strPcapFilePath,_T("pcap"));
#endif

	//20240105 suyang 保存文件给提示信息
	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("正在保存文件(%s)......"),strPcapFilePath.GetString());
	CTickCount32 oTickCount;
	oTickCount.DoEvents(20);
	

	BOOL bRet = FALSE;

#ifdef _XSmartCap_use_SttRcdSocket_
	CSttRcdSocketBase::CloseAt02dRcdFileWrite();

	if (g_pSttIecRecordDetectWidget->m_bViewFT3)
	{
		bRet = stt_save_pcap_file_ft3(strWriteFilePath,strPcapFilePath.GetString());
	} 
	else
	{
		bRet = stt_save_pcap_file(strWriteFilePath,strPcapFilePath.GetString());
	}

	if (bRet)
	{
		X_DeleteFile(strWriteFilePath);
	}
#else
	bRet = CXSmartCapFileWrite::StopWrite(strPcapFilePath);

	//2023/11/24 wangjunsheng 改变录波文件为可读状态
	m_bIsStartRecord = TRUE;
	CXSmartCapFileWrite::Release();


#endif	

	if (bRet)
	{
		QString qstrMsgText = QString("文件(%1)保存成功.").arg(strPcapFilePath);//dingxy 20240410 解决中文乱码
		strMsgText.Format(qstrMsgText);
	}
	else
	{
		QString qstrMsgText = QString("文件(%1)保存失败.").arg(strPcapFilePath);
		strMsgText.Format(qstrMsgText);
	}

	CXMessageBox::information(this,/* tr("提示")*/g_sLangTxt_Message,strMsgText);
	CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,strMsgText.GetString());
}

BOOL QSttIecRecordWriteFileWidget::HasSaveAsWriteFile()
{
#ifdef _XSmartCap_use_SttRcdSocket_
	return (CSttRcdSocketBase::IsWriteAt02dRcdFileWrite() == FALSE);
#else
	return CXSmartCapFileWrite::HasCloseFile();
#endif	

	return TRUE;
}




