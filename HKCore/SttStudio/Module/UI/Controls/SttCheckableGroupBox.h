#ifndef QSTTCHECKABLEGROPBOX_H
#define QSTTCHECKABLEGROPBOX_H

#include <QGroupBox>


class QSttCheckableGroupBox: public QGroupBox
{
	Q_OBJECT

public:
	QSttCheckableGroupBox(QWidget *parent = NULL);
	~QSttCheckableGroupBox();

public:
	void InitStyleSheet();


};
extern QFont *g_pSttGlobalFont;

#endif  
