#ifndef QSTTCHECKBOX_H
#define QSTTCHECKBOX_H

#include <QCheckBox>
#include "../../../../Module/OSInterface/OSInterface.h"

class QSttCheckBox : public QCheckBox
{
	Q_OBJECT

public:
	QSttCheckBox(QWidget *parent = NULL);
	QSttCheckBox(const QString &text,QWidget *parent = NULL);
	~QSttCheckBox();

public:
	void InitStyleSheet();

protected slots:
	
};

extern CFont *g_pSttGlobalFont;

#endif // QSTTCHECKBOX_H
