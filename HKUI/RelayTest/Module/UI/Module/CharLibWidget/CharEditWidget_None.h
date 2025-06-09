#ifndef CharEditWidget_None_H
#define CharEditWidget_None_H

#include "CharEditWidgetBase.h"
#include <QLabel>

class QCharEditWidget_None : public QWidget, public QCharEditWidgetBase
{
public:
	QCharEditWidget_None(QWidget* pParent = NULL);
	virtual ~QCharEditWidget_None();

	QLabel *m_pText; 
};

#endif//!CharEditWidget_None_H