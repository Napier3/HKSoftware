#ifndef QSTTWGTTEXT_H
#define	QSTTWGTTEXT_H

#include <QLabel>
#include "../Module/SttWgtBaseList.h"

class QSttWgtText : public QSttWgtBaseList, public QLabel
{
public:
	QSttWgtText(QWidget* pParent = NULL);
	virtual ~QSttWgtText();

private:
	void SetWgtStyle(QSttWgtStyle* pStyle);

public:
	virtual void InitUIOwn(CExBaseObject *pSttXuiData);

};

#endif//!QSTTWGTTEXT_H