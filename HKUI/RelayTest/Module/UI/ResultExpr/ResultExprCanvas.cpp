#include "ResultExprCanvas.h"

#include <QPainter>

QResultExprCanvas::QResultExprCanvas(QWidget *parent) : QResultExprWidget(parent)
{
	m_pRsltExpr = NULL;
    m_pRoot = NULL;
	setBackgroundColor(QColor(255, 255, 255));

	CXExprXmlRWKeys::Create();
}

QResultExprCanvas::~QResultExprCanvas()
{
	CXExprXmlRWKeys::Release();
}

CSttItemRsltExpr* QResultExprCanvas::NewRoot(CSttItemRsltExpr* pItemBase, CSttItemBase* pSttItemBase, CSttReports* pReports, CSttGuideBook* pGuideBook, CTestMacros* pTestMacros)
{
	if(!m_pRoot)
	{
		m_pRoot = new QResultExprWidget_Node(this);
		m_pRoot->SetReportDatas(pReports);
		m_pRoot->SetGuideBookDatas(pGuideBook);
		m_pRoot->SetSttItemBase(pSttItemBase);
		m_pRoot->SetTestMacros(pTestMacros);
		m_pRoot->SetCanvasWidget(this);
		if(pItemBase)
		{
			m_pRsltExpr = pItemBase;
			LoadExprBase(m_pRsltExpr);
		}
		else
		{
			m_pRsltExpr = new CSttItemRsltExpr;
			m_pRoot->SetExprBase(m_pRsltExpr);
		}
	}

	return m_pRsltExpr;
}

void QResultExprCanvas::paintEvent(QPaintEvent *event)
{
    QResultExprWidget::paintEvent(event);

	UpdateArea();
}

void QResultExprCanvas::SaveExprBase()
{
	m_pRoot->SaveExprBase();
}

void QResultExprCanvas::LoadExprBase(CXExprBase* pExprBase)
{
	m_pRoot->SetExprBase(pExprBase);
	m_pRoot->LoadExprBase(pExprBase);
}

void QResultExprCanvas::UpdateArea()
{
	adjustSize();
}