#include "SttSclIedSketchMapWidget.h"
#include "../../../../../Module/OSInterface/QT/CString_QT.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QEvent>
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"

QSttSclIedSkectMapWidget::QSttSclIedSkectMapWidget(QWidget *parent):QWidget(parent)
{
	m_pSttSclViewWidget = NULL;
	m_pBtnZoomIn = NULL;
	m_pBtnZoomOut = NULL;
}


QSttSclIedSkectMapWidget::~QSttSclIedSkectMapWidget()
{

}

void QSttSclIedSkectMapWidget::InitUI()
{
	CString strText;
	xlang_GetLangStrByFile(strText, "sStrRet");
	m_pBtnZoomOut = new QPushButton(this);
	strText = g_sLangTxt_State_Magnify;
	m_pBtnZoomOut->setText(strText);
	m_pBtnZoomOut->setFont(*g_pSttGlobalFont);
	m_pBtnZoomIn = new QPushButton(this);
	strText = g_sLangTxt_State_Shrink;
	m_pBtnZoomIn->setText(strText);
	m_pBtnZoomIn->setFont(*g_pSttGlobalFont);


	QHBoxLayout *pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->setMargin(0);
	pHBoxLayout->addStretch();
	pHBoxLayout->addWidget(m_pBtnZoomOut);
	pHBoxLayout->addWidget(m_pBtnZoomIn);

	m_pSttSclViewWidget = new QSttSclIedDrawViewWidget;
	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->setMargin(0);
	pMainLayout->addLayout(pHBoxLayout);
	pMainLayout->addWidget(m_pSttSclViewWidget);
	setLayout(pMainLayout);


	InitConnection();
}

void QSttSclIedSkectMapWidget::InitConnection()
{
	connect(m_pBtnZoomOut, SIGNAL(clicked()), this,SLOT(slot_ZoomOut()));
	connect(m_pBtnZoomIn, SIGNAL(clicked()),this, SLOT(slot_ZoomIn()));
}

void QSttSclIedSkectMapWidget::ShowIED( CSclIed *pSclIed )
{
	m_pSttSclViewWidget->InitData(pSclIed);
}

void QSttSclIedSkectMapWidget::slot_ZoomIn()
{
	m_pSttSclViewWidget->m_pGraphicsView->scale(0.8, 0.8);
}

void QSttSclIedSkectMapWidget::slot_ZoomOut()
{
	m_pSttSclViewWidget->m_pGraphicsView->scale(1.25, 1.25);
}

void QSttSclIedSkectMapWidget::UpdateViewScale( qreal scale )
{
	m_pSttSclViewWidget->m_pGraphicsView->resetTransform();
	m_pSttSclViewWidget->m_pGraphicsView->scale(scale, scale);
}












