#ifndef QChMapsQuickWidget_H
#define QChMapsQuickWidget_H

#include "QChMapsAnalogQuickGrid.h"
#include "QChMapsWeakQuickGrid.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

#include <QWidget>
#include <QGridLayout>
#include <QHeaderView>

class QChMapsQuickWidget : public QWidget
{

public:
	QChMapsQuickWidget(CSttChMaps *pChMaps, QWidget *parent);
	~QChMapsQuickWidget();

	void initUI();//添加模拟量电压/电流tab页，是否有弱信号插件tab页并创建表头

public:
	CChMapsAnalogQuickGrid* m_pVoltAnalogQuickGrid;//模拟量电压表头
	CChMapsAnalogQuickGrid* m_pCurAnalogQuickGrid;//模拟量电流表头
	CChMapsWeakQuickGrid* m_pCurWeakQuickGrid;//弱信号表头
	QTabWidget* m_pTabWidget;
	QGridLayout* m_pLayout;//widget中插入电流表电压表，使用布局
	QVBoxLayout* m_pMainLayout;
	CSttChMaps *m_pSttChMaps;

};

#endif // GOOSEPUBWIDGET_H