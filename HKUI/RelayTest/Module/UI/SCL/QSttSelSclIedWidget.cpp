#include "QSttSelSclIedWidget.h"
#include "../../XLangResource_Native.h"

QSttSelSclIedWidget::QSttSelSclIedWidget(QWidget *parent)
	: QDialog(parent)
{
	m_pMainVLayout = NULL;
	m_pSttSelSclIedGrid =NULL;
}

QSttSelSclIedWidget::~QSttSelSclIedWidget()
{

}

void QSttSelSclIedWidget::InitUI()
{
	resize(800,600);
	this->setFixedWidth(800);
	this->setFixedHeight(600);
	CString strTitle,strTemp;
	//strTitle = _T("IED选择对话框");
//	xlang_GetLangStrByFile(g_sLangTxt_IEDdialog,"IEDdialog");
	setWindowTitle(g_sLangTxt_IEDdialog);
	m_pMainVLayout = new QVBoxLayout;
	m_pSttSelSclIedGrid = new CSttSelSclIedGrid(this);
	m_pSttSelSclIedGrid->InitGrid();

	m_pOK_PushButton = new QPushButton(this);
	//strTemp = _T("关闭");
//	xlang_GetLangStrByFile(g_sLangTxt_Close,"sClose");
	
	if(g_sLangTxt_Close.GetLength())
	{
		m_pOK_PushButton->setText(g_sLangTxt_Close);
	}
	else
	{
		m_pOK_PushButton->setText("关闭");
	}

	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);
	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);

	m_pMainVLayout->addWidget(m_pSttSelSclIedGrid);
	m_pMainVLayout->addLayout(m_pOK_CancelHLayout);
	setLayout(m_pMainVLayout);
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
}

void QSttSelSclIedWidget::InitDatas(CSclStation *pSclStation)
{
	m_pSttSelSclIedGrid->ShowDatas(pSclStation);
}

void QSttSelSclIedWidget::slot_OKClicked()
{
	close();
}

