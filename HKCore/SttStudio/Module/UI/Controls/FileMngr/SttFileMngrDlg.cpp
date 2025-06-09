#include "SttFileMngrDlg.h"

#include "SttFileMngrChildren.h"
#include "SttFileMoveDlg.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../Module/DataMngr/DvmData.h"
#include "../../../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

#include <QProcess>
#include <QHeaderView>
#include <QDesktopWidget>
#include <QApplication>

QSttFileMngrDlg::QSttFileMngrDlg(QWidget *parent)
: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	//showFullScreen();//全屏显示
	m_pMemory_PgBar = NULL;
	m_pUsed_Label = NULL;
	m_pAvailable_Label = NULL;
	m_pAvailaText_Label = NULL;
	m_pUsedText_Label = NULL;
	m_pFodlerGrid = NULL;

	InitUI();

}
QSttFileMngrDlg::~QSttFileMngrDlg()
{

}

void QSttFileMngrDlg::InitUI()
{
	//20230829 suyang  336D 分辨率1024x600 
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		resize(850,500);
		this->setFixedWidth(850);
		this->setFixedHeight(500);

	}
	else
	{
	resize(850,700);
	this->setFixedWidth(850);
	this->setFixedHeight(700);
	}



	CString strName ;
	strName =/*_T("文件管理")*/g_sLangTxt_FileMngr;
	setWindowTitle(strName);
	
	CString strTemp;
	m_pMemory_PgBar = new QProgressBar();
	
	//strTemp =_T("已使用");
	m_pUsed_Label = new QLabel(g_sLangTxt_FileMngr_Used);
	m_pUsedText_Label = new QLabel();
	//strTemp = _T("可用");
	m_pAvailable_Label = new QLabel(g_sLangTxt_FileMngr_Available);
	m_pAvailaText_Label = new QLabel();

	m_pMenoryLayout = new QHBoxLayout();
	m_pMenoryLayout->addWidget(m_pUsed_Label);
	m_pMenoryLayout->addWidget(m_pUsedText_Label);
	m_pMenoryLayout->addStretch();
	m_pMenoryLayout->addWidget(m_pAvailaText_Label);
	m_pMenoryLayout->addWidget(m_pAvailable_Label);
	

	strTemp = /*_T("关闭")*/g_sLangTxt_Close;
	m_pCancel_PushButton = new QPushButton(strTemp);
	xlang_SetLangStrToWidget(m_pCancel_PushButton, "sClose", XLang_Ctrls_QPushButton);
	connect(m_pCancel_PushButton,SIGNAL(clicked()),SLOT(slot_CloseClicked()));

	m_pOpen_CancelHLayout = new QHBoxLayout();
	m_pOpen_CancelHLayout->addStretch();
	m_pOpen_CancelHLayout->addWidget(m_pCancel_PushButton);
	m_pOpen_CancelHLayout->setDirection(QBoxLayout::LeftToRight);

	m_pCancel_PushButton->setFixedWidth(80);

	m_pFodlerGrid = new CFileTypeMngrGrid(this);
	m_pFodlerGrid->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	m_pFodlerGrid->SetTableFont(*g_pSttGlobalFont);
	m_pFodlerGrid->AttachDataViewOptrInterface(this);

	m_pMain_VLayout = new QVBoxLayout(this);
	m_pMain_VLayout->addWidget(m_pMemory_PgBar);
	m_pMain_VLayout->addLayout(m_pMenoryLayout);
	m_pMain_VLayout->addWidget(m_pFodlerGrid);
	m_pMain_VLayout->addLayout(m_pOpen_CancelHLayout);


	OpenFileTypeMngr();
	GetDiskInfo();
	SetFileMngrFont();
}

void QSttFileMngrDlg::SetFileMngrFont()
{
	m_pUsed_Label->setFont(*g_pSttGlobalFont);
	m_pUsedText_Label->setFont(*g_pSttGlobalFont);
	m_pMemory_PgBar->setFont(*g_pSttGlobalFont);
	m_pAvailable_Label->setFont(*g_pSttGlobalFont);
	m_pAvailaText_Label->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
}

void QSttFileMngrDlg::OpenFileTypeMngr()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SttFileTypeMngr.xml");

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

//2024.2.23 zyq 文件管理表格多语言处理，直接在文件中进行翻译转换
#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(&m_oDataGroup, _T("SttFileTypeMngr.xml"));
#endif	

	POS pos = m_oDataGroup.GetHeadPosition();
	CDvmData *pDvmData = NULL;
	while(pos)
	{
		pDvmData = (CDvmData *)m_oDataGroup.GetNext(pos);
		CString strSize,strPath;
		strPath = _P_GetSystemPath();
		strPath += pDvmData->m_strDefaultValue;
		CreateAllDirectories(strPath);
		GetFolderSize(strPath,strSize);
		pDvmData->m_strDefaultValue =strPath;
		pDvmData->m_strMax =strSize;

	}
	
	m_pFodlerGrid->ShowDatas(&m_oDataGroup);
	SetFoderIecon();
}

char* QSttFileMngrDlg::Global_GetByteValue(char *pzfString,double &dValue)
{
	if (pzfString == NULL)
	{
		return NULL;
	}

	char *pzfCurrString = pzfString;
	CString strCurrValue;

 	while(*pzfCurrString != '\0')
	{
		if (*pzfCurrString=='M')
		{
			*pzfCurrString = '\0';
			strCurrValue = pzfString;
			dValue = CString_To_double(strCurrValue);
			dValue *= (1024*1024);
			pzfCurrString++;
			break;
		}
		else if (*pzfCurrString=='G')
		{
			*pzfCurrString = '\0';
			strCurrValue = pzfString;
			dValue = CString_To_double(strCurrValue);
			dValue *= (1024*1024*1024);
			pzfCurrString++;
			break;
		}

		pzfCurrString++;
	}

	return pzfCurrString;
}


void QSttFileMngrDlg::GetDiskInfo()
{
	QProcess oProcess;
	CString strCmd,strSizeString,strTemp1,strTemp2;
	oProcess.start("df -h");
	oProcess.waitForFinished();
	QByteArray nSize = oProcess.readAllStandardOutput();

	strSizeString =(const char * ) nSize;
	long nIndex = strSizeString.Find("/dev/mmcblk0p1");

	if (nIndex<0)
	{
		return;
	}

	strTemp1 = strSizeString.Mid(nIndex+ strlen("/dev/mmcblk0p1"));
	nIndex = strTemp1.Find("/mnt");

	if (nIndex<0)
	{
		return;
	}

	strTemp2 = strTemp1.Left(nIndex);
	strTemp2.Replace(" ","");
	char *pzfSizeString = NULL,*pzfCurrPos = NULL;
	CString_to_char(strTemp2,&pzfSizeString);
	double dValue  = 0.0f, dUsed = 0.0f,dAvaila = 0.0f;
	pzfCurrPos = Global_GetByteValue(pzfSizeString,dValue );

	pzfCurrPos = Global_GetByteValue(pzfCurrPos,dUsed);

	CString strSize;
	FileSizeTypeChanged(dUsed,strSize);
	m_pUsedText_Label->setText(strSize);
 
	pzfCurrPos = Global_GetByteValue(pzfCurrPos,dAvaila);
	FileSizeTypeChanged(dAvaila,strSize);
	m_pAvailaText_Label->setText(strSize);

	double nUtilizationRate = 0.00f;
	nUtilizationRate =( dUsed/dValue)*100;
	m_pMemory_PgBar->setValue(nUtilizationRate);
	delete pzfSizeString;

}


void QSttFileMngrDlg::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{

}

BOOL QSttFileMngrDlg::OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar)
{
	CExBaseObject *pData =  m_pFodlerGrid->GetCurrSelData();
	
	if (pData == NULL)
	{
		return TRUE;
	}

	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return TRUE;
	}

#ifdef USE_SttFileMngrChildren
	QSttFileMngrChildren dlg(this);
#else
	QSttFileMoveDlg dlg(this);
#endif
	dlg.setFont(*g_pSttGlobalFont);
	dlg.setWindowTitle(pData->m_strName);
	dlg.SetCurrFileMnrTypeData((CDvmData*)pData);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg, Keyboard::ENGLISH);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif

	return FALSE;
}

// BOOL QSttFileMngrDlg::IsFolderPath(const CString &strPath,CString &strFilePath)
// {
// 	CString strRootPath,strSystemPath,strCurrFilePath;
// 
// // 	if (!_P_GetFullPathEx(strPath,strRootPath))
// // 	{
// // 		if (strPath == "Workspace_PATH")
// // 		{
// // 			strRootPath = _P_GetWorkspacePath();
// // 		}
// // 	}
// 
// 	strSystemPath = _P_GetSystemPath();
// 	strCurrFilePath = strSystemPath + strPath;
// 
// 	if (IsFileExist(strCurrFilePath))
// 	{
// 		strRootPath = strCurrFilePath;
// 	}
// 
// 	if (!IsFileExist(strRootPath))
// 	{
// 		CreateAllDirectories(strCurrFilePath);
// 		strRootPath = strCurrFilePath;
// 	}
// 	strFilePath = strRootPath;
// 
// 	return FALSE;
// 	
// }
BOOL QSttFileMngrDlg::GetFolderSize(const CString &strPath,CString &strFileSize)
{
	QProcess oProcess;
	CString strCmd;
	strCmd.Format(_T("du -c %s"),strPath.GetString());
	oProcess.start(strCmd);
	oProcess.waitForFinished();
	QByteArray bSize = oProcess.readAllStandardOutput();

	CString strSize,strTmp1,strTmp2;
	strSize = (const char *)bSize;
	long nIndex = strSize.ReverseFind('t');
	strTmp1 = strSize.Left(nIndex);
	nIndex = strTmp1.ReverseFind('\n');
	strTmp2 = strTmp1.Mid(nIndex+1);
	long totalSize = CString_To_long(strTmp2);

	long nM = totalSize / 1024;
	double nG = 0.0f;
	nG = totalSize/1024/1024;

	CString strFolderSize;

	if (nG >= 1)
	{
		strFolderSize.Format(_T("%.1f G"), nG);
	}
	else if (nM > 0)
	{
		strFolderSize.Format(_T("%d M"), nM);
	} 
	else
	{
		strFolderSize.Format(_T("%d KB"), totalSize);
	}

	strFileSize = strFolderSize;
	return FALSE;

}

BOOL QSttFileMngrDlg::FileSizeTypeChanged(double nSize,CString &strSize)
{
	long nKB_Size = nSize / 1024;
	long nM = nKB_Size / 1024;
	long nK = nKB_Size - nM * 1024;
	double nG = 0.0f;
	nG = nSize/1024/1024/1024;

	CString strFolderSize;

	if (nG >= 1)
	{
		strFolderSize.Format(_T("%.1f G"), nG);
	}
	else if (nM > 0)
	{
		strFolderSize.Format(_T("%d M"), nM);
	} 
	else if (nK > 0)
	{
		strFolderSize.Format(_T("%d KB"), nK);
	}
	else
	{
		strFolderSize.Format(_T("%d B"), nSize);
	}
	strSize = strFolderSize;

	return FALSE;
}

void QSttFileMngrDlg::slot_CloseClicked()
{
	close();
}

void QSttFileMngrDlg::SetFoderIecon()
{
	for (int i = 0;i<= m_pFodlerGrid->rowCount();i++)
	{
		QGV_ITEM *pItem = m_pFodlerGrid->GetCell(i,0); 

		if (pItem == NULL)
		{
			return ;
		}

		CString strPicPath;
#ifdef _PSX_QT_WINDOWS_
		strPicPath = _P_GetResourcePath();
		strPicPath.AppendFormat(_T("folder.png"));
#else
        strPicPath = ":/ctrls/images/folder.png";
#endif		
		pItem->setIcon(QIcon(strPicPath));
	}
}