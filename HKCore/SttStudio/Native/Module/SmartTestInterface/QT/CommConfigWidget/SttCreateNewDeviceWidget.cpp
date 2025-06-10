#include "SttCreateNewDeviceWidget.h"
#include "ui_SttCreateNewDeviceWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../Module/PopupDialog/SttPopupOpenDialog.h"
#include "../../../../Module/BaseClass/QT/ExBaseListComboBox.h"
#include "../../SttGlobalDef.h"

//2022-09-10  lijunqing
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../../../../61850/Module/61850ClientConfig/61850ClientConfig.h"
#include "../../../../61850/Module/MMS_STACK_CFG/MMS_STACK_CFG.h"
#include "../SttTestCntrFrameBase.h"
#include "../../../../IotProtoServer/Module/SttPxCommCmdDef.h"
#include "SttTestCntrFrameWin.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;

QSttCreateNewDeviceWidget::QSttCreateNewDeviceWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttCreateNewDeviceWidget)
{
    ui->setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

	m_strLocalIP = _T("172.21.0.100");
    m_font = font;
	UI_SetFont();
	ui->m_edtDevIP->setText(g_theGbSmartGenWzd->m_strDevIP);
	CString strPort;
	strPort.Format(_T("%d"), g_theGbSmartGenWzd->m_nDevPort);
	ui->m_edtDevPort->setText(strPort);

	CString strFileName;
	strFileName = GetFileNameFromFilePath(g_theGbSmartGenWzd->m_strDvmFile, '/');
	ui->m_edtDvmFile->setText(strFileName);
	ui->m_Btn_OK->setDisabled(true);//开始时默认禁用

	QRegExp regExp("^[1-9][0-9]{1,8}$");
	ui->m_edtDevPort->setValidator(new QRegExpValidator(regExp, this));

	ui->m_cmbProtolID->SetDefaultVisibleItems();
	connect(ui->m_cmbProtolID, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cmbEngineID_currentIndexChanged(int)));
	ex_InsertChildreComboBox(g_theGbSmartGenWzd->m_pProtocolEngineCfg, ui->m_cmbProtolID);
	ui->m_cmbProtolID->setCurrentIndex(0);

	//2022-9-28  lijunqing
	CDataGroup *pDeviceTypeDef = CGbWzdItemsNameLib::GetDeviceTypeDef();
	if (pDeviceTypeDef != NULL)
	{
		ex_InsertChildreComboBox(pDeviceTypeDef, ui->m_cmbDeviceType);
	}

	connect(ui->m_Btn_OK,SIGNAL(clicked()),this,SLOT(slot_OKClick()));
	connect(ui->m_Btn_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
	connect(ui->m_btnBrowseDvm,SIGNAL(clicked()),this,SLOT(slot_SelDvmFileClick()));
	connect(ui->m_btnBrowsePp,SIGNAL(clicked()),this,SLOT(slot_SelPpFileClick()));
	connect(ui->m_btnSelFromScl,SIGNAL(clicked()),this,SLOT(slot_SelIedFromSclClick()));
	connect(ui->m_btnAdvancedCfg,SIGNAL(clicked()),this,SLOT(slot_AdvancedCfgClick()));
}

QSttCreateNewDeviceWidget::~QSttCreateNewDeviceWidget()
{
    delete ui;
}

void QSttCreateNewDeviceWidget::UI_SetFont()
{
	ui->m_Btn_OK->setFont(m_font);
	ui->m_Btn_Cancel->setFont(m_font);
	ui->m_lblDvmFile->setFont(m_font);
	ui->m_edtDvmFile->setFont(m_font);
	ui->m_btnBrowseDvm->setFont(m_font);
	ui->m_lblProtolID->setFont(m_font);
	ui->m_cmbProtolID->setFont(m_font);
	ui->m_lblPpFile->setFont(m_font);
	ui->m_edtPpFile->setFont(m_font);
	ui->m_lblDevIP->setFont(m_font);
	ui->m_edtDevIP->setFont(m_font);
	ui->m_lblDevPort->setFont(m_font);
	ui->m_edtDevPort->setFont(m_font);
	ui->m_lblDeviceType->setFont(m_font);
	ui->m_cmbDeviceType->setFont(m_font);
}

void QSttCreateNewDeviceWidget::EnableOK()
{
	if (g_theGbSmartGenWzd->ValidateCreateParas())
	{
		ui->m_Btn_OK->setDisabled(false);
	}
	else
	{
		ui->m_Btn_OK->setDisabled(true);
	}
}

void QSttCreateNewDeviceWidget::SaveDevInfoToCfg()
{
	if (g_theGbSmartGenWzd->m_strEngineProgID == STT_IOT_PP_TYPE_CmsEngine)  //原先为_T("DltEngine.PoEngine")
	{
		SaveDevInfoToCfg_CMS();
	}
	else if (g_theGbSmartGenWzd->m_strEngineProgID == STT_IOT_PP_TYPE_MmsEngine) //原先为_T("PpMmsEngine.PoEngine")
	{
		SaveDevInfoToCfg_MMS();
	}
}

void QSttCreateNewDeviceWidget::SaveDevInfoToCfg_MMS()
{
	//以下是PpMmsEngine需要用到的配置文件
	CString strName = GetFileTitleFromFilePath(g_theGbSmartGenWzd->m_strDvmFile, '/');
	CMMS_STACK_CFG oMMS_STACK_CFG;
	oMMS_STACK_CFG.Open_MMS_STACK_CFG_Outer();
	CStkCfg_RemoteAddressList *pRemoteAddressList = oMMS_STACK_CFG.GetRemoteAddressList();
	long nIndex = 0;
	pRemoteAddressList->SetCount(1);
	CStkCfg_RemoteAddress *pAddress = (CStkCfg_RemoteAddress *)pRemoteAddressList->GetAtIndex(0);
	pAddress->SetIP(g_theGbSmartGenWzd->m_strDevIP);
	pAddress->m_strModel = strName;

	oMMS_STACK_CFG.Save_MMS_STACK_CFG_Outer();
	oMMS_STACK_CFG.WriteIpToVMDFile();

	//以下是规约后台用到的对象
	m_oCommConfig.InitEngine(strName, STT_IOT_PP_TYPE_MmsEngine, g_theGbSmartGenWzd->m_strPpFile, g_theGbSmartGenWzd->m_strDvmFile);
	m_oCommConfig.MMS_Init(m_strLocalIP, g_theGbSmartGenWzd->m_strDevIP, g_theGbSmartGenWzd->m_nDevPort);
}

void QSttCreateNewDeviceWidget::SaveDevInfoToCfg_CMS()
{
	//以下是DltEngine需要用到的配置文件
	CString strName = GetFileTitleFromFilePath(g_theGbSmartGenWzd->m_strDvmFile, '/');
	CString strPath;
	strPath = _P_GetInstallPath();
	strPath += _T("e-Protocol\\Config\\");    //需要将DltEngine.exe的工作目录，与PpMmsEngine一致。这样，模型文件的路径好固定下来
	strPath += _T("860ClientConfig.xml");
	C61850ClientConfig o61850ClientConfig;

	if (o61850ClientConfig.OpenClientConfg(strPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("配置文件(%s)打开成功."),strPath);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("配置文件(%s)打开失败."),strPath);
		return;
	}

	CRemoteDev *pRemoteDev = o61850ClientConfig.GetRemoteDev(0);
	pRemoteDev->m_strIP = g_theGbSmartGenWzd->m_strDevIP;
	pRemoteDev->m_strName = strName;
	o61850ClientConfig.SaveClientConfg();

	//以下是规约后台用到的对象
	m_oCommConfig.InitEngine(strName, STT_IOT_PP_TYPE_CmsEngine, g_theGbSmartGenWzd->m_strPpFile, g_theGbSmartGenWzd->m_strDvmFile);
	m_oCommConfig.CMS_Init(m_strLocalIP, g_theGbSmartGenWzd->m_strDevIP, g_theGbSmartGenWzd->m_nDevPort);
}

void QSttCreateNewDeviceWidget::slot_OKClick()
{
	if (!g_theTestCntrFrame->IsContinueCreateNew())
	{
		return;
	}

	g_theTestCntrFrame->EnableStartStopButton(FALSE);
	g_theGbSmartGenWzd->InitCreateParas_Device();
	SaveDevInfoToCfg();
	accept();
}

void QSttCreateNewDeviceWidget::slot_CancelClick()
{
	reject();
}

void QSttCreateNewDeviceWidget::slot_SelDvmFileClick()
{
// 	QStringList astrPostfix;
// 	CString strFolderPath;
// 	strFolderPath = _P_GetInstallPath();
// 	strFolderPath += _T("e-Protocol/Library");
// 	astrPostfix<<"*.xml";	
// 	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
// 	oOpenDlg.setFont(font());
// 	oOpenDlg.InitUI();
// 	CString strTitle;
// 	strTitle = "打开模型文件：";
// 	strTitle += " [";
// 	strTitle += strFolderPath;
// 	strTitle += "]";
// 	oOpenDlg.setWindowTitle(strTitle);
// 
// 	if (oOpenDlg.exec() != QDialog::Accepted)
// 		return;
// 
// 	if (!oOpenDlg.GetFilePath(g_theGbSmartGenWzd->m_strDvmFile))
// 	{
// 		return;
// 	}

	QSttTestCntrFrameWin *pFrame = (QSttTestCntrFrameWin *)g_theTestCntrFrame;
	CString strFile = pFrame->OpenDvmFileDlg(_T(""), TRUE);

	if (strFile.GetLength() <= 4)
	{
		return;
	}

	g_theGbSmartGenWzd->m_strDvmFile = strFile;
	CString strFileName;
	strFileName = GetFileNameFromFilePath(g_theGbSmartGenWzd->m_strDvmFile, '/');
	ui->m_edtDvmFile->setText(strFileName);
	EnableOK();
}

void QSttCreateNewDeviceWidget::slot_SelPpFileClick()
{
// 	QStringList astrPostfix;
// 	CString strFolderPath;
// 	strFolderPath = _P_GetInstallPath();
// 	strFolderPath += _T("e-Protocol/Template");
// 	astrPostfix<<"*.ppxml";	
// 	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
// 	oOpenDlg.setFont(font());
// 	oOpenDlg.InitUI();
// 	CString strTitle;
// 	strTitle = "打开规约模板文件：";
// 	strTitle += " [";
// 	strTitle += strFolderPath;
// 	strTitle += "]";
// 	oOpenDlg.setWindowTitle(strTitle);
// 
// 	if (oOpenDlg.exec() != QDialog::Accepted)
// 		return;
// 
// 	if (!oOpenDlg.GetFilePath(g_theGbSmartGenWzd->m_strPpFile))
// 	{
// 		return;
// 	}

	QSttTestCntrFrameWin *pFrame = (QSttTestCntrFrameWin *)g_theTestCntrFrame;
	CString strFile = pFrame->OpenPpxmlFileDlg(TRUE);

	if (strFile.GetLength() <= 6)
	{
		return;
	}

	g_theGbSmartGenWzd->m_strPpFile = strFile;
	CString strFileName;
	strFileName = GetFileNameFromFilePath(g_theGbSmartGenWzd->m_strPpFile, '/');
	ui->m_edtPpFile->setText(strFileName);
	EnableOK();
}

void QSttCreateNewDeviceWidget::slot_SelIedFromSclClick()
{
	CSclStation *pScl = g_theTestCntrFrame->GetSclStation();

	if (pScl->GetCount() == 0)
	{
		BOOL bOk = g_theTestCntrFrame->OpenSclFile();

		if (!bOk)
		{
			return;
		}
	}

	CString strModelFilePath;

	if (pScl->GetSelectedIed() == NULL)
	{
		strModelFilePath = g_theTestCntrFrame->SelIedFromScl();
	}

	CSclIed* pIed = pScl->GetSelectedIed();

	if(pIed == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("未选择IED"));
	}
	else
	{
		strModelFilePath = pIed->m_strDvmFilePath;
		g_theGbSmartGenWzd->m_strDevIP = pIed->m_strIP;
		ui->m_edtDevIP->setText(g_theGbSmartGenWzd->m_strDevIP);

		g_theGbSmartGenWzd->m_strDvmFile = strModelFilePath;

		CString strFileName;
		strFileName = GetFileNameFromFilePath(strModelFilePath, '/');
		ui->m_edtDvmFile->setText(strFileName);
	}
}

void QSttCreateNewDeviceWidget::slot_AdvancedCfgClick()
{

}

void QSttCreateNewDeviceWidget::on_m_edtDevIP_textChanged(const QString &arg1)
{
	g_theGbSmartGenWzd->m_strDevIP = arg1;
    EnableOK();
}

void QSttCreateNewDeviceWidget::on_m_edtDevPort_textChanged(const QString &arg1)
{
	g_theGbSmartGenWzd->m_nDevPort = CString_To_long(arg1);
    EnableOK();
}

void QSttCreateNewDeviceWidget::on_m_cmbEngineID_currentIndexChanged(int index)
{
	if (index < 0)
	{
		index = ui->m_cmbProtolID->currentIndex();
	}

	CDvmData *pEngine = (CDvmData*)g_theGbSmartGenWzd->m_pProtocolEngineCfg->GetAtIndex(index);
	g_theGbSmartGenWzd->m_strEngineProgID = pEngine->m_strID;
	EnableOK();

	if (g_theGbSmartGenWzd->m_strEngineProgID != STT_IOT_PP_TYPE_PpEngine)  //原先为_T("PpEngine.PoEngine")
	{
		ui->m_edtPpFile->setDisabled(TRUE);
		ui->m_btnBrowsePp->setDisabled(TRUE);
	}
	else
	{
		ui->m_edtPpFile->setDisabled(FALSE);
		ui->m_btnBrowsePp->setDisabled(FALSE);
	}
}

void QSttCreateNewDeviceWidget::on_m_cmbDeviceType_currentIndexChanged(int index)
{
	CExBaseObject *pSel = ex_ComboBox_GetSelObj(ui->m_cmbDeviceType, index);

	if (pSel != NULL)
	{
		g_theGbSmartGenWzd->m_strDeviceType = pSel->m_strID;
	}
}
