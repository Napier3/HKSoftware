#ifndef QTEMPLATEWIDGETOFOVERCURRENT_H
#define QTEMPLATEWIDGETOFOVERCURRENT_H

#include <QObject>
#include <QSplitter>
#include "../Module/TestWinFrame/qtemplatewidget.h"
class QItemTableBase;
class ParaSetWidgetInterface;

class QTemplateWidgetExtend : public QTemplateWidget
{
	Q_OBJECT

public:
	QTemplateWidgetExtend();
	virtual ~QTemplateWidgetExtend();

	QItemTableBase* getItemTableWidget(){
		return m_TestTable;
	}

	ParaSetWidgetInterface* getParaSetWidget(){
		return m_ParaSetWidgetInterface;
	}

	QSplitter *m_pSplitterV;

public:
	virtual void initUI();

	QItemTableBase* m_TestTable;
	ParaSetWidgetInterface* m_ParaSetWidgetInterface;
};

#endif // QTEMPLATEWIDGETOFOVERCURRENT_H
