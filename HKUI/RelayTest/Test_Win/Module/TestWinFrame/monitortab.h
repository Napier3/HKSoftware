#ifndef MONITORTAB_H
#define MONITORTAB_H

#include <QWidget>
#include <QTableWidget>
#include "plotWidget/TimeResponseWidget.h"
#include "vectorwidget/vectorwidget.h"
#include "powerWidget/powerWidget.h"
#include "powerWidget/PowerDiagramWidget.h"
#include "seqWidget/seqWidget.h"
#include "lineVoltWidget/lineVoltWidget.h"
#include "infowidget/infowidget.h"

class MonitorTab : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorTab(QWidget *parent = 0);
    ~MonitorTab();

	//重载增加数据监视模块
	virtual void initUI();

	//重载增加数据初始化
	virtual void initData();

	QTabWidget* GetTabWidget(){ 
		return m_tabWidget;
	}

	QTimeResponseWidget* GetTimeResponseWidget(){
		return m_plotWidget;
	}

	VectorWidget* GetVectorWidget(){
		return m_vectorWidget;
	}

	//chenling
	PowerDiagramWidget* GetPowerDiagramWidget()
	{
		return m_powerdiagramWidget;
	}

// 	PowerWidget* GetPowerWidget(){
// 		return m_powerWidget;
// 	}

	SeqWidget* GetSeqWidget(){
		return m_seqWidget;
	}

	LineVoltWidget* GetLineVoltWidget(){
		return m_lineVoltWidget;
	}

	InfoWidget* GetInfoWidget(){
		return m_infoWidget;
	}

public:
    QTabWidget *m_tabWidget;
	QTimeResponseWidget* m_plotWidget;
	VectorWidget *m_vectorWidget;
// 	PowerWidget *m_powerWidget;
	SeqWidget *m_seqWidget;
	LineVoltWidget *m_lineVoltWidget;
	InfoWidget *m_infoWidget;
	PowerDiagramWidget* m_powerdiagramWidget;
};

#endif // MONITORTAB_H
