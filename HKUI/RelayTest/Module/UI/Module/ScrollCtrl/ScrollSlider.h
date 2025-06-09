#ifndef ScrollSlider_H
#define ScrollSlider_H

#include <QSlider>

class ScrollSlider : public QSlider 
{
public:
	ScrollSlider(QWidget *parent = 0);
	void paintEvent(QPaintEvent *event);

protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);

private:
	QPoint m_lastMousePos;

};

#endif//ScrollSlider_H