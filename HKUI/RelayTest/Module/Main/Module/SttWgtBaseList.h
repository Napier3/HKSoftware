#ifndef QSTTWGTBASELIST_H
#define QSTTWGTBASELIST_H

#include "../../../Module/BaseClass/ExBaseList.h"
#include "SttWgtBase.h"

class QSttWgtBaseList : public QSttWgtBase, public CTLinkList <QSttWgtBase>
{
public:
	QSttWgtBaseList(QWidget* pParent = NULL);
	virtual ~QSttWgtBaseList();

};

#endif//!QSTTWGTBASELIST_H