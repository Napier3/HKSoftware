#include "SttIecCapDialog.h"
#include "../../XLangResource_Native.h"

extern double g_dUIShowCoef; // 界面显示缩放比例

QSttIecCapDialog::QSttIecCapDialog(QWidget *parent)
	: QDialog(parent)
{
	m_pSttIecRecordMainWidget = NULL;
}

QSttIecCapDialog::~QSttIecCapDialog()
{

}

void QSttIecCapDialog::InitUI()
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
// 	long nWidth = g_theTestCntrFrame->m_pSttFrameConfig->m_nWidth-10;
// 	long nHeight = g_theTestCntrFrame->m_pSttFrameConfig->m_nHeight-30;
 	resize(1000*g_dUIShowCoef,600*g_dUIShowCoef);
 	this->setFixedWidth(1000*g_dUIShowCoef);
 	this->setFixedHeight(600*g_dUIShowCoef);
	CString strTitle,strTemp;
	strTitle = /*_T("报文探测界面")*/g_sLangTxt_Gradient_DetectMessageI; //lcq
	setWindowTitle(strTitle);
	m_pMainVLayout = new QVBoxLayout(this);

	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setFixedWidth(60);
	m_pOK_PushButton->setText(g_sLangTxt_Close);

	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);

	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);

	m_pSttIecRecordMainWidget= new QSttIecRecordMainWidget(font(),this);
	m_pSttIecRecordMainWidget->SetIecCapWriteFile(false);
	m_pSttOutPutWidget = new QSttOutPutWidget(this);
	m_pSttOutPutWidget->setFixedHeight(100);
	m_pMainVLayout->addWidget(m_pSttIecRecordMainWidget);
	m_pMainVLayout->addWidget(m_pSttOutPutWidget);
	m_pMainVLayout->addLayout(m_pOK_CancelHLayout);
	setLayout(m_pMainVLayout);
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
}

void QSttIecCapDialog::StartDetect(bool bStartDetect)
{
	if (m_pSttIecRecordMainWidget == NULL)
	{
		return;
	}

	m_pSttIecRecordMainWidget->StartDetect();
}

void QSttIecCapDialog::slot_OKClicked()
{
	this->accept();
}
