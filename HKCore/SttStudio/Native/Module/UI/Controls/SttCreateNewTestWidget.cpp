#include "SttCreateNewTestWidget.h"
#include "ui_SttCreateNewTestWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../Module/PopupDialog/SttPopupOpenDialog.h"
#include "../../../../Module/BaseClass/QT/ExBaseListComboBox.h"
#include "../../SttGlobalDef.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

//2022-09-10  lijunqing
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
// #include "../../../../61850/Module/61850ClientConfig/61850ClientConfig.h"
//#include "../../../../61850/Module/MMS_STACK_CFG/MMS_STACK_CFG.h"
#include "../SttTestCntrFrameBase.h"
#include "../../../../IotProtoServer/Module/SttPxCommCmdDef.h"
#include "SttTestCntrFrameWin.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;

QSttCreateNewTestWidget::QSttCreateNewTestWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttCreateNewTestWidget)
{
    ui->setupUi(this);
	InitLanguage();
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

	m_strLocalIP = _T("172.21.0.123");
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
	//ui->m_cmbProtolID->setCurrentIndex(0);
	ui->m_cmbProtolID->setCurrentIndex(g_theGbSmartGenWzd->GetEngineProgIDIndex());

	if (g_theGbSmartGenWzd->m_nIsTimeSetsUnit_ms)
	{
		ui->m_chkTSettingUnit_ms->setCheckState(Qt::Checked);
	}
	else
	{
		ui->m_chkTSettingUnit_ms->setCheckState(Qt::Unchecked);
	}

	if (g_theGbSmartGenWzd->m_nIsAddDevReset)
	{
		ui->m_chkAddDevReset->setCheckState(Qt::Checked);
	}
	else
	{
		ui->m_chkAddDevReset->setCheckState(Qt::Unchecked);
	}

	//2022-9-28  lijunqing
	CDataGroup *pDeviceTypeDef = CGbWzdItemsNameLib::GetDeviceTypeDef();
	if (pDeviceTypeDef != NULL)
	{
		ex_InsertChildreComboBox(pDeviceTypeDef, ui->m_cmbDeviceType);
		ui->m_cmbDeviceType->setCurrentIndex(GetDeviceTypeIndex(g_theGbSmartGenWzd->m_strDeviceType));
	}

	connect(ui->m_Btn_OK,SIGNAL(clicked()),this,SLOT(slot_OKClick()));
	connect(ui->m_Btn_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
	connect(ui->m_btnBrowseDvm,SIGNAL(clicked()),this,SLOT(slot_SelDvmFileClick()));
	connect(ui->m_btnBrowsePp,SIGNAL(clicked()),this,SLOT(slot_SelPpFileClick()));
	connect(ui->m_btnSelFromScl,SIGNAL(clicked()),this,SLOT(slot_SelIedFromSclClick()));
	connect(ui->m_btnAdvancedCfg,SIGNAL(clicked()),this,SLOT(slot_AdvancedCfgClick()));
}

QSttCreateNewTestWidget::~QSttCreateNewTestWidget()
{
    delete ui;
}

void QSttCreateNewTestWidget::UI_SetFont()
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
	ui->m_chkTSettingUnit_ms->setFont(m_font);
	ui->m_btnSelFromScl->setFont(m_font);
	ui->m_btnAdvancedCfg->setFont(m_font);
	ui->m_btnBrowsePp->setFont(m_font);
}

void QSttCreateNewTestWidget::EnableOK()
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

long QSttCreateNewTestWidget::GetDeviceTypeIndex(const CString &strType)
{
	CDataGroup *pDeviceTypeDef = CGbWzdItemsNameLib::GetDeviceTypeDef();

	if (pDeviceTypeDef == NULL)
	{
		return 0;
	}

	CExBaseObject *pFind = pDeviceTypeDef->FindByID(g_theGbSmartGenWzd->m_strDeviceType);

	if (pFind == NULL)
	{
		return 0;
	}

	return pDeviceTypeDef->FindIndex(pFind);
}

void QSttCreateNewTestWidget::slot_OKClick()
{
	if (!g_theTestCntrFrame->IsContinueCreateNew())
	{
		return;
	}

	//给通讯规约赋值
	long index = ui->m_cmbProtolID->currentIndex();
	CDvmData *pEngine = (CDvmData*)g_theGbSmartGenWzd->m_pProtocolEngineCfg->GetAtIndex(index);
	g_theGbSmartGenWzd->m_strEngineProgID = pEngine->m_strID;

	//给装置类型赋值
	CDataGroup *pDeviceTypeDef = CGbWzdItemsNameLib::GetDeviceTypeDef();

	if (pDeviceTypeDef != NULL)
	{
		long nIndex = ui->m_cmbDeviceType->currentIndex();
		CExBaseObject *pFind = pDeviceTypeDef->GetAtIndex(nIndex);

		if (pFind != NULL)
		{
			g_theGbSmartGenWzd->m_strDeviceType = pFind->m_strID;
		}
	}

	g_theTestCntrFrame->EnableStartStopButton(FALSE);
	g_theGbSmartGenWzd->InitCreateParas_Device();
	g_theGbSmartGenWzd->SaveDevInfoToCfg();
	accept();
}

void QSttCreateNewTestWidget::slot_CancelClick()
{
	reject();
}

void QSttCreateNewTestWidget::slot_SelDvmFileClick()
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

void QSttCreateNewTestWidget::slot_SelPpFileClick()
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

void QSttCreateNewTestWidget::slot_SelIedFromSclClick()
{
	CSclStation *pScl = g_theTestCntrFrame->GetSclStation();
	CString strModelFilePath;
	BOOL bOpenSelIed = FALSE;

	if (pScl->GetCount() == 0)
	{
		BOOL bOk = g_theTestCntrFrame->OpenSclFile();

		if (!bOk)
		{
			EnableOK();
			return;
		}
		else
		{
			bOpenSelIed = TRUE;
		}
	}
	else if (pScl->GetSelectedIed() == NULL)
	{
		strModelFilePath = g_theTestCntrFrame->SelIedFromScl();
		bOpenSelIed = TRUE;
	}

	CSclIed* pIed = pScl->GetSelectedIed();

	if(pIed == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, /*_T("未选择IED")*/g_sLangTxt_Native_IEDNotSel.GetString());
	}
	else
	{
		if (pIed->m_strDvmFilePath == g_theGbSmartGenWzd->m_strDvmFile)
		{
			//如果已经是已选择的IED，说明是第二次点击该按钮；此时需要重新选择IED
			if (!bOpenSelIed)
			{
				strModelFilePath = g_theTestCntrFrame->SelIedFromScl();
				pIed = pScl->GetSelectedIed();
			}
		}

		if(pIed == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR, /*_T("未选择IED")*/g_sLangTxt_Native_IEDNotSel.GetString());
			EnableOK();
			return;
		}
		
		strModelFilePath = pIed->m_strDvmFilePath;
		g_theGbSmartGenWzd->m_strDevIP = pIed->m_strIP;
		ui->m_edtDevIP->setText(g_theGbSmartGenWzd->m_strDevIP);
		g_theGbSmartGenWzd->m_strDvmFile = strModelFilePath;

		CString strFileName;
		strFileName = GetFileNameFromFilePath(strModelFilePath, '/');
		ui->m_edtDvmFile->setText(strFileName);
	}

	EnableOK();
}

void QSttCreateNewTestWidget::slot_AdvancedCfgClick()
{

}

void QSttCreateNewTestWidget::on_m_edtDevIP_textChanged(const QString &arg1)
{
	g_theGbSmartGenWzd->m_strDevIP = arg1;
    EnableOK();
}

void QSttCreateNewTestWidget::on_m_edtDevPort_textChanged(const QString &arg1)
{
	g_theGbSmartGenWzd->m_nDevPort = CString_To_long(arg1);
    EnableOK();
}

void QSttCreateNewTestWidget::on_m_cmbEngineID_currentIndexChanged(int index)
{
	if (index < 0)
	{
		index = ui->m_cmbProtolID->currentIndex();
	}

	CDvmData *pEngine = (CDvmData*)g_theGbSmartGenWzd->m_pProtocolEngineCfg->GetAtIndex(index);
	CString strEngineProgID = pEngine->m_strID;
	//g_theGbSmartGenWzd->m_strEngineProgID = pEngine->m_strID;  //改到点OK中赋值
	EnableOK();

	if (strEngineProgID != STT_IOT_PP_TYPE_PpEngine)  //原先为_T("PpEngine.PoEngine")
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

void QSttCreateNewTestWidget::on_m_cmbDeviceType_currentIndexChanged(int index)
{
	//改到点击OK时，进行赋值
// 	CExBaseObject *pSel = ex_ComboBox_GetSelObj(ui->m_cmbDeviceType, index);
// 
// 	if (pSel != NULL)
// 	{
// 		g_theGbSmartGenWzd->m_strDeviceType = pSel->m_strID;
// 	}
}

void QSttCreateNewTestWidget::on_m_chkTSettingUnit_ms_clicked()
{
	if (Qt::Checked ==ui->m_chkTSettingUnit_ms->checkState() )
	{
		g_theGbSmartGenWzd->m_nIsTimeSetsUnit_ms = 1;
	}
	else
	{
		g_theGbSmartGenWzd->m_nIsTimeSetsUnit_ms = 0;
	}
}


void QSttCreateNewTestWidget::on_m_chkAddDevReset_clicked()
{
	if (Qt::Checked ==ui->m_chkAddDevReset->checkState() )
	{
		g_theGbSmartGenWzd->m_nIsAddDevReset = 1;
	}
	else
	{
		g_theGbSmartGenWzd->m_nIsAddDevReset = 0;
	}
}
void QSttCreateNewTestWidget::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->m_lblDeviceType,g_sLangTxt_Native_DevType,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblProtolID,g_sLangTxt_Native_ProtoEngin,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblDevIP,g_sLangTxt_Native_DevIP,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblDevPort,g_sLangTxt_Native_DevPort,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblDvmFile,g_sLangTxt_ModelFile,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblPpFile,g_sLangTxt_Native_ProtoTemp,XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget_Txt(ui->m_btnBrowseDvm,g_sLangTxt_Browse,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnSelFromScl,g_sLangTxt_Native_SelSCDFile,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnBrowsePp,g_sLangTxt_Browse,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnAdvancedCfg,g_sLangTxt_Native_AdvConfig,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_OK,g_sLangTxt_OK,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_Cancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);


	xlang_SetLangStrToWidget_Txt(ui->m_chkTSettingUnit_ms,g_sLangTxt_Native_TimeSetUnit,XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget_Txt(ui->m_chkAddDevReset,g_sLangTxt_Native_AddDevReset,XLang_Ctrls_QCheckBox);

}
