#ifndef ScrollWebView_H
#define ScrollWebView_H

#include "ScrollDef.h"

#ifdef QT_USE_WEBKIT
#include <QWebView>
#endif

#ifdef QT_USE_WEBKIT
class QScrollWebView : public QWebView
#else
class QScrollWebView : public QWidget
#endif
{
	Q_OBJECT
private:
	tagSliderAttri m_oAttri;

public:
	explicit QScrollWebView(QWidget* pParent = NULL);
	virtual ~QScrollWebView();

#ifdef QT_USE_WEBKIT
#else
    void stop() {};
#endif

protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
};

#endif//!ScrollWebView_H
