#include "SttAuxIPSetDlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../../../../../Module/Log/LogPrint.h"
#include "../CommonMethod/commonMethod.h"
#include "../../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../XLangResource_Native.h"
#include "../../SttTestCntrFrameBase.h"
#include "SttAuxModifyIPDlg.h"
#include "../../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../SttTestCtrl/SttTestCtrlCntrNative.h"

#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttAuxIPSetDlg::QSttAuxIPSetDlg(QWidget *pParent)
	:QDialog(pParent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setWindowTitle(g_sLangTxt_Gradient_SecondaryIPSet);
	resize(550,400);
	setFixedSize(550,400);
	m_pIP_QLabel = NULL;
	m_pIP_QLineEdit = NULL;	
	m_pAuxIP_QLabel = NULL;
	m_pAuxIP_QLineEdit = NULL;
	m_pbtnOK = NULL;
	m_pbtnCancel = NULL;
	m_pbtnAdd = NULL;
	m_pbtnModify = NULL;
	m_pbtnDel = NULL;
	m_pSttAuxIPSetGrid = NULL;
	m_pCurSelData = NULL;
	m_pClientEngine = NULL;
	
	initUI(); 
	initSignalSlots();
	CreateSttSocket();
}

QSttAuxIPSetDlg::~QSttAuxIPSetDlg()
{
	FreeClientEngine();

	if (m_pSttAuxIPSetGrid != NULL)
	{
		delete m_pSttAuxIPSetGrid;
		m_pSttAuxIPSetGrid = NULL;
	}


	m_oGridDatas.RemoveAll();
}

void QSttAuxIPSetDlg::initUI()
{
	CString strText;
	m_pIP_QLabel = new QLabel(this);
	m_pIP_QLabel->setFont(*g_pSttGlobalFont);
	strText = _T("主IP地址:");
	m_pIP_QLabel->setText(strText);
	m_pIP_QLineEdit = new QSttLineEdit(this);
	m_pIP_QLineEdit->setFont(*g_pSttGlobalFont);
	m_pIP_QLineEdit->setFixedWidth(150);
	m_pIP_QLineEdit->setEnabled(false);
	m_pIP_QLineEdit->setText("0.0.0.0");

	QHBoxLayout* pIPHLayout = new QHBoxLayout;
	pIPHLayout->addWidget(m_pIP_QLabel);
	pIPHLayout->addWidget(m_pIP_QLineEdit);
	pIPHLayout->addStretch();
	
	m_pSttAuxIPSetGrid = new QSttAuxIPSetGrid(this);
	m_pSttAuxIPSetGrid->AttachDataViewOptrInterface(this);
	m_pSttAuxIPSetGrid->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); 
	m_pSttAuxIPSetGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pSttAuxIPSetGrid->setFont(*g_pSttGlobalFont);

	m_pbtnAdd = new QPushButton(this);
	m_pbtnAdd->setFont(*g_pSttGlobalFont);
	strText = _T("添加");
	m_pbtnAdd->setText(strText);
	m_pbtnAdd->setEnabled(FALSE);

	m_pbtnModify = new QPushButton(this);
	m_pbtnModify->setFont(*g_pSttGlobalFont);
	strText = _T("修改");
	m_pbtnModify->setText(strText);
	m_pbtnDel = new QPushButton(this);
	m_pbtnDel->setFont(*g_pSttGlobalFont);
	strText = _T("删除");
	m_pbtnDel->setText(strText);
	m_pbtnOK = new QPushButton(g_sLangTxt_OK); 
	m_pbtnCancel = new QPushButton(g_sLangTxt_Cancel); 
	m_pbtnOK->setFont(*g_pSttGlobalFont);
	m_pbtnCancel->setFont(*g_pSttGlobalFont);


	QHBoxLayout* pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->addWidget(m_pbtnAdd);
	pHBoxLayout->addWidget(m_pbtnModify);
	pHBoxLayout->addWidget(m_pbtnDel);
	pHBoxLayout->addStretch();
	pHBoxLayout->addWidget(m_pbtnOK);
	pHBoxLayout->addWidget(m_pbtnCancel);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addLayout(pIPHLayout);
	pMainLayout->addWidget(m_pSttAuxIPSetGrid);
	pMainLayout->addLayout(pHBoxLayout);
	setLayout(pMainLayout);

	EnableButtons();
}

void QSttAuxIPSetDlg::initSignalSlots()
{
	connect(m_pbtnOK, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pbtnCancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pbtnAdd, SIGNAL(clicked()), this, SLOT(slot_AddClicked()));
	connect(m_pbtnModify, SIGNAL(clicked()), this, SLOT(slot_ModifyClicked()));
	connect(m_pbtnDel, SIGNAL(clicked()), this, SLOT(slot_DelClicked()));
}

void QSttAuxIPSetDlg::slot_OKClicked()
{


	accept();
}

void QSttAuxIPSetDlg::slot_CancelClicked()
{
	close();
}


void QSttAuxIPSetDlg::slot_AddClicked()
{
	QAuxModifyIPDlg oAuxModifyIPDlg(this);
	oAuxModifyIPDlg.setFont(*g_pSttGlobalFont);
	oAuxModifyIPDlg.setWindowModality(Qt::WindowModal);
	oAuxModifyIPDlg.InitParas(_T(""));
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oAuxModifyIPDlg);
#endif
	connect(&oAuxModifyIPDlg, SIGNAL(sig_ModifyTesterIP_OK(QString &,const QString &)), this, SLOT(slot_AddTesterIPAsMask(QString &,const QString &)));
	oAuxModifyIPDlg.exec();
#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif
	disconnect(&oAuxModifyIPDlg, SIGNAL(sig_ModifyTesterIP_OK(QString &,const QString &)), this, SLOT(slot_AddTesterIPAsMask(QString &,const QString &)));
}

void QSttAuxIPSetDlg::slot_ModifyClicked()
{
	CString strIP,strMask;
	stt_GetDataValueByID(m_pCurSelData, STT_SYS_DATA_ID_IP, strIP);
	stt_GetDataValueByID(m_pCurSelData, STT_SYS_DATA_ID_Mask, strMask);

	for(int i=0;i<m_astrIP.GetCount();i++)
	{
		CString strIPs = m_astrIP.GetAt(i);
		if (strIPs == strIP)
		{
			m_astrIP.RemoveAt(i);
			m_astrMask.RemoveAt(i);
		}
	}

	QAuxModifyIPDlg oAuxModifyIPDlg(this);
	oAuxModifyIPDlg.setFont(*g_pSttGlobalFont);
	oAuxModifyIPDlg.InitParas(strIP,strMask);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oAuxModifyIPDlg);
#endif
	connect(&oAuxModifyIPDlg, SIGNAL(sig_ModifyTesterIP_OK(QString &,const QString &)), this, SLOT(slot_ModifyTesterIPAsMask(QString &,const QString &)));
	oAuxModifyIPDlg.exec();

#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif

	disconnect(&oAuxModifyIPDlg, SIGNAL(sig_ModifyTesterIP_OK(QString &,const QString &)), this, SLOT(slot_ModifyTesterIPAsMask(QString &,const QString &)));
}

void QSttAuxIPSetDlg::slot_DelClicked()
{
	CString strIP;
	stt_GetDataValueByID(m_pCurSelData, STT_SYS_DATA_ID_IP, strIP);
	for(int i=0;i<m_astrIP.GetCount();i++)
	{
		CString strIPs = m_astrIP.GetAt(i);

		if (strIPs == strIP)
		{
			m_astrIP.RemoveAt(i);
			m_astrMask.RemoveAt(i);
		}
	}

	int row = m_pSttAuxIPSetGrid->currentRow();
	m_pSttAuxIPSetGrid->removeRow(row);

	m_oGridDatas.RemoveAll();
	m_oGridDatas.DeleteAll();
	CString strID; 
	for (int i = 1 ; i<m_astrIP.GetCount();i++)
	{
		strID.Format(_T("SubIP%ld"), i);
		CDataGroup *RecvGroup = new CDataGroup;
		RecvGroup->m_strID = strID;
		RecvGroup->m_strName = strID;
		RecvGroup->m_strDataType = STT_SYS_DATA_ID_SubIP;
		RecvGroup->AddNewData(STT_SYS_DATA_ID_IP, m_astrIP.GetAt(i));
		RecvGroup->AddNewData(STT_SYS_DATA_ID_Mask, m_astrMask.GetAt(i));
		RecvGroup->AddNewData(STT_SYS_DATA_ID_GateWay, _T("192.168.1.1"));
		RecvGroup->AddNewData(STT_SYS_DATA_ID_Metric,long(1));
		m_oGridDatas.AddTail(RecvGroup);
	}

	m_pClientEngine->System_SetSysConfig(&m_oGridDatas,TRUE,NULL,TRUE);
}


void QSttAuxIPSetDlg::slot_AddTesterIPAsMask( QString &strIP,const QString &strSubNetMask )
{
	CString strMsg,strTemp;
	if (!IsIPExactness(strIP))
	{
		strMsg = QString(g_sLangTxt_validentry.arg(strIP));
		CXMessageBox::information(this,g_sLangTxt_Message ,strMsg);
		return;
	}

	for (int i = 0 ; i<m_astrIP.GetCount();i++)
	{
		CString strListIP = m_astrIP.GetAt(i);

		if (strListIP == strIP)
		{
			strMsg = QString(g_sLangTxt_listIP .arg(strIP));
			CXMessageBox::information(this,g_sLangTxt_Message,strMsg);
			return;
		}
	}

	if (m_astrIP.GetCount() > MaxAuxIpCount)
	{
		strMsg = _T("最多添加10个辅助IP地址.");
		CXMessageBox::information(this,g_sLangTxt_Message,strMsg);
		return;
	}


	m_astrIP.Add(strIP);
	m_astrMask.Add(strSubNetMask);
	m_oGridDatas.RemoveAll();
	m_oGridDatas.DeleteAll();

	CString strID;
	for (int i = 1 ; i<m_astrIP.GetCount();i++)
	{
		strID.Format(_T("SubIP%ld"), i);
		CDataGroup *RecvGroup = new CDataGroup;
		RecvGroup->m_strID = strID;
		RecvGroup->m_strName = strID;
		RecvGroup->m_strDataType = STT_SYS_DATA_ID_SubIP;
		RecvGroup->AddNewData(STT_SYS_DATA_ID_IP, m_astrIP.GetAt(i));
		RecvGroup->AddNewData(STT_SYS_DATA_ID_Mask, m_astrMask.GetAt(i));
		RecvGroup->AddNewData(STT_SYS_DATA_ID_GateWay, _T("192.168.1.1"));
		RecvGroup->AddNewData(STT_SYS_DATA_ID_Metric,long(1));
		m_oGridDatas.AddTail(RecvGroup);
	}
	m_pSttAuxIPSetGrid->ShowDatas(&m_oGridDatas);
	m_pClientEngine->System_SetSysConfig(&m_oGridDatas,TRUE,NULL,TRUE);
}

void QSttAuxIPSetDlg::slot_ModifyTesterIPAsMask( QString &strIP,const QString &strSubNetMask )
{
	CString strMsg,strTemp;
	if (!IsIPExactness(strIP))
	{
		strMsg = QString(g_sLangTxt_validentry.arg(strIP));
		CXMessageBox::information(this,g_sLangTxt_Message,strMsg);
		return;
	}

	for (int i = 0 ; i<m_astrIP.GetCount();i++) 
	{
		CString strListIP = m_astrIP.GetAt(i);
		if (strListIP == strIP)
		{
			strMsg = QString(g_sLangTxt_listIP.arg(strIP));
			CXMessageBox::information(this,g_sLangTxt_Message,strMsg);
			return;
		}
	}

	m_astrIP.Add(strIP);
	m_astrMask.Add(strSubNetMask);
	m_oGridDatas.RemoveAll();
	m_oGridDatas.DeleteAll();

	CString strID;
	for(int i = 1;i < m_astrIP.GetCount();i++)
	{
		strID.Format(_T("SubIP%ld"), i);
		CDataGroup *RecvGroup = new CDataGroup;
		RecvGroup->m_strID = strID;
		RecvGroup->m_strName = strID;
		RecvGroup->m_strDataType = STT_SYS_DATA_ID_SubIP;
		RecvGroup->AddNewData(STT_SYS_DATA_ID_IP, m_astrIP.GetAt(i));
		RecvGroup->AddNewData(STT_SYS_DATA_ID_Mask, m_astrMask.GetAt(i));
		RecvGroup->AddNewData(STT_SYS_DATA_ID_GateWay, _T("192.168.1.1"));
		RecvGroup->AddNewData(STT_SYS_DATA_ID_Metric,long(1));
		m_oGridDatas.AddTail(RecvGroup);
	}
	
	m_pSttAuxIPSetGrid->ShowDatas(&m_oGridDatas);
	m_pClientEngine->System_SetSysConfig(&m_oGridDatas,TRUE,NULL,TRUE);
}


BOOL QSttAuxIPSetDlg::IsIPExactness(CString strIP)
{
	QRegExp rx2("^(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$");
	if( !rx2.exactMatch(strIP) )
	{
		return FALSE;
	}

	return TRUE;
}


BOOL QSttAuxIPSetDlg::CreateSttSocket()
{
	if (m_pClientEngine == NULL)	
	{
		CSttClientTestEngine *pNew = new CSttClientTestEngine();
		m_pClientEngine = pNew;
		m_pClientEngine->SetTestEventInterface(this);
	}

	if (m_oClientSocket.IsSocketValid())
	{
		return TRUE;
	}

	if (m_oClientSocket.m_hSocket != 0)
	{
		m_oClientSocket.Close();
	}

	m_oSttTestAppCfg.SttOpen(m_oSttTestAppCfg.GetSttCfgFile());
	BOOL bRet = m_pClientEngine->ConnectServer(m_oSttTestAppCfg.GetTestAppIP(),m_oSttTestAppCfg.GetTestServerPort());
	if (!bRet)
	{
		return FALSE;
	}

	CSttCmdData oRetData;
	long nRet = 0;
	nRet = m_pClientEngine->System_GetSysConfig(TRUE, &oRetData,TRUE);
	if (nRet > 0)
	{
		m_pbtnAdd->setEnabled(TRUE);
	}
	return TRUE;
}


void QSttAuxIPSetDlg::OnDataSelChanged( QTableWidget *pGridCtrl, int nRow, int nCol )
{
	if (nRow < 0 || nRow >= pGridCtrl->rowCount() || nCol < 0 || nCol >= pGridCtrl->columnCount())
	{
		return; 
	}

	CDataGroup *pCurrSelData = new CDataGroup;

	for (int col = 0; col < pGridCtrl->columnCount(); ++col)
	{
		QTableWidgetItem *pItem = pGridCtrl->item(nRow, col);
		if (pItem)
		{	
			CString strText = pItem->text();

			if (col == 0)
			{
				pCurrSelData->AddNewData(STT_SYS_DATA_ID_IP, strText);
			}
			else
			{
				pCurrSelData->AddNewData(STT_SYS_DATA_ID_Mask, strText);
			}
		}
	}


 	//CDataGroup *pCurrSelData = (CDataGroup*)m_pSttAuxIPSetGrid->GetCurrSelData();
	if (pCurrSelData->GetCount() > 0)
	{
		m_pCurSelData = pCurrSelData;
		EnableButtons();
	}
}

void QSttAuxIPSetDlg::EnableButtons()
{
	if (m_pCurSelData == NULL)
	{
		m_pbtnModify->setEnabled(FALSE);
		m_pbtnDel->setEnabled(FALSE);
	}
	else
	{
		m_pbtnModify->setEnabled(TRUE);
		m_pbtnDel->setEnabled(TRUE);
	}
}


void QSttAuxIPSetDlg::FreeClientEngine()
{
	if(m_pClientEngine != NULL)
	{
		m_pClientEngine->DisConnect();
		delete m_pClientEngine;
		m_pClientEngine = NULL;
	}
}


void QSttAuxIPSetDlg::OnRecvSysConfigData(CSttParas *pSttParas)
{
	if (pSttParas == NULL)
 	{
 		CString strMsgText;
 		strMsgText = _T("功能暂不支持.");
 		CXMessageBox::information(this,g_sLangTxt_Message,strMsgText);
 		return ;
 	}

 	m_astrIP.RemoveAll();
 	m_astrMask.RemoveAll();
 	m_oGridDatas.DeleteAll();
 	CString strIP = _T(""),strMask = _T("");
	CExBaseObject *pChildObj = NULL;
	POS pos = pSttParas->GetHeadPosition();

 	CDataGroup *pDataGroup = NULL;
 
 	while (pos != NULL)
 	{
 		pDataGroup = (CDataGroup *)pSttParas->GetNext(pos);
 
		if (pDataGroup == NULL || pDataGroup->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}
 		
		stt_GetDataValueByID(pDataGroup, STT_SYS_DATA_ID_IP, strIP);
		stt_GetDataValueByID(pDataGroup, STT_SYS_DATA_ID_Mask, strMask);
		m_astrIP.Add(strIP);
		m_astrMask.Add(strMask);
 
 		if (pDataGroup->m_strDataType == STT_SYS_DATA_ID_SubIP)
 		{
 			m_oGridDatas.AddTail(pDataGroup);
 		}
 	}

	m_pIP_QLineEdit->setText(m_astrIP.GetAt(0));
	m_pSttAuxIPSetGrid->ShowDatas(&m_oGridDatas);
}


