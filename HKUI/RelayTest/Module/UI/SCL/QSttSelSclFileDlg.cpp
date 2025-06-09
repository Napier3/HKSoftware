#include "QSttSelSclFileDlg.h"
#include "../SttTestCntrFrameApi.h"
#include "../../XLangResource_Native.h"
#include <QApplication>

QSttSelSclFileDlg::QSttSelSclFileDlg(QWidget *parent)
	: QDialog(parent)
{
	m_pSttSelSclFileWidget = NULL;
}

QSttSelSclFileDlg::~QSttSelSclFileDlg()
{

}

void QSttSelSclFileDlg::InitUI()
{
#ifdef _PSX_QT_LINUX_
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	long nWidth = stt_FrameTestCntrFrameWidth()-10;
	long nHeight = stt_FrameTestCntrFrameHeight()-30;
	resize(nWidth,nHeight);
	this->setFixedWidth(nWidth);
	this->setFixedHeight(nHeight);
 #else
	this->setFixedWidth(800/*nWidth*/);
	this->setFixedHeight(600/*nHeight*/);
#endif
// 	Qt::WindowFlags flags=Qt::Dialog;  
// 	flags |=Qt::WindowMinMaxButtonsHint;  
// 	flags |=Qt::WindowCloseButtonHint;  
// 	setWindowFlags(flags); 
// // 	QRect rcScreen = QApplication::desktop()->availableGeometry();
// // 	long nWidth = rcScreen.width();
// // 	long nHeight = rcScreen.height() - 30;
// // 	long nTmp = nWidth*0.8;
// // 
// // 	if (nHeight<nTmp)
// // 	{
// // 		nWidth = (nHeight/0.8);
// // 	} 
// // 	else
// // 	{
// // 		nHeight = nTmp;
// // 	}
// #endif
//  	resize(1000,650);
//  	this->setFixedWidth(1000);
//  	this->setFixedHeight(650);
	CString strTitle,strTemp;
	//strTitle = _T("选择SCL文件");
//	xlang_GetLangStrByFile(g_sLangTxt_Native_SCLPath,"IEC_Select");
	setWindowTitle(g_sLangTxt_Native_SCLPath);
	m_pMainVLayout = new QVBoxLayout;
	m_pSttSelSclFileWidget = new QSttSelSclFileWidget(this);
	m_pSttSelSclFileWidget->InitUI();

	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setFixedWidth(60);
	//strTemp = _T("确定");
//	xlang_GetLangStrByFile(g_sLangTxt_Native_OK,"Native_OK");
	m_pOK_PushButton->setText(g_sLangTxt_OK);

// 	m_pCancel_PushButton = new QPushButton(this);
// 	strTemp = _T("取消");
// 	m_pCancel_PushButton->setText(strTemp);

	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);
//	m_pOK_CancelHLayout->addWidget(m_pCancel_PushButton);
	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);

	m_pMainVLayout->addWidget(m_pSttSelSclFileWidget);
	m_pMainVLayout->addLayout(m_pOK_CancelHLayout);
	setLayout(m_pMainVLayout);
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
//	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QSttSelSclFileDlg::slot_OKClicked()
{
	QDialog::accept();
}

// void QSttSelSclFileDlg::slot_CancelClicked()
// {
// 	close();
// }
