#include "QSttCommCfgProtocolTemplateDlg.h"
#include <QDirIterator>
#include "../../../../SttCmd/SttParas.h"
#include "../../../../SttGlobalDef.h"
#include "../../../../../../Module/System/TickCount32.h"
#include "../../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../CommonMethod/commonMethod.h"
#include "../../../Module/XLangResource_Native.h"
#include "../CommCfg/QSttCommCfgMainDlg.h"
#include "../../PopupDialog/SttPopupOpenDialog.h"
//extern CString  Global_GetProtolTemplPath();
#include <QFileDialog>

extern CFont *g_pSttGlobalFont;

QSttCommCfgProtocolTemplateDlg::QSttCommCfgProtocolTemplateDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setWindowTitle(CString("规约模板管理"));

	initUI();
	InitDatas();

}

QSttCommCfgProtocolTemplateDlg::~QSttCommCfgProtocolTemplateDlg()
{

}

void QSttCommCfgProtocolTemplateDlg::initUI()
{
	ReleaseUI();
	resize(800, 630);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

  	//QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  	//sizePolicy.setHorizontalStretch(30);
  	//sizePolicy.setVerticalStretch(30);

	QVBoxLayout *pAllVLayout = new QVBoxLayout(this);
	m_pProtocolTmplGrid = new SttCCommCfgProtocolTemplateGrid(this);
	m_pProtocolTmplGrid->InitGrid();
	QHBoxLayout *pUp_HLayout = new QHBoxLayout(this);
	pUp_HLayout->addWidget(m_pProtocolTmplGrid);
	pAllVLayout->addLayout(pUp_HLayout);
	m_pImportProtocol_PushButton = new QPushButton(this);
	m_pImportProtocol_PushButton->setText(CString("导入"));
	
	CString strText;
	//strText = _T("确定");
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(g_sLangTxt_OK);
	
	//strText = _T("取消");
	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(g_sLangTxt_Cancel);
	QHBoxLayout *pOkCancel_HBoxLayout = new QHBoxLayout(this);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->addWidget(m_pImportProtocol_PushButton);
	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(m_pOK_PushButton);
	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(m_pCancel_PushButton);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);
	pAllVLayout->addLayout(pOkCancel_HBoxLayout);
	this->setLayout(pAllVLayout);

 	connect(m_pImportProtocol_PushButton, SIGNAL(clicked()), this, SLOT(slot_ImportProtocolBtnClicked()));
 	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
 	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	SetDialogFont();
}


void QSttCommCfgProtocolTemplateDlg::SetDialogFont()
{
	if (g_pSttGlobalFont == NULL)
	{
		return;
	}
	m_pImportProtocol_PushButton->setFont(*g_pSttGlobalFont);
	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);

}

void QSttCommCfgProtocolTemplateDlg::ReleaseUI()
{

}

void QSttCommCfgProtocolTemplateDlg::InitDatas()
{
	CString strProtPath = Global_GetProtolTemplPath();
	CDataGroup* pDataGroup = ScanDataDir(strProtPath,CString("ppxml"));
	if (pDataGroup != NULL)
	{
		m_pProtocolTmplGrid->ShowDatas(pDataGroup);
	}
}


CDataGroup* QSttCommCfgProtocolTemplateDlg::ScanDataDir(CString strScanPath, CString argFileSuffix)
{
	CDataGroup *dataGrou = new CDataGroup();
	QStringList *pAllFilesList = new QStringList;
	QDir dirProtoDir(strScanPath);
	if (!dirProtoDir.exists())
	{
		//return NULL; 
	}
	dirProtoDir.setFilter(QDir::Files | QDir::NoSymLinks);
	QFileInfoList oSubFilesList = dirProtoDir.entryInfoList();
	int iSubFilesListCnt = oSubFilesList.count();
	if (iSubFilesListCnt <= 0)
	{
		//return NULL; 
	}
	for (int i=0; i<iSubFilesListCnt; i++)
	{
		QFileInfo oFileInfo = oSubFilesList.at(i);
		QString strSuffix = oFileInfo.suffix();	

		if(QString::compare(strSuffix, argFileSuffix, Qt::CaseInsensitive) == 0)
			//if(QString::compare(suffix, QString("ppxml"), Qt::CaseInsensitive) == 0)
		{
			CDvmData *pData = new CDvmData();
			pData->m_strID = "";

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

			dataGrou->AddNode(pData);
			pAllFilesList->append(fileName);
		}

	}

	return dataGrou;

}

void QSttCommCfgProtocolTemplateDlg::slot_ImportProtocolBtnClicked()
{
	CString strFilePath, strFolderPath;
	strFolderPath = _P_GetInstallPath();
	long nSize = 0;
#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;

	astrPostfix<<"*.ppxml";	
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
	strFilePath = QFileDialog::getOpenFileName(this, g_sLangTxt_Open, _P_GetInstallPath(), _T("规约文件(*.ppxml)"));
#endif

	CString strFileName = strFilePath;
	CString strSrcPath = strFileName;
	int iPos = strSrcPath.ReverseFind('/');
	CString strSelName;
	if (iPos >= 0)
	{
		strSelName=strSrcPath.Mid(iPos+1);
	}
	
	CString strProtPath = Global_GetProtolTemplPath();
	CString strDestPath = strProtPath+strSelName;

	BOOL bRet = X_CopyFile(strSrcPath, strDestPath);
	InitDatas();

	//close();
}
void QSttCommCfgProtocolTemplateDlg::slot_OKClicked()
{
	close();
}

void QSttCommCfgProtocolTemplateDlg::slot_CancelClicked()
{
	close();
}
