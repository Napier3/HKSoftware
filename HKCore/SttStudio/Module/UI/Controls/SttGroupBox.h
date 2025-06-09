#ifndef QSTTGROPBOX_H
#define QSTTGROPBOX_H

#include <QGroupBox>

class QSttGroupBox : public QGroupBox
{
	Q_OBJECT

public:
	QSttGroupBox(QWidget *parent = NULL);
	QSttGroupBox(const QString &text,QWidget *parent = NULL);
	~QSttGroupBox();

public:
	void InitStyleSheet();

protected slots:
	
};

extern QFont *g_pSttGlobalFont;

#endif // QSTTGROPBOX_H
