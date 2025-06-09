#include "QSttCommCfgPointTblFileImportDlg.h"
#include <QDirIterator>
#include <QMessageBox>
#include <QFileDialog>
#include "../../../../XLangResource_Native.h"
#include "../../../../SmartTestInterface/PpSttCommConfig.h"
#include "../../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../../Module/API/FileApi.h"
#include "QSttCommCfgPointTblFileEditorDlg.h"
#include "../CommCfg/QSttCommCfgMainDlg.h"
#include "../../PopupDialog/SttPopupOpenDialog.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../../SoftKeyboard/SoftKeyBoard.h"
#endif
//extern CString Global_GetPointTbFilePath();
//extern CString  Global_GetProtolTemplPath();
extern QFont *g_pSttGlobalFont;

QSttCommCfgPointTblFileImportDlg::QSttCommCfgPointTblFileImportDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setWindowTitle(CString("点表文件管理"));
	m_strPointTbFileDir = CString("");
	initUI();
	InitDatas();
}

QSttCommCfgPointTblFileImportDlg::~QSttCommCfgPointTblFileImportDlg()
{
}

void QSttCommCfgPointTblFileImportDlg::initUI()
{
	ReleaseUI();
	resize(800, 630);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	QVBoxLayout *pAllVLayout = new QVBoxLayout(this);

	m_pPointTbImportGrid = new SttCCommCfgPointTblFileImportGrid(this);
	m_pPointTbImportGrid->InitGrid();
	m_pPpXmlTreeCtrl = new QSttCommCfgPointTblFileImportTreeCtrl(NULL, this);
	m_pPpXmlTreeCtrl->AttachOptrInterface(this);
	QHBoxLayout *pUp_HLayout = new QHBoxLayout(this);
	m_pPpXmlTreeCtrl->setMaximumWidth(200);
	pUp_HLayout->addWidget(m_pPpXmlTreeCtrl);
	pUp_HLayout->addWidget(m_pPointTbImportGrid);
	pAllVLayout->addLayout(pUp_HLayout);
	m_pImportPointFile_PushButton = new QPushButton(this);
	m_pImportPointFile_PushButton->setText(CString("导入"));
	
	m_pEditPointFile_PushButton = new QPushButton(this);
	m_pEditPointFile_PushButton->setText(CString("点表编辑"));
	
// 	m_pOK_PushButton = new QPushButton(this);
// 	m_pOK_PushButton->setText(g_sLangTxt_OK);
	
	//strText = _T("取消");
	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(g_sLangTxt_Close);
	
	QHBoxLayout *pOkCancel_HBoxLayout = new QHBoxLayout(this);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->addWidget(m_pImportPointFile_PushButton);
	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(m_pEditPointFile_PushButton);
	pOkCancel_HBoxLayout->addSpacing(10);
// 	pOkCancel_HBoxLayout->addWidget(m_pOK_PushButton);
// 	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(m_pCancel_PushButton);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);
	pAllVLayout->addLayout(pOkCancel_HBoxLayout);
	this->setLayout(pAllVLayout);
	connect(m_pImportPointFile_PushButton, SIGNAL(clicked()), this, SLOT(slot_ImportPointBtnClicked()));
	connect(m_pEditPointFile_PushButton, SIGNAL(clicked()), this, SLOT(slot_EditPointBtnClicked()));
	//connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	SetDialogFont();


}

void QSttCommCfgPointTblFileImportDlg::SetDialogFont()
{
	if (g_pSttGlobalFont == NULL)
	{
		return;
	}
	m_pImportPointFile_PushButton->setFont(*g_pSttGlobalFont);
	m_pEditPointFile_PushButton->setFont(*g_pSttGlobalFont);
	//m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
}

void QSttCommCfgPointTblFileImportDlg::ReleaseUI()
{

}

void QSttCommCfgPointTblFileImportDlg::InitDatas()
{
	initTreeDatas();
	initGridData();
}


BOOL QSttCommCfgPointTblFileImportDlg::CheckPpSttCommConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");

	CPpSttCommConfig oCommConfig;
	if (! oCommConfig.OpenCommConfigFile(strFile) )
	{
		return FALSE;
	}
	CString strPpXmlFile = oCommConfig.Get_PpxmlFile();
	if (strPpXmlFile.IsEmpty())
	{
		m_strPointTbFileDir=CString("");
		//QMessageBox oChkBox(QMessageBox::Information,CString("提示"),CString("ppxml-file配置参数空,请首先去通讯配置界面选择"),QMessageBox::Ok);
		//使 MyBox 对话框显示s
		//oChkBox.exec();
		return FALSE;
	}
	int iPos = strPpXmlFile.ReverseFind('.');
	if (iPos >= 0)
	{
		strPpXmlFile = strPpXmlFile.Left(iPos);
	}
	CString strPointTbPath = Global_GetPointTbFilePath();
	CString strPointSubPath = strPointTbPath + strPpXmlFile + CString("/");
	m_strPointTbFileDir = strPointSubPath;
	return TRUE;
}


void QSttCommCfgPointTblFileImportDlg::initGridData()
{
	BOOL isSucc = CheckPpSttCommConfigFile();
	if (!isSucc)
	{
		return;
	}
	CDataGroup* pDataGpList = ScanDataDir(m_strPointTbFileDir, CString("xml"));
	if (pDataGpList != NULL)
	{
		m_pPointTbImportGrid->ShowDatas(pDataGpList);
	}

	//yuanting 2024-01-31
	int nCount = m_pPointTbImportGrid->rowCount();
	if (nCount == 0)
	{
		m_pEditPointFile_PushButton->setEnabled(false);
	}
	else if (nCount > 0)
	{
		m_pEditPointFile_PushButton->setEnabled(true);
		m_pPointTbImportGrid->setCurrentItem(m_pPointTbImportGrid->item(0,1));
	}

}

CDataGroup* QSttCommCfgPointTblFileImportDlg::ScanDataDir(CString strScanPath, CString argFileSuffix)
{
	CDataGroup *dataGrou = new CDataGroup();
	QStringList *pAllFilesList = new QStringList;
	QDir dirProtoDir(strScanPath);
	if (!dirProtoDir.exists())
	{
		return dataGrou; 
	}
	dirProtoDir.setFilter(QDir::Files | QDir::NoSymLinks);
	QFileInfoList oSubFilesList = dirProtoDir.entryInfoList();
	int iSubFilesListCnt = oSubFilesList.count();
	if (iSubFilesListCnt <= 0)
	{
		return dataGrou; 
	}
	for (int i=0; i<iSubFilesListCnt; i++)
	{
		QFileInfo oFileInfo = oSubFilesList.at(i);
		QString strSuffix = oFileInfo.suffix();	
		if (QString::compare(strSuffix, argFileSuffix, Qt::CaseInsensitive) == 0)
			//if(QString::compare(suffix, QString("ppxml"), Qt::CaseInsensitive) == 0)
		{
			CDvmData *pData = new CDvmData();
			pData->m_strID="";

			//QString absolute_file_path = file_info.absoluteFilePath();
			QString fileNameold = oFileInfo.fileName();
			CString fileName = (CString)fileNameold;
			char ch = '.';
			int nPos = fileName.ReverseFind(ch);
			if (nPos >= 0)
			{
				fileName = fileName.Left(nPos);
			}
			pData->m_strName = fileName;
			int iFileSizeK = (int)(oFileInfo.size() / 1024);
			CString strSizeK;
			strSizeK.Format(_T("%dK"), iFileSizeK);
			pData->m_strMin = strSizeK;
			CString crtFileMdyDt = oFileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");
			pData->m_strMax = crtFileMdyDt;		
			CString strAbsPath = oFileInfo.absoluteFilePath();
			pData->m_strValue=strAbsPath;
			dataGrou->AddNode(pData);
			pAllFilesList->append(fileName);
		}

	}
	return dataGrou;

}

void QSttCommCfgPointTblFileImportDlg::slot_ImportPointBtnClicked()
{
	if (m_strPointTbFileDir.IsEmpty())
	{
		return;
	}
	CString strFilePath, strFolderPath;
	strFolderPath = _P_GetInstallPath();
	long nSize = 0;
#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;

	astrPostfix<<"*.xml";	
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
	oOpenDlg.setFont(font());
	oOpenDlg.InitUI();

	if (oOpenDlg.exec() != QDialog::Accepted)
		return;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return;
	}

	nSize = oOpenDlg.GetFileSize();
#else
	strFilePath = QFileDialog::getOpenFileName(this, g_sLangTxt_Open, _P_GetInstallPath(), _T("点表文件(*.xml)"));
#endif

	//CString strFileName = QFileDialog::getOpenFileName(this, g_sLangTxt_Open, _P_GetInstallPath(), _T("点表文件(*.xml)"));
	CString strSrcPath = strFilePath;
	int iPos = strSrcPath.ReverseFind('/');
	CString strSelName;
	if (iPos >= 0)
	{
		strSelName = strSrcPath.Mid(iPos+1);
	}
	CString strDestPath = m_strPointTbFileDir + strSelName;
	BOOL bRet = X_CopyFile(strSrcPath,strDestPath);
	CDataGroup* pDataGpList = ScanDataDir(m_strPointTbFileDir, CString("xml"));
	if (pDataGpList != NULL)
	{
		m_pPointTbImportGrid->ShowDatas(pDataGpList);
	}
}

void QSttCommCfgPointTblFileImportDlg::slot_EditPointBtnClicked()
{
	if (m_pPointTbImportGrid->rowCount() <= 0)
	{
		return;
	}
	int iCrtRow = m_pPointTbImportGrid->currentIndex().row();
	if (iCrtRow < 0)
	{
		return;
	}
	CString strFileName = m_pPointTbImportGrid->item(iCrtRow,0)->text();
	CDvmData *pData = (CDvmData*)m_pPointTbImportGrid->GetCurrSelData();
	if (pData == NULL)
	{
		return;
	}
	if (!pData->m_strValue.IsEmpty())
	{
		CString strFullPath = pData->m_strValue;
		QSttCommCfgPointTblFileEditorDlg editDlg(strFullPath,this);
		//editDlg.exec();

#ifdef _USE_SoftKeyBoard_	
		QSoftKeyBoard::AttachObj(&editDlg, Keyboard::NUMBER);
#endif
		editDlg.exec();
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif


	}

	//close();
}

void QSttCommCfgPointTblFileImportDlg::slot_OKClicked()
{
	close();
}

void QSttCommCfgPointTblFileImportDlg::slot_CancelClicked()
{
	close();
}

void QSttCommCfgPointTblFileImportDlg::initTreeDatas()
{
	CString strProtolTempPath = Global_GetProtolTemplPath();
	CDataGroup* pProtolDataGpList = ScanDataDir(strProtolTempPath, CString("ppxml"));
	if (pProtolDataGpList != NULL)
	{
		pProtolDataGpList->m_strName=CString("规约文件");
		m_pPpXmlTreeCtrl->ShowBaseList(pProtolDataGpList);
	}
}


BOOL QSttCommCfgPointTblFileImportDlg::OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)
{
	if (pSelObj->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		 CDvmData *pDvmData = (CDvmData*)pSelObj;
		 CString strPpxmlFilePath = pDvmData->m_strName;
		 CString strPointTbPath = Global_GetPointTbFilePath();
		 CString strPointSubPath = strPointTbPath + strPpxmlFilePath + CString("/");
		 m_strPointTbFileDir = strPointSubPath;		 
		 CDataGroup* pDataGpList = ScanDataDir(strPointSubPath, CString("xml"));
		 if (pDataGpList != NULL)
		 {
			 m_pPointTbImportGrid->ShowDatas(pDataGpList);
			 if (pDataGpList->GetCount() == 0)
			 {
				// m_pEditPointFile_PushButton->setDisabled(true);
				 m_pEditPointFile_PushButton->setEnabled(false);
			 }
			 else if (pDataGpList->GetCount() > 0)
			 {
				 m_pEditPointFile_PushButton->setEnabled(true);
				 //m_pPointTbImportGrid->SelectRow(0);
				 m_pPointTbImportGrid->setCurrentItem(m_pPointTbImportGrid->item(0,1));
			 }
		 }
	}


	return TRUE;
}

void QSttCommCfgPointTblFileImportDlg::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	if (pSelObj->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		CDvmData *pDvmData = (CDvmData*)pSelObj;
		CString strPpxmlFilePath = pDvmData->m_strName;
		CString strPointTbPath = Global_GetPointTbFilePath();
		CString strPointSubPath = strPointTbPath + strPpxmlFilePath + CString("/");
		m_strPointTbFileDir = strPointSubPath;		 
		CDataGroup* pDataGpList = ScanDataDir(strPointSubPath, CString("xml"));
		if (pDataGpList != NULL)
		{
			m_pPointTbImportGrid->ShowDatas(pDataGpList);
			if (pDataGpList->GetCount() == 0)
			{
				//m_pEditPointFile_PushButton->setDisabled(true);
				m_pEditPointFile_PushButton->setEnabled(false);
			}
			else if (pDataGpList->GetCount() > 0)
			{
				m_pEditPointFile_PushButton->setEnabled(true);
				//m_pPointTbImportGrid->SelectRow(0);
				m_pPointTbImportGrid->setCurrentItem(m_pPointTbImportGrid->item(0,1));
			}

		}
	}
}
