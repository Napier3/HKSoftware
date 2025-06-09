#ifndef SttTabWidget_H
#define SttTabWidget_H

#include <QTabWidget>
#include <QTabBar>
#include "../../../../Module/API/GlobalConfigApi.h"

const CString g_strQTabWidgetStyleSheet = _T("QTabBar::tab { ""min-height: 40px;"

// 													 "} QTabBar::tab:selected{ "
// 													 "background-color:rgb(255,192,203);"
// 													 "color:rgb(0,0,0); "//字体颜色
// 
// 													 "} QTabBar::tab:!enabled{ "
// 													 "background-color:rgb(205,205,205);"
// 													 "color:rgb(192,192,192); "//字体颜色
// 													 "margin-left:1px; border:1px;"

													"}");//QTabBar::tab{min-height: 40px;} 


class QSttTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	QSttTabWidget(QWidget* pParent = NULL);
	virtual ~QSttTabWidget();

public:

	void InitStyleSheet();
//	QTabBar* m_pTbaBar;

private:
	

signals:
	
};

#endif//!SttTabWidget_H
