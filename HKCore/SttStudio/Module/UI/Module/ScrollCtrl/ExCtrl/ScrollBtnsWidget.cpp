#include "ScrollBtnsWidget.h"

#include "../../../XLangResource_Native.h"

QScrollBtnsWidget::QScrollBtnsWidget(QWidget *parent) : QScrollWidgetEx(parent)
{
	OpenConfigXml();
}

QScrollBtnsWidget::~QScrollBtnsWidget()
{

}

void QScrollBtnsWidget::OpenConfigXml()
{
	//test
	QScrollExElement* pElement = new QScrollExElement;
	pElement->SetGemoetry(100, 10, 200, 40);
	pElement->SetType(QScrollExElement::TYPE_BUTTON);
    pElement->m_strText = /* "Ê¸Á¿Í¼" */ g_sLangTxt_Native_VecGraphics;
    m_oBtnGroup.AddNewChild(pElement);
	pElement = new QScrollExElement;
	pElement->SetGemoetry(300, 10, 400, 40);
	pElement->SetType(QScrollExElement::TYPE_BUTTON);
    pElement->m_strText = /* "×´Ì¬Í¼" */ g_sLangTxt_Native_StateGraph;
    m_oBtnGroup.AddNewChild(pElement);
	pElement = new QScrollExElement;
	pElement->SetGemoetry(500, 10, 600, 40);
	pElement->SetType(QScrollExElement::TYPE_BUTTON);
    pElement->m_strText = /* "ÐÅÏ¢Í¼" */ g_sLangTxt_Native_InfoChart;
    m_oBtnGroup.AddNewChild(pElement);
}

void QScrollBtnsWidget::OnPaintEvent(QScrollExElement* pElement)
{
	QPainter painter(this);
	DrawRect(&painter, pElement->m_rcLocal);
	DrawText(&painter, pElement->m_rcLocal, pElement->m_strText);
}

void QScrollBtnsWidget::paintEvent(QPaintEvent* event)
{
	POS pos = m_oBtnGroup.GetHeadPosition();
	while (pos)
	{
		QScrollExElement* pElement = (QScrollExElement*)m_oBtnGroup.GetNext(pos);
		OnPaintEvent(pElement);
	}
}