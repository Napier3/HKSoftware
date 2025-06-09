#include "SttExportPcapFileDialog.h"
#include "../../XLangResource_Native.h"
#include <QFileDialog>
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/API/FileApi.h"
#include "../SttRcdSocketBufferZip.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../../Module/SmartCap/61850Cap/CapGlobalDef.h"

QSttExportPcapFileDialog::QSttExportPcapFileDialog(QWidget *parent)
	: QDialog(parent)
{
}

QSttExportPcapFileDialog::~QSttExportPcapFileDialog()
{

}

void QSttExportPcapFileDialog::InitUI()
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
// 	long nWidth = stt_FrameTestCntrFrameWidth()-10;
// 	long nHeight = stt_FrameTestCntrFrameHeight()-30;
 	resize(500,150);
 	this->setFixedWidth(500);
 	this->setFixedHeight(150);
	CString strTitle,strTemp;
	strTitle = /*_T("导出Pcap文件界面")*/g_sLangTxt_Native_ExpPcapInterf; 
	setWindowTitle(strTitle);
	m_pMainVLayout = new QVBoxLayout;

	strTemp = /*_T("原始数据文件:")*/g_sLangTxt_Native_RawDataFile;
	m_pSrcFile_Label = new QLabel(strTemp,this);
	m_pSrcFilePath_LineEdit = new QLineEdit;
	m_pSrcFilePath_LineEdit->setReadOnly(true);
	strTemp = /*_T("选择...")*/g_sLangTxt_Native_SelectOmit;
	m_pSelSrcFile_Btn = new QPushButton(strTemp);

	m_pSrcFilePathHLayout = new QHBoxLayout;
	m_pSrcFilePathHLayout->addWidget(m_pSrcFile_Label);
	m_pSrcFilePathHLayout->addWidget(m_pSrcFilePath_LineEdit);
	m_pSrcFilePathHLayout->addWidget(m_pSelSrcFile_Btn);

	strTemp = /*_T("Pcap文件名:")*/g_sLangTxt_Native_PcapFileN;
	m_pDstFile_Label = new QLabel(strTemp,this);
	m_pDstFile_LineEdit = new QLineEdit;
//	m_pDstFile_LineEdit->setReadOnly(true);

	m_pDstFileHLayout = new QHBoxLayout;
	m_pDstFileHLayout->addWidget(m_pDstFile_Label);
	m_pDstFileHLayout->addWidget(m_pDstFile_LineEdit);


	strTemp = /*_T("开始转换")*/g_sLangTxt_Native_StartConver;
	m_pStartTrans_PushButton = new QPushButton(this);
	m_pStartTrans_PushButton->setFixedWidth(120);
	m_pStartTrans_PushButton->setText(strTemp);

	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setFixedWidth(60);
	m_pOK_PushButton->setText(g_sLangTxt_Close);

	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addWidget(m_pStartTrans_PushButton);
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);

	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);

	m_pMainVLayout->addLayout(m_pSrcFilePathHLayout);
	m_pMainVLayout->addLayout(m_pDstFileHLayout);
	m_pMainVLayout->addLayout(m_pOK_CancelHLayout);
	setLayout(m_pMainVLayout);
	connect(m_pSelSrcFile_Btn, SIGNAL(clicked()), this, SLOT(slot_SelSrcFileClicked()));
	connect(m_pStartTrans_PushButton, SIGNAL(clicked()), this, SLOT(slot_StartTransClicked()));
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
}

void QSttExportPcapFileDialog::slot_SelSrcFileClicked()
{
	CString strFileName,strFilePath,strTmp;
	strTmp =/*_T("at02d压缩文件(*.at02dz);;at02d文件(*.at02d)")*/g_sLangTxt_Native_at02dCompFiles;
	strFilePath = QFileDialog::getOpenFileName(this,g_sLangTxt_Open,
		_P_GetLibraryPath(),strTmp);

	if (strFilePath.IsEmpty())
	{
		return;
	}

	strFileName = GetFileTitleFromFilePath(strFilePath);
	m_pSrcFilePath_LineEdit->setText(strFilePath);
	m_pDstFile_LineEdit->setText(strFileName);

}

void QSttExportPcapFileDialog::slot_StartTransClicked()
{
	CString strSrcFilePath,strDesFilePath,strDstFileName;
	strDstFileName = m_pDstFile_LineEdit->text();
	strSrcFilePath = m_pSrcFilePath_LineEdit->text();

	if (strSrcFilePath.IsEmpty())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("请先选择原始数据文件.")*/g_sLangTxt_Native_SelectRawFile.GetString());
		return;
	}

	if (strDstFileName.IsEmpty())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("请先设置生成文件名称.")*/g_sLangTxt_Native_SetOutFileName.GetString());
		return;
	}

	if (!IsFileExist(strSrcFilePath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前原始数据文件(%s)不存在.")*/g_sLangTxt_Native_CurRawFileNotEx.GetString(),strSrcFilePath.GetString());
		return;
	}

	CString strPostfix,strAt02dFilePath;
	strAt02dFilePath = strSrcFilePath;
	strPostfix = ParseFilePostfix(strSrcFilePath);
	strPostfix.MakeLower();

	if (strPostfix == _T("at02dz"))
	{
		strAt02dFilePath = ChangeFilePostfix(strSrcFilePath,_T("at02d"));
		stt_rcd_unzip_file(strSrcFilePath.GetString(),strAt02dFilePath.GetString());
	} 

	strDesFilePath = GetPathFromFilePathName(strSrcFilePath);
	strDesFilePath += strDstFileName;
	strDesFilePath += _T(".pcap");
	CString strMsgText;

	if (stt_save_pcap_file(strAt02dFilePath/*.GetString()*/,strDesFilePath.GetString()))
	{
		strMsgText.Format(/*_T("Pcap文件(%s)生成成功.")*/g_sLangTxt_Native_PcapGenSuccess.GetString(),strAt02dFilePath.GetString());
		
	} 
	else
	{
		strMsgText.Format(/*_T("Pcap文件(%s)生成失败.")*/g_sLangTxt_Native_PcapGenFailed.GetString(),strAt02dFilePath.GetString());
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,strMsgText.GetString());
	CXMessageBox::information(this, "", strMsgText, QMessageBox::Ok, QMessageBox::Ok);
	
//	stt_rcd_unzip_file(strSrcFilePath.GetString(),strDesFilePath.GetString());
}

void QSttExportPcapFileDialog::slot_OKClicked()
{
	this->accept();
}
