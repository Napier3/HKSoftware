#ifndef ScrollWebView_H
#define ScrollWebView_H

#include "ScrollDef.h"
#include <QWebView>

class QScrollWebView : public QWebView
{
	Q_OBJECT
private:
	tagSliderAttri m_oAttri;

public:
	explicit QScrollWebView(QWidget* pParent = NULL);
	virtual ~QScrollWebView();

protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
};

#endif//!ScrollWebView_H