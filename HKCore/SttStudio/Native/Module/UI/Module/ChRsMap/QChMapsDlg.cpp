#include "QChMapsDlg.h"
#include <QDirIterator>
#include "../../../SttCmd/SttParas.h"
#include "../../../SttGlobalDef.h"
#include "../../../Module/System/TickCount32.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../CommonMethod/commonMethod.h"
#include "../../../Module/OSInterface/QT/XMessageBox.h"
#include "../PopupDialog/SttPopupOpenDialog.h"
#include "../PopupDialog/SttPopupSaveAsDialog.h"
#include "../Module/XLangResource_Native.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#include "../../../SttSystemConfig/SttSystemConfig.h"
#endif

#include "../../../SttSystemConfig/SttSystemConfig.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QFileDialog>

extern void Stt_Global_NoticeUpdateBinBinary();	//20240912 huangliang 更新通知各界面刷新信息

QChMapsDlg::QChMapsDlg(QWidget *parent)
	: QDialog(parent)
{
	//2024-10-30 wuxinyi 应北京需求，窗口需可最大最小化
#ifdef _PSX_QT_WINDOWS_
	setWindowFlags(/*Qt::Dialog |*/ Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::Window | Qt::WindowCloseButtonHint);
#else
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
#endif

//	setWindowFlags(Qt::WindowCloseButtonHint);
	CString strName;
	xlang_GetLangStrByFile(strName,"ChMaps_Title");

	setWindowTitle(strName);
	m_pChMapsWidget = NULL;
	m_pBinMapsGrid = NULL;//20240905 huangliang 
	m_pBoutMapsGrid = NULL;
	m_pTabWidget = NULL;

	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_bSysParasHasChanged = FALSE;

	m_strChMapsRelPath = _T("");
	m_strChMapsFileName = _T("");
}

QChMapsDlg::~QChMapsDlg()
{
	m_olistBin.DeleteAll();
	m_olistBout.DeleteAll();
}

void QChMapsDlg::initUI()
{
	ReleaseUI();
	resize(700, 400);//wangtao 620->700 20240507 增加了锁定映射勾选框
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	m_pAllVLayout = new QVBoxLayout(this);

	//20240905 huangliang 
	m_pChMapsWidget = new QChMapsWidget(this);
	m_pBinMapsGrid = new CBinBoutMapsGrid(this, BINBOUT_MAPS_TYPE_BIN);
	m_pBoutMapsGrid = new CBinBoutMapsGrid(this, BINBOUT_MAPS_TYPE_BOUT);
	m_pBinMapsGrid->InitGrid();
	m_pBoutMapsGrid->InitGrid();

	m_pChMapsWidget->setFont(font());
	m_pBinMapsGrid->setFont(font());
	m_pBoutMapsGrid->setFont(font());

	m_pTabWidget = new QTabWidget(this);
    m_pTabWidget->addTab(m_pChMapsWidget, "test1");
    m_pTabWidget->addTab(m_pBinMapsGrid, "test2");
    m_pTabWidget->addTab(m_pBoutMapsGrid, "test3");
	m_pAllVLayout->addWidget(m_pTabWidget);
	//m_pAllVLayout->addWidget(m_pChMapsWidget);

	m_pLockMaps_CheckBox = new QSttCheckBox/*(m_pOutputSel_GroupBox)*/;
	xlang_SetLangStrToWidget(m_pLockMaps_CheckBox, "ChMaps_LockMaps", XLang_Ctrls_QCheckBox);
	//m_pLockMaps_CheckBox->setText("锁定映射");
	m_pLockMaps_CheckBox->setChecked(false);

	m_pDefautMaps_PButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pDefautMaps_PButton, "ChMaps_DefautMaps", XLang_Ctrls_QPushButton);
	m_pDefautMaps_PButton->setEnabled(true);
//	m_pChMapsSet_HBoxLayout->addWidget(m_pDefautMaps_PButton);

//	m_pChMapsSet_HBoxLayout->addStretch();

	m_pImportChMaps_PButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pImportChMaps_PButton, "ChMaps_ImportChMaps", XLang_Ctrls_QPushButton);
	m_pImportChMaps_PButton->setEnabled(true);
//	m_pChMapsSet_HBoxLayout->addWidget(m_pImportChMaps_PButton);

	m_pExportChMaps_PButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pExportChMaps_PButton, "ChMaps_ExportChMaps", XLang_Ctrls_QPushButton);
	m_pExportChMaps_PButton->setEnabled(true);
//	m_pChMapsSet_HBoxLayout->addWidget(m_pExportChMaps_PButton);


	m_pOK_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pOK_PushButton, "sOK", XLang_Ctrls_QPushButton);

	m_pCancel_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pCancel_PushButton, "sCancel", XLang_Ctrls_QPushButton);

	m_pBottom_HBoxLayout = new QHBoxLayout(this);
	m_pBottom_HBoxLayout->addWidget(m_pLockMaps_CheckBox);
    m_pBottom_HBoxLayout->addSpacing(10);
	m_pBottom_HBoxLayout->addWidget(m_pDefautMaps_PButton);
	m_pBottom_HBoxLayout->addSpacing(10);
	m_pBottom_HBoxLayout->addWidget(m_pImportChMaps_PButton);
	m_pBottom_HBoxLayout->addSpacing(10);
	m_pBottom_HBoxLayout->addWidget(m_pExportChMaps_PButton);
	m_pBottom_HBoxLayout->addStretch();
	m_pBottom_HBoxLayout->addWidget(m_pOK_PushButton);
	m_pBottom_HBoxLayout->addSpacing(10);
	m_pBottom_HBoxLayout->addWidget(m_pCancel_PushButton);
//	m_pBottom_HBoxLayout->addStretch();
	m_pBottom_HBoxLayout->setDirection(QBoxLayout::LeftToRight);
	m_pAllVLayout->addLayout(m_pBottom_HBoxLayout);
	this->setLayout(m_pAllVLayout);

	if (!g_oSttTestResourceMngr.SelectDeviceFromLocalDB())
	{
		m_pOK_PushButton->setDisabled(true);
	}

	if (g_oSttSystemConfig.GetLockMaps() != 0)
	{
		m_pLockMaps_CheckBox->setChecked(true);
	}
	connect(m_pLockMaps_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_LockMapsChecked(int)));

	g_oSttTestResourceMngr.InitLocalSysPara();
	if (!(g_oSttTestResourceMngr.HasLoadChMaps()))
	{
		if (m_pLockMaps_CheckBox->isChecked())
		{
			CString strSavePath;

#ifdef _PSX_QT_LINUX_
			strSavePath = g_oSttTestResourceMngr.GetRsDirPath_Device();
#else
			strSavePath = g_oSttTestResourceMngr.GetCurSelDirPath_SN();
#endif

			strSavePath += _T("ChMapConfig.sync");
			g_oSttTestResourceMngr.OpenChMapsFile(strSavePath);
		}
		else
		{
			g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&g_oSttTestResourceMngr.m_oChMaps,g_oSystemParas.m_nIecFormat ,g_oSystemParas.m_nHasDigital);
		}
	}

	InitDatas();
 	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
 	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pDefautMaps_PButton, SIGNAL(clicked()), this, SLOT(slot_DefautMapsClicked()));
	connect(m_pImportChMaps_PButton, SIGNAL(clicked()), this, SLOT(slot_ImportChMapsClicked()));
	connect(m_pExportChMaps_PButton, SIGNAL(clicked()), this, SLOT(slot_ExportChMapsClicked()));

	
}

void QChMapsDlg::ReleaseUI()
{

}

void QChMapsDlg::DisableCtrls_SysCfg()
{
	if (m_pChMapsWidget == NULL)
	{
		return;
	}

	m_pChMapsWidget->DisableCtrls_SysCfg();
}

void QChMapsDlg::InitDatas()
{
	m_oSttChMaps.DeleteAll();
	g_oSttTestResourceMngr.m_oChMaps.Copy(&m_oSttChMaps);
	g_oSystemParas.CopyOwn(&m_oSysParas);
	m_pChMapsWidget->initUI(&m_oSysParas,&m_oSttChMaps);

	////20240921 huangliang	//20241011 huangliang	移到此处，设置缺省值和导入通道时才能改变
	//m_olistBin.DeleteAll();
	//m_olistBout.DeleteAll();
	//m_oSttChMaps.CreateBinToList(&m_olistBin);
	////m_oSttChMaps.CreateBinExToList(&m_olistBin);	//20240923 huangliang 暂时不编辑扩展
	//m_oSttChMaps.CreateBoutToList(&m_olistBout);
	////m_oSttChMaps.CreateBoutExToList(&m_olistBout);
	SetGridShowDatas();	
}

void QChMapsDlg::slot_OKClicked()
{
	//20240921 huangliang 
	m_oSttChMaps.ReadListToBin(&m_olistBin);
	m_oSttChMaps.ReadListToBout(&m_olistBout);

	m_pOK_PushButton->setDisabled(true);
	m_pChMapsWidget->SaveDatas();
	m_bSysParasHasChanged = FALSE;
	BOOL bNeedCreateDefaultChMaps = FALSE;
	CString strType;
    QString strMsg = "test4";

	if (m_oSysParas.m_nHasAnalog && (!m_oSttChMaps.HasMapHdResource(STT_MODULETYPE_ID_ANALOG)))
	{
		bNeedCreateDefaultChMaps = TRUE;
		strType = g_sLangTxt_AnalogValue;
		strMsg = QString(strMsg).arg(strType);
	}
	else if (m_oSysParas.m_nHasDigital && (!m_oSttChMaps.HasMapHdResource(STT_MODULETYPE_ID_DIGITAL)))
	{
		bNeedCreateDefaultChMaps = TRUE;
		strType = g_sLangTxt_ChMaps_DigitalCh;
		strMsg = QString(strMsg).arg(strType);
	}
	else if (m_oSysParas.m_nHasWeek && (!m_oSttChMaps.HasMapHdResource(STT_MODULETYPE_ID_WEEK)))
	{
		bNeedCreateDefaultChMaps = TRUE;
		strType = g_sLangTxt_ChMaps_WeekCh;
		strMsg = QString(strMsg).arg(strType);
	}

	if (bNeedCreateDefaultChMaps)
	{
		CString strTitle = g_sLangTxt_Message;

		CXMessageBox messageBox;
		messageBox.setWindowTitle(strTitle);
		messageBox.setText(strMsg);
		QPushButton *yesButton = messageBox.addButton(/*tr("是")*/g_sLangTxt_State_Yes, QMessageBox::YesRole);
		QPushButton *noButton = messageBox.addButton(/*tr("否")*/g_sLangTxt_State_No, QMessageBox::NoRole);
		messageBox.setDefaultButton(yesButton);
		messageBox.setIcon(QMessageBox::NoIcon); // 设置图标为空
		messageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

		int result = messageBox.exec();

		if (result == 0)//是
		{
			g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&m_oSttChMaps, m_oSysParas.m_nIecFormat, m_oSysParas.m_nHasDigital, m_oSysParas.m_nHasWeek);
		}
	}

	
	//2024-11-15 wuxinyi 无通道映射，弹窗是否创建缺省
//	if (m_oSysParas.m_nHasDigital == 1 && g_oSystemParas.m_nHasDigital == 0)
//	{
//// 		int nDigtalCount = g_oSttTestResourceMngr.GetDigitalModuleNum();
//		strType = /*_T("数字量")*/g_sLangTxt_ChMaps_DigitalCh;
//// 		if (nDigtalCount == 0)
//		{		
//			strMsg = QString(strMsg).arg(strType);
//			CString strTitle = g_sLangTxt_Message;
//			CXMessageBox messageBox;
//			messageBox.setWindowTitle(strTitle);
//			messageBox.setText(strMsg);
//			QPushButton *yesButton = messageBox.addButton(/*tr("是")*/g_sLangTxt_State_Yes, QMessageBox::YesRole);
//			QPushButton *noButton = messageBox.addButton(/*tr("否")*/g_sLangTxt_State_No, QMessageBox::NoRole);
//			messageBox.setDefaultButton(yesButton);
//			messageBox.setIcon(QMessageBox::NoIcon); // 设置图标为空
//			messageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
//
//			int result = messageBox.exec();
//
//			if (result == 0)//是
//			{
//				g_oSttTestResourceMngr.CreateDefaultChMapsByDevice_Digital(&m_oSttChMaps, m_oSysParas.m_nIecFormat);
//			}
//		}
//	}
//
//	if (m_oSysParas.m_nHasWeek == 1 && g_oSystemParas.m_nHasWeek == 0)
//	{
//		strType = g_sLangTxt_ChMaps_WeekCh;
//		strMsg.arg(strType);
//		CString strTitle = /*_T("提示")*/g_sLangTxt_Message;
//		CXMessageBox messageBox;
//		messageBox.setWindowTitle(strTitle);
//		messageBox.setText(strMsg);
//		QPushButton *yesButton = messageBox.addButton(/*tr("是")*/g_sLangTxt_State_Yes, QMessageBox::YesRole);
//		QPushButton *noButton = messageBox.addButton(/*tr("否")*/g_sLangTxt_State_No, QMessageBox::NoRole);
//		messageBox.setDefaultButton(yesButton);
//		messageBox.setIcon(QMessageBox::NoIcon); // 设置图标为空
//		messageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
//
//		int result = messageBox.exec();
//
//		if (result == 0)//是
//		{
//			g_oSttTestResourceMngr.CreateDefaultChMapsByDevice_Weak(&m_oSttChMaps);
//		}
//
//	}

	if ((m_oSysParas.m_nHasAnalog != g_oSystemParas.m_nHasAnalog)||(m_oSysParas.m_nHasDigital != g_oSystemParas.m_nHasDigital)
		||(m_oSysParas.m_nHasWeek != g_oSystemParas.m_nHasWeek)||(m_oSysParas.m_nIecFormat != g_oSystemParas.m_nIecFormat))
	{
		g_oSystemParas.m_nHasAnalog = m_oSysParas.m_nHasAnalog;
		g_oSystemParas.m_nHasDigital = m_oSysParas.m_nHasDigital;
		g_oSystemParas.m_nHasWeek = m_oSysParas.m_nHasWeek;
		g_oSystemParas.m_nIecFormat = m_oSysParas.m_nIecFormat;
		m_bSysParasHasChanged = TRUE;
		g_oSttTestResourceMngr.SaveSystemParasFile();
	}

	g_oSttTestResourceMngr.m_oChMaps.DeleteAll();
	//wangtao 20240504 更新别名，使其与Name保持一致
	m_oSttChMaps.UpdateAliasByName();
	m_oSttChMaps.Copy(&g_oSttTestResourceMngr.m_oChMaps);

	g_oSttTestResourceMngr.SaveCurChMapsFile();
	g_oSttSystemConfig.SaveSystemConfig();//保存系统配置

	//20240912 huangliang 通知更新界面	
	Stt_Global_NoticeUpdateBinBinary();

//	emit sig_UpdateChRsMaps(bSysParasHasChanged);
	accept();
//	m_pOK_PushButton->setDisabled(false);
}

void QChMapsDlg::slot_CancelClicked()
{
// 	close();
	reject();
}

void QChMapsDlg::slot_DefautMapsClicked()
{
	BOOL bHasDigital = FALSE;

	if (m_pChMapsWidget->IsDigitalSelected())
	{
		bHasDigital = TRUE;
	}

	if (!g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&m_oSttChMaps,m_oSysParas.m_nIecFormat,bHasDigital))
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("缺少硬件资源文件,无法创建缺省通道映射."));
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_MissingDefaultMappings.GetString()); //缺少硬件资源文件,无法创建缺省通道映射 lcq 3.14
		return;
	}
	
	//m_pChMapsWidget->ShowDatas(&m_oSttChMaps);	//20240919 huangliang 移到函数SetGridShowDatas中执行 
	SetGridShowDatas();  
}

void QChMapsDlg::slot_ImportChMapsClicked()
{
	CString strDBPath,strFilePath,strTmp;
	QStringList astrPostfix;
	strDBPath = _P_GetDBPath();
	if (g_oSttTestResourceMngr.m_pTestResouce == NULL)
	{
		strTmp = _T("*.sync");
	}
	else
	{
	strTmp = _T("*.") + g_oSttTestResourceMngr.m_pTestResouce->GetChMapsFilePostfix();
	}
	
	astrPostfix<<strTmp;
	if (m_strChMapsRelPath != _T(""))
	{
		QFileInfo fileInfo(m_strChMapsRelPath);
		strDBPath = fileInfo.absolutePath();
	}
#ifdef _PSX_QT_WINDOWS_//20241119 luozibing 在Win环境下 在资源管理器打开上次导出文件路径

	CString strText = /*_T("选择需要打开的文件")*/g_sLangTxt_Native_ChooseOpenFile;
	QFileDialog dlg(this, strText);
	dlg.setFileMode(QFileDialog::AnyFile);

	QDir dir(strDBPath);
	if (!dir.exists(strDBPath))
	{
		strDBPath = _P_GetDBPath();
	}

	dlg.setDirectory(dir);
	if (m_strChMapsFileName != _T(""))
	{
		dlg.selectFile(m_strChMapsFileName);
	}
	dlg.setNameFilters(astrPostfix);
	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);

	strText = /*_T("文件目录：")*/g_sLangTxt_Gradient_DirectoryFile;
	dlg.setLabelText(QFileDialog::LookIn, strText);
	strText = /*_T("文件名称：")*//*g_sLangTxt_Gradient_FmFileName*/g_sLangTxt_Native_FileName + ":";
	dlg.setLabelText(QFileDialog::FileName, strText);
	strText = /*_T("文件类型")*/g_sLangTxt_Native_FileType;
	dlg.setLabelText(QFileDialog::FileType, strText);
	strText = /*_T("打开")*/g_sLangTxt_OpenTip;
	dlg.setLabelText(QFileDialog::Accept, strText);
	strText = /*_T("取消")*/g_sLangTxt_Cancel;
	dlg.setLabelText(QFileDialog::Reject, strText);

	CString strFileName;
	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strFileName = fileNames.at(0);
		CString strCurrPostfix = dlg.selectedNameFilter();
		strCurrPostfix.replace("*.", "");
		strFilePath = ChangeFilePostfix(strFileName, strCurrPostfix);
	}
#else
/*#ifdef _PSX_QT_LINUX_*/
	QSttPopupOpenDialog oOpenDlg(strDBPath,astrPostfix,this);
	oOpenDlg.setFont(font());
	oOpenDlg.InitUI();
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		oOpenDlg.resize(850,600);
		oOpenDlg.setFixedHeight(500);
	}
	
	if (oOpenDlg.exec() != QDialog::Accepted)
		return;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return;
	}
#endif
	if (strFilePath != "")
	{	
		if (m_oSttChMaps.OpenChMapsFile(strFilePath))
	{
			m_strChMapsRelPath = strFilePath;
			QFileInfo fileInfo(m_strChMapsRelPath);
			m_strChMapsFileName = fileInfo.fileName();
		}
		//m_pChMapsWidget->ShowDatas(&m_oSttChMaps);	//20240919 huangliang 移到函数SetGridShowDatas中执行 
		SetGridShowDatas();//20240905 huangliang
	}
}

void QChMapsDlg::slot_ExportChMapsClicked()
{
	CString strDBPath = _P_GetDBPath();
	CString strFilePath;

#ifdef _PSX_QT_WINDOWS_//20241114 luozibing 在Win环境下 在资源管理器打开上次保存文件路径
	if (m_strChMapsRelPath != _T(""))
	{
		QFileInfo fileInfo(m_strChMapsRelPath);
		strDBPath = fileInfo.absolutePath();
	}
#endif

	QDir dir(strDBPath);
	if (!dir.exists(strDBPath))
	{
		if(!dir.mkpath(strDBPath))
		{
			//CXMessageBox::information(NULL, QObject::tr("提示"), QObject::tr("创建通道映射缺省路径失败."));
			CXMessageBox::information(NULL,g_sLangTxt_Message.GetString(), g_sLangTxt_Gradient_FailDefaultPath.GetString()); // 提示 创建通道映射缺省路径失败 lcq 3.14
			return ;
		}
	}

	QStringList astrPostfix;
	CString strTmp;
	if (g_oSttTestResourceMngr.m_pTestResouce == NULL)
	{
		strTmp = _T("*.sync") ;
	}
	else
	{
	strTmp = _T("*.") + g_oSttTestResourceMngr.m_pTestResouce->GetChMapsFilePostfix();
	}

	astrPostfix<<strTmp;
#ifdef _PSX_QT_LINUX_

	QSttPopupSaveAsDialog dlg(strDBPath, astrPostfix, m_strChMapsFileName, this);
	dlg.m_strRelFolderPath = m_strChMapsRelPath;//20241113 luozibing 设置上次保存导出通道映射文件信息
	dlg.InitUI();
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		dlg.resize(850,500);
		dlg.setFixedHeight(500);
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::ENGLISH);
#endif

	if (dlg.exec() != QDialog::Accepted)
	{
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif
	return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif
	strFilePath = dlg.GetFilePath();
//#endif

//#ifdef _PSX_QT_WINDOWS_
#else

	CString strText = /*_T("文件另存为")*/g_sLangTxt_IEC_FileSaveAs;
	QFileDialog dlg(this, strText);
	dlg.setFileMode(QFileDialog::AnyFile);
	dlg.setDirectory(dir);
	if (m_strChMapsFileName != _T(""))
	{
		dlg.selectFile(m_strChMapsFileName);//20241114 luozibing 在Win环境下 设置文件名为上次保存文件名
	}

	dlg.setNameFilters(astrPostfix);
	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptSave);
	
	strText = /*_T("文件目录：")*/g_sLangTxt_Gradient_DirectoryFile;
	dlg.setLabelText(QFileDialog::LookIn, strText);
	strText = /*_T("文件名称：")*//*g_sLangTxt_Gradient_FmFileName*/g_sLangTxt_Native_FileName + ":";
	dlg.setLabelText(QFileDialog::FileName, strText);
	strText = /*_T("文件类型")*/g_sLangTxt_Native_FileType;
	dlg.setLabelText(QFileDialog::FileType, strText);
	strText = /*_T("保存")*/g_sLangTxt_Save;
	dlg.setLabelText(QFileDialog::Accept, strText);
	strText = /*_T("取消")*/g_sLangTxt_Cancel;
	dlg.setLabelText(QFileDialog::Reject, strText);

	CString strFileName;
	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strFileName = fileNames.at(0);
		CString strCurrPostfix = dlg.selectedNameFilter();
		strCurrPostfix.replace("*.", "");
		strFilePath = ChangeFilePostfix(strFileName, strCurrPostfix);
	}
#endif
	if (strFilePath == _T(""))
	{
		return;
	}
		if (m_oSttChMaps.SaveChMapsFile(strFilePath))
		{

#ifdef _PSX_QT_LINUX_
		m_strChMapsRelPath = dlg.m_strRelFolderPath;//20241113 luozibing 获取保存导出通道映射文件信息
		m_strChMapsFileName = dlg.m_strFileName;
//#endif
//#ifdef _PSX_QT_WINDOWS_
#else
		m_strChMapsRelPath = strFilePath;//20241114 luozibing 获取保存导出通道映射文件信息
		QFileInfo fileInfo(m_strChMapsRelPath);
		m_strChMapsFileName = fileInfo.fileName();
#endif
			//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("导出通道映射文件[%s]成功."),strFilePath.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST, g_sLangTxt_Gradient_ExportfileSucceeded.GetString(), strFilePath.GetString()); // 导出通道映射文件[%s]成功.
		}
		else
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("导出通道映射文件[%s]失败."),strFilePath.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST, g_sLangTxt_Gradient_Failedtofile.GetString(), strFilePath.GetString());  //导出通道映射文件[%s]失败.
		}
}
void QChMapsDlg::slot_LockMapsChecked(int nState)
{
	//g_oSttSystemConfig.SetLockMaps(nState);
	if (m_pLockMaps_CheckBox->checkState() == Qt::Checked)
	{
		g_oSttSystemConfig.SetLockMaps(1);
	}
	else
	{
		g_oSttSystemConfig.SetLockMaps(0);
	}
	
}

//20240905 huangliang  设置3个表格数据
void QChMapsDlg::SetGridShowDatas()
{
	//20241011 huangliang	移到此处，设置缺省值和导入通道时才能改变
	m_olistBin.DeleteAll();
	m_olistBout.DeleteAll();
	m_oSttChMaps.CreateBinToList(&m_olistBin);
	//m_oSttChMaps.CreateBinExToList(&m_olistBin);	//20240923 huangliang 暂时不编辑扩展
	m_oSttChMaps.CreateBoutToList(&m_olistBout);
	//m_oSttChMaps.CreateBoutExToList(&m_olistBout);

	m_pChMapsWidget->ShowDatas(&m_oSttChMaps);

	m_pBinMapsGrid->ShowDatas(&m_olistBin);
	m_pBoutMapsGrid->ShowDatas(&m_olistBout);
}
