#include "ScrollExElement.h"

QScrollExElement::QScrollExElement()
{
	InitUI();
}

QScrollExElement::~QScrollExElement()
{

}

void QScrollExElement::InitUI()
{
	m_tagType = TYPE_TEXT;
}

void QScrollExElement::SetGemoetry(long nLeft, long nTop, long nRight, long nBottom)
{
	m_rcLocal.setLeft(nLeft);
	m_rcLocal.setRight(nRight);
	m_rcLocal.setTop(nTop);
	m_rcLocal.setBottom(nBottom);
}