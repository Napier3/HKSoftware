#include "QChMapsDlg.h"
#include <QDirIterator>
#include "../../../SttCmd/SttParas.h"
#include "../../../SttGlobalDef.h"
#include "../../Module/System/TickCount32.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../CommonMethod/commonMethod.h"
#include "../../Module/OSInterface/QT/XMessageBox.h"
#include "../PopupDialog/SttPopupOpenDialog.h"
#include "../PopupDialog/SttPopupSaveAsDialog.h"
#include "../Module/XLangResource_Native.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#include "../../../SttSystemConfig/SttSystemConfig.h"
#endif

#include "../../../SttSystemConfig/SttSystemConfig.h"

QChMapsDlg::QChMapsDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
//	setWindowFlags(Qt::WindowCloseButtonHint);
	CString strName;
	xlang_GetLangStrByFile(strName,"ChMaps_Title");

	setWindowTitle(strName);
	m_pChMapsWidget = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_bSysParasHasChanged = FALSE;
}

QChMapsDlg::~QChMapsDlg()
{

}

void QChMapsDlg::initUI()
{
	ReleaseUI();
	resize(700, 400);//wangtao 620->700 20240507 ����������ӳ�乴ѡ��
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	m_pAllVLayout = new QVBoxLayout(this);

	m_pChMapsWidget = new QChMapsWidget(this);
	m_pChMapsWidget->setFont(font());
	m_pAllVLayout->addWidget(m_pChMapsWidget);

	m_pLockMaps_CheckBox = new QSttCheckBox/*(m_pOutputSel_GroupBox)*/;
	xlang_SetLangStrToWidget(m_pLockMaps_CheckBox, "ChMaps_LockMaps", XLang_Ctrls_QCheckBox);
	//m_pLockMaps_CheckBox->setText("����ӳ��");
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

	g_oSttTestResourceMngr.InitLocalSysPara();
	InitDatas();
 	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
 	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pDefautMaps_PButton, SIGNAL(clicked()), this, SLOT(slot_DefautMapsClicked()));
	connect(m_pImportChMaps_PButton, SIGNAL(clicked()), this, SLOT(slot_ImportChMapsClicked()));
	connect(m_pExportChMaps_PButton, SIGNAL(clicked()), this, SLOT(slot_ExportChMapsClicked()));

	if (g_oSttSystemConfig.GetLockMaps() != 0)
	{
        m_pLockMaps_CheckBox->setChecked(true);
	}
    connect(m_pLockMaps_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_LockMapsChecked(int)));
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
}

void QChMapsDlg::slot_OKClicked()
{
	m_pOK_PushButton->setDisabled(true);
	m_pChMapsWidget->SaveDatas();
	m_bSysParasHasChanged = FALSE;

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
	//wangtao 20240504 ���±�����ʹ����Name����һ��
	m_oSttChMaps.UpdateAliasByName();
	m_oSttChMaps.Copy(&g_oSttTestResourceMngr.m_oChMaps);
	g_oSttTestResourceMngr.SaveCurChMapsFile();
	g_oSttSystemConfig.SaveSystemConfig();//����ϵͳ����
//	emit sig_UpdateChRsMaps(bSysParasHasChanged);
	accept();
//	m_pOK_PushButton->setDisabled(false);
}

void QChMapsDlg::slot_CancelClicked()
{
	close();
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
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("ȱ��Ӳ����Դ�ļ�,�޷�����ȱʡͨ��ӳ��."));
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_MissingDefaultMappings.GetString()); //ȱ��Ӳ����Դ�ļ�,�޷�����ȱʡͨ��ӳ�� lcq 3.14
		return;
	}

	m_pChMapsWidget->ShowDatas(&m_oSttChMaps);
}

void QChMapsDlg::slot_ImportChMapsClicked()
{
	CString strDBPath,strFilePath,strTmp;
	QStringList astrPostfix;
	strDBPath = _P_GetDBPath();
	strTmp = _T("*.") + g_oSttTestResourceMngr.m_pTestResouce->GetChMapsFilePostfix();
	astrPostfix<<strTmp;	
//chenling 2024.8.26 
#ifdef _PSX_QT_LINUX_
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
#else
	strFilePath = QFileDialog::getOpenFileName(0, _T("ѡ��ͨ��ӳ���ļ�"),strDBPath,strTmp);
#endif

	if (!strFilePath.IsEmpty())
	{
		m_oSttChMaps.OpenChMapsFile(strFilePath);
		m_pChMapsWidget->ShowDatas(&m_oSttChMaps);
	}
}

void QChMapsDlg::slot_ExportChMapsClicked()
{
	CString strDBPath = _P_GetDBPath();
	CString strFilePath;

	QDir dir;
	if (!dir.exists(strDBPath))
	{
		if(!dir.mkpath(strDBPath))
		{
			//CXMessageBox::information(NULL, QObject::tr("��ʾ"), QObject::tr("����ͨ��ӳ��ȱʡ·��ʧ��."));
			CXMessageBox::information(NULL,g_sLangTxt_Message.GetString(), g_sLangTxt_Gradient_FailDefaultPath.GetString()); // ��ʾ ����ͨ��ӳ��ȱʡ·��ʧ�� lcq 3.14
			return ;
		}
	}

	QStringList astrPostfix;
	CString strTmp;
	strTmp = _T("*.") + g_oSttTestResourceMngr.m_pTestResouce->GetChMapsFilePostfix();
	astrPostfix<<strTmp;

#ifdef _PSX_QT_LINUX_
	QSttPopupSaveAsDialog dlg(strDBPath, astrPostfix,_T(""), this);
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

#else
	strFilePath = QFileDialog::getSaveFileName(0, _T("ͨ��ӳ���ļ����Ϊ"),strDBPath,strTmp);
#endif

		if (m_oSttChMaps.SaveChMapsFile(strFilePath))
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("����ͨ��ӳ���ļ�[%s]�ɹ�."),strFilePath.GetString());
              CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_ExportfileSucceeded.GetString(),strFilePath.GetString()); // ����ͨ��ӳ���ļ�[%s]�ɹ�.
		}
		else
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("����ͨ��ӳ���ļ�[%s]ʧ��."),strFilePath.GetString());
			CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_Failedtofile.GetString(),strFilePath.GetString());  //����ͨ��ӳ���ļ�[%s]ʧ��.
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
