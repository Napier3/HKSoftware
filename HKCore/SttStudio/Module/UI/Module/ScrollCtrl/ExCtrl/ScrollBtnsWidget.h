#ifndef SCROLLBTNSWIDGET_H
#define SCROLLBTNSWIDGET_H

#include "ScrollExElement.h"
#include "ScrollWidgetEx.h"

class QScrollBtnsWidget : public QScrollWidgetEx
{
public:
	CExBaseList m_oBtnGroup;

public:
	QScrollBtnsWidget(QWidget *parent=0);
	virtual ~QScrollBtnsWidget();

public:
	void OpenConfigXml();
	void OnPaintEvent(QScrollExElement* pElement);

public:
	void paintEvent(QPaintEvent* event);
};

#endif//!SCROLLBTNSWIDGET_H