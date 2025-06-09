#include "QSttCommCfgPkgMonitorWidget.h"

#include <QDirIterator>
#include "../../../../SttCmd/SttParas.h"
#include "../../../../SttGlobalDef.h"
#include "../../../../../../Module/System/TickCount32.h"
#include "../../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../CommonMethod/commonMethod.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../SttTestCntrFrameBase.h"
#include "../../PopupDialog/SttPopupSaveAsDialog.h"

#ifdef _USE_SoftKeyBoard_	
#include "../../../../UI/SoftKeyboard/SoftKeyBoard.h"
#endif

#include <QDesktopWidget>
#include <QApplication>
#include <QFileDialog>

QSttCommCfgPkgMonitorWidget::QSttCommCfgPkgMonitorWidget(QWidget *parent)
: QWidget(parent)
{
// 	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
// 	setWindowTitle(CString("报文监听"));
	m_pRecvPkgTimer = NULL;
	m_bIsCreateWidget = FALSE;

	initUI();
	if(g_theTestCntrFrame->m_pEngineClientWidget == NULL)
	{
		g_theTestCntrFrame->CreateEngineClientWidget();
		m_bIsCreateWidget = TRUE;
	}
	m_pCommCfgDeviceWidget =  (QSttCommCfgDeviceWidget*)g_theTestCntrFrame->m_pEngineClientWidget;
}

QSttCommCfgPkgMonitorWidget::~QSttCommCfgPkgMonitorWidget()
{
	if(m_pRecvPkgTimer)
	{
		delete m_pRecvPkgTimer;
		m_pRecvPkgTimer = NULL;
	}
}

void QSttCommCfgPkgMonitorWidget::initUI()
{
	ReleaseUI();
	//resize(800, 630);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	//  	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	//  	sizePolicy.setHorizontalStretch(30);
	//  	sizePolicy.setVerticalStretch(30);
	m_pLeftPkgMonitorGrid = new SttCCommCfgPkgMonitorLeftGrid(this);
	m_pLeftPkgMonitorGrid->InitGrid();

	m_pRightPkgMonitorGrid = new SttCCommCfgPkgMonitorRightGrid(this);
	m_pRightPkgMonitorGrid->InitGrid();

	QVBoxLayout *pAllVLayout = new QVBoxLayout(this);

	QHBoxLayout *pUp_HLayout = new QHBoxLayout(this);
	m_pRightPkgMonitorGrid->setMaximumWidth(180);
	pUp_HLayout->addWidget(m_pLeftPkgMonitorGrid);
	pUp_HLayout->addWidget(m_pRightPkgMonitorGrid);
	pAllVLayout->addLayout(pUp_HLayout);

	QHBoxLayout *pDown_HLayout = new QHBoxLayout(this);
	//pDown_HLayout->setAlignment(Qt::AlignTop);
	m_pStartMonitor_PushButton = new QPushButton(this);
	m_pStartMonitor_PushButton->setText(CString("开始监听"));
	pDown_HLayout->addWidget(m_pStartMonitor_PushButton);
	m_pStopMonitor_PushButton = new QPushButton(this);
	m_pStopMonitor_PushButton->setText(CString("终止监听"));
	pDown_HLayout->addWidget(m_pStopMonitor_PushButton);
	m_pClearList_PushButton = new QPushButton(this);
	m_pClearList_PushButton->setText(CString("清空列表"));
	pDown_HLayout->addWidget(m_pClearList_PushButton);
	m_pExportMonitor_PushButton = new QPushButton(this);
	m_pExportMonitor_PushButton->setText(CString("导出"));
	pDown_HLayout->addWidget(m_pExportMonitor_PushButton);
	pAllVLayout->addLayout(pDown_HLayout);

// 	QPushButton *pOK_PushButton = new QPushButton(this);
// 	pOK_PushButton->setText(g_sLangTxt_OK);
// 	//strText = _T("取消");
// 	QPushButton *pCancel_PushButton = new QPushButton(this);
// 	pCancel_PushButton->setText(g_sLangTxt_Cancel);
// 	QHBoxLayout *m_pOkCancel_HBoxLayout = new QHBoxLayout(this);
// 	m_pOkCancel_HBoxLayout->addStretch();
// 	m_pOkCancel_HBoxLayout->addWidget(pOK_PushButton);
// 	m_pOkCancel_HBoxLayout->addSpacing(10);
// 	m_pOkCancel_HBoxLayout->addWidget(pCancel_PushButton);
// 	m_pOkCancel_HBoxLayout->addStretch();
// 	m_pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);
// 	pAllVLayout->addLayout(m_pOkCancel_HBoxLayout);
	this->setLayout(pAllVLayout);

	m_pRecvPkgTimer = new QTimer();
	m_bIsClearPkg = false;

	m_pStartMonitor_PushButton->setEnabled(true);
	m_pStopMonitor_PushButton->setEnabled(false);

	SetPkgMonitorFont();

	connect(m_pRecvPkgTimer,SIGNAL(timeout()),this,SLOT(slot_TimerOut()));
// 	connect(pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
// 	connect(pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pStartMonitor_PushButton, SIGNAL(clicked()), this, SLOT(slot_StartMonitorClicked()));
	connect(m_pStopMonitor_PushButton, SIGNAL(clicked()), this, SLOT(slot_StopMonitorClicked()));
	connect(m_pClearList_PushButton, SIGNAL(clicked()), this, SLOT(slot_ClearListrClicked()));
	connect(m_pExportMonitor_PushButton, SIGNAL(clicked()), this, SLOT(slot_ExportClicked()));
	connect(m_pLeftPkgMonitorGrid,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(slot_TabSelectRowChange(QTableWidgetItem*)));
}

void QSttCommCfgPkgMonitorWidget::SetPkgMonitorFont()
{
	if (g_pSttGlobalFont == NULL)
	{
		return;
	}

	m_pStartMonitor_PushButton->setFont(*g_pSttGlobalFont);
	m_pStopMonitor_PushButton->setFont(*g_pSttGlobalFont);
	m_pClearList_PushButton->setFont(*g_pSttGlobalFont);
	m_pExportMonitor_PushButton->setFont(*g_pSttGlobalFont);
}

void QSttCommCfgPkgMonitorWidget::ReleaseUI()
{

}

void QSttCommCfgPkgMonitorWidget::InitDatas()
{

}

void QSttCommCfgPkgMonitorWidget::DeleteCommCfgDeviceWidget()
{
	if(m_bIsCreateWidget)
	{
		if(m_pCommCfgDeviceWidget)
		{
			delete m_pCommCfgDeviceWidget;
			m_pCommCfgDeviceWidget = NULL;
			g_theTestCntrFrame->m_pEngineClientWidget = NULL;
		}
	}
}

void QSttCommCfgPkgMonitorWidget::slot_TimerOut()
{
	//正在清空报文列表，暂时不更新列表
	if(m_bIsClearPkg)
	{
		return;
	}
	//更新报文列表数据
	int nRowCount = m_pLeftPkgMonitorGrid->rowCount();
	int nlstCount = m_pCommCfgDeviceWidget->m_lstSttParas.size();
	if(nRowCount >= nlstCount)
	{
		return;
	}
	m_pLeftPkgMonitorGrid->SetRowCount(nlstCount);

	for(int i = nRowCount; i < nlstCount; i++)
	{
		CSttParas *pTemp = m_pCommCfgDeviceWidget->m_lstSttParas[i];
		m_pLeftPkgMonitorGrid->ShowData(pTemp,i);
	}
}

void QSttCommCfgPkgMonitorWidget::slot_StartMonitorClicked()
{
	if(m_pRecvPkgTimer->isActive())
	{
		CString strMsgText;
		strMsgText = _T("已经监听报文，不能重复开始！");
		CXMessageBox::information(this, /*tr("提示")*/g_sLangTxt_Message, /*tr("已经监听报文，不能重复开始！")*/strMsgText);
		return;
	}
	m_pRecvPkgTimer->start(2000);
	m_pCommCfgDeviceWidget->m_bIsStarPkgMonitor = TRUE;
	m_pStartMonitor_PushButton->setEnabled(false);
	m_pStopMonitor_PushButton->setEnabled(true);
}

void QSttCommCfgPkgMonitorWidget::slot_StopMonitorClicked()
{
	if(m_pRecvPkgTimer->isActive())
	{
		m_pRecvPkgTimer->stop();
		m_pCommCfgDeviceWidget->m_bIsStarPkgMonitor = FALSE;
		m_pStartMonitor_PushButton->setEnabled(true);
		m_pStopMonitor_PushButton->setEnabled(false);
	}
}

void QSttCommCfgPkgMonitorWidget::slot_ClearListrClicked()
{
	m_bIsClearPkg = TRUE;
	int nRowCount = m_pLeftPkgMonitorGrid->rowCount();
	int nlstCount = m_pCommCfgDeviceWidget->m_lstSttParas.size();

	int nDelCount = 0;
	while(nDelCount < nRowCount)
	{
		CSttParas* pSttParas = m_pCommCfgDeviceWidget->m_lstSttParas.at(0);
		m_pCommCfgDeviceWidget->m_lstSttParas.removeAt(0);
		delete pSttParas;
		pSttParas = NULL;
		nDelCount++;
	}
	m_pLeftPkgMonitorGrid->clearContents();
	m_pLeftPkgMonitorGrid->setRowCount(0);
	m_bIsClearPkg = FALSE;
}

void QSttCommCfgPkgMonitorWidget::slot_ExportClicked()
{
	if(m_bIsClearPkg)
	{
		return;
	}

	CString strfilePath;
	QStringList astrPostfix;
#ifdef _PSX_QT_LINUX_
	strfilePath = _P_GetWorkspacePath();
	astrPostfix<<"*.txt";
	QSttPopupSaveAsDialog dlg(strfilePath, astrPostfix,"", this);
	dlg.InitUI();
	dlg.InitTitle(_T("导出报告"));
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		dlg.resize(850,500);
		dlg.setFixedHeight(500);
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::CHINESE);

	if (dlg.exec() != QDialog::Accepted)
	{
		QSoftKeyBoard::ReAttachObj();
		return;
	}
	QSoftKeyBoard::ReAttachObj();
#else
	if (dlg.exec() != QDialog::Accepted)
	{
		return;
	}
#endif
	strfilePath = dlg.GetFilePath();
#else		
	strfilePath = QFileDialog::getSaveFileName(NULL, "导出报告", _P_GetWorkspacePath(), "txt报告(*.txt)");
#endif

  UINT nOpenMode = CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive;
#ifdef _PSX_IDE_QT_
  nOpenMode |= CFile::modeTruncate;
#endif
 	if (!strfilePath.isEmpty()) 
 	{
		CFile file/*(strfilePath)*/;
#ifdef _PSX_QT_LINUX_
		QTextCodec *pOldTextCodec = NULL;
		InitLocalCodec_BeforeReadWrite(strfilePath,&pOldTextCodec);
#endif
		BOOL bRet = file.Open(strfilePath, nOpenMode);

#ifdef _PSX_QT_LINUX_
		ResetLocalCodec(pOldTextCodec);
#endif
		if(bRet)
		//if (file.open(QIODevice::WriteOnly | QIODevice::Text)) 
		{
			//QTextStream out(&file);
	int nRowCount = m_pLeftPkgMonitorGrid->rowCount();
	int nlstCount = m_pCommCfgDeviceWidget->m_lstSttParas.size();
	int nSaveCount = nRowCount;
	if(nRowCount > nlstCount)
	{
		nSaveCount = nlstCount;
	}
			for (int i = 0; i< nSaveCount ; i++)
	{
		CSttParas* pSttParas = NULL;
		pSttParas = m_pCommCfgDeviceWidget->m_lstSttParas[i];
				CString strMsg,strValue;
				long nDir = 0;
				pSttParas->GetDataValue("Time",strValue);
				pSttParas->GetDataValue("Dir",nDir);

				if (nDir)
				{
					strMsg.Format("%d.接收时间(%s),原始报文:", i + 1, strValue.GetString());
				} 
				else
				{
					strMsg.Format("%d.发送时间(%s),原始报文:",i + 1,strValue.GetString());
				}
				pSttParas->GetDataValue("Pkg",strValue);
				strMsg += strValue + "\n";
				
				const char* szMsg = strMsg.GetString(); 
				file.Write(szMsg, strlen(szMsg));

				//out << strMsg << "\n";
			}
			file.Close();
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("报文监听文件%s导出成功."),strfilePath.GetString());  
			CXMessageBox::information(this, "提示", "文件导出成功.");
	}
	else
	{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("无法打开文件%s"),strfilePath.GetString());
		CXMessageBox::information(this, "提示", "文件导出失败.");
	}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("报文监听文件%s导出失败."),strfilePath.GetString());  
		CXMessageBox::information(this, "提示", "文件导出失败.");
	}

#ifdef _PSX_QT_LINUX_  
	system("sync");
#endif
}

void QSttCommCfgPkgMonitorWidget::slot_TabSelectRowChange(QTableWidgetItem *item)
{
	if(item == NULL)    return;

	if(m_bIsClearPkg)
	{
		return;
	}

	int nCurrentRow = item->row();
	int nAllRow = m_pLeftPkgMonitorGrid->rowCount();
	int nLstCount = m_pCommCfgDeviceWidget->m_lstSttParas.size();
	if(nCurrentRow < 0 || nCurrentRow > nAllRow || nCurrentRow > nLstCount)
	{
		return;
	}

	CSttParas* pSttParas = NULL;
	pSttParas = m_pCommCfgDeviceWidget->m_lstSttParas[nCurrentRow];
	if(pSttParas == NULL)  return;

	m_pRightPkgMonitorGrid->ShowData(pSttParas,0);
}

// void QSttCommCfgPkgMonitorWidget::slot_OKClicked()
// {
// 	DeleteCommCfgDeviceWidget();
// 
// 	close();
// }

// void QSttCommCfgPkgMonitorWidget::slot_CancelClicked()
// {
// 	DeleteCommCfgDeviceWidget();
// 	close();
// }


