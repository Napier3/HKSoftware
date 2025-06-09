#ifndef QITEMPARAEDITWIDGETBASE_H
#define QITEMPARAEDITWIDGETBASE_H

#include <QWidget>
#include "../../SttCmd/GuideBook/SttMacroTest.h"

class QItemParaEditWidgetBase : public QWidget
{
	Q_OBJECT

public:
	QItemParaEditWidgetBase(QWidget *parent);
	virtual ~QItemParaEditWidgetBase();

public:
	virtual void InitUI();
	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
public:
	CSttMacroTest *m_pCurrMacroTest;//��ǰ����������

	
};

#endif // QITEMPARAEDITWIDGETBASE_H
