#ifndef QSttIecSmvDiscretCharWidget_H
#define QSttIecSmvDiscretCharWidget_H

#include <QWidget>
#include <QMap>
#include <QVector>
#include <QObject>
#include <qwt.h>
#include <qwt_plot_multi_barchart.h>
#include "SttIecSmvDiscretChartAxis.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDevice92.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DISCRETCHARCOLUMN 7 //柱形图柱子个数

class QSttIecSmvDiscretCharWidget : public QWidget
{//柱状图绘图
	Q_OBJECT
public:
	QSttIecSmvDiscretCharWidget(QWidget* parent = 0);
	~QSttIecSmvDiscretCharWidget();
	QSttIecSmvDiscretChartAxis *m_pDiscretChart;

	virtual void resizeEvent(QResizeEvent *pReSizeEvent);
	/*virtual void timerEvent(QTimerEvent *event);*/
	void InitAxisTitle(QString xlabel, QString ylabel);
	void PrepareData();
	void GetMaxTimeDiscrete(CCapDeviceBase *pCapDevice);
	void SetMaxTimeDiscreteCount();
	void GetMaxPkgCount();//获取最大报文数
	CCapDevice92 *m_pCapDevice92;
	int m_nMaxPkgNum;
private:
	int m_nDisCretNum[DISCRETCHARCOLUMN];

};

#endif
