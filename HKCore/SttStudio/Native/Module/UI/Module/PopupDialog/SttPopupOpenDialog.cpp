#include "SttPopupOpenDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QDirIterator>
#include"../../../Module/API/StringConvert/String_Utf8_To_Gbk.h"
#include"../../../Module/API/StringConvert/String_Gbk_To_Utf8.h"
//#include "../../SttTestCntrFrameBase.h"

QSttPopupOpenDialog::QSttPopupOpenDialog(const CString &strFolderPath,QStringList &astrPostfix ,QWidget *parent,BOOL UseCodeConversion)
	: QSttFileDlgBase(strFolderPath,astrPostfix,parent,UseCodeConversion)
{
	
}

QSttPopupOpenDialog::~QSttPopupOpenDialog()
{
}

void QSttPopupOpenDialog::InitUI()
{
	QSttFileDlgBase::InitUI();

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"Native_ChooseOpenFile");
	//strTemp = QObject::tr("选择需要打开的文件");
	setWindowTitle(strTemp);

	xlang_GetLangStrByFile(strTemp,"sOpenTip");
	m_pOpenSave_PushButton->setText(strTemp);

	m_pMain_VLayout = new QVBoxLayout(this);
	m_pMain_VLayout->addWidget(m_pSttFileMngrTree);
	m_pMain_VLayout->addLayout(m_pOK_CancelHLayout);

	UpdateFileMngrTree();
	EnableButtons();
}

BOOL QSttPopupOpenDialog::GetFilePath(CString &strFilePath)
{
	if (m_pCurrSelObj == NULL)
	{
		return FALSE;
	}

	CXFile *pXFile = (CXFile *)m_pCurrSelObj;
	strFilePath = pXFile->GetRelativePath(TRUE);

// 	if (m_bUseCodeConversion)
// 	{
// 		CString strGbk;
// 		utf8_to_gbk(strFilePath,strGbk);
// 		strFilePath = strGbk;
// 	}

// 	CString strSrcPathUTF8,strDesPath;
// 	strDesPath = _P_GetLibraryPath();
// 	strDesPath += pXFile->m_strName;
// 
// 	const unsigned char *pDesPathGBK = (const unsigned char*)strDesPath.GetString();
// 	unsigned char *pDesPathUTF8 = NULL;
// 	int nDesLenth = 0;
// 	gbk_to_utf8_r(pDesPathGBK,strlen((const char *)pDesPathGBK),&pDesPathUTF8,&nDesLenth,0);
// 	strDesPath = (char *)pDesPathUTF8;
// //	pDesPathUTF8 = NULL;
// //	pDesPathGBK = (const unsigned char*)strFilePath.GetString();
// //	nDesLenth = 0;
// //	gbk_to_utf8_r(pDesPathGBK,strlen((const char *)pDesPathGBK),&pDesPathUTF8,&nDesLenth,0);
// //	strFilePath = (char *)pDesPathUTF8;
// 	strDesPath = strFilePath;
// 	strDesPath += _T("1");
// 
// //    if(QFile::copy(strFilePath, strDesPath))
// 	if (X_CopyFile(strFilePath,strDesPath))
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("文件路径从(%s)拷贝到(%s)成功."),strFilePath.GetString(),pDesPathUTF8);
// 	} 
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("文件路径从(%s)拷贝到(%s)失败."),strFilePath.GetString(),pDesPathUTF8);
// 	}

	return TRUE;
}

long QSttPopupOpenDialog::GetFileSize()
{
	if (m_pCurrSelObj == NULL)
	{
		return 0;
	}

	CXFile *pXFile = (CXFile *)m_pCurrSelObj;
// #ifdef _PSX_QT_LINUX_
// 	CString strFilePath;
// 	strFilePath = pXFile->GetTotalFileName();
// 	//在U盘内使用GBK，否则使用utf8
// 	long nSize = pXFile->GetFileSize(strFilePath.Find(_T("/Usb/sda")) == -1);
// #else
	long nSize = pXFile->GetFileSize();
//#endif
	return nSize;
}

void QSttPopupOpenDialog::EnableButtons()
{
	if (m_pCurrSelObj != NULL)
	{
		m_pOpenSave_PushButton->setEnabled(true);
	}
	else
	{
		m_pOpenSave_PushButton->setEnabled(false);
	}
}
