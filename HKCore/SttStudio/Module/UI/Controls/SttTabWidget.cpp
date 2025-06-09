#include "SttTabWidget.h"
#include "../SttTestCntrFrameBase.h"


QSttTabWidget::QSttTabWidget(QWidget* pParent) : QTabWidget(pParent)
{
	setFocusPolicy(Qt::StrongFocus);
	InitStyleSheet();
//	m_pTbaBar = NULL;
}

QSttTabWidget::~QSttTabWidget()
{
	
}

void QSttTabWidget::InitStyleSheet()
{

// 	QList<QTabBar*> list = findChildren<QTabBar*>();
// 	m_pTbaBar = list.at(0);
	CString strStyle;
	CSttFrameConfig * pSttFrameConfig = CSttFrameConfig::g_pSttFrameConfig;
	long nTabHeight = 40;

	if (pSttFrameConfig != NULL)
	{
		nTabHeight = pSttFrameConfig->GetTabHeight();
	}

#ifdef _PSX_QT_LINUX_
	strStyle.Format("QTabBar:tab{height:%d}", nTabHeight);
	/*m_pTbaBar->*/setStyleSheet(strStyle);
#endif

//	setStyleSheet(g_strQTabWidgetStyleSheet);
}