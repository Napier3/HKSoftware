#ifndef QSTTGROPBOX_H
#define QSTTGROPBOX_H

#include <QGroupBox>
#include "../../../../Module/OSInterface/OSInterface.h"

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

extern CFont *g_pSttGlobalFont;

#endif // QSTTGROPBOX_H
