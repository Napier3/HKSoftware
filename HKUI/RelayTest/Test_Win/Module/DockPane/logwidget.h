#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QColor>
#include <QVector>

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();

    void logString(int nLevel,QString strMsg);
	void addRecord(QColor color, QString description );

private:
    Ui::LogWidget *ui;
    QVector<QColor> m_vColor;
};

#endif // LOGWIDGET_H
